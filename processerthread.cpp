#include "processerthread.h"

ProcesserThread::ProcesserThread(QObject *parent):QThread(parent){
    // Initialize ready as false.
    ready = false;
    result = -1;
}

void ProcesserThread::slotProcessFrame(Mat frame){

    // Update ready as false.
    mutex.lock();
    ready = false;
    mutex.unlock();

    // Process Frame.
    processFrame(frame);

    // Update ready as true.
    mutex.lock();
    ready = true;
    mutex.unlock();

    emit signalProcessFrameResult(result);
}

bool ProcesserThread::isResultReady(){

    // Create local temporary variable
    bool response;

    // Mutex to get ready value.
    response = ready;

    // Return response.
    return response;

}

void ProcesserThread::processFrame(Mat frame){

    result = -1;

    frame.copyTo(image);

    // Convert image to grayscale.
    cvtColor(image,convertedImage,CV_BGR2GRAY);

    // Detect edge.
    Canny(convertedImage,cannyImage,CANNY_THRESHOLD,CANNY_THRESHOLD*3);

    // Dilate image.
    dilate(cannyImage,dilatedImage,getStructuringElement(MORPH_RECT,Size(5,5)));

    // Apply threshold.
    Mat bimage = dilatedImage >= 200;

    // Find contours in image.
    vector<vector<Point> > contours;
    findContours(bimage, contours, RETR_LIST, CHAIN_APPROX_NONE);

    // Create empty image.
    cimage = Mat::zeros(bimage.size(), CV_8UC3);
    vector<RotatedRect> boxes;
    // Fit ellipse and get boxes from contours.
    for(size_t i = 0; i < contours.size(); i++)
    {
        size_t count = contours[i].size();
        if( count < 6 )
            continue;
        drawContours(cimage, contours, (int)i, Scalar::all(255), 1, 8);

        Mat pointsf;
        Mat(contours[i]).convertTo(pointsf, CV_32F);

        RotatedRect box = fitEllipse(pointsf);
        if(!(MAX(box.size.width, box.size.height) > MIN(box.size.width, box.size.height)*30 || box.boundingRect().area() < 3000))
            boxes.push_back(box);

    }

    vector<RotatedRect> boxes2;
    for (int i = 0; i < boxes.size(); ++i) {
        for (int j = 0; j < boxes.size(); ++j) {
            if (i != j && boxes.at(i).boundingRect().contains(boxes.at(j).center)) {
                RotatedRect rect1 = boxes.at(i);
                RotatedRect rect2 = boxes.at(j);
                boxes2.push_back(rect1);
                boxes2.push_back(rect2);
                break;
            }
        }

    }

    if (boxes2.size() == 2) {

        RotatedRect box1 = boxes2.at(0);
        RotatedRect box2 = boxes2.at(1);
        RotatedRect temp;
        if (box1.boundingRect().area() < box2.boundingRect().area()) {
            temp = box2;
            box2 = box1;
            box1 = temp;
        }

        if (box1.boundingRect().contains(box2.center)) {

            rectangle(cimage, box1.boundingRect(), Scalar(255, 0, 0));  // Bigger
            rectangle(cimage, box2.boundingRect(), Scalar(0, 0, 255));  // Smaller
            double sin, cos;
            double tan = calculate(box1.center, box2.center, sin, cos);
            putText(cimage, "Tan : " + to_string(tan), Point(50, 50), 1, FONT_HERSHEY_COMPLEX, Scalar(255, 255, 255));
            putText(cimage, "Sin : " + to_string(sin), Point(50, 130), 1, FONT_HERSHEY_COMPLEX, Scalar(255, 255, 255));
            putText(cimage, "Cos : " + to_string(cos), Point(50, 170), 1, FONT_HERSHEY_COMPLEX, Scalar(255, 255, 255));
            imshow("cimage",cimage);
            if (sin > 0 && cos > 0) {
                result = 0;
            } else if (sin > 0 && cos < 0) {
                result = 1;
            } else if (sin < 0 && cos < 0) {
                result = 2;
            } else
                result = 3;
        }

        emit signalProcessFrameResult(result);
    }
}

int ProcesserThread::getResult(){
    return result;
}

// TODO:: output parametre
double ProcesserThread::calculate(Point2f point1, Point2f point2, double &sin, double &cos) {

    double yDistance = point2.y - point1.y;
    double xDistance = point2.x - point1.x;

    double hipo = sqrt(pow(xDistance,2) + pow(yDistance,2));

    sin = (atan(yDistance / hipo) * 180) / (atan(1) * 4);
    cos = (atan(xDistance / hipo) * 180) / (atan(1) * 4);
    return (atan(sin/cos)*180)/(atan(1)*4);
}
