#include "trackbar.h"
#include <QWidget>
#include <QPainter>
#include <QMouseEvent>

double deta=0;
TrackBar::TrackBar(Configuration *configuration):QWidget(configuration)
{
    this->configuration=configuration;
    this->setMinimumSize(280,40);
    this->setMaximumSize(280,40);
    //this->position=100;//竖线的位置，标识亮度的数值
    this->position = Configuration::bright;
    //this->position = configuration->bright;
    this->mousedown=false;//为了实现拖动效果，先判断是否点下了鼠标，然后鼠标移动才有效
}

void TrackBar:: mouseReleaseEvent(QMouseEvent *event){
    this->mousedown=false;//鼠标放下后，鼠标移动不再具有拖动效果
    int pos=event->x();
    if(pos<5)
        position=0;
    else if(pos>205)
        position=200;
    else
        position=pos-5;//减5是因为显示的时候为了好看左边从5的位置开始显示，当作亮度0
    update();//触发重绘操作，生成paintEvent事件
    deta = position*5-500;
    configuration->adjustment();
    //configuration->bright=position;
    Configuration::bright = position;
//    mainWindow->bright_TrackbarValue=position;
//    mainWindow->adjustment();
}


void TrackBar::paintEvent(QPaintEvent *){
    QPainter p(this);
    p.setPen(Qt::lightGray);
    p.drawLine(QPoint(5,20),QPoint(200,20));//中间的横线
    p.setPen(QPen(Qt::lightGray, 5));
    p.drawLine(QPoint(position+5,10),QPoint(position+5,30));//竖线，标识亮度数值的位置
    p.drawText(215,25,QString::number(position*5-500));
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
    else if(pos>205)
        position=200;
    else
        position=pos-5;
    update();
}

void TrackBar::setPosition(int position){
    this->position = position;
}
