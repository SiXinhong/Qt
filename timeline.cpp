#include "timeline.h"
#include <QWidget>
#include <QPainter>
#include <QMouseEvent>
TimeLine::TimeLine(BackWindow* backWindow):QWidget()
{
    this->backWindow=backWindow;
    this->setMinimumSize(350,40);
    this->setMaximumSize(350,40);
    this->position=0;//���ߵ�λ�ã���ʶ���ȵ���ֵ
    this->mousedown=false;//Ϊ��ʵ���϶�Ч�������ж��Ƿ��������꣬Ȼ������ƶ�����Ч
}


void TimeLine::setTime(QTime start, QTime stop){
    this->start=start;
    this->stop=stop;
    int millseconds=start.msecsTo(stop);//�������ĺ�����
    every=millseconds/255;
}

void TimeLine:: mouseReleaseEvent(QMouseEvent *event){
    this->mousedown=false;//�����º�����ƶ����پ����϶�Ч��
    int pos=event->x();
    if(pos<5)
        position=0;
    else if(pos>260)
        position=255;
    else
        position=pos-5;//��5����Ϊ��ʾ��ʱ��Ϊ�˺ÿ���ߴ�5��λ�ÿ�ʼ��ʾ����������0
    update();//�����ػ����������paintEvent�¼�
//    backWindow->bright_TimeLineValue=position;
//    backWindow->adjustment();
    backWindow->fileIndex=position*backWindow->fileInfo->count()/255;
}


void TimeLine::paintEvent(QPaintEvent *){
    QPainter p(this);
    p.setPen(Qt::lightGray);
    p.drawLine(QPoint(5,20),QPoint(260,20));//�м�ĺ���
    p.setPen(QPen(Qt::lightGray, 5));
    p.drawLine(QPoint(position+5,10),QPoint(position+5,30));//���ߣ���ʶ������ֵ��λ��
    QTime nowTime=start.addMSecs(position*every);
    p.drawText(265,25,QString("ʱ��:")+nowTime.toString("HH:mm:ss"));
}

void TimeLine:: mousePressEvent(QMouseEvent *){
    this->mousedown=true;//��갴�£�֮������ƶ����������϶�Ч��
}

void TimeLine::mouseMoveEvent(QMouseEvent *event){//����ƶ��¼����Ƿ����϶���Ҫ�ж��Ƿ���갴����
    if(mousedown==false)
        return;
    //����ĸ�����ͷŲ�����һ����
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
