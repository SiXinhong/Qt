#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QImage>
#include <QPixmap>
#include <QLabel>
#include "region.h"
#include "regiongroup.h"
#include "mylabel.h"
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
#include <QGridLayout>
#include <cv.h>
#include <phonon>
#include <QToolButton>
#include <QApplication>
#include <QSound>
#include<QGroupBox>
#include <QButtonGroup>

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
#include <QMenu>
#include <QMenuBar>
#include <QAction>
#include "objectAttributes.h"
class MainWindow;
#include "welcomewindow.h"
#include <QQueue>
#include<QMap>
#include "monitor.h"

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
  virtual void onTimerOut2();
    
public:
  Monitor *monitor;
    bool location;
   QQueue<QTime> video;
   QQueue<QTime> videoEnd;//recent
   QQueue<QDate> videoDate;//recent
   void flushRecentVideo();//recent
   QAction* videoAction[6];//recent
 // QMap<QTime,QTime> video;
  QDir *directory;
  WelcomeWindow *welcome;
  int num_objs;
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
   int newObjCount;
   int addOneLight;
   QPixmap fitpixmap1;
   QPixmap fitpixmap2;
   QPixmap fitpixmap3;
   QPixmap fitpixmap4;
   QPixmap fitpixmap5;
   QPixmap fitpixmap6;
   QPixmap fitpixmap7;
   QPixmap fitpixmap8;
//   Mat mat;
//   Mat mat1, mat2;
   //HSL *hsl;
   int color ;
  // int saturation1;
   void updateBright(Mat &mat1);
   void updateContrast(Mat &mat1);
    //QApplication a;
    explicit MainWindow(WelcomeWindow *welcome = 0,QWidget *parent = 0);
    ~MainWindow();
    void paintEvent(QPaintEvent *);
    void resizeEvent(QResizeEvent *);
    void update();

    void test();

    void paintRectangle(Mat image,double x,double y,double width,double height);//������
    void paintCircle(Mat image,double x,double y);//��Բ
    void paintScale(Mat image,double startw,double starth);//�����

   cv:: Mat QImageToMat(QImage image);
    static QImage MatToQImage(const cv::Mat& mat, QImage imgLabel);

    //---xiaotian   ����ͼƬ��Label�ϡ�
    void loadPictureToLabel(QLabel *label,QImage image);
    //����ͼƬ��Label1��
    void loadPictureToLabel1(boolean isRect, QRect qrect, Scalar co, QRect rectRegion, vector<Point> ps);
    //����ͼƬ��Label2��
    void loadPictureToLabel2(boolean isRect, QRect qrect, Scalar co, QRect rectRegion, vector<Point> ps);
    //����ͼƬ��Label3��
    void loadPictureToLabel3(Scalar co, QRect rectRegion, vector<Point> ps);
    //����ͼƬ��Label4��
    void loadPictureToLabel4(Scalar co, QRect rectRegion, vector<Point> ps);
    //����ͼƬ��Label5��
    void loadPictureToLabel5();
    //����ͼƬ��Label6��
    void loadPictureToLabel6(Scalar co, QRect rectRegion, vector<Point> ps);
    // ����ͼƬ��Label7��
    void loadPictureToLabel7();
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
    // void init();
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
    //�жϴ����Ƿ��
    bool is_open;
    //�ж��Ƿ��ڶ����������״̬
    boolean isDefiningRegion;
    //�ж��Ƿ��Ƕ�����μ�������״̬
    boolean isDefiningRectRegion;
    //��ʱ�洢���ζ���ļ������
    vector<Region> rs;
    //����ļ�����������ļ��������
    RegionGroup rg;

    vector<RegionGroup> rgs;

     QLabel *label;
     QLabel *label2;
     QLabel *label3;
     QLabel *label4;
     QLabel *label5;
     QLabel *label6;
     QLabel *label7;

     //���ص�6��QLabel�ϵ�6��QImage
     QImage imgLabel1;
     QImage imgLabel2;
     QImage imgLabel3;
     QImage imgLabel4;
     QImage imgLabel5;
     QImage imgLabel6;
     QImage imgLabel7;


     Qj1Widget* widget1;
     Qj2Widget* widget2;
     ZWidget* widget3;
     NWidget1* widget4;
     HWidget* widget5;
     //LWidget* widget6;
     NWidget2* widget6;

     QTimer *timer;
     QTimer *timerSysTime;
     QTimer *timerFlash;
     QTimer *timerInit;
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
     double getDirectionX(double x, Mat mat);

     double getDirectionY(double y, Mat mat);

     void addMyMenuBar();
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
     //����澯
     void alertProcessing(vector<MyObject> objs);

     QToolBar *mainToolBar;
     //��һ�鰴ť����غͺ��ˣ����лط�
     //QLabel *listLabel1;
     //QString startStopSet;
     QLabel *backLabel;
     QString mstopSet;
     QString backSet;
     //QString openSet;
     //QToolButton *startStop;//��/��ͣ
     QToolButton *mstop;//��ͣ
     QToolButton *back;
     //�ط�
     QString openSet;
     QToolButton *open;//��
     //�ڶ��鰴ť��ͼ��
     //QLabel *listLabel3;
     QLabel *photo;
     QString chexiaoDuibidu;
     QString automSet;
     QString addBrightnessSet;
     QString reduceBrightnessSet;
     QString addSaturationSet;
     QString reduceSaturationSet;
     QString pseudoColorSet;
   //  QString serialNumberSet;
