#include "hwidget.h"
#include "mainwindow.h"
#include "myobject.h"


#include <QtCore/qmath.h>
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
    r = 120;
    r1 = 60;
    x0 = 150;
    y0 = 150;
}

void HWidget::setMat(Mat m){
    mat = m;
    //在这里生成环带图像

    for(int i=0;i<pano.rows;i++){

        for(int j=0;j<pano.cols;j++){
            int ii = (int)this->getDirectionX((double)j, (double)i);
            int jj = (int)this->getDirectionY((double)j, (double)i);
            mat.at<cv::Vec3b>(jj,ii)[0]=pano.at<cv::Vec3b>(i,j)[0];
            mat.at<cv::Vec3b>(jj,ii)[1]=pano.at<cv::Vec3b>(i,j)[1];
            mat.at<cv::Vec3b>(jj,ii)[2]=pano.at<cv::Vec3b>(i,j)[2];
        }
    }
}

Mat HWidget::getMat(){
    return mat;
}

void HWidget::setPano(Mat p){
    this->pano = p;
    r0 = this->pano.cols/(2*M_PI);
}

Mat HWidget::getPano(){
    return this->pano;
}

void HWidget::setObjects(vector<MyObject> os){
    this->objs = os;
}

vector<MyObject> HWidget::getObjects(){
    return this->objs;
}

void HWidget::setObjects3(vector<MyObject> os3){
    this->objs3 = os3;
}

vector<MyObject> HWidget::getObjects3(){
    return this->objs3;
}

void HWidget::setObjects4(vector<MyObject> os4){
    this->objs4 = os4;
}

vector<MyObject> HWidget::getObjects4(){
    return this->objs4;
}

//计算在环带显示区的坐标，输入是运动目标在全景图像中的位置
double HWidget::getDirectionX(double x, double y){
    //顺时针旋转90度
    double x90;
    if(x< 3*pano.cols/4)
        x90 = x+pano.cols/4;
    else
        x90 = x-3*pano.cols/4;
    //double x2 = x0 + (r/r0)*(((y*(r-r1)/(pano.rows))-r0) * qSin(2*M_PI*x/pano.cols));
    double x2 = x0 + ((y*(r-r1)/(pano.rows))-(r/r0)*r0) * qSin(2*M_PI*x90/pano.cols);
    return x2;
}

double HWidget::getDirectionY(double x, double y){
    //double y2 = y0 + (r/r0)*((r0-(y*(r-r1)/(pano.rows))) * qCos(2*M_PI*x/pano.cols));
    //顺时针旋转90度
    double x90;
    if(x< 3*pano.cols/4)
        x90 = x+pano.cols/4;
    else
        x90 = x-3*pano.cols/4;

    double y2 = y0 + ((r/r0)*r0-(y*(r-r1)/(pano.rows))) * qCos(2*M_PI*x90/pano.cols);
    return y2;
}

Point HWidget::getDirectionPoint(Point p){
    double x1 = p.x;
    double y1 = p.y;
    double x2 = this->getDirectionX(x1, y1);
    double y2 = this->getDirectionY(x1, y1);
    return Point(x2,y2);
}

Point HWidget::getPoint1(Point p){
    double xa = p.x;
    double ya = p.y;

    double ra = qSqrt((xa-x0)*(xa-x0)+(ya-y0)*(ya-y0));

    double xaa = x0 + (r/ra)*(xa - x0);

    double yaa = y0 + (r/ra)*(ya - y0);

    return Point(xaa,yaa);
}

Point HWidget::getPoint2(Point p){
    double xa = p.x;
    double ya = p.y;

    double ra = qSqrt((xa-x0)*(xa-x0)+(ya-y0)*(ya-y0));

    double xaa = x0 + (r1/ra)*(xa - x0);

    double yaa = y0 + (r1/ra)*(ya - y0);

    return Point(xaa,yaa);
}

