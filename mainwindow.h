/*--------------- User Interface for Finding Joe ---------------
    |  Author: Semih Bertug Benim
    |  Created on 25.04.2017
    |  ID: 111044073
    |  Lecture: Project II
 *-------------------------------------------------------------------*/

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMainWindow>
#include <QtCore>
#include <QtGui>
#include <QGraphicsScene>
#include <QGraphicsEllipseItem>
#include <QGraphicsPolygonItem>
#include <QGraphicsPixmapItem>
#include <QElapsedTimer>
#include <QTimer>
#include "coor.h"
#include "camera.h"
#include <QCloseEvent>
#include <QString>
#include "workerthread.h"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    Ui::MainWindow *ui;
    QGraphicsLineItem *drawLine(Coor &c1, Coor &c2, QPen pen); // Draw A line between 2 coordinates

public slots:
    void DebugLog(QString text);
    void DebugWarning(QString text);
    void DebugError(QString text);
    void ShowJoe(int x, int y, float angle);
    void clearLines(); // Clear all drawed lines
    void UpdateMap(Coor currentPosition);
    void showFrame(QImage frame);

private slots:
    void on_startButton_clicked();
    void on_stopButton_clicked();
    void on_testMapButton_clicked();
    void on_testDebugButton_clicked();
    void updateUI();

private:
    QGraphicsScene *scene;
    QGraphicsScene *frameWidgetScene;
    int map(int,int,int,int,int);
    //QGraphicsPolygonItem *locationMarker;
    QGraphicsRectItem *locationMarker;
    QList<QGraphicsItem *> drawedLines;
    QGraphicsPixmapItem *joePixmap;
    Coor lastKnownPosition;
    QElapsedTimer elapsedTime;
    QScrollBar *sb;
    QTimer *timer;

    bool updateTimer;

    void drawBackground();

    WorkerThread *mainThread;
    bool isRunnig;

};

#endif // MAINWINDOW_H
