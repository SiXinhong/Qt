#include "hwidget.h"
#include "mainwindow.h"
#include "myobject.h"

//opencv的头文件
#include <vector>
#include <highgui.h>
#include <cv.h>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace cv;
using namespace std;

HWidget::HWidget(QWidget *parent) :
    QWidget(parent){


}

void HWidget::setMat(Mat m){
    mat = m;
}

Mat HWidget::getMat(){
    return mat;
}

void HWidget::setObjects(vector<MyObject> os){
    this->objs = os;
}

vector<MyObject> HWidget::getObjects(){
    return this->objs;
}

void HWidget::draw(){
//    MainWindow *mw = (MainWindow*)parentWidget()->parentWidget();

//    int count = objs.size();
//    for (int i = 0; i < count;i++)
//    {
//        Rect rect = objs[i].getRect();
//        Scalar color = objs[i].getColor();
//        rectangle(mat,rect,color,2,1,0);
//        cv::cvtColor(mat, mat, CV_BGR2RGB);
//    }
//    //mw->paintScale(mat, 1.0, 1.0);
//    cv::cvtColor(mat,mat,CV_BGR2RGB);

//    mw->imgLabel4 = mw->MatToQImage(mat,mw->imgLabel4);

//    mw->loadPictureToLabel4();
    cv::Point point1(75,60);
    cv::Point point2(110,40);
    cv::Point point3(75,60);
    cv::Point point4(125,118);
    cv::Point point5(125,118);
    cv::Point point6(130,114);
    cv::Point point7(130,114);
    cv::Point point8(110,40);
    vector<cv::Point> points;
    points.push_back(point1);
    points.push_back(point2);
    points.push_back(point3);
    points.push_back(point4);
    points.push_back(point5);
    points.push_back(point6);
    points.push_back(point7);
    points.push_back(point8);
//    drawCircleOnPic(image,points,120,100);
    int count = points.size();
    for (int i = 0; i <count;i+=2)
    {
        cv::Point point1 = points[i];
        cv::Point point2 = points[i+1];
        line(mat,point1,point2,Scalar(255,255,0),1,8,0);
    }
    //在图像上画圆点
    count = objs.size();
    for (int i = 0; i < count; i++){
        cv::Point p = objs[i].getCenPoint();
        Scalar color = objs[i].getColor();
        circle(mat, p, 2, color,-1,8,2);//在图像中画出特征点，2是圆的半径
    }
    cv::cvtColor(mat,mat,CV_BGR2RGB);
    MainWindow *mw = (MainWindow*)parentWidget()->parentWidget();
    mw->imgLabel5 = mw->MatToQImage(mat, mw->imgLabel5);
    cv::cvtColor(mat, mat, CV_BGR2RGB);
    mw->loadPictureToLabel5();

}
