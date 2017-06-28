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
    painter.drawText(40,y,QString("目标中心坐标：<").append(QString::number(obj->cenPoint.x)).append(",").append(QString::number(obj->cenPoint.y)).append(">"));
    y+=30;
    painter.drawText(40,y,QString("检测框大小：<").append(QString::number(obj->blocksize.width)).append(",").append(QString::number(obj->blocksize.height)).append(">"));
    y+=30;
    painter.drawText(40,y,QString("运动速率：").append(QString::number(obj->Velocity)));
    y+=30;
    painter.drawText(40,y,QString("运动方向：").append(QString::number(obj->MotionDerection)));
    y+=30;
    painter.drawText(40,y,QString("目标面积：").append(QString::number(obj->area)));
    y+=30;
    painter.drawText(40,y,QString("水平轴长度：").append(QString::number(obj->horizontalAxisLength)));
    y+=30;
    painter.drawText(40,y,QString("竖直轴长度：").append(QString::number(obj->verticalAxisLength)));
    y+=30;
    painter.drawText(40,y,QString("绝对强度：").append(QString::number(obj->absoluteIntensity)));
    y+=30;
    painter.drawText(40,y,QString("相对强度：").append(QString::number(obj->relativeIntensity)));
    y+=30;
    painter.drawText(40,y,QString("目标尺度：").append(QString::number(obj->targetScale)));
    y+=30;
    painter.drawText(40,y,QString("中央周围对比度的响应强度：").append(QString::number(obj->CenSueEintensity)));
    y+=30;
    painter.drawText(40,y,QString("目标背景信杂比：").append(QString::number(obj->SCRValue)));
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
