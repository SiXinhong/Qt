﻿#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qj1widget.h"
#include "qj2widget.h"
#include "zwidget.h"
#include "nwidget1.h"
#include "nwidget2.h"
#include "hwidget.h"
#include "lwidget.h"
#include "myinterface.h"
#include "myobject.h"
#include "mixer.h"
#include "cvutil.h"
#include <QDesktopWidget>
#include "imagedeal.h"
#include "monitor.h"


//opencv的头文件
#include <vector>
#include <highgui.h>
#include <cv.h>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

#include <QApplication>
#include <QToolBar>
#include <QGridLayout>
#include <QPainter>
#include<QPalette>
#include<QPixmap>
#include<QImage>
#include<QLabel>
#include<QDebug>
#include<QTimer>
#include<QDateTime>
#include<QMessageBox>

#include <QPoint>
#include <QMouseEvent>
#include <QtGui/QPainter>
#include "trackbar.h"
#include <QDir>
#include "stdio.h"
#include <stdlib.h>

//截图
#include<windows.h>

//////////////////////////////ZC/////////////////
SOCKET hSocket;			//事件对象连接的套接字
WSAEVENT hEvent;			//套接字相连的事件对象
int datalen;			//定义一个整数，表示从当前传输的数据中得到的数据长度
char sendbuffer[SEND_BUFFER_SIZE];				//定义的一个socket的发送缓冲区
char recvbuffer[RECV_BUFFER_SIZE];				//定义的一个socket的接收缓冲区
char *databuffer = (char *)malloc(DATA_BUFFER_SIZE);//存放数据的静态缓冲区

WSANETWORKEVENTS netEvents;

#define DATA_LENGTH_MAX     10*1024*1024
#define DATA_LENGTH_MIN     9
////////////////////////////////zc//////////////////

using namespace cv;
using namespace std;

QTime dateTimeStart;
QTime dateTimeStop;
MainWindow::MainWindow(WelcomeWindow *welcome,QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    this->welcome=welcome;
    configure = 0;
    widget3=0;
    widget4=0;
    widget6=0;
    qDebug()<<"mainwindow";
    //因为Backwindow继承了MainWindow，Backwindow不需要启动界面，给构造函数传递空指针，
    //这时候一定要立即执行init()，否则Backwindow以为初始化工作完成开始执行别的代码时就报错了
    if(welcome != 0){
        backwindow =0;
        welcome->show();
        //        timerInit=new QTimer();
        //        timerInit->setInterval(100);
        //        timerInit->setSingleShot(true);
        //        timerInit->start();
        //        connect(timerInit, SIGNAL(timeout()), SLOT(init()));
    }else{
        backwindow = (BackWindow*)this;
        init();
        //configurationClicked();
    }
}

QString MainWindow::zhanweiName="";

bool MainWindow::isInit =false;

void MainWindow::init(){
//    configure = 0;
    if(0 == backwindow){
        inThread.start();//启动通信线程
        storeThread = new StoreThread(this);
        storeThread->start();//启动序列化多线程
    }
    alert = 0;
    monitor = 0;
    isOpenMonitor = false;
    this->setWindowTitle("红外全景控制系统");
    location = false;
    directory = new QDir();
    widgetNew=NULL;

    this->setWindowFlags(Qt::FramelessWindowHint);
    // this->objectAttributes=new ObjectAttributes(&this->in);
    this->objectAttributes = 0;
//    cmixer = new CMixer();
//    sound = new QSound("E:\github\Qt\1.mp3",this);
    color = 0;
    //saturation1 = 100;
    //hsl=new HSL();

    isBright = false;
    isContrast = false;

    bright_TrackbarValue=0;
    alpha_contrast = 100;
    //objectAttributes = new QLabel();
    isPseudo = false;
    isVoice = false;
    //设置属性设置中的变量的默认值-------------------------------
    //启动还是停止
    isQidong = true;
    //暂停还是继续
    isJixu = false;
    //告警启动还是关闭
    isGaojing = true;
    //声音打开还是关闭
    isShengyin = false;
    //目标属性是否跟随
    isMubiao = false;
    //系统编号
    //xtbh = QString("BJ036A战位");
    //-------------------------------------------------------
    //判断窗口是否打开
    is_open=false;
    //判断是否处于定义监控区域的状态
    this->isDefiningRegion = false;
    this->isDefiningRectRegion = true;

    readRgs();

    //临时的，监控区域的定义需要由定义监控区域的界面来打开
    char name  = 'a'+rgs.size();
    rg = RegionGroup((QString)name, Scalar(0,255,0));
    rgs.push_back(rg);
    rgsIndex = rgs.size()-1;

    ui->setupUi(this);
    QWidget* widget = new QWidget(this);

    //widget10 = new QWidget(this);

    QWidget *tempW = new QWidget(this);
    tempW->setGeometry(0,0,1,1);
    qDebug()<<"ini()3";
    //    widget1 = new Qj1Widget(new QWidget(this));
    //    widget2 = new Qj2Widget(new QWidget(this));
    //    widget3 = new ZWidget(new QWidget(this));
    //    widget4 = new NWidget1(new QWidget(this));
    //    widget5 = new HWidget(new QWidget(this));
    //    //widget6 = new LWidget(new QWidget(this));
    //    widget6 = new NWidget2(new QWidget(this));

    widget1 = new Qj1Widget(tempW);
    widget2 = new Qj2Widget(tempW);
    widget3 = new ZWidget(tempW);
    widget4 = new NWidget1(tempW);
    widget5 = new HWidget(tempW);
    widget6 = new NWidget2(tempW);
    widget7 = new LWidget(tempW);

    label=new QLabel(widget1);
    label2=new QLabel(widget2);
    label3=new QLabel(widget3);
    label4=new QLabel(widget4);
    label5=new QLabel(widget5);
    label6=new QLabel(widget6);

    label7=new QLabel(widget7);


    zWini = new QToolButton(label3);
    zWZoomIn = new QToolButton(label3);
    zWZoomout = new QToolButton(label3);

    n1Wini = new QToolButton(label4);
    n1WZoomIn = new QToolButton(label4);
    n1WZoomout = new QToolButton(label4);

    n2Wini = new QToolButton(label6);
    n2WZoomIn = new QToolButton(label6);
    n2WZoomout = new QToolButton(label6);


    //zWZoomIn->setText("放大");
    zWZoomIn->setGeometry(40,40,50,50);
    zWZoomIn->setToolTip("放大");
    zWZoomIn->setIcon(QPixmap("./iconUpdate/放大.png"));
    zWZoomIn->setIconSize(QSize(50,50));
    //zWZoomout->setText("缩小");
    zWZoomout->setGeometry(100,40,50,50);
    zWZoomout->setToolTip("缩小");
    zWZoomout->setIcon(QPixmap("./iconUpdate/缩小.png"));
    zWZoomout->setIconSize(QSize(50,50));
    //zWini->setText("还原");
    zWini->setGeometry(160,40,50,50);
    zWini->setToolTip("还原");
    zWini->setIcon(QPixmap("./iconUpdate/还原.png"));
    zWini->setIconSize(QSize(50,50));
    connect(zWZoomIn,SIGNAL(clicked()),this,SLOT(zoomIn3()));
    connect(zWZoomout,SIGNAL(clicked()),this,SLOT(zoomOut3()));
    connect(zWini,SIGNAL(clicked()),this,SLOT(zoomInitial3()));

    n1WZoomIn->setText("放大");
    n1WZoomIn->setGeometry(40,40,50,50);
    n1WZoomIn->setToolTip("放大");
    n1WZoomIn->setIcon(QPixmap("./iconUpdate/放大.png"));
    n1WZoomIn->setIconSize(QSize(50,50));
    n1WZoomout->setText("缩小");
    n1WZoomout->setGeometry(100,40,50,50);
    n1WZoomout->setToolTip("缩小");
    n1WZoomout->setIcon(QPixmap("./iconUpdate/缩小.png"));
    n1WZoomout->setIconSize(QSize(50,50));
    n1Wini->setText("还原");
    n1Wini->setGeometry(160,40,50,50);
    n1Wini->setToolTip("还原");
    n1Wini->setIcon(QPixmap("./iconUpdate/还原.png"));
    n1Wini->setIconSize(QSize(50,50));
    connect(n1WZoomIn,SIGNAL(clicked()),this,SLOT(zoomIn4()));
    connect(n1WZoomout,SIGNAL(clicked()),this,SLOT(zoomOut4()));
    connect(n1Wini,SIGNAL(clicked()),this,SLOT(zoomInitial4()));

    n2WZoomIn->setText("放大");
    n2WZoomIn->setGeometry(40,40,50,50);
    n2WZoomIn->setToolTip("放大");
    n2WZoomIn->setIcon(QPixmap("./iconUpdate/放大.png"));
    n2WZoomIn->setIconSize(QSize(50,50));
    n2WZoomout->setText("缩小");
    n2WZoomout->setGeometry(100,40,50,50);
    n2WZoomout->setToolTip("缩小");
    n2WZoomout->setIcon(QPixmap("./iconUpdate/缩小.png"));
    n2WZoomout->setIconSize(QSize(50,50));
    n2Wini->setText("还原");
    n2Wini->setGeometry(160,40,50,50);
    n2Wini->setToolTip("还原");
    n2Wini->setIcon(QPixmap("./iconUpdate/还原.png"));
    n2Wini->setIconSize(QSize(50,50));
    connect(n2WZoomIn,SIGNAL(clicked()),this,SLOT(zoomIn6()));
    connect(n2WZoomout,SIGNAL(clicked()),this,SLOT(zoomOut6()));
    connect(n2Wini,SIGNAL(clicked()),this,SLOT(zoomInitial6()));

    //鼠标拖拽控制变量赋初值
    isDrag1 = false;
    isDrag2 = false;
    isMove = false;

    ////////////////zc///////////////////////
    //通信连接
   // MySocketInitial();
    qDebug()<<"ini()6";
    //自定义接口处理，将来被金老师SDK替换--------------------------------
    //in = MyInterface();
//    selfProcessing();
    if(0==backwindow){
        this->jinProcessing();
    }
    //---------------------------------------------------------
    qDebug()<<"ini()4";
    //临时性处理，将来被金老师SDK替换--------------------------------
    //tempProcessing();
    //---------------------------------------------------------
    //定时器
    showAlert = new QTimer();

    timer=new QTimer();
    timer->setInterval(1500);

    //定时器，获取系统时间

    timerSysTime=new QTimer();
    timerSysTime->setInterval(1000);



    timerFlash = new QTimer();
    timerFlash->setInterval(100);

    timerUpdateHWidget = new QTimer();
    timerUpdateHWidget->setInterval(1000*60*5);//每5分钟更新一次环带视图
    if(0==backwindow){
        timer->start();
        connect(timer, SIGNAL(timeout()), SLOT(onTimerOut()));
        timerSysTime->start();
        connect(timerSysTime, SIGNAL(timeout()), SLOT(onTimerOut2()));
        connect(timerFlash, SIGNAL(timeout()), SLOT(flash()));
        timerUpdateHWidget->start();
        connect(timerUpdateHWidget, SIGNAL(timeout()), SLOT(updateHWidget()));
    }

    //创建菜单栏
    addMyMenuBar();
    // 创建工具栏
    //qDebug()<<"addmytoolbar1";
    addMyToolBar();
    //qDebug()<<"addmytoolbar2";
    //布局
    gridlayout = new QGridLayout;
    //mainToolBar->setStyleSheet("background-color:#2E302D");
    gridlayout->addWidget(menubar,0,0,1,3);
    gridlayout->addWidget(mainToolBar,1,0,1,3);

    gridlayout->addWidget(widget1,2,0,1,3);
    gridlayout->addWidget(widget2,3,0,1,3);
    gridlayout->addWidget(widget3,4,0,1,3);
    gridlayout->addWidget(widget4,5,0);
    gridlayout->addWidget(widget5,5,1);
    //gridlayout->addWidget(widget7,5,1);
    gridlayout->addWidget(widget6,5,2);

    //gridlayout->setRowStretch(1, 1);

    gridlayout->setRowStretch(2, 1);
    gridlayout->setRowStretch(3, 1);
    gridlayout->setRowStretch(4, 6);
    gridlayout->setRowStretch(5, 5);

    gridlayout->setColumnStretch(0,2);
    gridlayout->setColumnStretch(1,1);
    gridlayout->setColumnStretch(2,2);


    widget->setLayout(gridlayout);
    this->setCentralWidget(widget);

    this->setWindowState(Qt::WindowMaximized);
//    this->trackBar=new TrackBar(this);
//    this->strackBar = new STrackBar(this);
//      senAdjust = new Sensitivity(this);
      isSensi =false;
      senAdjust = 0;
    qDebug()<<"ini()5";

    //    double x = widget5->getDirectionX(1,2);
    //    qDebug()<<x<<"getDirectionX";
    //     double y = widget5->getDirectionY(1,2);
    //     x= widget5->getInverseDirectionX(x,y);
    //     qDebug()<<x<<"InverseDirectionX";

//    if(welcome!=0){
//        welcome->close();

//        this->show();//BackWindow的show是由mainwindow中指定代码调用的
//    }
 this->show();
    qDebug()<<"ini()7";
    isInit = true;
}

MainWindow::~MainWindow(){
    delete ui;
    // delete hsl;
    //delete strackBar;
    //delete trackBar;
    if(senAdjust)
        delete senAdjust;
    if( objectAttributes)
        delete objectAttributes;
    if(monitor)
        delete monitor;
//   delete cmixer;
//    delete sound;
    if(welcome){
        delete welcome;
    }
    delete directory;
    //cv::pointPolygonTest()//判断点是不是落在多边形之内的函数
    //cv::polylines()//绘制多边形
}

//处理告警，当有目标进入监控区域的时候，亮红灯
void MainWindow::alertProcessing(vector<MyObject> os){
    //qDebug()<<"rgs size:"<<this->rgs.size()<<",objs size:"<<os.size();
    QString group;
     boolean alert = false;
    if(isGaojing){
//        boolean alert = false;
        for(int i = 0; i < os.size(); i++){
            MyObject mo = os[i];
            for(int j = 0; j < this->rgs.size(); j++){
                if(rgs[j].isInner(Point2f(mo.cenPoint.x, mo.cenPoint.y))){
                    alert = true;
                    group =rgs.at(j).name;
                    break;
                }
            }
            if(alert){
                //播放音效
                if(isShengyin){
                    mp.setMedia(QUrl::fromLocalFile("./1.mp3"));
                    mp.setVolume(100);
                    mp.play();
                }
                break;
            }
        }
    }

    QPixmap pixmap1("./iconUpdate/报警灯-红.png");
    QPixmap pixmap2("./iconUpdate/报警灯-绿.png");
    //      fitpixmap1=pixmap1.scaled(buttonSize,buttonSize, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    //      fitpixmap2=pixmap2.scaled(buttonSize,buttonSize, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    if(alert){
        light->setIcon(pixmap1);
    }else{
        light->setIcon(pixmap2);
    }

    //        if(alert)
    //            QMessageBox::information(this,tr("告警"),QString("有目标进入监控区域组").append(group).append(" !"));
    //    }
    //
    //    if(alert){
    //        lightSet="./icon/16_1.png";
    //        light->setIcon(QPixmap(lightSet));
    //    }
    //    else{
    //        lightSet="./icon/16_2.png";
    //        light->setIcon(QPixmap(lightSet));
    //    }
}

//与金老师的接口处理
void MainWindow::jinProcessing(){
    //int v=in.getIntegratedData();
    int v = inThread.getIntegratedData();
//    if(v == 0){
        //std::cout<<"getintegrated data "<<std::endl;
        //图片1
        //        QString s1=in.getQJ1();
        //        imageurl=s1.toStdString();
        //        //qDebug()<<in.getObjs().size();
        //在全景上画矩形，文字，轨迹等
        //在两个全景上画矩形，文字，轨迹等
        QString today=QString("./回放/")+QDate::currentDate().toString("yyyy-MM-dd");
        // QDir *todayDir=new QDir();
        bool exist=directory->exists(today);
        if(!exist){
            directory->mkdir(today);
        }
        // delete todayDir;

        /***
         * 从interfaceThread一次性获取完数据，然后马上获取下一次的数据，不要到后边还有get调用，否则可能到下次执行timer通信还没结束
         */
        mainPano = inThread.getPano();
        vector<TrackingPoint> tps = inThread.GetTps();
        vector<MyObject> objs = inThread.getObjs();

        inThread.getNext();//开始下次通信
        //从interfaceThread获取数据结束
        storeThread->con.wakeOne();

        //qDebug()<<"jinPano.x.y"<<mainPano.cols<<mainPano.rows;
        if(isJixu == true){
            QString current_time=QTime::currentTime().toString("hh-mm-ss");
            QString current_path=QString("").append(today).append("/").append(current_time).append(".pan");
            QFile file(current_path);
            file.open(QIODevice::WriteOnly);
            QDataStream out(&file);
            if(mainPano.empty()){
                out<<-1;
            }else{
                out<<1;
                MyObject::writeMat(out,mainPano);
            }
            file.close();
            current_time.clear();
            current_path.clear();

        }


        Mat pano1 = mainPano.clone();
        Mat pano2 = mainPano.clone();
        Mat mat;
        hconcat(pano1,pano2,mat);
        //画轨迹
        //if(isMubiao){
            for(int ii = 0; ii < tps.size(); ii++){
                TrackingPoint tp = tps[ii];
                int id = tp.id;
                vector<Point> points = tp.track;
                //if(id == obj.getID()){
                for(int iii = 0; iii < points.size(); iii++){
                    Point point = points[iii];
                    Point point2 = Point(point.x+mainPano.cols, point.y);
                    //  std::cout<<"sdk point circle "<<point.x<<" "<<point.y<<std::endl;
                    circle(mat, point, 2, Scalar(0,0,255),1,8,0);//在图像中画出特征点，2是圆的半径
                    circle(mat, point2, 2, Scalar(0,0,255),1,8,0);//在图像中画出特征点，2是圆的半径
                    if(iii >= 1){
                        //std::cout<<"sdk point line "<<std::endl;
                        Point point3 = points[iii-1];
                       // std::cout<<"sdk point3 circle "<<point3.x<<" "<<point3.y<<std::endl;
                        Point point4 = Point(point3.x+mainPano.cols, point3.y);
                        line(mat,point,point3,Scalar(0,0,255),1,8,0);
                        line(mat,point2,point4,Scalar(0,0,255),1,8,0);
                    }
                    //cv::cvtColor(mat, mat, CV_BGR2RGB);
                }
                //}
            }
        //}
        //在全景上画矩形，文字，轨迹等
//        vector<MyObject> objs = in.getObjs();
//        for(int i=0;i<objs.size();i++){
//            QString current_time=QTime::currentTime().toString("hh-mm-ss");
//            QString current_path=QString("").append(today).append("/").append(current_time).append("-").append(QString::number(i)).append(".dat");
//            QFile file(current_path);
//            if(isJixu == true){
//                file.open(QIODevice::WriteOnly);
//                QDataStream out(&file);
//                out<<objs.at(i);
//                file.close();
//            }
//            current_time.clear();
//            current_path.clear();
//        }

//        vector<MyObjectTrack> tracks = in.getTracks();

        int num_objs = objs.size();
        for (int i = 0; i < num_objs;i++)
        {
            //画对象的box
            MyObject obj = objs[i];
            Rect rect2 = Rect(obj.getRect().x+mainPano.cols, obj.getRect().y, obj.getRect().width, obj.getRect().height);
            rectangle(mat,obj.getRect(),obj.getColor(),2,1,0);
            rectangle(mat,rect2,obj.getColor(),2,1,0);
            // cv::cvtColor(mat, mat, CV_BGR2RGB);


            //画对象中心点的位置
            if(isMubiao){
                int x = (int)(this->getDirectionX(obj.getCenPoint().x, mainPano));
                int y = (int)(10-this->getDirectionY(obj.getCenPoint().y, mainPano)/2);//(10-10*(this->getDirectionY(obj.getCenPoint().y)-this->getDirectionY())/(this->getDirectionY2()-this->getDirectionY()));//endh - i*(endh-starth)/10
                QString tx = QString::number(x,10);
                QString ty = QString::number(y,10);
                QString tstr = "x="+tx+",y="+ty;
                string str = tstr.toStdString();
                QString idstr = "id="+QString::number(obj.getID(),10);
                string idst = idstr.toStdString();
                //qDebug()<<tstr;
                Point p = Point(obj.getRect().x+obj.getRect().width,obj.getRect().y+obj.getRect().height);
                Point p2 = Point(obj.getRect().x+obj.getRect().width+mainPano.cols,obj.getRect().y+obj.getRect().height);

                putText(mat,str,p,3,0.5,obj.getColor());
                putText(mat,str,p2,3,0.5,obj.getColor());

                Point p3 = Point(obj.getRect().x+obj.getRect().width,obj.getRect().y+obj.getRect().height/3);
                Point p4 = Point(obj.getRect().x+obj.getRect().width+mainPano.cols,obj.getRect().y+obj.getRect().height/3);

                putText(mat,idst,p3,3,0.5,obj.getColor());
                putText(mat,idst,p4,3,0.5,obj.getColor());
            }
            // cv::cvtColor(mat, mat, CV_BGR2RGB);
        }
        // cv::cvtColor(mat, mat, CV_BGR2RGB);

        //画告警区域
        for(int iii = 0; iii < this->rgs.size(); iii++){
            RegionGroup rg = rgs[iii];
            rg.draw(mat);
        }

        //画矩形
        if(this->widget1->isTo3){
            //qDebug()<<"w1 rect3: x="<<this->widget1->rectan3.x<<",y="<<this->widget1->rectan3.y<<",width="<<this->widget1->rectan3.width<<",height="<<this->widget1->rectan3.height;
            rectangle(mat,this->widget1->rectan3,this->widget3->getColor(),4,1,0);
            Rect rect2 = Rect(this->widget1->rectan3.x+mainPano.cols, this->widget1->rectan3.y, this->widget1->rectan3.width, this->widget1->rectan3.height);
            rectangle(mat,rect2,this->widget3->getColor(),4,1,0);
        }
        if(this->widget1->isTo4){
            rectangle(mat,this->widget1->rectan4,this->widget4->getColor(),4,1,0);
            Rect rect2 = Rect(this->widget1->rectan4.x+mainPano.cols, this->widget1->rectan4.y, this->widget1->rectan4.width, this->widget1->rectan4.height);
            rectangle(mat,rect2,this->widget4->getColor(),4,1,0);
        }
        if(this->widget1->isTo6){
            rectangle(mat,this->widget1->rectan6,this->widget6->getColor(),4,1,0);
            Rect rect2 = Rect(this->widget1->rectan6.x+mainPano.cols, this->widget1->rectan6.y, this->widget1->rectan6.width, this->widget1->rectan6.height);
            rectangle(mat,rect2,this->widget6->getColor(),4,1,0);
        }
        if(this->widget2->isTo3){
            rectangle(mat,this->widget2->getQRectan3(),this->widget3->getColor(),4,1,0);
            Rect rect2 = Rect(this->widget2->getQRectan3().x+mainPano.cols, this->widget2->getQRectan3().y, this->widget2->getQRectan3().width, this->widget2->getQRectan3().height);
            rectangle(mat,rect2,this->widget3->getColor(),4,1,0);
        }
        if(this->widget2->isTo4){
            rectangle(mat,this->widget2->getQRectan4(),this->widget4->getColor(),4,1,0);
            Rect rect2 = Rect(this->widget2->getQRectan4().x+mainPano.cols, this->widget2->getQRectan4().y, this->widget2->getQRectan4().width, this->widget2->getQRectan4().height);
            rectangle(mat,rect2,this->widget4->getColor(),4,1,0);
        }
        if(this->widget2->isTo6){
            rectangle(mat,this->widget2->getQRectan6(),this->widget6->getColor(),4,1,0);
            Rect rect2 = Rect(this->widget2->getQRectan6().x+mainPano.cols, this->widget2->getQRectan6().y, this->widget2->getQRectan6().width, this->widget2->getQRectan6().height);
            rectangle(mat,rect2,this->widget6->getColor(),4,1,0);
        }
        //然后劈成2半

        //    Size dsize ;
        //    double scale = 1;
        //    dsize = Size(mat.cols*scale,mat.rows*scale);
        //    Mat image11 = Mat(dsize,CV_32S);
        //    cv::resize(mat, image11,dsize);

        //    QImage img = QImage((const unsigned char*)(image11.data),image11.cols,image11.rows, image11.cols*image11.channels(),  QImage::Format_RGB888);
        //    QImage aa=(&img)->copy(QRect(0,0,mat.cols/2,mat.rows));
        //    Mat image4 = CVUtil::QImageToMat(aa);
        //    Mat image44 = Mat(dsize,CV_32S);
        //    cv::resize(image4, image44,dsize);

        //    //全景2Mat
        //    QImage aa2=(&img)->copy(QRect(mat.cols/2,0,mat.cols/2,mat.rows));
        //    Mat image5 = CVUtil::QImageToMat(aa2);
        //    Mat image55 = Mat(dsize,CV_32S);
        //    cv::resize(image5, image55,dsize);



        Mat mat1, mat2;
        mat(Rect(mat.cols/2,0,mat.cols/4,mat.rows)).copyTo(mat1);
        mat(Rect(mat.cols/4,0,mat.cols/4,mat.rows)).copyTo(mat2);

        Mat newpano;

        hconcat(mat1,mat2,newpano);


        widget1->setMat(mat1);
        widget1->setPano(newpano);
        widget1->setTwoPano(mat);
        widget1->setObjects(objs);
//        widget1->setTracks(in.getTracks());
        widget1->draw();
        //图片2
        widget2->setPano(newpano);
        widget2->setMat(mat2);
        widget2->setTwoPano(mat);
        widget2->setObjects(objs);
//        widget2->setTracks(in.getTracks());
        widget2->draw();
        //qDebug()<<s2;
        //drawUiLabel(mat2,2);
        //图片3
        //Mat mat3 =imread(imageurl);
        widget3->setPano(newpano);
        widget3->setTwoPanos(mat);
        widget3->setAllObjects(objs);
        widget3->draw();
        //drawUiLabelByCopy(mat3,3);
        //图片4
        //Mat mat4 =imread(imageurl2);
        //drawUiLabelByCopy(mat4,4);
        widget4->setPano(newpano);
        widget4->setTwoPanos(mat);
        widget4->setAllObjects(objs);
        widget4->draw();
        //图片5
        QString imageurl5="./0.png";//in.getHD();
        Mat mat5 =imread(imageurl5.toStdString());
        widget5->setMat(mat5);
        widget5->setPano(mainPano);
        widget5->setObjects(objs);
        widget5->draw();
        //图片6
        //        QString imageurl6= in.getLD();
        //        Mat mat6 =imread(imageurl6.toStdString());
        //        widget6->setMat(mat6);
        //        widget6->setPano(pano);
        //        widget6->setObjects(objs);
        //        widget6->draw();
        widget6->setPano(newpano);
        widget6->setTwoPanos(mat);
        widget6->setAllObjects(objs);
        widget6->draw();
        //this->alertProcessing(objs);
        //7雷达图
//                QString imageurl7= "./0.png";
//                Mat mat7 =imread(imageurl7.toStdString());
//                widget7->setMat(mat7);
//                //widget7->setPano(mainPano);
//                widget7->setObjects(objs);
//                widget7->draw();
//    }
//    else{
//        QMessageBox::information(this,tr("接口返回值"),QString::number(v,10));
//        this->selfProcessing();

//    }
}

