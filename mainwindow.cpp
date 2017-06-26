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

//opencv��ͷ�ļ�
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

QDateTime dateTimeStart;
QDateTime dateTimeStop;
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    //�������������еı�����Ĭ��ֵ-------------------------------
    //��������ֹͣ
    isQidong = true;
    //��ͣ���Ǽ���
    isJixu = true;
    //�澯�������ǹر�
    isGaojing = true;
    //�����򿪻��ǹر�
    isShengyin = true;
    //Ŀ�������Ƿ����
    isMubiao = true;
    //ϵͳ���
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

    //�����ק���Ʊ�������ֵ
    isDrag1 = false;
    isDrag2 = false;
    isMove = false;

    //�Զ���ӿڴ�������������ʦSDK�滻--------------------------------
    in = MyInterface();
    selfProcessing();
    //this->jinProcessing();
    //---------------------------------------------------------

    //��ʱ�Դ�������������ʦSDK�滻--------------------------------
    //tempProcessing();
    //---------------------------------------------------------
    //��ʱ��
    timer=new QTimer();
    timer->setInterval(3000);
    timer->start();
    connect(timer, SIGNAL(timeout()), SLOT(onTimerOut()));
    //��ʱ������ȡϵͳʱ��

    timerSysTime=new QTimer();
    timerSysTime->setInterval(1000);
    timerSysTime->start();
    connect(timerSysTime, SIGNAL(timeout()), SLOT(onTimerOut2()));

    // ����������
    addMyToolBar();
    //�����˵���
    //���
//    QActionGroup *group=new QActionGroup(this);
//    QAction *startStopc=group->addAction(tr("��/ͣ"));
//    ui->monitoring->addAction(startStopc);
//    connect(startStopc,SIGNAL(triggered()),this,SLOT(startStopFunction()));

//    QAction *mstopc=group->addAction(tr("��ͣ"));
//    ui->monitoring->addAction(mstopc);
//    connect(mstopc,SIGNAL(triggered()),this,SLOT(mstopFunction()));

//    //�ط�
//    QActionGroup *group2=new QActionGroup(this);
//    QAction *openc=group2->addAction(tr("��"));
//    ui->playback->addAction(openc);
//    connect(openc,SIGNAL(triggered()),this,SLOT(openFunction()));

//    QAction *playc=group2->addAction(tr("����"));
//    ui->playback->addAction(playc);
//    connect(playc,SIGNAL(triggered()),this,SLOT(playFunction()));

//    QAction *rstopc=group2->addAction(tr("��ͣ"));
//    ui->playback->addAction(rstopc);
//    connect(rstopc,SIGNAL(triggered()),this,SLOT(rstopFunction()));

//    QAction *timeLinec=group2->addAction(tr("ʱ����"));
//    ui->playback->addAction(timeLinec);
//    connect(timeLinec,SIGNAL(triggered()),this,SLOT(timeLineFunction()));

//    //ͼ��
//    QActionGroup *group3=new QActionGroup(this);
//    QAction *automc=group3->addAction(tr("�Զ�"));
//    ui->image->addAction(automc);
//    connect(automc,SIGNAL(triggered()),this,SLOT(automFunction()));

//    QAction *brightnessc=group3->addAction(tr("����"));
//    ui->image->addAction(brightnessc);
//    connect(brightnessc,SIGNAL(triggered()),this,SLOT(brightnessFunction()));

//    QAction *saturationc=group3->addAction(tr("���Ͷ�"));
//    ui->image->addAction(saturationc);
//    connect(saturationc,SIGNAL(triggered()),this,SLOT(saturationFunction()));

//    QAction *pseudoColorc=group3->addAction(tr("α��ɫ"));
//    ui->image->addAction(pseudoColorc);
//    connect(pseudoColorc,SIGNAL(triggered()),this,SLOT(pseudoColorFunction()));

//    QAction *serialNumberc=group3->addAction(tr("���"));
//    ui->image->addAction(serialNumberc);
//    connect(serialNumberc,SIGNAL(triggered()),this,SLOT(serialNumberFunction()));

//    //�澯
//    QActionGroup *group4=new QActionGroup(this);
//    QAction *openClosec=group4->addAction(tr("��/��"));
//    ui->alarm->addAction(openClosec);
//    connect(openClosec,SIGNAL(triggered()),this,SLOT(openCloseFunction()));

//    QAction *manualc=group4->addAction(tr("�ֶ�"));
//    ui->alarm->addAction(manualc);
//    connect(manualc,SIGNAL(triggered()),this,SLOT(manualFunction()));

//    QAction *attributec=group4->addAction(tr("����"));
//    ui->alarm->addAction(attributec);
//    connect(attributec,SIGNAL(triggered()),this,SLOT(attributeFunction()));

//    QAction *setUpc=group4->addAction(tr("����"));
//    ui->alarm->addAction(setUpc);
//    connect(setUpc,SIGNAL(triggered()),this,SLOT(setUpFunction()));

//    QAction *voicec=group4->addAction(tr("����"));
//    ui->alarm->addAction(voicec);
//    connect(voicec,SIGNAL(triggered()),this,SLOT(voiceFunction()));

//    QAction *lightc=group4->addAction(tr("ָʾ��"));
//    ui->alarm->addAction(lightc);
//    connect(lightc,SIGNAL(triggered()),this,SLOT(lightFunction()));

    //����״̬��
    // addMyStatusBar();
    //ui->statusBar->addWidget(new QLabel(QObject::tr("�ۼƼ��ʱ��:")));
    //ui->statusBar->addWidget(new QLabel(QObject::tr("   ")));
    //ui->statusBar->addWidget(new QLabel(QObject::tr("���γ���Ŀ����Ϣ:")));
    //�Ҽ�
    //addAction(new QAction("Ŀ���б�",this));
    //widget1->addAction(new QAction("������ʾ��",widget1));
    //widget1->addAction(new QAction("��������ʾ��",widget1));
    //addAction(new QAction("���",this));
    //addAction(new QAction("�����ʾЧ��",this));
    //setContextMenuPolicy(Qt::ActionsContextMenu);

    //����
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

