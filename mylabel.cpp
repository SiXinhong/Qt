#include "mylabel.h"
#include <QPainter>
MyLabel::MyLabel(QWidget *parent) :
    QLabel(parent)
{
}

void MyLabel::paintEvent(QPaintEvent *){
//        QLabel::paintEvent(event);//先调用父类的paintEvent为了显示'背景'!!!
//        QPainter *paint = new QPainter(this);
//        paint->begin(this);
//        paint->setPen(QPen(Qt::red,4,Qt::DashLine));
//        paint->drawRect(20,20,50,30);
//        paint->end();
}
