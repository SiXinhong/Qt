#include "s_trackbar.h"
#include <QWidget>
#include <QPainter>
#include <QMouseEvent>
STrackBar::STrackBar(MainWindow* mainWindow):QWidget()
{
    this->mainWindow=mainWindow;
    this->setFixedHeight(40);
    this->setFixedWidth(280);
    this->position=100;//���ߵ�λ�ã���ʶ���ȵ���ֵ
    this->mousedown=false;//Ϊ��ʵ���϶�Ч�������ж��Ƿ��������꣬Ȼ������ƶ�����Ч
}

void STrackBar:: mouseReleaseEvent(QMouseEvent *event){
    this->mousedown=false;//�����º�����ƶ����پ����϶�Ч��
    int pos=event->x();
    if(pos<5)
        position=0;
    else if(pos>205)
        position=200;
    else
        position=pos-5;//��5����Ϊ��ʾ��ʱ��Ϊ�˺ÿ���ߴ�5��λ�ÿ�ʼ��ʾ���������Ͷ�0
    update();//�����ػ����������paintEvent�¼�
    mainWindow->alpha_contrast=position;
    mainWindow->adjustment();

}
void STrackBar::paintEvent(QPaintEvent *){
    QPainter p(this);
    p.setPen(Qt::lightGray);
    p.drawLine(QPoint(5,20),QPoint(200,20));//�м�ĺ���
    p.setPen(QPen(Qt::lightGray, 5));
    p.drawLine(QPoint(position+5,10),QPoint(position+5,30));//���ߣ���ʶ������ֵ��λ��
    p.drawText(215,25,QString("�Աȶ�")+QString::number(position));
}
void STrackBar:: mousePressEvent(QMouseEvent *){
    this->mousedown=true;//��갴�£�֮������ƶ����������϶�Ч��
}
void STrackBar::mouseMoveEvent(QMouseEvent *event){//����ƶ��¼����Ƿ����϶���Ҫ�ж��Ƿ���갴����
    if(mousedown==false)
        return;
    //����ĸ�����ͷŲ�����һ����
    int pos=event->x();
    if(pos<5)
        position=0;
    else if(pos>205)
        position=200;
    else
        position=pos-5;
    update();
}
void STrackBar::setPosition(int position){
    this->position = position;
}
