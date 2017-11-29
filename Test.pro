#-------------------------------------------------
#
# Project created by QtCreator 2017-05-08T20:02:54
#
#-------------------------------------------------

QT       += core gui
#QT +=phonon

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Test
TEMPLATE = app
INCLUDEPATH += D:\opencv-2.4.9-build\install\include
INCLUDEPATH += D:\opencv-2.4.9-build\install\include\opencv

LIBS += -L D:\opencv-2.4.9-build\install\x64\mingw\lib\libopencv_*.a\

SOURCES += main.cpp\
        mainwindow.cpp \
    mylabel.cpp \
    rectan.cpp \
    zwidget.cpp \
    hwidget.cpp \
    lwidget.cpp \
    qj1widget.cpp \
    qj2widget.cpp \
    cvutil.cpp \
    trackbar.cpp \
    myobject.cpp \
    myinterface.cpp \
    myobjecttrack.cpp \
    show_sdk.cpp \
#    backwindow.cpp \
    backwindow.cpp \
    s_trakbar.cpp \
    objectattributes.cpp \
    mixer.cpp \
    timeline.cpp \
    socket.cpp \
    welcomewindow.cpp \
    nwidget1.cpp \
    nwidget2.cpp \
    region.cpp \
    regiongroup.cpp \
    monitor.cpp \
    detailsofrg.cpp \
    alert.cpp \
    timecontrol.cpp

HEADERS  += mainwindow.h \
    mylabel.h \
    rectan.h \
    zwidget.h \
    hwidget.h \
    lwidget.h \
    qj1widget.h \
    qj2widget.h \
    cvutil.h \
    trackbar.h \
    myobject.h \
    myinterface.h \
    myobjecttrack.h \
    show_sdk.h\
#    backwindow.h \
    backwindow.h \
    s_trackbar.h \
    s_trackbar.h \
    objectAttributes.h \
    objectAttributes.h \
    mixer.h \
    timeline.h \
    socket.h \
    welcomewindow.h \
    nwidget1.h \
    nwidget2.h \
    region.h \
    regiongroup.h \
    monitor.h \
    detailsofrg.h \
    alert.h \
    timecontrol.h

FORMS    += mainwindow.ui\
#    backwindow.ui \
    timetrackbar.ui \
    backwindow.ui

#INCLUDEPATH+=.\OpenCV\include\opencv\

#             INCLUDEPATH+=.\OpenCV\include\opencv2\

#             INCLUDEPATH+=.\OpenCV\include

#LIBS+=.\OpenCV\lib\libopencv_calib3d231.dll.a\

#        LIBS+=.\OpenCV\lib\libopencv_contrib231.dll.a\

#        LIBS+=.\OpenCV\lib\libopencv_core231.dll.a\

#        LIBS+=.\OpenCV\lib\libopencv_features2d231.dll.a\

#        LIBS+=.\OpenCV\lib\libopencv_flann231.dll.a\

#        LIBS+=.\OpenCV\lib\libopencv_gpu231.dll.a\

#        LIBS+=.\OpenCV\lib\libopencv_highgui231.dll.a\

#        LIBS+=.\OpenCV\lib\libopencv_imgproc231.dll.a\

#        LIBS+=.\OpenCV\lib\libopencv_legacy231.dll.a\

#        LIBS+=.\OpenCV\lib\libopencv_ml231.dll.a\

#        LIBS+=.\OpenCV\lib\libopencv_objdetect231.dll.a\

#        LIBS+=.\OpenCV\lib\libopencv_ts231.a\

#LIBS += .\lib\WinMM.Lib
#LIBS += .\lib\User32.Lib


#///////////////////////////////////////////////////////zc

LIBS += -lwsock32 libws2_32
