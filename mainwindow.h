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
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
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
     //监控
     QLabel *listLabel1;
     QString startStopSet;
     QString mstopSet;
     QToolButton *startStop;//打开/暂停
     QToolButton *mstop;//暂停
     //回放
     QString openSet;
     QString playSet;
     QString rstopSet;
     QString timeLineSet;
     QLabel *listLabel2;
     QToolButton *open;//打开
     QToolButton *play;//播放
     QToolButton *rstop;//暂停
     QToolButton *timeLine;//时间线
     //图像
     QLabel *listLabel3;
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
     QToolButton *serialNumber;//编号
     QToolButton *time;//时间
     //告警
     QLabel *listLabel4;
     QString openCloseSet;
     QString manualSet;
     QString attributeSet;
     QString setUpSet;
     QString voiceSet;
     QString lightSet;
     QToolButton *openClose;//开/关
     QToolButton *manual;//手动
     QToolButton *attribute;//属性
     QToolButton *setUp;//设置
     QToolButton *voice;//声音
     QToolButton *light;//指示灯
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
//     QImage imgLabe3;
//     QImage imgLabel4;
//     QImage imgLabel5;
//     QImage imgLabel6;
     QImage imgLabel;
    QImage image;
    QImage image2;

protected slots:
     void startStopFunction();
	 void mstopFunction();

     void openFunction();
     void playFunction();
     void rstopFunction();
     void timeLineFunction();

     void automFunction();
     void brightnessFunction();
     void saturationFunction();
     void pseudoColorFunction();
     void serialNumberFunction();
     void timeFunction();

     void openCloseFunction();
     void manualFunction();
     void attributeFunction();
     void setUpFunction();
     void voiceFunction();
     void lightFunction();

  //   void on_trackbar(int, void*);

private:
    Ui::MainWindow *ui;



};

#endif // MAINWINDOW_H
