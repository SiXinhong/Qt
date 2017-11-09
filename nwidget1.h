#ifndef NWIDGET1_H
#define NWIDGET1_H

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

//OpenCVͷ�ļ�
#include <vector>
#include <highgui.h>
#include <cv.h>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace cv;
using namespace std;

class NWidget1 : public QWidget
{
    Q_OBJECT

private:


public:
    bool isGaojing;
    bool isShow;
  //  bool completeRDefine;
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

    Scalar color;

    vector<MyObject> allobjs;

    vector<MyObject> objs;

    int from;

    //������μ������ı���
    Rect rectRegion;
    //�������μ������ı���
    vector<Point> points;
    //��ʱ�洢���ζ���ļ������
    vector<Region> rs;
    //����ļ�����������ļ��������
    RegionGroup rg;

    //�ж��ǲ��ǵ�һ��������¼������ھ��μ������Ļ���
    boolean isFirstDoubleClick;
    QPoint position11;
    QPoint position22;


    explicit NWidget1(QWidget *parent = 0);

    void alertProcessing(vector<MyObject> os);

    void setFrom(int f);

    int getFrom();

    Rect getRectFromObjs(Rect r);

    //Rect getRectFromObjs2(Rect r);

    void setTwoPanos(Mat tps);

    Mat getTwoPanos();

    void setPano(Mat p);

    Mat getPano();

    void setColor(Scalar c);

    Scalar getColor();

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

    //�Ŵ�
    void ZoomIn();
    //��С
    void ZoomOut();

};

#endif // NWIDGET1_H
