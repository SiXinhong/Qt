#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qjwidget.h"
//opencv的头文件
#include <vector>
#include <highgui.h>
#include <cv.h>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>


#include <QToolBar>
#include <QGridLayout>
#include <QPainter>
#include<QPalette>
#include<QPixmap>
#include<QImage>
#include<QLabel>
#include<QDebug>
#include<QTimer>

#include <QtGui/QPainter>


using namespace cv;
using namespace std;

//int threshval = 160;
//Mat img;
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);   
    QWidget* widget = new QWidget(this);



    //widget10 = new QWidget(this);
    widget1 = new QjWidget(new QWidget(this));
    widget2 = new QjWidget(new QWidget(this));
    widget3 = new QWidget(this);
    widget4 = new QWidget(this);
    widget5 = new QWidget(this);
    widget6 = new QWidget(this);

    label=new QLabel(widget1);
    label2=new QLabel(widget2);
    label3=new QLabel(widget3);
    label4=new QLabel(widget4);
    label5=new QLabel(widget5);
    label6=new QLabel(widget6);

    index=0;//用于计算标尺的起始位置
    index1=0;//用于取第一栏的图片
    index2=0;//用于取第二栏的图片

    dialogLabel=new QLabel;


    //图片1
    string imageurl="./s1/1.bmp";
    drawUiLabel(imageurl,1);
    //图片2
    string imageurl2 = "./s2/1.bmp";
    drawUiLabel(imageurl2,2);
    //图片3
    drawUiLabelByCopy(imageurl,3);
    //图片4
    drawUiLabelByCopy(imageurl2,4);
    //图片5
    string imageurl5="./0.png";//第五个图片的
    drawUiLabel(imageurl5,5);
    //图片6
    string imageurl6= "./0.png";//第五个图片的
    drawUiLabel(imageurl6,6);

//    string imageurl="./s1/1.bmp";
//    String imageurl2="./s2/1.bmp";
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

    //定时器
    timer=new QTimer();
    timer->setInterval(3000);
    timer->start();
    connect(timer, SIGNAL(timeout()), SLOT(onTimerOut()));

    // 创建工具栏
    addMyToolBar();
    //创建菜单栏
    //监控
//    QActionGroup *group=new QActionGroup(this);
//    QAction *startStopc=group->addAction(tr("启/停"));
//    ui->monitoring->addAction(startStopc);
//    connect(startStopc,SIGNAL(triggered()),this,SLOT(startStopFunction()));

//    QAction *mstopc=group->addAction(tr("暂停"));
//    ui->monitoring->addAction(mstopc);
//    connect(mstopc,SIGNAL(triggered()),this,SLOT(mstopFunction()));

//    //回放
//    QActionGroup *group2=new QActionGroup(this);
//    QAction *openc=group2->addAction(tr("打开"));
//    ui->playback->addAction(openc);
//    connect(openc,SIGNAL(triggered()),this,SLOT(openFunction()));

//    QAction *playc=group2->addAction(tr("播放"));
//    ui->playback->addAction(playc);
//    connect(playc,SIGNAL(triggered()),this,SLOT(playFunction()));

//    QAction *rstopc=group2->addAction(tr("暂停"));
//    ui->playback->addAction(rstopc);
//    connect(rstopc,SIGNAL(triggered()),this,SLOT(rstopFunction()));

//    QAction *timeLinec=group2->addAction(tr("时间线"));
//    ui->playback->addAction(timeLinec);
//    connect(timeLinec,SIGNAL(triggered()),this,SLOT(timeLineFunction()));

//    //图像
//    QActionGroup *group3=new QActionGroup(this);
//    QAction *automc=group3->addAction(tr("自动"));
//    ui->image->addAction(automc);
//    connect(automc,SIGNAL(triggered()),this,SLOT(automFunction()));

