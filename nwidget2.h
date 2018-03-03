﻿#ifndef NWIDGET2_H
#define NWIDGET2_H

#include "rectan.h"
#include "myobject.h"
#include "region.h"
#include "regiongroup.h"

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

class NWidget2 : public QWidget
{
    Q_OBJECT

private:

    //把监控区的坐标转换成在全景视图的坐标
    int convertToOriginX(int x);
    int convertToOriginY(int y);
    int convertToOriginWidth(int width);
    int convertToOriginHeight(int height);
    void adjustRect(int x,int y);
public:
  //  bool completeRDefine;
     bool isShow;

     bool isGaojing;

    QAction* Yuan_Xuanze;
    QAction* Wu_Bianxing;

    QAction* Define_Rect;
    QAction* Define_Poly;

    QAction* Cancel_RDefining;
    QAction* Cancel_RGDefining;
    QAction* Complete_RDefining;
    QAction* Complete_RGDefining;

    QAction* Zoom_In;
    QAction* Zoom_Out;

    boolean isYuan;
    boolean isClicked;

    Rect rect;

    Rect realRect;

    Mat twopanos;

    Mat pano;

    Mat mat;

    static Scalar color;

    vector<MyObject> allobjs;

    vector<MyObject> objs;

    int from;

    //定义矩形监控区域的变量
    Rect rectRegion;
    //定义多边形监控区域的变量
    vector<Point> points;
    //临时存储本次定义的监控区域
    vector<Region> rs;

    //判断是不是第一次鼠标点击事件，用于矩形监控区域的绘制
    boolean isFirstDoubleClick;
    QPoint position11;
    QPoint position22;

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

    double getMatX(double x);

    double getMatY(double y);

    double getWidgetX(double x);

    double getWidgetY(double y);


    double getDirectionX(double x);

    double getDirectionY(double y);

    double getDirectionX2();

    double getDirectionY2();

    void setMat(Mat m);

    Mat getMat();

    static void setColor(Scalar c);

    Scalar getColor();

    void setObjects(vector<MyObject> os);

    vector<MyObject> getObjects();

    void setAllObjects(vector<MyObject> aos);

    vector<MyObject> getAllObjects();

    void draw();

    void contextMenuEvent(QContextMenuEvent *);
    void mouseDoubleClickEvent(QMouseEvent *e);

    void mousePressEvent(QMouseEvent *e);
    void mouseMoveEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);

    boolean isObjSelected(MyObject obj);

    vector<MyObject> getSelectedObjects();


signals:

public slots:

    void Yuanxuanze();

    void Wubianxing();

    //定义矩形监控区域
    void DefineRect();
    //定义多边形监控区域
    void DefinePoly();

    //取消监控区域定义
    void CancelRDefining();

    //取消监控区域组定义
    void CancelRGDefining();
    //完成监控区域定义
    void CompleteRDefining();
    //完成监控区域组定义
    void CompleteRGDefining();

    //放大
    void ZoomIn();
    //缩小
    void ZoomOut();
    //还原
    void ZoomInitial();
};

#endif // NWIDGET2_H

