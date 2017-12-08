#include "hourwidget.h"

HourWidget::HourWidget(Monitor *monitor) :
    QWidget(monitor)
{
    this->monitor = monitor;
//    xStart = this->x()+60;
//    yStart = this->y()+30;
//    w = this->width()/10;
//    h = 2*w;
    for(int i=0;i<7;i++){
        for(int j=0;j<48;j++){
            isActive[i][j] = true;
        }
    }
    stringOfDay[0]=QString("星期一");
    stringOfDay[1]=QString("星期二");
    stringOfDay[2]=QString("星期三");
    stringOfDay[3]=QString("星期四");
    stringOfDay[4]=QString("星期五");
    stringOfDay[5]=QString("星期六");
    stringOfDay[6]=QString("星期日");

    btn = new QToolButton(this);
    btn->setText(QString("应用变更后的时间表"));
    connect(btn,SIGNAL(clicked()),this,SLOT(saveTime()));

    unit = new QLabel(this);
    unit->setText("单位：小时");
    use = new QLabel(this);
    use->setText("激活");
    noUse = new QLabel(this);
    noUse->setText("禁用");

    noUse->setAlignment(Qt::AlignCenter);
    noUse->setFrameShape(QFrame::Box);
    use->setStyleSheet(QString("border-width: 1px;border-style: solid;background-color: rgb(0, 0, 255);"));
    use->setAlignment(Qt::AlignCenter);
    noUse->setFrameShape(QFrame::Box);
    noUse->setStyleSheet(QString("border-width: 1px;border-style: solid;background-color: rgb(255,255,255);"));
    //this->setGeometry(monitor->width()/2,0,1050,400);
//    qDebug()<<"monitor.width:"<<monitor->width();
//    qDebug()<<"monitor.height"<<monitor->height();
}

void HourWidget::paintEvent(QPaintEvent *){
    QPainter p(this);
    QColor color(0,0,255);

    int y = yStart;
    for(int i=0;i<=24;i++){

        int x1=xStart+i*w*2;
        if(i>9)
            x1-=4;
        else
            x1-=2;
        p.drawText(x1,y-2,QString::number(i));
    }
    for(int i=0;i<7;i++){
        int x = xStart;
        for(int j = 0;j<48;j++){
            if(isActive[i][j]){
                p.fillRect(x,y,w,h,color);
            }
            x += w;
        }
        y += h;
        p.drawText(10,y-15,stringOfDay[i]);
    }
    int xEnd = xStart + 48*w;
    int yEnd = yStart + 7*h;
    int x = xStart;
    for(int i=0;i<=48;i++){
        p.drawLine(x,yStart,x,yEnd);
        x+=w;
    }

    y = yStart;
    for(int i=0;i<=7;i++){
        p.drawLine(xStart,y,xEnd,y);
        y+=h;
    }

    btn->setGeometry(xEnd-this->width()/4,yEnd+20,this->width()/4,this->height()/13);
    use->setGeometry(xEnd/3-xStart/3,yEnd+20,this->width()/20,this->height()/13);
    noUse->setGeometry(xEnd/2-xStart/2,yEnd+20,this->width()/20,this->height()/13);
    unit->setGeometry(xEnd/6-xStart/6,yEnd+20,this->width()/9,this->height()/13);
    //qDebug()<<unit->geometry().x()<<"   "<<unit->geometry().y()<<"  "<<unit->geometry().width()<<"  "<<unit->geometry().height();
}

void HourWidget::mouseReleaseEvent(QMouseEvent *e){
    if(e->button() == Qt::LeftButton){
        QPoint p = e->pos();
        int x = p.x();
        int y = p.y();
        x-=xStart;
        y-=yStart;
        if(x<0 || y<0 || x>=48*w || y>=7*h){
            e->ignore();
            return;
        }
        int j = x/w;
        int i = y/h;
        isActive[i][j] = !isActive[i][j];
        update();
    }
    e->ignore();
}

void HourWidget::saveTime(){
    monitor->onSelectTime();
}
