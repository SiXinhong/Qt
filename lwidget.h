#ifndef LWIDGET_H
#define LWIDGET_H

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

class LWidget : public QWidget
{
    Q_OBJECT

private:
    double r0;

    double r;

    double x0;

    double y0;
public:

    Mat mat;

    //ȫ��ͼ��
    Mat pano;

    //vector<Rect> rects;//������Ŀ���box
    vector<MyObject> objs;

    void setObjects(vector<MyObject> os);

    vector<MyObject> getObjects();


    explicit LWidget(QWidget *parent = 0);

    void setMat(Mat m);

    Mat getMat();

    void setPano(Mat p);

    Mat getPano();

    void draw();

    double getDirectionX(double x, double y);

    double getDirectionY(double x, double y);

    Point getDirectionPoint(Point p);

    Point getPoint(Point p);

    vector<Point> getPoints(vector<MyObject> objs);

signals:

public slots:


};

#endif // LWIDGET_H
