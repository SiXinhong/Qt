#include "mainwindow.h"
#include "ui_mainwindow.h"
//opencv��ͷ�ļ�
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


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);   
    QWidget* widget = new QWidget(this);

    widget1 = new QWidget(this);
    widget2 = new QWidget(this);
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

    index=0;//���ڼ����ߵ���ʼλ��
    index1=0;//����ȡ��һ����ͼƬ
    index2=0;//����ȡ�ڶ�����ͼƬ

    //ͼƬ1
    string imageurl="./s1/1.bmp";
    drawUiLabel(imageurl,1);
    //ͼƬ2
    string imageurl2 = "./s2/1.bmp";
    drawUiLabel(imageurl2,2);
    //ͼƬ3
    drawUiLabelByCopy(imageurl,3);
    //ͼƬ4
    drawUiLabelByCopy(imageurl2,4);
    //ͼƬ5
    string imageurl5="./0.png";;//�����ͼƬ��
    drawUiLabel(imageurl5,5);
    //ͼƬ6
    string imageurl6= "./0.png";//�����ͼƬ��
    drawUiLabel(imageurl6,6);

    //��ʱ��
    timer=new QTimer();
    timer->setInterval(3000);
    timer->start();
    connect(timer, SIGNAL(timeout()), SLOT(onTimerOut()));

    // ����������
      addMyToolBar();
    //����״̬��
     // addMyStatusBar();
      ui->statusBar->addWidget(new QLabel(QObject::tr("�ۼƼ��ʱ��:")));
      ui->statusBar->addWidget(new QLabel(QObject::tr("   ")));
      ui->statusBar->addWidget(new QLabel(QObject::tr("���γ���Ŀ����Ϣ:")));
      //�Ҽ�
      addAction(new QAction("Ŀ���б�",this));
      addAction(new QAction("������ʾ��",this));
      addAction(new QAction("��������ʾ��",this));
      addAction(new QAction("���",this));
      addAction(new QAction("�����ʾЧ��",this));
      setContextMenuPolicy(Qt::ActionsContextMenu);

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
}