//�����ʦ�Ľӿڴ���
void MainWindow::jinProcessing(){
    //vector<MyObject> objs = in.getObjs2();
    if(in.getIntegratedData() == 0){
        //ͼƬ1
        //QString s1=in.getQJ1();
        //imageurl=s1.toStdString();
        Mat mat1 = in.getQJ1Mat();
        widget1->setMat(mat1);
        widget1->setObjects(in.getQj1Objs());
        widget1->setTracks(in.getTracks());
        widget1->draw();
        //ͼƬ2
        //QString s2=in.getQJ2();
        //imageurl2=s2.toStdString();
        Mat mat2 = in.getQJ2Mat();
        widget2->setMat(mat2);
        widget2->setObjects(in.getQj2Objs());
        widget2->setTracks(in.getTracks());
        widget2->draw();
        //ͼƬ3
        widget3->draw();
        //ͼƬ4
        widget4->draw();
        //ͼƬ5
        QString imageurl5=in.getHD();
        Mat mat5 =imread(imageurl5.toStdString());
        widget5->setMat(mat5);
        widget5->setPano(in.getPano());
        widget5->setObjects(in.getObjs());
        widget5->draw();
        //ͼƬ6
        QString imageurl6= in.getLD();
        Mat mat6 =imread(imageurl6.toStdString());
        widget6->setMat(mat6);
        widget6->setPano(in.getPano());
        widget6->setObjects(in.getObjs());
        widget6->draw();
    }
    else{
        this->selfProcessing();
    }
}

//�Զ���ӿڴ�����������������ʦSDK�滻------------------------------
void MainWindow::selfProcessing(){
    index=0;//���ڼ����ߵ���ʼλ��
//    index1=0;//����ȡ��һ����ͼƬ
//    index2=0;//����ȡ�ڶ�����ͼƬ
    vector<MyObject> objs = in.getObjs2();

    //ͼƬ1
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
    //ͼƬ2
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
    //ͼƬ3
    //Mat mat3 =imread(imageurl);
    widget3->draw();
    //drawUiLabelByCopy(mat3,3);
    //ͼƬ4
    //Mat mat4 =imread(imageurl2);
    //drawUiLabelByCopy(mat4,4);
    widget4->draw();
    //ͼƬ5
    QString imageurl5=in.getHD();
    Mat mat5 =imread(imageurl5.toStdString());
    widget5->setMat(mat5);
    widget5->setPano(mat1);
    widget5->setObjects(objs);
    widget5->draw();
    //drawUiLabel(mat5,5);
    //ͼƬ6
    QString imageurl6= in.getLD();
    Mat mat6 =imread(imageurl6.toStdString());
    widget6->setMat(mat6);
    widget6->setPano(mat1);
    widget6->setObjects(objs);
    widget6->draw();
    //drawUiLabel(mat6,6);

//    imageurl="./s1/1.bmp";
//    imageurl2="./s2/1.bmp";

//    //�洢��һ��
//    filename1 = "./s1/1.bmp";
//    filename2 = "./s1/2.bmp";
//    filename3 = "./s1/3.bmp";
//    filename4 = "./s1/4.bmp";
//    //�洢�ڶ���
//    filename5 = "./s2/1.bmp";
//    filename6 = "./s2/2.bmp";
//    filename7 = "./s2/3.bmp";
//    filename8 = "./s2/4.bmp";
//    //����һ���洢��vector��
//    vc1.push_back(filename1);
//    vc1.push_back(filename2);
//    vc1.push_back(filename3);
//    vc1.push_back(filename4);
//    //���ڶ����洢��vector��
//    vc2.push_back(filename5);
//    vc2.push_back(filename6);
//    vc2.push_back(filename7);
//    vc2.push_back(filename8);
}

//----------------------------------------------------------

//��ʱ�Դ�����������������ʦSDK�滻------------------------------
void MainWindow::tempProcessing(){
    index=0;//���ڼ����ߵ���ʼλ��
    index1=0;//����ȡ��һ����ͼƬ
    index2=0;//����ȡ�ڶ�����ͼƬ

    //ͼƬ1
    string imageurl="./s1/1.bmp";
    Mat mat1 =imread(imageurl);
    widget1->setMat(mat1);
    drawUiLabel(mat1,1);

    //ͼƬ2
    string imageurl2 = "./s2/1.bmp";
    Mat mat2 =imread(imageurl2);
    widget2->setMat(mat2);
    drawUiLabel(mat2,2);
    //ͼƬ3
    Mat mat3 =imread(imageurl);
    drawUiLabelByCopy(mat3,3);
    //ͼƬ4
    Mat mat4 =imread(imageurl2);
    drawUiLabelByCopy(mat4,4);
    //ͼƬ5
    string imageurl5="./0.png";//�����ͼƬ��
    Mat mat5 =imread(imageurl5);

    drawUiLabel(mat5,5);
    //ͼƬ6
    string imageurl6= "./0.png";//�����ͼƬ��
    Mat mat6 =imread(imageurl6);

    drawUiLabel(mat6,6);

    imageurl="./s1/1.bmp";
    imageurl2="./s2/1.bmp";

    //�洢��һ��
    filename1 = "./s1/1.bmp";
    filename2 = "./s1/2.bmp";
    filename3 = "./s1/3.bmp";
    filename4 = "./s1/4.bmp";
    //�洢�ڶ���
    filename5 = "./s2/1.bmp";
    filename6 = "./s2/2.bmp";
    filename7 = "./s2/3.bmp";
    filename8 = "./s2/4.bmp";
    //����һ���洢��vector��
    vc1.push_back(filename1);
    vc1.push_back(filename2);
    vc1.push_back(filename3);
    vc1.push_back(filename4);
    //���ڶ����洢��vector��
    vc2.push_back(filename5);
    vc2.push_back(filename6);
    vc2.push_back(filename7);
    vc2.push_back(filename8);
}