//    QAction *brightnessc=group3->addAction(tr("亮度"));
//    ui->image->addAction(brightnessc);
//    connect(brightnessc,SIGNAL(triggered()),this,SLOT(brightnessFunction()));

//    QAction *saturationc=group3->addAction(tr("饱和度"));
//    ui->image->addAction(saturationc);
//    connect(saturationc,SIGNAL(triggered()),this,SLOT(saturationFunction()));

//    QAction *pseudoColorc=group3->addAction(tr("伪彩色"));
//    ui->image->addAction(pseudoColorc);
//    connect(pseudoColorc,SIGNAL(triggered()),this,SLOT(pseudoColorFunction()));

//    QAction *serialNumberc=group3->addAction(tr("编号"));
//    ui->image->addAction(serialNumberc);
//    connect(serialNumberc,SIGNAL(triggered()),this,SLOT(serialNumberFunction()));

//    //告警
//    QActionGroup *group4=new QActionGroup(this);
//    QAction *openClosec=group4->addAction(tr("开/关"));
//    ui->alarm->addAction(openClosec);
//    connect(openClosec,SIGNAL(triggered()),this,SLOT(openCloseFunction()));

//    QAction *manualc=group4->addAction(tr("手动"));
//    ui->alarm->addAction(manualc);
//    connect(manualc,SIGNAL(triggered()),this,SLOT(manualFunction()));

//    QAction *attributec=group4->addAction(tr("属性"));
//    ui->alarm->addAction(attributec);
//    connect(attributec,SIGNAL(triggered()),this,SLOT(attributeFunction()));

//    QAction *setUpc=group4->addAction(tr("设置"));
//    ui->alarm->addAction(setUpc);
//    connect(setUpc,SIGNAL(triggered()),this,SLOT(setUpFunction()));

//    QAction *voicec=group4->addAction(tr("声音"));
//    ui->alarm->addAction(voicec);
//    connect(voicec,SIGNAL(triggered()),this,SLOT(voiceFunction()));

//    QAction *lightc=group4->addAction(tr("指示灯"));
//    ui->alarm->addAction(lightc);
//    connect(lightc,SIGNAL(triggered()),this,SLOT(lightFunction()));

    //创建状态栏
    // addMyStatusBar();
    ui->statusBar->addWidget(new QLabel(QObject::tr("累计监控时间:")));
    ui->statusBar->addWidget(new QLabel(QObject::tr("   ")));
    ui->statusBar->addWidget(new QLabel(QObject::tr("初次出现目标信息:")));
    //右键
    //addAction(new QAction("目标列表",this));
    //widget1->addAction(new QAction("到主显示区",widget1));
    //widget1->addAction(new QAction("到凝视显示区",widget1));
    //addAction(new QAction("最大化",this));
    //addAction(new QAction("最佳显示效果",this));
    //setContextMenuPolicy(Qt::ActionsContextMenu);

    //布局
    gridlayout = new QGridLayout;
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
}

