/*--------------- User Interface for Finding Joe ---------------
    |  Author: Semih Bertug Benim
    |  Created on 25.04.2017
    |  ID: 111044073
    |  Lecture: Project II
 *-------------------------------------------------------------------*/

#include "mainwindow.h"
#include <QApplication>
#include <QtWidgets>

// Include opencv headers.
#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"

#include "coor.h"

using namespace cv;

int main(int argc, char *argv[])
{
    // Register Opencv "cv::Mat" Types.
    qRegisterMetaType<Mat>("Mat");

    qRegisterMetaType<Coor>("Coor");

    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
