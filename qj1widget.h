#ifndef QJWIDGET_H
#define QJWIDGET_H

#include "rectan.h"

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

class Qj1Widget : public QWidget
{
    Q_OBJECT

private:
QAction* To_Zhu;
QAction* To_Ningshi;
QAction* To_Tanchu;

public:

    Mat mat;

    QPoint position1;
    QPoint position2;
    boolean isDrag;
    Rect rectan;


    explicit Qj1Widget(QWidget *parent = 0);
    void contextMenuEvent(QContextMenuEvent *);
    void mousePressEvent(QMouseEvent *e);
    void mouseMoveEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);

    void setMat(Mat m);
    Mat getMat();

signals:

public slots:
    //到主显示区显示菜单处理事件
    void ToZhu();
    //到凝视显示区显示菜单处理事件
    void ToNingshi();
    //到弹出窗口显示菜单处理事件
    //void ToTanchu();
};

#endif // QJWIDGET_H
