#ifndef HWIDGET_H
#define HWIDGET_H

#include "rectan.h"
#include "myobject.h"

#include <QWidget>
#include <QMenu>
#include <QCursor>
#include <QDebug>
#include <QPoint>
#include <QMouseEvent>
#include <QLabel>

//OpenCV头文件
#include <vector>
#include <highgui.h>
#include <cv.h>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace cv;
using namespace std;

class HWidget : public QWidget
{
    Q_OBJECT

private:


public:

    Mat mat;
    //vector<Rect> rects;//包含的目标的box
    vector<MyObject> objs;

    void setObjects(vector<MyObject> os);

    vector<MyObject> getObjects();


    explicit HWidget(QWidget *parent = 0);

    void setMat(Mat m);

    Mat getMat();

    void draw();

    double getDirectionX(double x);

    double getDirectionY(double y);

    Point getDirectionPoint(Point p);

    vector<Point> getPoints(vector<MyObject> objs);

signals:

public slots:


};

#endif // HWIDGET_H
