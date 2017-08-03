#include "timeline.h"
#include <QWidget>
#include <QPainter>
#include <QMouseEvent>
TimeLine::TimeLine(BackWindow* backWindow):QWidget()
{
    this->backWindow=backWindow;
    this->setMinimumSize(400,40);
    this->setMaximumSize(400,40);
    this->position=0;//竖线的位置，标识亮度的数值
    this->mousedown=false;//为了实现拖动效果，先判断是否点下了鼠标，然后鼠标移动才有效
}


void TimeLine::setTime(QTime start, QTime stop){
    this->start=start;
    this->stop=stop;
    int millseconds=start.msecsTo(stop);//两者相差的毫秒数
    every=millseconds/255;
}

void TimeLine:: mouseReleaseEvent(QMouseEvent *event){
    this->mousedown=false;//鼠标放下后，鼠标移动不再具有拖动效果
    int pos=event->x();
    if(pos<5)
        position=0;
    else if(pos>260)
        position=255;
    else
        position=pos-5;//减5是因为显示的时候为了好看左边从5的位置开始显示，当作亮度0
    update();//触发重绘操作，生成paintEvent事件
//    backWindow->bright_TimeLineValue=position;
//    backWindow->adjustment();
    backWindow->fileIndex=position*backWindow->fileInfo->count()/255;
    backWindow->panoIndex=position*backWindow->fileInfo->count()/255;

}



void TimeLine::paintEvent(QPaintEvent *){
    QPainter p(this);
    p.setPen(Qt::lightGray);
    p.drawLine(QPoint(5,20),QPoint(260,20));//中间的横线
    p.setPen(QPen(Qt::lightGray, 5));
    p.drawLine(QPoint(position+5,10),QPoint(position+5,30));//竖线，标识亮度数值的位置
    QTime nowTime=start.addMSecs(position*every);
    p.drawText(265,25,QString("时间:")+nowTime.toString("HH:mm:ss"));
}

void TimeLine:: mousePressEvent(QMouseEvent *){
    this->mousedown=true;//鼠标按下，之后鼠标移动操作产生拖动效果
}

void TimeLine::mouseMoveEvent(QMouseEvent *event){//鼠标移动事件，是否是拖动需要判断是否鼠标按下了
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

void TimeLine::setPosition(int position){
    this->position = position;
}
