#ifndef BACKWINDOW_H
#define BACKWINDOW_H

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
#include <QGridLayout>
#include <cv.h>
#include <phonon>
#include <QToolButton>
#include <QApplication>

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
#include "trackbar.h"
//#include"ltrackbar.h"
//回放所需要的头文件
//#include"backwindow.h"
#include<QDateEdit>
#include<QDateTimeEdit>
#include<QPushButton>
#include <QDesktopWidget>
//时间线需要的头文件
#include"timetrackbar.h"

using namespace cv;
using namespace std;


namespace Ui {
class BackWindow;
}

class BackWindow : public QMainWindow
{
    Q_OBJECT
public slots:
  void onTimerOut();
  void onTimerOut2();

public:
   void adjustment();
   int bright_TrackbarValue;
   bool isPseudo;
    //QApplication a;
       explicit BackWindow(QWidget *parent = 0);
       ~BackWindow();

    void paintEvent(QPaintEvent *);
    void resizeEvent(QResizeEvent *);
    void update();

    void test();

    void paintRectangle(Mat image,double x,double y,double width,double height);//画矩形
    void paintCircle(Mat image,double x,double y);//画圆
    void paintScale(Mat image,double startw,double starth);//画标尺

    cv::Mat QImageToMat(QImage image);
    QImage MatToQImage(const cv::Mat& mat, QImage imgLabel);

    //---xiaotian   加载图片到Label上。
    void loadPictureToLabel(QLabel *label,QImage image);
    //加载图片到Label1上
    void loadPictureToLabel1();
    //加载图片到Label2上
    void loadPictureToLabel2();
    //加载图片到Label3上
    void loadPictureToLabel3();
    //加载图片到Label4上
    void loadPictureToLabel4();
    //加载图片到Label5上
    void loadPictureToLabel5();
    //加载图片到Label6上
    void loadPictureToLabel6();
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

     QLabel *label;
     QLabel *label2;
     QLabel *label3;
     QLabel *label4;
     QLabel *label5;
     QLabel *label6;

     //加载到6个QLabel上的6个QImage
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
   timeTrackBar *ttbar;

protected:
     //工具条需要的变量
     void addMyToolBar();
     //临时性处理
     void tempProcessing();
     //自定义接口处理
     void selfProcessing();
     //与金老师的接口处理
     void jinProcessing();

     //自定义接口定时器
     void selfTimerout();

     //与金老师接口的定时器处理
     void jinTimerout();

     QToolBar *mainToolBar;
     //第一组按钮：监控和后退，还有回放
     //QLabel *listLabel1;
     QString startStopSet;
     QString mstopSet;
     QString backSet;
     //QString openSet;
     QToolButton *startStop;//打开/暂停
     QToolButton *mstop;//暂停
     QToolButton *back;
     //回放
     QString openSet;
     QToolButton *open;//打开
     //第二组按钮，图像
     //QLabel *listLabel3;
     QString automSet;
     QString brightnessSet;
     QString saturationSet;
     QString pseudoColorSet;
     QString serialNumberSet;
     QString timeSet;
     QToolButton *autom;//自动
     QToolButton *brightness;//亮度
     QToolButton *saturation;//饱和度
     QToolButton *pseudoColor;//伪彩色

     //第三组按钮，指示灯，五盏，一个目标一盏红灯；二个目标二盏红灯；三个目标三盏红灯；四个目标四盏红灯；五个目标及以上，五盏红灯
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

     //第四组，显示编号和系统当前时间
     QLabel *serialNumber;//编号
     QLabel *systime;//时间
     //告警
     //QLabel *listLabel4;
     QString openCloseSet;
     QString objectAttributeSet;
     QString manualSet;
     QString objectSet;
     QString attributeSet;
     QString voiceSet;
     QString exitSet;
     QString timeLineSet;

     QToolButton *openClose;//开/关
     QToolButton *objectAttribute;//对象属性
     QToolButton *manual;//手动
     QToolButton *objects;//目标对象的属性是否跟随目标
     QToolButton *attribute;//属性
     //QToolButton *setUp;//设置
     QToolButton *voice;//声音
     QToolButton *exitButton;//退出按钮

     //第五组 时间线
     QToolButton *timeLine;

     //回放按钮所需要的参数
     BackWindow *backwindow;
     QWidget *widgetNew;
//     QPushButton *inputBtn;
     QPushButton *queDing;
     QPushButton *quXiao;
     QLabel *startTime;
     QLabel *stopTime;
     QDateTimeEdit *startTimeSet;
     QDateTimeEdit *stopTimeSet;
     QGridLayout *gridLayout;

     class TrackBar *trackBar1;

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
     //回放所需函数
     void queDingFunction();
     void quXiaoFunction();

     //时间线
     void timeLineFunction();
private:
    Ui::BackWindow *ui;
//class TrackBar* trackBar;
Mat setPseudocolor(Mat& image);

};

#endif // MAINWINDOW_H