//凝视显示区的，获得画多边形的八个点，需要计算主显示区所关注的对象集合的坐标来确定。
void HWidget::drawArc4(vector<MyObject> sobjs, Mat tmat){
    //找出对象集合中最左边的点，和最右边的点，就是x的最小点和最大点
    //先找最小点
    //qDebug()<<QString("xuanzhong");
    //qDebug()<<sobjs.size();
    double xtemp1 = this->pano.cols;
    double ytemp1 = this->pano.rows;
    //再找最大点
    double xtemp2 = 0;
    double ytemp2 = 0;

    for(int i = 0; i < sobjs.size(); i++){
        MyObject obj = sobjs[i];
        if(xtemp1 > obj.getCenPoint().x){
            xtemp1 = obj.getCenPoint().x;
            ytemp1 = obj.getCenPoint().y;
        }
        if(xtemp2 < obj.getCenPoint().x){
            xtemp2 = obj.getCenPoint().x;
            ytemp2 = obj.getCenPoint().y;
        }
    }
    //再向左上靠靠
    if(xtemp1-5>=0 && ytemp1-5 >= 0){
        xtemp1 -= 5;
        ytemp1 -= 5;
    }
    //再向右下靠靠
    if(xtemp2+5<= this->pano.cols && ytemp2+5<= this->pano.rows){
        xtemp2 += 5;
        ytemp2 += 5;
    }
    //重新找最小点
    if((sobjs.size() > 0) && (xtemp2 - xtemp1 > this->pano.cols/2)){
        xtemp1 = 0;

        for(int i = 0; i < sobjs.size(); i++){
            MyObject obj = objs[i];
            if(obj.getRect().x > this->pano.cols/2){

            }
            else{
                if(xtemp1 < obj.getCenPoint().x){
                    xtemp1 = obj.getCenPoint().x;
                    ytemp1 = obj.getCenPoint().y;
                }

            }
        }
    }


    Point p1 = getDirectionPoint(Point(xtemp1, ytemp1));
    Point p2 = getDirectionPoint(Point(xtemp2, ytemp2));
    Point p3 = Point(x0, y0);

    Point p11 = this->getPoint1(p1);
    Point p12 = this->getPoint2(p1);

    Point p21 = this->getPoint1(p2);
    Point p22 = this->getPoint2(p2);

    line(tmat,p11,p12,Scalar(255,255,0),1,8,0);

    line(tmat,p21,p22,Scalar(255,255,0),1,8,0);
    //p11和p22之间是一段圆弧
    double angle1 = 180*qAtan((p21.y-y0)/(p21.x-x0))/M_PI;
    double angle2 = 180*qAtan((p11.y-y0)/(p11.x-x0))/M_PI;

//    if(angle1 < 0){
//        angle1 += 360;
//    }
//    if(angle2 < 0){
//        angle2 += 360;
//    }
    if(p22.x<x0){
        angle1+=180;
    }
    if(p11.x<x0){
        angle2+=180;
    }
    if(angle1<0 && angle2>180){
        angle1+=360;
    }

    ellipse(tmat,p3,Size(r1, r1),0,angle1,angle2,Scalar(255,255,0));

    ellipse(tmat,p3,Size(r, r),0,angle1,angle2,Scalar(255,255,0));
   // cv::cvtColor(tmat,tmat,CV_BGR2RGB);

//    vector<Point> ps;
//    cv::Point point1(75,60);
//    cv::Point point2(110,40);
//    cv::Point point3(75,60);
//    cv::Point point4(125,118);
//    cv::Point point5(125,118);
//    cv::Point point6(130,114);
//    cv::Point point7(130,114);
//    cv::Point point8(110,40);
//    ps.push_back(p11);
//    ps.push_back(p21);
//    ps.push_back(p11);
//    ps.push_back(p12);
//    ps.push_back(p12);
//    ps.push_back(p22);
//    ps.push_back(p22);
//    ps.push_back(p21);
    //return ps;
}