MainWindow::~MainWindow()
{
    delete ui;
}
//���ƹ�����
void MainWindow::addMyToolBar()
{
    mainToolBar = addToolBar("monitoring");
    //���
    mainToolBar->addSeparator();
    listLabel1=new QLabel(tr(" ��� "));
    mainToolBar->addWidget(listLabel1);
    startStop = new QToolButton(this);
    startStop->setToolTip(tr("��/ͣ"));
    startStopSet="./icon/1_2.png";
    startStop->setIcon(QPixmap(startStopSet));
    startStop->setMinimumHeight(35);
    mainToolBar->addWidget(startStop);
    connect(startStop,SIGNAL(clicked()),this,SLOT(startStopFunction()));

    mstop = new QToolButton(this);
    mstop->setToolTip(tr("��ͣ"));
    mstopSet="./icon/2_2.png";
    mstop->setIcon(QPixmap(mstopSet));
    mstop->setMinimumHeight(35);
    mainToolBar->addWidget(mstop);
    mainToolBar->addSeparator();
    connect(mstop,SIGNAL(clicked()),this,SLOT(mstopFunction()));
    //�ط�
    listLabel2=new QLabel(tr(" �ط� "));
    mainToolBar->addWidget(listLabel2);
    open = new QToolButton(this);
    open->setToolTip(tr("��"));
    openSet="./icon/3_2.png";
    open->setIcon(QPixmap(openSet));
    open->setMinimumHeight(35);
    mainToolBar->addWidget(open);

    connect(open,SIGNAL(clicked()),this,SLOT(openFunction()));



    play = new QToolButton(this);
    play->setToolTip(tr("����"));
    playSet="./icon/4_2.png";
    play->setIcon(QPixmap(playSet));
    play->setMinimumHeight(35);
    mainToolBar->addWidget(play);
    connect(play,SIGNAL(clicked()),this,SLOT(playFunction()));

    rstop = new QToolButton(this);
    rstop->setToolTip(tr("��ͣ"));
    rstopSet="./icon/2_2.png";
    rstop->setIcon(QPixmap(rstopSet));
    rstop->setMinimumHeight(35);
    mainToolBar->addWidget(rstop);
    connect(rstop,SIGNAL(clicked()),this,SLOT(rstopFunction()));


    timeLine = new QToolButton(this);
    timeLine->setToolTip(tr("ʱ����"));
    timeLineSet="./icon/5_2.png";
    timeLine->setIcon(QPixmap(timeLineSet));
    timeLine->setMinimumHeight(35);
    mainToolBar->addWidget(timeLine);
    connect(timeLine,SIGNAL(clicked()),this,SLOT(timeLineFunction()));

    mainToolBar->addSeparator();
    //ͼ��
    listLabel3=new QLabel(tr(" ͼ�� "));
    mainToolBar->addWidget(listLabel3);
    autom = new QToolButton(this);
    autom->setToolTip(tr("�Զ�"));
    automSet="./icon/6_2.png";
    autom->setIcon(QPixmap(automSet));
    autom->setMinimumHeight(35);
    mainToolBar->addWidget(autom);
    connect(autom,SIGNAL(clicked()),this,SLOT(automFunction()));

    brightness = new QToolButton(this);
    brightness->setToolTip(tr("����"));
    brightnessSet="./icon/7_2.png";
    brightness->setIcon(QPixmap(brightnessSet));
    brightness->setMinimumHeight(35);
    mainToolBar->addWidget(brightness);
    connect(brightness,SIGNAL(clicked()),this,SLOT(brightnessFunction()));

    saturation = new QToolButton(this);
    saturation->setToolTip(tr("���Ͷ�"));
    saturationSet="./icon/8_2.png";
    saturation->setIcon(QPixmap(saturationSet));
    saturation->setMinimumHeight(35);
    mainToolBar->addWidget(saturation);
    connect(saturation,SIGNAL(clicked()),this,SLOT(saturationFunction()));

    pseudoColor = new QToolButton(this);
    pseudoColor->setToolTip(tr("α��ɫ"));
    pseudoColorSet="./icon/9_2.png";
    pseudoColor->setIcon(QPixmap(pseudoColorSet));
    pseudoColor->setMinimumHeight(35);
    mainToolBar->addWidget(pseudoColor);
    connect(pseudoColor,SIGNAL(clicked()),this,SLOT(pseudoColorFunction()));

    serialNumber = new QToolButton(this);
    serialNumber->setToolTip(tr("���"));
    serialNumberSet="./icon/17_2.png";
    serialNumber->setIcon(QPixmap(serialNumberSet));
    serialNumber->setMinimumHeight(35);
    mainToolBar->addWidget(serialNumber);
    connect(serialNumber,SIGNAL(clicked()),this,SLOT(serialNumberFunction()));

    time = new QToolButton(this);
    time->setToolTip(tr("ʱ��"));
    timeSet="./icon/10_2.png";
    time->setIcon(QPixmap(timeSet));
    time->setMinimumHeight(35);
    mainToolBar->addWidget(time);
    mainToolBar->addSeparator();
    connect(time,SIGNAL(clicked()),this,SLOT(timeFunction()));

    //�澯
    listLabel4=new QLabel(tr(" �澯 "));
    mainToolBar->addWidget(listLabel4);
    openClose = new QToolButton(this);
    openClose->setToolTip(tr("��/��"));
    openCloseSet="./icon/11_2.png";
    openClose->setIcon(QPixmap(openCloseSet));
    openClose->setMinimumHeight(35);
    mainToolBar->addWidget(openClose);
    connect(openClose,SIGNAL(clicked()),this,SLOT(openCloseFunction()));

    manual = new QToolButton(this);
    manual->setToolTip(tr("�ֶ�"));
    manualSet="./icon/12_2.png";
    manual->setIcon(QPixmap(manualSet));
    manual->setMinimumHeight(35);
    mainToolBar->addWidget(manual);
    connect(manual,SIGNAL(clicked()),this,SLOT(manualFunction()));

    attribute = new QToolButton(this);
    attribute->setToolTip(tr("����"));
    attributeSet="./icon/13_2.png";
    attribute->setIcon(QPixmap(attributeSet));
    attribute->setMinimumHeight(35);
    mainToolBar->addWidget(attribute);
    connect(attribute,SIGNAL(clicked()),this,SLOT(attributeFunction()));

    setUp = new QToolButton(this);
    setUp->setToolTip(tr("����"));
    setUpSet="./icon/14_2.png";
    setUp->setIcon(QPixmap(setUpSet));
    setUp->setMinimumHeight(35);
    mainToolBar->addWidget(setUp);
    connect(setUp,SIGNAL(clicked()),this,SLOT(setUpFunction()));

    voice = new QToolButton(this);
    voice->setToolTip(tr("����"));
    voiceSet="./icon/15_2.png";
    voice->setIcon(QPixmap(voiceSet));
    voice->setMinimumHeight(35);
    mainToolBar->addWidget(voice);
    connect(voice,SIGNAL(clicked()),this,SLOT(voiceFunction()));

    light = new QToolButton(this);
    light->setToolTip(tr("ָʾ��"));
    lightSet="./icon/16_2.png";
    light->setIcon(QPixmap(lightSet));
    light->setMinimumHeight(35);
    mainToolBar->addWidget(light);
    connect(light,SIGNAL(clicked()),this,SLOT(lightFunction()));
    mainToolBar->addSeparator();
}
//---xiaotian ���ƽ����ϵ�ͼƬ3  ͼƬ4
void MainWindow::drawUiLabelByCopy(string imgurl, int index1){
    Mat image =imread(imgurl);
    Size dsize ;
    double scale = 1;
    dsize = Size(image.cols*scale,image.rows*scale);
    Mat image11 = Mat(dsize,CV_32S);
    cv::resize(image, image11,dsize);
    QImage img = QImage((const unsigned char*)(image11.data),image11.cols,image.rows, image11.cols*image11.channels(),  QImage::Format_RGB888);
    vector<Rectan> rectans;
    QImage aa;
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
        QImage imgLabe3 = drawScaleAndRecOnPic(image33,rectans1,index,-1);
        cv::cvtColor(image11, image11, CV_BGR2RGB);
        loadPictureToLabel(label3,imgLabe3);
    }
    if(index1 == 4){
        aa=(&img)->copy(2604,13,92,92);
        Mat image4 = QImageToMat(aa);
        Mat image44 = Mat(dsize,CV_32S);
        cv::resize(image4, image44,dsize);
        Rectan rec4(1650,250,400,100);
        rectans.clear();
        rectans.push_back(rec4);
        QImage imgLabel4 = drawRecOnPic(image44,rectans);
        cv::cvtColor(image11, image11, CV_BGR2RGB);
        loadPictureToLabel(label4,imgLabel4);
    }
}


