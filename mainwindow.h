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
//#include <phonon>
#include <QToolButton>
#include <QApplication>
//#include <QSound>
#include<QGroupBox>
#include <QButtonGroup>

//OpenCV头文件
#include <vector>
#include <highgui.h>
#include <cv.h>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

#include <QtGui/QPainter>
#include "rectan.h"
//#define arraySize 10;
//SLOG头文件

#include <QFileDialog>
//对话框所需要的头文件
#include <QLineEdit>
#include <QMessageBox>

//图像所需要的头文件
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <QSlider>
#include<QLineEdit>
#include<QWidgetAction>

//回放所需要的头文件

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
#include "configuration.h"
#include "monitor.h"
#include "alert.h"
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
  void onAlertTimer();
    
public:

   QToolButton *zWZoomIn;
   QToolButton *zWZoomout;
   QToolButton *n1WZoomIn;
   QToolButton *n1WZoomout;
   QToolButton *n2WZoomIn;
   QToolButton *n2WZoomout;
  void readRgs();//读取监控组配置
  void writeRgs();//保存监控组配置

  Monitor *monitor;
  Configuration *configure;
  class Alert *alert;
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
//  QSound *sound;
   void adjustment();
   int bright_TrackbarValue;
   int alpha_contrast;
   int bOld;
   int aOld;
   bool isPseudo;
   bool oldPseudo;
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

    void paintRectangle(Mat image,double x,double y,double width,double height);//画矩形
    void paintCircle(Mat image,double x,double y);//画圆
    void paintScale(Mat image,double startw,double starth);//画标尺

   cv:: Mat QImageToMat(QImage image);
    static QImage MatToQImage(const cv::Mat& mat, QImage imgLabel);

    //---xiaotian   加载图片到Label上。
    void loadPictureToLabel(QLabel *label,QImage image);
    //加载图片到Label1上
    void loadPictureToLabel1(boolean isRect, QRect qrect, Scalar co, QRect rectRegion, vector<Point> ps);
    //加载图片到Label2上
    void loadPictureToLabel2(boolean isRect, QRect qrect, Scalar co, QRect rectRegion, vector<Point> ps);
    //加载图片到Label3上
    void loadPictureToLabel3(Scalar co, QRect rectRegion, vector<Point> ps);
    //加载图片到Label4上
    void loadPictureToLabel4(Scalar co, QRect rectRegion, vector<Point> ps);
    //加载图片到Label5上
    void loadPictureToLabel5();
    //加载图片到Label6上
    void loadPictureToLabel6(Scalar co, QRect rectRegion, vector<Point> ps);
    // 加载图片到Label7上
    void loadPictureToLabel7();
    //---xiaotian  在图像上绘制矩形框  使用数组，最多不超过10个
    void drawRecOnPic(Mat image,vector<Rectan> rectan);
    //绘制鼠标选取的矩形
    void drawRecOnPic2(Mat image, Rect rect);
    //---xiaotian   在图像是绘制标尺和矩形框
    void drawScaleAndRecOnPic(Mat image11,vector<Rectan> rectan,double startw,double starth);
    //---xiaotian  在图像上画圆和多边形
    void drawCircleOnPic(Mat image11,vector<Point> point,double x,double y);

    //---xiaotian  在界面上画label  图片1 图片2  图片5 图片6
    void drawUiLabel(Mat image,int index);
    //---xiaotian  在界面上画label  图片3 图片4.（这两张图片需要截取，所以属于一类方法）
    void drawUiLabelByCopy(Mat iamge,int index1);
    //处理鼠标拖拽事件，重载JMainFrame的鼠标事件处理函数
    void mousePressEvent(QMouseEvent *e);
    void mouseMoveEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);
    // void init();
    //添加属性设置中的变量
    //启动还是停止
    boolean isQidong;
    //暂停还是继续
    boolean isJixu;
    //告警启动还是关闭
    boolean isGaojing;
    //声音打开还是关闭
    boolean isShengyin;
    //目标属性是否跟随
    boolean isMubiao;
    //系统编号
    QString xtbh;
    //判断窗口是否打开
    bool is_open;
    //判断是否处于定义监控区域的状态
    boolean isDefiningRegion;
    //判断是否是定义矩形监控区域的状态
    boolean isDefiningRectRegion;
    //临时存储本次定义的监控区域
    vector<Region> rs;
    //定义的监控区域所属的监控区域组
    RegionGroup rg;

    int rgsIndex;
    vector<RegionGroup> rgs;

     QLabel *label;
     QLabel *label2;
     QLabel *label3;
     QLabel *label4;
     QLabel *label5;
     QLabel *label6;
     QLabel *label7;

     //加载到6个QLabel上的6个QImage
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
     QTimer *showAlert;
     //处理鼠标拖拽事件的变量
     boolean isDrag1;
     boolean isDrag2;
     boolean isMove;

     QGridLayout *gridlayout;

     //----------------以下为临时性变量-----------------
     MyInterface in;
     Mat image11;
     //动图需要的变量
     vector<Rectan> rectans1;
     int index;//用于标尺动
     //存储文件的图片需要的变量
     int index1;//读取第几张图片
     vector<QString> vc1;//存储第一栏的图片
     int index2;//读取第二栏第几张图片
     vector<QString> vc2;//存储第二栏的图片

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
         QString zhanwei;
          QLabel *zhanweiLabel;