MainWindow::~MainWindow()
{
    delete ui;
}
//绘制工具栏
void MainWindow::addMyToolBar()
{
    mainToolBar = addToolBar("monitoring");
    //监控
    mainToolBar->addSeparator();
    listLabel1=new QLabel(tr(" 监控 "));
    mainToolBar->addWidget(listLabel1);
    startStop = new QToolButton(this);
    startStop->setToolTip(tr("启/停"));
    startStopSet="./icon/1_1.png";
    startStop->setIcon(QPixmap(startStopSet));
    startStop->setMinimumHeight(35);
    mainToolBar->addWidget(startStop);
    connect(startStop,SIGNAL(clicked()),this,SLOT(startStopFunction()));

    mstop = new QToolButton(this);
    mstop->setToolTip(tr("暂停"));
    mstopSet="./icon/2_1.png";
    mstop->setIcon(QPixmap(mstopSet));
    mstop->setMinimumHeight(35);
    mainToolBar->addWidget(mstop);
    mainToolBar->addSeparator();
    connect(mstop,SIGNAL(clicked()),this,SLOT(mstopFunction()));
    //回放
    listLabel2=new QLabel(tr(" 回放 "));
    mainToolBar->addWidget(listLabel2);
    open = new QToolButton(this);
    open->setToolTip(tr("打开"));
    openSet="./icon/3_1.png";
    open->setIcon(QPixmap(openSet));
    open->setMinimumHeight(35);
    mainToolBar->addWidget(open);

    connect(open,SIGNAL(clicked()),this,SLOT(openFunction()));



    play = new QToolButton(this);
    play->setToolTip(tr("播放"));
    playSet="./icon/4_1.png";
    play->setIcon(QPixmap(playSet));
    play->setMinimumHeight(35);
    mainToolBar->addWidget(play);
    connect(play,SIGNAL(clicked()),this,SLOT(playFunction()));

    rstop = new QToolButton(this);
    rstop->setToolTip(tr("暂停"));
    rstopSet="./icon/2_1.png";
    rstop->setIcon(QPixmap(rstopSet));
    rstop->setMinimumHeight(35);
    mainToolBar->addWidget(rstop);
    connect(rstop,SIGNAL(clicked()),this,SLOT(rstopFunction()));


    timeLine = new QToolButton(this);
    timeLine->setToolTip(tr("时间线"));
    timeLineSet="./icon/5_1.png";
    timeLine->setIcon(QPixmap(timeLineSet));
    timeLine->setMinimumHeight(35);
    mainToolBar->addWidget(timeLine);
    connect(timeLine,SIGNAL(clicked()),this,SLOT(timeLineFunction()));

    mainToolBar->addSeparator();
    //图像
    listLabel3=new QLabel(tr(" 图像 "));
    mainToolBar->addWidget(listLabel3);
    autom = new QToolButton(this);
    autom->setToolTip(tr("自动"));
    automSet="./icon/6_1.png";
    autom->setIcon(QPixmap(automSet));
    autom->setMinimumHeight(35);
    mainToolBar->addWidget(autom);
    connect(autom,SIGNAL(clicked()),this,SLOT(automFunction()));

    brightness = new QToolButton(this);
    brightness->setToolTip(tr("亮度"));
    brightnessSet="./icon/7_1.png";
    brightness->setIcon(QPixmap(brightnessSet));
    brightness->setMinimumHeight(35);
    mainToolBar->addWidget(brightness);
    connect(brightness,SIGNAL(clicked()),this,SLOT(brightnessFunction()));

    saturation = new QToolButton(this);
    saturation->setToolTip(tr("饱和度"));
    saturationSet="./icon/8_1.png";
    saturation->setIcon(QPixmap(saturationSet));
    saturation->setMinimumHeight(35);
    mainToolBar->addWidget(saturation);
    connect(saturation,SIGNAL(clicked()),this,SLOT(saturationFunction()));

    pseudoColor = new QToolButton(this);
    pseudoColor->setToolTip(tr("伪彩色"));
    pseudoColorSet="./icon/9_1.png";
    pseudoColor->setIcon(QPixmap(pseudoColorSet));
    pseudoColor->setMinimumHeight(35);
    mainToolBar->addWidget(pseudoColor);
    connect(pseudoColor,SIGNAL(clicked()),this,SLOT(pseudoColorFunction()));

    serialNumber = new QToolButton(this);
    serialNumber->setToolTip(tr("编号"));
    serialNumberSet="./icon/17_1.png";
    serialNumber->setIcon(QPixmap(serialNumberSet));
    serialNumber->setMinimumHeight(35);
    mainToolBar->addWidget(serialNumber);
    connect(serialNumber,SIGNAL(clicked()),this,SLOT(serialNumberFunction()));

    time = new QToolButton(this);
    time->setToolTip(tr("时间"));
    timeSet="./icon/10_1.png";
    time->setIcon(QPixmap(timeSet));
    time->setMinimumHeight(35);
    mainToolBar->addWidget(time);
    mainToolBar->addSeparator();
    connect(time,SIGNAL(clicked()),this,SLOT(timeFunction()));

    //告警
    listLabel4=new QLabel(tr(" 告警 "));
    mainToolBar->addWidget(listLabel4);
    openClose = new QToolButton(this);
    openClose->setToolTip(tr("开/关"));
    openCloseSet="./icon/11_1.png";
    openClose->setIcon(QPixmap(openCloseSet));
    openClose->setMinimumHeight(35);
    mainToolBar->addWidget(openClose);
    connect(openClose,SIGNAL(clicked()),this,SLOT(openCloseFunction()));

    manual = new QToolButton(this);
    manual->setToolTip(tr("手动"));
    manualSet="./icon/12_1.png";
    manual->setIcon(QPixmap(manualSet));
    manual->setMinimumHeight(35);
    mainToolBar->addWidget(manual);
    connect(manual,SIGNAL(clicked()),this,SLOT(manualFunction()));

    attribute = new QToolButton(this);
    attribute->setToolTip(tr("属性"));
    attributeSet="./icon/13_1.png";
    attribute->setIcon(QPixmap(attributeSet));
    attribute->setMinimumHeight(35);
    mainToolBar->addWidget(attribute);
    connect(attribute,SIGNAL(clicked()),this,SLOT(attributeFunction()));

    setUp = new QToolButton(this);
    setUp->setToolTip(tr("设置"));
    setUpSet="./icon/14_1.png";
    setUp->setIcon(QPixmap(setUpSet));
    setUp->setMinimumHeight(35);
    mainToolBar->addWidget(setUp);
    connect(setUp,SIGNAL(clicked()),this,SLOT(setUpFunction()));

    voice = new QToolButton(this);
    voice->setToolTip(tr("声音"));
    voiceSet="./icon/15_1.png";
    voice->setIcon(QPixmap(voiceSet));
    voice->setMinimumHeight(35);
    mainToolBar->addWidget(voice);
    connect(voice,SIGNAL(clicked()),this,SLOT(voiceFunction()));

    light = new QToolButton(this);
    light->setToolTip(tr("指示灯"));
    lightSet="./icon/16_1.png";
    light->setIcon(QPixmap(lightSet));
    light->setMinimumHeight(35);
    mainToolBar->addWidget(light);
    connect(light,SIGNAL(clicked()),this,SLOT(lightFunction()));
    mainToolBar->addSeparator();
}
//---xiaotian 绘制界面上的图片3  图片4
void MainWindow::drawUiLabelByCopy(string imgurl, int index1){
    Mat image =imread(imgurl);
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
        imgLabel = drawScaleAndRecOnPic(image33,rectans1,index,-1);
        cv::cvtColor(image11, image11, CV_BGR2RGB);
        loadPictureToLabel(label3,imgLabel);
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
        imgLabel = drawRecOnPic(image44,rectans);
        cv::cvtColor(image11, image11, CV_BGR2RGB);
        loadPictureToLabel(label4,imgLabel);
        //cvReleaseMat(&image4);
        //cvReleaseMat(&image44);
    }
    //cvReleaseMat(&image);
    //cvReleaseMat(&image11);
    //delete & aa;
    //delete & img;
}


