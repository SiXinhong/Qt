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
        painter.drawText(x,y,QString("Ŀ��").append(QString::number(i+1)).append(":"));
        y+=30;
        painter.drawText(x,y,QString("oid:").append(QString::number(obj->oid)));
        x+=180;
        painter.drawText(x,y,QString("Ŀ���������꣺<").append(QString::number(obj->cenPoint.x)).append(",").append(QString::number(obj->cenPoint.y)).append(">"));
        x+=180;
        painter.drawText(x,y,QString("�����С��<").append(QString::number(obj->blocksize.width)).append(",").append(QString::number(obj->blocksize.height)).append(">"));
        x+=180;
        painter.drawText(x,y,QString("�˶����ʣ�").append(QString::number(obj->Velocity)));
        x+=180;
        painter.drawText(x,y,QString("�˶�����").append(QString::number(obj->MotionDerection)));
        y+=30;
        x=30;
        painter.drawText(x,y,QString("Ŀ�������").append(QString::number(obj->area)));
        x+=180;
        painter.drawText(x,y,QString("ˮƽ�᳤�ȣ�").append(QString::number(obj->horizontalAxisLength)));
        x+=180;
        painter.drawText(x,y,QString("��ֱ�᳤�ȣ�").append(QString::number(obj->verticalAxisLength)));
         x+=180;
        painter.drawText(x,y,QString("����ǿ�ȣ�").append(QString::number(obj->absoluteIntensity)));
        x+=180;
        painter.drawText(x,y,QString("���ǿ�ȣ�").append(QString::number(obj->relativeIntensity)));
        y+=30;
        x=30;
        painter.drawText(x,y,QString("Ŀ��߶ȣ�").append(QString::number(obj->targetScale)));
        x+=180;
        painter.drawText(x,y,QString("������Χ�Աȶȵ���Ӧǿ�ȣ�").append(QString::number(obj->CenSueEintensity)));
        x+=180;
        painter.drawText(x,y,QString("Ŀ�걳�����ӱȣ�").append(QString::number(obj->SCRValue)));
        x=30;
        y+=30;
        painter.drawText(x,y,QString("Ŀ��������"));
        if (!obj->contours.empty())
        {
//            x=30;
//            y+=30;
//            painter.drawText(x,y,QString("Ŀ������:"));
            x+=100;
            for(int k = 0; k <= obj->contours.size();k++)
            {
                //qDebug()<<k;
                painter.drawText(x,y,QString::number(obj->contours.at(k).x).append(QString::number(obj->contours.at(k).y)));
            }
        }
        else {
            x+=80;
            painter.drawText(x,y,QString("��"));
        }
        x+=240;
        painter.drawText(x,y,QString("Ŀ����գ�"));
        if(!obj->Snapshoot.empty())
        {
//            x=30;
//            y+=50;
//            painter.drawText(x,y,QString("Ŀ����գ�"));
            x+=100;
            cv::resize(obj->Snapshoot, obj->Snapshoot, cv::Size(50,50));
            QImage qimage = MainWindow::MatToQImage(obj->Snapshoot,QImage());
            painter.drawImage(x,y,qimage);
         }
        else{
            x+=80;
            painter.drawText(x,y,QString("��"));
        }
        x+=240;
        painter.drawText(x,y,QString("Ŀ���Ӱ��"));
        if(!obj->sihouette.empty())
        {
//            x=30;
//            y+=50;
//            painter.drawText(x,y,QString("Ŀ���Ӱ��"));
            x+=100;
            cv::resize(obj->Snapshoot, obj->Snapshoot, cv::Size(50,50));
            QImage qimage = MainWindow::MatToQImage(obj->Snapshoot,QImage());
            painter.drawImage(x,y,qimage);

        }
        else{
            x+=80;
            painter.drawText(x,y,QString("��"));
        }
        y+=90;
       }

   QFont font("����", 15, QFont::Bold, true);
    //�����»���
   font.setUnderline(true);
    //�����ϻ���
   font.setOverline(true);
    //������ĸ��Сд
    font.setCapitalization(QFont::SmallCaps);
    //�����ַ���ļ��
    font.setLetterSpacing(QFont::AbsoluteSpacing, 10);
}
