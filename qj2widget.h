#ifndef QJ2WIDGET_H
#define QJ2WIDGET_H

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

class Qj2Widget : public QWidget
{
    Q_OBJECT

private:
QAction* Cancel_Select;
QAction* To_Zhu;
QAction* To_Ningshi;
//QAction* To_Tanchu;

public:

    Mat mat;

    //ȫ��1���������˶�Ŀ��
    vector<MyObject> objs;

    QPoint position1;
    QPoint position2;
    boolean isDrag;
    boolean isMove;
    boolean isRect;
    Rect rectan;
    //QRect qrectan;


    explicit Qj2Widget(QWidget *parent = 0);
    void contextMenuEvent(QContextMenuEvent *);
    void mousePressEvent(QMouseEvent *e);
    void mouseMoveEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);

    void setMat(Mat m);
    Mat getMat();

    void setObjects(vector<MyObject> os);
    vector<MyObject> getObjects();

    Rect getRectan();
    QRect getQRectan();

    double getMatX(double x);

    double getMatY(double y);

    double getWidgetX(double x);

    double getWidgetY(double y);

    double getDirectionX();

    double getDirectionY();

    void draw();

    boolean isObjSelected(MyObject obj);

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