//---xiaotian ���ƽ����ϵ�ͼƬ1 ͼƬ2 ͼƬ5 ͼƬ6
void MainWindow::drawUiLabel(string imgurl, int index){
     Mat image =imread(imgurl);
     vector<Rectan> rectans;
     if(index == 1){
         //ͼƬ1
         Rectan rec(1490,250,100,100);
         Rectan rec2(1800,250,50,50);
         rectans.push_back(rec);
         rectans.push_back(rec2);
         QImage imgLabel = drawRecOnPic(image,rectans);
         cv::cvtColor(image, image, CV_BGR2RGB);
         loadPictureToLabel(label,imgLabel);
     }

     if(index == 2){
        //ͼƬ2
         Rectan rec3(2600,10,100,100);
         rectans.clear();
         rectans.push_back(rec3);
         QImage imgLabel = drawRecOnPic(image,rectans);
         cv::cvtColor(image, image, CV_BGR2RGB);
         loadPictureToLabel(label2,imgLabel);
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
         QImage imgLabel5 = drawCircleOnPic(image,points,120,100);
         cv::cvtColor(image, image, CV_BGR2RGB);
         loadPictureToLabel(label5,imgLabel5);
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
         QImage imgLabel6 = drawCircleOnPic(image,points1,120,100);
         cv::cvtColor(image, image, CV_BGR2RGB);
         loadPictureToLabel(label6,imgLabel6);
     }
}



//---xiaotian   ����ͼƬ��label�ϡ�
void MainWindow::loadPictureToLabel(QLabel *label, QImage image){
    QPixmap pixmap = QPixmap::fromImage(image);
    label->setPixmap(pixmap);
    label->setScaledContents(true);
}

//---xiaotian   ͼ���ϻ��ƾ��ο�
QImage MainWindow::drawRecOnPic(Mat image, vector<Rectan> rectans){
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
    QImage imglabel;
    imglabel = MatToQImage(image);
    return imglabel;
}



//---xiaotian  ͼ���ϻ��Ʊ�ߺ;��ο�
QImage MainWindow::drawScaleAndRecOnPic(Mat image, vector<Rectan> rectans, double startw, double starth){
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
    QImage imglabel3;
    imglabel3 = MatToQImage(image);
    return imglabel3;
}

//---xiaotian  ͼ���ϻ��ƶ���κ�Բ
QImage MainWindow::drawCircleOnPic(Mat image, vector<Point> point, double x, double y){
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
    QImage imglabel;
    imglabel = MatToQImage(image);
    return imglabel;
}


//����
QImage MainWindow:: paintRectangle(Mat image,double x,double y,double width,double height)
{
    Rect rect;
    QImage img;
    rect.x = x;
    rect.y = y;
    rect.width = width;
    rect.height = height;
    rectangle(image,rect,Scalar(0,0,255),4,1,0);
    cv::cvtColor(image, image, CV_BGR2RGB);
    img = QImage((const unsigned char*)(image.data),image.cols,image.rows, image.cols*image.channels(),  QImage::Format_RGB888);
    return img;
}
//Բ
QImage MainWindow::paintCircle(Mat image,double x,double y)
{
    QImage img;
    Point pointInterest;//�����㣬���Ի���ͼ����,��Բ�ε��Բ��
    pointInterest.x=x;//��������ͼ���к�����
    pointInterest.y=y;//��������ͼ����������
    circle(image, pointInterest, 2, Scalar(255, 0,0 ),-1,8,2);//��ͼ���л��������㣬2��Բ�İ뾶
    img = QImage((const unsigned char*)(image.data),image.cols,image.rows, image.cols*image.channels(),  QImage::Format_RGB888);
    return img;
}

