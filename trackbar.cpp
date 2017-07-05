#include "trackbar.h"
#include <QWidget>
#include <QPainter>
#include <QMouseEvent>
TrackBar::TrackBar(MainWindow* mainWindow):QWidget()
{
    this->mainWindow=mainWindow;
    this->setMinimumSize(319,40);
    this->setMaximumSize(319,40);
    this->position=0;//���ߵ�λ�ã���ʶ���ȵ���ֵ
    this->mousedown=false;//Ϊ��ʵ���϶�Ч�������ж��Ƿ��������꣬Ȼ������ƶ�����Ч
}

void TrackBar:: mouseReleaseEvent(QMouseEvent *event){
    this->mousedown=false;//�����º�����ƶ����پ����϶�Ч��
    int pos=event->x();
    if(pos<5)
        position=0;
    else if(pos>260)
        position=255;
    else
        position=pos-5;//��5����Ϊ��ʾ��ʱ��Ϊ�˺ÿ���ߴ�5��λ�ÿ�ʼ��ʾ����������0
    update();//�����ػ����������paintEvent�¼�
    mainWindow->bright_TrackbarValue=position;
    mainWindow->adjustment();
}


void TrackBar::paintEvent(QPaintEvent *){
    QPainter p(this);
    p.setPen(Qt::lightGray);
    p.drawLine(QPoint(5,20),QPoint(260,20));//�м�ĺ���
    p.setPen(QPen(Qt::lightGray, 5));
    p.drawLine(QPoint(position+5,10),QPoint(position+5,30));//���ߣ���ʶ������ֵ��λ��
    p.drawText(265,25,QString("����")+QString::number(position));
}

void TrackBar:: mousePressEvent(QMouseEvent *){
    this->mousedown=true;//��갴�£�֮������ƶ����������϶�Ч��
}

void TrackBar::mouseMoveEvent(QMouseEvent *event){//����ƶ��¼����Ƿ����϶���Ҫ�ж��Ƿ���갴����
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

void TrackBar::setPosition(int position){
    this->position = position;
}
