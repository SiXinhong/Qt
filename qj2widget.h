#ifndef QJ2WIDGET_H
#define QJ2WIDGET_H

#include "rectan.h"
#include "myobject.h"
#include "myobjecttrack.h"
#include "region.h"
#include "regiongroup.h"

#include <QWidget>
#include <QMenu>
#include <QCursor>
#include <QDebug>
#include <QPoint>
#include <QMouseEvent>
#include <QLabel>
#include <QPainter>


//OpenCV头文件
#include <vector>
#include <highgui.h>
#include <cv.h>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace cv;
using namespace std;

class Qj2Widget : public QWidget
{
    Q_OBJECT

private:
QAction* Cancel_Select;
QAction* To_Zhu;
QAction* To_Ningshi1;
QAction* To_Ningshi2;

QAction* Define_Rect;
QAction* Define_Poly;

QAction* Cancel_RDefining;
QAction* Cancel_RGDefining;
QAction* Complete_RDefining;
QAction* Complete_RGDefining;

//QPainter * paint;
QRect qrect;

//QAction* To_Tanchu;

public:
    //bool completeRDefine;
    bool isGaojing;
     bool isShow;
    int x_position1;
    int y_position1;
    int x_position2;
    int y_position2;

    Mat mat;

    Mat pano;

    Mat twoPano;

    //全景1所包含的运动目标
    vector<MyObject> objs;

    //全景1所包含的运动目标轨迹
    vector<MyObjectTrack> tracks;

    QPoint position1;
    QPoint position2;
    boolean isDrag;
    boolean isMove;
    boolean isRect;
    Rect rectan3;
    Rect rectan4;
    Rect rectan6;

    boolean isTo3;
    boolean isTo4;
    boolean isTo6;
    boolean isClicked;


    Rect newrect;
    //QRect qrectan;
    //定义矩形监控区域的变量
    Rect rectRegion;
    //定义多边形监控区域的变量
    vector<Point> points;
    //临时存储本次定义的监控区域
    vector<Region> rs;
    //定义的监控区域所属的监控区域组
    RegionGroup rg;

    //判断是不是第一次鼠标点击事件，用于矩形监控区域的绘制
    boolean isFirstDoubleClick;
    QPoint position11;
    QPoint position22;


    explicit Qj2Widget(QWidget *parent = 0);
    void contextMenuEvent(QContextMenuEvent *);
    void mousePressEvent(QMouseEvent *e);
    void mouseMoveEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);
    //void paintEvent(QPaintEvent *);
    void mouseDoubleClickEvent(QMouseEvent *e);

    void alertProcessing(vector<MyObject> os);

    void setMat(Mat m);
    Mat getMat();

    void setPano(Mat p);
    Mat getPano();

    void setTwoPano(Mat tp);
    Mat getTwoPano();

    void setObjects(vector<MyObject> os);
    vector<MyObject> getObjects();

    void setTracks(vector<MyObjectTrack> ts);
    vector<MyObjectTrack> getTracks();

    Rect getRectan3();
    Rect getQRectan3();

    Rect getRectan4();
    Rect getQRectan4();

    Rect getRectan6();
    Rect getQRectan6();


    double getMatX(double x);

    double getMatY(double y);

    double getWidgetX(double x);

    double getWidgetY(double y);

    double getDirectionX3();

    double getDirectionY3();

    double getDirectionX4();

    double getDirectionY4();

    double getDirectionX6();

    double getDirectionY6();

    double getDirectionX(double x);

    double getDirectionY(double y);

    double getDirectionX32();

    double getDirectionY32();

    double getDirectionX42();

    double getDirectionY42();

    double getDirectionX62();

    double getDirectionY62();

    void draw();

    boolean isObjSelected3(MyObject obj);

    boolean isObjSelected4(MyObject obj);

    boolean isObjSelected6(MyObject obj);

    vector<MyObject> getSelectedObjects3();

    vector<MyObject> getSelectedObjects4();

    vector<MyObject> getSelectedObjects6();

signals:

public slots:
    //取消选择
    void CancelSelect();
    //到主显示区显示菜单处理事件
    void ToZhu();
    //到凝视显示区显示菜单处理事件
    void ToNingshi1();

    void ToNingshi2();
    //到弹出窗口显示菜单处理事件
    //void ToTanchu();
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

};

#endif // QJ2WIDGET_H
