#include "sensitivity.h"

Sensitivity::Sensitivity(MainWindow *mw) :
    QWidget(mw)
{
    this->mw = mw;
    this->mousedown = false;
    this->setMinimumSize(40,130);
    this->setMaximumSize(40,130);
    this->position=50;
}


void Sensitivity::mouseReleaseEvent(QMouseEvent *event){
    this->mousedown = false;
    int pos = event->y();
    if(pos<5)
        this->position = 0;
    else if(pos>105)
        this->position = 100;
    else
        position = pos-5;
    update();

}

void Sensitivity::paintEvent(QPaintEvent *){
    QPainter p(this);
    p.setBackground(QBrush(Qt::lightGray));
    p.setPen(Qt::black);
    p.drawLine(QPoint(20,5),QPoint(20,105));
    p.setPen(QPen(Qt::black,5));
    p.drawLine(QPoint(10,position+5),QPoint(30,position+5));
    p.drawText(15,120,QString::number(position));
}

void Sensitivity::mousePressEvent(QMouseEvent *){
    this->mousedown = true;
}


void Sensitivity::mouseMoveEvent(QMouseEvent *event){
    if(!mousedown)
        return;
    int pos = event->y();
    if(pos<5)
        this->position = 0;
    else if(pos>105)
        this->position = 100;
    else
        position = pos-5;
    update();
}