//---xiaotian 绘制界面上的图片1 图片2 图片5 图片6
void MainWindow::drawUiLabel(string imgurl, int index){
     Mat image =imread(imgurl);
     vector<Rectan> rectans;
     if(index == 1){
         //图片1
         Rectan rec(1490,250,100,100);
         Rectan rec2(1800,250,50,50);
         rectans.push_back(rec);
         rectans.push_back(rec2);
         //QImage imgLabel = drawRecOnPic(image,rectans);
         imgLabel = drawRecOnPic(image,rectans);
         cv::cvtColor(image, image, CV_BGR2RGB);
         loadPictureToLabel(label,imgLabel);
     }

     if(index == 2){
        //图片2
         Rectan rec3(2600,10,100,100);
         rectans.clear();
         rectans.push_back(rec3);
         //QImage imgLabel = drawRecOnPic(image,rectans);
         imgLabel = drawRecOnPic(image,rectans);
         cv::cvtColor(image, image, CV_BGR2RGB);
         loadPictureToLabel(label2,imgLabel);
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
         imgLabel = drawCircleOnPic(image,points,120,100);
         cv::cvtColor(image, image, CV_BGR2RGB);
         loadPictureToLabel(label5,imgLabel);
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
         imgLabel = drawCircleOnPic(image,points1,120,100);
         cv::cvtColor(image, image, CV_BGR2RGB);
         loadPictureToLabel(label6,imgLabel);
         //delete imgLabel6;
     }
     //cvReleaseMat(&image);
}



