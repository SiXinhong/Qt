//#include "timetrackbar.h"
//#include "ui_timetrackbar.h"

//timeTrackBar::timeTrackBar(QWidget *parent) :
//    QMainWindow(parent),
//    ui(new Ui::timeTrackBar)
//{
//    ui->setupUi(this);
//}

//timeTrackBar::~timeTrackBar()
//{
//    delete ui;
//}
#include "timetrackbar.h"
#include "ui_timetrackbar.h"
#include<QDebug>

extern QDateTime dateTimeStart;
extern QDateTime dateTimeStop;
timeTrackBar::timeTrackBar(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::timeTrackBar)
{
    ui->setupUi(this);
    this->setWindowTitle("ʱ����");
    this->setMinimumSize(500,50);
    this->setMaximumSize(500,50);
    this->mousedown=false;//Ϊ��ʵ���϶�Ч�������ж��Ƿ��������꣬Ȼ������ƶ�����Ч
    start=dateTimeStart.toTime_t();//ת��ʱ���
    stop=dateTimeStop.toTime_t();//ת��ʱ���
    cha=stop-start;
    startTimes = QDateTime::fromTime_t(start).toString("yyyy-MM-dd hh:mm:ss");
    stopTimes = QDateTime::fromTime_t(stop).toString("yyyy-MM-dd hh:mm:ss");
    qDebug()<<start;
    qDebug()<<stop;
    this->posi=0;
    this->position=startTimes;//���ߵ�λ�ã���ʶ���ȵ���ֵ
   // this->setWindowFlags(Qt::WindowStaysOnTopHint);

}

timeTrackBar::~timeTrackBar()
{
    delete ui;
}
void timeTrackBar:: mouseReleaseEvent(QMouseEvent *event){
    this->mousedown=false;//�����º�����ƶ����پ����϶�Ч��
    //pos=event->x()/(300/cha)+start;//������ʱ���
    posi=event->x();
    pos=cha*posi/300+start;//������ʱ���
    if(posi<0)
    {
        position=startTimes;
        posi=0;
    }
    else if(posi>305)
    {
        position=stopTimes;
        posi=300;
    }
    else
        position=QDateTime::fromTime_t(pos).toString("yyyy-MM-dd hh:mm:ss");//��5����Ϊ��ʾ��ʱ��Ϊ�˺ÿ���ߴ�5��λ�ÿ�ʼ��ʾ����������0
    update();//�����ػ����������paintEvent�¼�


}


void timeTrackBar::paintEvent(QPaintEvent *){
    QPainter p(this);
    p.setPen(Qt::lightGray);
    //p.drawLine(QPoint(5,20),QPoint(5+cha,20));//�м�ĺ���
    p.drawLine(QPoint(5,20),QPoint(305,20));//�м�ĺ���
    p.setPen(QPen(Qt::lightGray, 5));
    p.drawLine(QPoint(posi+5,10),QPoint(posi+5,30));//���ߣ���ʶ������ֵ��λ��
    p.drawText(310,25,QString("ʱ��")+QString(position));
}

void timeTrackBar:: mousePressEvent(QMouseEvent *){
    this->mousedown=true;//��갴�£�֮������ƶ����������϶�Ч��
}

void timeTrackBar::mouseMoveEvent(QMouseEvent *event){//����ƶ��¼����Ƿ����϶���Ҫ�ж��Ƿ���갴����
    if(mousedown==false)
        return;
    //����ĸ�����ͷŲ�����һ����
    int pos=cha*posi/300+start;//������ʱ���
    posi=event->x();
    if(posi<0)
    {
        position=startTimes;
        posi=0;
    }
    else if(posi>305)
    {
        position=stopTimes;
        posi=300;
    }
    else
        position=QDateTime::fromTime_t(pos).toString("yyyy-MM-dd hh:mm:ss");
    update();
}
