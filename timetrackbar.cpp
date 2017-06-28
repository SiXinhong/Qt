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
    this->setWindowTitle("时间线");
    this->setMinimumSize(500,50);
    this->setMaximumSize(500,50);
    this->mousedown=false;//为了实现拖动效果，先判断是否点下了鼠标，然后鼠标移动才有效
    start=dateTimeStart.toTime_t();//转成时间戳
    stop=dateTimeStop.toTime_t();//转成时间戳
    cha=stop-start;
    startTimes = QDateTime::fromTime_t(start).toString("yyyy-MM-dd hh:mm:ss");
    stopTimes = QDateTime::fromTime_t(stop).toString("yyyy-MM-dd hh:mm:ss");
    qDebug()<<start;
    qDebug()<<stop;
    this->posi=0;
    this->position=startTimes;//竖线的位置，标识亮度的数值
   // this->setWindowFlags(Qt::WindowStaysOnTopHint);

}

timeTrackBar::~timeTrackBar()
{
    delete ui;
}
void timeTrackBar:: mouseReleaseEvent(QMouseEvent *event){
    this->mousedown=false;//鼠标放下后，鼠标移动不再具有拖动效果
    //pos=event->x()/(300/cha)+start;//滑动后时间戳
    posi=event->x();
    pos=cha*posi/300+start;//滑动后时间戳
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
        position=QDateTime::fromTime_t(pos).toString("yyyy-MM-dd hh:mm:ss");//减5是因为显示的时候为了好看左边从5的位置开始显示，当作亮度0
    update();//触发重绘操作，生成paintEvent事件


}


void timeTrackBar::paintEvent(QPaintEvent *){
    QPainter p(this);
    p.setPen(Qt::lightGray);
    //p.drawLine(QPoint(5,20),QPoint(5+cha,20));//中间的横线
    p.drawLine(QPoint(5,20),QPoint(305,20));//中间的横线
    p.setPen(QPen(Qt::lightGray, 5));
    p.drawLine(QPoint(posi+5,10),QPoint(posi+5,30));//竖线，标识亮度数值的位置
    p.drawText(310,25,QString("时间")+QString(position));
}

void timeTrackBar:: mousePressEvent(QMouseEvent *){
    this->mousedown=true;//鼠标按下，之后鼠标移动操作产生拖动效果
}

void timeTrackBar::mouseMoveEvent(QMouseEvent *event){//鼠标移动事件，是否是拖动需要判断是否鼠标按下了
    if(mousedown==false)
        return;
    //下面的跟鼠标释放操作是一样的
    int pos=cha*posi/300+start;//滑动后时间戳
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
