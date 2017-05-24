#ifndef PROCESSERTHREAD_H
#define PROCESSERTHREAD_H

#include <QThread>
#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include <QDebug>
#include <QMutex>
#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include <iostream>
#include <string>

#define CANNY_THRESHOLD 50

using namespace cv;
using namespace std;

/**
 * @brief The ProcesserThread class
 * This class is processing frame.
 */
class ProcesserThread : public QThread
{
    Q_OBJECT
public:
    explicit ProcesserThread(QObject* parent=0);
    bool isResultReady();
    int getResult();
    double calculate(Point2f point1, Point2f point2, double &sin, double &cos);

signals:
    void signalProcessFrameResult(int result);

public slots:
    // Start to process frame.
    void slotProcessFrame(Mat frame);

private:
    void processFrame(Mat frame);
    bool ready;
    int result;
    QMutex mutex;
    Mat image,
        convertedImage,
        gaussianImage,
        cannyImage,
        dilatedImage,
        cimage;

};

#endif // PROCESSERTHREAD_H
