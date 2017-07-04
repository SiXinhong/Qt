#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QImage>
#include <QPixmap>
#include <QLabel>
#include "mylabel.h"
#include "qj1widget.h"
#include "qj2widget.h"
#include "zwidget.h"
#include "nwidget.h"
#include "hwidget.h"
#include "lwidget.h"
#include "myinterface.h"
#include "myobject.h"
#include "mixer.h"
#include <QGridLayout>
#include <cv.h>
#include <phonon>
#include <QToolButton>
#include <QApplication>
#include <QSound>

//OpenCVͷ�ļ�
#include <vector>
#include <highgui.h>
#include <cv.h>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

#include <QtGui/QPainter>
#include "rectan.h"
//#define arraySize 10;
//SLOGͷ�ļ�

#include <QFileDialog>
//�Ի�������Ҫ��ͷ�ļ�
#include <QLineEdit>
#include <QMessageBox>

//ͼ������Ҫ��ͷ�ļ�
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <QSlider>
#include<QLineEdit>
#include<QWidgetAction>
#include "trackbar.h"
#include "s_trackbar.h"

//#include"ltrackbar.h"
//�ط�����Ҫ��ͷ�ļ�

#include<QDateEdit>
#include<QDateTimeEdit>
#include<QTimeEdit>
#include<QPushButton>
#include <QDesktopWidget>
#include "objectAttributes.h"

using namespace cv;
using namespace std;


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
public slots:
  void onTimerOut();
  void onTimerOut2();
    
public:
  CMixer * cmixer;
  MyObject myobjects;
  ObjectAttributes *objectAttributes;
  //QLabel *objectAttributes;
  QSound *sound;
   void adjustment();
   int bright_TrackbarValue;
   int alpha_contrast;
   bool isPseudo;
   bool isVoice;
   //HSL *hsl;
   int color ;
  // int saturation1;
   void updateBright(Mat &mat1);
   void updateContrast(Mat &mat1);
    //QApplication a;
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void paintEvent(QPaintEvent *);
    void resizeEvent(QResizeEvent *);
    void update();

    void test();

    void paintRectangle(Mat image,double x,double y,double width,double height);//������
    void paintCircle(Mat image,double x,double y);//��Բ
    void paintScale(Mat image,double startw,double starth);//�����

    cv::Mat QImageToMat(QImage image);
    static QImage MatToQImage(const cv::Mat& mat, QImage imgLabel);

    //---xiaotian   ����ͼƬ��Label�ϡ�
    void loadPictureToLabel(QLabel *label,QImage image);
    //����ͼƬ��Label1��
    void loadPictureToLabel1(boolean isRect, QRect qrect);
    //����ͼƬ��Label2��
    void loadPictureToLabel2(boolean isRect, QRect qrect);
    //����ͼƬ��Label3��
    void loadPictureToLabel3();
    //����ͼƬ��Label4��
    void loadPictureToLabel4();
    //����ͼƬ��Label5��
    void loadPictureToLabel5();
    //����ͼƬ��Label6��
    void loadPictureToLabel6();
    //---xiaotian  ��ͼ���ϻ��ƾ��ο�  ʹ�����飬��಻����10��
    void drawRecOnPic(Mat image,vector<Rectan> rectan);
    //�������ѡȡ�ľ���
    void drawRecOnPic2(Mat image, Rect rect);
    //---xiaotian   ��ͼ���ǻ��Ʊ�ߺ;��ο�
    void drawScaleAndRecOnPic(Mat image11,vector<Rectan> rectan,double startw,double starth);
    //---xiaotian  ��ͼ���ϻ�Բ�Ͷ����
    void drawCircleOnPic(Mat image11,vector<Point> point,double x,double y);

    //---xiaotian  �ڽ����ϻ�label  ͼƬ1 ͼƬ2  ͼƬ5 ͼƬ6
    void drawUiLabel(Mat image,int index);
    //---xiaotian  �ڽ����ϻ�label  ͼƬ3 ͼƬ4.��������ͼƬ��Ҫ��ȡ����������һ�෽����
    void drawUiLabelByCopy(Mat iamge,int index1);
    //���������ק�¼�������JMainFrame������¼�������
    void mousePressEvent(QMouseEvent *e);
    void mouseMoveEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);

    //������������еı���
    //��������ֹͣ
    boolean isQidong;
    //��ͣ���Ǽ���
    boolean isJixu;
    //�澯�������ǹر�
    boolean isGaojing;
    //�����򿪻��ǹر�
    boolean isShengyin;
    //Ŀ�������Ƿ����
    boolean isMubiao;
    //ϵͳ���
    QString xtbh;

     QLabel *label;
     QLabel *label2;
     QLabel *label3;
     QLabel *label4;
     QLabel *label5;
     QLabel *label6;

     //���ص�6��QLabel�ϵ�6��QImage
     QImage imgLabel1;
     QImage imgLabel2;
     QImage imgLabel3;
     QImage imgLabel4;
     QImage imgLabel5;
     QImage imgLabel6;


     Qj1Widget* widget1;
     Qj2Widget* widget2;
     ZWidget* widget3;
     NWidget* widget4;
     HWidget* widget5;
     LWidget* widget6;

     QTimer *timer;
     QTimer *timerSysTime;

     //���������ק�¼��ı���
     boolean isDrag1;
     boolean isDrag2;
     boolean isMove;

     QGridLayout *gridlayout;

     //----------------����Ϊ��ʱ�Ա���-----------------
     MyInterface in;
     Mat image11;
     //��ͼ��Ҫ�ı���
     vector<Rectan> rectans1;
     int index;//���ڱ�߶�
     //�洢�ļ���ͼƬ��Ҫ�ı���
     int index1;//��ȡ�ڼ���ͼƬ
     vector<QString> vc1;//�洢��һ����ͼƬ
     int index2;//��ȡ�ڶ����ڼ���ͼƬ
     vector<QString> vc2;//�洢�ڶ�����ͼƬ

     string imageurl;
     string imageurl2;


     QString filename1;
     QString filename2;
     QString filename3;
     QString filename4;
     QString filename5;
     QString filename6;
     QString filename7;
     QString filename8;

     QPixmap pixmap;
     QImage aa;
     QImage img;

     QImage image;
     QImage image2;
     //-----------------------------------------------


