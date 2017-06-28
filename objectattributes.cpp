#include "objectattributes.h"
#include <QPainter>
#include<QString>

ObjectAttributes::ObjectAttributes(MyObject *obj) :
    QMainWindow()
{
    this->obj=obj;
}

ObjectAttributes::~ObjectAttributes()
{
}
void ObjectAttributes::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    int y = 30;
    painter.drawText(40,y,QString("oid:").append(QString::number(obj->oid)));
    y+=30;
    painter.drawText(40,y,QString("Ŀ���������꣺<").append(QString::number(obj->cenPoint.x)).append(",").append(QString::number(obj->cenPoint.y)).append(">"));
    y+=30;
    painter.drawText(40,y,QString("�����С��<").append(QString::number(obj->blocksize.width)).append(",").append(QString::number(obj->blocksize.height)).append(">"));
    y+=30;
    painter.drawText(40,y,QString("�˶����ʣ�").append(QString::number(obj->Velocity)));
    y+=30;
    painter.drawText(40,y,QString("�˶�����").append(QString::number(obj->MotionDerection)));
    y+=30;
    painter.drawText(40,y,QString("Ŀ�������").append(QString::number(obj->area)));
    y+=30;
    painter.drawText(40,y,QString("ˮƽ�᳤�ȣ�").append(QString::number(obj->horizontalAxisLength)));
    y+=30;
    painter.drawText(40,y,QString("��ֱ�᳤�ȣ�").append(QString::number(obj->verticalAxisLength)));
    y+=30;
    painter.drawText(40,y,QString("����ǿ�ȣ�").append(QString::number(obj->absoluteIntensity)));
    y+=30;
    painter.drawText(40,y,QString("���ǿ�ȣ�").append(QString::number(obj->relativeIntensity)));
    y+=30;
    painter.drawText(40,y,QString("Ŀ��߶ȣ�").append(QString::number(obj->targetScale)));
    y+=30;
    painter.drawText(40,y,QString("������Χ�Աȶȵ���Ӧǿ�ȣ�").append(QString::number(obj->CenSueEintensity)));
    y+=30;
    painter.drawText(40,y,QString("Ŀ�걳�����ӱȣ�").append(QString::number(obj->SCRValue)));
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
