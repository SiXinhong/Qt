#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QImage>
#include <QPixmap>
#include <QLabel>
#include "mylabel.h"
#include "qjwidget.h"
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
    
public:
    //QApplication a;
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    //QApplication getA();
    //void setA(QApplication aa);
    void paintEvent(QPaintEvent *);
    void resizeEvent(QResizeEvent *);
    void update();
//    QImage paintRectangle(Mat image,double x,double y,double width,double height);//画矩形
//    QImage paintCircle(Mat image,double x,double y);//画圆
//    QImage paintScale(Mat image,double startw,double starth);//画标尺

    void paintRectangle(Mat image,double x,double y,double width,double height);//画矩形
    void paintCircle(Mat image,double x,double y);//画圆
    void paintScale(Mat image,double startw,double starth);//画标尺

    cv::Mat QImageToMat(QImage image);
    QImage MatToQImage(const cv::Mat& mat);

    //---xiaotian   加载图片到Label上。
    void loadPictureToLabel(QLabel *label,QImage image);
    //---xiaotian  在图像上绘制矩形框  使用数组，最多不超过10个
    QImage drawRecOnPic(Mat image,vector<Rectan> rectan);
    //---xiaotian   在图像是绘制标尺和矩形框
    QImage drawScaleAndRecOnPic(Mat image11,vector<Rectan> rectan,double startw,double starth);
    //---xiaotian  在图像上画圆和多边形
    QImage drawCircleOnPic(Mat image11,vector<Point> point,double x,double y);

    //---xiaotian  在界面上画label  图片1 图片2  图片5 图片6
    void drawUiLabel(string imgurl,int index);
    //---xiaotian  在界面上画label  图片3 图片4.（这两张图片需要截取，所以属于一类方法）
    void drawUiLabelByCopy(string imgurl,int index1);

     QLabel *label;
     QLabel *label2;
     QLabel *label3;
     QLabel *label4;
     QLabel *label5;
     QLabel *label6;

     QjWidget* widget1;
     QjWidget* widget2;
     QWidget* widget3;
     QWidget* widget4;
     QWidget* widget5;
     QWidget* widget6;
     QGridLayout *gridlayout;

     Mat image11;
     //动图需要的变量
     QTimer *timer;
     vector<Rectan> rectans1;
     int index;//用于标尺动
     //存储文件的图片需要的变量
     int index1;//读取第几张图片
     vector<QString> vc1;//存储第一栏的图片
     int index2;//读取第二栏第几张图片
     vector<QString> vc2;//存储第二栏的图片

     //添加对话框所需要的变量

protected:
     //工具条需要的变量
     void addMyToolBar();
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
     //QString playSet;
     //QString rstopSet;
     //QString timeLineSet;
     //QLabel *listLabel2;
     QToolButton *open;//打开
     //QToolButton *play;//播放
     //QToolButton *rstop;//暂停
     //QToolButton *timeLine;//时间线
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
     QLabel *time;//时间
     //告警
     //QLabel *listLabel4;
     QString openCloseSet;
     QString objectAttributeSet;
     QString manualSet;
     QString objectSet;
     QString attributeSet;
     QString voiceSet;
     QString exitSet;

     QToolButton *openClose;//开/关
     QToolButton *objectAttribute;//对象属性
     QToolButton *manual;//手动
     QToolButton *objects;//目标对象的属性是否跟随目标
     QToolButton *attribute;//属性
     //QToolButton *setUp;//设置
     QToolButton *voice;//声音
     QToolButton *exitButton;//退出按钮
     //QToolButton *light;//指示灯
     //对话框需要的变量
     //QLineEdit *fileLineEdit;
     QLabel *dialogLabel;

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
     QImage imgLabel;
     QImage image;
     QImage image2;
     //调节图像所需要的参数
//     QSlider *slider;
//     QLineEdit *lineEdit;
//     QLabel *labelbrightness;
//     QMenu menu;

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
<<<<<<< HEAD
     void closeEvent(QCloseEvent *event);
=======
     void lightFunction();
     void adjustbrightness();

  //   void on_trackbar(int, void*);
//     void setLineEditValue(int);


>>>>>>> 1ab6e46fb26066a072d742ca9d4babbe3f67fc3f
private:
    Ui::MainWindow *ui;



};

#endif // MAINWINDOW_H
