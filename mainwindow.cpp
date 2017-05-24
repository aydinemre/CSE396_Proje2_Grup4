/*--------------- User Interface for Finding Joe ---------------
    |  Author: Semih Bertug Benim
    |  Created on 25.04.2017
    |  ID: 111044073
    |  Lecture: Project II
 *-------------------------------------------------------------------*/

#include "settings.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "string.h"
#include "Communication.h"
#include "iostream"
#include <fstream>
#include <vector>
#include <QFile>
#include <QTextStream>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    // Setup user interface.
    ui->setupUi(this);

    // Initialize Scenes.
    scene               = new QGraphicsScene(this);
    frameWidgetScene    = new QGraphicsScene(this);

    settings::Secure(this);

    ui->graphicsView->setScene(scene);
    ui->graphicsView_2->setScene(frameWidgetScene);
    //ui->graphicsView_2->setFixedSize(size());

    lastKnownPosition = Coor(-1,-1);

    QPen blackPen(Qt::black); // Main Pen
    QBrush greenBrush(Qt::green); // Main Brush
    blackPen.setWidth(1);

    // Create a Location Marker
    //locationMarker = scene -> addPolygon(QPolygonF( QVector<QPointF>() << QPointF( 20, -20 ) << QPointF( 0, -20) << QPointF( 10, 20)),blackPen,blueBrush);
    locationMarker = scene -> addRect(QRect(0,0,50,40), blackPen, greenBrush);
    //locationMarker->setFlag(QGraphicsItem::ItemIsMovable);
    locationMarker->hide();

    // Show Grid
    drawBackground();

    // Add Joe Asset
    joePixmap = scene -> addPixmap(QPixmap(JOEASSETPATH));
    if(QPixmap(JOEASSETPATH).isNull())
        DebugError("Joe image not found!");
    joePixmap->hide(); // Hide Joe
    joePixmap->setOffset(-0.5 * QPointF(joePixmap->boundingRect().width(), joePixmap->boundingRect().height()));
    joePixmap->setScale(0.2f); // May removed with the new asset

    // Set Timer that updates elapsedTime label every 1 sec.
    updateTimer = false; // Do not update timer panel by default
    timer = new QTimer(this);
    //timer->setTimerType(Qt::PreciseTimer);
    connect(timer, SIGNAL(timeout()), this, SLOT(updateUI()));
    timer->start(16); // Set interval from here for more precise updates

    //drawLine(Coor(0,0), Coor(100,100), blackPen); // Draw a test line
    sb = ui->textEdit->verticalScrollBar();
    mainThread = new WorkerThread(this);

    connect(mainThread,SIGNAL(threadDebugLog(QString)),     this,   SLOT(DebugLog(QString)));
    connect(mainThread,SIGNAL(threadDebugError(QString)),   this,   SLOT(DebugError(QString)));
    connect(mainThread,SIGNAL(threadDebugWarning(QString)), this,   SLOT(DebugWarning(QString)));
    connect(mainThread,SIGNAL(threadclearLines()),          this,   SLOT(clearLines()));
    connect(mainThread,SIGNAL(threadShowJoe(int,int,float)),this,   SLOT(ShowJoe(int,int,float)));
    connect(mainThread,SIGNAL(threadUpdateMap(Coor)),       this,   SLOT(UpdateMap(Coor)));
    connect(mainThread,SIGNAL(showImage(QImage)),this,SLOT(showFrame(QImage)));

    isRunnig    = false;

   // DebugLog(qApp->applicationDirPath());
}

MainWindow::~MainWindow()
{
    delete ui;
}

/* Sends main procedure start signal
 * Now it s only test debug functions
 */
void MainWindow::on_startButton_clicked()
{
    DebugLog("Program Started :)");

    mainThread->start();
    isRunnig = true;

    ui->stopButton->setEnabled(true);
    ui->startButton->setEnabled(false);
    elapsedTime.restart();
    ui->timeLabel->setText("00:00");
    updateTimer = true;
    joePixmap->hide();

}

void MainWindow::on_stopButton_clicked()
{
    DebugLog("Program Stopped");
    ui->stopButton->setEnabled(false);
    ui->startButton->setEnabled(true);
    updateTimer = false;
    isRunnig = false;
}

void MainWindow::UpdateMap(Coor currentPosition)
{
    //locationMarker->show();

    currentPosition.x = map(currentPosition.x, 0 ,950 , 0, 810);
    currentPosition.y = map(currentPosition.y,0,800,0,650);

    QString message = QString::number(currentPosition.x) + "-" + QString::number(currentPosition.y);
    DebugLog(message);
    QPen redPen(Qt::red);
    redPen.setWidth(5);
    if(lastKnownPosition != Coor(-1,-1))
    {
        QGraphicsLineItem *line;
        line = drawLine(lastKnownPosition, currentPosition, redPen);
        drawedLines.push_front(line);
    }
    lastKnownPosition = currentPosition;
    int x =map(currentPosition.x,0,810,0,21);
    int y =map(currentPosition.y,0,650,0,15);
    DebugLog("x:" +QString::number(x) + "y:" + QString::number(y));

}

