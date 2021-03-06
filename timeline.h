﻿#ifndef TIMELINE_H
#define TIMELINE_H
#include "backwindow.h"
class TimeLine:public QWidget
{
public:
    TimeLine(class BackWindow*);
    void setTime(QTime start,QTime stop);
    void setPosition(int position);
    void mouseReleaseEvent(QMouseEvent *);
    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *);
    void keyPressEvent(QKeyEvent *);
    int position;


private:
    class BackWindow* backWindow;

    bool mousedown;
    QTime start;
    QTime stop;
    int every;
};
#endif
