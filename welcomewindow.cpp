#include "welcomewindow.h"
#include <QApplication>
#include <QDesktopWidget>
#include <QDebug>
#include <QPainter>
#include <QPen>


WelcomeWindow::WelcomeWindow(QWidget *parent) :
    QWidget(parent)
{
    this->setWindowFlags(Qt::FramelessWindowHint);
    QDesktopWidget* desktopWidget = QApplication::desktop();
    QRect screenRect = desktopWidget->screenGeometry();  //��Ļ����
    int screenWidth=screenRect.width();
    int screenHeight=screenRect.height();
    this->setGeometry(screenWidth/2-1250/2,screenHeight/2-600/2,1250,700);
}

void WelcomeWindow::paintEvent(QPaintEvent *){
    QPainter p(this);
    QFont font("����",20,75);
    p.setFont(font);
//    QString co("������");
//    p.drawText(20,100,co);
    QString title("����ȫ�����ϵͳ");
    int widthOfTitle = p.fontMetrics().width(title);
    p.drawText(this->width()/2-widthOfTitle/2,100,title);
    QImage image("./icon/load.bmp");
    p.drawImage(this->width()/2-image.width()/2,this->height()/2-image.height()/2,image);
    font.setPointSize(8);
    p.setFont(font);
    QString copyright("��Ȩ����");
    int widthOfCopy = p.fontMetrics().width(copyright);
    p.drawText(this->width()/2-widthOfCopy/2,650,copyright);

}