//     QString timeSet;
     QToolButton *chexiao;
     QToolButton *autom;//�Զ�
     QToolButton *addbrightness;//����
     QToolButton *reducebrightness;
     QToolButton *addsaturation;//���Ͷ�
     QToolButton *reducesaturation;
     QToolButton *pseudoColor;//α��ɫ

     //�����鰴ť��ָʾ�ƣ���յ��һ��Ŀ��һյ��ƣ�����Ŀ���յ��ƣ�����Ŀ����յ��ƣ��ĸ�Ŀ����յ��ƣ����Ŀ�꼰���ϣ���յ���
//     QString light1Set;
//     QString light2Set;
//     QString light3Set;
//     QString light4Set;
//     QString light5Set;


    QLabel *lights[5];
    QLabel *light1;
////     //QToolButton *light1;
     QLabel *light2;
     QLabel *light3;
     QLabel *light4;
     QLabel *light5;

     //�����飬��ʾ��ź�ϵͳ��ǰʱ��
      QLabel *currentTime;
    QLabel *serialNumber;//���
     QLabel *systime;//ʱ��
     //�澯
     //QLabel *listLabel4;
     QLabel *setup;
     QLabel *alarm;
     QLabel *position;
     QLabel *zhanweiLabel;

     QString objectAttributeSet;//��ʾ�����λ��
     QString manualSet;//���ӱ�ǩ

     QToolButton *objectAttribute;//��ʾ�����λ��
     QToolButton *manual;//���ӱ�ǩ
     QToolButton *stability;

     QString stabilityset;
     QString openCloseSet;//�����رո澯
     QString objectSet;//����̽�������ȵȼ�
     QString voiceSet;
     QString lightSet;
     QString exitSet;
     QString zhanwei;

     QToolButton *openClose;//��/��
     QToolButton *objects;//Ŀ�����������Ƿ����Ŀ��
     QToolButton *voice;//����
     QToolButton *light;//����
     //QToolButton *setUp;//����
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
     QDateTimeEdit *startTimeSet;
     QDateTimeEdit *stopTimeSet;
     QDateEdit *dateEdit;
     QGridLayout *gridLayout;

     QMenu* FileMenu;
     QMenu* OptionMenu;
     QMenu* ToolMenu;
     QMenu* DisplayMenu;
     QMenu* HelpMenu;
     QMenu* videoMenu;

     QMenuBar* menubar;

     QAction* connection;
     QAction* connectionplus;
     QAction* disconnection;
     QAction* openplus;
     QAction* backplus;
     QAction* closeaction;
     QMenu* recentvidio;//recent
     QAction* changeuser;
     QAction* installation;
     QAction* exit;

     QAction* configuration;
     QAction* saveconfiguration;
     QAction* region;

     QAction* figure;

     QAction* openalert;
     QAction* closealert;

     QAction* help;
     QAction* about;

protected slots:
     void videoClick();//recent
     void startStopFunction();
     void mstopFunction();
     void backFunction();
     void openFunction();

     void chexiaoFunction();
     void automFunction();
     void addBrightnessFunction();
     void reduceBrightnessFunction();
     void addSaturationFunction();
     void reduceSaturationFunction();
     void pseudoColorFunction();

     void openCloseFunction();
     void objectAttributeFunction();
     void manualFunction();
     void objectsFunction();
     void lightFunction();
     void voiceFunction();
     void stabilityFunction();

     virtual void exitFunction();

     void closeEvent(QCloseEvent *event);

     //�˵����ۺ���
     void connectionClicked();
     void connectionplusClicked();
     void disconnectionClicked();
     void openplusClicked();
     void backplusClicked();
     void closeClicked();
     void recentvidioClicked();
     void changeuserClicked();
     void installationClicked();
     void exitClicked();

     void configurationClicked();
     void saveconfigurationClicked();
     void regionClicked();
     void figureClicked();

     void openalertClicked();
     void closealertClicked();

     void helpClicked();
     void aboutClicked();

     //void lightFunction();
    // void adjustbrightness();
     //�ط����躯��
     void queDingFunction();
     void quXiaoFunction();
     virtual void timeLineFunction();
     void flash();

public slots:
    void init();

//private:
public:
    Ui::MainWindow *ui;
class TrackBar* trackBar;
class STrackBar* strackBar;
Mat setPseudocolor(Mat& image);

private slots:

};
#include"backwindow.h"
#endif // MAINWINDOW_H
