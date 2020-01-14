#-------------------------------------------------
#
# Project created by QtCreator 2018-11-27T14:58:44
#
#-------------------------------------------------

QT       += core gui
QT       += websockets
QT       += core gui network
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = test
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        mainwindow.cpp \
    service.cpp \
    quanju.cpp \
    colorprogressbar.cpp \
    cloudpanel.cpp \
    roundprogressbar.cpp \
    savepicture.cpp \
    videoplayer.cpp

HEADERS += \
        mainwindow.h \
    service.h \
    quanju.h \
    colorprogressbar.h \
    cloudpanel.h \
    roundprogressbar.h \
    savepicture.h \
    videoplayer.h

FORMS += \
        mainwindow.ui

INCLUDEPATH += D:\opencv\opencv\build\include\opencv2\
INCLUDEPATH += D:\opencv\opencv\build\include\opencv\
INCLUDEPATH += D:\opencv\opencv\build\include

CONFIG(debug, debug|release): {
LIBS += -LD:\opencv\opencv\build\x64\vc14\lib\
-lopencv_core2413d \
-lopencv_imgproc2413d \
-lopencv_highgui2413d \
-lopencv_ml2413d \
-lopencv_video2413d \
-lopencv_features2d2413d \
-lopencv_calib3d2413d \
-lopencv_objdetect2413d \
-lopencv_contrib2413d \
-lopencv_legacy2413d \
-lopencv_flann2413d
} else:CONFIG(release, debug|release): {
LIBS += -LD:\opencv\opencv\build\x64\vc14\lib\
-lopencv_core2413 \
-lopencv_imgproc2413 \
-lopencv_highgui2413 \
-lopencv_ml2413 \
-lopencv_video2413 \
-lopencv_features2d2413 \
-lopencv_calib3d2413 \
-lopencv_objdetect2413 \
-lopencv_contrib2413 \
-lopencv_legacy2413 \
-lopencv_flann2413
}



INCLUDEPATH += $$PWD/ffmpeg/include \
               $$PWD/src \

LIBS += $$PWD/ffmpeg/lib/avcodec.lib \
        $$PWD/ffmpeg/lib/avdevice.lib \
        $$PWD/ffmpeg/lib/avfilter.lib \
        $$PWD/ffmpeg/lib/avformat.lib \
        $$PWD/ffmpeg/lib/avutil.lib \
        $$PWD/ffmpeg/lib/postproc.lib \
        $$PWD/ffmpeg/lib/swresample.lib \
        $$PWD/ffmpeg/lib/swscale.lib \
