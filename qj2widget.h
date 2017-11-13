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
    Rect rectan6;

    boolean isTo3;
    boolean isTo4;
    boolean isTo6;
    boolean isClicked;


    Rect newrect;
    //QRect qrectan;
    //������μ������ı���
    Rect rectRegion;
    //�������μ������ı���
    vector<Point> points;
    //��ʱ�洢���ζ���ļ������
    vector<Region> rs;

    //�ж��ǲ��ǵ�һ��������¼������ھ��μ������Ļ���
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
    //ȡ��ѡ��
    void CancelSelect();
    //������ʾ����ʾ�˵������¼�
    void ToZhu();
    //��������ʾ����ʾ�˵������¼�
    void ToNingshi1();

    void ToNingshi2();
    //������������ʾ�˵������¼�
    //void ToTanchu();
    //������μ������
    void DefineRect();
    //�������μ������
    void DefinePoly();

    //ȡ�����������
    void CancelRDefining();

    //ȡ����������鶨��
    void CancelRGDefining();
    //��ɼ��������
    void CompleteRDefining();
    //��ɼ�������鶨��
    void CompleteRGDefining();

};

#endif // QJ2WIDGET_H
