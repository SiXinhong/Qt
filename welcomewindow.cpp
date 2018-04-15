#include "welcomewindow.h"
#include <QApplication>
#include <QDesktopWidget>
#include <QDebug>
#include <QPainter>
#include <QPen>
#include <QToolButton>
#include <QHBoxLayout>
#include <QGroupBox>
#include <QSettings>
#include <QDateTime>



WelcomeWindow::WelcomeWindow(QWidget *parent) :
    QWidget(parent)
{
    start = false;
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
    mainwindow = new MainWindow(this);
//    usernameInput->setGeometry(150,425,90,30);
//    passwordInput->setGeometry(150,515,90,30);
//    logIn->setGeometry(80,590,60,25);
//    exit->setGeometry(150,590,60,25);
    User user1("test1m","123456",2);
    User user2("test3m","000000",3);
    User user3("test6m","000000",6);
    User user4("test1y","000000",12);
    User user5("test2y","000000",24);
    User user6("test3y","000000",36);
    User user7("test5y","000000",60);
    users.insert(pair<QString,User>(user1.name,user1));
    users.insert(pair<QString,User>(user2.name,user2));
    users.insert(pair<QString,User>(user3.name,user3));
    users.insert(pair<QString,User>(user4.name,user4));
    users.insert(pair<QString,User>(user5.name,user5));
    users.insert(pair<QString,User>(user6.name,user6));
    users.insert(pair<QString,User>(user7.name,user7));
    qDebug()<<"welcome";
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

    map<QString,User>::iterator iter;
    iter = users.find(usernameInput->text());
    if(iter == users.end()){
        QMessageBox::information(this,tr("登录失败"),QString("用户名错误！"));
        return;
    }
    User user = iter->second;

    if(user.password.compare(passwordInput->text())!=0){
        QMessageBox::information(this,tr("登录失败"),QString("密码错误！"));
        return;
    }

    QSettings reg("HKEY_LOCAL_MACHINE\\SOFTWARE\\fjrcopyright2018",QSettings::NativeFormat);
    QString key=QString("initTime").append(user.name);
    QVariant result = reg.value(key);
    uint currentTime = QDateTime::currentDateTime().toTime_t();
    if(!result.isValid()){
        qDebug()<<"init"<<user.name;
        reg.setValue(key,QVariant(3,&currentTime));//第一个参数表明是uint类型的数据
        result = reg.value(key);//再读一遍以免写入失败
    }
    // 写入失败的情况
    if(!result.isValid()){
        QMessageBox::information(this,tr("登录失败"),QString("登录失败！"));
        return;
    }
    qDebug()<<result.toUInt()<<","<<user.validity;
    if(currentTime>result.toUInt()+user.validity){
        QMessageBox::information(this,tr("登录失败"),QString("用户已过期！"));
        return;
    }

    if(!start){
         //mainwindow->init();
        if(mainwindow->configure == NULL){
            mainwindow->configure = new Configuration(mainwindow);
        }
//        mainwindow->configure->readCon();放到configuration的构造函数里调用了
        //mainwindow->configurationClicked();注释以直接展示mainwindow，添加mainwindow->configure->mainwindowShow();
        mainwindow->configure->mainwindowShow();
         start =true;
    }
    else{
        qDebug()<<"welcome1";
        mainwindow->show();
        qDebug()<<"welcome2";
        this->close();
        qDebug()<<"welcome3";
//        delete mainwindow;
//        MainWindow *mainwindow1 = new MainWindow(this);
//        mainwindow1->init();

    }
}


