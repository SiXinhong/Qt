#ifndef HWIDGET_H
#define HWIDGET_H

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

class HWidget : public QWidget
{
    Q_OBJECT

private:


public:
//    QPoint position1;
//    QPoint position2;
//    boolean isDrag;
//    Rectan rectan;

    explicit HWidget(QWidget *parent = 0);
//    void contextMenuEvent(QContextMenuEvent *);
//    void mousePressEvent(QMouseEvent *e);
//    void mouseMoveEvent(QMouseEvent *e);
//    void mouseReleaseEvent(QMouseEvent *e);

signals:

public slots:
//    //到主显示区显示菜单处理事件
//    void ToZhu();
//    //到凝视显示区显示菜单处理事件
//    void ToNingshi();
//    //到弹出窗口显示菜单处理事件
//    //void ToTanchu();
};

#endif // HWIDGET_H
