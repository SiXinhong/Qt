#include "mylabel.h"
#include <QPainter>
MyLabel::MyLabel(QWidget *parent) :
    QLabel(parent)
{
}

void MyLabel::paintEvent(QPaintEvent *){
//        QLabel::paintEvent(event);//�ȵ��ø����paintEventΪ����ʾ'����'!!!
//        QPainter *paint = new QPainter(this);
//        paint->begin(this);
//        paint->setPen(QPen(Qt::red,4,Qt::DashLine));
//        paint->drawRect(20,20,50,30);
//        paint->end();
}
