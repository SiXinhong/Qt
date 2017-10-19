#include "welcomewindow.h"
#include <QApplication>
#include <QDesktopWidget>
#include <QDebug>
#include <QPainter>
#include <QPen>
#include <QToolButton>
#include <QHBoxLayout>
#include <QGroupBox>



WelcomeWindow::WelcomeWindow(QWidget *parent) :
    QWidget(parent)
{
    this->setWindowFlags(Qt::FramelessWindowHint);
    QDesktopWidget* desktopWidget = QApplication::desktop();
    QRect screenRect = desktopWidget->screenGeometry();  //屏幕区域
    int screenWidth=screenRect.width();
    int screenHeight=screenRect.height();
    this->setGeometry(screenWidth/2-1250/2,screenHeight/2-600/2,1250,700);

    usernameInput = new QLineEdit(this);
    passwordInput = new QLineEdit(this);
    logIn = new QToolButton(this);
    exit = new QToolButton(this);

    passwordInput->setEchoMode(QLineEdit::Password);

    logIn->setText(QString("登陆"));
    exit->setText(QString("退出"));
    connect(exit,SIGNAL(clicked()),this,SLOT(exitClicked()));
    connect(logIn,SIGNAL(clicked()),this,SLOT(loginClicked()));
   // mainwindow = new MainWindow(this);
//    usernameInput->setGeometry(150,425,90,30);
//    passwordInput->setGeometry(150,515,90,30);
//    logIn->setGeometry(80,590,60,25);
//    exit->setGeometry(150,590,60,25);
}

void WelcomeWindow::paintEvent(QPaintEvent *){
    QPainter p(this);
    QFont font("宋体",18,75);
    p.setFont(font);
    //标题
    QString title("红外全景监控系统");
    int widthOfTitle = p.fontMetrics().width(title);
    p.drawText(this->width()/2-widthOfTitle/2,100,title);
    //图片
    QImage image("./icon/load.bmp");
    p.drawImage(this->width()/2-image.width()/2,this->height()/2-image.height()/2-100,image);
    //p.drawImage();
    //默认用户名密码
    font.setPointSize(12);
    p.setFont(font);
    QString user("用户名:");
    QString password("密码:");
    p.drawText(80,450,user);
    p.drawText(80,540,password);

    int h = p.fontMetrics().height();
    int w = p.fontMetrics().width(user);
    usernameInput->setGeometry(80+w+20,450-h,w*2,h*1.5);
    passwordInput->setGeometry(80+w+20,540-h,w*2,h*1.5);
    logIn->setGeometry(80,590,w,h*1.5);
    exit->setGeometry(80+w*1.2,590,w,h*1.5);
    //版权所有
    font.setPointSize(8);
    p.setFont(font);
    QString copyright("版权所有");
    int widthOfCopy = p.fontMetrics().width(copyright);
    p.drawText(this->width()/2-widthOfCopy/2,650,copyright);

}

void WelcomeWindow::exitClicked(){
    QApplication::closeAllWindows();

}

void WelcomeWindow::loginClicked(){
    //mainwindow->init();
}

//void WelcomeWindow::setMainwindow(MainWindow mainwindow){
//    this->mainwindow = mainwindow
//}
