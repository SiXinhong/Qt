#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qj1widget.h"
#include "qj2widget.h"
#include "zwidget.h"
#include "nwidget.h"
#include "hwidget.h"
#include "lwidget.h"
#include "myinterface.h"
#include "myobject.h"
#include "mixer.h"
#include "cvutil.h"
#include <QDesktopWidget>
#include "imagedeal.h"

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
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    widgetNew=NULL;
    this->setWindowFlags(Qt::FramelessWindowHint);
   // this->objectAttributes=new ObjectAttributes(&this->in);
    this->objectAttributes = 0;
    cmixer = new CMixer();
    sound = new QSound("E:\github\Qt\1.mp3",this);
    color = 0;
    //saturation1 = 100;
    //hsl=new HSL();
    bright_TrackbarValue=0;
    alpha_contrast = 100;
    //objectAttributes = new QLabel();
    isPseudo = false;
    isVoice = false;
    //设置属性设置中的变量的默认值-------------------------------
    //启动还是停止
    isQidong = true;
    //暂停还是继续
    isJixu = true;
    //告警启动还是关闭
    isGaojing = true;
    //声音打开还是关闭
    isShengyin = true;
    //目标属性是否跟随
    isMubiao = true;
    //系统编号
    xtbh = QString("BJ036A战位");
    //-------------------------------------------------------
    //判断窗口是否打开
    is_open=false;


    ui->setupUi(this);
    QWidget* widget = new QWidget(this);

    //widget10 = new QWidget(this);
    widget1 = new Qj1Widget(new QWidget(this));
    widget2 = new Qj2Widget(new QWidget(this));
    widget3 = new ZWidget(new QWidget(this));
    widget4 = new NWidget(new QWidget(this));
    widget5 = new HWidget(new QWidget(this));
    widget6 = new LWidget(new QWidget(this));

    label=new QLabel(widget1);
    label2=new QLabel(widget2);
    label3=new QLabel(widget3);
    label4=new QLabel(widget4);
    label5=new QLabel(widget5);
    label6=new QLabel(widget6);

    //鼠标拖拽控制变量赋初值
    isDrag1 = false;
    isDrag2 = false;
    isMove = false;

    ////////////////zc///////////////////////
    //通信连接
    MySocketInitial();

    //自定义接口处理，将来被金老师SDK替换--------------------------------
    in = MyInterface();
    //selfProcessing();
    this->jinProcessing();
    //---------------------------------------------------------

    //临时性处理，将来被金老师SDK替换--------------------------------
    //tempProcessing();
    //---------------------------------------------------------
    //定时器
    timer=new QTimer();
    timer->setInterval(3000);
    timer->start();
    connect(timer, SIGNAL(timeout()), SLOT(onTimerOut()));
    //定时器，获取系统时间

    timerSysTime=new QTimer();
    timerSysTime->setInterval(1000);
    timerSysTime->start();
    connect(timerSysTime, SIGNAL(timeout()), SLOT(onTimerOut2()));

    timerFlash = new QTimer();
    timerFlash->setInterval(100);
    connect(timerFlash, SIGNAL(timeout()), SLOT(flash()));

    // 创建工具栏
    addMyToolBar();
    //布局
    gridlayout = new QGridLayout;
    mainToolBar->setStyleSheet("background-color:#2E302D");
    gridlayout->addWidget(mainToolBar,0,0,1,3);
    gridlayout->addWidget(widget1,1,0,1,3);
    gridlayout->addWidget(widget2,2,0,1,3);
    gridlayout->addWidget(widget3,3,0,1,3);
    gridlayout->addWidget(widget4,4,0);
    gridlayout->addWidget(widget5,4,1);
    gridlayout->addWidget(widget6,4,2);

    gridlayout->setRowStretch(0, 1);
    gridlayout->setRowStretch(1, 1);
    gridlayout->setRowStretch(2, 1);
    gridlayout->setRowStretch(3, 6);
    gridlayout->setRowStretch(4, 5);

    gridlayout->setColumnStretch(0,3);
    gridlayout->setColumnStretch(1,1);
    gridlayout->setColumnStretch(2,1);


    widget->setLayout(gridlayout);
    this->setCentralWidget(widget);

    this->setWindowState(Qt::WindowMaximized);
    this->trackBar=new TrackBar(this);
    this->strackBar = new STrackBar(this);


}

MainWindow::~MainWindow(){
    delete ui;
    // delete hsl;
    delete strackBar;
    delete trackBar;
    if( objectAttributes)
        delete objectAttributes;
    delete cmixer;
    delete sound;
}

//与金老师的接口处理
void MainWindow::jinProcessing(){
    int v=in.getIntegratedData();
    if(v == 0){
        //std::cout<<"getintegrated data "<<std::endl;
        //图片1
        //        QString s1=in.getQJ1();
        //        imageurl=s1.toStdString();
        //        //qDebug()<<in.getObjs().size();
        //在全景上画矩形，文字，轨迹等
        //在两个全景上画矩形，文字，轨迹等
        QString today=QString("./回放/")+QDate::currentDate().toString("yyyy-MM-dd");
        QDir *todayDir=new QDir();
        bool exist=todayDir->exists(today);
        if(!exist){
            todayDir->mkdir(today);
        }
        delete todayDir;

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
        //Mat mat = in.getPano().clone();
        vector<MyObject> objs = in.getObjs();
        for(int i=0;i<objs.size();i++){
            QString current_time=QTime::currentTime().toString("hh-mm-ss");
            QString current_path=QString("").append(today).append("/").append(current_time).append("-").append(QString::number(i)).append(".dat");
            QFile file(current_path);
            if(isJixu == true){
                file.open(QIODevice::WriteOnly);
                QDataStream out(&file);
                out<<objs.at(i);
                file.close();
            }
            current_time.clear();
            current_path.clear();
        }

        vector<MyObjectTrack> tracks = in.getTracks();

        int num_objs = objs.size();
        for (int i = 0; i < num_objs;i++)
        {
            //画对象的box
            MyObject obj = objs[i];
            Rect rect2 = Rect(obj.getRect().x+pano.cols, obj.getRect().y, obj.getRect().width, obj.getRect().height);
            rectangle(mat,obj.getRect(),obj.getColor(),2,1,0);
            rectangle(mat,rect2,obj.getColor(),2,1,0);
           // cv::cvtColor(mat, mat, CV_BGR2RGB);
    
            //画轨迹
            if(isMubiao){
            for(int ii = 0; ii < tracks.size(); ii++){
                MyObjectTrack track = tracks[ii];
                int id = track.getId();
                vector<Point> points = track.getTrack();
                if(id == obj.getID()){
                    for(int iii = 0; iii < points.size(); iii++){
                        Point point = points[iii];
                        Point point2 = Point(point.x+pano.cols, point.y);
                        circle(mat, point, 2, obj.getColor(),-1,8,2);//在图像中画出特征点，2是圆的半径
                        circle(mat, point2, 2, obj.getColor(),-1,8,2);//在图像中画出特征点，2是圆的半径
                        if(iii >= 1){
                            Point point3 = points[iii-1];
                            Point point4 = Point(point3.x+pano.cols, point3.y);
                            line(mat,point,point3,obj.getColor(),1,8,0);
                            line(mat,point2,point4,obj.getColor(),1,8,0);
                        }
                       // cv::cvtColor(mat, mat, CV_BGR2RGB);
                    }
                }
            }
           }
            //画对象中心点的位置
            if(isMubiao){
                int x = (int)(this->getDirectionX(obj.getCenPoint().x, pano));
                int y = (int)(10-this->getDirectionY(obj.getCenPoint().y, pano)/2);//(10-10*(this->getDirectionY(obj.getCenPoint().y)-this->getDirectionY())/(this->getDirectionY2()-this->getDirectionY()));//endh - i*(endh-starth)/10
                QString tx = QString::number(x,10);
                QString ty = QString::number(y,10);
                QString tstr = "x="+tx+",y="+ty;
                string str = tstr.toStdString();
                //qDebug()<<tstr;
                Point p = Point(obj.getRect().x+obj.getRect().width,obj.getRect().y+obj.getRect().height);
                Point p2 = Point(obj.getRect().x+obj.getRect().width+pano.cols,obj.getRect().y+obj.getRect().height);
    
                putText(mat,str,p,3,0.5,obj.getColor());
                putText(mat,str,p2,3,0.5,obj.getColor());
                        }
           // cv::cvtColor(mat, mat, CV_BGR2RGB);
        }
       // cv::cvtColor(mat, mat, CV_BGR2RGB);

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
        widget1->setObjects(objs);
        widget1->setTracks(in.getTracks());
        widget1->draw();
        //图片2
        widget2->setPano(newpano);
        widget2->setMat(mat2);
        widget2->setObjects(objs);
        widget2->setTracks(in.getTracks());
        widget2->draw();
        //qDebug()<<s2;
        //drawUiLabel(mat2,2);
        //图片3
        //Mat mat3 =imread(imageurl);
        widget3->setPano(newpano);
        widget3->setTwoPanos(mat);
        widget3->setAllObjects(in.getObjs());
        widget3->draw();
        //drawUiLabelByCopy(mat3,3);
        //图片4
        //Mat mat4 =imread(imageurl2);
        //drawUiLabelByCopy(mat4,4);
        widget4->setPano(newpano);
        widget4->setTwoPanos(mat);
        widget4->setAllObjects(in.getObjs());
        widget4->draw();
        //图片5
        widget5->setPano(pano);
        QString imageurl5=in.getHD();
        Mat mat5 =imread(imageurl5.toStdString());
        widget5->setMat(mat5);
        widget5->setObjects(objs);
        widget5->draw();
        //图片6
        QString imageurl6= in.getLD();
        Mat mat6 =imread(imageurl6.toStdString());
        widget6->setMat(mat6);
        widget6->setPano(pano);
        widget6->setObjects(objs);
        widget6->draw();
    }
    else{
        QMessageBox::information(this,tr("接口返回值"),QString::number(v,10));
        this->selfProcessing();

    }
}

