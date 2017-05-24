#include "workerthread.h"

WorkerThread::WorkerThread(QObject *parent):QThread(parent)
{
    found = false;
    alive = false;
    angle = -1.0;
}

void WorkerThread::run(){

    alive = true;
    found = false;

    // Check video capture.
    videoCapture.open(0);
    if( !videoCapture.isOpened() ){
        emit threadDebugError("Video capture can't open");
        alive = false;
        return;
    }else
        emit threadDebugLog("Video capture opened");

    // Check Communication.
    com = new Communication("/dev/ttyACM0",SerialPort::BR_9600);
    if( !com->isCommunicationReady()){
      emit threadDebugError("Can't connect to arduino");
      alive = false;
      return;
    }else
        emit threadDebugLog("Communication ready");

    algorithmObject = new algorithm();
    int x = 1;
    int y = 1;
    do{

        // Read frame from video capture.
        for(int i = 0; i < 15; ++i)
            videoCapture >> frame;

        // Copy frame to temproray frame.
        frame.copyTo(processedFrame);

        // Convert BGR image to RGB image.
        cvtColor(processedFrame,processedFrame,COLOR_BGR2RGB);
        // Send signal to show image.
        emit showImage(QImage(processedFrame.data,
                                      processedFrame.cols,
                                      processedFrame.rows,
                                      processedFrame.step,
                                      QImage::Format_RGB888));
        // Process frame.
        processFrame(frame);

        if(!found){
            algorithmObject->Continue(com);
            QString message = QString::number(algorithmObject->getX()) + "-" + QString::number(algorithmObject->getY());
            //emit threadDebugLog(message);
            emit threadUpdateMap(Coor((algorithmObject->getX() +800)/5, (algorithmObject->getY() +675)/5 ));
        }

    }while(alive == true & found == false);

    emit showImage(QImage(frame.data,
                                  frame.cols,
                                  frame.rows,
                                  frame.step,
                                  QImage::Format_RGB888));
    // Show Joe. !!!
    emit threadShowJoe((algorithmObject->getX() +800)/5,(algorithmObject->getY() +675)/5,angle);

    emit threadDebugLog(QString::number(angle));
    // Print Debug.
    emit threadDebugLog("Joe Founded :)");

    alive = false;

}

bool WorkerThread::isAlive(){

    bool response = false;

    response = alive;

    return response;
}

void WorkerThread::terminate(){

    alive = false;
}

void WorkerThread::processFrame(Mat frame){
    result = -1;

    frame.copyTo(image);

    // Convert image to grayscale.
    cvtColor(image,convertedImage,CV_BGR2GRAY);

    // Detect edge.
    Canny(convertedImage,cannyImage,CANNY_THRESHOLD,CANNY_THRESHOLD*3);

    // Dilate image.
    dilate(cannyImage,dilatedImage,getStructuringElement(MORPH_RECT,Size(13,13)));

    // Apply threshold.
    Mat bimage = dilatedImage >= 200;

    // Find contours in image.
    vector<vector<Point> > contours;
    findContours(bimage, contours, RETR_LIST, CHAIN_APPROX_NONE);

    // Create empty image.
    cimage = Mat::zeros(bimage.size(), CV_8UC3);
    vector<RotatedRect> boxes;
    // Fit ellipse and get boxes from contours.
    emit threadDebugLog(QString::number(contours.size()));
    for(size_t i = 0; i < contours.size(); i++)
    {
        size_t count = contours[i].size();
        if( count < 6 )
            continue;
        drawContours(cimage, contours, (int)i, Scalar::all(255), 1, 8);

        Mat pointsf;
        Mat(contours[i]).convertTo(pointsf, CV_32F);

        RotatedRect box = fitEllipse(pointsf);
        if(!(MAX(box.size.width, box.size.height) > MIN(box.size.width, box.size.height)*30 || box.boundingRect().area() < 1000))
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

            rectangle(frame, box1.boundingRect(), Scalar(255, 0, 0));  // Bigger
            rectangle(frame, box2.boundingRect(), Scalar(0, 0, 255));  // Smaller
            double sin, cos;
            double tan = calculate(box1.center, box2.center, sin, cos);

            if (sin > 0 && cos >0) { // 1.bölge
                found = true;
                angle = tan;
                //emit threadDebugLog(QString::number(angle));

            } else if (sin > 0 && cos < 0) { //2.bölge
                found = true;
                angle = (PI/2) + abs(tan);
                //emit threadDebugLog(QString::number(angle));

            } else if (sin < 0 && cos < 0) { //3.bölge
                found = true;
                angle = PI+abs(tan);
                //emit threadDebugLog(QString::number(angle));

            } else{
                found = true;
                angle = (3*(PI/2))+abs(tan);
                //emit threadDebugLog(QString::number(angle));

            }
            angle +=90;
            emit threadDebugLog(QString::number(angle));

        }

    }
}

double WorkerThread::calculate(Point2f point1, Point2f point2, double &sin, double &cos) {
    double yDistance = point2.y - point1.y;
    double xDistance = point2.x - point1.x;

    double hipo = sqrt(pow(xDistance,2) + pow(yDistance,2));

    sin = (atan(yDistance / hipo) * 180) / (atan(1) * 4);
    cos = (atan(xDistance / hipo) * 180) / (atan(1) * 4);
    return (atan(sin/cos)*180)/(atan(1)*4);
}

