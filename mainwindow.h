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
//    QImage paintRectangle(Mat image,double x,double y,double width,double height);//������
//    QImage paintCircle(Mat image,double x,double y);//��Բ
//    QImage paintScale(Mat image,double startw,double starth);//�����

    void paintRectangle(Mat image,double x,double y,double width,double height);//������
    void paintCircle(Mat image,double x,double y);//��Բ
    void paintScale(Mat image,double startw,double starth);//�����

    cv::Mat QImageToMat(QImage image);
    QImage MatToQImage(const cv::Mat& mat);

    //---xiaotian   ����ͼƬ��Label�ϡ�
    void loadPictureToLabel(QLabel *label,QImage image);
    //---xiaotian  ��ͼ���ϻ��ƾ��ο�  ʹ�����飬��಻����10��
    QImage drawRecOnPic(Mat image,vector<Rectan> rectan);
    //---xiaotian   ��ͼ���ǻ��Ʊ�ߺ;��ο�
    QImage drawScaleAndRecOnPic(Mat image11,vector<Rectan> rectan,double startw,double starth);
    //---xiaotian  ��ͼ���ϻ�Բ�Ͷ����
    QImage drawCircleOnPic(Mat image11,vector<Point> point,double x,double y);

    //---xiaotian  �ڽ����ϻ�label  ͼƬ1 ͼƬ2  ͼƬ5 ͼƬ6
    void drawUiLabel(string imgurl,int index);
    //---xiaotian  �ڽ����ϻ�label  ͼƬ3 ͼƬ4.��������ͼƬ��Ҫ��ȡ����������һ�෽����
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
     //��ͼ��Ҫ�ı���
     QTimer *timer;
     vector<Rectan> rectans1;
     int index;//���ڱ�߶�
     //�洢�ļ���ͼƬ��Ҫ�ı���
     int index1;//��ȡ�ڼ���ͼƬ
     vector<QString> vc1;//�洢��һ����ͼƬ
     int index2;//��ȡ�ڶ����ڼ���ͼƬ
     vector<QString> vc2;//�洢�ڶ�����ͼƬ

     //��ӶԻ�������Ҫ�ı���

protected:
     //��������Ҫ�ı���
     void addMyToolBar();
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
     //QString playSet;
     //QString rstopSet;
     //QString timeLineSet;
     //QLabel *listLabel2;
     QToolButton *open;//��
     //QToolButton *play;//����
     //QToolButton *rstop;//��ͣ
     //QToolButton *timeLine;//ʱ����
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
     QLabel *time;//ʱ��
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
     //����ͼ������Ҫ�Ĳ���
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
     void closeEvent(QCloseEvent *event);

     //void lightFunction();
     void adjustbrightness();

  //   void on_trackbar(int, void*);
//     void setLineEditValue(int);


//>>>>>>> 1ab6e46fb26066a072d742ca9d4babbe3f67fc3f
private:
    Ui::MainWindow *ui;



};

#endif // MAINWINDOW_H
