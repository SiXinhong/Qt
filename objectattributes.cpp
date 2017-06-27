#include "objectattributes.h"
#include "ui_objectattributes.h"
#include <QPainter>
#include<QString>

ObjectAttributes::ObjectAttributes(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ObjectAttributes)
{
    ui->setupUi(this);
}

ObjectAttributes::~ObjectAttributes()
{
    delete ui;
}
void ObjectAttributes::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.drawText(40,40,"好");
    painter.drawText(40,60,"hao");

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