//---xiaotian   加载图片到label上。
void MainWindow::loadPictureToLabel(QLabel *label, QImage image){
    pixmap = QPixmap::fromImage(image);
    label->setPixmap(pixmap);
    label->setScaledContents(true);
    //释放image
    //delete & image;
}

//---xiaotian   图像上绘制矩形框
QImage MainWindow::drawRecOnPic(Mat image, vector<Rectan> rectans){
    //在图像上画矩形。
    int count = rectans.size();
    for (int i = 0; i < count;i++)
    {
        Rect rect;
        rect.x = rectans[i].getX();
        rect.y = rectans[i].getY();
        rect.width = rectans[i].getWidth();
        rect.height = rectans[i].getHeight();
        rectangle(image,rect,Scalar(0,0,255),4,1,0);
        cv::cvtColor(image, image, CV_BGR2RGB);
    }
    cv::cvtColor(image,image,CV_BGR2RGB);
    //QImage imglabel;
    imgLabel = MatToQImage(image);
    return imgLabel;

}



//---xiaotian  图像上绘制标尺和矩形框
QImage MainWindow::drawScaleAndRecOnPic(Mat image, vector<Rectan> rectans, double startw, double starth){
    //在图像上画矩形。
    int count = rectans.size();
    for (int i = 0; i < count;i++)
    {
        Rect rect;
        rect.x = rectans[i].getX();
        rect.y = rectans[i].getY();
        rect.width = rectans[i].getWidth();
        rect.height = rectans[i].getHeight();
        rectangle(image,rect,Scalar(0,0,255),4,1,0);
        cv::cvtColor(image, image, CV_BGR2RGB);
    }
    //在图像上画标尺
    paintScale(image,startw,starth);
    cv::cvtColor(image,image,CV_BGR2RGB);
    //QImage imglabel3;
    imgLabel = MatToQImage(image);
    return imgLabel;
}

