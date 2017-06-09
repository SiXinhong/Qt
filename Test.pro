#-------------------------------------------------
#
# Project created by QtCreator 2017-05-08T20:02:54
#
#-------------------------------------------------

QT       += core gui
QT +=phonon

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Test
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    mylabel.cpp \
    rectan.cpp

HEADERS  += mainwindow.h \
    mylabel.h \
    rectan.h

FORMS    += mainwindow.ui

INCLUDEPATH+=E:\QTsource\OpenCV\include\opencv\

             INCLUDEPATH+=E:\QTsource\OpenCV\include\opencv2\

             INCLUDEPATH+=E:\QTsource\OpenCV\include

LIBS+=E:\QTsource\OpenCV\lib\libopencv_calib3d231.dll.a\

        LIBS+=E:\QTsource\OpenCV\lib\libopencv_contrib231.dll.a\

        LIBS+=E:\QTsource\OpenCV\lib\libopencv_core231.dll.a\

        LIBS+=E:\QTsource\OpenCV\lib\libopencv_features2d231.dll.a\

        LIBS+=E:\QTsource\OpenCV\lib\libopencv_flann231.dll.a\

        LIBS+=E:\QTsource\OpenCV\lib\libopencv_gpu231.dll.a\

        LIBS+=E:\QTsource\OpenCV\lib\libopencv_highgui231.dll.a\

        LIBS+=E:\QTsource\OpenCV\lib\libopencv_imgproc231.dll.a\

        LIBS+=E:\QTsource\OpenCV\lib\libopencv_legacy231.dll.a\

        LIBS+=E:\QTsource\OpenCV\lib\libopencv_ml231.dll.a\

        LIBS+=E:\QTsource\OpenCV\lib\libopencv_objdetect231.dll.a\

        LIBS+=E:\QTsource\OpenCV\lib\libopencv_ts231.a\