//自定义接口处理函数，将来被金老师SDK替换------------------------------
void MainWindow::selfProcessing(){
    QString today=QString("./回放/")+QDate::currentDate().toString("yyyy-MM-dd");
    QDir *todayDir=new QDir();
    bool exist=todayDir->exists(today);
    if(!exist){
        todayDir->mkdir(today);
    }
    delete todayDir;

    in.getIntegratedData2();
    vector<MyObject> objs = in.getObjs2();
   num_objs =objs.size();
   // num_objs =0;
    for(int i=0;i<objs.size();i++){
        QString current_time=QTime::currentTime().toString("hh-mm-ss");
        QString current_path=QString("").append(today).append("/").append(current_time).append("-").append(QString::number(i)).append(".dat");
        QFile file(current_path);
        if(isJixu == true){
            file.open(QIODevice::WriteOnly);
            QDataStream out(&file);
            out<<objs.at(i);
            file.close();
        }
        current_time.clear();
        current_path.clear();
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

    Mat pano1 = pano.clone();
    Mat pano2 = pano.clone();
    Mat mat;
    hconcat(pano1,pano2,mat);

    //在全景上画矩形，文字，轨迹等
    //Mat mat = in.getPano().clone();
    //vector<MyObject> objs = in.getObjs();
    vector<MyObjectTrack> tracks = in.getTracks();

    for (int i = 0; i < num_objs;i++)
    {
        //画对象的box
        MyObject obj = objs[i];
        Rect rect2 = Rect(obj.getRect().x+pano.cols, obj.getRect().y, obj.getRect().width, obj.getRect().height);
        rectangle(mat,obj.getRect(),obj.getColor(),2,1,0);
        rectangle(mat,rect2,obj.getColor(),2,1,0);
       // cv::cvtColor(mat, mat, CV_BGR2RGB);

        //画轨迹
        if(isMubiao){
        for(int ii = 0; ii < tracks.size(); ii++){
            MyObjectTrack track = tracks[ii];
            int id = track.getId();
            vector<Point> points = track.getTrack();
            if(id == obj.getID()){
                for(int iii = 0; iii < points.size(); iii++){
                    Point point = points[iii];
                    Point point2 = Point(point.x+pano.cols, point.y);
                    circle(mat, point, 2, obj.getColor(),-1,8,2);//在图像中画出特征点，2是圆的半径
                    circle(mat, point2, 2, obj.getColor(),-1,8,2);//在图像中画出特征点，2是圆的半径
                    if(iii >= 1){
                        Point point3 = points[iii-1];
                        Point point4 = Point(point3.x+pano.cols, point3.y);
                        line(mat,point,point3,obj.getColor(),1,8,0);
                        line(mat,point2,point4,obj.getColor(),1,8,0);
                    }
                   // cv::cvtColor(mat, mat, CV_BGR2RGB);
                }
            }
        }
       }
        //画对象中心点的位置
        if(isMubiao){
            int x = (int)(this->getDirectionX(obj.getCenPoint().x, pano));
            int y = (int)(10-this->getDirectionY(obj.getCenPoint().y, pano)/2);//(10-10*(this->getDirectionY(obj.getCenPoint().y)-this->getDirectionY())/(this->getDirectionY2()-this->getDirectionY()));//endh - i*(endh-starth)/10
            QString tx = QString::number(x,10);
            QString ty = QString::number(y,10);
            QString tstr = "x="+tx+",y="+ty;
            string str = tstr.toStdString();
            //qDebug()<<tstr;
            Point p = Point(obj.getRect().x+obj.getRect().width,obj.getRect().y+obj.getRect().height);
            Point p2 = Point(obj.getRect().x+obj.getRect().width+pano.cols,obj.getRect().y+obj.getRect().height);

            putText(mat,str,p,3,0.5,obj.getColor());
            putText(mat,str,p2,3,0.5,obj.getColor());
                    }
       // cv::cvtColor(mat, mat, CV_BGR2RGB);
    }
    //cv::cvtColor(mat, mat, CV_BGR2RGB);

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
    if(this->isPseudo==true)
        mat=setPseudocolor(mat);
    updateBright(mat);
    updateContrast(mat);

    Mat mat1, mat2;
    mat(Rect(mat.cols/2,0,mat.cols/4,mat.rows)).copyTo(mat1);
    mat(Rect(mat.cols/4,0,mat.cols/4,mat.rows)).copyTo(mat2);

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
    widget1->setMat(mat1);
    widget1->setPano(newpano);
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
    if(this->isPseudo==true)
                        mat2=setPseudocolor(mat2);
        updateBright(mat2);
        updateContrast(mat2);
//        if(saturation1!=100){
//               hsl->channels[color].saturation1 = saturation1 - 100;
//               hsl->adjust(mat2, mat2);
//           }
    widget2->setPano(newpano);
//    if(this->isPseudo==true)
//        mat2=setPseudocolor(mat2);
//    updateBright(mat2);
//    updateContrast(mat2);
    //        if(saturation1!=100){
    //               hsl->channels[color].saturation1 = saturation1 - 100;
    //               hsl->adjust(mat2, mat2);
    //           }
    //widget2->setPano(mat);
    widget2->setMat(mat2);
    widget2->setObjects(objs);
    widget2->setTracks(in.getTracks());
    widget2->draw();
    //qDebug()<<s2;
    //drawUiLabel(mat2,2);
    //图片3
    //Mat mat3 =imread(imageurl);
    widget3->setPano(newpano);
    widget3->setTwoPanos(mat);
    widget3->setAllObjects(in.getObjs());
    widget3->draw();
    //drawUiLabelByCopy(mat3,3);
    //图片4
    //Mat mat4 =imread(imageurl2);
    //drawUiLabelByCopy(mat4,4);
    widget4->setPano(newpano);
    widget4->setTwoPanos(mat);
    widget4->setAllObjects(in.getObjs());
    widget4->draw();
    //图片5
    widget5->setPano(pano);
    QString imageurl5=in.getHD();
    Mat mat5 =imread(imageurl5.toStdString());
    widget5->setMat(mat5);
    widget5->setObjects(objs);
    widget5->draw();
    //图片6
    QString imageurl6= in.getLD();
    Mat mat6 =imread(imageurl6.toStdString());
    widget6->setMat(mat6);
    widget6->setPano(pano);
    widget6->setObjects(objs);
    widget6->draw();

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



//绘制工具栏
void MainWindow::addMyToolBar()
{

    //图标太大导致在小屏幕上显示不全，改为按照屏幕宽度自动调整图标的大小
    QDesktopWidget* desktopWidget = QApplication::desktop();
    QRect screenRect = desktopWidget->screenGeometry();  //屏幕区域
    int screenWidth=screenRect.width();
//    qDebug()<<screenWidth;
//    qDebug()<<screenRect.height();
    const int buttonSize=(screenWidth*0.7)/21.6;

    QGroupBox *group1=new QGroupBox(this);
    QGroupBox *group2=new QGroupBox(this);
    QGroupBox *group3=new QGroupBox(this);
    QGroupBox *group4=new QGroupBox(this);
    QGroupBox *group5=new QGroupBox(this);
    QGroupBox *group6=new QGroupBox(this);

    QHBoxLayout *vbox1 = new QHBoxLayout;
    QHBoxLayout *vbox2 = new QHBoxLayout;
    QHBoxLayout *vbox3 = new QHBoxLayout;
    QVBoxLayout *vbox4 = new QVBoxLayout;
    QHBoxLayout *vbox5 = new QHBoxLayout;
    QHBoxLayout *vbox6 = new QHBoxLayout;

    mainToolBar = addToolBar("monitoring");

    //加图标
    //mainToolBar->addWidget(new QLabel(""));
    QPixmap pixmap3("./icon/fujirui.png");
    QPixmap fitpixmap3=pixmap3.scaled(buttonSize*1.7,buttonSize*1.7, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    QLabel *tuBiao=new QLabel(this);
    tuBiao->setPixmap(fitpixmap3);
    mainToolBar->addWidget(tuBiao);
    mainToolBar->addWidget(new QLabel(" "));
    //第一组按钮：监控和后退，还有回放
    //启动/停止

    startStop = new QToolButton(this);
    startStop->setToolTip(tr("停止"));
    startStop->setMinimumHeight(buttonSize);
    startStop->setMaximumHeight(buttonSize);
    startStop->setMinimumWidth(buttonSize);
    startStop->setMaximumWidth(buttonSize);
    startStop->setStyleSheet("border-style:flat;background-color:2E302D");
    startStopSet="./icon/1_1.png";
    startStop->setIcon(QPixmap(startStopSet));
    startStop->setIconSize(QSize(buttonSize,buttonSize));
    vbox1->addWidget(startStop);
    connect(startStop,SIGNAL(clicked()),this,SLOT(startStopFunction()));
    //vbox1->addWidget(new QLabel(" "));

    //暂停/继续
    mstop = new QToolButton(this);
    mstop->setToolTip(tr("暂停"));
    mstop->setMinimumHeight(buttonSize);
    mstop->setMaximumHeight(buttonSize);
    mstop->setMinimumWidth(buttonSize);
    mstop->setMaximumWidth(buttonSize);
    mstop->setStyleSheet("border-style:flat;background-color:2E302D");
    mstopSet="./icon/2_1.png";
    mstop->setIcon(QPixmap(mstopSet));
    mstop->setIconSize(QSize(buttonSize,buttonSize));
    vbox1->addWidget(mstop);
    connect(mstop,SIGNAL(clicked()),this,SLOT(mstopFunction()));
    //vbox1->addWidget(new QLabel(" "));

    //后退
    back = new QToolButton(this);
    back->setToolTip(tr("后退"));
    back->setMinimumHeight(buttonSize);
    back->setMaximumHeight(buttonSize);
    back->setMinimumWidth(buttonSize);
    back->setMaximumWidth(buttonSize);
    back->setStyleSheet("border-style:flat;background-color:2E302D");
    backSet="./icon/19.png";
    back->setIcon(QPixmap(backSet));
    back->setIconSize(QSize(buttonSize,buttonSize));
    vbox1->addWidget(back);
    connect(back,SIGNAL(clicked()),this,SLOT(backFunction()));
    //vbox1->addWidget(new QLabel(" "));

    //回放
    open = new QToolButton(this);
    open->setToolTip(tr("回放"));
    open->setMinimumHeight(buttonSize);
    open->setMaximumHeight(buttonSize);
    open->setMinimumWidth(buttonSize);
    open->setMaximumWidth(buttonSize);
    open->setStyleSheet("border-style:flat;background-color:2E302D");
    openSet="./icon/3_1.png";
    open->setIcon(QPixmap(openSet));
    open->setIconSize(QSize(buttonSize,buttonSize));
    vbox1->addWidget(open);
    connect(open,SIGNAL(clicked()),this,SLOT(openFunction()));

    group1->setLayout(vbox1);
    mainToolBar->addWidget(group1);
    //mainToolBar->addWidget(new QLabel("    "));
    //第二组按钮：图像
    //自动
    autom = new QToolButton(this);
    autom->setToolTip(tr("自动"));
    autom->setMinimumHeight(buttonSize);
    autom->setMaximumHeight(buttonSize);
    autom->setMinimumWidth(buttonSize);
    autom->setMaximumWidth(buttonSize);
    autom->setStyleSheet("border-style:flat;background-color:2E302D");
    automSet="./icon/6_1.png";
    autom->setIcon(QPixmap(automSet));
    autom->setIconSize(QSize(buttonSize,buttonSize));
    vbox2->addWidget(autom);
    connect(autom,SIGNAL(clicked()),this,SLOT(automFunction()));
    //vbox2->addWidget(new QLabel(" "));

    //亮度
    brightness = new QToolButton(this);
    brightness->setToolTip(tr("亮度"));
    brightness->setMinimumHeight(buttonSize);
    brightness->setMaximumHeight(buttonSize);
    brightness->setMinimumWidth(buttonSize);
    brightness->setMaximumWidth(buttonSize);
    brightness->setStyleSheet("border-style:flat;background-color:2E302D");
    brightnessSet="./icon/7_1.png";
    brightness->setIcon(QPixmap(brightnessSet));
    brightness->setIconSize(QSize(buttonSize,buttonSize));
    vbox2->addWidget(brightness);
    connect(brightness,SIGNAL(clicked()),this,SLOT(brightnessFunction()));
    //vbox2->addWidget(new QLabel(" "));

    //对比度
    saturation = new QToolButton(this);
    saturation->setToolTip(tr("对比度"));
    saturation->setMinimumHeight(buttonSize);
    saturation->setMaximumHeight(buttonSize);
    saturation->setMinimumWidth(buttonSize);
    saturation->setMaximumWidth(buttonSize);
    saturation->setStyleSheet("border-style:flat;background-color:2E302D");
    saturationSet="./icon/8_1.png";
    saturation->setIcon(QPixmap(saturationSet));
    saturation->setIconSize(QSize(buttonSize,buttonSize));
    vbox2->addWidget(saturation);
    connect(saturation,SIGNAL(clicked()),this,SLOT(saturationFunction()));
    //vbox2->addWidget(new QLabel(" "));

    //伪彩色
    pseudoColor = new QToolButton(this);
    pseudoColor->setToolTip(tr("伪彩色"));
    pseudoColor->setMinimumHeight(buttonSize);
    pseudoColor->setMaximumHeight(buttonSize);
    pseudoColor->setMinimumWidth(buttonSize);
    pseudoColor->setMaximumWidth(buttonSize);
    pseudoColor->setStyleSheet("border-style:flat;background-color:2E302D");
    pseudoColorSet="./icon/9_1.png";
    pseudoColor->setIcon(QPixmap(pseudoColorSet));
    pseudoColor->setIconSize(QSize(buttonSize,buttonSize));
    vbox2->addWidget(pseudoColor);
    connect(pseudoColor,SIGNAL(clicked()),this,SLOT(pseudoColorFunction()));

    group2->setLayout(vbox2);
    mainToolBar->addWidget(group2);
    //mainToolBar->addWidget(new QLabel("    "));

    //第三组按钮，指示灯，五盏，一个目标一盏红灯；二个目标二盏红灯；三个目标三盏红灯；四个目标四盏红灯；五个目标及以上，五盏红灯
    QPixmap pixmap1("./icon/16_1.png");
    QPixmap pixmap2("./icon/16_2.png");
    fitpixmap1=pixmap1.scaled(buttonSize,buttonSize, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    fitpixmap2=pixmap2.scaled(buttonSize,buttonSize, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);

    vector<MyObject> vec = in.getObjs2();

    lights[0]=new QLabel(this);
    lights[1]=new QLabel(this);
    lights[2]=new QLabel(this);
    lights[3]=new QLabel(this);
    lights[4]=new QLabel(this);

//    light1=new QLabel(this);
//    light2=new QLabel(this);
//    light3=new QLabel(this);
//    light4=new QLabel(this);
//    light5=new QLabel(this);

    if(!isGaojing)
    {
        lights[0]->setPixmap(fitpixmap2);
        lights[1]->setPixmap(fitpixmap2);
        lights[2]->setPixmap(fitpixmap2);
        lights[3]->setPixmap(fitpixmap2);
        lights[4]->setPixmap(fitpixmap2);
//        light1->setPixmap(fitpixmap2);
//        light2->setPixmap(fitpixmap2);
//        light3->setPixmap(fitpixmap2);
//        light4->setPixmap(fitpixmap2);
//        light5->setPixmap(fitpixmap2);
    }
    else
    {
        if(vec.size()==0)
        {


            lights[0]->setPixmap(fitpixmap2);
            lights[1]->setPixmap(fitpixmap2);
            lights[2]->setPixmap(fitpixmap2);
            lights[3]->setPixmap(fitpixmap2);
            lights[4]->setPixmap(fitpixmap2);
//            light1->setPixmap(fitpixmap2);
//            light2->setPixmap(fitpixmap2);
//            light3->setPixmap(fitpixmap2);
//            light4->setPixmap(fitpixmap2);
//            light5->setPixmap(fitpixmap2);
        }
        else if(vec.size()==1)
        {
            lights[0]->setPixmap(fitpixmap1);
            lights[1]->setPixmap(fitpixmap2);
            lights[2]->setPixmap(fitpixmap2);
            lights[3]->setPixmap(fitpixmap2);
            lights[4]->setPixmap(fitpixmap2);
//            light1->setPixmap(fitpixmap1);
//            light2->setPixmap(fitpixmap2);
//            light3->setPixmap(fitpixmap2);
//            light4->setPixmap(fitpixmap2);
//            light5->setPixmap(fitpixmap2);
        }
        else if(vec.size()==2)
        {

            lights[0]->setPixmap(fitpixmap1);
            lights[1]->setPixmap(fitpixmap1);
            lights[2]->setPixmap(fitpixmap2);
            lights[3]->setPixmap(fitpixmap2);
            lights[4]->setPixmap(fitpixmap2);
//            light1->setPixmap(fitpixmap1);
//            light2->setPixmap(fitpixmap1);
//            light3->setPixmap(fitpixmap2);
//            light4->setPixmap(fitpixmap2);
//            light5->setPixmap(fitpixmap2);
        }
        else if(vec.size()==3)
        {

            lights[0]->setPixmap(fitpixmap1);
            lights[1]->setPixmap(fitpixmap1);
            lights[2]->setPixmap(fitpixmap1);
            lights[3]->setPixmap(fitpixmap2);
            lights[4]->setPixmap(fitpixmap2);
//            light1->setPixmap(fitpixmap1);
//            light2->setPixmap(fitpixmap1);
//            light3->setPixmap(fitpixmap1);
//            light4->setPixmap(fitpixmap2);
//            light5->setPixmap(fitpixmap2);
        }
        else if(vec.size()==4)
        {

            lights[0]->setPixmap(fitpixmap1);
            lights[1]->setPixmap(fitpixmap1);
            lights[2]->setPixmap(fitpixmap1);
            lights[3]->setPixmap(fitpixmap1);
            lights[4]->setPixmap(fitpixmap2);
//            light1->setPixmap(fitpixmap1);
//            light2->setPixmap(fitpixmap1);
//            light3->setPixmap(fitpixmap1);
//            light4->setPixmap(fitpixmap1);
//            light5->setPixmap(fitpixmap2);
        }
        else if(vec.size()>= 5 )
        {

            lights[0]->setPixmap(fitpixmap1);
            lights[1]->setPixmap(fitpixmap1);
            lights[2]->setPixmap(fitpixmap1);
            lights[3]->setPixmap(fitpixmap1);
            lights[4]->setPixmap(fitpixmap1);
//            light1->setPixmap(fitpixmap1);
//            light2->setPixmap(fitpixmap1);
//            light3->setPixmap(fitpixmap1);
//            light4->setPixmap(fitpixmap1);
//            light5->setPixmap(fitpixmap1);

        }
    }
    vbox3->addWidget(lights[0]);
    vbox3->addWidget(lights[1]);
    vbox3->addWidget(lights[2]);
    vbox3->addWidget(lights[3]);
    vbox3->addWidget(lights[4]);

    group3->setLayout(vbox3);
    mainToolBar->addWidget(group3);
    //mainToolBar->addWidget(new QLabel("    "));

    //第四组，显示编号和系统当前时间
    serialNumber=new QLabel("    位置："+xtbh);//编号
    serialNumber->setStyleSheet("color:White");
    vbox4->addWidget(serialNumber);
    //vbox4->addWidget(new QLabel("   "));
    systime=new QLabel(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss ddd"));//时间
    systime->setStyleSheet("color:White");
    vbox4->addWidget(systime);
    //vbox4->addWidget(new QLabel("   "));

    group4->setLayout(vbox4);
    mainToolBar->addWidget(group4);
    //mainToolBar->addWidget(new QLabel("    "));

    //第五组，告警
    //关闭告警
    openClose = new QToolButton(this);
    openClose->setToolTip(tr("关闭告警"));
    openClose->setMinimumHeight(buttonSize);
    openClose->setMaximumHeight(buttonSize);
    openClose->setMinimumWidth(buttonSize);
    openClose->setMaximumWidth(buttonSize);
    openClose->setStyleSheet("border-style:flat;background-color:2E302D");
    openCloseSet="./icon/11_1.png";
    openClose->setIcon(QPixmap(openCloseSet));
    openClose->setIconSize(QSize(buttonSize,buttonSize));
    vbox5->addWidget(openClose);
    connect(openClose,SIGNAL(clicked()),this,SLOT(openCloseFunction()));
    //vbox5->addWidget(new QLabel(" "));

    //对象属性
    objectAttribute = new QToolButton(this);
    objectAttribute->setToolTip(tr("对象属性"));
    objectAttribute->setMinimumHeight(buttonSize);
    objectAttribute->setMaximumHeight(buttonSize);
    objectAttribute->setMinimumWidth(buttonSize);
    objectAttribute->setMaximumWidth(buttonSize);
    objectAttribute->setStyleSheet("border-style:flat;background-color:2E302D");
    objectAttributeSet="./icon/17_1.png";
    objectAttribute->setIcon(QPixmap(objectAttributeSet));
    objectAttribute->setIconSize(QSize(buttonSize,buttonSize));
    vbox5->addWidget(objectAttribute);
    connect(objectAttribute,SIGNAL(clicked()),this,SLOT(objectAttributeFunction()));
    //vbox5->addWidget(new QLabel(" "));

    //手动
    manual = new QToolButton(this);
    manual->setToolTip(tr("手动"));
    manual->setMinimumHeight(buttonSize);
    manual->setMaximumHeight(buttonSize);
    manual->setMinimumWidth(buttonSize);
    manual->setMaximumWidth(buttonSize);
    manual->setStyleSheet("border-style:flat;background-color:2E302D");
    manualSet="./icon/12_1.png";
    manual->setIcon(QPixmap(manualSet));
    manual->setIconSize(QSize(buttonSize,buttonSize));
    vbox5->addWidget(manual);
    connect(manual,SIGNAL(clicked()),this,SLOT(manualFunction()));
    //vbox5->addWidget(new QLabel(" "));

    //关闭目标属性跟随
    objects = new QToolButton(this);
    objects->setToolTip(tr("关闭目标属性跟随"));
    objects->setMinimumHeight(buttonSize);
    objects->setMaximumHeight(buttonSize);
    objects->setMinimumWidth(buttonSize);
    objects->setMaximumWidth(buttonSize);
    objects->setStyleSheet("border-style:flat;background-color:2E302D");
    objectSet="./icon/13_1.png";
    objects->setIcon(QPixmap(objectSet));
    objects->setIconSize(QSize(buttonSize,buttonSize));
    vbox5->addWidget(objects);
    connect(objects,SIGNAL(clicked()),this,SLOT(objectsFunction()));
    //vbox5->addWidget(new QLabel(" "));

    //设置
    attribute = new QToolButton(this);
    attribute->setToolTip(tr("设置"));
    attribute->setMinimumHeight(buttonSize);
    attribute->setMaximumHeight(buttonSize);
    attribute->setMinimumWidth(buttonSize);
    attribute->setMaximumWidth(buttonSize);
    attribute->setStyleSheet("border-style:flat;background-color:2E302D");
    attributeSet="./icon/14_1.png";
    attribute->setIcon(QPixmap(attributeSet));
    attribute->setIconSize(QSize(buttonSize,buttonSize));
    vbox5->addWidget(attribute);
    connect(attribute,SIGNAL(clicked()),this,SLOT(attributeFunction()));
    //vbox5->addWidget(new QLabel(" "));

    //关闭声音
    voice = new QToolButton(this);
    voice->setToolTip(tr("关闭声音"));
    voice->setMinimumHeight(buttonSize);
    voice->setMaximumHeight(buttonSize);
    voice->setMinimumWidth(buttonSize);
    voice->setMaximumWidth(buttonSize);
    voice->setStyleSheet("border-style:flat;background-color:2E302D");
    voiceSet="./icon/15_1.png";
    voice->setIcon(QPixmap(voiceSet));
    voice->setIconSize(QSize(buttonSize,buttonSize));
    vbox5->addWidget(voice);
    connect(voice,SIGNAL(clicked()),this,SLOT(voiceFunction()));

    group5->setLayout(vbox5);
    mainToolBar->addWidget(group5);
    //mainToolBar->addWidget(new QLabel("   "));

    //第六组
    exitButton = new QToolButton(this);
    exitButton->setToolTip(tr("退出"));
    exitButton->setMinimumHeight(buttonSize);
    exitButton->setMaximumHeight(buttonSize);
    exitButton->setMinimumWidth(buttonSize);
    exitButton->setMaximumWidth(buttonSize);
    exitButton->setStyleSheet("border-style:flat;background-color:2E302D");
    exitSet="./icon/18.png";
    exitButton->setIcon(QPixmap(exitSet));
    exitButton->setIconSize(QSize(buttonSize,buttonSize));
    //mainToolBar->addWidget(exitButton);
        vbox6->addWidget(exitButton);
    connect(exitButton,SIGNAL(clicked()),this,SLOT(exitFunction()));


    mainToolBar->addWidget(group6);
    group6->setLayout(vbox6);
}

//获取系统当前时间定时器
void MainWindow::onTimerOut2(){
    systime->setText(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss ddd"));//时间
}

void MainWindow::adjustment()
{
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

    Mat w1 = widget1->getMat();
    if(this->isPseudo==true)
        mat=setPseudocolor(w1);
    updateBright(w1);
    updateContrast(w1);
   // widget1->setMat(w1);

    widget1->setMat(mat1);
  //  widget1->setPano(mat);
    widget1->setPano(newpano);
   //widget1->setObjects(objs);
    widget1->setTracks(in.getTracks());
    widget1->draw();

    Mat w2 = widget2->getMat();
    if(this->isPseudo==true)
        mat=setPseudocolor(w2);
    updateBright(w2);
    updateContrast(w2);
    //widget2->setMat(w2);

    //widget2->setPano(mat);
    widget2->setMat(mat2);
    widget2->setPano(newpano);
    //widget2->setObjects(objs);
    widget2->setTracks(in.getTracks());
    widget2->draw();


    widget3->setPano(newpano);
    widget3->setTwoPanos(mat);
   widget3->setAllObjects(in.getObjs());
    widget3->draw();

    widget4->setPano(newpano);
    widget4->setTwoPanos(mat);
    widget4->setAllObjects(in.getObjs());
    widget4->draw();

  //  widget3->setPano(mat);



    //widget4->setPano(mat);

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
    //index=index+1;
    timerFlash->stop();
  //  qDebug()<<QTime::currentTime().toString("hh:mm:ss");
    QString today=QString("./回放/")+QDate::currentDate().toString("yyyy-MM-dd");
    QDir *todayDir=new QDir();
    bool exist=todayDir->exists(today);
    if(!exist){
        todayDir->mkdir(today);
    }
    delete todayDir;

    in.getIntegratedData2();
    vector<MyObject> objs = in.getObjs2();

    QDesktopWidget* desktopWidget = QApplication::desktop();
    QRect screenRect = desktopWidget->screenGeometry();
    const int buttonSize=(screenRect.width()*0.7)/21.6;
    QPixmap pixmap1("./icon/16_1.png");
    QPixmap pixmap2("./icon/16_2.png");
    fitpixmap1=pixmap1.scaled(buttonSize,buttonSize, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    fitpixmap2=pixmap2.scaled(buttonSize,buttonSize, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);



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
    //Mat mat = in.getPano().clone();
    //vector<MyObject> objs = in.getObjs();
    vector<MyObjectTrack> tracks = in.getTracks();

    if(this->isPseudo==true)
        mat=setPseudocolor(mat);
    updateBright(mat);
    updateContrast(mat);

    for (int i = 0; i < objs.size();i++)
    {
        //画对象的box
        MyObject obj = objs[i];
        Rect rect2 = Rect(obj.getRect().x+pano.cols, obj.getRect().y, obj.getRect().width, obj.getRect().height);
        rectangle(mat,obj.getRect(),obj.getColor(),2,1,0);
        rectangle(mat,rect2,obj.getColor(),2,1,0);
        //cv::cvtColor(mat, mat, CV_BGR2RGB);

        //画轨迹
        if(isMubiao){
        for(int ii = 0; ii < tracks.size(); ii++){
            MyObjectTrack track = tracks[ii];
            int id = track.getId();
            vector<Point> points = track.getTrack();
            if(id == obj.getID()){
                for(int iii = 0; iii < points.size(); iii++){
                    Point point = points[iii];
                    Point point2 = Point(point.x+pano.cols, point.y);
                    circle(mat, point, 2, obj.getColor(),-1,8,2);//在图像中画出特征点，2是圆的半径
                    circle(mat, point2, 2, obj.getColor(),-1,8,2);//在图像中画出特征点，2是圆的半径
                    if(iii >= 1){
                        Point point3 = points[iii-1];
                        Point point4 = Point(point3.x+pano.cols, point3.y);
                        line(mat,point,point3,obj.getColor(),1,8,0);
                        line(mat,point2,point4,obj.getColor(),1,8,0);
                    }
                    //cv::cvtColor(mat, mat, CV_BGR2RGB);
                }
            }
        }
}
        //画对象中心点的位置
        if(isMubiao){
            int x = (int)(this->getDirectionX(obj.getCenPoint().x, pano));
            int y = (int)(10-this->getDirectionY(obj.getCenPoint().y, pano)/2);//(10-10*(this->getDirectionY(obj.getCenPoint().y)-this->getDirectionY())/(this->getDirectionY2()-this->getDirectionY()));//endh - i*(endh-starth)/10
            QString tx = QString::number(x,10);
            QString ty = QString::number(y,10);
            QString tstr = "x="+tx+",y="+ty;
            string str = tstr.toStdString();
            //qDebug()<<tstr;
            Point p = Point(obj.getRect().x+obj.getRect().width,obj.getRect().y+obj.getRect().height);
            Point p2 = Point(obj.getRect().x+obj.getRect().width+pano.cols,obj.getRect().y+obj.getRect().height);

            putText(mat,str,p,3,0.5,obj.getColor());
            putText(mat,str,p2,3,0.5,obj.getColor());
                    }
       // cv::cvtColor(mat, mat, CV_BGR2RGB);
    }
   // cv::cvtColor(mat, mat, CV_BGR2RGB);

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

    //Mat mat1 = image44;
//    if(this->isPseudo==true)
//        mat1=setPseudocolor(mat1);
//    updateBright(mat1);
//    updateContrast(mat1);
    //        if(saturation1!=100){
    //               hsl->channels[color].saturation1 = saturation1 - 100;
    //               hsl->adjust(mat1, mat1);
    //           }
    widget1->setMat(mat1);
    widget1->setPano(newpano);
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
    //widget2->setPano(mat);
    widget2->setMat(mat2);
    widget2->setObjects(objs);
    widget2->setTracks(in.getTracks());
    widget2->draw();
    //qDebug()<<s2;
    //drawUiLabel(mat2,2);
    //图片3
    //Mat mat3 =imread(imageurl);
    widget3->setPano(newpano);
    widget3->setTwoPanos(mat);
    widget3->setAllObjects(in.getObjs());
    widget3->draw();
    //drawUiLabelByCopy(mat3,3);
    //图片4
    //Mat mat4 =imread(imageurl2);
    //drawUiLabelByCopy(mat4,4);
    widget4->setPano(newpano);
    widget4->setTwoPanos(mat);
    widget4->setAllObjects(in.getObjs());
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
    widget6->setPano(newpano);
    widget6->setObjects(objs);
    widget6->draw();
// qDebug()<<QTime::currentTime().toString("hh:mm:ss");

 if(isGaojing)
 {
     if(objs.size()>num_objs){
         this->sound->play();
         newObjCount=objs.size()-num_objs;
         timerFlash->start();

         num_objs = objs.size();
     }
     else
         num_objs =objs.size();
 }

 if(isGaojing)
 {
     if(num_objs==0)
     {
         lights[0]->setPixmap(fitpixmap2);
         lights[1]->setPixmap(fitpixmap2);
         lights[2]->setPixmap(fitpixmap2);
         lights[3]->setPixmap(fitpixmap2);
         lights[4]->setPixmap(fitpixmap2);
     }
     else if(num_objs==1)
     {
         lights[0]->setPixmap(fitpixmap1);
         lights[1]->setPixmap(fitpixmap2);
         lights[2]->setPixmap(fitpixmap2);
         lights[3]->setPixmap(fitpixmap2);
         lights[4]->setPixmap(fitpixmap2);
//            light1->setPixmap(fitpixmap1);
//            light2->setPixmap(fitpixmap2);
//            light3->setPixmap(fitpixmap2);
//            light4->setPixmap(fitpixmap2);
//            light5->setPixmap(fitpixmap2);
     }
     else if(num_objs==2)
     {
         lights[0]->setPixmap(fitpixmap1);
         lights[1]->setPixmap(fitpixmap1);
         lights[2]->setPixmap(fitpixmap2);
         lights[3]->setPixmap(fitpixmap2);
         lights[4]->setPixmap(fitpixmap2);

//            light1->setPixmap(fitpixmap1);
//            light2->setPixmap(fitpixmap1);
//            light3->setPixmap(fitpixmap2);
//            light4->setPixmap(fitpixmap2);
//            light5->setPixmap(fitpixmap2);
     }
     else if(num_objs==3)
     {
         lights[0]->setPixmap(fitpixmap1);
         lights[1]->setPixmap(fitpixmap1);
         lights[2]->setPixmap(fitpixmap1);
         lights[3]->setPixmap(fitpixmap2);
         lights[4]->setPixmap(fitpixmap2);
//            light1->setPixmap(fitpixmap1);
//            light2->setPixmap(fitpixmap1);
//            light3->setPixmap(fitpixmap1);
//            light4->setPixmap(fitpixmap2);
//            light5->setPixmap(fitpixmap2);
     }
     else if(num_objs==4)
     {
         lights[0]->setPixmap(fitpixmap1);
         lights[1]->setPixmap(fitpixmap1);
         lights[2]->setPixmap(fitpixmap1);
         lights[3]->setPixmap(fitpixmap1);
         lights[4]->setPixmap(fitpixmap2);
//            light1->setPixmap(fitpixmap1);
//            light2->setPixmap(fitpixmap1);
//            light3->setPixmap(fitpixmap1);
//            light4->setPixmap(fitpixmap1);
//            light5->setPixmap(fitpixmap2);
     }
     else if(num_objs>= 5 )
     {
         lights[0]->setPixmap(fitpixmap1);
         lights[1]->setPixmap(fitpixmap1);
         lights[2]->setPixmap(fitpixmap1);
         lights[3]->setPixmap(fitpixmap1);
         lights[4]->setPixmap(fitpixmap1);
//            light1->setPixmap(fitpixmap1);
//            light2->setPixmap(fitpixmap1);
//            light3->setPixmap(fitpixmap1);
//            light4->setPixmap(fitpixmap1);
//            light5->setPixmap(fitpixmap1);
   }
 }
 else
 {
     lights[0]->setPixmap(fitpixmap2);
     lights[1]->setPixmap(fitpixmap2);
     lights[2]->setPixmap(fitpixmap2);
     lights[3]->setPixmap(fitpixmap2);
     lights[4]->setPixmap(fitpixmap2);
}
}

//与金老师接口的定时器处理
void MainWindow::jinTimerout(){
    //vector<MyObject> objs = in.getObjs2();
    //std::cout<<"ok2 "<<std::endl;
    //#if 1
    int v=in.getIntegratedData();
    if(v == 0){
        //std::cout<<"getintegrated data "<<std::endl;
        //图片1
        //        QString s1=in.getQJ1();
        //        imageurl=s1.toStdString();
        //        //qDebug()<<in.getObjs().size();
        //在全景上画矩形，文字，轨迹等
        //在两个全景上画矩形，文字，轨迹等
        timerFlash->stop();
        qDebug()<<QTime::currentTime().toString("hh:mm:ss");
        QString today=QString("./回放/")+QDate::currentDate().toString("yyyy-MM-dd");
        QDir *todayDir=new QDir();
        bool exist=todayDir->exists(today);
        if(!exist){
            todayDir->mkdir(today);
        }
        delete todayDir;

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
        //Mat mat = in.getPano().clone();
        vector<MyObject> objs = in.getObjs();
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

        vector<MyObjectTrack> tracks = in.getTracks();
        if(this->isPseudo==true)
            mat=setPseudocolor(mat);
        updateBright(mat);
        updateContrast(mat);

        int num_objs = objs.size();
        for (int i = 0; i < num_objs;i++)
        {
            //画对象的box
            MyObject obj = objs[i];
            Rect rect2 = Rect(obj.getRect().x+pano.cols, obj.getRect().y, obj.getRect().width, obj.getRect().height);
            rectangle(mat,obj.getRect(),obj.getColor(),2,1,0);
            rectangle(mat,rect2,obj.getColor(),2,1,0);
            //cv::cvtColor(mat, mat, CV_BGR2RGB);
    
            //画轨迹
            if(isMubiao){
            for(int ii = 0; ii < tracks.size(); ii++){
                MyObjectTrack track = tracks[ii];
                int id = track.getId();
                vector<Point> points = track.getTrack();
                if(id == obj.getID()){
                    for(int iii = 0; iii < points.size(); iii++){
                        Point point = points[iii];
                        Point point2 = Point(point.x+pano.cols, point.y);
                        circle(mat, point, 2, obj.getColor(),-1,8,2);//在图像中画出特征点，2是圆的半径
                        circle(mat, point2, 2, obj.getColor(),-1,8,2);//在图像中画出特征点，2是圆的半径
                        if(iii >= 1){
                            Point point3 = points[iii-1];
                            Point point4 = Point(point3.x+pano.cols, point3.y);
                            line(mat,point,point3,obj.getColor(),1,8,0);
                            line(mat,point2,point4,obj.getColor(),1,8,0);
                        }
                        //cv::cvtColor(mat, mat, CV_BGR2RGB);
                    }
                }
            }
    }
            //画对象中心点的位置
            if(isMubiao){
                int x = (int)(this->getDirectionX(obj.getCenPoint().x, pano));
                int y = (int)(10-this->getDirectionY(obj.getCenPoint().y, pano)/2);//(10-10*(this->getDirectionY(obj.getCenPoint().y)-this->getDirectionY())/(this->getDirectionY2()-this->getDirectionY()));//endh - i*(endh-starth)/10
                QString tx = QString::number(x,10);
                QString ty = QString::number(y,10);
                QString tstr = "x="+tx+",y="+ty;
                string str = tstr.toStdString();
                //qDebug()<<tstr;
                Point p = Point(obj.getRect().x+obj.getRect().width,obj.getRect().y+obj.getRect().height);
                Point p2 = Point(obj.getRect().x+obj.getRect().width+pano.cols,obj.getRect().y+obj.getRect().height);
    
                putText(mat,str,p,3,0.5,obj.getColor());
                putText(mat,str,p2,3,0.5,obj.getColor());
                        }
           // cv::cvtColor(mat, mat, CV_BGR2RGB);
        }
      //  cv::cvtColor(mat, mat, CV_BGR2RGB);

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

        //Mat mat1 = image44;
    //    if(this->isPseudo==true)
    //        mat1=setPseudocolor(mat1);
    //    updateBright(mat1);
    //    updateContrast(mat1);
        //        if(saturation1!=100){
        //               hsl->channels[color].saturation1 = saturation1 - 100;
        //               hsl->adjust(mat1, mat1);
        //           }
        widget1->setMat(mat1);
        widget1->setPano(newpano);
        widget1->setObjects(objs);
        widget1->setTracks(in.getTracks());
        widget1->draw();
        widget2->setPano(newpano);
        //widget2->setPano(mat);
        widget2->setMat(mat2);
        widget2->setObjects(objs);
        widget2->setTracks(in.getTracks());
        widget2->draw();
        //qDebug()<<s2;
        //drawUiLabel(mat2,2);
        //图片3
        //Mat mat3 =imread(imageurl);
        widget3->setPano(newpano);
        widget3->setTwoPanos(mat);
        widget3->setAllObjects(in.getObjs());
        widget3->draw();
        //drawUiLabelByCopy(mat3,3);
        //图片4
        //Mat mat4 =imread(imageurl2);
        //drawUiLabelByCopy(mat4,4);
        widget4->setPano(newpano);
        widget4->setTwoPanos(mat);
        widget4->setAllObjects(in.getObjs());
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
        widget6->setPano(newpano);
        widget6->setObjects(objs);
        widget6->draw();
     qDebug()<<QTime::currentTime().toString("hh:mm:ss");
    
     if(isGaojing)
     {
         if(objs.size()>num_objs){
             this->sound->play();
             newObjCount=objs.size()-num_objs;
             timerFlash->start();
    
             num_objs = objs.size();
         }
         else
             num_objs =objs.size();
     }
    
     if(isGaojing)
     {
         if(num_objs==0)
         {
             lights[0]->setPixmap(fitpixmap2);
             lights[1]->setPixmap(fitpixmap2);
             lights[2]->setPixmap(fitpixmap2);
             lights[3]->setPixmap(fitpixmap2);
             lights[4]->setPixmap(fitpixmap2);
         }
         else if(num_objs==1)
         {
             lights[0]->setPixmap(fitpixmap1);
             lights[1]->setPixmap(fitpixmap2);
             lights[2]->setPixmap(fitpixmap2);
             lights[3]->setPixmap(fitpixmap2);
             lights[4]->setPixmap(fitpixmap2);
    //            light1->setPixmap(fitpixmap1);
    //            light2->setPixmap(fitpixmap2);
    //            light3->setPixmap(fitpixmap2);
    //            light4->setPixmap(fitpixmap2);
    //            light5->setPixmap(fitpixmap2);
         }
         else if(num_objs==2)
         {
             lights[0]->setPixmap(fitpixmap1);
             lights[1]->setPixmap(fitpixmap1);
             lights[2]->setPixmap(fitpixmap2);
             lights[3]->setPixmap(fitpixmap2);
             lights[4]->setPixmap(fitpixmap2);
    
    //            light1->setPixmap(fitpixmap1);
    //            light2->setPixmap(fitpixmap1);
    //            light3->setPixmap(fitpixmap2);
    //            light4->setPixmap(fitpixmap2);
    //            light5->setPixmap(fitpixmap2);
         }
         else if(num_objs==3)
         {
             lights[0]->setPixmap(fitpixmap1);
             lights[1]->setPixmap(fitpixmap1);
             lights[2]->setPixmap(fitpixmap1);
             lights[3]->setPixmap(fitpixmap2);
             lights[4]->setPixmap(fitpixmap2);
    //            light1->setPixmap(fitpixmap1);
    //            light2->setPixmap(fitpixmap1);
    //            light3->setPixmap(fitpixmap1);
    //            light4->setPixmap(fitpixmap2);
    //            light5->setPixmap(fitpixmap2);
         }
         else if(num_objs==4)
         {
             lights[0]->setPixmap(fitpixmap1);
             lights[1]->setPixmap(fitpixmap1);
             lights[2]->setPixmap(fitpixmap1);
             lights[3]->setPixmap(fitpixmap1);
             lights[4]->setPixmap(fitpixmap2);
    //            light1->setPixmap(fitpixmap1);
    //            light2->setPixmap(fitpixmap1);
    //            light3->setPixmap(fitpixmap1);
    //            light4->setPixmap(fitpixmap1);
    //            light5->setPixmap(fitpixmap2);
         }
         else if(num_objs>= 5 )
         {
             lights[0]->setPixmap(fitpixmap1);
             lights[1]->setPixmap(fitpixmap1);
             lights[2]->setPixmap(fitpixmap1);
             lights[3]->setPixmap(fitpixmap1);
             lights[4]->setPixmap(fitpixmap1);
    //            light1->setPixmap(fitpixmap1);
    //            light2->setPixmap(fitpixmap1);
    //            light3->setPixmap(fitpixmap1);
    //            light4->setPixmap(fitpixmap1);
    //            light5->setPixmap(fitpixmap1);
       }
     }
     else
     {
         lights[0]->setPixmap(fitpixmap2);
         lights[1]->setPixmap(fitpixmap2);
         lights[2]->setPixmap(fitpixmap2);
         lights[3]->setPixmap(fitpixmap2);
         lights[4]->setPixmap(fitpixmap2);
    }
    }
    else{
        //QMessageBox::information(this,tr("接口返回值"),QString::number(v,10));
        this->selfTimerout();
    }
    //    }
    //    else
    //    {
    //    std::cout<<"no ok"<<std::endl;
    //    }
    //    #endif
}

//以下处理鼠标拖拽事件，在全景显示区1或者2有选择框的情况下，从全景显示区1或者2出发，目标是主显示区，则拷贝图像到主显示区；目标是凝视显示区，则拷贝图像到凝视显示区。
void MainWindow::mousePressEvent(QMouseEvent *e)
{
    //qDebug()<<"鼠标压下事件来自mainframe";
    if(e->button() == Qt::LeftButton)
    {
        //isRect = false;
        //判断是否是拖拽出发点
        QPoint position1 = e->pos();//e->globalPos() - this->pos();
        //起始点是落在全景显示区1中的情况
        if((position1.x() <= this->widget1->pos().x()+this->widget1->width()) &&(position1.x() >= this->widget1->pos().x()) && (position1.y() <= this->widget1->pos().y()+this->widget1->height()) &&(position1.y() >= this->widget1->pos().y())){
            isDrag1 = true;
            isDrag2 = false;
        }
        //起始点是落在全景显示区2中的情况
        if((position1.x() <= this->widget2->pos().x()+this->widget2->width()) &&(position1.x() >= this->widget2->pos().x()) && (position1.y() <= this->widget2->pos().y()+this->widget2->height()) &&(position1.y() >= this->widget2->pos().y())){
            isDrag2 = true;
            isDrag1 = false;
        }

        //e->accept();
        //qDebug()<<position1;
    }
}

void MainWindow::mouseMoveEvent(QMouseEvent *e)
{
    if(isDrag1 && (e->buttons() && Qt::LeftButton)){
        //move(e->globalPos() - position1);
        isMove = true;
        //e->accept();
    }
    if(isDrag2 && (e->buttons() && Qt::LeftButton)){
        //move(e->globalPos() - position1);
        isMove = true;
        //e->accept();
    }
}

void MainWindow::mouseReleaseEvent(QMouseEvent *e)
{
    //判断目的点落在主显示区的标志变量
    boolean target3 = false;
    boolean target4 = false;
    QPoint position2 = e->pos();//e->globalPos() - this->pos();

    //判断目的点落在主显示区的情况
    if((position2.x() <= this->widget3->pos().x()+this->widget3->width()) &&(position2.x() >= this->widget3->pos().x()) && (position2.y() <= this->widget3->pos().y()+this->widget3->height()) &&(position2.y() >= this->widget3->pos().y())){
        target3 = true;
        target4 = false;
    }
    //判断目的点落在凝视显示区的情况
    else if((position2.x() <= this->widget4->pos().x()+this->widget4->width()) &&(position2.x() >= this->widget4->pos().x()) && (position2.y() <= this->widget4->pos().y()+this->widget4->height()) &&(position2.y() >= this->widget4->pos().y())){
        target4 = true;
        target3 = false;
    }
    else{
        isDrag1 = false;
        isDrag2 = false;
        isMove = false;
    }
    //4种组合
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
    //3. 如果出发点是全景显示区1，并且全景显示区1中有选择框，并且目的是凝视显示区，则拷贝全景显示区1选择框内的图像到凝视显示区
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
    //4. 如果出发点是全景显示区2，并且全景显示区2中有选择框，并且目的是凝视显示区，则拷贝全景显示区2选择框内的图像到凝视显示区
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
    isDrag1 = false;
    isDrag2 = false;
    isMove = false;
}

void MainWindow::resizeEvent(QResizeEvent *){
    label->resize(widget1->size());
    label2->resize(widget2->size());
    label3->resize(widget3->size());
    label4->resize(widget4->size());
    label5->resize(widget5->size());
    label6->resize(widget6->size());
}

void MainWindow::paintEvent(QPaintEvent *){
    //重新绘制图片。
}

Mat MainWindow::setPseudocolor(Mat& image){
    Mat img_pseudocolor(image.rows, image.cols, CV_8UC3);
    for (int y = 0; y < image.rows; y++)//转为伪彩色图像的具体算法
    {
        for (int x = 0; x < image.cols; x++)
        {
            int tmp = image.at<unsigned char>(y, x);
            img_pseudocolor.at<Vec3b>(y, x)[0] = abs(255 - tmp); //blue
            img_pseudocolor.at<Vec3b>(y, x)[1] = abs(127 - tmp); //green
            img_pseudocolor.at<Vec3b>(y, x)[2] = abs(0 - tmp); //red
        }
    }
    return img_pseudocolor;
}

double MainWindow::getDirectionX(double x, Mat mat){
    //double x = this->rectan.x;
    return 360*x/mat.cols -90;
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
void MainWindow::loadPictureToLabel1(boolean isRect, QRect qrect){
    //loadPictureToLabel(label,imgLabel1);
    QPixmap pixmap1 = QPixmap::fromImage(imgLabel1);
    if(isRect){
        QPainter painter(&pixmap1);
        painter.setPen(QPen(Qt::red,4,Qt::SolidLine)); //设置画笔形式
        //painter.setBrush(QBrush(Qt::red,Qt::SolidPattern)); //设置画刷形式
        painter.drawRect(qrect);
    }
    label->setScaledContents(true);
    label->setPixmap(pixmap1);
}

//加载图片到Label2上
void MainWindow::loadPictureToLabel2(boolean isRect, QRect qrect){
    //loadPictureToLabel(label2,imgLabel2);
    QPixmap pixmap1 = QPixmap::fromImage(imgLabel2);

    if(isRect){
        QPainter painter(&pixmap1);
        painter.setPen(QPen(Qt::red,4,Qt::SolidLine)); //设置画笔形式
        //painter.setBrush(QBrush(Qt::red,Qt::SolidPattern)); //设置画刷形式
        painter.drawRect(qrect);
    }
    label2->setScaledContents(true);
    label2->setPixmap(pixmap1);
}

//加载图片到Label3上
void MainWindow::loadPictureToLabel3(){
    loadPictureToLabel(label3,imgLabel3);
}

//加载图片到Label4上
void MainWindow::loadPictureToLabel4(){
    loadPictureToLabel(label4,imgLabel4);
}

//加载图片到Label5上
void MainWindow::loadPictureToLabel5(){
    loadPictureToLabel(label5,imgLabel5);
}

//加载图片到Label6上
void MainWindow::loadPictureToLabel6(){
    loadPictureToLabel(label6,imgLabel6);
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
    circle(image, pointInterest, 2, Scalar(255, 0,0 ),-1,8,2);//在图像中画出特征点，2是圆的半径
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
            putText(image,str,Point(i*c-10,50),3,1,Scalar(255,255,255));
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
            putText(image,str2,Point(50,i*r+10),3,1,Scalar(255,255,255));
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
    if (isQidong)
    {
        startStop->setIcon(QPixmap("./icon/播放.png"));
        startStop->setToolTip("启动");
        //startStopSet="./icon/1_1.png";
        isQidong = false;
    }
    else
    {
        startStop->setIcon(QPixmap("./icon/1_1.png"));
        startStop->setToolTip("停止");
        isQidong = true;
        //startStopSet="./icon/1_2.png";
    }

}
//暂停/继续
void MainWindow::mstopFunction()
{
    //if(mstopSet=="./icon/2_2.png")
    if(isJixu)
    {
        mstop->setIcon(QPixmap("./icon/2_1灰.png"));
        mstop->setToolTip("继续");
        isJixu = false;
        //mstopSet="./icon/2_1.png";
    }
    else
    {
        mstop->setIcon(QPixmap("./icon/2_1.png"));
        mstop->setToolTip("暂停");
        isJixu = true;
        //mstopSet="./icon/2_2.png";
        //        dialogLabel->setText(tr("Information Message Box"));
        //        QMessageBox::information(this,tr("红外全景系统"),tr("通过金老师SDK，实现监控继续。"));
    }

}
//后退
void MainWindow::backFunction()
{
    //dialogLabel->setText(tr("Information Message Box"));
    QMessageBox::information(this,tr("后退功能，有待实现。"),tr("继续努力。"));
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
        //qDebug()<<(stop-start);
        widgetNew->close();
        backwindow=new BackWindow(date,dateTimeStart,dateTimeStop);
        backwindow->show();
    }

}
void MainWindow::quXiaoFunction()
{
    widgetNew->close();
}
//图像
//自动
void MainWindow::automFunction()
{
    bright_TrackbarValue = 0;
    alpha_contrast = 100;
    trackBar->setPosition(0);
    strackBar->setPosition(100);
    //saturation1 = 100;
    isPseudo = false;
    adjustment();
}
void MainWindow::updateBright(Mat &mat1 )
{
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
//亮度
void MainWindow::brightnessFunction()
{
    trackBar->setWindowFlags(Qt::WindowStaysOnTopHint);
    trackBar->setWindowTitle("亮度");
    trackBar->show();
    //trackBar->setWindowFlags(Qt::WindowStaysOnTopHint);
    //trackBar->activateWindow();
    trackBar->move(trackBar->x(),trackBar->y());
    if(brightnessSet=="./icon/7_1.png")
    {
        brightness->setIcon(QPixmap("./icon/7_1.png"));
        brightnessSet="./icon/7_1.png";
    }
    else
    {
        brightness->setIcon(QPixmap("./icon/7_1.png"));
        brightnessSet="./icon/7_1.png";
    }
}

void MainWindow::updateContrast(Mat &mat1){
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
//对比度
void MainWindow::saturationFunction()
{
    strackBar->setWindowFlags(Qt::WindowStaysOnTopHint);
    strackBar->setWindowTitle("对比度");
    strackBar->show();
    strackBar->activateWindow();
    strackBar->move(strackBar->x(),strackBar->y());
    if(saturationSet=="./icon/8_1.png")
    {
        saturation->setIcon(QPixmap("./icon/8_1.png"));
        saturationSet="./icon/8_1.png";
    }
    else
    {
        saturation->setIcon(QPixmap("./icon/8_1.png"));
        saturationSet="./icon/8_1.png";
    }
}
//伪彩色
void MainWindow::pseudoColorFunction()
{
    isPseudo=!isPseudo;
    adjustment();
}

//告警
//打开关闭
void MainWindow::openCloseFunction()
{
    isGaojing = !isGaojing;
    QDesktopWidget* desktopWidget = QApplication::desktop();
    QRect screenRect = desktopWidget->screenGeometry();
    const int buttonSize=(screenRect.width()*0.7)/21.6;
    QPixmap pixmap1("./icon/16_1.png");
    QPixmap pixmap2("./icon/16_2.png");
    fitpixmap1=pixmap1.scaled(buttonSize,buttonSize, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    fitpixmap2=pixmap2.scaled(buttonSize,buttonSize, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    vector<MyObject> vec = in.getObjs2();
    if(isGaojing)
    {
        openClose->setIcon(QPixmap("./icon/11_1.png"));
        openClose->setToolTip("关闭告警");
        if(vec.size()==0)
        {
            lights[0]->setPixmap(fitpixmap2);
            lights[1]->setPixmap(fitpixmap2);
            lights[2]->setPixmap(fitpixmap2);
            lights[3]->setPixmap(fitpixmap2);
            lights[4]->setPixmap(fitpixmap2);
//            light1->setPixmap(fitpixmap2);
//            light2->setPixmap(fitpixmap2);
//            light3->setPixmap(fitpixmap2);
//            light4->setPixmap(fitpixmap2);
//            light5->setPixmap(fitpixmap2);
        }
        else if(vec.size()==1)
        {
            lights[0]->setPixmap(fitpixmap1);
            lights[1]->setPixmap(fitpixmap2);
            lights[2]->setPixmap(fitpixmap2);
            lights[3]->setPixmap(fitpixmap2);
            lights[4]->setPixmap(fitpixmap2);
//            light1->setPixmap(fitpixmap1);
//            light2->setPixmap(fitpixmap2);
//            light3->setPixmap(fitpixmap2);
//            light4->setPixmap(fitpixmap2);
//            light5->setPixmap(fitpixmap2);
        }
        else if(vec.size()==2)
        {
            lights[0]->setPixmap(fitpixmap1);
            lights[1]->setPixmap(fitpixmap1);
            lights[2]->setPixmap(fitpixmap2);
            lights[3]->setPixmap(fitpixmap2);
            lights[4]->setPixmap(fitpixmap2);
//            light1->setPixmap(fitpixmap1);
//            light2->setPixmap(fitpixmap1);
//            light3->setPixmap(fitpixmap2);
//            light4->setPixmap(fitpixmap2);
//            light5->setPixmap(fitpixmap2);
        }
        else if(vec.size()==3)
        {
            lights[0]->setPixmap(fitpixmap1);
            lights[1]->setPixmap(fitpixmap1);
            lights[2]->setPixmap(fitpixmap1);
            lights[3]->setPixmap(fitpixmap2);
            lights[4]->setPixmap(fitpixmap2);
//            light1->setPixmap(fitpixmap1);
//            light2->setPixmap(fitpixmap1);
//            light3->setPixmap(fitpixmap1);
//            light4->setPixmap(fitpixmap2);
//            light5->setPixmap(fitpixmap2);
        }
        else if(vec.size()==4)
        {
            lights[0]->setPixmap(fitpixmap1);
            lights[1]->setPixmap(fitpixmap1);
            lights[2]->setPixmap(fitpixmap1);
            lights[3]->setPixmap(fitpixmap1);
            lights[4]->setPixmap(fitpixmap2);
//            light1->setPixmap(fitpixmap1);
//            light2->setPixmap(fitpixmap1);
//            light3->setPixmap(fitpixmap1);
//            light4->setPixmap(fitpixmap1);
//            light5->setPixmap(fitpixmap2);
        }
        else if(vec.size()>= 5 )
        {
            lights[0]->setPixmap(fitpixmap1);
            lights[1]->setPixmap(fitpixmap1);
            lights[2]->setPixmap(fitpixmap1);
            lights[3]->setPixmap(fitpixmap1);
            lights[4]->setPixmap(fitpixmap1);
//            light1->setPixmap(fitpixmap1);
//            light2->setPixmap(fitpixmap1);
//            light3->setPixmap(fitpixmap1);
//            light4->setPixmap(fitpixmap1);
//            light5->setPixmap(fitpixmap1);
      }
    }
    else
    {
        openClose->setIcon(QPixmap("./icon/11_2.png"));
        openClose->setToolTip("打开告警");

        lights[0]->setPixmap(fitpixmap2);
        lights[1]->setPixmap(fitpixmap2);
        lights[2]->setPixmap(fitpixmap2);
        lights[3]->setPixmap(fitpixmap2);
        lights[4]->setPixmap(fitpixmap2);
//        light1->setPixmap(fitpixmap2);
//        light2->setPixmap(fitpixmap2);
//        light3->setPixmap(fitpixmap2);
//        light4->setPixmap(fitpixmap2);
//        light5->setPixmap(fitpixmap2);
   }
}
//手动
void MainWindow::manualFunction()
{
    //dialogLabel->setText(tr("Information Message Box"));
    QMessageBox::information(this,tr("手动捕获目标功能，有待实现。"),tr("继续努力。"));

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
}
//目标属性列表
void MainWindow::objectAttributeFunction()
{
    //dialogLabel->setText(tr("Information Message Box"));
    //const QString &objectstring = "oid =" ;
    // QMessageBox::information(this,"目标属性列表",&objectstring);
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

    // this->objectAttributes->tr("oid");
    // this->objectAttributes->resize(300,500);
    //this->objectAttributes->setText("oid=: ");
    //this->objectAttributes->setText("cenPoint");
    //QString s=QString("oid:")+myobjects.oid+"\n目标中心坐标:<"+myobjects.cenPoint.x+","+myobjects.cenPoint.y
    //            +">/n监测框大小:<"+myobjects.blocksize.width+","+myobjects.blocksize.height;
    //QString s1=QString(">\n运动速率:")+myobjects.Velocity
    //            +"\n运动方向："+myobjects.MotionDerection+"\n目标面积:"+myobjects.area+"\n水平轴长度:"+myobjects.horizontalAxisLength
    //            +"\n竖直轴长度:"+myobjects.verticalAxisLength+"\n绝对强度:"+myobjects.absoluteIntensity+"\n相对强度"+myobjects.relativeIntensity
    //            +"\n目标尺度:"+myobjects.targetScale+"\n中央周围对比度的相应强度:"+myobjects.CenSueEintensity+"\n目标背景信杂比"+myobjects.SCRValue;
    //    qDebug()<<"22222222222";
    //    this->objectAttributes->setText(s);
    //    this->objectAttributes->show();
    this->objectAttributes->show();
}
//设置
void MainWindow::objectsFunction()
{
    //if(objectSet=="./icon/13_2.png")
    if(isMubiao)
    {
        objects->setIcon(QPixmap("./icon/13_1.png"));
        isMubiao = false;
        //objectSet="./icon/13_1.png";
        objects->setToolTip("开启目标属性跟随");
    }
    else
    {
        objects->setIcon(QPixmap("./icon/13_1.png"));
        isMubiao = true;
        //objectSet="./icon/13_2.png";
        objects->setToolTip("关闭目标属性跟随");
    }
}
//目标属性列表
void MainWindow::attributeFunction()
{
    QMessageBox::information(this,tr("属性设置界面，有待实现。"),tr("继续努力。"));
}
//声音
void MainWindow::voiceFunction()
{

    //if(voiceSet=="./icon/15_2.png")
    isVoice = !isVoice;
    cmixer->SetMute(isVoice);
    if(isVoice == false)
        this->sound->play();
//     QImage icon;
//     icon = QImage("./icon/15_1.png");
//    Mat micon;
//    micon =  QImageToMat(icon);
//    cv::cvtColor(micon, micon, CV_RGB2GRAY);
    //icon = QImage((unsigned char*)micon.data,micon.cols,micon.rows,micon.step,QImage::Format_RGB16);

    if(isShengyin)
    {
        voice->setIcon(QPixmap("./icon/15_1灰.png"));
        isShengyin = false;
        //voiceSet="./icon/15_1.png";
        voice->setToolTip("打开声音");
    }
    else
    {
        voice->setIcon(QPixmap("./icon/15_1.png"));
        isShengyin = true;
        //voiceSet="./icon/15_2.png";
        voice->setToolTip("关闭声音");

    }
}

void MainWindow::exitFunction(){
    QApplication::closeAllWindows();
}

//退出系统事件
void MainWindow::closeEvent(QCloseEvent *event)
{


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
    static bool flag = false;
    if(num_objs-newObjCount<5){
        for(addOneLight=0;addOneLight<newObjCount;addOneLight++){
            if(num_objs+addOneLight-newObjCount>4)
                break;
            else{
                if(flag)
                   lights[num_objs+addOneLight-newObjCount]->setPixmap(fitpixmap1);
                else
                   lights[num_objs+addOneLight-newObjCount]->setPixmap(fitpixmap2);
            }
        }
    }else{
        if(flag)
             lights[4]->setPixmap(fitpixmap1);
        else
             lights[4]->setPixmap(fitpixmap2);
    }
    flag = !flag;
}
