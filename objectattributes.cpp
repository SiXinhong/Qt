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
    painter.drawText(40,40,"��");
    painter.drawText(40,60,"hao");

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