//---xiaotian  图像上绘制多边形和圆
QImage MainWindow::drawCircleOnPic(Mat image, vector<Point> point, double x, double y){
    //在图像上画多边形
    int count = point.size();
    for (int i = 0; i <count;i+=2)
    {
        Point point1 = point[i];
        Point point2 = point[i+1];
        line(image,point1,point2,Scalar(255,255,0),1,8,0);
    }
    //在图像上画圆点
    paintCircle(image,x,y);
    cv::cvtColor(image,image,CV_BGR2RGB);
    //QImage imglabel;
    imgLabel = MatToQImage(image);
    return imgLabel;
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
    cv::cvtColor(image, image, CV_BGR2RGB);
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

//定时器任务
void MainWindow::onTimerOut()
{
    index=index+1;
//    string imageurl="./s1/1.bmp";
//    string imageurl2="./s2/1.bmp";
//    //存储第一栏
//    QString filename1("./s1/1.bmp");
//    QString filename2("./s1/2.bmp");
//    QString filename3("./s1/3.bmp");
//    QString filename4("./s1/4.bmp");
//    //存储第二栏
//    QString filename5("./s2/1.bmp");
//    QString filename6("./s2/2.bmp");
//    QString filename7("./s2/3.bmp");
//    QString filename8("./s2/4.bmp");
//    //将第一栏存储在vector中
//    vc1.push_back(filename1);
//    vc1.push_back(filename2);
//    vc1.push_back(filename3);
//    vc1.push_back(filename4);
//    //将第二栏存储在vector中
//    vc2.push_back(filename5);
//    vc2.push_back(filename6);
//    vc2.push_back(filename7);
//    vc2.push_back(filename8);
    //更新第一栏的图片
    index1=index1+1;
    //QImage *image=new QImage(vc1[(index1)%4]);
    image= QImage(vc1[(index1)%4]);
    QString s1=vc1[(index1)%4];
    imageurl=s1.toStdString();
    qDebug()<<s1;
    drawUiLabel(imageurl,1);

    //更新第二栏的图片
    index2=index2+1;
    //QImage *image2=new QImage(vc2[(index2)%4]);
    image2= QImage(vc2[(index2)%4]);
    QString s2=vc2[(index2)%4];
    imageurl2=s2.toStdString();
    qDebug()<<s2;
    drawUiLabel(imageurl2,2);
    //更新第三栏
    Mat img=QImageToMat(image);
    paintRectangle(img,1490,250,100,100);
    drawUiLabelByCopy(imageurl,3);
    //更新第四栏
    Mat img2=QImageToMat(image2);
    paintRectangle(img2,1650,250,400,100);
    drawUiLabelByCopy(imageurl2,4);
    qDebug()<<"tongguo 3!!!!!";
//delete & image;
    //delete & image2;
    //delete & s1;
    //delete & s2;
    //delete & imageurl;
    //delete & imageurl2;}
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
QImage MainWindow::MatToQImage(const cv::Mat& mat)
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
//监控
void MainWindow::startStopFunction()
{
    if(startStopSet=="./icon/1_2.png")
    {
        startStop->setIcon(QPixmap("./icon/1_1.png"));
        startStopSet="./icon/1_1.png";
        dialogLabel->setText(tr("Information Message Box"));
        QMessageBox::information(this,tr("红外全景系统"),tr("通过金老师SDK，实现监控启动。"));
    }
    else
    {
        startStop->setIcon(QPixmap("./icon/1_2.png"));
        startStopSet="./icon/1_2.png";
        dialogLabel->setText(tr("Information Message Box"));
        QMessageBox::information(this,tr("红外全景系统"),tr("通过金老师SDK，实现监控停止。"));
    }

}
void MainWindow::mstopFunction()
{
    if(mstopSet=="./icon/2_2.png")
    {
        mstop->setIcon(QPixmap("./icon/2_1.png"));
        mstopSet="./icon/2_1.png";
        dialogLabel->setText(tr("Information Message Box"));
        QMessageBox::information(this,tr("红外全景系统"),tr("通过金老师SDK，实现监控暂停。"));
    }
    else
    {
        mstop->setIcon(QPixmap("./icon/2_2.png"));
        mstopSet="./icon/2_2.png";
        dialogLabel->setText(tr("Information Message Box"));
        QMessageBox::information(this,tr("红外全景系统"),tr("通过金老师SDK，实现监控继续。"));
    }

}
//回放功能
//打开
void MainWindow::openFunction()
{
    if(openSet=="./icon/3_2.png")
    {
        open->setIcon(QPixmap("./icon/3_1.png"));
        openSet="./icon/3_1.png";
    }
    else
    {
        open->setIcon(QPixmap("./icon/3_2.png"));
        openSet="./icon/3_2.png";
    }
//    QString s=QFileDialog::getOpenFileName(this,"opem file dialog","/",
//                                           "C++ files(*.cpp)::C files(*.c)::Head files(*.h)");
//    fileLineEdit->setText(s);
}
//播放
void MainWindow::playFunction()
{
    if(playSet=="./icon/4_2.png")
    {
        play->setIcon(QPixmap("./icon/4_1.png"));
        playSet="./icon/4_1.png";
    }
    else
    {
        play->setIcon(QPixmap("./icon/4_2.png"));
        playSet="./icon/4_2.png";
    }
}
//暂停
void MainWindow::rstopFunction()
{
    if(rstopSet=="./icon/2_2.png")
    {
        rstop->setIcon(QPixmap("./icon/2_1.png"));
        rstopSet="./icon/2_1.png";
    }
    else
    {
        rstop->setIcon(QPixmap("./icon/2_2.png"));
        rstopSet="./icon/2_2.png";
    }
}
//时间线
void MainWindow::timeLineFunction()
{
    if(timeLineSet=="./icon/5_2.png")
    {
        timeLine->setIcon(QPixmap("./icon/5_1.png"));
        timeLineSet="./icon/5_1.png";
    }
    else
    {
        timeLine->setIcon(QPixmap("./icon/5_2.png"));
        timeLineSet="./icon/5_2.png";
    }
}
//图像
//自动
void MainWindow::automFunction()
{
    if(automSet=="./icon/6_2.png")
    {
        autom->setIcon(QPixmap("./icon/6_1.png"));
        automSet="./icon/6_1.png";
    }
    else
    {
        autom->setIcon(QPixmap("./icon/6_2.png"));
        automSet="./icon/6_2.png";
    }
}
//亮度
void MainWindow::brightnessFunction()
{
    if(brightnessSet=="./icon/7_2.png")
    {
        brightness->setIcon(QPixmap("./icon/7_1.png"));
        brightnessSet="./icon/7_1.png";
    }
    else
    {
        brightness->setIcon(QPixmap("./icon/7_2.png"));
        brightnessSet="./icon/7_2.png";
    }
//    int g_nTrackbarValue;
//    g_nTrackbarValue = 20;
//    createTrackbar("亮度","红外全景控制系统",&g_nTrackbarValue,threshval,on_trackbar);
}
//void MainWindow::on_trackbar(int, void*)
//{
//    Mat bw = threshval < 128 ? (img < threshval) : (img > threshval);//如果threshval小于128，则当bw中相应元素小于threshval时赋255，大于threshval时赋0。如果threshval大于128，则当bw相应元素大于threshval时赋255，小于threshval时赋0
//    //定义点和向量
//    vector<vector<Point> > contours;//存放轮廓，但是每个vector<Point>元素不一定只表示一个轮廓。
//    vector<Vec4i> hierarchy;//存放轮廓之间的拓扑关系。hierarchy[idx][0]、 hierarchy[idx][1]、 hierarchy[idx][2]、 hierarchy[idx][3]分别表示索引为idx的轮廓的前一个、后一个、子、父轮廓对应的索引；当索引为0时，表示相应的轮廓不存在。
//    findContours( bw, contours, hierarchy, CV_RETR_CCOMP, CV_CHAIN_APPROX_SIMPLE );//查找轮廓
//    Mat dst = Mat::zeros(img.size(), CV_8UC3);//初始化dst
//    if( !contours.empty() && !hierarchy.empty() )//开始处理
//    {
//        //遍历所有顶层轮廓，随机生成颜色值绘制给各连接组成部分
//        int idx = 0;
//        for( ; idx >= 0; idx = hierarchy[idx][0] )
//        {
//            Scalar color( (rand()&255), (rand()&255), (rand()&255) );
//            drawContours( dst, contours, idx, color, CV_FILLED, 8, hierarchy );//绘制填充轮廓
//        }
//    }
//    imshow("Connected Components", dst);//显示窗口
//}
//饱和度
void MainWindow::saturationFunction()
{
    if(saturationSet=="./icon/8_2.png")
    {
        saturation->setIcon(QPixmap("./icon/8_1.png"));
        saturationSet="./icon/8_1.png";
    }
    else
    {
        saturation->setIcon(QPixmap("./icon/8_2.png"));
        saturationSet="./icon/8_2.png";



    }
}



//伪彩色
void MainWindow::pseudoColorFunction()
{
    if(pseudoColorSet=="./icon/9_2.png")
    {
        pseudoColor->setIcon(QPixmap("./icon/9_1.png"));
        pseudoColorSet="./icon/9_1.png";
    }
    else
    {
        pseudoColor->setIcon(QPixmap("./icon/9_2.png"));
        pseudoColorSet="./icon/9_2.png";
    }
}
//编号
void MainWindow::serialNumberFunction()
{
    if(serialNumberSet=="./icon/17_2.png")
    {
        serialNumber->setIcon(QPixmap("./icon/17_1.png"));
        serialNumberSet="./icon/17_1.png";
    }
    else
    {
        serialNumber->setIcon(QPixmap("./icon/17_2.png"));
        serialNumberSet="./icon/17_2.png";
    }
}
//时间
void MainWindow::timeFunction()
{
    if(timeSet=="./icon/10_2.png")
    {
        time->setIcon(QPixmap("./icon/10_1.png"));
        timeSet="./icon/10_1.png";
    }
    else
    {
        time->setIcon(QPixmap("./icon/10_2.png"));
        timeSet="./icon/10_2.png";
    }
}
//告警
//打开关闭
void MainWindow::openCloseFunction()
{
    if(openCloseSet=="./icon/11_2.png")
    {
        openClose->setIcon(QPixmap("./icon/11_1.png"));
        openCloseSet="./icon/11_1.png";
    }
    else
    {
        openClose->setIcon(QPixmap("./icon/11_2.png"));
        openCloseSet="./icon/11_2.png";
    }
}
//手动
void MainWindow::manualFunction()
{
    if(manualSet=="./icon/12_2.png")
    {
        manual->setIcon(QPixmap("./icon/12_1.png"));
        manualSet="./icon/12_1.png";
    }
    else
    {
        manual->setIcon(QPixmap("./icon/12_2.png"));
        manualSet="./icon/12_2.png";
    }
}
//属性
void MainWindow::attributeFunction()
{
    if(attributeSet=="./icon/13_2.png")
    {
        attribute->setIcon(QPixmap("./icon/13_1.png"));
        attributeSet="./icon/13_1.png";
    }
    else
    {
        attribute->setIcon(QPixmap("./icon/13_2.png"));
        attributeSet="./icon/13_2.png";
    }
}
//设置
void MainWindow::setUpFunction()
{
    if(setUpSet=="./icon/14_2.png")
    {
        setUp->setIcon(QPixmap("./icon/14_1.png"));
        setUpSet="./icon/14_1.png";
    }
    else
    {
        setUp->setIcon(QPixmap("./icon/14_2.png"));
        setUpSet="./icon/14_2.png";
    }
}
//声音
void MainWindow::voiceFunction()
{
    if(voiceSet=="./icon/15_2.png")
    {
        voice->setIcon(QPixmap("./icon/15_1.png"));
        voiceSet="./icon/15_1.png";
    }
    else
    {
        voice->setIcon(QPixmap("./icon/15_2.png"));
        voiceSet="./icon/15_2.png";
    }
}
//指示灯
void MainWindow::lightFunction()
{
    if(lightSet=="./icon/16_2.png")
    {
        light->setIcon(QPixmap("./icon/16_1.png"));
        lightSet="./icon/16_1.png";
    }
    else
    {
        light->setIcon(QPixmap("./icon/16_2.png"));
        lightSet="./icon/16_2.png";
    }
}
