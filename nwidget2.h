#ifndef NWIDGET2_H
#define NWIDGET2_H

#include "rectan.h"
#include "myobject.h"

#include <QWidget>
#include <QMenu>
#include <QCursor>
#include <QDebug>
#include <QPoint>
#include <QMouseEvent>
#include <QLabel>

//OpenCVÍ·ÎÄ¼þ
#include <vector>
#include <highgui.h>
#include <cv.h>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace cv;
using namespace std;

class NWidget2 : public QWidget
{
    Q_OBJECT

private:


public:

    QAction* Yuan_Xuanze;
    QAction* Wu_Bianxing;

    boolean isYuan;

    Rect rect;

    Mat twopanos;

    Mat pano;

    Mat mat;

    vector<MyObject> allobjs;

    vector<MyObject> objs;

    int from;

    explicit NWidget2(QWidget *parent = 0);

    void setFrom(int f);

    int getFrom();

    Rect getRectFromObjs(Rect r);

    //Rect getRectFromObjs2(Rect r);

    void setTwoPanos(Mat tps);

    Mat getTwoPanos();

    void setPano(Mat p);

    Mat getPano();

    void setRect(Rect r);

    Rect getRect();

    double getDirectionX(double x);

    double getDirectionY(double y);

    double getDirectionX2();

    double getDirectionY2();

    void setMat(Mat m);

    Mat getMat();

    void setObjects(vector<MyObject> os);

    vector<MyObject> getObjects();

    void setAllObjects(vector<MyObject> aos);

    vector<MyObject> getAllObjects();

    void draw();

    void contextMenuEvent(QContextMenuEvent *);

    boolean isObjSelected(MyObject obj);

    vector<MyObject> getSelectedObjects();


signals:

public slots:

    void Yuanxuanze();

    void Wubianxing();

};

#endif // NWIDGET2_H