//自定义接口处理函数，将来被金老师SDK替换------------------------------
void MainWindow::selfProcessing(){
//    //QDir *todayDir=new QDir();
//    QString huiFile = QString("./回放");
//    QString today=QString("./回放/")+QDate::currentDate().toString("yyyy-MM-dd");
//    bool exist = directory->exists(huiFile);
//    if(!exist){
//        directory->mkdir(huiFile);
//    }
//    exist=directory->exists(today);
//    if(!exist){
//        directory->mkdir(today);
//    }


//    in.getIntegratedData2();
//    qDebug()<<"selfpocessing1";
//    vector<MyObject> objs;// = in.getObjs2();
//    num_objs =objs.size();
//    // num_objs =0;
//    for(int i=0;i<objs.size();i++){
//        QString current_time=QTime::currentTime().toString("hh-mm-ss");
//        QString current_path=QString("").append(today).append("/").append(current_time).append("-").append(QString::number(i)).append(".dat");
//        QFile file(current_path);
//        if(isJixu == true){
//            file.open(QIODevice::WriteOnly);
//            QDataStream out(&file);
//            out<<objs.at(i);
//            file.close();
//        }
//        current_time.clear();
//        current_path.clear();
//    }

//     qDebug()<<"selfpocessing3";
//    //    for(int i = 0; i < objs.size(); i++){
//    //        MyObject obj = objs[i];
//    //        qDebug()<<i;
//    //        qDebug()<<obj.getID();
//    //        qDebug()<<obj.getCenPoint().x;
//    //        qDebug()<<obj.getCenPoint().y;
//    //        qDebug()<<obj.getRect().x;
//    //        qDebug()<<obj.getRect().y;
//    //        qDebug()<<obj.getRect().width;
//    //        qDebug()<<obj.getRect().height;
//    //    }

//    //图片1
//    //图片1
//    //    QString s1=in.getQJ1();
//    //    imageurl=s1.toStdString();
//    //    Mat mat1 =imread(imageurl);

//    //在两个全景上画矩形，文字，轨迹等
//    Mat pano = in.getPano();
//    qDebug()<<"selfpocessing6";
//    Mat pano1 = pano.clone();
//    Mat pano2 = pano.clone();

//    Mat mat;
//     qDebug()<<"selfpocessing8";
//    hconcat(pano1,pano2,mat);
//     qDebug()<<"selfpocessing7";
//    //在全景上画矩形，文字，轨迹等
//    //vector<MyObject> objs = in.getObjs();
//    vector<MyObjectTrack> tracks = in.getTracks();
//    qDebug()<<num_objs;
//    for (int i = 0; i < num_objs;i++)
//    {
//        //画对象的box
//        MyObject obj = objs[i];
//        Rect rect2 = Rect(obj.getRect().x+pano.cols, obj.getRect().y, obj.getRect().width, obj.getRect().height);
//        rectangle(mat,obj.getRect(),obj.getColor(),2,1,0);
//        rectangle(mat,rect2,obj.getColor(),2,1,0);
//        // cv::cvtColor(mat, mat, CV_BGR2RGB);

//        //画轨迹
//        if(isMubiao){
//            for(int ii = 0; ii < tracks.size(); ii++){
//                MyObjectTrack track = tracks[ii];
//                int id = track.getId();
//                vector<Point> points = track.getTrack();
//                if(id == obj.getID()){
//                    for(int iii = 0; iii < points.size(); iii++){
//                        Point point = points[iii];
//                        Point point2 = Point(point.x+pano.cols, point.y);
//                        circle(mat, point, 2, obj.getColor(),-1,8,0);//在图像中画出特征点，2是圆的半径
//                        circle(mat, point2, 2, obj.getColor(),-1,8,0);//在图像中画出特征点，2是圆的半径
//                        if(iii >= 1){
//                            Point point3 = points[iii-1];
//                            Point point4 = Point(point3.x+pano.cols, point3.y);
//                            line(mat,point,point3,obj.getColor(),1,8,0);
//                            line(mat,point2,point4,obj.getColor(),1,8,0);
//                        }
//                        // cv::cvtColor(mat, mat, CV_BGR2RGB);
//                    }
//                }
//            }
//        }
//         qDebug()<<"selfpocessing4";
//        //画对象中心点的位置
//        if(isMubiao){
//            int x = (int)(this->getDirectionX(obj.getCenPoint().x, pano));
//            int y = (int)(10-this->getDirectionY(obj.getCenPoint().y, pano)/2);//(10-10*(this->getDirectionY(obj.getCenPoint().y)-this->getDirectionY())/(this->getDirectionY2()-this->getDirectionY()));//endh - i*(endh-starth)/10
//            QString tx = QString::number(x,10);
//            QString ty = QString::number(y,10);
//            QString tstr = "x="+tx+",y="+ty;
//            string str = tstr.toStdString();
//            QString idstr = "id="+QString::number(obj.getID(),10);
//            string idst = idstr.toStdString();
//            //qDebug()<<tstr;
//            Point p = Point(obj.getRect().x+obj.getRect().width,obj.getRect().y+obj.getRect().height);
//            Point p2 = Point(obj.getRect().x+obj.getRect().width+pano.cols,obj.getRect().y+obj.getRect().height);

//            putText(mat,str,p,3,0.5,obj.getColor());
//            putText(mat,str,p2,3,0.5,obj.getColor());

//            Point p3 = Point(obj.getRect().x+obj.getRect().width,obj.getRect().y+obj.getRect().height/3);
//            Point p4 = Point(obj.getRect().x+obj.getRect().width+pano.cols,obj.getRect().y+obj.getRect().height/3);

//            putText(mat,idst,p3,3,0.5,obj.getColor());
//            putText(mat,idst,p4,3,0.5,obj.getColor());
//        }
//        // cv::cvtColor(mat, mat, CV_BGR2RGB);
//    }
//    //cv::cvtColor(mat, mat, CV_BGR2RGB);
//    //画告警区域
//    for(int iii = 0; iii < this->rgs.size(); iii++){
//        RegionGroup rg = rgs[iii];
//        rg.draw(mat);
//    }
//    qDebug()<<"selfpocessing2";
//    //画矩形
//    if(this->widget1->isTo3){
//        //qDebug()<<"w1 rect3: x="<<this->widget1->rectan3.x<<",y="<<this->widget1->rectan3.y<<",width="<<this->widget1->rectan3.width<<",height="<<this->widget1->rectan3.height;
//        rectangle(mat,this->widget1->rectan3,this->widget3->getColor(),4,1,0);
//        Rect rect2 = Rect(this->widget1->rectan3.x+pano.cols, this->widget1->rectan3.y, this->widget1->rectan3.width, this->widget1->rectan3.height);
//        rectangle(mat,rect2,this->widget3->getColor(),4,1,0);
//    }
//    if(this->widget1->isTo4){
//        rectangle(mat,this->widget1->rectan4,this->widget4->getColor(),4,1,0);
//        Rect rect2 = Rect(this->widget1->rectan4.x+pano.cols, this->widget1->rectan4.y, this->widget1->rectan4.width, this->widget1->rectan4.height);
//        rectangle(mat,rect2,this->widget4->getColor(),4,1,0);
//    }
//    if(this->widget1->isTo6){
//        rectangle(mat,this->widget1->rectan6,this->widget6->getColor(),4,1,0);
//        Rect rect2 = Rect(this->widget1->rectan6.x+pano.cols, this->widget1->rectan6.y, this->widget1->rectan6.width, this->widget1->rectan6.height);
//        rectangle(mat,rect2,this->widget6->getColor(),4,1,0);
//    }
//    if(this->widget2->isTo3){
//        rectangle(mat,this->widget2->getQRectan3(),this->widget3->getColor(),4,1,0);
//        Rect rect2 = Rect(this->widget2->getQRectan3().x+pano.cols, this->widget2->getQRectan3().y, this->widget2->getQRectan3().width, this->widget2->getQRectan3().height);
//        rectangle(mat,rect2,this->widget3->getColor(),4,1,0);
//    }
//    if(this->widget2->isTo4){
//        rectangle(mat,this->widget2->getQRectan4(),this->widget4->getColor(),4,1,0);
//        Rect rect2 = Rect(this->widget2->getQRectan4().x+pano.cols, this->widget2->getQRectan4().y, this->widget2->getQRectan4().width, this->widget2->getQRectan4().height);
//        rectangle(mat,rect2,this->widget4->getColor(),4,1,0);
//    }
//    if(this->widget2->isTo6){
//        rectangle(mat,this->widget2->getQRectan6(),this->widget6->getColor(),4,1,0);
//        Rect rect2 = Rect(this->widget2->getQRectan6().x+pano.cols, this->widget2->getQRectan6().y, this->widget2->getQRectan6().width, this->widget2->getQRectan6().height);
//        rectangle(mat,rect2,this->widget6->getColor(),4,1,0);
//    }
//    //然后劈成2半

//    //    Size dsize ;
//    //    double scale = 1;
//    //    dsize = Size(mat.cols*scale,mat.rows*scale);
//    //    Mat image11 = Mat(dsize,CV_32S);
//    //    cv::resize(mat, image11,dsize);

//    //    QImage img = QImage((const unsigned char*)(image11.data),image11.cols,image11.rows, image11.cols*image11.channels(),  QImage::Format_RGB888);
//    //    QImage aa=(&img)->copy(QRect(0,0,mat.cols/2,mat.rows));
//    //    Mat image4 = CVUtil::QImageToMat(aa);
//    //    Mat image44 = Mat(dsize,CV_32S);
//    //    cv::resize(image4, image44,dsize);

//    //    //全景2Mat
//    //    QImage aa2=(&img)->copy(QRect(mat.cols/2,0,mat.cols/2,mat.rows));
//    //    Mat image5 = CVUtil::QImageToMat(aa2);
//    //    Mat image55 = Mat(dsize,CV_32S);
//    //    cv::resize(image5, image55,dsize);
//     qDebug()<<"selfpocessing999";
//    if(this->isPseudo==true)
//        mat=setPseudocolor(mat);
//    updateBright(mat);
//    updateContrast(mat);

//    Mat mat1, mat2;
//    mat(Rect(mat.cols/2,0,mat.cols/4,mat.rows)).copyTo(mat1);
//    mat(Rect(mat.cols/4,0,mat.cols/4,mat.rows)).copyTo(mat2);

//    Mat newpano;

//    hconcat(mat1,mat2,newpano);
//    //Mat mat1 = image44;
//    //    if(this->isPseudo==true)
//    //        mat1=setPseudocolor(mat1);
//    //    updateBright(mat1);
//    //    updateContrast(mat1);
//    //        if(saturation1!=100){
//    //               hsl->channels[color].saturation1 = saturation1 - 100;
//    //               hsl->adjust(mat1, mat1);
//    //           }
//    widget1->setMat(mat1);
//    widget1->setPano(newpano);
//    widget1->setTwoPano(mat);
//    widget1->setObjects(objs);
//    widget1->setTracks(in.getTracks());
//    widget1->draw();
//    //qDebug()<<s1;
//    //图片2
//    //图片1
//    //    QString s1=in.getQJ1();
//    //    imageurl=s1.toStdString();
//    //    Mat mat1 =imread(imageurl);

//    //Mat mat2 = image55;
//    if(this->isPseudo==true)
//        mat2=setPseudocolor(mat2);
//    updateBright(mat2);
//    updateContrast(mat2);
//    //        if(saturation1!=100){
//    //               hsl->channels[color].saturation1 = saturation1 - 100;
//    //               hsl->adjust(mat2, mat2);
//    //           }
//    widget2->setPano(newpano);
//    //    if(this->isPseudo==true)
//    //        mat2=setPseudocolor(mat2);
//    //    updateBright(mat2);
//    //    updateContrast(mat2);
//    //        if(saturation1!=100){
//    //               hsl->channels[color].saturation1 = saturation1 - 100;
//    //               hsl->adjust(mat2, mat2);
//    //           }
//    //widget2->setPano(mat);
//    widget2->setMat(mat2);
//    widget2->setTwoPano(mat);
//    widget2->setObjects(objs);
//    widget2->setTracks(in.getTracks());
//    widget2->draw();
//    //qDebug()<<s2;
//    //drawUiLabel(mat2,2);
//    //图片3
//    //Mat mat3 =imread(imageurl);

//    widget3->setPano(newpano);
//    widget3->setTwoPanos(mat);
//    widget3->setAllObjects(in.getObjs());
//    widget3->draw();
//    //drawUiLabelByCopy(mat3,3);
//    //图片4
//    //Mat mat4 =imread(imageurl2);
//    //drawUiLabelByCopy(mat4,4);
//    widget4->setPano(newpano);
//    widget4->setTwoPanos(mat);
//    widget4->setAllObjects(in.getObjs());
//    widget4->draw();
//    //图片5
//    widget5->setPano(pano);
//    QString imageurl5=in.getHD();
//    Mat mat5 =imread(imageurl5.toStdString());
//    widget5->setMat(mat5);
//    widget5->setObjects(objs);
//    widget5->draw();
//    //图片6
//    //    QString imageurl6= in.getLD();
//    //    Mat mat6 =imread(imageurl6.toStdString());
//    //    widget6->setMat(mat6);
//    //    widget6->setPano(pano);
//    //    widget6->setObjects(objs);
//    //    widget6->draw();
//    widget6->setPano(newpano);
//    widget6->setTwoPanos(mat);
//    widget6->setAllObjects(in.getObjs());
//    widget6->draw();
//    this->alertProcessing(objs);
//    qDebug()<<"selfpocessing";
}
//----------------------------------------------------------

//临时性处理函数，将来被金老师SDK替换------------------------------
void MainWindow::tempProcessing(){
    index=0;//用于计算标尺的起始位置
    index1=0;//用于取第一栏的图片
    index2=0;//用于取第二栏的图片

    //图片1
    string imageurl="./s1/1.bmp";
    Mat mat1 =imread(imageurl);
    widget1->setMat(mat1);
    drawUiLabel(mat1,1);

    //图片2
    string imageurl2 = "./s2/1.bmp";
    Mat mat2 =imread(imageurl2);
    widget2->setMat(mat2);
    drawUiLabel(mat2,2);
    //图片3
    Mat mat3 =imread(imageurl);
    drawUiLabelByCopy(mat3,3);
    //图片4
    Mat mat4 =imread(imageurl2);
    drawUiLabelByCopy(mat4,4);
    //图片5
    string imageurl5="./0.png";//第五个图片的
    Mat mat5 =imread(imageurl5);

    drawUiLabel(mat5,5);
    //图片6
    string imageurl6= "./0.png";//第五个图片的
    Mat mat6 =imread(imageurl6);

    drawUiLabel(mat6,6);

    imageurl="./s1/1.bmp";
    imageurl2="./s2/1.bmp";

    //存储第一栏
    filename1 = "./s1/1.bmp";
    filename2 = "./s1/2.bmp";
    filename3 = "./s1/3.bmp";
    filename4 = "./s1/4.bmp";
    //存储第二栏
    filename5 = "./s2/1.bmp";
    filename6 = "./s2/2.bmp";
    filename7 = "./s2/3.bmp";
    filename8 = "./s2/4.bmp";
    //将第一栏存储在vector中
    vc1.push_back(filename1);
    vc1.push_back(filename2);
    vc1.push_back(filename3);
    vc1.push_back(filename4);
    //将第二栏存储在vector中
    vc2.push_back(filename5);
    vc2.push_back(filename6);
    vc2.push_back(filename7);
    vc2.push_back(filename8);
}

//----------------------------------------------------------

void MainWindow::addMyMenuBar(){
    menubar = new QMenuBar(this);

    FileMenu = new QMenu("文件");
    OptionMenu = new QMenu("选项");
    ToolMenu = new QMenu("工具");
    DisplayMenu = new QMenu("显示");
    HelpMenu = new QMenu("帮助");

    connection = new QAction("单播连接",this);
    connectionplus = new QAction("多播连接",this);
    disconnection = new QAction("断开连接",this);
    openplus = new QAction("打开回放",this);
    backplus = new QAction("回放",this);
    closeaction = new QAction("退出回放",this);
    //recentvidio = new QAction("最近视频",this);
    recentvidio = new QMenu("最近视频");//recent 有单独的子菜单，所以定义成menu
    changeuser = new QAction("切换用户",this);
    installation = new QAction("启动安装向导",this);
    exit = new QAction("退出",this);

    installation->setEnabled(false);

    //增加热键
    changeuser->setShortcut(Qt::Key_F11);
    connection->setShortcut(Qt::CTRL+Qt::Key_D);

    for(int j=0;j<6;j++){//recent
        videoAction[j]=new QAction("",this);
        videoAction[j]->setVisible(false);
        videoAction[j]->setData(j);//在槽函数里获取发出信号的对象，取出data，看是第几个
        connect(videoAction[j],SIGNAL(triggered()),this,SLOT(videoClick()));
        recentvidio->addAction(videoAction[j]);
    }

    FileMenu->addAction(connection);
    FileMenu->addAction(connectionplus);
    FileMenu->addAction(disconnection);
    if(!backwindow){
        FileMenu->addAction(openplus);
    }
    //FileMenu->addAction(backplus);
    FileMenu->addMenu(recentvidio);
    FileMenu->addAction(changeuser);
    FileMenu->addAction(installation);
    if(!backwindow){
        FileMenu->addAction(exit);
    }
    if(backwindow){
        FileMenu->addAction(closeaction);
    }

    connect(connection,SIGNAL(triggered()),this,SLOT(connectionClicked()));
    connect(connectionplus,SIGNAL(triggered()),this,SLOT(connectionplusClicked()));
    connect(disconnection,SIGNAL(triggered()),this,SLOT(disconnectionClicked()));
    connect(openplus,SIGNAL(triggered()),this,SLOT(openplusClicked()));
    connect(backplus,SIGNAL(triggered()),this,SLOT(backplusClicked()));
    connect(closeaction,SIGNAL(triggered()),this,SLOT(closeClicked()));
    //connect(recentvidio,SIGNAL(triggered()),this,SLOT(recentvidioClicked())); recent
    connect(changeuser,SIGNAL(triggered()),this,SLOT(changeuserClicked()));
    connect(installation,SIGNAL(triggered()),this,SLOT(installationClicked()));
    connect(exit,SIGNAL(triggered()),this,SLOT(exitClicked()));

    configuration = new QAction("配置...",this);
    saveconfiguration = new QAction("保存当前设置",this);
    region = new QAction("创建或编辑区域",this);

    region->setShortcut(Qt::Key_F12);

    OptionMenu->addAction(configuration);
    OptionMenu->addAction(saveconfiguration);
    OptionMenu->addAction(region);


    connect(configuration,SIGNAL(triggered()),this,SLOT(configurationClicked()));
    connect(saveconfiguration,SIGNAL(triggered()),this,SLOT(saveconfigurationClicked()));
    connect(region,SIGNAL(triggered()),this,SLOT(regionClicked()));


    figure = new QAction("屏幕截图",this);
    figure->setShortcut(Qt::Key_F7);
    ToolMenu->addAction(figure);
    connect(figure,SIGNAL(triggered()),this,SLOT(figureClicked()));


    openalert = new QAction("显示报警信息",this);
    closealert = new QAction("关闭报警信息",this);
//    targetAtt = new QAction("目标属性列表",this);

    openalert->setShortcut(Qt::Key_F3);
    closealert->setShortcut(Qt::Key_F9);

    DisplayMenu->addAction(openalert);
    DisplayMenu->addAction(closealert);
//    DisplayMenu->addAction(targetAtt);

    connect(openalert,SIGNAL(triggered()),this,SLOT(openalertClicked()));
    connect(closealert,SIGNAL(triggered()),this,SLOT(closealertClicked()));
//    connect(targetAtt,SIGNAL(triggered()),this,SLOT(targetAttShow()));


    help = new QAction("帮助",this);
    about = new QAction("关于",this);

    HelpMenu->addAction(help);
    HelpMenu->addAction(about);

    connect(help,SIGNAL(triggered()),this,SLOT(helpClicked()));
    connect(about,SIGNAL(triggered()),this,SLOT(aboutClicked()));

    menubar->addMenu(FileMenu);
    menubar->addMenu(OptionMenu);
    menubar->addMenu(ToolMenu);
    menubar->addMenu(DisplayMenu);
    menubar->addMenu(HelpMenu);

}


