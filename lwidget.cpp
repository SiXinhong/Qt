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
    r0 = this->pano.cols/(2*M_PI);
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

void LWidget::setObjects3(vector<MyObject> os3){
    this->objs3 = os3;
}

vector<MyObject> LWidget::getObjects3(){
    return this->objs3;
}

void LWidget::setObjects4(vector<MyObject> os4){
    this->objs4 = os4;
}

vector<MyObject> LWidget::getObjects4(){
    return this->objs4;
}

//计算在环带显示区的坐标，输入是运动目标在全景图像中的位置
double LWidget::getDirectionX(double x, double y){
   //顺时针90度
    double x90;
    if(x< 3*pano.cols/4)
        x90 = x+pano.cols/4;
    else
        x90 = x-3*pano.cols/4;
    double x2 = x0 + (r/r0)*(((y*(this->pano.cols)/(2*M_PI*pano.rows))-r0) * qSin(2*M_PI*x90/pano.cols));
    return x2;
}

double LWidget::getDirectionY(double x, double y){
    //顺时针90度
    double x90;
    if(x < 3*pano.cols/4)
        x90 = x+pano.cols/4;
    else
        x90 = x-3*pano.cols/4;
    double y2 = y0 + (r/r0)*((r0-(y*(this->pano.cols)/(2*M_PI*pano.rows))) * qCos(2*M_PI*x90/pano.cols));
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

//凝视显示区的，获得画多边形的六个点，需要计算主显示区所关注的对象集合的坐标来确定。
void LWidget::drawArc4(vector<MyObject> sobjs, Mat tmat){
    if(sobjs.size()==0)
           return;
       int size=sobjs.size();
       int maxIndex,minIndex;
       vector<MyObject> newsobjs;
       if(size == 1){
           maxIndex=0;
           minIndex=0;
           newsobjs.push_back(sobjs[0]);
       }else{
           for(int j=0;j<size;j++){
               int min=0;
               for(int i=1;i<sobjs.size();i++){
                   if(sobjs[i].getCenPoint().x<sobjs[min].getCenPoint().x){
                       min=i;

                   }
               }
               newsobjs.push_back(sobjs[min]);
               sobjs.erase(sobjs.begin()+min);
           }
           int w=pano.cols;
           double minDistance=w;
           for(int i=0;i<size;i++){
               int prevI=(i-1+size)%size;
               double distBetweenIandPrevI=newsobjs[i].getCenPoint().x-newsobjs[prevI].getCenPoint().x;
               if(distBetweenIandPrevI<0)
                   distBetweenIandPrevI+=w;
               double distTmp=w-distBetweenIandPrevI;
               if(distTmp<minDistance){
                   minDistance=distTmp;
                   minIndex=i;
                   maxIndex=prevI;
                   qDebug()<<minIndex<<"<<"<<maxIndex<<"w="<<w<<"dist="<<distTmp;
               }
           }
       }
       double xtemp1 = newsobjs[minIndex].getCenPoint().x;
       double ytemp1 = newsobjs[minIndex].getCenPoint().y;

       double xtemp2 = newsobjs[maxIndex].getCenPoint().x;
       double ytemp2 = newsobjs[maxIndex].getCenPoint().y;

       xtemp1-=150;
       if(xtemp1<0)
           xtemp1+=pano.cols;
       xtemp2+=150;
       if(xtemp2>pano.cols)
           xtemp2-=pano.cols;


       Point p1 = getDirectionPoint(Point(xtemp1, ytemp1));
       Point p2 = getDirectionPoint(Point(xtemp2, ytemp2));

       Point p3 = Point(x0, y0);

       Point p11 = this->getPoint(p1);
       Point p22 = this->getPoint(p2);

       line(tmat,p11,p3,Scalar(255,255,0),1,8,0);

       line(tmat,p22,p3,Scalar(255,255,0),1,8,0);
       //p11和p22之间是一段圆弧
       double angle1 = 180*qAtan((p22.y-y0)/(p22.x-x0))/M_PI;
       double angle2 = 180*qAtan((p11.y-y0)/(p11.x-x0))/M_PI;

       if(p22.x<x0){
           angle1+=180;
       }
       if(p11.x<x0){
           angle2+=180;
       }
       if(angle1<0 && angle2>180){
           angle1+=360;
       }
       ellipse(tmat,p3,Size(r, r),0,angle1,angle2,Scalar(255,255,0));
//    //找出对象集合中最左边的点，和最右边的点，就是x的最小点和最大点
//    //先找最小点
//    double xtemp1 = this->pano.cols;
//    double ytemp1 = this->pano.rows;
//    //再找最大点
//    double xtemp2 = 0;
//    double ytemp2 = 0;

//    for(int i = 0; i < sobjs.size(); i++){
//        MyObject obj = sobjs[i];
//        //qDebug()<<QString("######obj").append(QString::number(i))<<": "<<obj.getCenPoint().x;
//        if(xtemp1 > obj.getCenPoint().x){
//            xtemp1 = obj.getCenPoint().x;
//            ytemp1 = obj.getCenPoint().y;
//        }
//        if(xtemp2 < obj.getCenPoint().x){
//            xtemp2 = obj.getCenPoint().x;
//            ytemp2 = obj.getCenPoint().y;
//        }
//    }
//    //再向左上靠靠
//    if(xtemp1-5>=0 && ytemp1-5 >= 0){
//        xtemp1 -= 5;
//        ytemp1 -= 5;
//    }
//    //再向右下靠靠
//    if(xtemp2+5<= this->pano.cols && ytemp2+5<= this->pano.rows){
//        xtemp2 += 5;
//        ytemp2 += 5;
//    }
//    //重新找最小点
//    if((sobjs.size() > 0) && (xtemp2 - xtemp1 > this->pano.cols/2)){
//        xtemp1 = 0;

//        for(int i = 0; i < sobjs.size(); i++){
//            MyObject obj = objs[i];
//            if(obj.getRect().x > this->pano.cols/2){

//            }
//            else{
//                if(xtemp1 < obj.getCenPoint().x){
//                    xtemp1 = obj.getCenPoint().x;
//                    ytemp1 = obj.getCenPoint().y;
//                }

//            }
//        }
//    }


//    Point p1 = getDirectionPoint(Point(xtemp1, ytemp1));
//    Point p2 = getDirectionPoint(Point(xtemp2, ytemp2));
//    //qDebug()<<"p1 & p2"<<p1.x<<p1.y<<p2.x<<p2.y;
//    Point p3 = Point(x0, y0);

//    Point p11 = this->getPoint(p1);
//    Point p22 = this->getPoint(p2);

//    line(tmat,p11,p3,Scalar(255,255,0),1,8,0);

//    line(tmat,p22,p3,Scalar(255,255,0),1,8,0);
//    //p11和p22之间是一段圆弧
//    double angle1 = 180*qAtan((p22.y-y0)/(p22.x-x0))/M_PI;
//    double angle2 = 180*qAtan((p11.y-y0)/(p11.x-x0))/M_PI;

////    if(angle1 < 0){
////        angle1 += 360;
////    }
////    if(angle2 < 0){
////        angle2 += 360;
////    }
//    qDebug()<<angle1<<"--->"<<angle2;
//    if(p22.x<x0){
//        angle1+=180;
//    }
//    if(p11.x<x0){
//        angle2+=180;
//    }
//    if(angle1<0 && angle2>180){
//        angle1+=360;
//    }
//    //ellipse(tmat,p3,Size(r, r),0,angle1+180,angle2+180,Scalar(255,0,0));
//    ellipse(tmat,p3,Size(r, r),0,angle1,angle2,Scalar(255,255,0));
//    //cv::cvtColor(tmat,tmat,CV_BGR2RGB);
}

//主显示区的，获得画多边形的六个点，需要计算主显示区所关注的对象集合的坐标来确定。
void LWidget::drawArc3(vector<MyObject> sobjs, Mat tmat){
    if(sobjs.size()==0)
           return;
       int size=sobjs.size();
       int maxIndex,minIndex;
       vector<MyObject> newsobjs;
       if(size == 1){
           maxIndex=0;
           minIndex=0;
           newsobjs.push_back(sobjs[0]);
       }else{
           for(int j=0;j<size;j++){
               int min=0;
               for(int i=1;i<sobjs.size();i++){
                   if(sobjs[i].getCenPoint().x<sobjs[min].getCenPoint().x){
                       min=i;

                   }
               }
               newsobjs.push_back(sobjs[min]);
               sobjs.erase(sobjs.begin()+min);
           }
           int w=pano.cols;
           double minDistance=w;
           for(int i=0;i<size;i++){
               int prevI=(i-1+size)%size;
               double distBetweenIandPrevI=newsobjs[i].getCenPoint().x-newsobjs[prevI].getCenPoint().x;
               if(distBetweenIandPrevI<0)
                   distBetweenIandPrevI+=w;
               double distTmp=w-distBetweenIandPrevI;
               if(distTmp<minDistance){
                   minDistance=distTmp;
                   minIndex=i;
                   maxIndex=prevI;
                   qDebug()<<minIndex<<"<<"<<maxIndex<<"w="<<w<<"dist="<<distTmp;
               }
           }
       }
       double xtemp1 = newsobjs[minIndex].getCenPoint().x;
       double ytemp1 = newsobjs[minIndex].getCenPoint().y;

       double xtemp2 = newsobjs[maxIndex].getCenPoint().x;
       double ytemp2 = newsobjs[maxIndex].getCenPoint().y;

       xtemp1-=100;
       if(xtemp1<0)
           xtemp1+=pano.cols;
       xtemp2+=100;
       if(xtemp2>pano.cols)
           xtemp2-=pano.cols;


       Point p1 = getDirectionPoint(Point(xtemp1, ytemp1));
       Point p2 = getDirectionPoint(Point(xtemp2, ytemp2));

       Point p3 = Point(x0, y0);

       Point p11 = this->getPoint(p1);
       Point p22 = this->getPoint(p2);

       line(tmat,p11,p3,Scalar(255,0,0),1,8,0);

       line(tmat,p22,p3,Scalar(255,0,0),1,8,0);
       //p11和p22之间是一段圆弧
       double angle1 = 180*qAtan((p22.y-y0)/(p22.x-x0))/M_PI;
       double angle2 = 180*qAtan((p11.y-y0)/(p11.x-x0))/M_PI;

       if(p22.x<x0){
           angle1+=180;
       }
       if(p11.x<x0){
           angle2+=180;
       }
       if(angle1<0 && angle2>180){
           angle1+=360;
       }
       ellipse(tmat,p3,Size(r, r),0,angle1,angle2,Scalar(255,0,0));
//    //找出对象集合中最左边的点，和最右边的点，就是x的最小点和最大点
//    //先找最小点
//    double xtemp1 = this->pano.cols;
//    double ytemp1 = this->pano.rows;
//    //再找最大点
//    double xtemp2 = 0;
//    double ytemp2 = 0;

//    for(int i = 0; i < sobjs.size(); i++){
//        MyObject obj = sobjs[i];
//        //qDebug()<<QString("######obj").append(QString::number(i))<<": "<<obj.getCenPoint().x;
//        if(xtemp1 > obj.getCenPoint().x){
//            xtemp1 = obj.getCenPoint().x;
//            ytemp1 = obj.getCenPoint().y;
//        }
//        if(xtemp2 < obj.getCenPoint().x){
//            xtemp2 = obj.getCenPoint().x;
//            ytemp2 = obj.getCenPoint().y;
//        }
//    }
//    //再向左上靠靠
//    if(xtemp1-5>=0 && ytemp1-5 >= 0){
//        xtemp1 -= 5;
//        ytemp1 -= 5;
//    }
//    //再向右下靠靠
//    if(xtemp2+5<= this->pano.cols && ytemp2+5<= this->pano.rows){
//        xtemp2 += 5;
//        ytemp2 += 5;
//    }
//    //重新找最小点
//    if((sobjs.size() > 0) && (xtemp2 - xtemp1 > this->pano.cols/2)){
//        xtemp1 = 0;

//        for(int i = 0; i < sobjs.size(); i++){
//            MyObject obj = objs[i];
//            if(obj.getRect().x > this->pano.cols/2){

//            }
//            else{
//                if(xtemp1 < obj.getCenPoint().x){
//                    xtemp1 = obj.getCenPoint().x;
//                    ytemp1 = obj.getCenPoint().y;
//                }

//            }
//        }
//    }


//    Point p1 = getDirectionPoint(Point(xtemp1, ytemp1));
//    Point p2 = getDirectionPoint(Point(xtemp2, ytemp2));
//    //qDebug()<<"p1 & p2"<<p1.x<<p1.y<<p2.x<<p2.y;
//    Point p3 = Point(x0, y0);

//    Point p11 = this->getPoint(p1);
//    Point p22 = this->getPoint(p2);

//    line(tmat,p11,p3,Scalar(255,0,0),1,8,0);

//    line(tmat,p22,p3,Scalar(255,0,0),1,8,0);
//    //p11和p22之间是一段圆弧
//    double angle1 = 180*qAtan((p22.y-y0)/(p22.x-x0))/M_PI;
//    double angle2 = 180*qAtan((p11.y-y0)/(p11.x-x0))/M_PI;

////    if(angle1 < 0){
////        angle1 += 360;
////    }
////    if(angle2 < 0){
////        angle2 += 360;
////    }
//   qDebug()<<angle1<<"--->"<<angle2;
//    if(p22.x<x0){
//        angle1+=180;
//    }
//    if(p11.x<x0){

//        angle2+=180;
//    }
//    if(angle1<0 && angle2>180){
//        angle1+=360;
//    }
//    //ellipse(tmat,p3,Size(r, r),0,angle1+180,angle2+180,Scalar(255,0,0));
//    ellipse(tmat,p3,Size(r, r),0,angle1,angle2,Scalar(255,0,0));
//    //cv::cvtColor(tmat,tmat,CV_BGR2RGB);

//    vector<Point> ps;
////    Point point1(75,60);
////    Point point2(110,39);
////    Point point3(75,60);
////    Point point4(150,150);
////    Point point5(110,40);
////    Point point6(150,150);
//    ps.push_back(p11);
//    ps.push_back(p22);
//    ps.push_back(p11);
//    ps.push_back(p3);
//    ps.push_back(p22);
//    ps.push_back(p3);
//    return ps;
}

void LWidget::draw(){

    MainWindow *mw = (MainWindow*)parentWidget()->parentWidget();

    Mat tmat = this->mat.clone();//一定要在克隆上画

    //画三角形
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
        Scalar color = objs[i].getColor();
        circle(tmat, this->getDirectionPoint(p), 2, color,-1,8,2);//在图像中画出特征点，2是圆的半径
       // cv::cvtColor(tmat,tmat,CV_BGR2RGB);
    }
   // cv::cvtColor(tmat,tmat,CV_BGR2RGB);
    mw->imgLabel6 = mw->MatToQImage(tmat, mw->imgLabel6);
   // cv::cvtColor(tmat, tmat, CV_BGR2RGB);
    mw->loadPictureToLabel6();

}
