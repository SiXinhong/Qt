#include "lwidget.h"
#include "mainwindow.h"
#include "myobject.h"

#include <QtCore/qmath.h>
#include <math.h>

//opencv的头文件
#include <vector>
#include <highgui.h>
#include <cv.h>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace cv;
using namespace std;

LWidget::LWidget(QWidget *parent) :
    QWidget(parent){
    r0 = this->pano.cols/(2*M_PI);
    r = 120;
    x0 = 150;
    y0 = 150;
}

void LWidget::setMat(Mat m){
    mat = m;
}

Mat LWidget::getMat(){
    return mat;
}

void LWidget::setPano(Mat p){
    this->pano = p;
}

Mat LWidget::getPano(){
    return this->pano;
}

void LWidget::setObjects(vector<MyObject> os){
    this->objs = os;
}

vector<MyObject> LWidget::getObjects(){
    return this->objs;
}

//计算在环带显示区的坐标，输入是运动目标在全景图像中的位置
double LWidget::getDirectionX(double x, double y){
    double x2 = x0 + (r/r0)*(((y*(this->pano.cols)/(2*M_PI*pano.rows))-r0) * qSin(2*M_PI*x/pano.cols));
    return x2;
}

double LWidget::getDirectionY(double x, double y){
    double y2 = y0 + (r/r0)*((r0-(y*(this->pano.cols)/(2*M_PI*pano.rows))) * qCos(2*M_PI*x/pano.cols));
    return y2;
}

Point LWidget::getDirectionPoint(Point p){
    double x1 = p.x;
    double y1 = p.y;
    double x2 = this->getDirectionX(x1, y1);
    double y2 = this->getDirectionY(x1, y1);
    return Point(x2,y2);
}

Point LWidget::getPoint(Point p){
    double xa = p.x;
    double ya = p.y;

    double ra = qSqrt((xa-x0)*(xa-x0)+(ya-y0)*(ya-y0));

    double xaa = x0 + (r/ra)*(xa - x0);

    double yaa = y0 + (r/ra)*(ya - y0);

    return Point(xaa,yaa);
}

//获得画多边形的六个点，需要计算主显示区所关注的对象集合的坐标来确定。
vector<Point> LWidget::getPoints(vector<MyObject> objs){
    //找出对象集合中最左边的点，和最右边的点，就是x的最小点和最大点
    //先找最小点
    double xtemp1 = this->pano.cols;
    double ytemp1 = this->pano.rows;
    //再找最大点
    double xtemp2 = 0;
    double ytemp2 = 0;

    for(int i = 0; i < objs.size(); i++){
        MyObject obj = objs[i];
        if(xtemp1 > obj.getCenPoint().x){
            xtemp1 = obj.getCenPoint().x;
            ytemp1 = obj.getCenPoint().y;
        }
        if(xtemp2 < obj.getCenPoint().x){
            xtemp2 = obj.getCenPoint().x;
            ytemp2 = obj.getCenPoint().y;
        }
    }
    //再向左靠靠
    xtemp1 -= 5;
    //再向右靠靠
    xtemp2 += 5;

    Point p1 = Point(xtemp1, ytemp1);
    Point p2 = Point(xtemp2, ytemp2);
    Point p3 = Point(x0, y0);

    Point p11 = this->getPoint(p1);
    Point p22 = this->getPoint(p2);

    vector<Point> ps;
//    Point point1(75,60);
//    Point point2(110,39);
//    Point point3(75,60);
//    Point point4(150,150);
//    Point point5(110,40);
//    Point point6(150,150);
    ps.push_back(p11);
    ps.push_back(p22);
    ps.push_back(p11);
    ps.push_back(p3);
    ps.push_back(p22);
    ps.push_back(p3);
    return ps;
}

void LWidget::draw(){

    MainWindow *mw = (MainWindow*)parentWidget()->parentWidget();

    //画三角形
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
    mw->imgLabel6 = mw->MatToQImage(mat, mw->imgLabel6);
    cv::cvtColor(mat, mat, CV_BGR2RGB);
    mw->loadPictureToLabel6();

}
