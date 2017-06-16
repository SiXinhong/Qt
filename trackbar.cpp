#include "trackbar.h"
#include <QWidget>
#include <QPainter>
#include <QMouseEvent>
TrackBar::TrackBar(MainWindow* mainWindow):QWidget()
{
    this->mainWindow=mainWindow;
    this->setFixedHeight(40);
    this->setFixedWidth(319);
    this->position=0;//竖线的位置，标识亮度的数值
    this->mousedown=false;//为了实现拖动效果，先判断是否点下了鼠标，然后鼠标移动才有效
}

void TrackBar:: mouseReleaseEvent(QMouseEvent *event){
    this->mousedown=false;//鼠标放下后，鼠标移动不再具有拖动效果
    int pos=event->x();
    if(pos<5)
        position=0;
    else if(pos>260)
        position=255;
    else
        position=pos-5;//减5是因为显示的时候为了好看左边从5的位置开始显示，当作亮度0
    update();//触发重绘操作，生成paintEvent事件
    mainWindow->bright_TrackbarValue=position;
    mainWindow->onTimerOut();

}


void TrackBar::paintEvent(QPaintEvent *){
    QPainter p(this);
    p.setPen(Qt::lightGray);
    p.drawLine(QPoint(5,20),QPoint(260,20));//中间的横线
    p.setPen(QPen(Qt::lightGray, 5));
    p.drawLine(QPoint(position+5,10),QPoint(position+5,30));//竖线，标识亮度数值的位置
    p.drawText(265,25,QString("亮度")+QString::number(position));
}

void TrackBar:: mousePressEvent(QMouseEvent *){
    this->mousedown=true;//鼠标按下，之后鼠标移动操作产生拖动效果
}

void TrackBar::mouseMoveEvent(QMouseEvent *event){//鼠标移动事件，是否是拖动需要判断是否鼠标按下了
    if(mousedown==false)
        return;
    //下面的跟鼠标释放操作是一样的
    int pos=event->x();
    if(pos<5)
        position=0;
    else if(pos>260)
        position=255;
    else
        position=pos-5;
    update();
}