//绘制工具栏
void MainWindow::addMyToolBar()
{

    //    //图标太大导致在小屏幕上显示不全，改为按照屏幕宽度自动调整图标的大小
    QDesktopWidget* desktopWidget = QApplication::desktop();
    QRect screenRect = desktopWidget->screenGeometry();  //屏幕区域
    int screenWidth=screenRect.width();
    const int buttonSize=(screenWidth*0.7)/28;

    QGroupBox* group0=new QGroupBox(this);
    QGroupBox* group1=new QGroupBox(this);
    QGroupBox* group2=new QGroupBox(this);
    QGroupBox *group3=new QGroupBox(this);
    QGroupBox *group4=new QGroupBox(this);
    //QGroupBox* group5=new QGroupBox(this);
    QGroupBox *group6=new QGroupBox(this);
    QGroupBox *group7=new QGroupBox(this);
    QGroupBox *group8=new QGroupBox(this);

    QHBoxLayout *vbox0 = new QHBoxLayout;
    QHBoxLayout *vbox1 = new QHBoxLayout;
    QHBoxLayout *vbox2 = new QHBoxLayout;
    QHBoxLayout *vbox3 = new QHBoxLayout;
    QHBoxLayout *vbox4 = new QHBoxLayout;
    //QHBoxLayout *vbox5 = new QHBoxLayout;
    QHBoxLayout *vbox6 = new QHBoxLayout;
    QHBoxLayout *vbox7 = new QHBoxLayout;
    QHBoxLayout *vbox8 = new QHBoxLayout;


    mainToolBar = addToolBar("monitoring");

    //加图标
    //mainToolBar->addWidget(new QLabel(""));
    //    QPixmap pixmap3("./icon/fujirui.png");
    //    //QPixmap fitpixmap3=pixmap3.scaled(buttonSize*1.7,buttonSize*1.7, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    //    QLabel *tuBiao=new QLabel(this);
    //    tuBiao->setPixmap(pixmap3);
    //    mainToolBar->addWidget(tuBiao);
    //    mainToolBar->addWidget(new QLabel(" "));
    //第一组按钮：监控和后退，还有回放
    //启动/停止

    //    startStop = new QToolButton(this);
    //    startStop->setToolTip(tr("停止"));
    //    //startStop->setMinimumHeight(buttonSize);
    //    //startStop->setMaximumHeight(buttonSize);
    //    //startStop->setMinimumWidth(buttonSize);
    //    //startStop->setMaximumWidth(buttonSize);
    //    //startStop->setStyleSheet("border-style:flat;background-color:2E302D");
    //    startStopSet="./icon/1_1.png";
    //    startStop->setIcon(QPixmap(startStopSet));
    //    //startStop->setIconSize(QSize(buttonSize,buttonSize));
    //    vbox1->addWidget(startStop);
    //    connect(startStop,SIGNAL(clicked()),this,SLOT(startStopFunction()));
    //    //vbox1->addWidget(new QLabel(" "));
    //富吉瑞logo
    logo = new QLabel(this);
    QPixmap pixmap0("./iconUpdate/FJR(颜色）.png");
    QPixmap fitpixmap0=pixmap0.scaled(1.4*buttonSize,0.9*buttonSize, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    logo->setPixmap(fitpixmap0);
    vbox0->addWidget(logo);

    vbox0->addWidget(new QLabel("  "));
    vbox0->setMargin(0);
    vbox0->setSpacing(0);

    group0->setLayout(vbox0);
    group0->setStyleSheet("border:0px;background-image:url(./iconUpdate/回放栏-背景-3.png)");
    mainToolBar->addWidget(group0);
    mainToolBar->addSeparator();
    //回放
    backLabel = new QLabel(this);
    QPixmap pixmap4("./iconUpdate/回放.png");
    fitpixmap4=pixmap4.scaled(1.4*buttonSize,0.9*buttonSize, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    backLabel->setPixmap(fitpixmap4);
    vbox1->addWidget(backLabel);

    //暂停/继续
    mstop = new QToolButton(this);
    mstop->setToolTip(tr("记录当前场景"));
    mstop->setMinimumHeight(buttonSize);
    mstop->setMaximumHeight(buttonSize);
    mstop->setMinimumWidth(buttonSize);
    mstop->setMaximumWidth(buttonSize);
    mstop->setStyleSheet("border-style:flat;background-color:2E302D");
    mstopSet="./iconUpdate/录像停.png";
    mstop->setIcon(QPixmap(mstopSet));
    mstop->setIconSize(QSize(buttonSize,buttonSize));
    mstop->setCheckable(true);
    vbox1->addWidget(mstop);
    connect(mstop,SIGNAL(clicked()),this,SLOT(mstopFunction()));
    //vbox1->addWidget(new QLabel(" "));

    //后退
    back = new QToolButton(this);
    back->setToolTip(tr("执行非均匀性校正"));
    back->setMinimumHeight(buttonSize);
    back->setMaximumHeight(buttonSize);
    back->setMinimumWidth(buttonSize);
    back->setMaximumWidth(buttonSize);
    back->setStyleSheet("border-style:flat;background-color:2E302D");
    backSet="./iconUpdate/执行非均匀性矫正.png";
    back->setIcon(QPixmap(backSet));
    back->setIconSize(QSize(buttonSize,buttonSize));
    back->setCheckable(true);
    vbox1->addWidget(back);
    connect(back,SIGNAL(clicked()),this,SLOT(backFunction()));
    //vbox1->addWidget(new QLabel(" "));

    //回放
    open = new QToolButton(this);
    open->setToolTip(tr("显示隐藏时间轴"));
    open->setMinimumHeight(buttonSize);
    open->setMaximumHeight(buttonSize);
    open->setMinimumWidth(buttonSize);
    open->setMaximumWidth(buttonSize);
    open->setStyleSheet("border-style:flat;background-color:2E302D");
    openSet="./iconUpdate/显示隐藏时间轴开.png";
    open->setIcon(QPixmap(openSet));
    open->setIconSize(QSize(buttonSize,buttonSize));
    open->setCheckable(true);
    vbox1->addWidget(open);
    connect(open,SIGNAL(clicked()),this,SLOT(openFunction()));
    \
    vbox1->addWidget(new QLabel("  "));
    vbox1->setMargin(0);
    vbox1->setSpacing(0);
    //vbox1->setContentsMargins(QMargins(0,0,0,0));

    group1->setLayout(vbox1);
    group1->setStyleSheet("border:0px;background-image:url(./iconUpdate/回放栏-背景.png)");


    mainToolBar->addWidget(group1);
    mainToolBar->addSeparator();
    //mainToolBar->addWidget(new QLabel("    "));
    //第二组按钮：图像
    //图像
    photo = new QLabel(this);
    QPixmap pixmap5("./iconUpdate/图像.png");
    fitpixmap5=pixmap5.scaled(1.4*buttonSize,0.9*buttonSize, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    photo->setPixmap(fitpixmap5);
    vbox2->addWidget(photo);

    //撤销手动对比度参数
    chexiao = new QToolButton(this);
    chexiao->setToolTip(tr("撤销手动对比度参数"));
    chexiao->setMinimumHeight(buttonSize);
    chexiao->setMaximumHeight(buttonSize);
    chexiao->setMinimumWidth(buttonSize);
    chexiao->setMaximumWidth(buttonSize);
    chexiao->setStyleSheet("border-style:flat;background-color:2E302D");
    chexiaoDuibidu ="./iconUpdate/撤销手动对比参数.png";
    chexiao->setIcon(QPixmap(chexiaoDuibidu));
    chexiao->setIconSize(QSize(buttonSize,buttonSize));
    chexiao->setCheckable(true);
    vbox2->addWidget(chexiao);
    connect(chexiao,SIGNAL(clicked()),this,SLOT(chexiaoFunction()));

    //自动
    autom = new QToolButton(this);
    autom->setToolTip(tr("应用自动对比度"));
    autom->setMinimumHeight(buttonSize);
    autom->setMaximumHeight(buttonSize);
    autom->setMinimumWidth(buttonSize);
    autom->setMaximumWidth(buttonSize);
    autom->setStyleSheet("border-style:flat;background-color:2E302D");
    automSet="./iconUpdate/应用自动对比度开.png";
    autom->setIcon(QPixmap(automSet));
    autom->setIconSize(QSize(buttonSize,buttonSize));
    autom->setCheckable(true);
    vbox2->addWidget(autom);
    connect(autom,SIGNAL(clicked()),this,SLOT(automFunction()));
    //vbox2->addWidget(new QLabel(" "));

    //降低亮度
    reducebrightness = new QToolButton(this);
    reducebrightness->setToolTip(tr("降低亮度"));
    reducebrightness->setMinimumHeight(buttonSize);
    reducebrightness->setMaximumHeight(buttonSize);
    reducebrightness->setMinimumWidth(buttonSize);
    reducebrightness->setMaximumWidth(buttonSize);
    reducebrightness->setStyleSheet("border-style:flat;background-color:2E302D");
    reduceBrightnessSet="./iconUpdate/亮度减弱.png";
    reducebrightness->setIcon(QPixmap(reduceBrightnessSet));
    reducebrightness->setIconSize(QSize(buttonSize,buttonSize));
    reducebrightness->setCheckable(true);
    vbox2->addWidget(reducebrightness);
    connect(reducebrightness,SIGNAL(clicked()),this,SLOT(reduceBrightnessFunction()));
    //vbox2->addWidget(new QLabel(" "));

    //增加亮度
    addbrightness = new QToolButton(this);
    addbrightness->setToolTip(tr("增加亮度"));
    addbrightness->setMinimumHeight(buttonSize);
    addbrightness->setMaximumHeight(buttonSize);
    addbrightness->setMinimumWidth(buttonSize);
    addbrightness->setMaximumWidth(buttonSize);
    addbrightness->setStyleSheet("border-style:flat;background-color:2E302D");
    addBrightnessSet="./iconUpdate/亮度加强.png";
    addbrightness->setIcon(QPixmap(addBrightnessSet));
    addbrightness->setIconSize(QSize(buttonSize,buttonSize));
    addbrightness->setCheckable(true);
    vbox2->addWidget(addbrightness);
    connect(addbrightness,SIGNAL(clicked()),this,SLOT(addBrightnessFunction()));
    //vbox2->addWidget(new QLabel(" "));




    //降低对比度
    reducesaturation = new QToolButton(this);
    reducesaturation->setToolTip(tr("降低对比度"));
    reducesaturation->setMinimumHeight(buttonSize);
    reducesaturation->setMaximumHeight(buttonSize);
    reducesaturation->setMinimumWidth(buttonSize);
    reducesaturation->setMaximumWidth(buttonSize);
    reducesaturation->setStyleSheet("border-style:flat;background-color:2E302D");
    reduceSaturationSet="./iconUpdate/对比度减弱.png";
    reducesaturation->setIcon(QPixmap(reduceSaturationSet));
    reducesaturation->setIconSize(QSize(buttonSize,buttonSize));
    reducesaturation->setCheckable(true);
    vbox2->addWidget(reducesaturation);
    connect(reducesaturation,SIGNAL(clicked()),this,SLOT(reduceSaturationFunction()));
    //vbox2->addWidget(new QLabel(" "));

    //增加对比度
    addsaturation = new QToolButton(this);
    addsaturation->setToolTip(tr("增加对比度"));
    addsaturation->setMinimumHeight(buttonSize);
    addsaturation->setMaximumHeight(buttonSize);
    addsaturation->setMinimumWidth(buttonSize);
    addsaturation->setMaximumWidth(buttonSize);
    addsaturation->setStyleSheet("border-style:flat;background-color:2E302D");
    addSaturationSet="./iconUpdate/对比度增加.png";
    addsaturation->setIcon(QPixmap(addSaturationSet));
    addsaturation->setIconSize(QSize(buttonSize,buttonSize));
    addsaturation->setCheckable(true);
    vbox2->addWidget(addsaturation);
    connect(addsaturation,SIGNAL(clicked()),this,SLOT(addSaturationFunction()));
    //vbox2->addWidget(new QLabel(" "));


    //伪彩色
    pseudoColor = new QToolButton(this);
    pseudoColor->setToolTip(tr("伪彩色"));
    pseudoColor->setMinimumHeight(buttonSize);
    pseudoColor->setMaximumHeight(buttonSize);
    pseudoColor->setMinimumWidth(buttonSize);
    pseudoColor->setMaximumWidth(buttonSize);
    pseudoColor->setStyleSheet("border-style:flat;background-color:2E302D");
    pseudoColorSet="./iconUpdate/更多色板.png";
    pseudoColor->setIcon(QPixmap(pseudoColorSet));
    pseudoColor->setIconSize(QSize(buttonSize,buttonSize));
    pseudoColor->setCheckable(true);
    vbox2->addWidget(pseudoColor);
    connect(pseudoColor,SIGNAL(clicked()),this,SLOT(pseudoColorFunction()));

    vbox2->addWidget(new QLabel("  "));
    vbox2->setMargin(0);
    vbox2->setSpacing(0);

    group2->setLayout(vbox2);
    group2->setStyleSheet("border:0px;background-image:url(./iconUpdate/回放栏-背景-2.png)");
    mainToolBar->addWidget(group2);
    mainToolBar->addSeparator();

    //站位
    position = new QLabel(this);
    QPixmap pixmap8("./iconUpdate/位置.png");
    fitpixmap8=pixmap8.scaled(1.4*buttonSize,0.9*buttonSize, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    position->setPixmap(fitpixmap8);
    vbox8->addWidget(position);

    zhanweiLabel = new QLabel(this);
    if(zhanweiName!="")
        zhanweiLabel->setText(zhanweiName);
    else{
        zhanwei = "BJ036 战位";
        zhanweiLabel->setText(zhanwei);
    }
    vbox8->addWidget(zhanweiLabel);

    vbox8->addWidget(new QLabel("  "));
    vbox8->setMargin(0);
    vbox8->setSpacing(0);

    group8->setLayout(vbox8);
    group8->setStyleSheet("border:0px;background-image:url(./iconUpdate/回放栏-背景-3.png)");
    mainToolBar->addWidget(group8);
    mainToolBar->addSeparator();

    //时间组
    currentTime = new QLabel(this);
    QPixmap pixmap3("./iconUpdate/当前时间.png");
    fitpixmap3=pixmap3.scaled(1.4*buttonSize,0.9*buttonSize, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    currentTime->setPixmap(fitpixmap3);
    vbox6->addWidget(currentTime);


    systime=new QLabel(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss ddd"));//时间
    systime->setStyleSheet("color:Black");
    vbox6->addWidget(systime);

    vbox6->addWidget(new QLabel("  "));

    vbox6->setMargin(0);
    vbox6->setSpacing(0);
    group6->setLayout(vbox6);
    group6->setStyleSheet("border:0px;background-image:url(./iconUpdate/回放栏-背景-4.png)");
    mainToolBar->addWidget(group6);
    mainToolBar->addSeparator();

    //第三组

    setup = new QLabel(this);
    QPixmap pixmap6("./iconUpdate/设置.png");
    fitpixmap6=pixmap6.scaled(1.4*buttonSize,0.9*buttonSize, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    setup->setPixmap(fitpixmap6);
    vbox3->addWidget(setup);

    //启用垂直稳定图像
    stability = new QToolButton(this);
    stability->setToolTip(tr("启用垂直稳定图像"));
    stability->setMinimumHeight(buttonSize);
    stability->setMaximumHeight(buttonSize);
    stability->setMinimumWidth(buttonSize);
    stability->setMaximumWidth(buttonSize);
    stability->setStyleSheet("border-style:flat;background-color:2E302D");
    stabilityset = "./iconUpdate/启用垂直稳定图像";
    stability->setIcon(QPixmap(stabilityset));
    stability->setIconSize(QSize(buttonSize,buttonSize));
    stability->setCheckable(true);
    vbox3->addWidget(stability);
    connect(stability,SIGNAL(clicked()),this,SLOT(stabilityFunction()));


    //显示点击处的位置信息
    objectAttribute = new QToolButton(this);
    objectAttribute->setToolTip(tr("开启显示点击处的位置信息"));
    objectAttribute->setMinimumHeight(buttonSize);
    objectAttribute->setMaximumHeight(buttonSize);
    objectAttribute->setMinimumWidth(buttonSize);
    objectAttribute->setMaximumWidth(buttonSize);
    objectAttribute->setStyleSheet("border-style:flat;background-color:2E302D");
    objectAttributeSet="./iconUpdate/显示点击处的位置.png";
    objectAttribute->setIcon(QPixmap(objectAttributeSet));
    objectAttribute->setIconSize(QSize(buttonSize,buttonSize));
    objectAttribute->setCheckable(true);
    vbox3->addWidget(objectAttribute);
    connect(objectAttribute,SIGNAL(clicked()),this,SLOT(objectAttributeFunction()));
    //vbox5->addWidget(new QLabel(" "));

    //增加标签
    manual = new QToolButton(this);
    manual->setToolTip(tr("增加标签"));
    manual->setMinimumHeight(buttonSize);
    manual->setMaximumHeight(buttonSize);
    manual->setMinimumWidth(buttonSize);
    manual->setMaximumWidth(buttonSize);
    manual->setStyleSheet("border-style:flat;background-color:2E302D");
    manualSet="./iconUpdate/增加标签.png";
    manual->setIcon(QPixmap(manualSet));
    manual->setIconSize(QSize(buttonSize,buttonSize));
    manual->setCheckable(true);
    vbox3->addWidget(manual);

    vbox3->addWidget(new QLabel("  "));
    vbox3->setMargin(0);
    vbox3->setSpacing(0);
    connect(manual,SIGNAL(clicked()),this,SLOT(manualFunction()));
    //vbox5->addWidget(new QLabel(" "));
    group3->setLayout(vbox3);
    group3->setStyleSheet("border:0px;background-image:url(./iconUpdate/回放栏-背景-5.png)");
    mainToolBar->addWidget(group3);
    mainToolBar->addSeparator();
    //第四组，告警
    //告警

    alarm = new QLabel(this);
    QPixmap pixmap7("./iconUpdate/告警.png");
    fitpixmap7=pixmap7.scaled(1.4*buttonSize,0.9*buttonSize, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    alarm->setPixmap(fitpixmap7);
    vbox4->addWidget(alarm);


    //启动/禁用探测功能
    openClose = new QToolButton(this);
    openClose->setToolTip(tr("禁用探测功能"));
    openClose->setMinimumHeight(buttonSize);
    openClose->setMaximumHeight(buttonSize);
    openClose->setMinimumWidth(buttonSize);
    openClose->setMaximumWidth(buttonSize);
    openClose->setStyleSheet("border-style:flat;background-color:2E302D");
    openCloseSet="./iconUpdate/自动探测.png";
    openClose->setIcon(QPixmap(openCloseSet));
    openClose->setIconSize(QSize(buttonSize,buttonSize));
    openClose->setCheckable(true);
    vbox4->addWidget(openClose);
    connect(openClose,SIGNAL(clicked()),this,SLOT(openCloseFunction()));
    //vbox5->addWidget(new QLabel(" "));

    //调整探测灵敏度等级
    objects = new QToolButton(this);
    objects->setToolTip(tr("调整探测灵敏度等级"));
    objects->setMinimumHeight(buttonSize);
    objects->setMaximumHeight(buttonSize);
    objects->setMinimumWidth(buttonSize);
    objects->setMaximumWidth(buttonSize);
    objects->setStyleSheet("border-style:flat;background-color:2E302D");
    objectSet="./iconUpdate/调整灵敏度等级.png";
    objects->setIcon(QPixmap(objectSet));
    objects->setIconSize(QSize(buttonSize,buttonSize));
    objects->setCheckable(true);



    vbox4->addWidget(objects);
    connect(objects,SIGNAL(clicked()),this,SLOT(objectsFunction()));
    //vbox5->addWidget(new QLabel(" "));

    //关闭声音
    voice = new QToolButton(this);
    voice->setToolTip(tr("关闭声音"));
    voice->setMinimumHeight(buttonSize);
    voice->setMaximumHeight(buttonSize);
    voice->setMinimumWidth(buttonSize);
    voice->setMaximumWidth(buttonSize);
    voice->setStyleSheet("border-style:flat;background-color:2E302D");
    voiceSet="./iconUpdate/告警音开关.png";
    voice->setIcon(QPixmap(voiceSet));
    voice->setIconSize(QSize(buttonSize,buttonSize));
    voice->setCheckable(true);
    vbox4->addWidget(voice);
    connect(voice,SIGNAL(clicked()),this,SLOT(voiceFunction()));


    //mainToolBar->addWidget(new QLabel("   "));

    //告警指示
    //    light = new QToolButton(this);
    //    light->setToolTip(tr("告警指示"));
    //    light->setMinimumHeight(buttonSize);
    //    light->setMaximumHeight(buttonSize);
    //    light->setMinimumWidth(buttonSize);
    //    light->setMaximumWidth(buttonSize);
    //    light->setStyleSheet("border-style:flat;background-color:2E302D");
    //    lightSet="./icon/16_1.png";
    //    light->setIcon(QPixmap(lightSet));
    //    light->setIconSize(QSize(buttonSize,buttonSize));
    //    vbox4->addWidget(light);
    //    connect(light,SIGNAL(clicked()),this,SLOT(lightFunction()));
    //    vbox5->addWidget(new QLabel(" "));

    // 灯
   // QPixmap pixmap1("./iconUpdate/报警灯-红.png");
    QPixmap pixmap2("./iconUpdate/报警灯-绿.png");
    //      fitpixmap1=pixmap1.scaled(buttonSize,buttonSize, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    //      fitpixmap2=pixmap2.scaled(buttonSize,buttonSize, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);

    light = new QToolButton(this);
//    if(isGaojing){
//        light->setIcon(pixmap1);
//    }else
        light->setIcon(pixmap2);
    light->setIconSize(QSize(buttonSize,buttonSize));
    connect(light,SIGNAL(clicked()),this,SLOT(alertInformation()));
    //        lights[0]=new QLabel(this);
    //        lights[1]=new QLabel(this);
    //        lights[2]=new QLabel(this);
    //        lights[3]=new QLabel(this);
    //        lights[4]=new QLabel(this);

    //        num_objs=widget1->objs.size();

    //            if(!isGaojing)
    //            {
    //                lights[0]->setPixmap(fitpixmap2);
    //                lights[1]->setPixmap(fitpixmap2);
    //                lights[2]->setPixmap(fitpixmap2);
    //                lights[3]->setPixmap(fitpixmap2);
    //                lights[4]->setPixmap(fitpixmap2);
    //            }
    //            else
    //            {
    //                if(num_objs==0)
    //                {
    //                    lights[0]->setPixmap(fitpixmap2);
    //                    lights[1]->setPixmap(fitpixmap2);
    //                    lights[2]->setPixmap(fitpixmap2);
    //                    lights[3]->setPixmap(fitpixmap2);
    //                    lights[4]->setPixmap(fitpixmap2);
    //                }
    //                else if(num_objs==1)
    //                {
    //                    lights[0]->setPixmap(fitpixmap1);
    //                    lights[1]->setPixmap(fitpixmap2);
    //                    lights[2]->setPixmap(fitpixmap2);
    //                    lights[3]->setPixmap(fitpixmap2);
    //                    lights[4]->setPixmap(fitpixmap2);
    //                }
    //                else if(num_objs==2)
    //                {
    //                    lights[0]->setPixmap(fitpixmap1);
    //                    lights[1]->setPixmap(fitpixmap1);
    //                    lights[2]->setPixmap(fitpixmap2);
    //                    lights[3]->setPixmap(fitpixmap2);
    //                    lights[4]->setPixmap(fitpixmap2);
    //                }
    //                else if(num_objs==3)
    //                {

    //                    lights[0]->setPixmap(fitpixmap1);
    //                    lights[1]->setPixmap(fitpixmap1);
    //                    lights[2]->setPixmap(fitpixmap1);
    //                    lights[3]->setPixmap(fitpixmap2);
    //                    lights[4]->setPixmap(fitpixmap2);
    //                }
    //                else if(num_objs==4)
    //                {

    //                    lights[0]->setPixmap(fitpixmap1);
    //                    lights[1]->setPixmap(fitpixmap1);
    //                    lights[2]->setPixmap(fitpixmap1);
    //                    lights[3]->setPixmap(fitpixmap1);
    //                    lights[4]->setPixmap(fitpixmap2);
    //                }
    //                else if(num_objs>= 5 )
    //                {
    //                    lights[0]->setPixmap(fitpixmap1);
    //                    lights[1]->setPixmap(fitpixmap1);
    //                    lights[2]->setPixmap(fitpixmap1);
    //                    lights[3]->setPixmap(fitpixmap1);
    //                    lights[4]->setPixmap(fitpixmap1);
    //                }
    //            }

    //            vbox4->addWidget(lights[0]);
    //            vbox4->addWidget(lights[1]);
    //            vbox4->addWidget(lights[2]);
    //            vbox4->addWidget(lights[3]);
    //            vbox4->addWidget(lights[4]);
    vbox4->addWidget(light);

    vbox4->addWidget(new QLabel("  "));
    vbox4->setMargin(0);
    vbox4->setSpacing(0);
    group4->setLayout(vbox4);
    group4->setStyleSheet("border:0px;background-image:url(./iconUpdate/回放栏-背景-6.png)");
    mainToolBar->addWidget(group4);
    mainToolBar->addSeparator();

    //        group5->setLayout(vbox5);
    //        mainToolBar->addWidget(group5);


    //第六组
        exitButton = new QToolButton(this);
        exitButton->setToolTip(tr("退出"));
        exitButton->setMinimumHeight(buttonSize);
        exitButton->setMaximumHeight(buttonSize);
        exitButton->setMinimumWidth(buttonSize);
        exitButton->setMaximumWidth(buttonSize);
        exitButton->setStyleSheet("border-style:flat;background-color:2E302D");
        exitSet="./iconUpdate/退出.png";
        exitButton->setIcon(QPixmap(exitSet));
        exitButton->setIconSize(QSize(buttonSize,buttonSize));
        vbox7->addWidget(exitButton);
        vbox7->addWidget(new QLabel("  "));
        vbox7->setMargin(0);
        vbox7->setSpacing(0);
        connect(exitButton,SIGNAL(clicked()),this,SLOT(exitFunction()));
        group7->setLayout(vbox7);
        group7->setStyleSheet("border:0px;background-image:url(./iconUpdate/回放栏-背景-6.png)");
        mainToolBar->addWidget(group7);
}

//获取系统当前时间定时器
void MainWindow::onTimerOut2(){
    systime->setText(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss ddd"));//时间
}

void MainWindow::updateHWidget(){
    //int v=inThread.getIntegratedData();
    //mainPano = inThread.getPano();
    //vector<MyObject> objs = inThread.getObjs();
    if(!HWidget::isRadar)
        widget5->setPano(mainPano);
    if(HWidget::isRadar){
        QString imageurl5="./0.png";//in.getHD();
        Mat mat5 =imread(imageurl5.toStdString());
        widget5->setMat(mat5);
       // widget5->setPano(mainPano);
    }
    //widget5->setObjects(objs);
    widget5->draw();
}

void MainWindow::adjustment()
{/*
    Mat pano = in.getPano();

    Mat pano1 = pano.clone();
    Mat pano2 = pano.clone();
    Mat mat;
    hconcat(pano1,pano2,mat);
    // Mat mat = in.getPano().clone();

    if(this->isPseudo==true)
        mat=setPseudocolor(mat);
    updateBright(mat);
    updateContrast(mat);

    //cv::cvtColor(mat, mat, CV_BGR2RGB);

    Mat mat1, mat2;
    mat(Rect(mat.cols/2,0,mat.cols/4,mat.rows)).copyTo(mat1);
    mat(Rect(mat.cols/4,0,mat.cols/4,mat.rows)).copyTo(mat2);

    Mat newpano;

    hconcat(mat1,mat2,newpano);

    //    Mat w1 = widget1->getMat();
    //    if(this->isPseudo==true)
    //        mat=setPseudocolor(w1);
    //    updateBright(w1);
    //    updateContrast(w1);
    // widget1->setMat(w1);

    widget1->setMat(mat1);
    //  widget1->setPano(mat);
    widget1->setPano(newpano);
    widget1->setTwoPano(mat);
    //widget1->setObjects(objs);
    widget1->setTracks(in.getTracks());
    widget1->draw();

    //    Mat w2 = widget2->getMat();
    //    if(this->isPseudo==true)
    //        mat=setPseudocolor(w2);
    //    updateBright(w2);
    //    updateContrast(w2);
    //widget2->setMat(w2);

    //widget2->setPano(mat);
    widget2->setMat(mat2);
    widget2->setPano(newpano);
    widget2->setTwoPano(mat);
    //widget2->setObjects(objs);
    widget2->setTracks(in.getTracks());
    widget2->draw();


    widget3->setPano(newpano);
    widget3->setTwoPanos(mat);
    widget3->setAllObjects(widget1->objs);
    widget3->draw();

    widget4->setPano(newpano);
    widget4->setTwoPanos(mat);
    widget4->setAllObjects(widget1->objs);
    widget4->draw();

    widget6->setPano(newpano);
    widget6->setTwoPanos(mat);
    widget6->setAllObjects(widget1->objs);
    widget6->draw();
    */
}

//定时器任务
void MainWindow::onTimerOut()
{
    //std::cout<<"ok1 "<<std::endl;
    //this->selfTimerout();
    this->jinTimerout();
}

//自定义接口定时器
void MainWindow::selfTimerout(){
    /*
    //index=index+1;

    timerFlash->stop();
    //  qDebug()<<QTime::currentTime().toString("hh:mm:ss");
    QString today=QString("./回放/")+QDate::currentDate().toString("yyyy-MM-dd");
     //QDir *todayDir=new QDir();
    bool exist= directory->exists(today);
    if(!exist){
        directory->mkdir(today);
    }

    unitSize = getMemory(QString("./回放/"));
    qDebug()<<"allM:"<<unitSize;

//    if(unitSize>1024){
//        unitSize/=1024;
//        memoryUnit = "K";
//        if(unitSize>1024){
//            unitSize/=1024;
//            memoryUnit = "M";
//            if(unitSize>1024){
//                unitSize/=1024;
//                memoryUnit = "G";
//                if(unitSize>1024){
//                    unitSize/=1024;
//                    memoryUnit = "T";
//                }
//            }
//        }
//    }
//    qDebug()<<"memoryUnit:"<<unitSize<<memoryUnit;

   // while(memoryUnit == "M" && unitSize >50){
        while( unitSize >1024*1024*200){
        qDebug()<<" inremove";
        removeFile(QString("./回放/"));
    }

    in.getIntegratedData2();
    vector<MyObject> objs;// = in.getObjs2();

    //    QDesktopWidget* desktopWidget = QApplication::desktop();
    //    QRect screenRect = desktopWidget->screenGeometry();
    //    const int buttonSize=(screenRect.width()*0.7)/21.6;
    //    QPixmap pixmap1("./icon/16_1.png");
    //    QPixmap pixmap2("./icon/16_2.png");
    //    fitpixmap1=pixmap1.scaled(buttonSize,buttonSize, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    //    fitpixmap2=pixmap2.scaled(buttonSize,buttonSize, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);



    if(isJixu == true){
        for(int i=0;i<objs.size();i++){
            QString current_time=QTime::currentTime().toString("hh-mm-ss");
            QString current_path=QString("").append(today).append("/").append(current_time).append("-").append(QString::number(i)).append(".dat");
            QFile file(current_path);
            file.open(QIODevice::WriteOnly);
            QDataStream out(&file);
            out<<objs.at(i);
            file.close();
            current_time.clear();
            current_path.clear();
        }
    }
    //    for(int i = 0; i < objs.size(); i++){
    //        MyObject obj = objs[i];
    //        qDebug()<<i;
    //        qDebug()<<obj.getID();
    //        qDebug()<<obj.getCenPoint().x;
    //        qDebug()<<obj.getCenPoint().y;
    //        qDebug()<<obj.getRect().x;
    //        qDebug()<<obj.getRect().y;
    //        qDebug()<<obj.getRect().width;
    //        qDebug()<<obj.getRect().height;
    //    }

    //图片1
    //图片1
    //    QString s1=in.getQJ1();
    //    imageurl=s1.toStdString();
    //    Mat mat1 =imread(imageurl);

    //在两个全景上画矩形，文字，轨迹等
    Mat pano = in.getPano();

    if(isJixu == true){
        QString current_time=QTime::currentTime().toString("hh-mm-ss");
        QString current_path=QString("").append(today).append("/").append(current_time).append(".pan");
        QFile file(current_path);
        file.open(QIODevice::WriteOnly);
        QDataStream out(&file);
        if(pano.empty()){
            out<<-1;
        }else{
            out<<1;
            MyObject::writeMat(out,pano);
        }
        file.close();
        current_time.clear();
        current_path.clear();

    }



    Mat pano1 = pano.clone();
    Mat pano2 = pano.clone();
    Mat mat;
    hconcat(pano1,pano2,mat);

    //在全景上画矩形，文字，轨迹等
    //vector<MyObject> objs = in.getObjs();
    vector<MyObjectTrack> tracks = in.getTracks();

    if(this->isPseudo==true)
        mat=setPseudocolor(mat);
    updateBright(mat);
    updateContrast(mat);

//    for (int i = 0; i < objs.size();i++)
//    {
//        //画对象的box
//        MyObject obj = objs[i];
//        Rect rect2 = Rect(obj.getRect().x+pano.cols, obj.getRect().y, obj.getRect().width, obj.getRect().height);
//        rectangle(mat,obj.getRect(),obj.getColor(),2,1,0);
//        rectangle(mat,rect2,obj.getColor(),2,1,0);
//        //cv::cvtColor(mat, mat, CV_BGR2RGB);

//        //画轨迹
//        if(isMubiao){
//            for(int ii = 0; ii < tracks.size(); ii++){
//                MyObjectTrack track = tracks[ii];
//                int id = track.getId();
//                vector<Point> points = track.getTrack();
//                if(id == obj.getID()){
//                    for(int iii = 0; iii < points.size(); iii++){
//                        Point point = points[iii];
//                        Point point2 = Point(point.x+pano.cols, point.y);
//                        circle(mat, point, 2, obj.getColor(),-1,8,0);//在图像中画出特征点，2是圆的半径
//                        circle(mat, point2, 2, obj.getColor(),-1,8,0);//在图像中画出特征点，2是圆的半径
//                        if(iii >= 1){
//                            Point point3 = points[iii-1];
//                            Point point4 = Point(point3.x+pano.cols, point3.y);
//                            line(mat,point,point3,obj.getColor(),1,8,0);
//                            line(mat,point2,point4,obj.getColor(),1,8,0);
//                        }
//                        //cv::cvtColor(mat, mat, CV_BGR2RGB);
//                    }
//                }
//            }
//        }
//        //画对象中心点的位置
//        if(isMubiao){
//            int x = (int)(this->getDirectionX(obj.getCenPoint().x, pano));
//            int y = (int)(10-this->getDirectionY(obj.getCenPoint().y, pano)/2);//(10-10*(this->getDirectionY(obj.getCenPoint().y)-this->getDirectionY())/(this->getDirectionY2()-this->getDirectionY()));//endh - i*(endh-starth)/10
//            QString tx = QString::number(x,10);
//            QString ty = QString::number(y,10);
//            QString tstr = "x="+tx+",y="+ty;
//            string str = tstr.toStdString();
//            QString idstr = "id="+QString::number(obj.getID(),10);
//            string idst = idstr.toStdString();
//            //qDebug()<<tstr;
//            Point p = Point(obj.getRect().x+obj.getRect().width,obj.getRect().y+obj.getRect().height);
//            Point p2 = Point(obj.getRect().x+obj.getRect().width+pano.cols,obj.getRect().y+obj.getRect().height);

//            putText(mat,str,p,3,0.5,obj.getColor());
//            putText(mat,str,p2,3,0.5,obj.getColor());

//            Point p3 = Point(obj.getRect().x+obj.getRect().width,obj.getRect().y+obj.getRect().height/3);
//            Point p4 = Point(obj.getRect().x+obj.getRect().width+pano.cols,obj.getRect().y+obj.getRect().height/3);

//            putText(mat,idst,p3,3,0.5,obj.getColor());
//            putText(mat,idst,p4,3,0.5,obj.getColor());
//        }
//        // cv::cvtColor(mat, mat, CV_BGR2RGB);
//    }
    // cv::cvtColor(mat, mat, CV_BGR2RGB);
    //qDebug()<<"目标个数："<<objs.size();
    //画告警区域
    for(int iii = 0; iii < this->rgs.size(); iii++){
        RegionGroup rg = rgs[iii];
        rg.draw(mat);
        rg.drawLabel(mat);
    }
    //qDebug()<<"widget1,isTo3"<<this->widget1->isTo3;
    //画矩形
    Mat tmat = mat.clone();
   //Mat tmat = mat;
    if(this->widget1->isTo3){
        //qDebug()<<"w1 rect3: x="<<this->widget1->rectan3.x<<",y="<<this->widget1->rectan3.y<<",width="<<this->widget1->rectan3.width<<",height="<<this->widget1->rectan3.height;
        //rectangle(tmat,this->widget1->rectan3,this->widget3->getColor(),4,1,0);
        rectangle(tmat,this->widget3->rect,this->widget3->getColor(),4,1,0);
        Rect rect2 = Rect(this->widget3->rect.x+pano.cols, this->widget3->rect.y, this->widget3->rect.width, this->widget3->rect.height);
        rectangle(tmat,rect2,this->widget3->getColor(),4,1,0);
        //        rectangle(mat,this->widget1->rectan3,this->widget3->getColor(),4,1,0);
        //        Rect rect2 = Rect(this->widget1->rectan3.x+pano.cols, this->widget1->rectan3.y, this->widget1->rectan3.width, this->widget1->rectan3.height);
        //        rectangle(mat,rect2,this->widget3->getColor(),4,1,0);
    }
    if(this->widget1->isTo4){
        rectangle(tmat,this->widget4->rect,this->widget4->getColor(),4,1,0);
        Rect rect2 = Rect(this->widget4->rect.x+pano.cols, this->widget4->rect.y, this->widget4->rect.width, this->widget4->rect.height);
        rectangle(tmat,rect2,this->widget4->getColor(),4,1,0);
//        rectangle(tmat,this->widget1->rectan4,this->widget4->getColor(),4,1,0);
//        Rect rect2 = Rect(this->widget1->rectan4.x+pano.cols, this->widget1->rectan4.y, this->widget1->rectan4.width, this->widget1->rectan4.height);
//        rectangle(tmat,rect2,this->widget4->getColor(),4,1,0);
        //        rectangle(mat,this->widget1->rectan4,this->widget4->getColor(),4,1,0);
        //        Rect rect2 = Rect(this->widget1->rectan4.x+pano.cols, this->widget1->rectan4.y, this->widget1->rectan4.width, this->widget1->rectan4.height);
        //        rectangle(mat,rect2,this->widget4->getColor(),4,1,0);
    }
    if(this->widget1->isTo6){

        //        rectangle(mat,this->widget1->rectan6,this->widget6->getColor(),4,1,0);
        //        Rect rect2 = Rect(this->widget1->rectan6.x+pano.cols, this->widget1->rectan6.y, this->widget1->rectan6.width, this->widget1->rectan6.height);
        //        rectangle(mat,rect2,this->widget6->getColor(),4,1,0);
//        rectangle(tmat,this->widget1->rectan6,this->widget6->getColor(),4,1,0);
//        Rect rect2 = Rect(this->widget1->rectan6.x+pano.cols, this->widget1->rectan6.y, this->widget1->rectan6.width, this->widget1->rectan6.height);
//        rectangle(tmat,rect2,this->widget6->getColor(),4,1,0);
        rectangle(tmat,this->widget6->rect,this->widget6->getColor(),4,1,0);
        Rect rect2 = Rect(this->widget6->rect.x+pano.cols, this->widget6->rect.y, this->widget6->rect.width, this->widget6->rect.height);
        rectangle(tmat,rect2,this->widget6->getColor(),4,1,0);
    }
    if(this->widget2->isTo3){
        //        rectangle(mat,this->widget2->getQRectan3(),this->widget3->getColor(),4,1,0);
        //        Rect rect2 = Rect(this->widget2->getQRectan3().x+pano.cols, this->widget2->getQRectan3().y, this->widget2->getQRectan3().width, this->widget2->getQRectan3().height);
        //        rectangle(mat,rect2,this->widget3->getColor(),4,1,0);
//        rectangle(tmat,this->widget2->getQRectan3(),this->widget3->getColor(),4,1,0);
//        Rect rect2 = Rect(this->widget2->getQRectan3().x+pano.cols, this->widget2->getQRectan3().y, this->widget2->getQRectan3().width, this->widget2->getQRectan3().height);
//        rectangle(tmat,rect2,this->widget3->getColor(),4,1,0);
        rectangle(tmat,this->widget3->rect,this->widget3->getColor(),4,1,0);
        Rect rect2 = Rect(this->widget3->rect.x+pano.cols, this->widget3->rect.y, this->widget3->rect.width, this->widget3->rect.height);
        rectangle(tmat,rect2,this->widget3->getColor(),4,1,0);
    }
    if(this->widget2->isTo4){
        //        rectangle(mat,this->widget2->getQRectan4(),this->widget4->getColor(),4,1,0);
        //        Rect rect2 = Rect(this->widget2->getQRectan4().x+pano.cols, this->widget2->getQRectan4().y, this->widget2->getQRectan4().width, this->widget2->getQRectan4().height);
        //        rectangle(mat,rect2,this->widget4->getColor(),4,1,0);
        rectangle(tmat,this->widget4->rect,this->widget4->getColor(),4,1,0);
        Rect rect2 = Rect(this->widget4->rect.x+pano.cols, this->widget4->rect.y, this->widget4->rect.width, this->widget4->rect.height);
        rectangle(tmat,rect2,this->widget4->getColor(),4,1,0);
    }
    if(this->widget2->isTo6){
        //        rectangle(mat,this->widget2->getQRectan6(),this->widget6->getColor(),4,1,0);
        //        Rect rect2 = Rect(this->widget2->getQRectan6().x+pano.cols, this->widget2->getQRectan6().y, this->widget2->getQRectan6().width, this->widget2->getQRectan6().height);
        //        rectangle(mat,rect2,this->widget6->getColor(),4,1,0);
//        rectangle(tmat,this->widget2->getQRectan6(),this->widget6->getColor(),4,1,0);
//        Rect rect2 = Rect(this->widget2->getQRectan6().x+pano.cols, this->widget2->getQRectan6().y, this->widget2->getQRectan6().width, this->widget2->getQRectan6().height);
//        rectangle(tmat,rect2,this->widget6->getColor(),4,1,0);

        rectangle(tmat,this->widget6->rect,this->widget6->getColor(),4,1,0);
        Rect rect2 = Rect(this->widget6->rect.x+pano.cols, this->widget6->rect.y, this->widget6->rect.width, this->widget6->rect.height);
        rectangle(tmat,rect2,this->widget6->getColor(),4,1,0);
    }
    //然后劈成2半

    //    Size dsize ;
    //    double scale = 1;
    //    dsize = Size(mat.cols*scale,mat.rows*scale);
    //    Mat image11 = Mat(dsize,CV_32S);
    //    cv::resize(mat, image11,dsize);

    //    QImage img = QImage((const unsigned char*)(image11.data),image11.cols,image11.rows, image11.cols*image11.channels(),  QImage::Format_RGB888);
    //    QImage aa=(&img)->copy(QRect(0,0,mat.cols/2,mat.rows));
    //    Mat image4 = CVUtil::QImageToMat(aa);
    //    Mat image44 = Mat(dsize,CV_32S);
    //    cv::resize(image4, image44,dsize);

    //    //全景2Mat
    //    QImage aa2=(&img)->copy(QRect(mat.cols/2,0,mat.cols/2,mat.rows));
    //    Mat image5 = CVUtil::QImageToMat(aa2);
    //    Mat image55 = Mat(dsize,CV_32S);
    //    cv::resize(image5, image55,dsize);

    Mat mat1, mat2;
    mat(Rect(mat.cols/2,0,mat.cols/4,mat.rows)).copyTo(mat1);
    mat(Rect(mat.cols/4,0,mat.cols/4,mat.rows)).copyTo(mat2);

    Mat mat3, mat4;
    tmat(Rect(mat.cols/2,0,mat.cols/4,mat.rows)).copyTo(mat3);
    tmat(Rect(mat.cols/4,0,mat.cols/4,mat.rows)).copyTo(mat4);

    Mat newpano;

    hconcat(mat1,mat2,newpano);

    //Mat mat1 = image44;
    //    if(this->isPseudo==true)
    //        mat1=setPseudocolor(mat1);
    //    updateBright(mat1);
    //    updateContrast(mat1);
    //        if(saturation1!=100){
    //               hsl->channels[color].saturation1 = saturation1 - 100;
    //               hsl->adjust(mat1, mat1);
    //           }
    widget1->setMat(mat3);
    widget1->setPano(newpano);
    widget1->setTwoPano(mat);
    widget1->setObjects(objs);
    widget1->setTracks(in.getTracks());
    widget1->draw();
    //qDebug()<<s1;
    //图片2
    //图片1
    //    QString s1=in.getQJ1();
    //    imageurl=s1.toStdString();
    //    Mat mat1 =imread(imageurl);

    //Mat mat2 = image55;
    //    if(this->isPseudo==true)
    //                        mat2=setPseudocolor(mat2);
    //        updateBright(mat2);
    //        updateContrast(mat2);
    //        if(saturation1!=100){
    //               hsl->channels[color].saturation1 = saturation1 - 100;
    //               hsl->adjust(mat2, mat2);
    //           }
    widget2->setPano(newpano);
    widget2->setTwoPano(mat);
    //widget2->setPano(mat);
    widget2->setMat(mat4);
    widget2->setObjects(objs);
    widget2->setTracks(in.getTracks());
    widget2->draw();
    //qDebug()<<s2;
    //drawUiLabel(mat2,2);
    //图片3
    //Mat mat3 =imread(imageurl);
    widget3->setPano(newpano);
    widget3->setTwoPanos(mat);
    widget3->setAllObjects(in.getObjs2());
    widget3->draw();
    //drawUiLabelByCopy(mat3,3);
    //图片4
    //Mat mat4 =imread(imageurl2);
    //drawUiLabelByCopy(mat4,4);
    widget4->setPano(newpano);
    widget4->setTwoPanos(mat);
    widget4->setAllObjects(in.getObjs2());
    widget4->draw();
    //图片5
    //QString imageurl5=in.getHD();
    //Mat mat5 =imread(imageurl5.toStdString());
    //widget5->setMat(mat5);
    widget5->setPano(newpano);
    widget5->setObjects(objs);
    widget5->draw();
    //drawUiLabel(mat5,5);
    //图片6
    //QString imageurl6= in.getLD();
    //Mat mat6 =imread(imageurl6.toStdString());
    //widget6->setMat(mat6);
    //    widget6->setPano(newpano);
    //    widget6->setObjects(objs);
    //    widget6->draw();
    // qDebug()<<QTime::currentTime().toString("hh:mm:ss");
    widget6->setPano(newpano);
    widget6->setTwoPanos(mat);
    widget6->setAllObjects(in.getObjs2());
    widget6->draw();
    this->alertProcessing(objs);

    // if(isGaojing)
    // {
    //     if(objs.size()>num_objs){
    //         this->sound->play();
    //         newObjCount=objs.size()-num_objs;
    //         timerFlash->start();

    //         num_objs = objs.size();
    //     }
    //     else
    //         num_objs =objs.size();
    // }

    // if(isGaojing)
    // {
    //     if(num_objs==0)
    //     {
    //         lights[0]->setPixmap(fitpixmap2);
    //         lights[1]->setPixmap(fitpixmap2);
    //         lights[2]->setPixmap(fitpixmap2);
    //         lights[3]->setPixmap(fitpixmap2);
    //         lights[4]->setPixmap(fitpixmap2);
    //     }
    //     else if(num_objs==1)
    //     {
    //         lights[0]->setPixmap(fitpixmap1);
    //         lights[1]->setPixmap(fitpixmap2);
    //         lights[2]->setPixmap(fitpixmap2);
    //         lights[3]->setPixmap(fitpixmap2);
    //         lights[4]->setPixmap(fitpixmap2);
    ////            light1->setPixmap(fitpixmap1);
    ////            light2->setPixmap(fitpixmap2);
    ////            light3->setPixmap(fitpixmap2);
    ////            light4->setPixmap(fitpixmap2);
    ////            light5->setPixmap(fitpixmap2);
    //     }
    //     else if(num_objs==2)
    //     {
    //         lights[0]->setPixmap(fitpixmap1);
    //         lights[1]->setPixmap(fitpixmap1);
    //         lights[2]->setPixmap(fitpixmap2);
    //         lights[3]->setPixmap(fitpixmap2);
    //         lights[4]->setPixmap(fitpixmap2);

    ////            light1->setPixmap(fitpixmap1);
    ////            light2->setPixmap(fitpixmap1);
    ////            light3->setPixmap(fitpixmap2);
    ////            light4->setPixmap(fitpixmap2);
    ////            light5->setPixmap(fitpixmap2);
    //     }
    //     else if(num_objs==3)
    //     {
    //         lights[0]->setPixmap(fitpixmap1);
    //         lights[1]->setPixmap(fitpixmap1);
    //         lights[2]->setPixmap(fitpixmap1);
    //         lights[3]->setPixmap(fitpixmap2);
    //         lights[4]->setPixmap(fitpixmap2);
    ////            light1->setPixmap(fitpixmap1);
    ////            light2->setPixmap(fitpixmap1);
    ////            light3->setPixmap(fitpixmap1);
    ////            light4->setPixmap(fitpixmap2);
    ////            light5->setPixmap(fitpixmap2);
    //     }
    //     else if(num_objs==4)
    //     {
    //         lights[0]->setPixmap(fitpixmap1);
    //         lights[1]->setPixmap(fitpixmap1);
    //         lights[2]->setPixmap(fitpixmap1);
    //         lights[3]->setPixmap(fitpixmap1);
    //         lights[4]->setPixmap(fitpixmap2);
    ////            light1->setPixmap(fitpixmap1);
    ////            light2->setPixmap(fitpixmap1);
    ////            light3->setPixmap(fitpixmap1);
    ////            light4->setPixmap(fitpixmap1);
    ////            light5->setPixmap(fitpixmap2);
    //     }
    //     else if(num_objs>= 5 )
    //     {
    //         lights[0]->setPixmap(fitpixmap1);
    //         lights[1]->setPixmap(fitpixmap1);
    //         lights[2]->setPixmap(fitpixmap1);
    //         lights[3]->setPixmap(fitpixmap1);
    //         lights[4]->setPixmap(fitpixmap1);
    ////            light1->setPixmap(fitpixmap1);
    ////            light2->setPixmap(fitpixmap1);
    ////            light3->setPixmap(fitpixmap1);
    ////            light4->setPixmap(fitpixmap1);
    ////            light5->setPixmap(fitpixmap1);
    //   }
    // }
    // else
    // {
    //     lights[0]->setPixmap(fitpixmap2);
    //     lights[1]->setPixmap(fitpixmap2);
    //     lights[2]->setPixmap(fitpixmap2);
    //     lights[3]->setPixmap(fitpixmap2);
    //     lights[4]->setPixmap(fitpixmap2);
    //}
    */
}

//与金老师接口的定时器处理
void MainWindow::jinTimerout(){
if(!isDefiningRegion){
    /**********start*******************/
    clock_t t1,t2,t3,t4,t5;
    /**********end*******************/
    /**********start*******************/
    t1=clock();
    /**********end*******************/
    //vector<MyObject> objs = in.getObjs2();
    //std::cout<<"ok2 "<<std::endl;
    //#if 1

    //qDebug()<<"jinTimerout";
  //  int v=in.getIntegratedData();
   // qDebug()<<"jinTimerOut2";

qDebug()<<"-----------------------------------------main:"<<QThread::currentThreadId();
qDebug()<<"jinTimerout";
    int v=inThread.getIntegratedData();
qDebug()<<"jinTimerOut2";
/**********start*******************/
t2=clock();
/**********end*******************/
//    if(v == 0){

        //std::cout<<"getintegrated data "<<std::endl;
        //图片1
        //        QString s1=in.getQJ1();
        //        imageurl=s1.toStdString();
        //        //qDebug()<<in.getObjs().size();
        //在全景上画矩形，文字，轨迹等
        //在两个全景上画矩形，文字，轨迹等
        timerFlash->stop();
        //qDebug()<<QTime::currentTime().toString("hh:mm:ss");
        QString today=QString("./回放/")+QDate::currentDate().toString("yyyy-MM-dd");
        //QDir *todayDir=new QDir();
        bool exist=directory->exists(today);
        if(!exist){
            directory->mkdir(today);
        }
        //delete todayDir;

        /***
         * 从interfaceThread一次性获取完数据，然后马上获取下一次的数据，不要到后边还有get调用，否则可能到下次执行timer通信还没结束
         */
        mainPano = inThread.getPano();
        vector<TrackingPoint> tps = inThread.GetTps();
        vector<MyObject> objs = inThread.getObjs();

        inThread.getNext();//开始下次通信
        //从interfaceThread获取数据结束
        storeThread->con.wakeOne();
        //cv::imshow("test",pano);

        //cv::imwrite("test.bmp",pano);

//        cv::imwrite("test.bmp",pano);

//        if(isJixu == true){
//            QString current_time=QTime::currentTime().toString("hh-mm-ss");
//            QString current_path=QString("").append(today).append("/").append(current_time).append(".pan");
//            QFile file(current_path);
//            file.open(QIODevice::WriteOnly);
//            QDataStream out(&file);
//            if(pano.empty()){
//                out<<-1;
//            }else{
//                out<<1;
//                MyObject::writeMat(out,pano);
//            }
//            file.close();
//            current_time.clear();
//            current_path.clear();

//        }

        Mat pano1 = mainPano.clone();
        Mat pano2 = mainPano.clone();
        Mat mat;
        hconcat(pano1,pano2,mat);


        //在全景上画矩形，文字，轨迹等
        //Mat mat = in.getPano().clone();
//        vector<MyObject> objs = in.getObjs();
        qDebug()<<"mainwindow objs.size "<<objs.size();

//        if(isJixu == true){
//            for(int i=0;i<objs.size();i++){
//                QString current_time=QTime::currentTime().toString("hh-mm-ss");
//                QString current_path=QString("").append(today).append("/").append(current_time).append("-").append(QString::number(i)).append(".dat");
//                QFile file(current_path);
//                file.open(QIODevice::WriteOnly);
//                QDataStream out(&file);
//                out<<objs.at(i);
//                file.close();
//                current_time.clear();
//                current_path.clear();
//            }
//        }

        //vector<MyObjectTrack> tracks = in.getTracks();
//       if(this->isPseudo==true)
//           mat=setPseudocolor(mat);
//        updateBright(mat);
//        updateContrast(mat);


        //if(isMubiao){
            for(int ii = 0; ii < tps.size(); ii++){
                TrackingPoint tp = tps[ii];
                int id = tp.id;
                vector<Point> points = tp.track;
                //if(id == obj.getID()){
                for(int iii = 0; iii < points.size(); iii++){
                    Point point = points[iii];
                    Point point2 = Point(point.x+mainPano.cols, point.y);
                    //  std::cout<<"sdk point circle "<<point.x<<" "<<point.y<<std::endl;
                    circle(mat, point, 2, Scalar(0,0,255),1,8,0);//在图像中画出特征点，2是圆的半径
                    circle(mat, point2, 2, Scalar(0,0,255),1,8,0);//在图像中画出特征点，2是圆的半径
                    if(iii >= 1){
                        //std::cout<<"sdk point line "<<std::endl;
                        Point point3 = points[iii-1];
                       // std::cout<<"sdk point3 circle "<<point3.x<<" "<<point3.y<<std::endl;
                        Point point4 = Point(point3.x+mainPano.cols, point3.y);
                        line(mat,point,point3,Scalar(0,0,255),1,8,0);
                        line(mat,point2,point4,Scalar(0,0,255),1,8,0);
                    }
                    //cv::cvtColor(mat, mat, CV_BGR2RGB);
                }
                //}
            }
        //}
        num_objs = objs.size();

        for (int i = 0; i < num_objs;i++)
        {
            //画对象的box
            MyObject obj = objs[i];

            //qDebug()<<"obj.point!!!!!"<<obj.cenPoint.x<<","<<obj.cenPoint.y;

            qDebug()<<"obj.point!!!!!x="<<obj.cenPoint.x<<",y="<<obj.cenPoint.y<<",rect w="<<obj.getRect().width<<",rect h = "<<obj.getRect().height;

            Rect rect2 = Rect(obj.getRect().x+mainPano.cols, obj.getRect().y, obj.getRect().width, obj.getRect().height);
            rectangle(mat,obj.getRect(),obj.getColor(),2,1,0);
            rectangle(mat,rect2,obj.getColor(),2,1,0);
            //cv::cvtColor(mat, mat, CV_BGR2RGB);

            //画轨迹
//            if(isMubiao){
//                for(int ii = 0; ii < tracks.size(); ii++){
//                    MyObjectTrack track = tracks[ii];
//                    int id = track.getId();
//                    vector<Point> points = track.getTrack();
//                    if(id == obj.getID()){
//                        for(int iii = 0; iii < points.size(); iii++){
//                            Point point = points[iii];
//                            Point point2 = Point(point.x+pano.cols, point.y);
//                            circle(mat, point, 2, obj.getColor(),-1,8,0);//在图像中画出特征点，2是圆的半径
//                            circle(mat, point2, 2, obj.getColor(),-1,8,0);//在图像中画出特征点，2是圆的半径
//                            if(iii >= 1){
//                                Point point3 = points[iii-1];
//                                Point point4 = Point(point3.x+pano.cols, point3.y);
//                                line(mat,point,point3,obj.getColor(),1,8,0);
//                                line(mat,point2,point4,obj.getColor(),1,8,0);
//                            }
//                            //cv::cvtColor(mat, mat, CV_BGR2RGB);
//                        }
//                    }
//                }
//            }

            //画对象中心点的位置
            if(isMubiao){
                int x = (int)(this->getDirectionX(obj.getCenPoint().x, mainPano));
                int y = (int)(10-this->getDirectionY(obj.getCenPoint().y, mainPano)/2);//(10-10*(this->getDirectionY(obj.getCenPoint().y)-this->getDirectionY())/(this->getDirectionY2()-this->getDirectionY()));//endh - i*(endh-starth)/10
                QString tx = QString::number(x,10);
                QString ty = QString::number(y,10);
                QString tstr = "x="+tx+",y="+ty;
                string str = tstr.toStdString();
                QString idstr = "id="+QString::number(obj.getID(),10);
                string idst = idstr.toStdString();
                //qDebug()<<tstr;
                Point p = Point(obj.getRect().x+obj.getRect().width,obj.getRect().y+obj.getRect().height);
                Point p2 = Point(obj.getRect().x+obj.getRect().width+mainPano.cols,obj.getRect().y+obj.getRect().height);

                putText(mat,str,p,3,0.5,obj.getColor());
                putText(mat,str,p2,3,0.5,obj.getColor());

                Point p3 = Point(obj.getRect().x+obj.getRect().width,obj.getRect().y+obj.getRect().height/3);
                Point p4 = Point(obj.getRect().x+obj.getRect().width+mainPano.cols,obj.getRect().y+obj.getRect().height/3);

                putText(mat,idst,p3,3,0.5,obj.getColor());
                putText(mat,idst,p4,3,0.5,obj.getColor());
            }
            // cv::cvtColor(mat, mat, CV_BGR2RGB);
        }
        //  cv::cvtColor(mat, mat, CV_BGR2RGB);

        //画告警区域
        for(int iii = 0; iii < this->rgs.size(); iii++){
            RegionGroup rg = rgs[iii];
            rg.draw(mat);
        }

        Mat tmat = mat.clone();

             //画矩形
             if(this->widget1->isTo3){
                 //qDebug()<<"w1 rect3: x="<<this->widget1->rectan3.x<<",y="<<this->widget1->rectan3.y<<",width="<<this->widget1->rectan3.width<<",height="<<this->widget1->rectan3.height;
                 rectangle(tmat,this->widget1->rectan3,this->widget3->getColor(),4,1,0);
                 Rect rect2 = Rect(this->widget1->rectan3.x+mainPano.cols, this->widget1->rectan3.y, this->widget1->rectan3.width, this->widget1->rectan3.height);
                 rectangle(tmat,rect2,this->widget3->getColor(),4,1,0);
             }
             if(this->widget1->isTo4){
                 rectangle(tmat,this->widget1->rectan4,this->widget4->getColor(),4,1,0);
                 Rect rect2 = Rect(this->widget1->rectan4.x+mainPano.cols, this->widget1->rectan4.y, this->widget1->rectan4.width, this->widget1->rectan4.height);
                 rectangle(tmat,rect2,this->widget4->getColor(),4,1,0);
             }
             if(this->widget1->isTo6){
                 rectangle(tmat,this->widget1->rectan6,this->widget6->getColor(),4,1,0);
                 Rect rect2 = Rect(this->widget1->rectan6.x+mainPano.cols, this->widget1->rectan6.y, this->widget1->rectan6.width, this->widget1->rectan6.height);
                 rectangle(tmat,rect2,this->widget6->getColor(),4,1,0);
             }
             if(this->widget2->isTo3){
                 rectangle(tmat,this->widget2->getQRectan3(),this->widget3->getColor(),4,1,0);
                 Rect rect2 = Rect(this->widget2->getQRectan3().x+mainPano.cols, this->widget2->getQRectan3().y, this->widget2->getQRectan3().width, this->widget2->getQRectan3().height);
                 rectangle(tmat,rect2,this->widget3->getColor(),4,1,0);
             }
             if(this->widget2->isTo4){
                 rectangle(tmat,this->widget2->getQRectan4(),this->widget4->getColor(),4,1,0);
                 Rect rect2 = Rect(this->widget2->getQRectan4().x+mainPano.cols, this->widget2->getQRectan4().y, this->widget2->getQRectan4().width, this->widget2->getQRectan4().height);
                 rectangle(tmat,rect2,this->widget4->getColor(),4,1,0);
             }
             if(this->widget2->isTo6){
                 rectangle(tmat,this->widget2->getQRectan6(),this->widget6->getColor(),4,1,0);
                 Rect rect2 = Rect(this->widget2->getQRectan6().x+mainPano.cols, this->widget2->getQRectan6().y, this->widget2->getQRectan6().width, this->widget2->getQRectan6().height);
                 rectangle(tmat,rect2,this->widget6->getColor(),4,1,0);
             }


             //然后劈成2半


        //    Size dsize ;
        //    double scale = 1;
        //    dsize = Size(mat.cols*scale,mat.rows*scale);
        //    Mat image11 = Mat(dsize,CV_32S);
        //    cv::resize(mat, image11,dsize);

        //    QImage img = QImage((const unsigned char*)(image11.data),image11.cols,image11.rows, image11.cols*image11.channels(),  QImage::Format_RGB888);
        //    QImage aa=(&img)->copy(QRect(0,0,mat.cols/2,mat.rows));
        //    Mat image4 = CVUtil::QImageToMat(aa);
        //    Mat image44 = Mat(dsize,CV_32S);
        //    cv::resize(image4, image44,dsize);

        //    //全景2Mat
        //    QImage aa2=(&img)->copy(QRect(mat.cols/2,0,mat.cols/2,mat.rows));
        //    Mat image5 = CVUtil::QImageToMat(aa2);
        //    Mat image55 = Mat(dsize,CV_32S);
        //    cv::resize(image5, image55,dsize);
        Mat mat1, mat2;
        mat(Rect(mat.cols/2,0,mat.cols/4,mat.rows)).copyTo(mat1);
        mat(Rect(mat.cols/4,0,mat.cols/4,mat.rows)).copyTo(mat2);

        Mat mat3,mat4;
        tmat(Rect(mat.cols/2,0,mat.cols/4,mat.rows)).copyTo(mat3);
        tmat(Rect(mat.cols/4,0,mat.cols/4,mat.rows)).copyTo(mat4);

        /*********************/


        Mat newpano;
        hconcat(mat1,mat2,newpano);

        //Mat mat1 = image44;
        //    if(this->isPseudo==true)
        //        mat1=setPseudocolor(mat1);
        //    updateBright(mat1);
        //    updateContrast(mat1);
        //        if(saturation1!=100){
        //               hsl->channels[color].saturation1 = saturation1 - 100;
        //               hsl->adjust(mat1, mat1);
        //           }

        widget1->setMat(mat3);
        widget1->setPano(newpano);
        widget1->setTwoPano(mat);
        widget1->setObjects(objs);
//        widget1->setTracks(in.getTracks());
        /**********start*******************/
        t3=clock();
        /**********end*******************/
        widget1->draw();
        /**********start*******************/
        t4=clock();
        /**********end*******************/
        widget2->setPano(newpano);
        widget2->setTwoPano(mat);
        //widget2->setPano(mat);
        widget2->setMat(mat4);
        widget2->setObjects(objs);
//        widget2->setTracks(in.getTracks());
        widget2->draw();

        //qDebug()<<s2;
        //drawUiLabel(mat2,2);
        //图片3
        //Mat mat3 =imread(imageurl);
        widget3->setPano(newpano);
        widget3->setTwoPanos(mat);
        widget3->setAllObjects(widget1->objs);
        widget3->draw();
        //drawUiLabelByCopy(mat3,3);
        //图片4
        //Mat mat4 =imread(imageurl2);
        //drawUiLabelByCopy(mat4,4);
        widget4->setPano(newpano);
        widget4->setTwoPanos(mat);
        widget4->setAllObjects(widget1->objs);
        widget4->draw();
        //图片5
        //QString imageurl5=in.getHD();
        //Mat mat5 =imread(imageurl5.toStdString());
        //widget5->setMat(mat5);
        //widget5->setPano(newpano);
        widget5->setObjects(objs);
        widget5->draw();
        //drawUiLabel(mat5,5);
        //图片6
        //QString imageurl6= in.getLD();
        //Mat mat6 =imread(imageurl6.toStdString());
        //widget6->setMat(mat6);
        //        widget6->setPano(newpano);
        //        widget6->setObjects(objs);
        //        widget6->draw();
        widget6->setPano(newpano);
        widget6->setTwoPanos(mat);
        widget6->setAllObjects(widget1->objs);
        widget6->draw();

//        QString imageurl7= "./0.png";
//        Mat mat7 =imread(imageurl7.toStdString());
//        widget7->setMat(mat7);
//        widget7->setObjects(objs);
//        widget7->draw();

        this->alertProcessing(objs);

        //qDebug()<<QTime::currentTime().toString("hh:mm:ss");

        //     if(isGaojing)
        //     {
        //         if(objs.size()>num_objs){
        //             this->sound->play();
        //             newObjCount=objs.size()-num_objs;
        //             timerFlash->start();

        //             num_objs = objs.size();
        //         }
        //         else
        //             num_objs =objs.size();
        //     }

        //     if(isGaojing)
        //     {
        //         if(num_objs==0)
        //         {
        //             lights[0]->setPixmap(fitpixmap2);
        //             lights[1]->setPixmap(fitpixmap2);
        //             lights[2]->setPixmap(fitpixmap2);
        //             lights[3]->setPixmap(fitpixmap2);
        //             lights[4]->setPixmap(fitpixmap2);
        //         }
        //         else if(num_objs==1)
        //         {
        //             lights[0]->setPixmap(fitpixmap1);
        //             lights[1]->setPixmap(fitpixmap2);
        //             lights[2]->setPixmap(fitpixmap2);
        //             lights[3]->setPixmap(fitpixmap2);
        //             lights[4]->setPixmap(fitpixmap2);
        //    //            light1->setPixmap(fitpixmap1);
        //    //            light2->setPixmap(fitpixmap2);
        //    //            light3->setPixmap(fitpixmap2);
        //    //            light4->setPixmap(fitpixmap2);
        //    //            light5->setPixmap(fitpixmap2);
        //         }
        //         else if(num_objs==2)
        //         {
        //             lights[0]->setPixmap(fitpixmap1);
        //             lights[1]->setPixmap(fitpixmap1);
        //             lights[2]->setPixmap(fitpixmap2);
        //             lights[3]->setPixmap(fitpixmap2);
        //             lights[4]->setPixmap(fitpixmap2);

        //    //            light1->setPixmap(fitpixmap1);
        //    //            light2->setPixmap(fitpixmap1);
        //    //            light3->setPixmap(fitpixmap2);
        //    //            light4->setPixmap(fitpixmap2);
        //    //            light5->setPixmap(fitpixmap2);
        //         }
        //         else if(num_objs==3)
        //         {
        //             lights[0]->setPixmap(fitpixmap1);
        //             lights[1]->setPixmap(fitpixmap1);
        //             lights[2]->setPixmap(fitpixmap1);
        //             lights[3]->setPixmap(fitpixmap2);
        //             lights[4]->setPixmap(fitpixmap2);
        //    //            light1->setPixmap(fitpixmap1);
        //    //            light2->setPixmap(fitpixmap1);
        //    //            light3->setPixmap(fitpixmap1);
        //    //            light4->setPixmap(fitpixmap2);
        //    //            light5->setPixmap(fitpixmap2);
        //         }
        //         else if(num_objs==4)
        //         {
        //             lights[0]->setPixmap(fitpixmap1);
        //             lights[1]->setPixmap(fitpixmap1);
        //             lights[2]->setPixmap(fitpixmap1);
        //             lights[3]->setPixmap(fitpixmap1);
        //             lights[4]->setPixmap(fitpixmap2);
        //    //            light1->setPixmap(fitpixmap1);
        //    //            light2->setPixmap(fitpixmap1);
        //    //            light3->setPixmap(fitpixmap1);
        //    //            light4->setPixmap(fitpixmap1);
        //    //            light5->setPixmap(fitpixmap2);
        //         }
        //         else if(num_objs>= 5 )
        //         {
        //             lights[0]->setPixmap(fitpixmap1);
        //             lights[1]->setPixmap(fitpixmap1);
        //             lights[2]->setPixmap(fitpixmap1);
        //             lights[3]->setPixmap(fitpixmap1);
        //             lights[4]->setPixmap(fitpixmap1);
        //    //            light1->setPixmap(fitpixmap1);
        //    //            light2->setPixmap(fitpixmap1);
        //    //            light3->setPixmap(fitpixmap1);
        //    //            light4->setPixmap(fitpixmap1);
        //    //            light5->setPixmap(fitpixmap1);
        //       }
        //     }
        //     else
        //     {
        //         lights[0]->setPixmap(fitpixmap2);
        //         lights[1]->setPixmap(fitpixmap2);
        //         lights[2]->setPixmap(fitpixmap2);
        //         lights[3]->setPixmap(fitpixmap2);
        //         lights[4]->setPixmap(fitpixmap2);
        //    }
//    }
//    else{
//        //QMessageBox::information(this,tr("接口返回值"),QString::number(v,10));
//        this->selfTimerout();
//    }
    /**************start******************/
    t5=clock();
    FILE *pFile=fopen("check_time.txt","a+");
//    fprintf(pFile,"socket time is %d\n",t2-t1);
    fprintf(pFile,"total  time is %d\n\n",t5-t1);

    fclose(pFile);
    printf("\t\t\t\twidget1 draw()time is %d\n",t4-t3);
    printf("\t\t\t\tsocket cost time is %d\n",t2-t1);
    printf("\t\t\t\twang time is %d\n",t5-t2);
    printf("\t\t\t\ttotal time is %d\n",t5-t1);
    /**********end*******************/
}
//定义监控区域的时候，停止接收图像。
else{

}

}

//以下处理鼠标拖拽事件，在全景显示区1或者2有选择框的情况下，从全景显示区1或者2出发，目标是主显示区，则拷贝图像到主显示区；目标是凝视显示区，则拷贝图像到凝视显示区。
void MainWindow::mousePressEvent(QMouseEvent *e)
{
    //qDebug()<<"鼠标压下事件来自mainframe";
    if(e->button() == Qt::LeftButton)
    {
        //isRect = false;
        //判断是否是拖拽出发点
        //        QPoint position1 = e->pos();//e->globalPos() - this->pos();
        //        //起始点是落在全景显示区1中的情况
        //        if((position1.x() <= this->widget1->pos().x()+this->widget1->width()) &&(position1.x() >= this->widget1->pos().x()) && (position1.y() <= this->widget1->pos().y()+this->widget1->height()) &&(position1.y() >= this->widget1->pos().y())){
        //            isDrag1 = true;
        //            isDrag2 = false;
        //        }
        //        //起始点是落在全景显示区2中的情况
        //        if((position1.x() <= this->widget2->pos().x()+this->widget2->width()) &&(position1.x() >= this->widget2->pos().x()) && (position1.y() <= this->widget2->pos().y()+this->widget2->height()) &&(position1.y() >= this->widget2->pos().y())){
        //            isDrag2 = true;
        //            isDrag1 = false;
        //        }

        //e->accept();
        //qDebug()<<position1;
    }
}

void MainWindow::mouseMoveEvent(QMouseEvent *e)
{
    //    if(isDrag1 && (e->buttons() && Qt::LeftButton)){
    //        //move(e->globalPos() - position1);
    //        isMove = true;
    //        //e->accept();
    //    }
    //    if(isDrag2 && (e->buttons() && Qt::LeftButton)){
    //        //move(e->globalPos() - position1);
    //        isMove = true;
    //        //e->accept();
    //    }
    e->ignore();
}

void MainWindow::mouseReleaseEvent(QMouseEvent *e)
{


    //判断目的点落在主显示区的标志变量
    boolean target3 = false;
    boolean target4 = false;
    boolean target6 = false;
    QPoint position2 = e->pos();//e->globalPos() - this->pos();
    //判断目的点落在主显示区的情况
    if((position2.x() <= this->widget3->pos().x()+this->widget3->width()) &&(position2.x() >= this->widget3->pos().x()) && (position2.y() <= this->widget3->pos().y()+this->widget3->height()) &&(position2.y() >= this->widget3->pos().y())){
        target3 = true;
        target4 = false;
        target6 = false;
    }
    //判断目的点落在辅助显示区1的情况
    else if((position2.x() <= this->widget4->pos().x()+this->widget4->width()) &&(position2.x() >= this->widget4->pos().x()) && (position2.y() <= this->widget4->pos().y()+this->widget4->height()) &&(position2.y() >= this->widget4->pos().y())){
        target4 = true;
        target3 = false;
        target6 = false;
    }
    //判断目的点落在辅助显示区2的情况
    else if((position2.x() <= this->widget6->pos().x()+this->widget6->width()) &&(position2.x() >= this->widget6->pos().x()) && (position2.y() <= this->widget6->pos().y()+this->widget6->height()) &&(position2.y() >= this->widget6->pos().y())){
        target6 = true;
        target3 = false;
        target4 = false;
    }

    else{
        isDrag1 = false;
        isDrag2 = false;
        isMove = false;
    }
    //qDebug()<<"here!!";
    //qDebug()<<"isDrag1:"<<isDrag1<<"isDrag2:"<<isDrag2<<"isMove:"<<isMove;
    //qDebug()<<"target3:"<<target3<<"target4:"<<target4<<"target6"<<target6;
    //6种组合
    //1. 如果出发点是全景显示区1，并且全景显示区1中有选择框，并且目的是主显示区，则拷贝全景显示区1选择框内的图像到主显示区
    if(isDrag1 && isMove && target3){

        //        widget1->rectan.x = widget1->newrect.x;
        //        widget1->rectan.y = widget1->newrect.y;
        //        widget1->rectan.width = widget1->newrect.width;
        //        widget1->rectan.height = widget1->newrect.height;
        widget1->isTo3 = true;
        widget2->isTo3 = false;

        if(widget1->newrect.width<0){
            widget1->rectan3.width = -widget1->newrect.width;
            widget1->rectan3.height= -widget1->newrect.height;
            widget1->rectan3.x = widget1->newrect.x+widget1->newrect.width;
            widget1->rectan3.y = widget1->newrect.y+widget1->newrect.height;
        }
        else if(widget1->newrect.height<0){
            widget1->rectan3.width = -widget1->newrect.width;
            widget1->rectan3.height= -widget1->newrect.height;
            widget1->rectan3.x = widget1->newrect.x+widget1->newrect.width;
            widget1->rectan3.y = widget1->newrect.y+widget1->newrect.height;
        }
        else{
            widget1->rectan3.x = widget1->newrect.x;
            widget1->rectan3.y = widget1->newrect.y;
            widget1->rectan3.width = widget1->newrect.width;
            widget1->rectan3.height = widget1->newrect.height;
        }
        widget1->isRect = false;

        //调整所选的矩形框，以使得在主显示区中的显示不变形
        //widget1->rectan3.width = widget1->rectan3.height * widget3->width() / widget3->height();

        //更新主显示区所包含的目标
        vector<MyObject> objs3;
        int num_objs = widget1->objs.size();
        for(int i = 0; i < num_objs; i++){
            MyObject obj = widget1->objs[i];
            if(widget1->isObjSelected3(obj)){
                objs3.push_back(obj);
            }
        }

        widget3->setObjects(objs3);

        widget3->setFrom(1);

        widget3->setRect(widget1->getQRectan3());
        //widget1->rectan = widget1->newrect;

        Mat mat = widget1->getPano();
        Size dsize ;
        double scale = 1;
        dsize = Size(mat.cols*scale,mat.rows*scale);
        //        Mat image11 = Mat(dsize,CV_32S);
        //        cv::resize(mat, image11,dsize);
        //        img = QImage((const unsigned char*)(image11.data),image11.cols,image11.rows, image11.cols*image11.channels(),  QImage::Format_RGB888);

        //        //vector<Rectan> rectans;
        //        aa=(&img)->copy(widget1->getQRectan3());
        //        Mat image3 = QImageToMat(aa);
        //        Mat image33 = Mat(dsize,CV_32S);
        //        cv::resize(image3, image33,dsize);
        //        widget3->setMat(image33);
        Mat image3;
        mat(widget1->rectan3).copyTo(image3);//mw->QImageToMat(mw->aa);
        Mat image33 = Mat(dsize,CV_32S);
        cv::resize(image3, image33,dsize);
        widget3->setMat(image33);
        widget3->draw();
    }
    //2. 如果出发点是全景显示区2，并且全景显示区2中有选择框，并且目的是主显示区，则拷贝全景显示区2选择框内的图像到主显示区
    if(isDrag2 && isMove && target3){
        //widget2->rectan = widget2->newrect;
        //        widget2->rectan.x = widget2->newrect.x;
        //        widget2->rectan.y = widget2->newrect.y;
        //        widget2->rectan.width = widget2->newrect.width;
        //        widget2->rectan.height = widget2->newrect.height;

        widget1->isTo3 = false;
        widget2->isTo3 = true;

        if(widget2->newrect.width<0){
            widget2->rectan3.width = -widget2->newrect.width;
            widget2->rectan3.height= -widget2->newrect.height;
            widget2->rectan3.x = widget2->newrect.x+widget2->newrect.width;
            widget2->rectan3.y = widget2->newrect.y+widget2->newrect.height;
        }
        else if(widget2->newrect.height<0){
            widget2->rectan3.width = -widget2->newrect.width;
            widget2->rectan3.height= -widget2->newrect.height;
            widget2->rectan3.x = widget2->newrect.x+widget2->newrect.width;
            widget2->rectan3.y = widget2->newrect.y+widget2->newrect.height;
        }
        else{
            widget2->rectan3.x = widget2->newrect.x;
            widget2->rectan3.y = widget2->newrect.y;
            widget2->rectan3.width = widget2->newrect.width;
            widget2->rectan3.height = widget2->newrect.height;
        }

        widget2->isRect = false;

        //调整所选的矩形框，以使得在主显示区中的显示不变形
        //widget2->rectan3.width = widget2->rectan3.height * widget3->width() / widget3->height();

        //更新主显示区所包含的目标
        vector<MyObject> objs3;
        int num_objs = widget2->objs.size();
        for(int i = 0; i < num_objs; i++){
            MyObject obj = widget2->objs[i];
            if(widget2->isObjSelected3(obj)){
                objs3.push_back(obj);
            }
        }

        widget3->setObjects(objs3);

        widget3->setFrom(2);

        widget3->setRect(widget2->getQRectan3());

        Mat mat = widget2->getPano();
        Size dsize ;
        double scale = 1;
        dsize = Size(mat.cols*scale,mat.rows*scale);
        //        Mat image11 = Mat(dsize,CV_32S);
        //        cv::resize(mat, image11,dsize);
        //        img = QImage((const unsigned char*)(image11.data),image11.cols,image11.rows, image11.cols*image11.channels(),  QImage::Format_RGB888);

        //        //vector<Rectan> rectans;
        //        aa=(&img)->copy(widget2->getQRectan3());
        //        Mat image3 = QImageToMat(aa);
        //        Mat image33 = Mat(dsize,CV_32S);
        //        cv::resize(image3, image33,dsize);
        //        widget3->setMat(image33);
        //        widget3->draw();
        Mat image3;
        mat(widget2->getQRectan3()).copyTo(image3);//mw->QImageToMat(mw->aa);
        Mat image33 = Mat(dsize,CV_32S);
        cv::resize(image3, image33,dsize);
        widget3->setMat(image33);
        widget3->draw();
    }
    //3. 如果出发点是全景显示区1，并且全景显示区1中有选择框，并且目的是辅助显示区1，则拷贝全景显示区1选择框内的图像到辅助显示区1
    if(isDrag1 && isMove && target4){
        //widget1->rectan = widget1->newrect;
        widget1->isTo4 = true;
        widget2->isTo4 = false;

        if(widget1->newrect.width<0){
            widget1->rectan4.width = -widget1->newrect.width;
            widget1->rectan4.height= -widget1->newrect.height;
            widget1->rectan4.x = widget1->newrect.x+widget1->newrect.width;
            widget1->rectan4.y = widget1->newrect.y+widget1->newrect.height;
        }
        else if(widget1->newrect.height<0){
            widget1->rectan4.width = -widget1->newrect.width;
            widget1->rectan4.height= -widget1->newrect.height;
            widget1->rectan4.x = widget1->newrect.x+widget1->newrect.width;
            widget1->rectan4.y = widget1->newrect.y+widget1->newrect.height;
        }
        else{
            widget1->rectan4.x = widget1->newrect.x;
            widget1->rectan4.y = widget1->newrect.y;
            widget1->rectan4.width = widget1->newrect.width;
            widget1->rectan4.height = widget1->newrect.height;
        }
        widget1->isRect = false;

        //调整所选的矩形框，以使得在主显示区中的显示不变形
        //widget1->rectan4.width = widget1->rectan4.height * widget4->width() / widget4->height();

        //更新主显示区所包含的目标
        vector<MyObject> objs4;
        int num_objs = widget1->objs.size();
        for(int i = 0; i < num_objs; i++){
            MyObject obj = widget1->objs[i];
            if(widget1->isObjSelected4(obj)){
                objs4.push_back(obj);
            }
        }

        widget4->setObjects(objs4);

        widget4->setFrom(1);

        widget4->setRect(widget1->getQRectan4());

        Mat mat = widget1->getPano();
        Size dsize ;
        double scale = 1;
        dsize = Size(mat.cols*scale,mat.rows*scale);
        //        Mat image11 = Mat(dsize,CV_32S);
        //        cv::resize(mat, image11,dsize);
        //        img = QImage((const unsigned char*)(image11.data),image11.cols,image11.rows, image11.cols*image11.channels(),  QImage::Format_RGB888);

        //        //vector<Rectan> rectans;
        //        aa=(&img)->copy(widget1->getQRectan4());
        //        Mat image4 = QImageToMat(aa);
        //        Mat image44 = Mat(dsize,CV_32S);
        //        cv::resize(image4, image44,dsize);
        //        widget4->setMat(image44);
        //        widget4->draw();
        Mat image4;
        mat(widget1->rectan4).copyTo(image4);//mw->QImageToMat(mw->aa);
        Mat image44 = Mat(dsize,CV_32S);
        cv::resize(image4, image44,dsize);
        widget4->setMat(image44);
        widget4->draw();
    }
    //4. 如果出发点是全景显示区2，并且全景显示区2中有选择框，并且目的是辅助显示区1，则拷贝全景显示区2选择框内的图像到辅助显示区1
    if(isDrag2 && isMove && target4){

        widget1->isTo4 = false;
        widget2->isTo4 = true;

        //widget2->rectan = widget2->newrect;
        if(widget2->newrect.width<0){
            widget2->rectan4.width = -widget2->newrect.width;
            widget2->rectan4.height= -widget2->newrect.height;
            widget2->rectan4.x = widget2->newrect.x+widget2->newrect.width;
            widget2->rectan4.y = widget2->newrect.y+widget2->newrect.height;
        }
        else if(widget2->newrect.height<0){
            widget2->rectan4.width = -widget2->newrect.width;
            widget2->rectan4.height= -widget2->newrect.height;
            widget2->rectan4.x = widget2->newrect.x+widget2->newrect.width;
            widget2->rectan4.y = widget2->newrect.y+widget2->newrect.height;
        }
        else{
            widget2->rectan4.x = widget2->newrect.x;
            widget2->rectan4.y = widget2->newrect.y;
            widget2->rectan4.width = widget2->newrect.width;
            widget2->rectan4.height = widget2->newrect.height;
        }
        widget2->isRect = false;

        //调整所选的矩形框，以使得在主显示区中的显示不变形
        //widget2->rectan4.width = widget2->rectan4.height * widget4->width() / widget4->height();

        //更新主显示区所包含的目标
        vector<MyObject> objs4;
        int num_objs = widget2->objs.size();
        for(int i = 0; i < num_objs; i++){
            MyObject obj = widget2->objs[i];
            if(widget2->isObjSelected4(obj)){
                objs4.push_back(obj);
            }
        }

        widget4->setObjects(objs4);

        widget4->setFrom(2);

        widget4->setRect(widget2->getQRectan4());

        Mat mat = widget2->getPano();
        Size dsize ;
        double scale = 1;
        dsize = Size(mat.cols*scale,mat.rows*scale);
        //        Mat image11 = Mat(dsize,CV_32S);
        //        cv::resize(mat, image11,dsize);
        //        img = QImage((const unsigned char*)(image11.data),image11.cols,image11.rows, image11.cols*image11.channels(),  QImage::Format_RGB888);

        //        //vector<Rectan> rectans;
        //        aa=(&img)->copy(widget2->getQRectan4());
        //        Mat image4 = QImageToMat(aa);
        //        Mat image44 = Mat(dsize,CV_32S);
        //        cv::resize(image4, image44,dsize);
        //        widget4->setMat(image44);
        //        widget4->draw();
        Mat image4;
        mat(widget2->getQRectan4()).copyTo(image4);//mw->QImageToMat(mw->aa);
        Mat image44 = Mat(dsize,CV_32S);
        cv::resize(image4, image44,dsize);
        widget4->setMat(image44);
        widget4->draw();
    }
    //5. 如果出发点是全景显示区1，并且全景显示区1中有选择框，并且目的是辅助显示区2，则拷贝全景显示区1选择框内的图像到辅助显示区2
    if(isDrag1 && isMove && target6){
        //widget1->rectan = widget1->newrect;
        widget1->isTo6 = true;
        widget2->isTo6 = false;

        if(widget1->newrect.width<0){
            widget1->rectan6.width = -widget1->newrect.width;
            widget1->rectan6.height= -widget1->newrect.height;
            widget1->rectan6.x = widget1->newrect.x+widget1->newrect.width;
            widget1->rectan6.y = widget1->newrect.y+widget1->newrect.height;
        }
        else if(widget1->newrect.height<0){
            widget1->rectan6.width = -widget1->newrect.width;
            widget1->rectan6.height= -widget1->newrect.height;
            widget1->rectan6.x = widget1->newrect.x+widget1->newrect.width;
            widget1->rectan6.y = widget1->newrect.y+widget1->newrect.height;
        }
        else{
            widget1->rectan6.x = widget1->newrect.x;
            widget1->rectan6.y = widget1->newrect.y;
            widget1->rectan6.width = widget1->newrect.width;
            widget1->rectan6.height = widget1->newrect.height;

        }
        widget1->isRect = false;

        //调整所选的矩形框，以使得在主显示区中的显示不变形
        //widget1->rectan4.width = widget1->rectan4.height * widget4->width() / widget4->height();

        //更新主显示区所包含的目标
        vector<MyObject> objs6;
        int num_objs = widget1->objs.size();
        for(int i = 0; i < num_objs; i++){
            MyObject obj = widget1->objs[i];
            if(widget1->isObjSelected6(obj)){
                objs6.push_back(obj);
            }
        }

        widget6->setObjects(objs6);

        widget6->setFrom(1);

        widget6->setRect(widget1->getQRectan6());

        Mat mat = widget1->getPano();
        Size dsize ;
        double scale = 1;
        dsize = Size(mat.cols*scale,mat.rows*scale);
        //        Mat image11 = Mat(dsize,CV_32S);
        //        cv::resize(mat, image11,dsize);
        //        img = QImage((const unsigned char*)(image11.data),image11.cols,image11.rows, image11.cols*image11.channels(),  QImage::Format_RGB888);

        //        //vector<Rectan> rectans;
        //        aa=(&img)->copy(widget1->getQRectan4());
        //        Mat image4 = QImageToMat(aa);
        //        Mat image44 = Mat(dsize,CV_32S);
        //        cv::resize(image4, image44,dsize);
        //        widget4->setMat(image44);
        //        widget4->draw();
        Mat image6;
        mat(widget1->rectan6).copyTo(image6);//mw->QImageToMat(mw->aa);
        Mat image66 = Mat(dsize,CV_32S);
        cv::resize(image6, image66,dsize);
        widget6->setMat(image66);
        widget6->draw();
    }
    //6. 如果出发点是全景显示区2，并且全景显示区2中有选择框，并且目的是辅助显示区2，则拷贝全景显示区2选择框内的图像到辅助显示区2
    if(isDrag2 && isMove && target6){

        widget1->isTo6 = false;
        widget2->isTo6 = true;

        //widget2->rectan = widget2->newrect;
        if(widget2->newrect.width<0){
            widget2->rectan6.width = -widget2->newrect.width;
            widget2->rectan6.height= -widget2->newrect.height;
            widget2->rectan6.x = widget2->newrect.x+widget2->newrect.width;
            widget2->rectan6.y = widget2->newrect.y+widget2->newrect.height;
        }
        else if(widget2->newrect.height<0){
            widget2->rectan6.width = -widget2->newrect.width;
            widget2->rectan6.height= -widget2->newrect.height;
            widget2->rectan6.x = widget2->newrect.x+widget2->newrect.width;
            widget2->rectan6.y = widget2->newrect.y+widget2->newrect.height;
        }
        else{
            widget2->rectan6.x = widget2->newrect.x;
            widget2->rectan6.y = widget2->newrect.y;
            widget2->rectan6.width = widget2->newrect.width;
            widget2->rectan6.height = widget2->newrect.height;
        }
        widget2->isRect = false;

        //调整所选的矩形框，以使得在主显示区中的显示不变形
        //widget2->rectan4.width = widget2->rectan4.height * widget4->width() / widget4->height();

        //更新主显示区所包含的目标
        vector<MyObject> objs6;
        int num_objs = widget2->objs.size();
        for(int i = 0; i < num_objs; i++){
            MyObject obj = widget2->objs[i];
            if(widget2->isObjSelected6(obj)){
                objs6.push_back(obj);
            }
        }

        widget6->setObjects(objs6);

        widget6->setFrom(2);

        widget6->setRect(widget2->getQRectan6());

        Mat mat = widget2->getPano();
        Size dsize ;
        double scale = 1;
        dsize = Size(mat.cols*scale,mat.rows*scale);
        //        Mat image11 = Mat(dsize,CV_32S);
        //        cv::resize(mat, image11,dsize);
        //        img = QImage((const unsigned char*)(image11.data),image11.cols,image11.rows, image11.cols*image11.channels(),  QImage::Format_RGB888);

        //        //vector<Rectan> rectans;
        //        aa=(&img)->copy(widget2->getQRectan4());
        //        Mat image4 = QImageToMat(aa);
        //        Mat image44 = Mat(dsize,CV_32S);
        //        cv::resize(image4, image44,dsize);
        //        widget4->setMat(image44);
        //        widget4->draw();
        Mat image6;
        mat(widget2->getQRectan6()).copyTo(image6);//mw->QImageToMat(mw->aa);
        Mat image66 = Mat(dsize,CV_32S);
        cv::resize(image6, image66,dsize);
        widget6->setMat(image66);
        widget6->draw();
    }
    isDrag1 = false;
    isDrag2 = false;
    isMove = false;
    e->ignore();
}

void MainWindow::resizeEvent(QResizeEvent *){
    label->resize(widget1->size());
    label2->resize(widget2->size());
    label3->resize(widget3->size());
    label4->resize(widget4->size());
    label5->resize(widget5->size());
    label6->resize(widget6->size());
    label7->resize(widget7->size());
}

void MainWindow::paintEvent(QPaintEvent *){
    //重新绘制图片。
}

Mat MainWindow::setPseudocolor(Mat& image){
    Mat img_pseudocolor(image.rows, image.cols, CV_8UC3);
    // qDebug()<<image.channels();
    for (int y = 0; y < image.rows; y++)//转为伪彩色图像的具体算法
    {
        for (int x = 0; x < image.cols; x++)
        {
            int tmp = image.at<unsigned char>(y, x)  ;
            img_pseudocolor.at<Vec3b>(y, x)[0] = abs(255 - tmp); //blue
            img_pseudocolor.at<Vec3b>(y, x)[1] = abs(127 - tmp); //green
            img_pseudocolor.at<Vec3b>(y, x)[2] = abs(0 - tmp); //red
        }
    }
    return img_pseudocolor;
}

double MainWindow::getDirectionX(double x, Mat mat){
    //double x = this->rectan.x;
    //return 360*x/mat.cols -90;
    return 360*x/mat.cols;
}

double MainWindow::getDirectionY(double y, Mat mat){

    double yy = 20;
    //double y = this->rectan.y;
    return yy*y/mat.rows;

}


//---xiaotian 绘制界面上的图片3  图片4
void MainWindow::drawUiLabelByCopy(Mat image, int index1){
    if(this->isPseudo==true)
        image=setPseudocolor(image);
    for (int y = 0; y < image.rows; y++)
    {
        for (int x = 0; x < image.cols; x++)
        {
            for (int c = 0; c < 3; c++)
            {
                //new_image.at<Vec3b>(y, x)[c] = saturate_cast<uchar>(alpha*(image.at<Vec3b>(y, x)[c]) + beta);
                image.at<Vec3b>(y, x)[c] = saturate_cast<uchar>((image.at<Vec3b>(y, x)[c]) +  bright_TrackbarValue);
                if (image.at<Vec3b>(y, x)[c] > 255)
                {
                    image.at<Vec3b>(y, x)[c] = 255;
                }
            }
        }
    }

    //Mat image =imread(imgurl);
    Size dsize ;
    double scale = 1;
    dsize = Size(image.cols*scale,image.rows*scale);
    Mat image11 = Mat(dsize,CV_32S);
    cv::resize(image, image11,dsize);
    //    QImage img = QImage((const unsigned char*)(image11.data),image11.cols,image.rows, image11.cols*image11.channels(),  QImage::Format_RGB888);
    img = QImage((const unsigned char*)(image11.data),image11.cols,image.rows, image11.cols*image11.channels(),  QImage::Format_RGB888);

    vector<Rectan> rectans;
    //QImage aa;
    if(index1 == 3){
        aa=(&img)->copy(1494,253,92,92);
        Mat image3 = QImageToMat(aa);
        Mat image33 = Mat(dsize,CV_32S);
        cv::resize(image3, image33,dsize);
        Rectan rec4(1600,400,400,100);
        if(rectans1.size()== 0){
            rectans1.clear();
            rectans1.push_back(rec4);
        }else{
            Rectan rectemp = rectans1[0];
            rectans1.pop_back();
            Rectan rectnew;
            rectnew.setX(rectemp.getX()+50);
            rectnew.setY(rectemp.getY());
            rectnew.setWidth(rectemp.getWidth());
            rectnew.setHeight(rectemp.getHeight());
            rectans1.push_back(rectnew);
        }
        //QImage imgLabe3 = drawScaleAndRecOnPic(image33,rectans1,index,-1);
        drawScaleAndRecOnPic(image33,rectans1,index,-1);
        imgLabel3 = MatToQImage(image33,imgLabel3);
        //   cv::cvtColor(image11, image11, CV_BGR2RGB);
        loadPictureToLabel(label3,imgLabel3);
        //release(&image3);
        //release(&image33);
    }
    if(index1 == 4){
        aa=(&img)->copy(2604,13,92,92);
        Mat image4 = QImageToMat(aa);
        Mat image44 = Mat(dsize,CV_32S);
        cv::resize(image4, image44,dsize);
        Rectan rec4(1650,250,400,100);
        rectans.clear();
        rectans.push_back(rec4);
        //QImage imgLabel4 = drawRecOnPic(image44,rectans);
        drawRecOnPic(image44,rectans);
        imgLabel4 = MatToQImage(image44,imgLabel4);
        // cv::cvtColor(image11, image11, CV_BGR2RGB);
        loadPictureToLabel(label4,imgLabel4);
        //cvReleaseMat(&image4);
        //cvReleaseMat(&image44);
    }
    //cvReleaseMat(&image);
    //cvReleaseMat(&image11);
    //delete & aa;
    //delete & img;
}


//---xiaotian 绘制界面上的图片1 图片2 图片5 图片6
void MainWindow::drawUiLabel(Mat image, int index){
    if(index == 1 || index==2){
        for (int y = 0; y < image.rows; y++)
        {
            for (int x = 0; x < image.cols; x++)
            {
                for (int c = 0; c < 3; c++)
                {
                    //new_image.at<Vec3b>(y, x)[c] = saturate_cast<uchar>(alpha*(image.at<Vec3b>(y, x)[c]) + beta);
                    image.at<Vec3b>(y, x)[c] = saturate_cast<uchar>((image.at<Vec3b>(y, x)[c]) +  bright_TrackbarValue);
                    if (image.at<Vec3b>(y, x)[c] > 255)
                    {
                        image.at<Vec3b>(y, x)[c] = 255;
                    }
                }
            }
        }
    }
    //Mat image =imread(imgurl);
    vector<Rectan> rectans;
    if(index == 1){
        //图片1
        Rectan rec(1490,250,100,100);
        Rectan rec2(1800,250,50,50);
        rectans.push_back(rec);
        rectans.push_back(rec2);
        //QImage imgLabel = drawRecOnPic(image,rectans);
        drawRecOnPic(image,rectans);
        cv::cvtColor(image, image, CV_BGR2RGB);
        imgLabel1 = MatToQImage(image,imgLabel1);
        loadPictureToLabel(label,imgLabel1);
    }

    if(index == 2){
        //图片2
        Rectan rec3(2600,10,100,100);
        rectans.clear();
        rectans.push_back(rec3);
        //QImage imgLabel = drawRecOnPic(image,rectans);
        drawRecOnPic(image,rectans);
        cv::cvtColor(image, image, CV_BGR2RGB);
        imgLabel2 = MatToQImage(image,imgLabel2);
        loadPictureToLabel(label2,imgLabel2);
    }

    if(index == 5){
        //图片5
        Point point1(75,60);
        Point point2(110,40);
        Point point3(75,60);
        Point point4(125,118);
        Point point5(125,118);
        Point point6(130,114);
        Point point7(130,114);
        Point point8(110,40);
        vector<Point> points;
        points.push_back(point1);
        points.push_back(point2);
        points.push_back(point3);
        points.push_back(point4);
        points.push_back(point5);
        points.push_back(point6);
        points.push_back(point7);
        points.push_back(point8);
        //QImage imgLabel5 = drawCircleOnPic(image,points,120,100);
        drawCircleOnPic(image,points,120,100);
        imgLabel5 = MatToQImage(image, imgLabel5);
        cv::cvtColor(image, image, CV_BGR2RGB);
        loadPictureToLabel(label5,imgLabel5);
        //delete imgLabel5;
    }
    if(index == 6){
        //图片6
        Point point11(75,60);
        Point point21(110,39);
        Point point31(75,60);
        Point point41(150,150);
        Point point51(110,40);
        Point point61(150,150);
        vector<Point> points1;
        points1.push_back(point11);
        points1.push_back(point21);
        points1.push_back(point31);
        points1.push_back(point41);
        points1.push_back(point51);
        points1.push_back(point61);
        //QImage imgLabel6 = drawCircleOnPic(image,points1,120,100);
        drawCircleOnPic(image,points1,120,100);
        imgLabel6 = MatToQImage(image, imgLabel6);
        cv::cvtColor(image, image, CV_BGR2RGB);
        loadPictureToLabel(label6,imgLabel6);
        //delete imgLabel6;
    }
    //cvReleaseMat(&image);
}



//---xiaotian   加载图片到label上。
void MainWindow::loadPictureToLabel(QLabel *label, QImage image){
    QPixmap pixmap1 = QPixmap::fromImage(image);
    label->setPixmap(pixmap1);
    label->setScaledContents(true);
    //释放image
    //delete & image;
}

//加载图片到Label1上
void MainWindow::loadPictureToLabel1(boolean isRect, QRect qrect, Scalar co, QRect rectRegion, vector<Point> ps, vector<Region> rgs){
    //loadPictureToLabel(label,imgLabel1);
    QPixmap pixmap1 = QPixmap::fromImage(imgLabel1);
    QPainter painter(&pixmap1);
    if(isRect){

        painter.setPen(QPen(Qt::red,4,Qt::SolidLine)); //设置画笔形式
        //painter.setBrush(QBrush(Qt::red,Qt::SolidPattern)); //设置画刷形式
        painter.drawRect(qrect);
    }
    if(isDefiningRegion){
        QColor qc = QColor();
        qc.setRed(co.val[2]);
        qc.setGreen(co.val[1]);
        qc.setBlue(co.val[0]);
        QPen pen;
        pen.setColor(qc);
        pen.setWidth(4);
        pen.setStyle(Qt::SolidLine);
        painter.setPen(pen);
        if(rectRegion.width() > 0){
            painter.drawRect(rectRegion);
        }

        int size  = ps.size();
        for(int i = 0; i < size - 1; i++){
            QPoint p1 = QPoint(ps[i].x, ps[i].y);
            QPoint p2 = QPoint(ps[i+1].x, ps[i+1].y);
            painter.drawLine(p1,p2);
        }

        for(int i = 0; i < rgs.size(); i++){
            vector<Point> ps2 = rgs[i].getPoly();
            int size = ps2.size();
            for(int ii = 0; ii < size - 1; ii++){
                QPoint p1 = QPoint(ps2[ii].x, ps2[ii].y);
                QPoint p2 = QPoint(ps2[ii+1].x, ps2[ii+1].y);
                painter.drawLine(p1,p2);
            }
            painter.drawLine(QPoint(ps2[ps2.size()-1].x,ps2[ps2.size()-1].y), QPoint(ps2[0].x, ps2[0].y));
        }

        //        if(size>2&&widget1->completeRDefine == true){
        //            painter.drawLine(QPoint(ps[0].x,ps[0].y),QPoint(ps[size-1].x,ps[size-1].y));
        //        }


    }
    label->setScaledContents(true);
    label->setPixmap(pixmap1);
}

//加载图片到Label2上
void MainWindow::loadPictureToLabel2(boolean isRect, QRect qrect, Scalar co, QRect rectRegion, vector<Point> ps, vector<Region> rgs){
    //loadPictureToLabel(label2,imgLabel2);
    QPixmap pixmap1 = QPixmap::fromImage(imgLabel2);
    QPainter painter(&pixmap1);
    if(isRect){

        painter.setPen(QPen(Qt::red,4,Qt::SolidLine)); //设置画笔形式
        //painter.setBrush(QBrush(Qt::red,Qt::SolidPattern)); //设置画刷形式
        painter.drawRect(qrect);

    }
    if(isDefiningRegion){
        QColor qc = QColor();
        qc.setRed(co.val[2]);
        qc.setGreen(co.val[1]);
        qc.setBlue(co.val[0]);
        QPen pen;
        pen.setColor(qc);
        pen.setWidth(4);
        pen.setStyle(Qt::SolidLine);
        painter.setPen(pen);
        if(rectRegion.width() > 0){
            painter.drawRect(rectRegion);
        }

        int size = ps.size();
        for(int i = 0; i < size - 1; i++){
            QPoint p1 = QPoint(ps[i].x, ps[i].y);
            QPoint p2 = QPoint(ps[i+1].x, ps[i+1].y);
            painter.drawLine(p1,p2);
        }
        for(int i = 0; i < rgs.size(); i++){
            vector<Point> ps2 = rgs[i].getPoly();
            int size = ps2.size();
            for(int ii = 0; ii < size -1 ; ii++){
                QPoint p1 = QPoint(ps2[ii].x, ps2[ii].y);
                QPoint p2 = QPoint(ps2[ii+1].x, ps2[ii+1].y);
                painter.drawLine(p1,p2);
            }
            painter.drawLine(QPoint(ps2[ps2.size()-1].x,ps2[ps2.size()-1].y), QPoint(ps2[0].x, ps2[0].y));
        }
        //        if(size>2&&widget2->completeRDefine == true){
        //            painter.drawLine(QPoint(ps[0].x,ps[0].y),QPoint(ps[size-1].x,ps[size-1].y));
        //        }

    }
    label2->setScaledContents(true);
    label2->setPixmap(pixmap1);
}

//加载图片到Label3上
void MainWindow::loadPictureToLabel3(Scalar co, QRect rectRegion, vector<Point> ps, vector<Region> rgs){
    //loadPictureToLabel(label3,imgLabel3);
    QPixmap pixmap1 = QPixmap::fromImage(imgLabel3);
    QPainter painter(&pixmap1);
    if(isDefiningRegion){
        QColor qc = QColor();
        qc.setRed(co.val[2]);
        qc.setGreen(co.val[1]);
        qc.setBlue(co.val[0]);
        QPen pen;
        pen.setColor(qc);
        pen.setWidth(4);
        pen.setStyle(Qt::SolidLine);
        painter.setPen(pen);
        if(rectRegion.width() > 0){
            painter.drawRect(rectRegion);
        }
        int size = ps.size();
        for(int i = 0; i < size - 1; i++){
            QPoint p1 = QPoint(ps[i].x, ps[i].y);
            QPoint p2 = QPoint(ps[i+1].x, ps[i+1].y);
            painter.drawLine(p1,p2);
        }
        //qDebug()<<"rgs.size()="<<rgs.size();
        for(int i = 0; i < rgs.size(); i++){
            vector<Point> ps2 = rgs[i].getPoly();
            int size = ps2.size();
            //qDebug()<<"ps2.size()="<<size;
            for(int ii = 0; ii < size - 1 ; ii++){
                QPoint p1 = QPoint(ps2[ii].x, ps2[ii].y);
                QPoint p2 = QPoint(ps2[ii+1].x, ps2[ii+1].y);
                painter.drawLine(p1,p2);
            }
            painter.drawLine(QPoint(ps2[size-1].x,ps2[ps2.size()-1].y), QPoint(ps2[0].x, ps2[0].y));
        }
        //        if(size>2&&widget3->completeRDefine == true){
        //            painter.drawLine(QPoint(ps[0].x,ps[0].y),QPoint(ps[size-1].x,ps[size-1].y));
        //        }



    }

//    zWZoomIn->setText("放大");
//    zWZoomIn->setGeometry(10,10,60,30);
//    zWZoomIn->setToolTip(QString::number(3));
//    zWZoomout->setText("缩小");
//    zWZoomout->setGeometry(80,10,60,30);
//    zWZoomout->setToolTip(QString::number(3));
//    connect(zWZoomIn,SIGNAL(clicked()),this,SLOT(zoomIn()));
//    connect(zWZoomout,SIGNAL(clicked()),this,SLOT(zoomOut()));
    label3->setScaledContents(true);
    label3->setPixmap(pixmap1);

}

//加载图片到Label4上
void MainWindow::loadPictureToLabel4(Scalar co, QRect rectRegion, vector<Point> ps, vector<Region> rgs){
    //loadPictureToLabel(label4,imgLabel4);
    QPixmap pixmap1 = QPixmap::fromImage(imgLabel4);
    QPainter painter(&pixmap1);
    if(isDefiningRegion){
        QColor qc = QColor();
        qc.setRed(co.val[2]);
        qc.setGreen(co.val[1]);
        qc.setBlue(co.val[0]);
        QPen pen;
        pen.setWidth(4);
        pen.setColor(qc);
        pen.setStyle(Qt::SolidLine);
        painter.setPen(pen);
        if(rectRegion.width() > 0){
            painter.drawRect(rectRegion);

        }
        int size = ps.size();
        for(int i = 0; i < size- 1; i++){
            QPoint p1 = QPoint(ps[i].x, ps[i].y);
            QPoint p2 = QPoint(ps[i+1].x, ps[i+1].y);
            painter.drawLine(p1,p2);
        }
        for(int i = 0; i < rgs.size(); i++){
            vector<Point> ps2 = rgs[i].getPoly();
            int size = ps2.size();
            for(int ii = 0; ii < size - 1; ii++){
                QPoint p1 = QPoint(ps2[ii].x, ps2[ii].y);
                QPoint p2 = QPoint(ps2[ii+1].x, ps2[ii+1].y);
                painter.drawLine(p1,p2);
            }
            painter.drawLine(QPoint(ps2[ps2.size()-1].x,ps2[ps2.size()-1].y), QPoint(ps2[0].x, ps2[0].y));
        }
        //        if(size>2&&widget4->completeRDefine == true){
        //            painter.drawLine(QPoint(ps[0].x,ps[0].y),QPoint(ps[size-1].x,ps[size-1].y));
        //        }

    }

//    n1WZoomIn->setText("放大");
//    n1WZoomIn->setGeometry(10,10,60,30);
//    n1WZoomIn->setToolTip(QString::number(4));
//    n1WZoomout->setText("缩小");
//    n1WZoomout->setGeometry(80,10,60,30);
//    n1WZoomout->setToolTip(QString::number(4));
//    connect(n1WZoomIn,SIGNAL(clicked()),this,SLOT(zoomIn()));
//    connect(n1WZoomout,SIGNAL(clicked()),this,SLOT(zoomOut()));
    label4->setScaledContents(true);
    label4->setPixmap(pixmap1);

}

//加载图片到Label5上
void MainWindow::loadPictureToLabel5(){
    loadPictureToLabel(label5,imgLabel5);
}

//加载图片到Label6上
void MainWindow::loadPictureToLabel6(Scalar co, QRect rectRegion, vector<Point> ps, vector<Region> rgs){
    //loadPictureToLabel(label6,imgLabel6);
    QPixmap pixmap1 = QPixmap::fromImage(imgLabel6);
    QPainter painter(&pixmap1);

    if(isDefiningRegion){
        QColor qc = QColor();
        qc.setRed(co.val[2]);
        qc.setGreen(co.val[1]);
        qc.setBlue(co.val[0]);
        QPen pen;
        pen.setColor(qc);
        pen.setWidth(4);
        pen.setStyle(Qt::SolidLine);
        painter.setPen(pen);
        painter.drawRect(rectRegion);

        int size = ps.size();
        for(int i = 0; i < size- 1; i++){
            QPoint p1 = QPoint(ps[i].x, ps[i].y);
            QPoint p2 = QPoint(ps[i+1].x, ps[i+1].y);
            painter.drawLine(p1,p2);
        }

        for(int i = 0; i < rgs.size(); i++){
            vector<Point> ps2 = rgs[i].getPoly();
            int size = ps2.size();
            for(int ii = 0; ii < size - 1; ii++){
                QPoint p1 = QPoint(ps2[ii].x, ps2[ii].y);
                QPoint p2 = QPoint(ps2[ii+1].x, ps2[ii+1].y);
                painter.drawLine(p1,p2);
            }
            painter.drawLine(QPoint(ps2[ps2.size()-1].x,ps2[ps2.size()-1].y), QPoint(ps2[0].x, ps2[0].y));
        }

        //        if(size>2&&widget6->completeRDefine == true){
        //            painter.drawLine(QPoint(ps[0].x,ps[0].y),QPoint(ps[size-1].x,ps[size-1].y));
        //        }

    }
//    n2WZoomIn->setText("放大");
//    n2WZoomIn->setGeometry(10,10,60,30);
//    n2WZoomIn->setToolTip(QString::number(6));
//    n2WZoomout->setToolTip(QString::number(6));
//    n2WZoomout->setText("缩小");
//    n2WZoomout->setGeometry(80,10,60,30);
//    connect(n2WZoomIn,SIGNAL(clicked()),this,SLOT(zoomIn()));
//    connect(n2WZoomout,SIGNAL(clicked()),this,SLOT(zoomOut()));
    label6->setScaledContents(true);
    label6->setPixmap(pixmap1);

}

void MainWindow::loadPictureToLabel7(){
    loadPictureToLabel(label7,imgLabel7);
}
//---xiaotian   图像上绘制矩形框
void MainWindow::drawRecOnPic(Mat image, vector<Rectan> rectans){
    //在图像上画矩形。
    int num_objs = rectans.size();
    for (int i = 0; i < num_objs;i++)
    {
        Rect rect;
        rect.x = rectans[i].getX();
        rect.y = rectans[i].getY();
        rect.width = rectans[i].getWidth();
        rect.height = rectans[i].getHeight();
        rectangle(image,rect,Scalar(0,0,255),4,1,0);

        //  cv::cvtColor(image, image, CV_BGR2RGB);
    }
    // cv::cvtColor(image,image,CV_BGR2RGB);
    //QImage imglabel;
    //    imgLabel = MatToQImage(image);
    //    return imgLabel;

}

//绘制鼠标选取的矩形
void MainWindow::drawRecOnPic2(Mat image, Rect rect){
    //在图像上画矩形。
    rectangle(image,rect,Scalar(0,0,255),1,1,0);
    // cv::cvtColor(image, image, CV_BGR2RGB);
    //QImage imglabel;
    //    imgLabel = MatToQImage(image);
    //    //return imgLabel;
}

//---xiaotian  图像上绘制标尺和矩形框
void MainWindow::drawScaleAndRecOnPic(Mat image, vector<Rectan> rectans, double startw, double starth){
    //在图像上画矩形。
    int num_objs = rectans.size();
    for (int i = 0; i < num_objs;i++)
    {
        Rect rect;
        rect.x = rectans[i].getX();
        rect.y = rectans[i].getY();
        rect.width = rectans[i].getWidth();
        rect.height = rectans[i].getHeight();
        rectangle(image,rect,Scalar(0,0,255),4,1,0);
        //   cv::cvtColor(image, image, CV_BGR2RGB);
    }
    //在图像上画标尺
    paintScale(image,startw,starth);
    //  cv::cvtColor(image,image,CV_BGR2RGB);
    //QImage imglabel3;
    //    imgLabel = MatToQImage(image);
    //    return imgLabel;
}

//---xiaotian  图像上绘制多边形和圆
void MainWindow::drawCircleOnPic(Mat image, vector<Point> point, double x, double y){
    //在图像上画多边形
    int num_objs = point.size();
    for (int i = 0; i <num_objs;i+=2)
    {
        Point point1 = point[i];
        Point point2 = point[i+1];
        line(image,point1,point2,Scalar(255,255,0),1,8,0);
    }
    //在图像上画圆点
    paintCircle(image,x,y);
    //  cv::cvtColor(image,image,CV_BGR2RGB);
    //QImage imglabel;
    //    imgLabel = MatToQImage(image);
    //    return imgLabel;
}


//矩形
void MainWindow:: paintRectangle(Mat image,double x,double y,double width,double height)
{
    Rect rect;
    //QImage img;
    rect.x = x;
    rect.y = y;
    rect.width = width;
    rect.height = height;
    rectangle(image,rect,Scalar(0,0,255),4,1,0);
    //   cv::cvtColor(image, image, CV_BGR2RGB);
    //img = QImage((const unsigned char*)(image.data),image.cols,image.rows, image.cols*image.channels(),  QImage::Format_RGB888);
    //return img;
}
//圆
void MainWindow::paintCircle(Mat image,double x,double y)
{
    //QImage img;
    Point pointInterest;//特征点，用以画在图像中,画圆形点的圆心
    pointInterest.x=x;//特征点在图像中横坐标
    pointInterest.y=y;//特征点在图像中纵坐标
    circle(image, pointInterest, 2, Scalar(255, 0,0 ),-1,8,0);//在图像中画出特征点，2是圆的半径
    //img = QImage((const unsigned char*)(image.data),image.cols,image.rows, image.cols*image.channels(),  QImage::Format_RGB888);
    //return img;
}

//画标尺
void MainWindow::paintScale(Mat image,double startw,double starth)
{
    //QImage img;
    int c = image.cols/30;
    int r = image.rows/10;
    line(image,Point(0,0),Point(image.cols,0),Scalar(255,255,255),2,8,0);
    for(int t=startw; t<=startw+30; t++)
    {
        int i=t-startw;
        if(i%2 == 0){
            line(image,Point(i*c,0),Point(i*c,20),Scalar(255,255,255),2,8,0);
            //标尺上写字
            QString text = QString::number(t,10);
            string str = text.toStdString();
            putText(image,str,Point(i*c-10,50),FONT_HERSHEY_SIMPLEX,10,Scalar(255,255,255),5,8,0);
        }
        else{
            line(image,Point(i*c,0),Point(i*c,15),Scalar(255,255,255),2,8,0);
        }
    }
    line(image,Point(0,0),Point(0,image.rows),Scalar(255,255,255),2,8,0);
    for(int t=starth; t<=starth+10; t++)
    {
        int i=t-starth;
        if(i%2 == 0){
            line(image,Point(0,i*r),Point(20,i*r),Scalar(255,255,255),2,8,0);
            QString text2 = QString::number(t,10);
            string str2 = text2.toStdString();
            //putText(image,str2,Point(50,i*r+10),3,1,Scalar(255,255,255));
            putText(image,str2,Point(50,i*r+10),FONT_HERSHEY_SIMPLEX,10,Scalar(255,255,255),5,8,0);
        }
        else{
            line(image,Point(0,i*r),Point(15,i*r),Scalar(255,255,255),2,8,0);
        }
    }
    //return img;
}

cv::Mat MainWindow::QImageToMat(QImage image)
{
    cv::Mat mat;
    switch (image.format())
    {
    case QImage::Format_ARGB32:
    case QImage::Format_RGB32:
    case QImage::Format_ARGB32_Premultiplied:
        mat = cv::Mat(image.height(), image.width(), CV_8UC4, (void*)image.constBits(), image.bytesPerLine());
        break;
    case QImage::Format_RGB888:
        mat = cv::Mat(image.height(), image.width(), CV_8UC3, (void*)image.constBits(), image.bytesPerLine());
        cv::cvtColor(mat, mat, CV_BGR2RGB);
        break;
    case QImage::Format_Indexed8:
        mat = cv::Mat(image.height(), image.width(), CV_8UC1, (void*)image.constBits(), image.bytesPerLine());
        break;
    default:
        break;
    }

    return mat;
}

QImage MainWindow::MatToQImage(const cv::Mat& mat, QImage imgLabel)
{
    // 8-bits unsigned, NO. OF CHANNELS = 1
    if(mat.type() == CV_8UC1)
    {

        //QImage image(mat.cols, mat.rows, QImage::Format_Indexed8);

        imgLabel = QImage(mat.cols, mat.rows, QImage::Format_Indexed8);

        // Set the color table (used to translate colour indexes to qRgb values)
        imgLabel.setColorCount(256);
        for(int i = 0; i < 256; i++)
        {
            //image.setColor(i, qRgb(i, i, i));
            imgLabel.setColor(i, qRgb(i, i, i));
        }
        // Copy input Mat
        uchar *pSrc = mat.data;

        for(int row = 0; row < mat.rows; row ++)
        {
            //uchar *pDest = image.scanLine(row);
            uchar *pDest = imgLabel.scanLine(row);
            memcpy(pDest, pSrc, mat.cols);
            pSrc += mat.step;
        }
        //return image;
        return imgLabel;
    }
    // 8-bits unsigned, NO. OF CHANNELS = 3
    else if(mat.type() == CV_8UC3)
    {
        // Copy input Mat
        const uchar *pSrc = (const uchar*)mat.data;
        // Create QImage with same dimensions as input Mat
        //QImage image(pSrc, mat.cols, mat.rows, mat.step, QImage::Format_RGB888);
        imgLabel = QImage(pSrc, mat.cols, mat.rows, mat.step, QImage::Format_RGB888);
         //imgLabel.rgbSwapped();
        return imgLabel.rgbSwapped();

    }
    else if(mat.type() == CV_8UC4)
    {
        qDebug() << "CV_8UC4";
        // Copy input Mat
        const uchar *pSrc = (const uchar*)mat.data;
        // Create QImage with same dimensions as input Mat
        //QImage image(pSrc, mat.cols, mat.rows, mat.step, QImage::Format_ARGB32);
        imgLabel = QImage(pSrc, mat.cols, mat.rows, mat.step, QImage::Format_ARGB32);
        return imgLabel.copy();
    }
    else
    {
        qDebug() << "ERROR: Mat could not be converted to QImage.";
        return imgLabel;
    }
}

//启动/停止
void MainWindow::startStopFunction()
{
    //if(startStopSet=="./icon/1_2.png")
    //    if (isQidong)
    //    {
    //        startStop->setIcon(QPixmap("./icon/播放.png"));
    //        startStop->setToolTip("启动");
    //        //startStopSet="./icon/1_1.png";
    //        isQidong = false;
    //    }
    //    else
    //    {
    //        startStop->setIcon(QPixmap("./icon/1_1.png"));
    //        startStop->setToolTip("停止");
    //        isQidong = true;
    //        //startStopSet="./icon/1_2.png";
    //    }

}
//暂停/继续记录当前场景
void MainWindow::mstopFunction()
{
    //if(mstopSet=="./icon/2_2.png")
    if(isJixu)
    {
        mstop->setIcon(QPixmap("./iconUpdate/录像停.png"));

        mstop->setToolTip("暂停");
        isJixu = false;
        //mstopSet="./icon/2_1.png";
    }
    else
    {
        mstop->setIcon(QPixmap("./iconUpdate/录像.png"));
        mstop->setToolTip("开启");
        isJixu = true;
        //mstopSet="./icon/2_2.png";
        //        dialogLabel->setText(tr("Information Message Box"));
        //        QMessageBox::information(this,tr("红外全景系统"),tr("通过金老师SDK，实现监控继续。"));
    }

}
//执行非均匀性校正
void MainWindow::backFunction()
{
    //dialogLabel->setText(tr("Information Message Box"));
   // QMessageBox::information(this,tr("执行非均匀性校正"),tr("消除图像中的非均匀性亮度差，若是采用面阵传感器，减少拼接线两边的图像亮度差异，图像拼接算法的一个设置参数。继续努力。"));
}
//回放
void MainWindow::openFunction()
{
    if(is_open==true){
        startTimeSet->setTime(QTime::currentTime().addSecs(-300));
        stopTimeSet->setTime(QTime::currentTime());
        widgetNew->show();
        return;
    }
    dateEdit=new QDateEdit(QDate::currentDate());
    startTime=new QLabel(QWidget::tr("起始时间"));
    //开始时间选择框
    startTimeSet=new QTimeEdit(QTime::currentTime().addSecs(-300), this);
    //startTimeSet->setCalendarPopup(true);
    startTimeSet->setDisplayFormat("HH:mm:ss");
    //结束时间选择框
    stopTime=new QLabel(QWidget::tr("结束时间"));
    stopTimeSet=new QTimeEdit(QTime::currentTime(), this);
    //stopTimeSet->setCalendarPopup(true);
    stopTimeSet->setDisplayFormat("HH:mm:ss");
    queDing=new QPushButton("确定",this);
    connect(queDing,SIGNAL(clicked()),this,SLOT(queDingFunction()));
    quXiao=new QPushButton("取消",this);
    connect(quXiao,SIGNAL(clicked()),this,SLOT(quXiaoFunction()));
    //采用网格布局
    //gridLayout=new QGridLayout(this);
    gridLayout=new QGridLayout();
    gridLayout->addWidget(new QLabel(QWidget::tr("日期")));
    gridLayout->addWidget(dateEdit,0,1);
    gridLayout->addWidget(startTime,0,2);
    gridLayout->addWidget(startTimeSet,0,3);
    gridLayout->addWidget(stopTime,0,4);
    gridLayout->addWidget(stopTimeSet,0,6);

    gridLayout->addWidget(queDing,3,2);
    gridLayout->addWidget(quXiao,3,3);
    gridLayout->setAlignment(Qt::AlignCenter);

    if(is_open==false)
    {
        if(widgetNew!=NULL)
            delete widgetNew;
        widgetNew=new QWidget();
        is_open=true;
    }

    widgetNew->setWindowTitle("时间选择框");
    widgetNew->setLayout(gridLayout);
    widgetNew->setMinimumSize(QSize(600,150));
    widgetNew->setMaximumSize(QSize(600,150));
    widgetNew->move((QApplication::desktop()->width() - widgetNew->width())/2,
                    (QApplication::desktop()->height() - widgetNew->height())/2);
    widgetNew->setWindowFlags(Qt::WindowStaysOnTopHint);
    widgetNew->show();

}
void MainWindow::flushRecentVideo(){
    int size=video.size();
    int index=0;
    for(int i=size-1;i>=0;i--){
        QString txt=((QDate)videoDate.at(i)).toString("yyyy-MM-dd ");
        txt.append(((QTime)video.at(i)).toString("hh:mm:ss"));
        txt.append("~");
        txt.append(((QTime)videoEnd.at(i)).toString("hh:mm:ss"));
        videoAction[index]->setText(txt);
        videoAction[index++]->setVisible(true);
    }
}
void MainWindow::videoClick(){
    QAction *act=qobject_cast<QAction*>(sender());
    int index=act->data().toInt();
    qDebug()<<"video click "<<index;
    int size=video.size();
    index=size-1-index;//因为最近的放到第一位，最近的在queue里是最后一位
    if(backwindow!=0)
        delete backwindow;
    backwindow=new BackWindow(videoDate.at(index),video.at(index),videoEnd.at(index));
    qDebug()<<"time:   "<<((QTime)video.at(index)).toString("hh:mm:ss");
    backwindow->show();
}

void MainWindow::queDingFunction()
{
    dateTimeStart=startTimeSet->time();
    dateTimeStop=stopTimeSet->time();
    QDate date=dateEdit->date();
    // int start=(int)dateTimeStart.currentTime();
    // int stop=(int)dateTimeStop.currentTime();
    int dif=dateTimeStart.secsTo(dateTimeStop);
    if(date>QDate::currentDate())
    {
        QMessageBox::information(widgetNew,tr("警告"),tr("日期不能大于今天"));
        //        widgetNew->close();
        //        widgetNew->show();
        return;
    }
    if(dif==0)
    {
        QMessageBox::information(widgetNew,tr("警告"),tr("开始时间和结束时间相同"));
        widgetNew->close();
        widgetNew->show();
    }
    else if(dif<0)
    {
        QMessageBox::information(widgetNew,tr("警告"),tr("开始时间大于结束时间"));
        widgetNew->close();
        widgetNew->show();
    }
    else
    {
        //        if(video.size()<6){
        //            video.insert(dateTimeStart,dateTimeStart);
        //        }
        //        else{
        //            video<QTime> ::iterator it = video.end()-1;
        //            video.erase(it);
        //            video.insert(dateTimeStart,dateTimeStart);
        //        }
        if(video.size()<6){
            video.enqueue(dateTimeStart);
            videoEnd.enqueue(dateTimeStop);//recent
            videoDate.enqueue(date);
        }
        else{
            video.dequeue();
            videoEnd.dequeue();//recent
            video.enqueue(dateTimeStart);
            videoEnd.enqueue(dateTimeStop);
            videoDate.dequeue();
            videoDate.enqueue(date);
        }

        flushRecentVideo();//recent
        widgetNew->close();
        if(backwindow!=0)
            delete backwindow;
        backwindow=new BackWindow(date,dateTimeStart,dateTimeStop);
        backwindow->show();
    }

}
void MainWindow::quXiaoFunction()
{
    widgetNew->close();
}
//图像
//撤销手动对比度参数
void MainWindow::chexiaoFunction(){
    //QMessageBox::information(this,tr("撤销手动对比度参数"),tr("恢复到最后一次调整操作之前？继续努力。"));

}

//自动
void MainWindow::automFunction()
{
    isBright = false;
    isContrast = false;
    bright_TrackbarValue = 0;
    alpha_contrast = 100;
//    trackBar->setPosition(0);
//    strackBar->setPosition(100);
    //saturation1 = 100;
    isPseudo = false;
    inThread.alpha_contrast = this->alpha_contrast;
    inThread.bright_TrackbarValue = this->bright_TrackbarValue;
    inThread.isPseudo = this->isPseudo;
    adjustment();
}
void MainWindow::updateBright(Mat &mat1 )
{
    if(!isBright)
        return;
    for (int y = 0; y <mat1.rows; y++)
    {
        for (int x = 0; x < mat1.cols; x++)
        {
            for (int c = 0; c < 3; c++)
            {
                //new_image.at<Vec3b>(y, x)[c] = saturate_cast<uchar>(alpha*(image.at<Vec3b>(y, x)[c]) + beta);
                mat1.at<Vec3b>(y, x)[c] = saturate_cast<uchar>((mat1.at<Vec3b>(y, x)[c]) +  bright_TrackbarValue);
                if (mat1.at<Vec3b>(y, x)[c] > 255)
                {
                    mat1.at<Vec3b>(y, x)[c] = 255;
                }
            }
        }
    }
}
//增加亮度
void MainWindow::addBrightnessFunction()
{
    isBright = true;
    bright_TrackbarValue+=20;
    //adjustment();
    if(0 == bright_TrackbarValue ){
        isBright = false;
    }
    inThread.bright_TrackbarValue = this->bright_TrackbarValue;
    //trackBar->setWindowFlags(Qt::WindowStaysOnTopHint);
    // trackBar->setWindowTitle("亮度");
    //trackBar->show();
    //trackBar->setWindowFlags(Qt::WindowStaysOnTopHint);
    //trackBar->activateWindow();
    //trackBar->move(trackBar->x(),trackBar->y());
    //    if(brightnessSet=="./icon/7_1.png")
    //    {
    //        brightness->setIcon(QPixmap("./icon/7_1.png"));
    //        brightnessSet="./icon/7_1.png";
    //    }
    //    else
    //    {
    //        brightness->setIcon(QPixmap("./icon/7_1.png"));
    //        brightnessSet="./icon/7_1.png";
    //    }
}

//降低亮度
void MainWindow::reduceBrightnessFunction()
{
    isBright = true;
    bright_TrackbarValue-=20;
    if(0 == bright_TrackbarValue ){
        isBright = false;
    }
    inThread.bright_TrackbarValue = this->bright_TrackbarValue;
    //adjustment();
    //    trackBar->setWindowFlags(Qt::WindowStaysOnTopHint);
    //    trackBar->setWindowTitle("亮度");
    //    trackBar->show();

    //    //trackBar->activateWindow();
    //    trackBar->move(trackBar->x(),trackBar->y());
    //    if(brightnessSet=="./icon/7_1.png")
    //    {
    //        brightness->setIcon(QPixmap("./icon/7_1.png"));
    //        brightnessSet="./icon/7_1.png";
    //    }
    //    else
    //    {
    //        brightness->setIcon(QPixmap("./icon/7_1.png"));
    //        brightnessSet="./icon/7_1.png";
    //    }
}

void MainWindow::updateContrast(Mat &mat1){
    if(!isContrast)
        return;

    for (int y = 0; y < mat1.rows; y++)
    {
        for (int x = 0; x < mat1.cols; x++)
        {
            for (int c = 0; c < 3; c++)
            {
                //new_image.at<Vec3b>(y, x)[c] = saturate_cast<uchar>(alpha*(image.at<Vec3b>(y, x)[c]) + beta);
                //new_image.at<Vec3b>(y, x)[c] = saturate_cast<uchar>((image.at<Vec3b>(y, x)[c]) + beta_value);
                mat1.at<Vec3b>(y, x)[c] = saturate_cast<uchar>(0.01*alpha_contrast*(mat1.at<Vec3b>(y, x)[c]));

                if (mat1.at<Vec3b>(y, x)[c] > 255)
                {
                    mat1.at<Vec3b>(y, x)[c] = 255;
                }
            }
        }
    }

}
//增加对比度
void MainWindow::addSaturationFunction()
{
    isContrast = true;
    alpha_contrast+=20;
    if(100 == alpha_contrast ){
        isContrast = false;
    }
    inThread.alpha_contrast = this->alpha_contrast;
    //adjustment();
    //    strackBar->setWindowFlags(Qt::WindowStaysOnTopHint);
    //    strackBar->setWindowTitle("对比度");
    //    strackBar->show();
    //    strackBar->activateWindow();
    //    strackBar->move(strackBar->x(),strackBar->y());

    //    if(saturationSet=="./icon/8_1.png")
    //    {
    //        saturation->setIcon(QPixmap("./icon/8_1.png"));
    //        saturationSet="./icon/8_1.png";
    //    }
    //    else
    //    {
    //        saturation->setIcon(QPixmap("./icon/8_1.png"));
    //        saturationSet="./icon/8_1.png";
    //    }
}

//降低对比度
void MainWindow::reduceSaturationFunction()
{
    isContrast = true;
    alpha_contrast-=20;
    if(100 == alpha_contrast ){
        isContrast = false;
    }
    inThread.alpha_contrast = this->alpha_contrast;
    //adjustment();
    //    strackBar->setWindowFlags(Qt::WindowStaysOnTopHint);
    //    strackBar->setWindowTitle("对比度");
    //    strackBar->show();
    //    strackBar->activateWindow();
    //    strackBar->move(strackBar->x(),strackBar->y());

    //    if(saturationSet=="./icon/8_1.png")
    //    {
    //        saturation->setIcon(QPixmap("./icon/8_1.png"));
    //        saturationSet="./icon/8_1.png";
    //    }
    //    else
    //    {
    //        saturation->setIcon(QPixmap("./icon/8_1.png"));
    //        saturationSet="./icon/8_1.png";
    //    }
}
//伪彩色
void MainWindow::pseudoColorFunction()
{
    isPseudo=!isPseudo;
    inThread.isPseudo = this->isPseudo;
    adjustment();
}


void MainWindow::targetAttShow(){
        if(objectAttributes)
        {
            delete objectAttributes;
        }
        this->objectAttributes=new ObjectAttributes(widget1->objs);
        this->objectAttributes->setWindowFlags(Qt::FramelessWindowHint);
        this->objectAttributes->activateWindow();
        //this->objectAttributes->setWindowTitle("目标属性列表");
        QDesktopWidget* desktopWidget = QApplication::desktop();
        QRect screenRect = desktopWidget->screenGeometry();  //屏幕区域
        int width = screenRect.width();
        int height = screenRect.height();
        this->objectAttributes->setGeometry(width/4,height/4,width/2,height/3);
        this->objectAttributes->show();

}

//第三组
//显示点击处位置
void MainWindow::objectAttributeFunction()
{
    //dialogLabel->setText(tr("Information Message Box"));
    //const QString &objectstring = "oid =" ;
    // QMessageBox::information(this,"目标属性列表",&objectstring);
    //    if(objectAttributes)
    //    {
    //        delete objectAttributes;
    //    }
    //    this->objectAttributes=new ObjectAttributes(widget1->objs);
    //    this->objectAttributes->setWindowFlags(Qt::FramelessWindowHint);
    //    this->objectAttributes->activateWindow();
    //    //this->objectAttributes->setWindowTitle("目标属性列表");
    //    QDesktopWidget* desktopWidget = QApplication::desktop();
    //    QRect screenRect = desktopWidget->screenGeometry();  //屏幕区域
    //    int width = screenRect.width();
    //    int height = screenRect.height();
    //    this->objectAttributes->setGeometry(width/4,height/4,width/2,height/3);

    //    // this->objectAttributes->tr("oid");
    //    // this->objectAttributes->resize(300,500);
    //    //this->objectAttributes->setText("oid=: ");
    //    //this->objectAttributes->setText("cenPoint");
    //    //QString s=QString("oid:")+myobjects.oid+"\n目标中心坐标:<"+myobjects.cenPoint.x+","+myobjects.cenPoint.y
    //    //            +">/n监测框大小:<"+myobjects.blocksize.width+","+myobjects.blocksize.height;
    //    //QString s1=QString(">\n运动速率:")+myobjects.Velocity
    //    //            +"\n运动方向："+myobjects.MotionDerection+"\n目标面积:"+myobjects.area+"\n水平轴长度:"+myobjects.horizontalAxisLength
    //    //            +"\n竖直轴长度:"+myobjects.verticalAxisLength+"\n绝对强度:"+myobjects.absoluteIntensity+"\n相对强度"+myobjects.relativeIntensity
    //    //            +"\n目标尺度:"+myobjects.targetScale+"\n中央周围对比度的相应强度:"+myobjects.CenSueEintensity+"\n目标背景信杂比"+myobjects.SCRValue;
    //    //    qDebug()<<"22222222222";
    //    //    this->objectAttributes->setText(s);
    //    //    this->objectAttributes->show();
    //    this->objectribuAtttes->show();

    location = !location;
    if(location){
        objectAttribute->setToolTip(tr("关闭显示点击处的位置信息"));
    }
    if(!location){
        objectAttribute->setToolTip(tr("开启显示点击处的位置信息"));
    }
    //QMessageBox::information(this,tr("显示点击处位置"),tr("鼠标在条带显示区左键点击时，显示位置信息，需要定位或标定？继续努力。"));
}

//启用垂直稳定图像
void MainWindow::stabilityFunction(){
    //QMessageBox::information(this,tr("启用垂直稳定图像"),tr("启用垂直稳定图像。继续努力！"));
}

//增加标签
void MainWindow::manualFunction()
{
    //dialogLabel->setText(tr("Information Message Box"));
    //QMessageBox::information(this,tr("增加标签"),tr("增加标签？啥意思？继续努力。"));

    //    string imageurl="./s1/1.bmp";
    //    Mat mat1 =imread(imageurl);
    //    Rect rectan;
    //    rectan.x=1690;// = Rect(1490,250,100,100);
    //    rectan.y=350;
    //    rectan.width=200;
    //    rectan.height=200;

    //    //MainWindow *mw = (MainWindow*)parentWidget();
    //    //mw->test();

    //    drawRecOnPic2(mat1,rectan);
    //    cv::cvtColor(mat1, mat1, CV_BGR2RGB);
    //    loadPictureToLabel1();
    if(this->isMubiao){
        this->isMubiao = false;
        for(int i = 0; i < this->rgs.size(); i++){
            this->rgs[i].isDrawLabel = false;
        }
    }
    else{
        this->isMubiao = true;
        for(int i = 0; i < this->rgs.size(); i++){
            this->rgs[i].isDrawLabel = true;
        }
    }

}


//告警
//启用/禁用探测功能
void MainWindow::openCloseFunction()
{
    isGaojing = !isGaojing;
//    QPixmap pixmap1("./iconUpdate/报警灯-红.png");
//    QPixmap pixmap2("./iconUpdate/报警灯-绿.png");
    QPixmap pixmap3("./iconUpdate/自动探测.png");
    QPixmap pixmap4("./iconUpdate/自动探测off.png");
    //      fitpixmap1=pixmap1.scaled(buttonSize,buttonSize, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    //      fitpixmap2=pixmap2.scaled(buttonSize,buttonSize, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);

    if(isGaojing){
        //light->setIcon(pixmap1);
        openClose->setIcon(pixmap3);
    }else{
        //light->setIcon(pixmap2);
        openClose->setIcon(pixmap4);
    }
    //    QDesktopWidget* desktopWidget = QApplication::desktop();
    //    QRect screenRect = desktopWidget->screenGeometry();
    //    const int buttonSize=(screenRect.width()*0.7)/21.6;
    //    QPixmap pixmap1("./icon/16_1.png");
    //    QPixmap pixmap2("./icon/16_2.png");
    //    fitpixmap1=pixmap1.scaled(buttonSize,buttonSize, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    //    fitpixmap2=pixmap2.scaled(buttonSize,buttonSize, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    //    //vector<MyObject> vec = in.getObjs2();
    //   // vector<MyObject> vec = in.getObjs();
    //    if(isGaojing)
    //    {
    //        openClose->setIcon(QPixmap("./icon/11_1.png"));
    //        openClose->setToolTip("关闭告警");
    //        if(num_objs==0)
    //        {
    //            lights[0]->setPixmap(fitpixmap2);
    //            lights[1]->setPixmap(fitpixmap2);
    //            lights[2]->setPixmap(fitpixmap2);
    //            lights[3]->setPixmap(fitpixmap2);
    //            lights[4]->setPixmap(fitpixmap2);
    ////            light1->setPixmap(fitpixmap2);
    ////            light2->setPixmap(fitpixmap2);
    ////            light3->setPixmap(fitpixmap2);
    ////            light4->setPixmap(fitpixmap2);
    ////            light5->setPixmap(fitpixmap2);
    //        }
    //        else if(num_objs==1)
    //        {
    //            lights[0]->setPixmap(fitpixmap1);
    //            lights[1]->setPixmap(fitpixmap2);
    //            lights[2]->setPixmap(fitpixmap2);
    //            lights[3]->setPixmap(fitpixmap2);
    //            lights[4]->setPixmap(fitpixmap2);
    ////            light1->setPixmap(fitpixmap1);
    ////            light2->setPixmap(fitpixmap2);
    ////            light3->setPixmap(fitpixmap2);
    ////            light4->setPixmap(fitpixmap2);
    ////            light5->setPixmap(fitpixmap2);
    //        }
    //        else if(num_objs==2)
    //        {
    //            lights[0]->setPixmap(fitpixmap1);
    //            lights[1]->setPixmap(fitpixmap1);
    //            lights[2]->setPixmap(fitpixmap2);
    //            lights[3]->setPixmap(fitpixmap2);
    //            lights[4]->setPixmap(fitpixmap2);
    ////            light1->setPixmap(fitpixmap1);
    ////            light2->setPixmap(fitpixmap1);
    ////            light3->setPixmap(fitpixmap2);
    ////            light4->setPixmap(fitpixmap2);
    ////            light5->setPixmap(fitpixmap2);
    //        }
    //        else if(num_objs==3)
    //        {
    //            lights[0]->setPixmap(fitpixmap1);
    //            lights[1]->setPixmap(fitpixmap1);
    //            lights[2]->setPixmap(fitpixmap1);
    //            lights[3]->setPixmap(fitpixmap2);
    //            lights[4]->setPixmap(fitpixmap2);
    ////            light1->setPixmap(fitpixmap1);
    ////            light2->setPixmap(fitpixmap1);
    ////            light3->setPixmap(fitpixmap1);
    ////            light4->setPixmap(fitpixmap2);
    ////            light5->setPixmap(fitpixmap2);
    //        }
    //        else if(num_objs==4)
    //        {
    //            lights[0]->setPixmap(fitpixmap1);
    //            lights[1]->setPixmap(fitpixmap1);
    //            lights[2]->setPixmap(fitpixmap1);
    //            lights[3]->setPixmap(fitpixmap1);
    //            lights[4]->setPixmap(fitpixmap2);
    ////            light1->setPixmap(fitpixmap1);
    ////            light2->setPixmap(fitpixmap1);
    ////            light3->setPixmap(fitpixmap1);
    ////            light4->setPixmap(fitpixmap1);
    ////            light5->setPixmap(fitpixmap2);
    //        }
    //        else if(num_objs>= 5 )
    //        {
    //            lights[0]->setPixmap(fitpixmap1);
    //            lights[1]->setPixmap(fitpixmap1);
    //            lights[2]->setPixmap(fitpixmap1);
    //            lights[3]->setPixmap(fitpixmap1);
    //            lights[4]->setPixmap(fitpixmap1);
    ////            light1->setPixmap(fitpixmap1);
    ////            light2->setPixmap(fitpixmap1);
    ////            light3->setPixmap(fitpixmap1);
    ////            light4->setPixmap(fitpixmap1);
    ////            light5->setPixmap(fitpixmap1);
    //      }
    //    }
    //    else
    //    {
    //        openClose->setIcon(QPixmap("./icon/11_2.png"));
    //        openClose->setToolTip("打开告警");

    //        lights[0]->setPixmap(fitpixmap2);
    //        lights[1]->setPixmap(fitpixmap2);
    //        lights[2]->setPixmap(fitpixmap2);
    //        lights[3]->setPixmap(fitpixmap2);
    //        lights[4]->setPixmap(fitpixmap2);
    ////        light1->setPixmap(fitpixmap2);
    ////        light2->setPixmap(fitpixmap2);
    ////        light3->setPixmap(fitpixmap2);
    ////        light4->setPixmap(fitpixmap2);
    ////        light5->setPixmap(fitpixmap2);
    //   }
    //QMessageBox::information(this,tr("启用/禁用探测功能"),tr("启动或关闭告警。继续努力。"));
}

//调整探测灵敏度等级
void MainWindow::objectsFunction()
{
        isSensi = !isSensi;
        if(senAdjust == NULL)
            senAdjust = new Sensitivity(this);

        senAdjust->setWindowFlags(Qt::ToolTip);
        senAdjust->activateWindow();
       //senAdjust->move(senAdjust->x(),senAdjust->y());
        //qDebug()<<"senAdjust"<<senAdjust->x()<<" "<<senAdjust->y();
//        QDesktopWidget *desktop= QApplication::desktop();
//        QRect screenRect = desktop->screenGeometry();
//        int width = screenRect.width();
//        int height = screenRect.height();
//        senAdjust->move(13*width/20-5,height/10);
senAdjust->move(objects->parentWidget()->x()+objects->x()+0.3*objects->width(),mainToolBar->y()+mainToolBar->height());
        if(isSensi)
            senAdjust->show();
        else
            senAdjust->hide();
    //    //if(objectSet=="./icon/13_2.png")
    //    if(isMubiao)
    //    {
    //        objects->setIcon(QPixmap("./icon/13_1.png"));
    //        isMubiao = false;
    //        //objectSet="./icon/13_1.png";
    //        objects->setToolTip("开启目标属性跟随");
    //    }
    //    else
    //    {
    //        objects->setIcon(QPixmap("./icon/13_1.png"));
    //        isMubiao = true;
    //        //objectSet="./icon/13_2.png";
    //        objects->setToolTip("关闭目标属性跟随");
    //    }
   // QMessageBox::information(this,tr("调整探测灵敏度等级"),tr("调整探测灵敏度就是目标识别的阈值。继续努力。"));
}
//目标属性列表
void MainWindow::lightFunction()
{
    //QMessageBox::information(this,tr("属性设置界面，有待实现。"),tr("继续努力。"));
}
//声音
void MainWindow::voiceFunction()
{

    //if(voiceSet=="./icon/15_2.png")
    isVoice = !isVoice;
    //cmixer->SetMute(isVoice);
    //if(isVoice == false)
//        this->sound->play();
    //     QImage icon;
    //     icon = QImage("./icon/15_1.png");
    //    Mat micon;
    //    micon =  QImageToMat(icon);
    //    cv::cvtColor(micon, micon, CV_RGB2GRAY);
    //icon = QImage((unsigned char*)micon.data,micon.cols,micon.rows,micon.step,QImage::Format_RGB16);

    if(isShengyin)
    {
        voice->setIcon(QPixmap("./iconUpdate/告警音开关.png"));
        isShengyin = false;
        //voiceSet="./icon/15_1.png";
        voice->setToolTip("打开声音");
    }
    else
    {
        voice->setIcon(QPixmap("./iconUpdate/告警音开.png"));
        isShengyin = true;
        //voiceSet="./icon/15_2.png";
        voice->setToolTip("关闭声音");

       // QMediaPlayer mp;
        //mp.setMedia(QUrl::fromLocalFile("E:\\github\\Qt\\1.mp3"));
        mp.setMedia(QUrl::fromLocalFile("./1.mp3"));
        mp.setVolume(100);
        mp.play();

    }
}

void MainWindow::exitFunction(){
    QApplication::closeAllWindows();
}

//退出系统事件
void MainWindow::closeEvent(QCloseEvent *event)
{
    writeRgs();
}

//void MainWindow::adjustbrightness()
//{
//    //    QImage a = ImageDeal.AdjustBrightness(QImage Img, int iBrightValue);
//}

void MainWindow::test()
{
    QMessageBox::information(this,tr("属性设置界面，有待实现。"),tr("继续努力。"));
}

void MainWindow :: timeLineFunction(){}


void MainWindow::flash(){
    //    static bool flag = false;
    //    if(num_objs-newObjCount<5){
    //        for(addOneLight=0;addOneLight<newObjCount;addOneLight++){
    //            if(num_objs+addOneLight-newObjCount>4)
    //                break;
    //            else{
    //                if(flag)
    //                   lights[num_objs+addOneLight-newObjCount]->setPixmap(fitpixmap1);
    //                else
    //                   lights[num_objs+addOneLight-newObjCount]->setPixmap(fitpixmap2);
    //            }
    //        }
    //    }else{
    //        if(flag)
    //             lights[4]->setPixmap(fitpixmap1);
    //        else
    //             lights[4]->setPixmap(fitpixmap2);
    //    }
    //    flag = !flag;
    //
}
//菜单栏槽函数
void MainWindow::connectionClicked(){
    //QMessageBox::information(this,tr("连接菜单项"),tr("单播方式连接相机。继续努力。"));
}

void MainWindow::connectionplusClicked(){
    //QMessageBox::information(this,tr("连接...菜单项"),tr("多播方式连接相机？连接相机前做一系列动作？继续努力。"));

}

void MainWindow::disconnectionClicked(){
    //QMessageBox::information(this,tr("断开菜单项"),tr("断开与相机的连接。继续努力。"));

}

void MainWindow::openplusClicked(){
    openFunction();
    //QMessageBox::information(this,tr("打开...菜单项"),tr("打开保存的记录文件，作为回放起点。继续努力。"));

}

void MainWindow::backplusClicked(){
    //QMessageBox::information(this,tr("回放菜单项"),tr("回放菜单项。继续努力。"));

}

void MainWindow::closeClicked(){
//    timer->stop();
//    timerSysTime->stop();
//    timerFlash->stop();
    if(backwindow){
        this->close();
//        delete backwindow;
//        backwindow = 0;
    }
    //this->close();
    // QMessageBox::information(this,tr("关闭菜单项"),tr("关闭回放的文件窗口，返回实时。继续努力。"));

}

void MainWindow::recentvidioClicked(){
    //      videoMenu = new QMenu();
    //      videoMenu->addActions()
    //    backwindow=new BackWindow(date,dateTimeStart,dateTimeStop);
    //    backwindow->show();
    // QMessageBox::information(this,tr("最近视频菜单项"),tr("保存若干个最近播放的视频文件。继续努力。"));

}

void MainWindow::changeuserClicked(){
    //in = MyInterface();
    hide();
    welcome->show();
    //QMessageBox::information(this,tr("切换用户菜单项"),tr("支持用户登录，有用户登录界面，替代原有的欢迎界面，设置默认用户名/口令。继续努力。"));

}

void MainWindow::installationClicked(){
    QMessageBox::information(this,tr("启动安装向导菜单项"),tr("重新安装本软件。继续努力。"));

}

void MainWindow::exitClicked(){
    writeRgs();
    QApplication::closeAllWindows();

}

void MainWindow::configurationClicked(){
    if(configure == NULL){
        configure = new Configuration(this);
    }
    this->configure->setWindowTitle(QString("配置"));
    this->configure->activateWindow();
    QDesktopWidget *desktop= QApplication::desktop();
    QRect screenRect = desktop->screenGeometry();
    int width = screenRect.width();
    int height = screenRect.height();
    //this->configure->setGeometry(width/4,height/4,850,height/3);
    this->configure->setGeometry(width/4,height/8,600,640);
    qDebug()<<"configure.height"<<configure->height();
    this->configure->show();
    this->configure->configure();
//    if(welcome!=0){
//        welcome->close();

//        this->show();//BackWindow的show是由mainwindow中指定代码调用的
//    }
    //QMessageBox::information(this,tr("配置...菜单项"),tr("根据我们的实际情况，包括相机参数、转台参数、检测算法参数、软件参数，定位参数等的设置。继续努力。"));
}

void MainWindow::saveconfigurationClicked(){
   // QMessageBox::information(this,tr("保存当前设置菜单项"),tr("将设置中设置的参数保存在配置文件中。继续努力。"));

}

void MainWindow::regionClicked(){
    //isDefiningRegion = true;

    if(monitor == NULL){
        monitor = new Monitor(this);
    }
    //this->monitor->setWindowFlags(/*Qt::WindowStaysOnTopHint|*/Qt::FramelessWindowHint);
    this->monitor->setWindowTitle(QString("创建或编辑区域"));
    this->monitor->activateWindow();
    QDesktopWidget *desktop= QApplication::desktop();
    QRect screenRect = desktop->screenGeometry();
    int width = screenRect.width();
    int height = screenRect.height();
    this->monitor->setGeometry(screenRect.x(),height/4,4*width/6,3*height/5);
    //this->monitor->setGeometry(screenRect.x(),height/4,width,3*height/5);
    this->monitor->show();
    this->monitor->widgetShow();
//    qDebug()<<"monitor main width"<<monitor->geometry().width();
//    qDebug()<<"monitor main height"<<monitor->geometry().height();
    // QMessageBox::information(this,tr("创建或编辑区域菜单项"),tr("在告警区域的设置窗口中，完成对应的设置以后，包括分组、组颜色、等级等，在条带显示区和主显示区完成告警区域的实际绘制，支持两种形状：矩形和不规则多边形。并实现告警区域的保存。继续努力。"));
    isOpenMonitor = true;
}

void MainWindow::figureClicked(){
    QString capture = QString("./屏幕截图");
    bool exist = directory->exists(capture);
    if(!exist){
        directory->mkdir(capture);
    }
    QString filename = QString("./屏幕截图/")+QDateTime::currentDateTime().toString("yyyy年MM月dd日hh时mm分ss秒")+".bmp";

//    QDesktopWidget* desktopWidget = QApplication::desktop();
//    QRect screenRect = desktopWidget->screenGeometry();

    QPixmap pix;
    //    pix = QPixmap::grabWindow(QApplication::desktop()->winId(),widget1->x(),menubar->y()+widget1->y(),widget6->x()+widget6->width()-widget1->x(),widget6->y()+widget6->height()-widget1->y());
    //pix = QPixmap::grabWindow(QApplication::desktop()->winId(),0,0,widget6->x()+widget6->width(),widget6->y()+widget6->height());
   RECT rect;
   SystemParametersInfo(SPI_GETWORKAREA,0,&rect,0);
   pix=QPixmap::grabWindow(QApplication::desktop()->winId(),rect.left,rect.top,rect.right,rect.bottom );
   qDebug()<<rect.left<<"  left";
   qDebug()<<rect.top<<"   top";
   qDebug()<<rect.right<<" right";
   qDebug()<<rect.bottom<<"  bottom";
   int width  = GetSystemMetrics(SM_CXSCREEN);
   int height = GetSystemMetrics(SM_CYSCREEN);
   qDebug()<<width<<"  width";
   qDebug()<<height<<"  height";
    if(pix.save(filename,"bmp")){
        QMessageBox::information(this,"屏幕截图","截屏保存成功！",QMessageBox::Ok);
    }
}

void MainWindow::openalertClicked(){
    isGaojing = true;
//    QPixmap pixmap1("./iconUpdate/报警灯-红.png");
//    light->setIcon(pixmap1);
    QPixmap pixmap2("./iconUpdate/自动探测.png");
    openClose->setIcon(pixmap2);
    //QMessageBox::information(this,tr("打开报警信息菜单项"),tr("打开报警信息。继续努力。"));

}

void MainWindow::closealertClicked(){
    isGaojing = false;
//    QPixmap pixmap2("./iconUpdate/报警灯-绿.png");
//    light->setIcon(pixmap2);
    QPixmap pixmap3("./iconUpdate/自动探测off.png");
    openClose->setIcon(pixmap3);
   // QMessageBox::information(this,tr("隐藏报警信息菜单项"),tr("隐藏报警信息。继续努力。"));

}

void MainWindow::helpClicked(){
   // QMessageBox::information(this,tr("帮助菜单项"),tr("打开帮助文档。继续努力。"));

}

void MainWindow::aboutClicked(){
   // QMessageBox::information(this,tr("关于菜单项"),tr("富吉瑞公司及本产品简介。继续努力。"));

}
void MainWindow::readRgs(){
    QFile file(QString("./config/rgs.config"));
    if(!file.exists())
        return;
    //qDebug()<<"readconf";
    file.open(QIODevice::ReadOnly);
    QDataStream in(&file);
    int size;
    in>>size;
     //qDebug()<<"readconf222";
    for(int i=0;i<size;i++){
        RegionGroup *rg = new RegionGroup();
        Scalar color;
        in>>color.val[0];
        in>>color.val[1];
        in>>color.val[2];
        in>>rg->name;
        in>>rg->isActive;
        in>>rg->isAlert;

        int regionSize;
        in>>regionSize;

        for(int k=0;k<7;k++){
            for(int p=0;p<48;p++){
                in>>rg->timeActive[k][p];
            }
        }

        for(int j=0;j<regionSize;j++){
            Region *r = new Region();
            in>>r->name;
            in>>r->hasObjects;
            in>>r->isActive;
            in>>r->isRect;
            if(r->isRect){
                in>>r->rect.x;
                in>>r->rect.y;
                in>>r->rect.width;
                in>>r->rect.height;
            }else{
                int polySize;
                in>>polySize;
                for(int k=0;k<polySize;k++){
                    Point p;
                    in>>p.x;
                    in>>p.y;
                    r->poly.push_back(p);
                }
            }
            rg->addRegion(*r);
        }
        rg->setColor(color);
        rgs.push_back(*rg);
    }
    file.close();
}

void MainWindow::writeLogs(){

}

void MainWindow::writeRgs(){
    int size = rgs.size();//最后一个是未完成的监控组
    if(size <= 1)
        return;
    QFile file(QString("./config/rgs.config"));
    file.open(QIODevice::WriteOnly);
    QDataStream out(&file);

    out<<size-1;
    for(int i=0;i < size-1;i++){
        out<<rgs[i].color.val[0];
        out<<rgs[i].color.val[1];
        out<<rgs[i].color.val[2];
        out<<rgs[i].name;
        out<<rgs[i].isActive;
        out<<rgs[i].isAlert;
        int size2 = rgs[i].rs.size();
        out<<size2;

        for(int k=0;k<7;k++){
            for(int p=0;p<48;p++){
                out<<rgs[i].timeActive[k][p];
            }
        }


        for(int j=0;j<rgs[i].rs.size();j++){
            out<<rgs[i].rs[j].name;
            out<<rgs[i].rs[j].hasObjects;
            out<<rgs[i].rs[j].isActive;
            out<<rgs[i].rs[j].isRect;
            if(rgs[i].rs[j].isRect){
                out<<rgs[i].rs[j].rect.x;
                out<<rgs[i].rs[j].rect.y;
                out<<rgs[i].rs[j].rect.width;
                out<<rgs[i].rs[j].rect.height;
            }else{
                size2 = rgs[i].rs[j].poly.size();
                out<<size2;
                for(int k=0;k<rgs[i].rs[j].poly.size();k++){
                    out<<rgs[i].rs[j].poly[k].x;
                    out<<rgs[i].rs[j].poly[k].y;
                }
            }
        }
    }
    file.flush();
    file.close();
}

void MainWindow::alertInformation(){
    qDebug()<<"alert....";
    this->onAlertTimer();
    if(showAlert->isActive()){
        showAlert->stop();
    }

    showAlert->setSingleShot(true);
    showAlert->start(5000);
    connect(showAlert,SIGNAL(timeout()),SLOT(onAlertTimer()));
    if(alert == NULL){
        alert = new Alert(this,widget1->getObjects());
    }

    this->alert->setWindowFlags(Qt::FramelessWindowHint);
    this->alert->activateWindow();
    QDesktopWidget *desktop= QApplication::desktop();
    QRect screenRect = desktop->screenGeometry();
    int width = screenRect.width();
    int height = screenRect.height();
    this->alert->setGeometry(8.5*width/10,height/10,width/10,height/10);
    if(isGaojing){
        this->alert->show();
        this->alert->alertInfo();

    }
}

void MainWindow::onAlertTimer(){
    if(alert){
        delete alert;
        alert=0;
    }
}

void MainWindow::zoomInitial3(){
    this->widget3->ZoomInitial();
}

void MainWindow::zoomIn3(){
    this->widget3->ZoomIn();
}

void MainWindow::zoomOut3(){
    this->widget3->ZoomOut();
}

void MainWindow::zoomInitial4(){
    this->widget4->ZoomInitial();
}

void MainWindow::zoomIn4(){
    this->widget4->ZoomIn();
}

void MainWindow::zoomOut4(){
    this->widget4->ZoomOut();
}
void MainWindow::zoomInitial6(){
    this->widget6->ZoomInitial();
}

void MainWindow::zoomIn6(){
    this->widget6->ZoomIn();
}

void MainWindow::zoomOut6(){
    this->widget6->ZoomOut();
}
//void MainWindow::zoomInitial(){
//    QObject *obj = sender();
//    QToolButton *button = dynamic_cast<QToolButton*>(obj);
//    int index = button->toolTip().toInt();
//    if(index==3){
//        this->widget3->ZoomInitial();
//    }else if(index == 4){
//        this->widget4->ZoomInitial();
//    }
//    else if(index == 6){
//        this->widget6->ZoomInitial();
//    }

//}

//void MainWindow::zoomIn(){
//    qDebug()<<"main:zoomIN";
//    QObject* obj = sender();
//    QToolButton* button = dynamic_cast<QToolButton*>(obj);
//    int index = button->toolTip().toInt();
//    if(index==3){
//        this->widget3->ZoomIn();
//    }
//    else if(index == 4){
//        this->widget4->ZoomIn();
//    }
//    else if(index == 6){
//        this->widget6->ZoomIn();
//    }
//}


//void MainWindow::zoomOut(){

//    QObject* obj = sender();
//    QToolButton* button = dynamic_cast<QToolButton*>(obj);
//    int index = button->toolTip().toInt();
//    if(index==3){
//        this->widget3->ZoomOut();
//    }
//    else if(index == 4){
//        this->widget4->ZoomOut();
//    }
//    else if(index == 6){
//        this->widget6->ZoomOut();
//    }
//}

long long MainWindow::getMemory(const  QString  &path){
    memoryUnit = "k";
    QDir dir(path);
    if(!dir.exists())
        return 0;
    long long allM = 0;

    foreach(QFileInfo fileinfo,dir.entryInfoList(QDir::Files) ){
        allM += fileinfo.size();
        qDebug()<<"allM::::"<<allM;
        qDebug()<<fileinfo.baseName();
    }

    foreach(QString subdir,dir.entryList(QDir::Dirs|QDir::NoDotAndDotDot)){
        allM += getMemory(path+QDir::separator()+subdir);
    }

    if(0 == allM && path!=QString("./回放/")){
        dir.rmdir(dir.absolutePath());
    }

    return allM;
}

void MainWindow::removeFile(const  QString  &path){
    QDir dir(path);
    if(!dir.exists())
        return;

    if(!dir.entryInfoList(QDir::Files).isEmpty()){
        QFileInfo fileinfo =dir.entryInfoList(QDir::Files).first();
        qDebug()<<fileinfo.fileName();
        if(fileinfo.absoluteDir().remove(fileinfo.fileName())){
            unitSize-=fileinfo.size();
        }
    }

    foreach(QString subdir,dir.entryList(QDir::Dirs|QDir::NoDotAndDotDot)){
        removeFile(path+QDir::separator()+subdir);
    }


}
