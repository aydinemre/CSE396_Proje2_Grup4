#-------------------------------------------------
#
# Project created by QtCreator 2017-04-19T14:42:06
#
#-------------------------------------------------

QT       +=  multimedia multimediawidgets

TARGET = FindJoeProject
TEMPLATE = app

INCLUDEPATH += /usr/local/include/opencv

LIBS += -L/usr/local/lib -lopencv_shape -lopencv_stitching -lopencv_objdetect \
    -lopencv_superres -lopencv_videostab -lopencv_calib3d \
    -lopencv_features2d -lopencv_highgui -lopencv_videoio -lopencv_imgcodecs \
    -lopencv_video \
    -lopencv_photo -lopencv_ml -lopencv_imgproc -lopencv_flann -lopencv_core

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += main.cpp\
        mainwindow.cpp \
    coor.cpp \
    settings.cpp \
    Communication.cpp \
    SerialPort.cpp \
    workerthread.cpp \
    algorithm.cpp

HEADERS  += mainwindow.h \
    coor.h \
    settings.h \
    Communication.h \
    SerialPort.h \
    workerthread.h \
    algorithm.h

FORMS    += mainwindow.ui

INSTALLS += target

QT       +=  widgets
