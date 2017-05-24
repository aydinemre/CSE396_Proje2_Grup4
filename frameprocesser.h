//
// Created by emreaydin on 13.05.2017.
//

enum information{
    isNotOpened = -1,
    cantFindJoe,
    up,
    down,
    left,
    right,
    leftAndUp,
    leftAndDown,
    RightAndUp,
    RightAndDown
};

#ifndef PROJE2V1_FRAMEPROCESSER_H
#define PROJE2V1_FRAMEPROCESSER_H

#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"

using namespace cv;

double calculate(Point2f point1, Point2f point2, double &sin, double &cos);


using namespace std;
using namespace cv;

class FrameProcesser {

public:

    FrameProcesser();
    FrameProcesser(int videoCaptureIndex);

    bool openVideoCapture(int videoCaptureIndex);

    int processFrame(Mat &frame);

    double getAngle();

    bool isFound();

private:

    // counter[0] -> up counter
    // counter[1] -> down counter
    // counter[2] -> left counter
    // counter[3] -> right counter
    // counter[4] -> left and up counter
    // counter[5] -> left and down counter
    // counter[6] -> right and up counter
    // counter[7] -> right and down counter
    int counter[MY_DIRECTIONS]; // Holds counters for 8 direction.

    VideoCapture videoCapture;
    bool isOpened;
    int flag;
    Mat copyFrame;
    bool found;
    double angle;
    Mat image,convertedImage,cannyImage,dilatedImage,cimage;

    Mat cur, cur_grey;
    Mat prev, prev_grey;

    void process();
    void stabilize();

};


#endif //PROJE2V1_FRAMEPROCESSER_H