//主显示区的，获得画多边形的八个点，需要计算主显示区所关注的对象集合的坐标来确定。
void HWidget::drawArc3(vector<MyObject> sobjs, Mat tmat){
    //找出对象集合中最左边的点，和最右边的点，就是x的最小点和最大点
    //先找最小点
    //qDebug()<<QString("xuanzhong");
    //qDebug()<<sobjs.size();
    double xtemp1 = this->pano.cols;
    double ytemp1 = this->pano.rows;
    //再找最大点
    double xtemp2 = 0;
    double ytemp2 = 0;

    for(int i = 0; i < sobjs.size(); i++){
        MyObject obj = sobjs[i];
        if(xtemp1 > obj.getCenPoint().x){
            xtemp1 = obj.getCenPoint().x;
            ytemp1 = obj.getCenPoint().y;
        }
        if(xtemp2 < obj.getCenPoint().x){
            xtemp2 = obj.getCenPoint().x;
            ytemp2 = obj.getCenPoint().y;
        }
    }
    //再向左上靠靠
    if(xtemp1-5>=0 && ytemp1-5 >= 0){
        xtemp1 -= 5;
        ytemp1 -= 5;
    }
    //再向右下靠靠
    if(xtemp2+5<= this->pano.cols && ytemp2+5<= this->pano.rows){
        xtemp2 += 5;
        ytemp2 += 5;
    }
    //重新找最小点
    if((sobjs.size() > 0) && (xtemp2 - xtemp1 > this->pano.cols/2)){
        xtemp1 = 0;

        for(int i = 0; i < sobjs.size(); i++){
            MyObject obj = objs[i];
            if(obj.getRect().x > this->pano.cols/2){

            }
            else{
                if(xtemp1 < obj.getCenPoint().x){
                    xtemp1 = obj.getCenPoint().x;
                    ytemp1 = obj.getCenPoint().y;
                }

            }
        }
    }


    Point p1 = getDirectionPoint(Point(xtemp1, ytemp1));
    Point p2 = getDirectionPoint(Point(xtemp2, ytemp2));
    Point p3 = Point(x0, y0);

    Point p11 = this->getPoint1(p1);
    Point p12 = this->getPoint2(p1);

    Point p21 = this->getPoint1(p2);
    Point p22 = this->getPoint2(p2);

    line(tmat,p11,p12,Scalar(255,0,0),1,8,0);

    line(tmat,p21,p22,Scalar(255,0,0),1,8,0);
    //p11和p22之间是一段圆弧
    double angle1 = 180*qAtan((p21.y-y0)/(p21.x-x0))/M_PI;
    double angle2 = 180*qAtan((p11.y-y0)/(p11.x-x0))/M_PI;

//    if(angle1 < 0){
//        angle1 += 360;
//    }
//    if(angle2 < 0){
//        angle2 += 360;
//    }
    if(p22.x<x0){
        angle1+=180;
    }
    if(p11.x<x0){
        angle2+=180;
    }
    if(angle1<0 && angle2>180){
         angle1+=360;
    }

    ellipse(tmat,p3,Size(r1, r1),0,angle1,angle2,Scalar(255,0,0));

    ellipse(tmat,p3,Size(r, r),0,angle1,angle2,Scalar(255,0,0));
   // cv::cvtColor(tmat,tmat,CV_BGR2RGB);

//    vector<Point> ps;
//    cv::Point point1(75,60);
//    cv::Point point2(110,40);
//    cv::Point point3(75,60);
//    cv::Point point4(125,118);
//    cv::Point point5(125,118);
//    cv::Point point6(130,114);
//    cv::Point point7(130,114);
//    cv::Point point8(110,40);
//    ps.push_back(p11);
//    ps.push_back(p21);
//    ps.push_back(p11);
//    ps.push_back(p12);
//    ps.push_back(p12);
//    ps.push_back(p22);
//    ps.push_back(p22);
//    ps.push_back(p21);
    //return ps;
}


void HWidget::draw(){
    MainWindow *mw = (MainWindow*)parentWidget()->parentWidget();

    Mat tmat = this->mat.clone();//一定要在克隆上画
    //画多边形
//    vector<Point> points = this->getPoints(mw->widget3->getObjects());
//    int count = points.size();
//    for (int i = 0; i <count;i+=2)
//    {
//        cv::Point point1 = points[i];
//        cv::Point point2 = points[i+1];
//        line(mat,point1,point2,Scalar(255,255,0),1,8,0);
//    }
    if(mw->widget3->getObjects().size() > 0){
        this->drawArc3(mw->widget3->getObjects(),tmat);
    }

    if(mw->widget4->getObjects().size() > 0){
        this->drawArc4(mw->widget4->getObjects(),tmat);
    }
    //在图像上画圆点
    int count = objs.size();
    for (int i = 0; i < count; i++){
        cv::Point p = objs[i].getCenPoint();
//        qDebug()<<p.x;
//        qDebug()<<p.y;
//        qDebug()<<this->getDirectionPoint(p).x;
//        qDebug()<<this->getDirectionPoint(p).y;
        Scalar color = objs[i].getColor();
        circle(tmat, this->getDirectionPoint(p), 2, color,-1,8,2);//在图像中画出特征点，2是圆的半径
       // cv::cvtColor(tmat,tmat,CV_BGR2RGB);
    }
 //   cv::cvtColor(tmat,tmat,CV_BGR2RGB);
    mw->imgLabel5 = mw->MatToQImage(tmat, mw->imgLabel5);
 //   cv::cvtColor(tmat, tmat, CV_BGR2RGB);
    mw->loadPictureToLabel5();

}
