#ifndef NWIDGET_H
#define NWIDGET_H

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

class NWidget : public QWidget
{
    Q_OBJECT

private:


public:

    Mat mat;
    vector<Rect> rects;//包含的目标的box

    explicit NWidget(QWidget *parent = 0);

    void setMat(Mat m);

    Mat getMat();

    void draw();

signals:

public slots:


};

#endif // NWIDGET_H