// Tests Map Function
void MainWindow::on_testMapButton_clicked()
{
    Coor currentPosition = Coor(locationMarker->pos().x(), locationMarker->pos().y());
    UpdateMap(currentPosition);
    ShowJoe(0,0,200);
}

// Tests Debug Panel
void MainWindow::on_testDebugButton_clicked()
{
    DebugLog("Normal Text");
    DebugWarning("Warning Text");
    DebugError("Error Text");
    ShowJoe(50,50,0);
}

/*
 *  Helper Functions
 */

// Shows given text in debug panel
void MainWindow::DebugLog(QString text)
{
    ui->textEdit->append(text);
    sb->setValue(sb->maximum());
}

// Shows given warning text in debug panel as blue
void MainWindow::DebugWarning(QString text)
{
    QString my_formatted_string = QString("<span style=\" font-size:7.8pt; color:#0000ff;\">%1</span>").arg(text);
    DebugLog(my_formatted_string);
}

// Shows given error text in debug panel as red
void MainWindow::DebugError(QString text)
{
    QString my_formatted_string = QString("<span style=\" font-size:7.8pt; color:#ff0000;\">%1</span>").arg(text);
    DebugLog(my_formatted_string);
}

QGraphicsLineItem* MainWindow::drawLine(Coor &c1, Coor &c2, QPen pen)
{
    return scene -> addLine(c1.getX(),c1.getY(),c2.getX(),c2.getY(),pen);
}

void MainWindow::clearLines()
{
    for(int i = 0; i < drawedLines.size(); ++i)
    {
        scene->removeItem(drawedLines[i]);
        scene->update();
    }
}

void MainWindow::updateUI()
{
    if(updateTimer)
    {
        QString out = QString("%1:%2").arg( elapsedTime.elapsed() / 60000        , 2, 10, QChar('0'))
                                      .arg((elapsedTime.elapsed() % 60000) / 1000, 2, 10, QChar('0'));
        ui->timeLabel->setText(out);
    }
}


void MainWindow::ShowJoe(int x, int y, float angle)
{

    int _x = map(x, 0 ,950 , 0, 810);
    int _y = map(y,0,800,0,650);
    joePixmap->setPos(_x,_y);
    joePixmap->setRotation(angle);
    joePixmap->show();
    _x =map(_x,0,810,0,21);
    _y =map(_y,0,650,0,15);
    QString foundMessage = QString("Joe found at [%1-%2] coordinates!").arg(QString::number(x/GRID_SIZE), QString::number(x/GRID_SIZE));
    DebugLog(foundMessage);
    DebugLog("Program Stopped");
    ui->stopButton->setEnabled(false);
    ui->startButton->setEnabled(true);
    updateTimer = false;
}

inline qreal round(qreal val, int step) {
   int tmp = int(val) + step /2;
   tmp -= tmp % step;
   return qreal(tmp);
}

void MainWindow::drawBackground()
{

    QPen _bgPen;  // creates a pen for Background Grids

    _bgPen.setStyle(Qt::DashDotLine);
    _bgPen.setWidth(1);
    _bgPen.setBrush(Qt::gray);
    _bgPen.setCapStyle(Qt::RoundCap);
    _bgPen.setJoinStyle(Qt::RoundJoin);

    // Add the vertical lines
    for (int x=0; x<=405; x+=GRID_SIZE)
    {
        QGraphicsTextItem * io = new QGraphicsTextItem;
        io->setPos(x,1);
        io->setPlainText(QString::number(x/GRID_SIZE));
        io->setScale(0.6);
        scene->addItem(io);
        scene->addLine(x,0,x,500, _bgPen);
    }
    // Add the horizontal lines
    for (int y=0; y<=325; y+=GRID_SIZE)
    {

        if(y != 0)//Visual improvement
        {
            QGraphicsTextItem * io = new QGraphicsTextItem;
            io->setPos(1,y);
            io->setPlainText(QString::number(y/GRID_SIZE));
            io->setScale(0.6);
            scene->addItem(io);
        }
        scene->addLine(0,y,500,y, _bgPen);
    }
    // Fit the view in the scene's bounding rect
    //ui->graphicsView->fitInView(0,0,10,10,Qt::KeepAspectRatio);
}

void MainWindow::showFrame(QImage frame){
    frameWidgetScene->addPixmap(QPixmap::fromImage(frame.scaled(ui->graphicsView_2->size())));
}

int MainWindow::map(int value,int oldMin,int oldMax,int newMin, int newMax){

    int leftSpan = oldMax - oldMin;
    int rightSpan = newMax - newMin;

    double valueScaled = float(value - oldMin) / float(leftSpan);

    return newMin + (valueScaled * rightSpan);
}
