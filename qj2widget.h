#ifndef QJ2WIDGET_H
#define QJ2WIDGET_H

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

class Qj2Widget : public QWidget
{
    Q_OBJECT

private:
//Ui::Widget *ui;
QAction* To_Zhu;
QAction* To_Ningshi;
QAction* To_Tanchu;

public:
    QPoint position1;
    QPoint position2;
    boolean isDrag;
    Rectan rectan;

    explicit Qj2Widget(QWidget *parent = 0);
    void contextMenuEvent(QContextMenuEvent *);
    void mousePressEvent(QMouseEvent *e);
    void mouseMoveEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);

signals:

public slots:
    //������ʾ����ʾ�˵������¼�
    void ToZhu();
    //��������ʾ����ʾ�˵������¼�
    void ToNingshi();
    //������������ʾ�˵������¼�
    //void ToTanchu();
};


#endif // QJ2WIDGET_H