protected:
     //��������Ҫ�ı���
     void addMyToolBar();
     //��ʱ�Դ���
     void tempProcessing();
     //�Զ���ӿڴ���
     void selfProcessing();
     //�����ʦ�Ľӿڴ���
     void jinProcessing();

     //�Զ���ӿڶ�ʱ��
     virtual void selfTimerout();

     //�����ʦ�ӿڵĶ�ʱ������
     void jinTimerout();

     QToolBar *mainToolBar;
     //��һ�鰴ť����غͺ��ˣ����лط�
     //QLabel *listLabel1;
     QString startStopSet;
     QString mstopSet;
     QString backSet;
     //QString openSet;
     QToolButton *startStop;//��/��ͣ
     QToolButton *mstop;//��ͣ
     QToolButton *back;
     //�ط�
     QString openSet;
     QToolButton *open;//��
     //�ڶ��鰴ť��ͼ��
     //QLabel *listLabel3;
     QString automSet;
     QString brightnessSet;
     QString saturationSet;
     QString pseudoColorSet;
     QString serialNumberSet;
     QString timeSet;
     QToolButton *autom;//�Զ�
     QToolButton *brightness;//����
     QToolButton *saturation;//���Ͷ�
     QToolButton *pseudoColor;//α��ɫ

     //�����鰴ť��ָʾ�ƣ���յ��һ��Ŀ��һյ��ƣ�����Ŀ���յ��ƣ�����Ŀ����յ��ƣ��ĸ�Ŀ����յ��ƣ����Ŀ�꼰���ϣ���յ���
     QString light1Set;
     QString light2Set;
     QString light3Set;
     QString light4Set;
     QString light5Set;
     QToolButton *light1;
     QToolButton *light2;
     QToolButton *light3;
     QToolButton *light4;
     QToolButton *light5;

     //�����飬��ʾ��ź�ϵͳ��ǰʱ��
     QLabel *serialNumber;//���
     QLabel *systime;//ʱ��
     //�澯
     //QLabel *listLabel4;
     QString openCloseSet;
     QString objectAttributeSet;
     QString manualSet;
     QString objectSet;
     QString attributeSet;
     QString voiceSet;
     QString exitSet;

     QToolButton *openClose;//��/��
     QToolButton *objectAttribute;//��������
     QToolButton *manual;//�ֶ�
     QToolButton *objects;//Ŀ�����������Ƿ����Ŀ��
     QToolButton *attribute;//����
     //QToolButton *setUp;//����
     QToolButton *voice;//����
     QToolButton *exitButton;//�˳���ť
     //QToolButton *light;//ָʾ��
     //�Ի�����Ҫ�ı���
     //QLineEdit *fileLineEdit;
     //QLabel *dialogLabel;

     //�طŰ�ť����Ҫ�Ĳ���
     class BackWindow *backwindow;
     QWidget *widgetNew;
//     QPushButton *inputBtn;
     QPushButton *queDing;
     QPushButton *quXiao;
     QLabel *startTime;
     QLabel *stopTime;
     QTimeEdit *startTimeSet;
     QTimeEdit *stopTimeSet;
     QGridLayout *gridLayout;

protected slots:
     void startStopFunction();
     void mstopFunction();

     void backFunction();
     void openFunction();
     void automFunction();
     void brightnessFunction();

     void saturationFunction();
     void pseudoColorFunction();
     void openCloseFunction();
     void objectAttributeFunction();
     void manualFunction();
     void objectsFunction();

     void attributeFunction();
     void voiceFunction();
     void exitFunction();
     void closeEvent(QCloseEvent *event);

     //void lightFunction();
     void adjustbrightness();
     //�ط����躯��
     void queDingFunction();
     void quXiaoFunction();



//private:
public:
    Ui::MainWindow *ui;
class TrackBar* trackBar;
class STrackBar* strackBar;
Mat setPseudocolor(Mat& image);

};
#include"backwindow.h"
#endif // MAINWINDOW_H
