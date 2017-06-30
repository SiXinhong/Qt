#include "objectAttributes.h"
#include <QPainter>
#include<QString>
#include "myinterface.h"
#include "QMainWindow.h"
#include <cv.h>
#include "mainwindow.h"
#include <QImage>

ObjectAttributes::ObjectAttributes(MyInterface *objectInterface) :
    QMainWindow()
{
    this->objectInterface=objectInterface;
}

ObjectAttributes::~ObjectAttributes()
{
}

void ObjectAttributes::paintEvent(QPaintEvent *event)
{
    vector<MyObject> vec = objectInterface->getObjs2();
    int y = 30;
    for(int i = 0; i < vec.size();i++){
        MyObject *obj = &vec.at(i);
        QPainter painter(this);
        int x=30;
        painter.drawText(x,y,QString("目标").append(QString::number(i+1)).append(":"));
        y+=30;
        painter.drawText(x,y,QString("oid:").append(QString::number(obj->oid)));
        x+=180;
        painter.drawText(x,y,QString("目标中心坐标：<").append(QString::number(obj->cenPoint.x)).append(",").append(QString::number(obj->cenPoint.y)).append(">"));
        x+=180;
        painter.drawText(x,y,QString("检测框大小：<").append(QString::number(obj->blocksize.width)).append(",").append(QString::number(obj->blocksize.height)).append(">"));
        x+=180;
        painter.drawText(x,y,QString("运动速率：").append(QString::number(obj->Velocity)));
        x+=180;
        painter.drawText(x,y,QString("运动方向：").append(QString::number(obj->MotionDerection)));
        y+=30;
        x=30;
        painter.drawText(x,y,QString("目标面积：").append(QString::number(obj->area)));
        x+=180;
        painter.drawText(x,y,QString("水平轴长度：").append(QString::number(obj->horizontalAxisLength)));
        x+=180;
        painter.drawText(x,y,QString("竖直轴长度：").append(QString::number(obj->verticalAxisLength)));
         x+=180;
        painter.drawText(x,y,QString("绝对强度：").append(QString::number(obj->absoluteIntensity)));
        x+=180;
        painter.drawText(x,y,QString("相对强度：").append(QString::number(obj->relativeIntensity)));
        y+=30;
        x=30;
        painter.drawText(x,y,QString("目标尺度：").append(QString::number(obj->targetScale)));
        x+=180;
        painter.drawText(x,y,QString("中央周围对比度的响应强度：").append(QString::number(obj->CenSueEintensity)));
        x+=180;
        painter.drawText(x,y,QString("目标背景信杂比：").append(QString::number(obj->SCRValue)));
        x=30;
        y+=30;
        painter.drawText(x,y,QString("目标轮廓："));
        if (!obj->contours.empty())
        {
//            x=30;
//            y+=30;
//            painter.drawText(x,y,QString("目标轮廓:"));
            x+=100;
            for(int k = 0; k <= obj->contours.size();k++)
            {
                //qDebug()<<k;
                painter.drawText(x,y,QString::number(obj->contours.at(k).x).append(QString::number(obj->contours.at(k).y)));
            }
        }
        else {
            x+=80;
            painter.drawText(x,y,QString("无"));
        }
        x+=240;
        painter.drawText(x,y,QString("目标快照："));
        if(!obj->Snapshoot.empty())
        {
//            x=30;
//            y+=50;
//            painter.drawText(x,y,QString("目标快照："));
            x+=100;
            cv::resize(obj->Snapshoot, obj->Snapshoot, cv::Size(50,50));
            QImage qimage = MainWindow::MatToQImage(obj->Snapshoot,QImage());
            painter.drawImage(x,y,qimage);
         }
        else{
            x+=80;
            painter.drawText(x,y,QString("无"));
        }
        x+=240;
        painter.drawText(x,y,QString("目标剪影："));
        if(!obj->sihouette.empty())
        {
//            x=30;
//            y+=50;
//            painter.drawText(x,y,QString("目标剪影："));
            x+=100;
            cv::resize(obj->Snapshoot, obj->Snapshoot, cv::Size(50,50));
            QImage qimage = MainWindow::MatToQImage(obj->Snapshoot,QImage());
            painter.drawImage(x,y,qimage);

        }
        else{
            x+=80;
            painter.drawText(x,y,QString("无"));
        }
        y+=90;
       }

   QFont font("宋体", 15, QFont::Bold, true);
    //设置下划线
   font.setUnderline(true);
    //设置上划线
   font.setOverline(true);
    //设置字母大小写
    font.setCapitalization(QFont::SmallCaps);
    //设置字符间的间距
    font.setLetterSpacing(QFont::AbsoluteSpacing, 10);
}
