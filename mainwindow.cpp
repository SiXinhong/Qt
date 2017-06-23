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

using namespace cv;
using namespace std;


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
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
    xtbh = QString("XXXXXXX");
    //-------------------------------------------------------


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

    //自定义接口处理，将来被金老师SDK替换--------------------------------
    in = MyInterface();
    selfProcessing();
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
    //ui->statusBar->addWidget(new QLabel(QObject::tr("累计监控时间:")));
    //ui->statusBar->addWidget(new QLabel(QObject::tr("   ")));
    //ui->statusBar->addWidget(new QLabel(QObject::tr("初次出现目标信息:")));
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
    this->trackBar=new TrackBar(this);
    bright_TrackbarValue=0;
}

MainWindow::~MainWindow(){
    delete ui;
}

//自定义接口处理函数，将来被金老师SDK替换------------------------------
void MainWindow::selfProcessing(){
    index=0;//用于计算标尺的起始位置
//    index1=0;//用于取第一栏的图片
//    index2=0;//用于取第二栏的图片
    vector<MyObject> objs = in.getObjs2();

    //图片1
//    QString imageurl=in.getQJ1();
//    qDebug()<<imageurl;
//    Mat mat1 =imread(imageurl.toStdString());
//    widget1->setMat(mat1);
//    drawUiLabel(mat1,1);
    //image= QImage(in.getQJ1());
    QString s1=in.getQJ1();
    imageurl=s1.toStdString();
    Mat mat1 =imread(imageurl);
    widget1->setMat(mat1);
    widget1->setObjects(objs);
    widget1->setTracks(in.getTracks());
    widget1->draw();
    //qDebug()<<s1;
    //drawUiLabel(mat1,1);
    //图片2
//    QString imageurl2 = in.getQJ2();
//    qDebug()<<imageurl2;
//    Mat mat2 =imread(imageurl2.toStdString());
//    widget2->setMat(mat2);
//    drawUiLabel(mat2,2);
    //image2= QImage(in.getQJ2());
    QString s2=in.getQJ2();
    imageurl2=s2.toStdString();
    Mat mat2 =imread(imageurl2);
    widget2->setMat(mat2);
    widget2->setObjects(objs);
    widget2->setTracks(in.getTracks());
    widget2->draw();
    //qDebug()<<s2;
    //drawUiLabel(mat2,2);
    //图片3
    //Mat mat3 =imread(imageurl);
    widget3->draw();
    //drawUiLabelByCopy(mat3,3);
    //图片4
    //Mat mat4 =imread(imageurl2);
    //drawUiLabelByCopy(mat4,4);
    widget4->draw();
    //图片5
    QString imageurl5=in.getHD();
    Mat mat5 =imread(imageurl5.toStdString());
    widget5->setMat(mat5);
    widget5->setPano(mat1);
    widget5->setObjects(objs);
    widget5->draw();
    //drawUiLabel(mat5,5);
    //图片6
    QString imageurl6= in.getLD();
    Mat mat6 =imread(imageurl6.toStdString());
    widget6->setMat(mat6);
    widget6->setPano(mat1);
    widget6->setObjects(objs);
    widget6->draw();
    //drawUiLabel(mat6,6);

//    imageurl="./s1/1.bmp";
//    imageurl2="./s2/1.bmp";

//    //存储第一栏
//    filename1 = "./s1/1.bmp";
//    filename2 = "./s1/2.bmp";
//    filename3 = "./s1/3.bmp";
//    filename4 = "./s1/4.bmp";
//    //存储第二栏
//    filename5 = "./s2/1.bmp";
//    filename6 = "./s2/2.bmp";
//    filename7 = "./s2/3.bmp";
//    filename8 = "./s2/4.bmp";
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
    mainToolBar = addToolBar("monitoring");

    //第一组按钮：监控和后退，还有回放
    //启动/停止
    mainToolBar->addSeparator();
    mainToolBar->addWidget(new QLabel("   "));
    //listLabel1=new QLabel(tr(" 监控 "));
    //mainToolBar->addWidget(listLabel1);
    startStop = new QToolButton(this);
    startStop->setToolTip(tr("停止"));
    startStopSet="./icon/1_1.png";
    startStop->setIcon(QPixmap(startStopSet));
    startStop->setMinimumHeight(35);
    mainToolBar->addWidget(startStop);
    connect(startStop,SIGNAL(clicked()),this,SLOT(startStopFunction()));
    mainToolBar->addWidget(new QLabel("   "));

    //暂停/继续
    mstop = new QToolButton(this);
    mstop->setToolTip(tr("暂停"));
    mstopSet="./icon/2_1.png";
    mstop->setIcon(QPixmap(mstopSet));
    mstop->setMinimumHeight(35);
    mainToolBar->addWidget(mstop);
    //mainToolBar->addSeparator();
    connect(mstop,SIGNAL(clicked()),this,SLOT(mstopFunction()));
    mainToolBar->addWidget(new QLabel("   "));
    //后退
    back = new QToolButton(this);
    back->setToolTip(tr("后退"));
    backSet="./icon/4_1.png";
    back->setIcon(QPixmap(backSet));
    back->setMinimumHeight(35);
    mainToolBar->addWidget(back);
    //mainToolBar->addSeparator();
    connect(back,SIGNAL(clicked()),this,SLOT(backFunction()));
    mainToolBar->addWidget(new QLabel("   "));
    //回放
    //listLabel2=new QLabel(tr(" 回放 "));
    //mainToolBar->addWidget(listLabel2);
    open = new QToolButton(this);
    open->setToolTip(tr("回放"));
    openSet="./icon/3_1.png";
    open->setIcon(QPixmap(openSet));
    open->setMinimumHeight(35);
    mainToolBar->addWidget(open);
    connect(open,SIGNAL(clicked()),this,SLOT(openFunction()));
    mainToolBar->addWidget(new QLabel("   "));


//    play = new QToolButton(this);
//    play->setToolTip(tr("播放"));
//    playSet="./icon/4_1.png";
//    play->setIcon(QPixmap(playSet));
//    play->setMinimumHeight(35);
//    mainToolBar->addWidget(play);
//    connect(play,SIGNAL(clicked()),this,SLOT(playFunction()));

//    rstop = new QToolButton(this);
//    rstop->setToolTip(tr("暂停"));
//    rstopSet="./icon/2_1.png";
//    rstop->setIcon(QPixmap(rstopSet));
//    rstop->setMinimumHeight(35);
//    mainToolBar->addWidget(rstop);
//    connect(rstop,SIGNAL(clicked()),this,SLOT(rstopFunction()));


//    timeLine = new QToolButton(this);
//    timeLine->setToolTip(tr("时间线"));
//    timeLineSet="./icon/5_1.png";
//    timeLine->setIcon(QPixmap(timeLineSet));
//    timeLine->setMinimumHeight(35);
//    mainToolBar->addWidget(timeLine);
//    connect(timeLine,SIGNAL(clicked()),this,SLOT(timeLineFunction()));

    mainToolBar->addSeparator();

    //第二组按钮：图像
    //listLabel3=new QLabel(tr(" 图像 "));
    //mainToolBar->addWidget(listLabel3);
    mainToolBar->addWidget(new QLabel("   "));
    autom = new QToolButton(this);
    autom->setToolTip(tr("自动"));
    automSet="./icon/6_1.png";
    autom->setIcon(QPixmap(automSet));
    autom->setMinimumHeight(35);
    mainToolBar->addWidget(autom);
    connect(autom,SIGNAL(clicked()),this,SLOT(automFunction()));
    mainToolBar->addWidget(new QLabel("   "));

    brightness = new QToolButton(this);
    brightness->setToolTip(tr("亮度"));
    brightnessSet="./icon/7_1.png";
    brightness->setIcon(QPixmap(brightnessSet));
    brightness->setMinimumHeight(35);
    mainToolBar->addWidget(brightness);
    connect(brightness,SIGNAL(clicked()),this,SLOT(brightnessFunction()));
    mainToolBar->addWidget(new QLabel("   "));

    saturation = new QToolButton(this);
    saturation->setToolTip(tr("饱和度"));
    saturationSet="./icon/8_1.png";
    saturation->setIcon(QPixmap(saturationSet));
    saturation->setMinimumHeight(35);
    mainToolBar->addWidget(saturation);
    connect(saturation,SIGNAL(clicked()),this,SLOT(saturationFunction()));
    mainToolBar->addWidget(new QLabel("   "));

    pseudoColor = new QToolButton(this);
    pseudoColor->setToolTip(tr("伪彩色"));
    pseudoColorSet="./icon/9_1.png";
    pseudoColor->setIcon(QPixmap(pseudoColorSet));
    pseudoColor->setMinimumHeight(35);
    mainToolBar->addWidget(pseudoColor);
    connect(pseudoColor,SIGNAL(clicked()),this,SLOT(pseudoColorFunction()));
    mainToolBar->addWidget(new QLabel("   "));

    mainToolBar->addSeparator();

    //第三组按钮，指示灯，五盏，一个目标一盏红灯；二个目标二盏红灯；三个目标三盏红灯；四个目标四盏红灯；五个目标及以上，五盏红灯
    mainToolBar->addWidget(new QLabel("   "));
    light1=new QToolButton(this);
    light1Set="./icon/16_1.png";
    light1->setIcon(QPixmap(light1Set));
    brightness->setMinimumHeight(35);
    mainToolBar->addWidget(light1);
    mainToolBar->addWidget(new QLabel("   "));

    light2=new QToolButton(this);
    light2Set="./icon/16_1.png";
    light2->setIcon(QPixmap(light2Set));
    brightness->setMinimumHeight(35);
    mainToolBar->addWidget(light2);
    mainToolBar->addWidget(new QLabel("   "));

    light3=new QToolButton(this);
    light3Set="./icon/16_1.png";
    light3->setIcon(QPixmap(light3Set));
    brightness->setMinimumHeight(35);
    mainToolBar->addWidget(light3);
    mainToolBar->addWidget(new QLabel("   "));

    light4=new QToolButton(this);
    light4Set="./icon/16_2.png";
    light4->setIcon(QPixmap(light4Set));
    brightness->setMinimumHeight(35);
    mainToolBar->addWidget(light4);
    mainToolBar->addWidget(new QLabel("   "));

    light5=new QToolButton(this);
    light5Set="./icon/16_2.png";
    light5->setIcon(QPixmap(light5Set));
    brightness->setMinimumHeight(35);
    mainToolBar->addWidget(light5);
    mainToolBar->addWidget(new QLabel("   "));

    mainToolBar->addSeparator();

    //第四组，显示编号和系统当前时间
    mainToolBar->addWidget(new QLabel("   "));
    serialNumber=new QLabel("系统编号："+xtbh);//编号
    mainToolBar->addWidget(serialNumber);
    mainToolBar->addWidget(new QLabel("   "));
    systime=new QLabel(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss ddd"));//时间
    mainToolBar->addWidget(systime);
    mainToolBar->addWidget(new QLabel("   "));

    mainToolBar->addSeparator();

//    serialNumber = new QToolButton(this);
//    serialNumber->setToolTip(tr("编号"));
//    serialNumberSet="./icon/17_1.png";
//    serialNumber->setIcon(QPixmap(serialNumberSet));
//    serialNumber->setMinimumHeight(35);
//    mainToolBar->addWidget(serialNumber);
//    connect(serialNumber,SIGNAL(clicked()),this,SLOT(serialNumberFunction()));

//    time = new QToolButton(this);
//    time->setToolTip(tr("时间"));
//    timeSet="./icon/10_1.png";
//    time->setIcon(QPixmap(timeSet));
//    time->setMinimumHeight(35);
//    mainToolBar->addWidget(time);
//    mainToolBar->addSeparator();
//    connect(time,SIGNAL(clicked()),this,SLOT(timeFunction()));

    //第五组，告警
    //listLabel4=new QLabel(tr(" 告警 "));
    //mainToolBar->addWidget(listLabel4);
    mainToolBar->addWidget(new QLabel("   "));
    openClose = new QToolButton(this);
    openClose->setToolTip(tr("关闭告警"));
    openCloseSet="./icon/11_1.png";
    openClose->setIcon(QPixmap(openCloseSet));
    openClose->setMinimumHeight(35);
    mainToolBar->addWidget(openClose);
    connect(openClose,SIGNAL(clicked()),this,SLOT(openCloseFunction()));
    mainToolBar->addWidget(new QLabel("   "));

    objectAttribute = new QToolButton(this);
    objectAttribute->setToolTip(tr("对象属性"));
    objectAttributeSet="./icon/17_1.png";
    objectAttribute->setIcon(QPixmap(objectAttributeSet));
    objectAttribute->setMinimumHeight(35);
    mainToolBar->addWidget(objectAttribute);
    connect(objectAttribute,SIGNAL(clicked()),this,SLOT(objectAttributeFunction()));
    mainToolBar->addWidget(new QLabel("   "));

    manual = new QToolButton(this);
    manual->setToolTip(tr("手动"));
    manualSet="./icon/12_1.png";
    manual->setIcon(QPixmap(manualSet));
    manual->setMinimumHeight(35);
    mainToolBar->addWidget(manual);
    connect(manual,SIGNAL(clicked()),this,SLOT(manualFunction()));
    mainToolBar->addWidget(new QLabel("   "));

    objects = new QToolButton(this);
    objects->setToolTip(tr("关闭目标属性跟随"));
    objectSet="./icon/13_1.png";
    objects->setIcon(QPixmap(objectSet));
    objects->setMinimumHeight(35);
    mainToolBar->addWidget(objects);
    connect(objects,SIGNAL(clicked()),this,SLOT(objectsFunction()));
    mainToolBar->addWidget(new QLabel("   "));

    attribute = new QToolButton(this);
    attribute->setToolTip(tr("设置"));
    attributeSet="./icon/14_1.png";
    attribute->setIcon(QPixmap(attributeSet));
    attribute->setMinimumHeight(35);
    mainToolBar->addWidget(attribute);
    connect(attribute,SIGNAL(clicked()),this,SLOT(attributeFunction()));
    mainToolBar->addWidget(new QLabel("   "));

    voice = new QToolButton(this);
    voice->setToolTip(tr("关闭声音"));
    voiceSet="./icon/15_1.png";
    voice->setIcon(QPixmap(voiceSet));
    voice->setMinimumHeight(35);
    mainToolBar->addWidget(voice);
    connect(voice,SIGNAL(clicked()),this,SLOT(voiceFunction()));
    mainToolBar->addWidget(new QLabel("   "));

    mainToolBar->addSeparator();

    mainToolBar->addWidget(new QLabel("   "));
    exitButton = new QToolButton(this);
    exitButton->setToolTip(tr("退出"));
    exitSet="./icon/16_1.png";
    exitButton->setIcon(QPixmap(exitSet));
    exitButton->setMinimumHeight(35);
    mainToolBar->addWidget(exitButton);
    connect(exitButton,SIGNAL(clicked()),this,SLOT(exitFunction()));
    mainToolBar->addWidget(new QLabel("   "));
    mainToolBar->addSeparator();
}

//获取系统当前时间定时器
void MainWindow::onTimerOut2(){
    systime->setText(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss ddd"));//时间
}

void MainWindow::adjustment()
{
//    Mat mat1 =imread(imageurl);
//    if(this->isPseudo==true)
//            mat1=setPseudocolor(mat1);
//    widget1->setMat(mat1);
//    drawUiLabel(mat1,1);

//    Mat mat2 =imread(imageurl2);
//    if(this->isPseudo==true)
//            mat2=setPseudocolor(mat2);
//    widget2->setMat(mat2);
//    drawUiLabel(mat2,2);
//    //更新第三栏
//    Mat mat3 = widget1->getMat();
//    Size dsize ;
//    double scale = 1;
//    dsize = Size(mat3.cols*scale,mat3.rows*scale);
//    Mat image11 = Mat(dsize,CV_32S);
//    cv::resize(mat3, image11,dsize);
//    img = QImage((const unsigned char*)(image11.data),image11.cols,mat3.rows, image11.cols*image11.channels(),  QImage::Format_RGB888);

//    aa=(&img)->copy(widget1->getQRectan());
//    Mat image3 = QImageToMat(aa);
//    Mat image33 = Mat(dsize,CV_32S);
//    cv::resize(image3, image33,dsize);
//    widget3->setMat(image33);
//    widget3->draw();

////    //更新第四栏
////    Mat img2=QImageToMat(image2);
////    paintRectangle(img2,1650,250,400,100);
////    Mat mat4 =imread(imageurl2);
////    drawUiLabelByCopy(mat4,4);
//    Mat mat4 = widget2->getMat();
//    //Size dsize ;
//    //double scale = 1;
//    dsize = Size(mat4.cols*scale,mat4.rows*scale);
//    image11 = Mat(dsize,CV_32S);
//    cv::resize(mat4, image11,dsize);
//    img = QImage((const unsigned char*)(image11.data),image11.cols,mat4.rows, image11.cols*image11.channels(),  QImage::Format_RGB888);

//    aa=(&img)->copy(widget2->getQRectan());
//    Mat image4 = QImageToMat(aa);
//    Mat image44 = Mat(dsize,CV_32S);
//    cv::resize(image4, image44,dsize);
//    widget4->setMat(image44);
//    widget4->draw();

}

//定时器任务
void MainWindow::onTimerOut()
{
    //index=index+1;
    vector<MyObject> objs = in.getObjs2();

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
    QString s1=in.getQJ1();
    imageurl=s1.toStdString();
    Mat mat1 =imread(imageurl);
    widget1->setMat(mat1);
    widget1->setObjects(objs);
    widget1->setTracks(in.getTracks());
    widget1->draw();
    //qDebug()<<s1;
    //图片2
    QString s2=in.getQJ2();
    imageurl2=s2.toStdString();
    Mat mat2 =imread(imageurl2);
    widget2->setMat(mat2);
    widget2->setObjects(objs);
    widget2->setTracks(in.getTracks());
    widget2->draw();
    //qDebug()<<s2;
    //drawUiLabel(mat2,2);
    //图片3
    //Mat mat3 =imread(imageurl);
    widget3->draw();
    //drawUiLabelByCopy(mat3,3);
    //图片4
    //Mat mat4 =imread(imageurl2);
    //drawUiLabelByCopy(mat4,4);
    widget4->draw();
    //图片5
    //QString imageurl5=in.getHD();
    //Mat mat5 =imread(imageurl5.toStdString());
    //widget5->setMat(mat5);
    widget5->setPano(mat1);
    widget5->setObjects(objs);
    widget5->draw();
    //drawUiLabel(mat5,5);
    //图片6
    //QString imageurl6= in.getLD();
    //Mat mat6 =imread(imageurl6.toStdString());
    //widget6->setMat(mat6);
    widget6->setPano(mat1);
    widget6->setObjects(objs);
    widget6->draw();

    //更新第一栏的图片
    //index1=index1+1;
    //QImage *image=new QImage(vc1[(index1)%4]);
//    image= QImage(vc1[(index1)%4]);
//    QString s1=vc1[(index1)%4];
//    imageurl=s1.toStdString();
//    Mat mat1 =imread(imageurl);
//    widget1->setMat(mat1);
//    qDebug()<<s1;
//    drawUiLabel(mat1,1);
//    image= QImage(in.getQJ1());
//    QString s1=in.getQJ1();
//    imageurl=s1.toStdString();
//    Mat mat1 =imread(imageurl);
//    if(this->isPseudo==true)
//            //mat1=setPseudocolor(mat1);
//    widget1->setMat(mat1);
//    qDebug()<<s1;
//    drawUiLabel(mat1,1);
//    //更新第二栏的图片
////    index2=index2+1;
////    //QImage *image2=new QImage(vc2[(index2)%4]);
////    image2= QImage(vc2[(index2)%4]);
////    QString s2=vc2[(index2)%4];
////    imageurl2=s2.toStdString();
////    Mat mat2 =imread(imageurl2);
////    widget2->setMat(mat2);
////    qDebug()<<s2;
////    drawUiLabel(mat2,2);
//    //index2=index2+1;
//    //QImage *image2=new QImage(vc2[(index2)%4]);
//    image2= QImage(in.getQJ2());
//    QString s2=in.getQJ2();
//    imageurl2=s2.toStdString();
//    Mat mat2 =imread(imageurl2);
//    if(this->isPseudo==true)
//            //mat2=setPseudocolor(mat2);
//    widget2->setMat(mat2);
//    qDebug()<<s2;
//    drawUiLabel(mat2,2);
//    //更新第三栏
////    Mat mat3 = widget1->getMat();
////    Size dsize ;
////    double scale = 1;
////    dsize = Size(mat3.cols*scale,mat3.rows*scale);
////    Mat image11 = Mat(dsize,CV_32S);
////    cv::resize(mat3, image11,dsize);
////    img = QImage((const unsigned char*)(image11.data),image11.cols,mat3.rows, image11.cols*image11.channels(),  QImage::Format_RGB888);

////    aa=(&img)->copy(widget1->getQRectan());
////    Mat image3 = QImageToMat(aa);
////    Mat image33 = Mat(dsize,CV_32S);
////    cv::resize(image3, image33,dsize);
////    widget3->setMat(image33);
//    widget3->draw();

////    //更新第四栏
////    Mat img2=QImageToMat(image2);
////    paintRectangle(img2,1650,250,400,100);
////    Mat mat4 =imread(imageurl2);
////    drawUiLabelByCopy(mat4,4);
////    Mat mat4 = widget2->getMat();
////    //Size dsize ;
////    //double scale = 1;
////    dsize = Size(mat4.cols*scale,mat4.rows*scale);
////    image11 = Mat(dsize,CV_32S);
////    cv::resize(mat4, image11,dsize);
////    img = QImage((const unsigned char*)(image11.data),image11.cols,mat4.rows, image11.cols*image11.channels(),  QImage::Format_RGB888);

////    aa=(&img)->copy(widget2->getQRectan());
////    Mat image4 = QImageToMat(aa);
////    Mat image44 = Mat(dsize,CV_32S);
////    cv::resize(image4, image44,dsize);
////    widget4->setMat(image44);
//    widget4->draw();
//    qDebug()<<"tongguo 3!!!!!";
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

        if(widget1->newrect.width<0){
            widget1->rectan.width = -widget1->newrect.width;
            widget1->rectan.height= -widget1->newrect.height;
            widget1->rectan.x = widget1->newrect.x+widget1->newrect.width;
            widget1->rectan.y = widget1->newrect.y+widget1->newrect.height;
        }
        else if(widget1->newrect.height<0){
            widget1->rectan.width = -widget1->newrect.width;
            widget1->rectan.height= -widget1->newrect.height;
            widget1->rectan.x = widget1->newrect.x+widget1->newrect.width;
            widget1->rectan.y = widget1->newrect.y+widget1->newrect.height;
        }
        else{
            widget1->rectan.x = widget1->newrect.x;
            widget1->rectan.y = widget1->newrect.y;
            widget1->rectan.width = widget1->newrect.width;
            widget1->rectan.height = widget1->newrect.height;
        }
        widget1->isRect = false;

        //更新主显示区所包含的目标
        vector<MyObject> objs3;
        int count = widget1->objs.size();
        for(int i = 0; i < count; i++){
            MyObject obj = widget1->objs[i];
            if(widget1->isObjSelected(obj)){
                objs3.push_back(obj);
            }
        }

        widget3->setObjects(objs3);

        widget3->setFrom(1);
        //widget1->rectan = widget1->newrect;

        Mat mat = widget1->getMat();
        Size dsize ;
        double scale = 1;
        dsize = Size(mat.cols*scale,mat.rows*scale);
        Mat image11 = Mat(dsize,CV_32S);
        cv::resize(mat, image11,dsize);
        img = QImage((const unsigned char*)(image11.data),image11.cols,mat.rows, image11.cols*image11.channels(),  QImage::Format_RGB888);

        //vector<Rectan> rectans;
        aa=(&img)->copy(widget1->getQRectan());
        Mat image3 = QImageToMat(aa);
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
        if(widget2->newrect.width<0){
            widget2->rectan.width = -widget2->newrect.width;
            widget2->rectan.height= -widget2->newrect.height;
            widget2->rectan.x = widget2->newrect.x+widget2->newrect.width;
            widget2->rectan.y = widget2->newrect.y+widget2->newrect.height;
        }
        else if(widget1->newrect.height<0){
            widget2->rectan.width = -widget2->newrect.width;
            widget2->rectan.height= -widget2->newrect.height;
            widget2->rectan.x = widget2->newrect.x+widget2->newrect.width;
            widget2->rectan.y = widget2->newrect.y+widget2->newrect.height;
        }
        else{
            widget2->rectan.x = widget2->newrect.x;
            widget2->rectan.y = widget2->newrect.y;
            widget2->rectan.width = widget2->newrect.width;
            widget2->rectan.height = widget2->newrect.height;
        }

        widget2->isRect = false;


        //更新主显示区所包含的目标
        vector<MyObject> objs3;
        int count = widget2->objs.size();
        for(int i = 0; i < count; i++){
            MyObject obj = widget2->objs[i];
            if(widget2->isObjSelected(obj)){
                objs3.push_back(obj);
            }
        }

        widget3->setObjects(objs3);

        widget3->setFrom(2);

        Mat mat = widget2->getMat();
        Size dsize ;
        double scale = 1;
        dsize = Size(mat.cols*scale,mat.rows*scale);
        Mat image11 = Mat(dsize,CV_32S);
        cv::resize(mat, image11,dsize);
        img = QImage((const unsigned char*)(image11.data),image11.cols,mat.rows, image11.cols*image11.channels(),  QImage::Format_RGB888);

        //vector<Rectan> rectans;
        aa=(&img)->copy(widget2->getQRectan());
        Mat image3 = QImageToMat(aa);
        Mat image33 = Mat(dsize,CV_32S);
        cv::resize(image3, image33,dsize);
        widget3->setMat(image33);
        widget3->draw();
    }
    //3. 如果出发点是全景显示区1，并且全景显示区1中有选择框，并且目的是凝视显示区，则拷贝全景显示区1选择框内的图像到凝视显示区
    if(isDrag1 && isMove && target4){
        //widget1->rectan = widget1->newrect;
        if(widget1->newrect.width<0){
            widget1->rectan.width = -widget1->newrect.width;
            widget1->rectan.height= -widget1->newrect.height;
            widget1->rectan.x = widget1->newrect.x+widget1->newrect.width;
            widget1->rectan.y = widget1->newrect.y+widget1->newrect.height;
        }
        else if(widget1->newrect.height<0){
            widget1->rectan.width = -widget1->newrect.width;
            widget1->rectan.height= -widget1->newrect.height;
            widget1->rectan.x = widget1->newrect.x+widget1->newrect.width;
            widget1->rectan.y = widget1->newrect.y+widget1->newrect.height;
        }
        else{
            widget1->rectan.x = widget1->newrect.x;
            widget1->rectan.y = widget1->newrect.y;
            widget1->rectan.width = widget1->newrect.width;
            widget1->rectan.height = widget1->newrect.height;
        }
        widget1->isRect = false;

        //更新主显示区所包含的目标
        vector<MyObject> objs4;
        int count = widget1->objs.size();
        for(int i = 0; i < count; i++){
            MyObject obj = widget1->objs[i];
            if(widget1->isObjSelected(obj)){
                objs4.push_back(obj);
            }
        }

        widget4->setObjects(objs4);

        widget4->setFrom(1);

        Mat mat = widget1->getMat();
        Size dsize ;
        double scale = 1;
        dsize = Size(mat.cols*scale,mat.rows*scale);
        Mat image11 = Mat(dsize,CV_32S);
        cv::resize(mat, image11,dsize);
        img = QImage((const unsigned char*)(image11.data),image11.cols,mat.rows, image11.cols*image11.channels(),  QImage::Format_RGB888);

        //vector<Rectan> rectans;
        aa=(&img)->copy(widget1->getQRectan());
        Mat image4 = QImageToMat(aa);
        Mat image44 = Mat(dsize,CV_32S);
        cv::resize(image4, image44,dsize);
        widget4->setMat(image44);
        widget4->draw();
    }
    //4. 如果出发点是全景显示区2，并且全景显示区2中有选择框，并且目的是凝视显示区，则拷贝全景显示区2选择框内的图像到凝视显示区
    if(isDrag2 && isMove && target4){
        //widget2->rectan = widget2->newrect;
        if(widget2->newrect.width<0){
            widget2->rectan.width = -widget2->newrect.width;
            widget2->rectan.height= -widget2->newrect.height;
            widget2->rectan.x = widget2->newrect.x+widget2->newrect.width;
            widget2->rectan.y = widget2->newrect.y+widget2->newrect.height;
        }
        else if(widget1->newrect.height<0){
            widget2->rectan.width = -widget2->newrect.width;
            widget2->rectan.height= -widget2->newrect.height;
            widget2->rectan.x = widget2->newrect.x+widget2->newrect.width;
            widget2->rectan.y = widget2->newrect.y+widget2->newrect.height;
        }
        else{
            widget2->rectan.x = widget2->newrect.x;
            widget2->rectan.y = widget2->newrect.y;
            widget2->rectan.width = widget2->newrect.width;
            widget2->rectan.height = widget2->newrect.height;
        }
        widget2->isRect = false;

        //更新主显示区所包含的目标
        vector<MyObject> objs4;
        int count = widget2->objs.size();
        for(int i = 0; i < count; i++){
            MyObject obj = widget2->objs[i];
            if(widget2->isObjSelected(obj)){
                objs4.push_back(obj);
            }
        }

        widget4->setObjects(objs4);

        widget4->setFrom(2);

        Mat mat = widget2->getMat();
        Size dsize ;
        double scale = 1;
        dsize = Size(mat.cols*scale,mat.rows*scale);
        Mat image11 = Mat(dsize,CV_32S);
        cv::resize(mat, image11,dsize);
        img = QImage((const unsigned char*)(image11.data),image11.cols,mat.rows, image11.cols*image11.channels(),  QImage::Format_RGB888);

        //vector<Rectan> rectans;
        aa=(&img)->copy(widget2->getQRectan());
        Mat image4 = QImageToMat(aa);
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
        cv::cvtColor(image11, image11, CV_BGR2RGB);
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
        cv::cvtColor(image11, image11, CV_BGR2RGB);
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
void MainWindow::loadPictureToLabel1(){
    loadPictureToLabel(label,imgLabel1);
}

//加载图片到Label2上
void MainWindow::loadPictureToLabel2(){
    loadPictureToLabel(label2,imgLabel2);
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
//    imgLabel = MatToQImage(image);
//    return imgLabel;

}

//绘制鼠标选取的矩形
void MainWindow::drawRecOnPic2(Mat image, Rect rect){
    //在图像上画矩形。
    rectangle(image,rect,Scalar(0,0,255),1,1,0);
    cv::cvtColor(image, image, CV_BGR2RGB);
    //QImage imglabel;
//    imgLabel = MatToQImage(image);
//    //return imgLabel;
}

//---xiaotian  图像上绘制标尺和矩形框
void MainWindow::drawScaleAndRecOnPic(Mat image, vector<Rectan> rectans, double startw, double starth){
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
//    imgLabel = MatToQImage(image);
//    return imgLabel;
}

//---xiaotian  图像上绘制多边形和圆
void MainWindow::drawCircleOnPic(Mat image, vector<Point> point, double x, double y){
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
        startStop->setIcon(QPixmap("./icon/4_1.png"));
        startStop->setToolTip("启动");
        //startStopSet="./icon/1_1.png";
        isQidong = false;
        //dialogLabel->setText(tr("Information Message Box"));
        //QMessageBox::information(this,tr("红外全景系统"),tr("通过金老师SDK，实现监控启动。"));
    }
    else
    {
        startStop->setIcon(QPixmap("./icon/1_1.png"));
        startStop->setToolTip("停止");
        isQidong = true;
        //startStopSet="./icon/1_2.png";
//        dialogLabel->setText(tr("Information Message Box"));
//        QMessageBox::information(this,tr("红外全景系统"),tr("通过金老师SDK，实现监控停止。"));
    }

}
//暂停/继续
void MainWindow::mstopFunction()
{
    //if(mstopSet=="./icon/2_2.png")
    if(isJixu)
    {
        mstop->setIcon(QPixmap("./icon/4_1.png"));
        mstop->setToolTip("继续");
        isJixu = false;
        //mstopSet="./icon/2_1.png";
//        dialogLabel->setText(tr("Information Message Box"));
//        QMessageBox::information(this,tr("红外全景系统"),tr("通过金老师SDK，实现监控暂停。"));
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
    //dialogLabel->setText(tr("Information Message Box"));
    QMessageBox::information(this,tr("回放功能，有待实现。"),tr("继续努力。"));
}

//图像
//自动
void MainWindow::automFunction()
{
   // dialogLabel->setText(tr("Information Message Box"));
    //QMessageBox::information(this,tr("自动色彩功能，有待实现。"),tr("继续努力。"));
    bright_TrackbarValue = 0;
    trackBar->setPosition(0);
    isPseudo = false;
    adjustment();
}
//亮度
void MainWindow::brightnessFunction()
{
    //dialogLabel->setText(tr("Information Message Box"));
    //QMessageBox::information(this,tr("调整图像亮度功能，有待实现。"),tr("继续努力。"));
    trackBar->setWindowTitle("亮度");
    trackBar->show();
    trackBar->activateWindow();
    trackBar->move(trackBar->x(),trackBar->y());
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
//    setPopupMode(QToolButton::InstantPopup);
//    QjWidget *popup=new QWidget(this);

//    slider=new QSlider(Qt::Horizontal);
//    slider->setRange(0,100);
//    connect(slider,SIGNAL(valueChanged(int)),this,SLOT(setLineEditValue(int)));

//    labelbrightness=new QLabel(popup);
//    labelbrightness->setAlignment(Qt::AlignCenter);
//    labelbrightness->setNum(100);
//    labelbrightness->setMinimumWidth(labelbrightness->sizeHint().width());
//    connect(slider,SIGNAL(valueChanged(int)),labelbrightness,SLOT(setNum(int)));

//    QBoxLayout *popupLayout=new QBoxLayout(popup);
//    popupLayout->setMargin(2);
//    popupLayout->addWidget(slider);
//    popupLayout->addWidget(labelbrightness);

//    QWidgetAction *action=new QWidgetAction(this);
//    action->setDefaultWidget(popup);

//    menu=new QMenu(this);
//    menu->addAction(action);
//    SetMenu(menu);

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
    //dialogLabel->setText(tr("Information Message Box"));
    QMessageBox::information(this,tr("调整图像饱和度功能，有待实现。"),tr("继续努力。"));
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
    isPseudo=!isPseudo;
    adjustment();
    //dialogLabel->setText(tr("Information Message Box"));
    //QMessageBox::information(this,tr("调整图像伪彩色功能，有待实现。"),tr("继续努力。"));
}

//告警
//打开关闭
void MainWindow::openCloseFunction()
{
    //if(openCloseSet=="./icon/11_2.png")
    if(!isGaojing)
    {
        openClose->setIcon(QPixmap("./icon/11_1.png"));
        //openCloseSet="./icon/11_1.png";
        isGaojing = true;
        openClose->setToolTip("关闭告警");
    }
    else
    {
        openClose->setIcon(QPixmap("./icon/11_2.png"));
        //openCloseSet="./icon/11_2.png";
        isGaojing = false;
        openClose->setToolTip("打开告警");
    }
}
//手动
void MainWindow::manualFunction()
{
    //dialogLabel->setText(tr("Information Message Box"));
    QMessageBox::information(this,tr("手动捕获目标功能，有待实现。"),tr("继续努力。"));

    string imageurl="./s1/1.bmp";
    Mat mat1 =imread(imageurl);
    Rect rectan;
    rectan.x=1690;// = Rect(1490,250,100,100);
    rectan.y=350;
    rectan.width=200;
    rectan.height=200;

    //MainWindow *mw = (MainWindow*)parentWidget();
    //mw->test();

    drawRecOnPic2(mat1,rectan);
    cv::cvtColor(mat1, mat1, CV_BGR2RGB);
    loadPictureToLabel1();
}
//目标属性列表
void MainWindow::objectAttributeFunction()
{
    //dialogLabel->setText(tr("Information Message Box"));
    QMessageBox::information(this,tr("目标属性列表功能，有待实现。"),tr("继续努力。"));
}
//设置
void MainWindow::objectsFunction()
{
    //if(objectSet=="./icon/13_2.png")
    if(isMubiao)
    {
        objects->setIcon(QPixmap("./icon/13_2.png"));
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
    //dialogLabel->setText(tr("Information Message Box"));
    QMessageBox::information(this,tr("属性设置界面，有待实现。"),tr("继续努力。"));
}
//声音
void MainWindow::voiceFunction()
{
    //if(voiceSet=="./icon/15_2.png")
    if(isShengyin)
    {
        voice->setIcon(QPixmap("./icon/15_2.png"));
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

void MainWindow::adjustbrightness()
{
//    QImage a = ImageDeal.AdjustBrightness(QImage Img, int iBrightValue);
}

void MainWindow::test()
{
    //dialogLabel->setText(tr("Information Message Box"));
    QMessageBox::information(this,tr("属性设置界面，有待实现。"),tr("继续努力。"));
}

