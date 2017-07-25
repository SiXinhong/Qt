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
#include <QDir>


//////////////////////////////ZC/////////////////
SOCKET hSocket;			//�¼��������ӵ��׽���
WSAEVENT hEvent;			//�׽����������¼�����
int datalen;			//����һ����������ʾ�ӵ�ǰ����������еõ������ݳ���
char sendbuffer[SEND_BUFFER_SIZE];				//�����һ��socket�ķ��ͻ�����
char recvbuffer[RECV_BUFFER_SIZE];				//�����һ��socket�Ľ��ջ�����
char *databuffer = (char *)malloc(DATA_BUFFER_SIZE);//������ݵľ�̬������

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
    this->objectAttributes=new ObjectAttributes(&this->in);
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
    xtbh = QString("BJ036Aվλ");
    //-------------------------------------------------------
    //�жϴ����Ƿ��
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

    //�����ק���Ʊ�������ֵ
    isDrag1 = false;
    isDrag2 = false;
    isMove = false;

    ////////////////zc///////////////////////
    //ͨ������
    //MySocketInitial();

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
    //����
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
    delete objectAttributes;
    delete cmixer;
    delete sound;
}

//�����ʦ�Ľӿڴ���
void MainWindow::jinProcessing(){
    //vector<MyObject> objs = in.getObjs2();
    if(in.getIntegratedData() == 0){
        //        //ͼƬ1
        //        //QString s1=in.getQJ1();
        //        //imageurl=s1.toStdString();
        //std::cout<<"get data ok "<<std::endl;
        //��ȫ���ϻ����Σ����֣��켣��
        Mat mat = in.getPano();

        vector<MyObject> objs = in.getObjs();
        vector<MyObjectTrack> tracks = in.getTracks();

        int count = objs.size();
        for (int i = 0; i < count;i++)
        {
            //�������box
            MyObject obj = objs[i];
            rectangle(mat,obj.getRect(),obj.getColor(),2,1,0);
            cv::cvtColor(mat, mat, CV_BGR2RGB);
            //���켣
            for(int ii = 0; ii < tracks.size(); ii++){
                MyObjectTrack track = tracks[ii];
                int id = track.getId();
                vector<Point> points = track.getTrack();
                if(id == obj.getID()){
                    for(int iii = 0; iii < points.size(); iii++){
                        Point point = points[iii];
                        circle(mat, point, 2, obj.getColor(),-1,8,2);//��ͼ���л��������㣬2��Բ�İ뾶
                        if(iii >= 1){
                            Point point2 = points[iii-1];
                            line(mat,point,point2,obj.getColor(),1,8,0);
                        }
                    }
                }
            }
            cv::cvtColor(mat, mat, CV_BGR2RGB);
            //���������ĵ��λ��
            if(isMubiao){
                int x = (int)(this->getDirectionX(obj.getCenPoint().x, mat));
                int y = (int)(10-this->getDirectionY(obj.getCenPoint().y, mat)/2);//(10-10*(this->getDirectionY(obj.getCenPoint().y)-this->getDirectionY())/(this->getDirectionY2()-this->getDirectionY()));//endh - i*(endh-starth)/10
                QString tx = QString::number(x,10);
                QString ty = QString::number(y,10);
                QString tstr = "x="+tx+",y="+ty;
                string str = tstr.toStdString();
                //qDebug()<<tstr;
                Point p = Point(obj.getRect().x+obj.getRect().width,obj.getRect().y+obj.getRect().height);
                putText(mat,str,p,3,1,obj.getColor());
            }
            cv::cvtColor(mat, mat, CV_BGR2RGB);
        }
        cv::cvtColor(mat, mat, CV_BGR2RGB);

        //Ȼ������2��

        Mat mat1, mat2;
        mat(Rect(0,0,mat.cols/2,mat.rows)).copyTo(mat1);
        mat(Rect(mat.cols/2,0,mat.cols/2,mat.rows)).copyTo(mat2);

        widget1->setPano(mat);
        widget1->setMat(mat1);
        widget1->setObjects(in.getObjs());
        widget1->setTracks(in.getTracks());
        widget1->draw();
        //ͼƬ2
        //        //QString s2=in.getQJ2();
        //        //imageurl2=s2.toStdString();
        widget2->setPano(mat);
        widget2->setMat(mat2);
        widget2->setObjects(in.getObjs());
        widget2->setTracks(in.getTracks());
        widget2->draw();
        //ͼƬ3
        widget3->setPano(mat);
        widget3->setAllObjects(in.getObjs());
        widget3->draw();
        //ͼƬ4
        widget4->setPano(mat);
        widget4->setAllObjects(in.getObjs());
        widget4->draw();
        //        //ͼƬ5
        widget5->setPano(in.getPano());
        QString imageurl5=in.getHD();
        Mat mat5 =imread(imageurl5.toStdString());
        widget5->setMat(mat5);
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
    in.getIntegratedData2();

    vector<MyObject> objs = in.getObjs2();

    //ͼƬ1
    //    QString s1=in.getQJ1();
    //    imageurl=s1.toStdString();
    //    Mat mat1 =imread(imageurl);

    //��ȫ���ϻ����Σ����֣��켣��
    Mat mat = in.getPano().clone();
    //vector<MyObject> objs = in.getObjs();
    vector<MyObjectTrack> tracks = in.getTracks();

    int count = objs.size();
    for (int i = 0; i < count;i++)
    {
        //�������box
        MyObject obj = objs[i];
        rectangle(mat,obj.getRect(),obj.getColor(),2,1,0);
        cv::cvtColor(mat, mat, CV_BGR2RGB);
        //���켣
        for(int ii = 0; ii < tracks.size(); ii++){
            MyObjectTrack track = tracks[ii];
            int id = track.getId();
            vector<Point> points = track.getTrack();
            if(id == obj.getID()){
                for(int iii = 0; iii < points.size(); iii++){
                    Point point = points[iii];
                    circle(mat, point, 2, obj.getColor(),-1,8,2);//��ͼ���л��������㣬2��Բ�İ뾶
                    if(iii >= 1){
                        Point point2 = points[iii-1];
                        line(mat,point,point2,obj.getColor(),1,8,0);
                    }
                }
            }
        }
        cv::cvtColor(mat, mat, CV_BGR2RGB);
        //���������ĵ��λ��
        if(isMubiao){
            int x = (int)(this->getDirectionX(obj.getCenPoint().x, mat));
            int y = (int)(10-this->getDirectionY(obj.getCenPoint().y, mat)/2);//(10-10*(this->getDirectionY(obj.getCenPoint().y)-this->getDirectionY())/(this->getDirectionY2()-this->getDirectionY()));//endh - i*(endh-starth)/10
            QString tx = QString::number(x,10);
            QString ty = QString::number(y,10);
            QString tstr = "x="+tx+",y="+ty;
            string str = tstr.toStdString();
            //qDebug()<<tstr;
            Point p = Point(obj.getRect().x+obj.getRect().width,obj.getRect().y+obj.getRect().height);
            putText(mat,str,p,3,1,obj.getColor());
        }
        cv::cvtColor(mat, mat, CV_BGR2RGB);
    }
    cv::cvtColor(mat, mat, CV_BGR2RGB);

    //Ȼ������2��

    Mat mat1, mat2;
    mat(Rect(0,0,mat.cols/2,mat.rows)).copyTo(mat1);
    mat(Rect(mat.cols/2,0,mat.cols/2,mat.rows)).copyTo(mat2);

    if(this->isPseudo==true)
        mat1=setPseudocolor(mat1);
    updateBright(mat1);
    updateContrast(mat1);
    widget1->setPano(mat);
    widget1->setMat(mat1);
    widget1->setObjects(objs);
    widget1->setTracks(in.getTracks());
    //qDebug()<<mat1.cols;
    widget1->draw();

    //ͼƬ2
    //    QString s2=in.getQJ2();
    //    imageurl2=s2.toStdString();
    //    Mat mat2 =imread(imageurl2);

    if(this->isPseudo==true)
        mat2=setPseudocolor(mat2);
    updateBright(mat2);
    updateContrast(mat2);
    widget2->setPano(mat);
    widget2->setMat(mat2);
    widget2->setObjects(objs);
    widget2->setTracks(in.getTracks());

    widget2->draw();

    //ͼƬ3
    //qDebug()<<mat2.cols;
    widget3->setPano(mat);
    widget3->setAllObjects(in.getObjs());
    widget3->draw();
    //qDebug()<<mat2.cols;
    //ͼƬ4
    widget4->setPano(mat);
    widget4->setAllObjects(in.getObjs());
    widget4->draw();
    //ͼƬ5
    widget5->setPano(in.getPano());
    QString imageurl5=in.getHD();
    Mat mat5 =imread(imageurl5.toStdString());
    widget5->setMat(mat5);
    widget5->setObjects(objs);
    widget5->draw();
    //ͼƬ6
    QString imageurl6= in.getLD();
    Mat mat6 =imread(imageurl6.toStdString());
    widget6->setMat(mat6);
    widget6->setPano(in.getPano());
    widget6->setObjects(objs);
    widget6->draw();

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

    //ͼ��̫������С��Ļ����ʾ��ȫ����Ϊ������Ļ����Զ�����ͼ��Ĵ�С
    QDesktopWidget* desktopWidget = QApplication::desktop();
    QRect screenRect = desktopWidget->screenGeometry();  //��Ļ����
    int screenWidth=screenRect.width();
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

    //��ͼ��
    //mainToolBar->addWidget(new QLabel(""));
    QPixmap pixmap3("./icon/fujirui.png");
    QPixmap fitpixmap3=pixmap3.scaled(buttonSize*1.7,buttonSize*1.7, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    QLabel *tuBiao=new QLabel(this);
    tuBiao->setPixmap(fitpixmap3);
    mainToolBar->addWidget(tuBiao);
    mainToolBar->addWidget(new QLabel(" "));
    //��һ�鰴ť����غͺ��ˣ����лط�
    //����/ֹͣ

    startStop = new QToolButton(this);
    startStop->setToolTip(tr("ֹͣ"));
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

    //��ͣ/����
    mstop = new QToolButton(this);
    mstop->setToolTip(tr("��ͣ"));
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

    //����
    back = new QToolButton(this);
    back->setToolTip(tr("����"));
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

    //�ط�
    open = new QToolButton(this);
    open->setToolTip(tr("�ط�"));
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
    //�ڶ��鰴ť��ͼ��
    //�Զ�
    autom = new QToolButton(this);
    autom->setToolTip(tr("�Զ�"));
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

    //����
    brightness = new QToolButton(this);
    brightness->setToolTip(tr("����"));
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

    //�Աȶ�
    saturation = new QToolButton(this);
    saturation->setToolTip(tr("�Աȶ�"));
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

    //α��ɫ
    pseudoColor = new QToolButton(this);
    pseudoColor->setToolTip(tr("α��ɫ"));
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


    //�����鰴ť��ָʾ�ƣ���յ��һ��Ŀ��һյ��ƣ�����Ŀ���յ��ƣ�����Ŀ����յ��ƣ��ĸ�Ŀ����յ��ƣ����Ŀ�꼰���ϣ���յ���
    QPixmap pixmap1("./icon/16_1.png");
    QPixmap pixmap2("./icon/16_2.png");
    QPixmap fitpixmap1=pixmap1.scaled(buttonSize,buttonSize, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    QPixmap fitpixmap2=pixmap2.scaled(buttonSize,buttonSize, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);

    vector<MyObject> vec = in.getObjs2();
    if(vec.size()==0)
    {
        light1=new QLabel(this);
        light1->setPixmap(fitpixmap2);
        vbox3->addWidget(light1);
        //vbox3->addWidget(new QLabel(" "));

        light2=new QLabel(this);
        light2->setPixmap(fitpixmap2);
        vbox3->addWidget(light2);
        //vbox3->addWidget(new QLabel(" "));

        light3=new QLabel(this);
        light3->setPixmap(fitpixmap2);
        vbox3->addWidget(light3);
        //vbox3->addWidget(new QLabel(" "));

        light4=new QLabel(this);
        light4->setPixmap(fitpixmap2);
        vbox3->addWidget(light4);
        // vbox3->addWidget(new QLabel(" "));

        light5=new QLabel(this);
        light5->setPixmap(fitpixmap2);
        //vbox3->addWidget(light5);
    }
    else if(vec.size()==1)
    {
        light1=new QLabel(this);
        light1->setPixmap(fitpixmap1);
        vbox3->addWidget(light1);
        //vbox3->addWidget(new QLabel(" "));

        light2=new QLabel(this);
        light2->setPixmap(fitpixmap2);
        vbox3->addWidget(light2);
        // vbox3->addWidget(new QLabel(" "));

        light3=new QLabel(this);
        light3->setPixmap(fitpixmap2);
        vbox3->addWidget(light3);
        //vbox3->addWidget(new QLabel(" "));

        light4=new QLabel(this);
        light4->setPixmap(fitpixmap2);
        vbox3->addWidget(light4);
        // vbox3->addWidget(new QLabel(" "));

        light5=new QLabel(this);
        light5->setPixmap(fitpixmap2);
        // vbox3->addWidget(light5);
    }
    else if(vec.size()==2)
    {
        light1=new QLabel(this);
        light1->setPixmap(fitpixmap1);
        vbox3->addWidget(light1);
        // vbox3->addWidget(new QLabel(" "));

        light2=new QLabel(this);
        light2->setPixmap(fitpixmap1);
        vbox3->addWidget(light2);
        // vbox3->addWidget(new QLabel(" "));

        light3=new QLabel(this);
        light3->setPixmap(fitpixmap2);
        vbox3->addWidget(light3);
        //  vbox3->addWidget(new QLabel(" "));

        light4=new QLabel(this);
        light4->setPixmap(fitpixmap2);
        vbox3->addWidget(light4);
        //  vbox3->addWidget(new QLabel(" "));

        light5=new QLabel(this);
        light5->setPixmap(fitpixmap2);
        //  vbox3->addWidget(light5);
    }
    else if(vec.size()==3)
    {
        light1=new QLabel(this);
        light1->setPixmap(fitpixmap1);
        vbox3->addWidget(light1);
        // vbox3->addWidget(new QLabel(" "));

        light2=new QLabel(this);
        light2->setPixmap(fitpixmap1);
        vbox3->addWidget(light2);
        //  vbox3->addWidget(new QLabel(" "));

        light3=new QLabel(this);
        light3->setPixmap(fitpixmap1);
        vbox3->addWidget(light3);
        //  vbox3->addWidget(new QLabel(" "));

        light4=new QLabel(this);
        light4->setPixmap(fitpixmap2);
        vbox3->addWidget(light4);
        // vbox3->addWidget(new QLabel(" "));

        light5=new QLabel(this);
        light5->setPixmap(fitpixmap2);
        vbox3->addWidget(light5);
    }
    else if(vec.size()==4)
    {
        light1=new QLabel(this);
        light1->setPixmap(fitpixmap1);
        vbox3->addWidget(light1);
        //   vbox3->addWidget(new QLabel(" "));

        light2=new QLabel(this);
        light2->setPixmap(fitpixmap1);
        vbox3->addWidget(light2);
        //   vbox3->addWidget(new QLabel(" "));

        light3=new QLabel(this);
        light3->setPixmap(fitpixmap1);
        vbox3->addWidget(light3);
        // vbox3->addWidget(new QLabel(" "));

        light4=new QLabel(this);
        light4->setPixmap(fitpixmap1);
        vbox3->addWidget(light4);
        // vbox3->addWidget(new QLabel(" "));

        light5=new QLabel(this);
        light5->setPixmap(fitpixmap2);
        vbox3->addWidget(light5);
    }
    else
    {
        light1=new QLabel(this);
        light1->setPixmap(fitpixmap1);
        vbox3->addWidget(light1);
        //    vbox3->addWidget(new QLabel(" "));

        light2=new QLabel(this);
        light2->setPixmap(fitpixmap1);
        vbox3->addWidget(light2);
        //    vbox3->addWidget(new QLabel(" "));

        light3=new QLabel(this);
        light3->setPixmap(fitpixmap1);
        vbox3->addWidget(light3);
        //    vbox3->addWidget(new QLabel(" "));

        light4=new QLabel(this);
        light4->setPixmap(fitpixmap1);
        vbox3->addWidget(light4);
        //   vbox3->addWidget(new QLabel(" "));

        light5=new QLabel(this);
        light5->setPixmap(fitpixmap1);
        vbox3->addWidget(light5);
    }


    group3->setLayout(vbox3);
    mainToolBar->addWidget(group3);
    //mainToolBar->addWidget(new QLabel("    "));

    //�����飬��ʾ��ź�ϵͳ��ǰʱ��
    serialNumber=new QLabel("    λ�ã�"+xtbh);//���
    serialNumber->setStyleSheet("color:White");
    vbox4->addWidget(serialNumber);
    //vbox4->addWidget(new QLabel("   "));
    systime=new QLabel(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss ddd"));//ʱ��
    systime->setStyleSheet("color:White");
    vbox4->addWidget(systime);
    //vbox4->addWidget(new QLabel("   "));

    group4->setLayout(vbox4);
    mainToolBar->addWidget(group4);
    //mainToolBar->addWidget(new QLabel("    "));

    //�����飬�澯
    //�رո澯
    openClose = new QToolButton(this);
    openClose->setToolTip(tr("�رո澯"));
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

    //��������
    objectAttribute = new QToolButton(this);
    objectAttribute->setToolTip(tr("��������"));
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

    //�ֶ�
    manual = new QToolButton(this);
    manual->setToolTip(tr("�ֶ�"));
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

    //�ر�Ŀ�����Ը���
    objects = new QToolButton(this);
    objects->setToolTip(tr("�ر�Ŀ�����Ը���"));
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

    //����
    attribute = new QToolButton(this);
    attribute->setToolTip(tr("����"));
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

    //�ر�����
    voice = new QToolButton(this);
    voice->setToolTip(tr("�ر�����"));
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

    //������
    exitButton = new QToolButton(this);
    exitButton->setToolTip(tr("�˳�"));
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

//��ȡϵͳ��ǰʱ�䶨ʱ��
void MainWindow::onTimerOut2(){
    systime->setText(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss ddd"));//ʱ��
}

void MainWindow::adjustment()
{
    Mat mat = in.getPano().clone();

    if(this->isPseudo==true)
        mat=setPseudocolor(mat);
    updateBright(mat);
    updateContrast(mat);

    cv::cvtColor(mat, mat, CV_BGR2RGB);

    Mat mat1, mat2;
    mat(Rect(0,0,mat.cols/2,mat.rows)).copyTo(mat1);
    mat(Rect(mat.cols/2,0,mat.cols/2,mat.rows)).copyTo(mat2);

    widget1->setMat(mat1);
    widget1->setPano(mat);
    widget1->draw();

    widget2->setPano(mat);
    widget2->setMat(mat2);
    widget2->draw();

    widget3->setPano(mat);
    widget3->setAllObjects(in.getObjs());
    widget3->draw();

    widget4->setPano(mat);
    widget4->setAllObjects(in.getObjs());
    widget4->draw();
}

//��ʱ������
void MainWindow::onTimerOut()
{
    //std::cout<<"ok1 "<<std::endl;
    this->selfTimerout();
    //this->jinTimerout();
}

//�Զ���ӿڶ�ʱ��
void MainWindow::selfTimerout(){
    //index=index+1;
    QString today=QString("./�ط�/")+QDate::currentDate().toString("yyyy-MM-dd");
    QDir *todayDir=new QDir();
    bool exist=todayDir->exists(today);
    if(!exist){
        todayDir->mkdir(today);
    }
    delete todayDir;

    in.getIntegratedData2();
    vector<MyObject> objs = in.getObjs2();

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

    //ͼƬ1
    //ͼƬ1
    //    QString s1=in.getQJ1();
    //    imageurl=s1.toStdString();
    //    Mat mat1 =imread(imageurl);

    //������ȫ���ϻ����Σ����֣��켣��
    Mat pano = in.getPano();

    Mat pano1 = pano.clone();
    Mat pano2 = pano.clone();
    Mat mat;
    hconcat(pano1,pano2,mat);

    //��ȫ���ϻ����Σ����֣��켣��
    //Mat mat = in.getPano().clone();
    //vector<MyObject> objs = in.getObjs();
    vector<MyObjectTrack> tracks = in.getTracks();

    int count = objs.size();
    for (int i = 0; i < count;i++)
    {
        //�������box
        MyObject obj = objs[i];
        Rect rect2 = Rect(obj.getRect().x+pano.cols, obj.getRect().y, obj.getRect().width, obj.getRect().height);
        rectangle(mat,obj.getRect(),obj.getColor(),2,1,0);
        rectangle(mat,rect2,obj.getColor(),2,1,0);
        cv::cvtColor(mat, mat, CV_BGR2RGB);

        //���켣
        for(int ii = 0; ii < tracks.size(); ii++){
            MyObjectTrack track = tracks[ii];
            int id = track.getId();
            vector<Point> points = track.getTrack();
            if(id == obj.getID()){
                for(int iii = 0; iii < points.size(); iii++){
                    Point point = points[iii];
                    Point point2 = Point(point.x+pano.cols, point.y);
                    circle(mat, point, 2, obj.getColor(),-1,8,2);//��ͼ���л��������㣬2��Բ�İ뾶
                    circle(mat, point2, 2, obj.getColor(),-1,8,2);//��ͼ���л��������㣬2��Բ�İ뾶
                    if(iii >= 1){
                        Point point3 = points[iii-1];
                        Point point4 = Point(point3.x+pano.cols, point3.y);
                        line(mat,point,point3,obj.getColor(),1,8,0);
                        line(mat,point2,point4,obj.getColor(),1,8,0);
                    }
                }
            }
        }
        cv::cvtColor(mat, mat, CV_BGR2RGB);
        //���������ĵ��λ��
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

            putText(mat,str,p,3,1,obj.getColor());
            putText(mat,str,p2,3,1,obj.getColor());
                    }
        cv::cvtColor(mat, mat, CV_BGR2RGB);
    }
    cv::cvtColor(mat, mat, CV_BGR2RGB);

    //Ȼ������2��

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

    //    //ȫ��2Mat
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
    //ͼƬ2
    //ͼƬ1
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
    widget2->setPano(mat);
    widget2->setMat(mat2);
    widget2->setObjects(objs);
    widget2->setTracks(in.getTracks());
    widget2->draw();
    //qDebug()<<s2;
    //drawUiLabel(mat2,2);
    //ͼƬ3
    //Mat mat3 =imread(imageurl);
    widget3->setPano(newpano);
    widget3->setAllObjects(in.getObjs());
    widget3->draw();
    //drawUiLabelByCopy(mat3,3);
    //ͼƬ4
    //Mat mat4 =imread(imageurl2);
    //drawUiLabelByCopy(mat4,4);
    widget4->setPano(newpano);
    widget4->setAllObjects(in.getObjs());
    widget4->draw();
    //ͼƬ5
    //QString imageurl5=in.getHD();
    //Mat mat5 =imread(imageurl5.toStdString());
    //widget5->setMat(mat5);
    widget5->setPano(newpano);
    widget5->setObjects(objs);
    widget5->draw();
    //drawUiLabel(mat5,5);
    //ͼƬ6
    //QString imageurl6= in.getLD();
    //Mat mat6 =imread(imageurl6.toStdString());
    //widget6->setMat(mat6);
    widget6->setPano(newpano);
    widget6->setObjects(objs);
    widget6->draw();
}

//�����ʦ�ӿڵĶ�ʱ������
void MainWindow::jinTimerout(){
    //vector<MyObject> objs = in.getObjs2();
    //std::cout<<"ok2 "<<std::endl;
    //#if 1
    if(in.getIntegratedData() == 0){
        //std::cout<<"getintegrated data "<<std::endl;
        //ͼƬ1
        //        QString s1=in.getQJ1();
        //        imageurl=s1.toStdString();
        //        //qDebug()<<in.getObjs().size();
        //��ȫ���ϻ����Σ����֣��켣��
        Mat mat = in.getPano();
        vector<MyObject> objs = in.getObjs();
        vector<MyObjectTrack> tracks = in.getTracks();

        int count = objs.size();
        for (int i = 0; i < count;i++)
        {
            //�������box
            MyObject obj = objs[i];
            rectangle(mat,obj.getRect(),obj.getColor(),2,1,0);
            cv::cvtColor(mat, mat, CV_BGR2RGB);
            //���켣
            for(int ii = 0; ii < tracks.size(); ii++){
                MyObjectTrack track = tracks[ii];
                int id = track.getId();
                vector<Point> points = track.getTrack();
                if(id == obj.getID()){
                    for(int iii = 0; iii < points.size(); iii++){
                        Point point = points[iii];
                        circle(mat, point, 2, obj.getColor(),-1,8,2);//��ͼ���л��������㣬2��Բ�İ뾶
                        if(iii >= 1){
                            Point point2 = points[iii-1];
                            line(mat,point,point2,obj.getColor(),1,8,0);
                        }
                    }
                }
            }
            cv::cvtColor(mat, mat, CV_BGR2RGB);
            //���������ĵ��λ��
            if(isMubiao){
                int x = (int)(this->getDirectionX(obj.getCenPoint().x, mat));
                int y = (int)(10-this->getDirectionY(obj.getCenPoint().y, mat)/2);//(10-10*(this->getDirectionY(obj.getCenPoint().y)-this->getDirectionY())/(this->getDirectionY2()-this->getDirectionY()));//endh - i*(endh-starth)/10
                QString tx = QString::number(x,10);
                QString ty = QString::number(y,10);
                QString tstr = "x="+tx+",y="+ty;
                string str = tstr.toStdString();
                //qDebug()<<tstr;
                Point p = Point(obj.getRect().x+obj.getRect().width,obj.getRect().y+obj.getRect().height);
                putText(mat,str,p,3,1,obj.getColor());
            }
            cv::cvtColor(mat, mat, CV_BGR2RGB);
        }
        cv::cvtColor(mat, mat, CV_BGR2RGB);

        //Ȼ������2��

        Mat mat1, mat2;
        mat(Rect(0,0,mat.cols/2,mat.rows)).copyTo(mat1);
        mat(Rect(mat.cols/2,0,mat.cols/2,mat.rows)).copyTo(mat2);

        widget1->setMat(mat1);
        widget1->setPano(mat);
        //        cv::imshow("pano", mat1);
        //        cv::waitKey(10);

        widget1->setObjects(in.getObjs());
        widget1->setTracks(in.getTracks());
        widget1->draw();
        //        //ͼƬ2
        //        //QString s2=in.getQJ2();
        //        //imageurl2=s2.toStdString();
        widget2->setMat(mat2);
        widget2->setPano(mat);
        widget2->setObjects(in.getObjs());
        widget2->setTracks(in.getTracks());
        widget2->draw();
        //ͼƬ3
        widget3->setPano(mat);
        widget3->setAllObjects(in.getObjs());
        widget3->draw();
        //ͼƬ4
        widget4->setPano(mat);
        widget4->setAllObjects(in.getObjs());
        widget4->draw();
        //ͼƬ5
        //QString imageurl5=in.getHD();
        //Mat mat5 =imread(imageurl5.toStdString());
        //widget5->setMat(mat5);
        widget5->setPano(in.getPano());
        widget5->setObjects(in.getObjs());
        //std::cout<<" parse object "<<std::endl;
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
    //    }
    //    else
    //    {
    //    std::cout<<"no ok"<<std::endl;
    //    }
    //    #endif
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

        //������ѡ�ľ��ο���ʹ��������ʾ���е���ʾ������
        //widget1->rectan3.width = widget1->rectan3.height * widget3->width() / widget3->height();

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

        //������ѡ�ľ��ο���ʹ��������ʾ���е���ʾ������
        //widget2->rectan3.width = widget2->rectan3.height * widget3->width() / widget3->height();

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

        //������ѡ�ľ��ο���ʹ��������ʾ���е���ʾ������
        //widget1->rectan4.width = widget1->rectan4.height * widget4->width() / widget4->height();

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

        //������ѡ�ľ��ο���ʹ��������ʾ���е���ʾ������
        //widget2->rectan4.width = widget2->rectan4.height * widget4->width() / widget4->height();

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

double MainWindow::getDirectionX(double x, Mat mat){
    //double x = this->rectan.x;
    return 360*x/mat.cols -90;
}

double MainWindow::getDirectionY(double y, Mat mat){

    double yy = 20;
    //double y = this->rectan.y;
    return yy*y/mat.rows;

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
void MainWindow::loadPictureToLabel1(boolean isRect, QRect qrect){
    //loadPictureToLabel(label,imgLabel1);
    QPixmap pixmap1 = QPixmap::fromImage(imgLabel1);
    if(isRect){
        QPainter painter(&pixmap1);
        painter.setPen(QPen(Qt::red,4,Qt::SolidLine)); //���û�����ʽ
        //painter.setBrush(QBrush(Qt::red,Qt::SolidPattern)); //���û�ˢ��ʽ
        painter.drawRect(qrect);
    }
    label->setScaledContents(true);
    label->setPixmap(pixmap1);
}

//����ͼƬ��Label2��
void MainWindow::loadPictureToLabel2(boolean isRect, QRect qrect){
    //loadPictureToLabel(label2,imgLabel2);
    QPixmap pixmap1 = QPixmap::fromImage(imgLabel2);

    if(isRect){
        QPainter painter(&pixmap1);
        painter.setPen(QPen(Qt::red,4,Qt::SolidLine)); //���û�����ʽ
        //painter.setBrush(QBrush(Qt::red,Qt::SolidPattern)); //���û�ˢ��ʽ
        painter.drawRect(qrect);
    }
    label2->setScaledContents(true);
    label2->setPixmap(pixmap1);
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
        startStop->setIcon(QPixmap("./icon/2_1��.png"));
        startStop->setToolTip("����");
        //startStopSet="./icon/1_1.png";
        isQidong = false;
    }
    else
    {
        startStop->setIcon(QPixmap("./icon/1_1.png"));
        startStop->setToolTip("ֹͣ");
        isQidong = true;
        //startStopSet="./icon/1_2.png";
    }

}
//��ͣ/����
void MainWindow::mstopFunction()
{
    //if(mstopSet=="./icon/2_2.png")
    if(isJixu)
    {
        mstop->setIcon(QPixmap("./icon/2_1��.png"));
        mstop->setToolTip("����");
        isJixu = false;
        //mstopSet="./icon/2_1.png";
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
    if(is_open==true){
        startTimeSet->setTime(QTime::currentTime());
        stopTimeSet->setTime(QTime::currentTime());
        widgetNew->show();
        return;
    }
    dateEdit=new QDateEdit(QDate::currentDate());
    startTime=new QLabel(QWidget::tr("��ʼʱ��"));
    //��ʼʱ��ѡ���
    startTimeSet=new QTimeEdit(QTime::currentTime(), this);
    //startTimeSet->setCalendarPopup(true);
    startTimeSet->setDisplayFormat("HH:mm:ss");
    //����ʱ��ѡ���
    stopTime=new QLabel(QWidget::tr("����ʱ��"));
    stopTimeSet=new QTimeEdit(QTime::currentTime(), this);
    //stopTimeSet->setCalendarPopup(true);
    stopTimeSet->setDisplayFormat("HH:mm:ss");
    queDing=new QPushButton("ȷ��",this);
    connect(queDing,SIGNAL(clicked()),this,SLOT(queDingFunction()));
    quXiao=new QPushButton("ȡ��",this);
    connect(quXiao,SIGNAL(clicked()),this,SLOT(quXiaoFunction()));
    //�������񲼾�
    //gridLayout=new QGridLayout(this);
    gridLayout=new QGridLayout();
    gridLayout->addWidget(new QLabel(QWidget::tr("����")));
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

    widgetNew->setWindowTitle("ʱ��ѡ���");
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
        QMessageBox::information(widgetNew,tr("����"),tr("���ڲ��ܴ��ڽ���"));
        //        widgetNew->close();
        //        widgetNew->show();
        return;
    }
    if(dif==0)
    {
        QMessageBox::information(widgetNew,tr("����"),tr("��ʼʱ��ͽ���ʱ����ͬ"));
        widgetNew->close();
        widgetNew->show();
    }
    else if(dif<0)
    {
        QMessageBox::information(widgetNew,tr("����"),tr("��ʼʱ����ڽ���ʱ��"));
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
//ͼ��
//�Զ�
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
//����
void MainWindow::brightnessFunction()
{
    trackBar->setWindowFlags(Qt::WindowStaysOnTopHint);
    trackBar->setWindowTitle("����");
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
//�Աȶ�
void MainWindow::saturationFunction()
{
    strackBar->setWindowFlags(Qt::WindowStaysOnTopHint);
    strackBar->setWindowTitle("�Աȶ�");
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
//α��ɫ
void MainWindow::pseudoColorFunction()
{
    isPseudo=!isPseudo;
    adjustment();
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
//Ŀ�������б�
void MainWindow::objectAttributeFunction()
{
    //dialogLabel->setText(tr("Information Message Box"));
    //const QString &objectstring = "oid =" ;
    // QMessageBox::information(this,"Ŀ�������б�",&objectstring);
    this->objectAttributes->setWindowFlags(Qt::WindowStaysOnTopHint);
    this->objectAttributes->activateWindow();
    this->objectAttributes->setWindowTitle("Ŀ�������б�");
    this->objectAttributes->setGeometry(250,60,900,650);
    // this->objectAttributes->tr("oid");
    // this->objectAttributes->resize(300,500);
    //this->objectAttributes->setText("oid=: ");
    //this->objectAttributes->setText("cenPoint");
    //QString s=QString("oid:")+myobjects.oid+"\nĿ����������:<"+myobjects.cenPoint.x+","+myobjects.cenPoint.y
    //            +">/n�����С:<"+myobjects.blocksize.width+","+myobjects.blocksize.height;
    //QString s1=QString(">\n�˶�����:")+myobjects.Velocity
    //            +"\n�˶�����"+myobjects.MotionDerection+"\nĿ�����:"+myobjects.area+"\nˮƽ�᳤��:"+myobjects.horizontalAxisLength
    //            +"\n��ֱ�᳤��:"+myobjects.verticalAxisLength+"\n����ǿ��:"+myobjects.absoluteIntensity+"\n���ǿ��"+myobjects.relativeIntensity
    //            +"\nĿ��߶�:"+myobjects.targetScale+"\n������Χ�Աȶȵ���Ӧǿ��:"+myobjects.CenSueEintensity+"\nĿ�걳�����ӱ�"+myobjects.SCRValue;
    //    qDebug()<<"22222222222";
    //    this->objectAttributes->setText(s);
    //    this->objectAttributes->show();
    this->objectAttributes->show();
}
//����
void MainWindow::objectsFunction()
{
    //if(objectSet=="./icon/13_2.png")
    if(isMubiao)
    {
        objects->setIcon(QPixmap("./icon/13_1.png"));
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
    QMessageBox::information(this,tr("�������ý��棬�д�ʵ�֡�"),tr("����Ŭ����"));
}
//����
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
        voice->setIcon(QPixmap("./icon/15_1��.png"));
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

//void MainWindow::adjustbrightness()
//{
//    //    QImage a = ImageDeal.AdjustBrightness(QImage Img, int iBrightValue);
//}

void MainWindow::test()
{
    QMessageBox::information(this,tr("�������ý��棬�д�ʵ�֡�"),tr("����Ŭ����"));
}

void MainWindow :: timeLineFunction(){}