//�����
QImage MainWindow::paintScale(Mat image,double startw,double starth)
{
    QImage img;
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
    return img;
}

//��ʱ������
void MainWindow::onTimerOut()
{
    index=index+1;
    string imageurl="./s1/1.bmp";
    String imageurl2="./s2/1.bmp";
    //�洢��һ��
    QString filename1("./s1/1.bmp");
    QString filename2("./s1/2.bmp");
    QString filename3("./s1/3.bmp");
    QString filename4("./s1/4.bmp");
    //�洢�ڶ���
    QString filename5("./s2/1.bmp");
    QString filename6("./s2/2.bmp");
    QString filename7("./s2/3.bmp");
    QString filename8("./s2/4.bmp");
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
    //���µ�һ����ͼƬ
    index1=index1+1;
    QImage *image=new QImage(vc1[(index1)%4]);
    QString s1=vc1[(index1)%4];
    imageurl=s1.toStdString();
    qDebug()<<s1;
    drawUiLabel(imageurl,1);
    //���µڶ�����ͼƬ
    index2=index2+1;
    QImage *image2=new QImage(vc2[(index2)%4]);
    QString s2=vc2[(index2)%4];
    imageurl2=s2.toStdString();
    qDebug()<<s2;
    drawUiLabel(imageurl2,2);
    //���µ�����
    Mat img=QImageToMat(*image);
    paintRectangle(img,1490,250,100,100);
    drawUiLabelByCopy(imageurl,3);
    //���µ�����
    Mat img2=QImageToMat(*image2);
    paintRectangle(img2,1650,250,400,100);
    drawUiLabelByCopy(imageurl2,4);
    qDebug()<<"tongguo 3!!!!!";
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
        QImage image(mat.cols, mat.rows, QImage::Format_Indexed8);
        // Set the color table (used to translate colour indexes to qRgb values)
        image.setColorCount(256);
        for(int i = 0; i < 256; i++)
        {
            image.setColor(i, qRgb(i, i, i));
        }
        // Copy input Mat
        uchar *pSrc = mat.data;
        for(int row = 0; row < mat.rows; row ++)
        {
            uchar *pDest = image.scanLine(row);
            memcpy(pDest, pSrc, mat.cols);
            pSrc += mat.step;
        }
        return image;
    }
    // 8-bits unsigned, NO. OF CHANNELS = 3
    else if(mat.type() == CV_8UC3)
    {
        // Copy input Mat
        const uchar *pSrc = (const uchar*)mat.data;
        // Create QImage with same dimensions as input Mat
        QImage image(pSrc, mat.cols, mat.rows, mat.step, QImage::Format_RGB888);
        return image.rgbSwapped();
    }
    else if(mat.type() == CV_8UC4)
    {
        qDebug() << "CV_8UC4";
        // Copy input Mat
        const uchar *pSrc = (const uchar*)mat.data;
        // Create QImage with same dimensions as input Mat
        QImage image(pSrc, mat.cols, mat.rows, mat.step, QImage::Format_ARGB32);
        return image.copy();
    }
    else
    {
        qDebug() << "ERROR: Mat could not be converted to QImage.";
        return QImage();
    }
}
//���
void MainWindow::startStopFunction()
{
    if(startStopSet=="./icon/1_2.png")
    {
        startStop->setIcon(QPixmap("./icon/1_1.png"));
        startStopSet="./icon/1_1.png";
    }
    else
    {
        startStop->setIcon(QPixmap("./icon/1_2.png"));
        startStopSet="./icon/1_2.png";
    }
}
void MainWindow::mstopFunction()
{
    if(mstopSet=="./icon/2_2.png")
    {
        mstop->setIcon(QPixmap("./icon/2_1.png"));
        mstopSet="./icon/2_1.png";
    }
    else
    {
        mstop->setIcon(QPixmap("./icon/2_2.png"));
        mstopSet="./icon/2_2.png";
    }
}
//�طŹ���
//��
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
}
//����
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
//��ͣ
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
//ʱ����
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
//ͼ��
//�Զ�
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
//����
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
}
//���Ͷ�
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



//α��ɫ
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
//���
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
//ʱ��
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
//�򿪹ر�
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
//�ֶ�
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
//����
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
//����
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
//����
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