//----------------------------------------------------------



//���ƹ�����
void MainWindow::addMyToolBar()
{
    mainToolBar = addToolBar("monitoring");

    //��һ�鰴ť����غͺ��ˣ����лط�
    //����/ֹͣ
    mainToolBar->addSeparator();
    mainToolBar->addWidget(new QLabel("   "));
    //listLabel1=new QLabel(tr(" ��� "));
    //mainToolBar->addWidget(listLabel1);
    startStop = new QToolButton(this);
    startStop->setToolTip(tr("ֹͣ"));
    startStopSet="./icon/1_1.png";
    startStop->setIcon(QPixmap(startStopSet));
    startStop->setMinimumHeight(35);
    mainToolBar->addWidget(startStop);
    connect(startStop,SIGNAL(clicked()),this,SLOT(startStopFunction()));
    mainToolBar->addWidget(new QLabel("   "));

    //��ͣ/����
    mstop = new QToolButton(this);
    mstop->setToolTip(tr("��ͣ"));
    mstopSet="./icon/2_1.png";
    mstop->setIcon(QPixmap(mstopSet));
    mstop->setMinimumHeight(35);
    mainToolBar->addWidget(mstop);
    //mainToolBar->addSeparator();
    connect(mstop,SIGNAL(clicked()),this,SLOT(mstopFunction()));
    mainToolBar->addWidget(new QLabel("   "));
    //����
    back = new QToolButton(this);
    back->setToolTip(tr("����"));
    backSet="./icon/4_1.png";
    back->setIcon(QPixmap(backSet));
    back->setMinimumHeight(35);
    mainToolBar->addWidget(back);
    //mainToolBar->addSeparator();
    connect(back,SIGNAL(clicked()),this,SLOT(backFunction()));
    mainToolBar->addWidget(new QLabel("   "));
    //�ط�
    //listLabel2=new QLabel(tr(" �ط� "));
    //mainToolBar->addWidget(listLabel2);
    open = new QToolButton(this);
    open->setToolTip(tr("�ط�"));
    openSet="./icon/3_1.png";
    open->setIcon(QPixmap(openSet));
    open->setMinimumHeight(35);
    mainToolBar->addWidget(open);
    connect(open,SIGNAL(clicked()),this,SLOT(openFunction()));
    mainToolBar->addWidget(new QLabel("   "));


//    play = new QToolButton(this);
//    play->setToolTip(tr("����"));
//    playSet="./icon/4_1.png";
//    play->setIcon(QPixmap(playSet));
//    play->setMinimumHeight(35);
//    mainToolBar->addWidget(play);
//    connect(play,SIGNAL(clicked()),this,SLOT(playFunction()));

//    rstop = new QToolButton(this);
//    rstop->setToolTip(tr("��ͣ"));
//    rstopSet="./icon/2_1.png";
//    rstop->setIcon(QPixmap(rstopSet));
//    rstop->setMinimumHeight(35);
//    mainToolBar->addWidget(rstop);
//    connect(rstop,SIGNAL(clicked()),this,SLOT(rstopFunction()));


//    timeLine = new QToolButton(this);
//    timeLine->setToolTip(tr("ʱ����"));
//    timeLineSet="./icon/5_1.png";
//    timeLine->setIcon(QPixmap(timeLineSet));
//    timeLine->setMinimumHeight(35);
//    mainToolBar->addWidget(timeLine);
//    connect(timeLine,SIGNAL(clicked()),this,SLOT(timeLineFunction()));

    mainToolBar->addSeparator();

    //�ڶ��鰴ť��ͼ��
    //listLabel3=new QLabel(tr(" ͼ�� "));
    //mainToolBar->addWidget(listLabel3);
    mainToolBar->addWidget(new QLabel("   "));
    autom = new QToolButton(this);
    autom->setToolTip(tr("�Զ�"));
    automSet="./icon/6_1.png";
    autom->setIcon(QPixmap(automSet));
    autom->setMinimumHeight(35);
    mainToolBar->addWidget(autom);
    connect(autom,SIGNAL(clicked()),this,SLOT(automFunction()));
    mainToolBar->addWidget(new QLabel("   "));

    brightness = new QToolButton(this);
    brightness->setToolTip(tr("����"));
    brightnessSet="./icon/7_1.png";
    brightness->setIcon(QPixmap(brightnessSet));
    brightness->setMinimumHeight(35);
    mainToolBar->addWidget(brightness);
    connect(brightness,SIGNAL(clicked()),this,SLOT(brightnessFunction()));
    mainToolBar->addWidget(new QLabel("   "));

    saturation = new QToolButton(this);
    saturation->setToolTip(tr("���Ͷ�"));
    saturationSet="./icon/8_1.png";
    saturation->setIcon(QPixmap(saturationSet));
    saturation->setMinimumHeight(35);
    mainToolBar->addWidget(saturation);
    connect(saturation,SIGNAL(clicked()),this,SLOT(saturationFunction()));
    mainToolBar->addWidget(new QLabel("   "));

    pseudoColor = new QToolButton(this);
    pseudoColor->setToolTip(tr("α��ɫ"));
    pseudoColorSet="./icon/9_1.png";
    pseudoColor->setIcon(QPixmap(pseudoColorSet));
    pseudoColor->setMinimumHeight(35);
    mainToolBar->addWidget(pseudoColor);
    connect(pseudoColor,SIGNAL(clicked()),this,SLOT(pseudoColorFunction()));
    mainToolBar->addWidget(new QLabel("   "));

    mainToolBar->addSeparator();

    //�����鰴ť��ָʾ�ƣ���յ��һ��Ŀ��һյ��ƣ�����Ŀ���յ��ƣ�����Ŀ����յ��ƣ��ĸ�Ŀ����յ��ƣ����Ŀ�꼰���ϣ���յ���
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

    //�����飬��ʾ��ź�ϵͳ��ǰʱ��
    mainToolBar->addWidget(new QLabel("   "));
    serialNumber=new QLabel("ϵͳ��ţ�"+xtbh);//���
    mainToolBar->addWidget(serialNumber);
    mainToolBar->addWidget(new QLabel("   "));
    systime=new QLabel(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss ddd"));//ʱ��
    mainToolBar->addWidget(systime);
    mainToolBar->addWidget(new QLabel("   "));

    mainToolBar->addSeparator();

//    serialNumber = new QToolButton(this);
//    serialNumber->setToolTip(tr("���"));
//    serialNumberSet="./icon/17_1.png";
//    serialNumber->setIcon(QPixmap(serialNumberSet));
//    serialNumber->setMinimumHeight(35);
//    mainToolBar->addWidget(serialNumber);
//    connect(serialNumber,SIGNAL(clicked()),this,SLOT(serialNumberFunction()));

//    time = new QToolButton(this);
//    time->setToolTip(tr("ʱ��"));
//    timeSet="./icon/10_1.png";
//    time->setIcon(QPixmap(timeSet));
//    time->setMinimumHeight(35);
//    mainToolBar->addWidget(time);
//    mainToolBar->addSeparator();
//    connect(time,SIGNAL(clicked()),this,SLOT(timeFunction()));

    //�����飬�澯
    //listLabel4=new QLabel(tr(" �澯 "));
    //mainToolBar->addWidget(listLabel4);
    mainToolBar->addWidget(new QLabel("   "));
    openClose = new QToolButton(this);
    openClose->setToolTip(tr("�رո澯"));
    openCloseSet="./icon/11_1.png";
    openClose->setIcon(QPixmap(openCloseSet));
    openClose->setMinimumHeight(35);
    mainToolBar->addWidget(openClose);
    connect(openClose,SIGNAL(clicked()),this,SLOT(openCloseFunction()));
    mainToolBar->addWidget(new QLabel("   "));

    objectAttribute = new QToolButton(this);
    objectAttribute->setToolTip(tr("��������"));
    objectAttributeSet="./icon/17_1.png";
    objectAttribute->setIcon(QPixmap(objectAttributeSet));
    objectAttribute->setMinimumHeight(35);
    mainToolBar->addWidget(objectAttribute);
    connect(objectAttribute,SIGNAL(clicked()),this,SLOT(objectAttributeFunction()));
    mainToolBar->addWidget(new QLabel("   "));

    manual = new QToolButton(this);
    manual->setToolTip(tr("�ֶ�"));
    manualSet="./icon/12_1.png";
    manual->setIcon(QPixmap(manualSet));
    manual->setMinimumHeight(35);
    mainToolBar->addWidget(manual);
    connect(manual,SIGNAL(clicked()),this,SLOT(manualFunction()));
    mainToolBar->addWidget(new QLabel("   "));

    objects = new QToolButton(this);
    objects->setToolTip(tr("�ر�Ŀ�����Ը���"));
    objectSet="./icon/13_1.png";
    objects->setIcon(QPixmap(objectSet));
    objects->setMinimumHeight(35);
    mainToolBar->addWidget(objects);
    connect(objects,SIGNAL(clicked()),this,SLOT(objectsFunction()));
    mainToolBar->addWidget(new QLabel("   "));

    attribute = new QToolButton(this);
    attribute->setToolTip(tr("����"));
    attributeSet="./icon/14_1.png";
    attribute->setIcon(QPixmap(attributeSet));
    attribute->setMinimumHeight(35);
    mainToolBar->addWidget(attribute);
    connect(attribute,SIGNAL(clicked()),this,SLOT(attributeFunction()));
    mainToolBar->addWidget(new QLabel("   "));

    voice = new QToolButton(this);
    voice->setToolTip(tr("�ر�����"));
    voiceSet="./icon/15_1.png";
    voice->setIcon(QPixmap(voiceSet));
    voice->setMinimumHeight(35);
    mainToolBar->addWidget(voice);
    connect(voice,SIGNAL(clicked()),this,SLOT(voiceFunction()));
    mainToolBar->addWidget(new QLabel("   "));

    mainToolBar->addSeparator();

    mainToolBar->addWidget(new QLabel("   "));
    exitButton = new QToolButton(this);
    exitButton->setToolTip(tr("�˳�"));
    exitSet="./icon/16_1.png";
    exitButton->setIcon(QPixmap(exitSet));
    exitButton->setMinimumHeight(35);
    mainToolBar->addWidget(exitButton);
    connect(exitButton,SIGNAL(clicked()),this,SLOT(exitFunction()));
    mainToolBar->addWidget(new QLabel("   "));
    mainToolBar->addSeparator();
}

//��ȡϵͳ��ǰʱ�䶨ʱ��
void MainWindow::onTimerOut2(){
    systime->setText(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss ddd"));//ʱ��
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
//    //���µ�����
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

////    //���µ�����
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

//��ʱ������
void MainWindow::onTimerOut()
{
    this->selfTimerout();
    //this->jinTimerout();
}

//�Զ���ӿڶ�ʱ��
void MainWindow::selfTimerout(){
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

    //ͼƬ1
    QString s1=in.getQJ1();
    imageurl=s1.toStdString();
    Mat mat1 =imread(imageurl);
    widget1->setMat(mat1);
    widget1->setObjects(objs);
    widget1->setTracks(in.getTracks());
    widget1->draw();
    //qDebug()<<s1;
    //ͼƬ2
    QString s2=in.getQJ2();
    imageurl2=s2.toStdString();
    Mat mat2 =imread(imageurl2);
    widget2->setMat(mat2);
    widget2->setObjects(objs);
    widget2->setTracks(in.getTracks());
    widget2->draw();
    //qDebug()<<s2;
    //drawUiLabel(mat2,2);
    //ͼƬ3
    //Mat mat3 =imread(imageurl);
    widget3->draw();
    //drawUiLabelByCopy(mat3,3);
    //ͼƬ4
    //Mat mat4 =imread(imageurl2);
    //drawUiLabelByCopy(mat4,4);
    widget4->draw();
    //ͼƬ5
    //QString imageurl5=in.getHD();
    //Mat mat5 =imread(imageurl5.toStdString());
    //widget5->setMat(mat5);
    widget5->setPano(mat1);
    widget5->setObjects(objs);
    widget5->draw();
    //drawUiLabel(mat5,5);
    //ͼƬ6
    //QString imageurl6= in.getLD();
    //Mat mat6 =imread(imageurl6.toStdString());
    //widget6->setMat(mat6);
    widget6->setPano(mat1);
    widget6->setObjects(objs);
    widget6->draw();

    //���µ�һ����ͼƬ
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
//    //���µڶ�����ͼƬ
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
//    //���µ�����
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

////    //���µ�����
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

//�����ʦ�ӿڵĶ�ʱ������
void MainWindow::jinTimerout(){
    //vector<MyObject> objs = in.getObjs2();
    if(in.getIntegratedData() == 0){
        //ͼƬ1
        //QString s1=in.getQJ1();
        //imageurl=s1.toStdString();
        //qDebug()<<in.getObjs().size();
        Mat mat1 = in.getQJ1Mat();
        widget1->setMat(mat1);
        widget1->setObjects(in.getQj1Objs());
        widget1->setTracks(in.getTracks());
        widget1->draw();
        //ͼƬ2
        //QString s2=in.getQJ2();
        //imageurl2=s2.toStdString();
        Mat mat2 = in.getQJ2Mat();
        widget2->setMat(mat2);
        widget2->setObjects(in.getQj2Objs());
        widget2->setTracks(in.getTracks());
        widget2->draw();
        //ͼƬ3
        widget3->draw();
        //ͼƬ4
        widget4->draw();
        //ͼƬ5
        //QString imageurl5=in.getHD();
        //Mat mat5 =imread(imageurl5.toStdString());
        //widget5->setMat(mat5);
        widget5->setPano(in.getPano());
        widget5->setObjects(in.getObjs());
        widget5->draw();
        //ͼƬ6
        //QString imageurl6= in.getLD();
        //Mat mat6 =imread(imageurl6.toStdString());
        //widget6->setMat(mat6);
        widget6->setPano(in.getPano());
        widget6->setObjects(in.getObjs());
        widget6->draw();
    }
    else{
        this->selfTimerout();
    }
}

//���´��������ק�¼�����ȫ����ʾ��1����2��ѡ��������£���ȫ����ʾ��1����2������Ŀ��������ʾ�����򿽱�ͼ������ʾ����Ŀ����������ʾ�����򿽱�ͼ��������ʾ����
void MainWindow::mousePressEvent(QMouseEvent *e)
{
    //qDebug()<<"���ѹ���¼�����mainframe";
    if(e->button() == Qt::LeftButton)
    {
        //isRect = false;
        //�ж��Ƿ�����ק������
        QPoint position1 = e->pos();//e->globalPos() - this->pos();
        //��ʼ��������ȫ����ʾ��1�е����
        if((position1.x() <= this->widget1->pos().x()+this->widget1->width()) &&(position1.x() >= this->widget1->pos().x()) && (position1.y() <= this->widget1->pos().y()+this->widget1->height()) &&(position1.y() >= this->widget1->pos().y())){
            isDrag1 = true;
            isDrag2 = false;
        }
        //��ʼ��������ȫ����ʾ��2�е����
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
    //�ж�Ŀ�ĵ���������ʾ���ı�־����
    boolean target3 = false;
    boolean target4 = false;
    QPoint position2 = e->pos();//e->globalPos() - this->pos();

    //�ж�Ŀ�ĵ���������ʾ�������
    if((position2.x() <= this->widget3->pos().x()+this->widget3->width()) &&(position2.x() >= this->widget3->pos().x()) && (position2.y() <= this->widget3->pos().y()+this->widget3->height()) &&(position2.y() >= this->widget3->pos().y())){
        target3 = true;
        target4 = false;
    }
    //�ж�Ŀ�ĵ�����������ʾ�������
    else if((position2.x() <= this->widget4->pos().x()+this->widget4->width()) &&(position2.x() >= this->widget4->pos().x()) && (position2.y() <= this->widget4->pos().y()+this->widget4->height()) &&(position2.y() >= this->widget4->pos().y())){
        target4 = true;
        target3 = false;
    }
    else{
        isDrag1 = false;
        isDrag2 = false;
        isMove = false;
    }
    //4�����
    //1. �����������ȫ����ʾ��1������ȫ����ʾ��1����ѡ��򣬲���Ŀ��������ʾ�����򿽱�ȫ����ʾ��1ѡ����ڵ�ͼ������ʾ��
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

        //��������ʾ����������Ŀ��
        vector<MyObject> objs3;
        int count = widget1->objs.size();
        for(int i = 0; i < count; i++){
            MyObject obj = widget1->objs[i];
            if(widget1->isObjSelected3(obj)){
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
        aa=(&img)->copy(widget1->getQRectan3());
        Mat image3 = QImageToMat(aa);
        Mat image33 = Mat(dsize,CV_32S);
        cv::resize(image3, image33,dsize);
        widget3->setMat(image33);
        widget3->draw();
    }
    //2. �����������ȫ����ʾ��2������ȫ����ʾ��2����ѡ��򣬲���Ŀ��������ʾ�����򿽱�ȫ����ʾ��2ѡ����ڵ�ͼ������ʾ��
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


        //��������ʾ����������Ŀ��
        vector<MyObject> objs3;
        int count = widget2->objs.size();
        for(int i = 0; i < count; i++){
            MyObject obj = widget2->objs[i];
            if(widget2->isObjSelected3(obj)){
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
        aa=(&img)->copy(widget2->getQRectan3());
        Mat image3 = QImageToMat(aa);
        Mat image33 = Mat(dsize,CV_32S);
        cv::resize(image3, image33,dsize);
        widget3->setMat(image33);
        widget3->draw();
    }
    //3. �����������ȫ����ʾ��1������ȫ����ʾ��1����ѡ��򣬲���Ŀ����������ʾ�����򿽱�ȫ����ʾ��1ѡ����ڵ�ͼ��������ʾ��
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

        //��������ʾ����������Ŀ��
        vector<MyObject> objs4;
        int count = widget1->objs.size();
        for(int i = 0; i < count; i++){
            MyObject obj = widget1->objs[i];
            if(widget1->isObjSelected4(obj)){
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
        aa=(&img)->copy(widget1->getQRectan4());
        Mat image4 = QImageToMat(aa);
        Mat image44 = Mat(dsize,CV_32S);
        cv::resize(image4, image44,dsize);
        widget4->setMat(image44);
        widget4->draw();
    }
    //4. �����������ȫ����ʾ��2������ȫ����ʾ��2����ѡ��򣬲���Ŀ����������ʾ�����򿽱�ȫ����ʾ��2ѡ����ڵ�ͼ��������ʾ��
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

        //��������ʾ����������Ŀ��
        vector<MyObject> objs4;
        int count = widget2->objs.size();
        for(int i = 0; i < count; i++){
            MyObject obj = widget2->objs[i];
            if(widget2->isObjSelected4(obj)){
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
        aa=(&img)->copy(widget2->getQRectan4());
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
    //���»���ͼƬ��
}

Mat MainWindow::setPseudocolor(Mat& image){
        Mat img_pseudocolor(image.rows, image.cols, CV_8UC3);
        for (int y = 0; y < image.rows; y++)//תΪα��ɫͼ��ľ����㷨
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

//---xiaotian ���ƽ����ϵ�ͼƬ3  ͼƬ4
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


//---xiaotian ���ƽ����ϵ�ͼƬ1 ͼƬ2 ͼƬ5 ͼƬ6
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
         //ͼƬ1
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
        //ͼƬ2
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
        //ͼƬ5
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
        //ͼƬ6
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



//---xiaotian   ����ͼƬ��label�ϡ�
void MainWindow::loadPictureToLabel(QLabel *label, QImage image){
    QPixmap pixmap1 = QPixmap::fromImage(image);
    label->setPixmap(pixmap1);
    label->setScaledContents(true);
    //�ͷ�image
    //delete & image;
}

//����ͼƬ��Label1��
void MainWindow::loadPictureToLabel1(){
    loadPictureToLabel(label,imgLabel1);
}

//����ͼƬ��Label2��
void MainWindow::loadPictureToLabel2(){
    loadPictureToLabel(label2,imgLabel2);
}

//����ͼƬ��Label3��
void MainWindow::loadPictureToLabel3(){
    loadPictureToLabel(label3,imgLabel3);
}

//����ͼƬ��Label4��
void MainWindow::loadPictureToLabel4(){
    loadPictureToLabel(label4,imgLabel4);
}

//����ͼƬ��Label5��
void MainWindow::loadPictureToLabel5(){
    loadPictureToLabel(label5,imgLabel5);
}

//����ͼƬ��Label6��
void MainWindow::loadPictureToLabel6(){
    loadPictureToLabel(label6,imgLabel6);
}

//---xiaotian   ͼ���ϻ��ƾ��ο�
void MainWindow::drawRecOnPic(Mat image, vector<Rectan> rectans){
    //��ͼ���ϻ����Ρ�
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

//�������ѡȡ�ľ���
void MainWindow::drawRecOnPic2(Mat image, Rect rect){
    //��ͼ���ϻ����Ρ�
    rectangle(image,rect,Scalar(0,0,255),1,1,0);
    cv::cvtColor(image, image, CV_BGR2RGB);
    //QImage imglabel;
//    imgLabel = MatToQImage(image);
//    //return imgLabel;
}

//---xiaotian  ͼ���ϻ��Ʊ�ߺ;��ο�
void MainWindow::drawScaleAndRecOnPic(Mat image, vector<Rectan> rectans, double startw, double starth){
    //��ͼ���ϻ����Ρ�
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
    //��ͼ���ϻ����
    paintScale(image,startw,starth);
    cv::cvtColor(image,image,CV_BGR2RGB);
    //QImage imglabel3;
//    imgLabel = MatToQImage(image);
//    return imgLabel;
}

//---xiaotian  ͼ���ϻ��ƶ���κ�Բ
void MainWindow::drawCircleOnPic(Mat image, vector<Point> point, double x, double y){
    //��ͼ���ϻ������
    int count = point.size();
    for (int i = 0; i <count;i+=2)
    {
        Point point1 = point[i];
        Point point2 = point[i+1];
        line(image,point1,point2,Scalar(255,255,0),1,8,0);
    }
    //��ͼ���ϻ�Բ��
    paintCircle(image,x,y);
    cv::cvtColor(image,image,CV_BGR2RGB);
    //QImage imglabel;
//    imgLabel = MatToQImage(image);
//    return imgLabel;
}


//����
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
//Բ
void MainWindow::paintCircle(Mat image,double x,double y)
{
    //QImage img;
    Point pointInterest;//�����㣬���Ի���ͼ����,��Բ�ε��Բ��
    pointInterest.x=x;//��������ͼ���к�����
    pointInterest.y=y;//��������ͼ����������
    circle(image, pointInterest, 2, Scalar(255, 0,0 ),-1,8,2);//��ͼ���л��������㣬2��Բ�İ뾶
    //img = QImage((const unsigned char*)(image.data),image.cols,image.rows, image.cols*image.channels(),  QImage::Format_RGB888);
    //return img;
}

//�����
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
        //�����д��
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

//����/ֹͣ
void MainWindow::startStopFunction()
{
    //if(startStopSet=="./icon/1_2.png")
    if (isQidong)
    {
        startStop->setIcon(QPixmap("./icon/4_1.png"));
        startStop->setToolTip("����");
        //startStopSet="./icon/1_1.png";
        isQidong = false;
        //dialogLabel->setText(tr("Information Message Box"));
        //QMessageBox::information(this,tr("����ȫ��ϵͳ"),tr("ͨ������ʦSDK��ʵ�ּ��������"));
    }
    else
    {
        startStop->setIcon(QPixmap("./icon/1_1.png"));
        startStop->setToolTip("ֹͣ");
        isQidong = true;
        //startStopSet="./icon/1_2.png";
//        dialogLabel->setText(tr("Information Message Box"));
//        QMessageBox::information(this,tr("����ȫ��ϵͳ"),tr("ͨ������ʦSDK��ʵ�ּ��ֹͣ��"));
    }

}
//��ͣ/����
void MainWindow::mstopFunction()
{
    //if(mstopSet=="./icon/2_2.png")
    if(isJixu)
    {
        mstop->setIcon(QPixmap("./icon/4_1.png"));
        mstop->setToolTip("����");
        isJixu = false;
        //mstopSet="./icon/2_1.png";
//        dialogLabel->setText(tr("Information Message Box"));
//        QMessageBox::information(this,tr("����ȫ��ϵͳ"),tr("ͨ������ʦSDK��ʵ�ּ����ͣ��"));
    }
    else
    {
        mstop->setIcon(QPixmap("./icon/2_1.png"));
        mstop->setToolTip("��ͣ");
        isJixu = true;
        //mstopSet="./icon/2_2.png";
//        dialogLabel->setText(tr("Information Message Box"));
//        QMessageBox::information(this,tr("����ȫ��ϵͳ"),tr("ͨ������ʦSDK��ʵ�ּ�ؼ�����"));
    }

}
//����
void MainWindow::backFunction()
{
    //dialogLabel->setText(tr("Information Message Box"));
    QMessageBox::information(this,tr("���˹��ܣ��д�ʵ�֡�"),tr("����Ŭ����"));
}
//�ط�
void MainWindow::openFunction()
{
    startTime=new QLabel(QWidget::tr("��ʼʱ��"));
    //��ʼʱ��ѡ���
    startTimeSet=new QDateTimeEdit(QDateTime::currentDateTime(), this);
    startTimeSet->setCalendarPopup(true);
    startTimeSet->setDisplayFormat("yyyy-MM-dd HH:mm:ss");
    //����ʱ��ѡ���
    stopTime=new QLabel(QWidget::tr("����ʱ��"));
    stopTimeSet=new QDateTimeEdit(QDateTime::currentDateTime(), this);
    stopTimeSet->setCalendarPopup(true);
    stopTimeSet->setDisplayFormat("yyyy-MM-dd HH:mm:ss");
    queDing=new QPushButton("ȷ��",this);
    connect(queDing,SIGNAL(clicked()),this,SLOT(queDingFunction()));
    quXiao=new QPushButton("ȡ��",this);
    connect(quXiao,SIGNAL(clicked()),this,SLOT(quXiaoFunction()));
    //�������񲼾�
    gridLayout=new QGridLayout(this);
    gridLayout->addWidget(startTime,0,0);
    gridLayout->addWidget(startTimeSet,0,2);
    gridLayout->addWidget(stopTime,0,3);
    gridLayout->addWidget(stopTimeSet,0,5);

    gridLayout->addWidget(queDing,3,2);
    gridLayout->addWidget(quXiao,3,3);
    gridLayout->setAlignment(Qt::AlignCenter);
    widgetNew=new QWidget;
    widgetNew->setWindowTitle("ʱ��ѡ���");
    widgetNew->setLayout(gridLayout);
    widgetNew->setMinimumSize(QSize(600,150));
    widgetNew->setMaximumSize(QSize(600,150));
    widgetNew->move((QApplication::desktop()->width() - widgetNew->width())/2,
              (QApplication::desktop()->height() - widgetNew->height())/2);
    //widgetNew->setWindowFlags(Qt::WindowStaysOnTopHint);
    widgetNew->show();

}
void MainWindow::queDingFunction()
{
    dateTimeStart=startTimeSet->dateTime();
    dateTimeStop=stopTimeSet->dateTime();
    int start=dateTimeStart.toTime_t();
    int stop=dateTimeStop.toTime_t();
    if(start==stop)
    {
        QMessageBox::information(this,tr("����"),tr("��ʼʱ��ͽ���ʱ����ͬ"));
        widgetNew->close();
        widgetNew->show();
    }
    else if(start>stop)
    {
        QMessageBox::information(this,tr("����"),tr("��ʼʱ����ڽ���ʱ��"));
        widgetNew->close();
        widgetNew->show();
    }
    else
    {
        //qDebug()<<(stop-start);
        widgetNew->close();
        backwindow=new BackWindow(this);
        backwindow->show();
    }

}
void MainWindow::quXiaoFunction()
{
    widgetNew->close();
}
//ͼ��
//�Զ�
void MainWindow::automFunction()
{
   // dialogLabel->setText(tr("Information Message Box"));
    //QMessageBox::information(this,tr("�Զ�ɫ�ʹ��ܣ��д�ʵ�֡�"),tr("����Ŭ����"));
    bright_TrackbarValue = 0;
    trackBar->setPosition(0);
    isPseudo = false;
    adjustment();
}
//����
void MainWindow::brightnessFunction()
{
    //dialogLabel->setText(tr("Information Message Box"));
    //QMessageBox::information(this,tr("����ͼ�����ȹ��ܣ��д�ʵ�֡�"),tr("����Ŭ����"));
    trackBar->setWindowTitle("����");
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
//    createTrackbar("����","����ȫ������ϵͳ",&g_nTrackbarValue,threshval,on_trackbar);
}

//void MainWindow::on_trackbar(int, void*)
//{
//    Mat bw = threshval < 128 ? (img < threshval) : (img > threshval);//���threshvalС��128����bw����ӦԪ��С��threshvalʱ��255������threshvalʱ��0�����threshval����128����bw��ӦԪ�ش���threshvalʱ��255��С��threshvalʱ��0
//    //����������
//    vector<vector<Point> > contours;//�������������ÿ��vector<Point>Ԫ�ز�һ��ֻ��ʾһ��������
//    vector<Vec4i> hierarchy;//�������֮������˹�ϵ��hierarchy[idx][0]�� hierarchy[idx][1]�� hierarchy[idx][2]�� hierarchy[idx][3]�ֱ��ʾ����Ϊidx��������ǰһ������һ�����ӡ���������Ӧ��������������Ϊ0ʱ����ʾ��Ӧ�����������ڡ�
//    findContours( bw, contours, hierarchy, CV_RETR_CCOMP, CV_CHAIN_APPROX_SIMPLE );//��������
//    Mat dst = Mat::zeros(img.size(), CV_8UC3);//��ʼ��dst
//    if( !contours.empty() && !hierarchy.empty() )//��ʼ����
//    {
//        //�������ж������������������ɫֵ���Ƹ���������ɲ���
//        int idx = 0;
//        for( ; idx >= 0; idx = hierarchy[idx][0] )
//        {
//            Scalar color( (rand()&255), (rand()&255), (rand()&255) );
//            drawContours( dst, contours, idx, color, CV_FILLED, 8, hierarchy );//�����������
//        }
//    }
//    imshow("Connected Components", dst);//��ʾ����
//}
//���Ͷ�
void MainWindow::saturationFunction()
{
    //dialogLabel->setText(tr("Information Message Box"));
    QMessageBox::information(this,tr("����ͼ�񱥺Ͷȹ��ܣ��д�ʵ�֡�"),tr("����Ŭ����"));
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
//α��ɫ
void MainWindow::pseudoColorFunction()
{
    isPseudo=!isPseudo;
    adjustment();
    //dialogLabel->setText(tr("Information Message Box"));
    //QMessageBox::information(this,tr("����ͼ��α��ɫ���ܣ��д�ʵ�֡�"),tr("����Ŭ����"));
}

//�澯
//�򿪹ر�
void MainWindow::openCloseFunction()
{
    //if(openCloseSet=="./icon/11_2.png")
    if(!isGaojing)
    {
        openClose->setIcon(QPixmap("./icon/11_1.png"));
        //openCloseSet="./icon/11_1.png";
        isGaojing = true;
        openClose->setToolTip("�رո澯");
    }
    else
    {
        openClose->setIcon(QPixmap("./icon/11_2.png"));
        //openCloseSet="./icon/11_2.png";
        isGaojing = false;
        openClose->setToolTip("�򿪸澯");
    }
}
//�ֶ�
void MainWindow::manualFunction()
{
    //dialogLabel->setText(tr("Information Message Box"));
    QMessageBox::information(this,tr("�ֶ�����Ŀ�깦�ܣ��д�ʵ�֡�"),tr("����Ŭ����"));

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
//Ŀ�������б�
void MainWindow::objectAttributeFunction()
{
    //dialogLabel->setText(tr("Information Message Box"));
    QMessageBox::information(this,tr("Ŀ�������б��ܣ��д�ʵ�֡�"),tr("����Ŭ����"));
}
//����
void MainWindow::objectsFunction()
{
    //if(objectSet=="./icon/13_2.png")
    if(isMubiao)
    {
        objects->setIcon(QPixmap("./icon/13_2.png"));
        isMubiao = false;
        //objectSet="./icon/13_1.png";
        objects->setToolTip("����Ŀ�����Ը���");
    }
    else
    {
        objects->setIcon(QPixmap("./icon/13_1.png"));
        isMubiao = true;
        //objectSet="./icon/13_2.png";
        objects->setToolTip("�ر�Ŀ�����Ը���");
    }
}
//Ŀ�������б�
void MainWindow::attributeFunction()
{
    //dialogLabel->setText(tr("Information Message Box"));
    QMessageBox::information(this,tr("�������ý��棬�д�ʵ�֡�"),tr("����Ŭ����"));
}
//����
void MainWindow::voiceFunction()
{
    //if(voiceSet=="./icon/15_2.png")
    if(isShengyin)
    {
        voice->setIcon(QPixmap("./icon/15_2.png"));
        isShengyin = false;
        //voiceSet="./icon/15_1.png";
        voice->setToolTip("������");
    }
    else
    {
        voice->setIcon(QPixmap("./icon/15_1.png"));
        isShengyin = true;
        //voiceSet="./icon/15_2.png";
        voice->setToolTip("�ر�����");

    }
}

void MainWindow::exitFunction(){
    QApplication::closeAllWindows();
}

//�˳�ϵͳ�¼�
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
    QMessageBox::information(this,tr("�������ý��棬�д�ʵ�֡�"),tr("����Ŭ����"));
}