protected:
     double getDirectionX(double x, Mat mat);

     double getDirectionY(double y, Mat mat);

     void addMyMenuBar();
     //工具条需要的变量
     void addMyToolBar();
     //临时性处理
     void tempProcessing();
     //自定义接口处理
     void selfProcessing();
     //与金老师的接口处理
     void jinProcessing();

     //自定义接口定时器
     virtual void selfTimerout();

     //与金老师接口的定时器处理
     void jinTimerout();
     //处理告警
     void alertProcessing(vector<MyObject> objs);

     QToolBar *mainToolBar;
     //第一组按钮：监控和后退，还有回放
     //QLabel *listLabel1;
     //QString startStopSet;
     QLabel *backLabel;
     QString mstopSet;
     QString backSet;
     //QString openSet;
     //QToolButton *startStop;//打开/暂停
     QToolButton *mstop;//暂停
     QToolButton *back;
     //回放
     QString openSet;
     QToolButton *open;//打开
     //第二组按钮，图像
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
     QToolButton *autom;//自动
     QToolButton *addbrightness;//亮度
     QToolButton *reducebrightness;
     QToolButton *addsaturation;//饱和度
     QToolButton *reducesaturation;
     QToolButton *pseudoColor;//伪彩色

     //第三组按钮，指示灯，五盏，一个目标一盏红灯；二个目标二盏红灯；三个目标三盏红灯；四个目标四盏红灯；五个目标及以上，五盏红灯
//     QString light1Set;
//     QString light2Set;
//     QString light3Set;
//     QString light4Set;
//     QString light5Set;

   // QLabel *light;
    QLabel *lights[5];
    QLabel *light1;
////     //QToolButton *light1;
     QLabel *light2;
     QLabel *light3;
     QLabel *light4;
     QLabel *light5;

     //第四组，显示编号和系统当前时间
      QLabel *currentTime;
    QLabel *serialNumber;//编号
     QLabel *systime;//时间
     //告警
     //QLabel *listLabel4;
     QLabel *setup;
     QLabel *alarm;
     QLabel *position;


     QString objectAttributeSet;//显示点击处位置
     QString manualSet;//增加标签

     QToolButton *objectAttribute;//显示点击处位置
     QToolButton *manual;//增加标签
     QToolButton *stability;

     QString stabilityset;
     QString openCloseSet;//启动关闭告警
     QString objectSet;//调整探测灵敏度等级
     QString voiceSet;
     QString lightSet;
     QString exitSet;


     QToolButton *openClose;//开/关
     QToolButton *objects;//目标对象的属性是否跟随目标
     QToolButton *voice;//声音
     QToolButton *light;//属性
     //QToolButton *setUp;//设置
     QToolButton *exitButton;//退出按钮
     //QToolButton *light;//指示灯
     //对话框需要的变量
     //QLineEdit *fileLineEdit;
     //QLabel *dialogLabel;

     //回放按钮所需要的参数
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

     QAction* targetAtt;

     QAction* openalert;
     QAction* closealert;

     QAction* help;
     QAction* about;

protected slots:
     void zoomIn();
     void zoomOut();
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
     virtual void alertInformation();


     virtual void exitFunction();

     void closeEvent(QCloseEvent *event);

     //菜单栏槽函数
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

//     void configurationClicked();
     void saveconfigurationClicked();
     void regionClicked();
     void figureClicked();

     void openalertClicked();
     void closealertClicked();
     void targetAttShow();

     void helpClicked();
     void aboutClicked();

     //void lightFunction();
    // void adjustbrightness();
     //回放所需函数
     void queDingFunction();
     void quXiaoFunction();
     virtual void timeLineFunction();
     void flash();

public slots:
    void init();
void configurationClicked();
//private:
public:
    Ui::MainWindow *ui;
//class TrackBar* trackBar;
//class STrackBar* strackBar;
Mat setPseudocolor(Mat& image);

private slots:

};
#include"backwindow.h"
#endif // MAINWINDOW_H
