#ifndef QJ2WIDGET_H
#define QJ2WIDGET_H

#include "rectan.h"
#include "myobject.h"
#include "myobjecttrack.h"

#include <QWidget>
#include <QMenu>
#include <QCursor>
#include <QDebug>
#include <QPoint>
#include <QMouseEvent>
#include <QLabel>
#include <QPainter>


//OpenCVͷ�ļ�
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
QAction* To_Ningshi;
//QPainter * paint;
QRect qrect;

//QAction* To_Tanchu;

public:

    Mat mat;

    Mat pano;

    //ȫ��1���������˶�Ŀ��
    vector<MyObject> objs;

    //ȫ��1���������˶�Ŀ��켣
    vector<MyObjectTrack> tracks;

    QPoint position1;
    QPoint position2;
    boolean isDrag;
    boolean isMove;
    boolean isRect;
    Rect rectan3;
    Rect rectan4;

    boolean isTo3;
    boolean isTo4;

    Rect newrect;
    //QRect qrectan;


    explicit Qj2Widget(QWidget *parent = 0);
    void contextMenuEvent(QContextMenuEvent *);
    void mousePressEvent(QMouseEvent *e);
    void mouseMoveEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);
    //void paintEvent(QPaintEvent *);


    void setMat(Mat m);
    Mat getMat();

    void setPano(Mat p);
    Mat getPano();

    void setObjects(vector<MyObject> os);
    vector<MyObject> getObjects();

    void setTracks(vector<MyObjectTrack> ts);
    vector<MyObjectTrack> getTracks();

    Rect getRectan3();
    Rect getQRectan3();

    Rect getRectan4();
    Rect getQRectan4();

    double getMatX(double x);

    double getMatY(double y);

    double getWidgetX(double x);

    double getWidgetY(double y);

    double getDirectionX3();

    double getDirectionY3();

    double getDirectionX4();

    double getDirectionY4();

    double getDirectionX(double x);

    double getDirectionY(double y);

    double getDirectionX32();

    double getDirectionY32();

    double getDirectionX42();

    double getDirectionY42();

    void draw();

    boolean isObjSelected3(MyObject obj);

    boolean isObjSelected4(MyObject obj);

    vector<MyObject> getSelectedObjects3();

    vector<MyObject> getSelectedObjects4();

signals:

public slots:
    //ȡ��ѡ��
    void CancelSelect();
    //������ʾ����ʾ�˵������¼�
    void ToZhu();
    //��������ʾ����ʾ�˵������¼�
    void ToNingshi();
    //������������ʾ�˵������¼�
    //void ToTanchu();
};

#endif // QJ2WIDGET_H
