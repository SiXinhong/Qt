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

//计算在环带显示区的坐标，输入是运动目标在全景图像中的位置
double HWidget::getDirectionX(double x){
    return x;
}

double HWidget::getDirectionY(double y){
    return y;
}

Point HWidget::getDirectionPoint(Point p){
    double x1 = p.x;
    double y1 = p.y;
    double x2 = this->getDirectionX(x1);
    double y2 = this->getDirectionY(y1);
    return Point(x2,y2);
}


//获得画多边形的八个点，需要计算主显示区所关注的对象集合的坐标来确定。
vector<Point> HWidget::getPoints(vector<MyObject> objs){
    vector<Point> ps;
    cv::Point point1(75,60);
    cv::Point point2(110,40);
    cv::Point point3(75,60);
    cv::Point point4(125,118);
    cv::Point point5(125,118);
    cv::Point point6(130,114);
    cv::Point point7(130,114);
    cv::Point point8(110,40);
    ps.push_back(point1);
    ps.push_back(point2);
    ps.push_back(point3);
    ps.push_back(point4);
    ps.push_back(point5);
    ps.push_back(point6);
    ps.push_back(point7);
    ps.push_back(point8);
    return ps;
}

void HWidget::draw(){
    MainWindow *mw = (MainWindow*)parentWidget()->parentWidget();

    vector<Point> points = this->getPoints(mw->widget3->getObjects());
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
        circle(mat, this->getDirectionPoint(p), 2, color,-1,8,2);//在图像中画出特征点，2是圆的半径
    }
    cv::cvtColor(mat,mat,CV_BGR2RGB);
    mw->imgLabel5 = mw->MatToQImage(mat, mw->imgLabel5);
    cv::cvtColor(mat, mat, CV_BGR2RGB);
    mw->loadPictureToLabel5();

}
