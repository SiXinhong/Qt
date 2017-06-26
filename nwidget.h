#ifndef NWIDGET_H
#define NWIDGET_H

#include "rectan.h"
#include "myobject.h"

#include <QWidget>
#include <QMenu>
#include <QCursor>
#include <QDebug>
#include <QPoint>
#include <QMouseEvent>
#include <QLabel>

//OpenCVͷ�ļ�
#include <vector>
#include <highgui.h>
#include <cv.h>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace cv;
using namespace std;

class NWidget : public QWidget
{
    Q_OBJECT

private:


public:

    Mat mat;
    //vector<Rect> rects;//������Ŀ���box
    vector<MyObject> objs;

    void setObjects(vector<MyObject> os);

    vector<MyObject> getObjects();


    explicit NWidget(QWidget *parent = 0);

    int from;

    void setFrom(int f);

    int getFrom();

    Rect getRectFromObjs(Rect r);

    void setMat(Mat m);

    Mat getMat();

    void draw();

signals:

public slots:


};

#endif // NWIDGET_H
