//
// Created by emreaydin on 13.05.2017.
//

#include "frameprocesser.h"

FrameProcesser::FrameProcesser() {

    isOpened = false;
    for (int i = 0; i < MY_DIRECTIONS; ++i)
        counter[i]  = 0;
    found = false;

}

FrameProcesser::FrameProcesser(int videoCaptureIndex) {

    isOpened = videoCapture.open(videoCaptureIndex) ? true : false;
    for (int i = 0; i < MY_DIRECTIONS; ++i)
        counter[i]  = 0;
    found = false;
}

bool FrameProcesser::openVideoCapture(int videoCaptureIndex) {

    isOpened = videoCapture.open(videoCaptureIndex) ? true : false;
    return isOpened;

}

int FrameProcesser::processFrame(Mat &frame) {

    if (!isOpened)
        return information::isNotOpened;

    videoCapture >> frame;

}

void FrameProcesser::process() {


}


void FrameProcesser::stabilize() {

}

double FrameProcesser::getAngle() {
    return 0;
}

bool FrameProcesser::isFound() {
    return found;
}

double calculate(Point2f point1, Point2f point2, double &sin, double &cos) {

    double yDistance = point2.y - point1.y;
    double xDistance = point2.x - point1.x;

    double hipo = sqrt(pow(xDistance,2) + pow(yDistance,2));

    sin = (atan(yDistance / hipo) * 180) / (atan(1) * 4);
    cos = (atan(xDistance / hipo) * 180) / (atan(1) * 4);
    return (atan(sin/cos)*180)/(atan(1)*4);
}

