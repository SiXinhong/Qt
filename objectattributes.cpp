#include "objectAttributes.h"
#include <QPainter>
#include<QString>
#include "myinterface.h"
#include "QMainWindow.h"

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
    int y = 30,x = 40;
    for(int i = 0; i < vec.size();i++){
        MyObject *obj = &vec.at(i);
        QPainter painter(this);
        painter.drawText(x,y,QString("Ŀ��").append(QString::number(i+1)).append(":"));
        y+=30;
        painter.drawText(x,y,QString("oid:").append(QString::number(obj->oid)));
        x+=180;
        painter.drawText(x,y,QString("Ŀ���������꣺<").append(QString::number(obj->cenPoint.x)).append(",").append(QString::number(obj->cenPoint.y)).append(">"));
        x+=180;
        painter.drawText(x,y,QString("�����С��<").append(QString::number(obj->blocksize.width)).append(",").append(QString::number(obj->blocksize.height)).append(">"));
        x+=180;
        painter.drawText(x,y,QString("�˶����ʣ�").append(QString::number(obj->Velocity)));
        y+=30;
        x=40;
        painter.drawText(x,y,QString("�˶�����").append(QString::number(obj->MotionDerection)));
        x+=180;
        painter.drawText(x,y,QString("Ŀ�������").append(QString::number(obj->area)));
        x+=180;
        painter.drawText(x,y,QString("ˮƽ�᳤�ȣ�").append(QString::number(obj->horizontalAxisLength)));
        x+=180;
        painter.drawText(x,y,QString("��ֱ�᳤�ȣ�").append(QString::number(obj->verticalAxisLength)));
        y+=30;
        x=40;
        painter.drawText(x,y,QString("����ǿ�ȣ�").append(QString::number(obj->absoluteIntensity)));
        x+=180;
        painter.drawText(x,y,QString("���ǿ�ȣ�").append(QString::number(obj->relativeIntensity)));
        x+=180;
        painter.drawText(x,y,QString("Ŀ��߶ȣ�").append(QString::number(obj->targetScale)));
        x+=180;
        painter.drawText(x,y,QString("������Χ�Աȶȵ���Ӧǿ�ȣ�").append(QString::number(obj->CenSueEintensity)));
        y+=30;
        x=40;
        painter.drawText(x,y,QString("Ŀ�걳�����ӱȣ�").append(QString::number(obj->SCRValue)));
        y+=70;
       }
   // painter.drawPicture(40,y,QPicture);
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
