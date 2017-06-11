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
     //���
     QLabel *listLabel1;
     QString startStopSet;
     QString mstopSet;
     QToolButton *startStop;//��/��ͣ
     QToolButton *mstop;//��ͣ
     //�ط�
     QString openSet;
     QString playSet;
     QString rstopSet;
     QString timeLineSet;
     QLabel *listLabel2;
     QToolButton *open;//��
     QToolButton *play;//����
     QToolButton *rstop;//��ͣ
     QToolButton *timeLine;//ʱ����
     //ͼ��
     QLabel *listLabel3;
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
     QToolButton *serialNumber;//���
     QToolButton *time;//ʱ��
     //�澯
     QLabel *listLabel4;
     QString openCloseSet;
     QString manualSet;
     QString attributeSet;
     QString setUpSet;
     QString voiceSet;
     QString lightSet;
     QToolButton *openClose;//��/��
     QToolButton *manual;//�ֶ�
     QToolButton *attribute;//����
     QToolButton *setUp;//����
     QToolButton *voice;//����
     QToolButton *light;//ָʾ��
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
     void adjustbrightness();

  //   void on_trackbar(int, void*);

private:
    Ui::MainWindow *ui;



};

#endif // MAINWINDOW_H
