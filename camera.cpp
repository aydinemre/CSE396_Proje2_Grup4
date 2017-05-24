#include "camera.h"
#include "ui_mainwindow.h"

#include <QCameraViewfinder>
#include <QCameraInfo>

#include <QtWidgets>

Q_DECLARE_METATYPE(QCameraInfo)

Camera::Camera(QWidget *targetWidget, QMenu *menu)
{
    // Set Up Local Values
    widget = targetWidget;
    menuDevices = menu;

    QActionGroup *videoDevicesGroup = new QActionGroup(this);
    videoDevicesGroup->setExclusive(true);
    foreach (const QCameraInfo &cameraInfo, QCameraInfo::availableCameras()) {
        QAction *videoDeviceAction = new QAction(cameraInfo.description(), videoDevicesGroup);
        videoDeviceAction->setCheckable(true);
        videoDeviceAction->setData(QVariant::fromValue(cameraInfo));
        if (cameraInfo == QCameraInfo::defaultCamera())
            videoDeviceAction->setChecked(true);

        menuDevices->addAction(videoDeviceAction);
    }
    setCamera(QCameraInfo::defaultCamera());
}


Camera::~Camera()
{
    delete camera;
}

void Camera::setCamera(const QCameraInfo &cameraInfo)
{
    camera = new QCamera(cameraInfo);
    viewFinder = new QCameraViewfinder(widget);
    camera->setViewfinder(viewFinder);
    camera->start();
}

void Camera::setExposureCompensation(int index)
{
    camera->exposure()->setExposureCompensation(index*0.5);
}

void Camera::displayViewfinder()
{
    //widget->setCurrentIndex(0);
}
