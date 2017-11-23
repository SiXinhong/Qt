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
//#include <qmath.h>

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
    double r0;

    double r;
    double r1;

    double x0;

    double y0;
public:

    bool isClicked;

    Mat mat;

    //全景图像
    Mat pano;

    //vector<Rect> rects;//包含的目标的box
    vector<MyObject> objs;

    vector<MyObject> objs3;

    vector<MyObject> objs4;

    vector<MyObject> objs6;

    void setObjects(vector<MyObject> os);

    vector<MyObject> getObjects();

    void setObjects3(vector<MyObject> os3);

    vector<MyObject> getObjects3();

    void setObjects4(vector<MyObject> os4);

    vector<MyObject> getObjects4();

    void setObjects6(vector<MyObject> os6);

    vector<MyObject> getObjects6();

    explicit HWidget(QWidget *parent = 0);

    void setMat(Mat m);

    Mat getMat();

    void setPano(Mat p);

    Mat getPano();

    void draw();

    double getDirectionX(double x, double y);

    double getDirectionY(double x, double y);

    Point getDirectionPoint(Point p);

    Point getPoint1(Point p);

    Point getPoint2(Point p);

    void drawArc3(vector<MyObject> sobjs, Mat tmat);

    void drawArc4(vector<MyObject> sobjs, Mat tmat);

    void drawArc6(vector<MyObject> sobjs, Mat tmat);

    void drawArc3(Mat tmat, Rect r);

    void drawArc4(Mat tmat, Rect r);

    void drawArc6(Mat tmat, Rect r);

    void mouseReleaseEvent(QMouseEvent *);

    double getInverseDirectionX(double x,double y);

    double getInverseDirectionY(double x,double y);

    Point getInverseDirectionPoint(Point p);

    double getMatX(double x);

    double getMatY(double y);

signals:

public slots:


};

#endif // HWIDGET_H
