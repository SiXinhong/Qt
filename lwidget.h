#ifndef LWIDGET_H
#define LWIDGET_H

#include "rectan.h"

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

class LWidget : public QWidget
{
    Q_OBJECT

private:


public:
//    QPoint position1;
//    QPoint position2;
//    boolean isDrag;
//    Rectan rectan;
    explicit LWidget(QWidget *parent = 0);
//    void contextMenuEvent(QContextMenuEvent *);
//    void mousePressEvent(QMouseEvent *e);
//    void mouseMoveEvent(QMouseEvent *e);
//    void mouseReleaseEvent(QMouseEvent *e);
signals:

public slots:
//    //������ʾ����ʾ�˵������¼�
//    void ToZhu();
//    //��������ʾ����ʾ�˵������¼�
//    void ToNingshi();
//    //������������ʾ�˵������¼�
//    //void ToTanchu();
};

#endif // LWIDGET_H
