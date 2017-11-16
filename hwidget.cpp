#include "hwidget.h"
#include "mainwindow.h"
#include "myobject.h"


#include <QtCore/qmath.h>
//opencv��ͷ�ļ�
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
    r1 = 30;
    x0 = 150;
    y0 = 150;
}

void HWidget::setMat(Mat m){
    mat = m;
    //���������ɻ���ͼ��

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

void HWidget::setObjects6(vector<MyObject> os6){
    this->objs6 = os6;
}

vector<MyObject> HWidget::getObjects6(){
    return this->objs6;
}

//�����ڻ�����ʾ�������꣬�������˶�Ŀ����ȫ��ͼ���е�λ��
double HWidget::getDirectionX(double x, double y){
    //˳ʱ����ת90��
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
    //˳ʱ����ת90��
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

void HWidget::drawArc4(Mat tmat, Rect re){

    Point p11 = getDirectionPoint(Point(re.x, re.y));
    Point p12 = getDirectionPoint(Point(re.x, re.y + re.height));
    Point p21 = getDirectionPoint(Point(re.x + re.width, re.y));
    Point p22 = getDirectionPoint(Point(re.x + re.width, re.y + re.height));

    Point p3 = Point(x0, y0);

    line(tmat,p11,p12,Scalar(255,255,0),1,8,0);

    line(tmat,p21,p22,Scalar(255,255,0),1,8,0);
    //p11��p22֮����һ��Բ��
    double angle1 = 180*qAtan((p21.y-y0)/(p21.x-x0))/M_PI;
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

    double r11 = qSqrt((p11.x-x0)*(p11.x-x0)+(p11.y-y0)*(p11.y-y0));
    double r12 = qSqrt((p12.x-x0)*(p12.x-x0)+(p12.y-y0)*(p12.y-y0));

    ellipse(tmat,p3,Size(r11, r11),0,angle1,angle2,Scalar(255,255,0));

    ellipse(tmat,p3,Size(r12, r12),0,angle1,angle2,Scalar(255,255,0));
}

//������ʾ��1�ģ���û�����εİ˸��㣬��Ҫ���㸨����ʾ��1����ע�Ķ��󼯺ϵ�������ȷ����

void HWidget::drawArc4(vector<MyObject> sobjs, Mat tmat){
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
                   //qDebug()<<minIndex<<"<<"<<maxIndex<<"w="<<w<<"dist="<<distTmp;
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

//    //�ҳ����󼯺�������ߵĵ㣬�����ұߵĵ㣬����x����С�������
//    //������С��
//    //qDebug()<<QString("xuanzhong");
//    //qDebug()<<sobjs.size();
//    double xtemp1 = this->pano.cols;
//    double ytemp1 = this->pano.rows;
//    //��������
//    double xtemp2 = 0;
//    double ytemp2 = 0;

//    for(int i = 0; i < sobjs.size(); i++){
//        MyObject obj = sobjs[i];
//        if(xtemp1 > obj.getCenPoint().x){
//            xtemp1 = obj.getCenPoint().x;
//            ytemp1 = obj.getCenPoint().y;
//        }
//        if(xtemp2 < obj.getCenPoint().x){
//            xtemp2 = obj.getCenPoint().x;
//            ytemp2 = obj.getCenPoint().y;
//        }
//    }
//    //�������Ͽ���
//    if(xtemp1-5>=0 && ytemp1-5 >= 0){
//        xtemp1 -= 5;
//        ytemp1 -= 5;
//    }
//    //�������¿���
//    if(xtemp2+5<= this->pano.cols && ytemp2+5<= this->pano.rows){
//        xtemp2 += 5;
//        ytemp2 += 5;
//    }
//    //��������С��
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
    Point p3 = Point(x0, y0);

    Point p11 = this->getPoint1(p1);
    Point p12 = this->getPoint2(p1);

    Point p21 = this->getPoint1(p2);
    Point p22 = this->getPoint2(p2);

    line(tmat,p11,p12,Scalar(255,255,0),1,8,0);

    line(tmat,p21,p22,Scalar(255,255,0),1,8,0);
    //p11��p22֮����һ��Բ��
    double angle1 = 180*qAtan((p21.y-y0)/(p21.x-x0))/M_PI;
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


void HWidget::drawArc6(Mat tmat, Rect re){

    Point p11 = getDirectionPoint(Point(re.x, re.y));
    Point p12 = getDirectionPoint(Point(re.x, re.y + re.height));
    Point p21 = getDirectionPoint(Point(re.x + re.width, re.y));
    Point p22 = getDirectionPoint(Point(re.x + re.width, re.y + re.height));

    Point p3 = Point(x0, y0);

    line(tmat,p11,p12,Scalar(255,0,0),1,8,0);

    line(tmat,p21,p22,Scalar(255,0,0),1,8,0);
    //p11��p22֮����һ��Բ��
    double angle1 = 180*qAtan((p21.y-y0)/(p21.x-x0))/M_PI;
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

    double r11 = qSqrt((p11.x-x0)*(p11.x-x0)+(p11.y-y0)*(p11.y-y0));
    double r12 = qSqrt((p12.x-x0)*(p12.x-x0)+(p12.y-y0)*(p12.y-y0));

    ellipse(tmat,p3,Size(r11, r11),0,angle1,angle2,Scalar(255,0,0));

    ellipse(tmat,p3,Size(r12, r12),0,angle1,angle2,Scalar(255,0,0));
}

//������ʾ��2�ģ���û�����εİ˸��㣬��Ҫ���㸨����ʾ��2����ע�Ķ��󼯺ϵ�������ȷ����
void HWidget::drawArc6(vector<MyObject> sobjs, Mat tmat){
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
                   //qDebug()<<minIndex<<"<<"<<maxIndex<<"w="<<w<<"dist="<<distTmp;
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

//    //�ҳ����󼯺�������ߵĵ㣬�����ұߵĵ㣬����x����С�������
//    //������С��
//    //qDebug()<<QString("xuanzhong");
//    //qDebug()<<sobjs.size();
//    double xtemp1 = this->pano.cols;
//    double ytemp1 = this->pano.rows;
//    //��������
//    double xtemp2 = 0;
//    double ytemp2 = 0;

//    for(int i = 0; i < sobjs.size(); i++){
//        MyObject obj = sobjs[i];
//        if(xtemp1 > obj.getCenPoint().x){
//            xtemp1 = obj.getCenPoint().x;
//            ytemp1 = obj.getCenPoint().y;
//        }
//        if(xtemp2 < obj.getCenPoint().x){
//            xtemp2 = obj.getCenPoint().x;
//            ytemp2 = obj.getCenPoint().y;
//        }
//    }
//    //�������Ͽ���
//    if(xtemp1-5>=0 && ytemp1-5 >= 0){
//        xtemp1 -= 5;
//        ytemp1 -= 5;
//    }
//    //�������¿���
//    if(xtemp2+5<= this->pano.cols && ytemp2+5<= this->pano.rows){
//        xtemp2 += 5;
//        ytemp2 += 5;
//    }
//    //��������С��
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
    Point p3 = Point(x0, y0);

    Point p11 = this->getPoint1(p1);
    Point p12 = this->getPoint2(p1);

    Point p21 = this->getPoint1(p2);
    Point p22 = this->getPoint2(p2);

    line(tmat,p11,p12,Scalar(255,0,0),1,8,0);

    line(tmat,p21,p22,Scalar(255,0,0),1,8,0);
    //p11��p22֮����һ��Բ��
    double angle1 = 180*qAtan((p21.y-y0)/(p21.x-x0))/M_PI;
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

void HWidget::drawArc3(Mat tmat, Rect re){

    Point p11 = getDirectionPoint(Point(re.x, re.y));
    Point p12 = getDirectionPoint(Point(re.x, re.y + re.height));
    Point p21 = getDirectionPoint(Point(re.x + re.width, re.y));
    Point p22 = getDirectionPoint(Point(re.x + re.width, re.y + re.height));

    Point p3 = Point(x0, y0);

    line(tmat,p11,p12,Scalar(0,0,255),1,8,0);

    line(tmat,p21,p22,Scalar(0,0,255),1,8,0);
    //p11��p22֮����һ��Բ��
    double angle1 = 180*qAtan((p21.y-y0)/(p21.x-x0))/M_PI;
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

    double r11 = qSqrt((p11.x-x0)*(p11.x-x0)+(p11.y-y0)*(p11.y-y0));
    double r12 = qSqrt((p12.x-x0)*(p12.x-x0)+(p12.y-y0)*(p12.y-y0));

    ellipse(tmat,p3,Size(r11, r11),0,angle1,angle2,Scalar(0,0,255));

    ellipse(tmat,p3,Size(r12, r12),0,angle1,angle2,Scalar(0,0,255));
}

//����ʾ���ģ���û�����εİ˸��㣬��Ҫ��������ʾ������ע�Ķ��󼯺ϵ�������ȷ����
void HWidget::drawArc3(vector<MyObject> sobjs, Mat tmat){
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
                   //qDebug()<<minIndex<<"<<"<<maxIndex<<"w="<<w<<"dist="<<distTmp;
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

//    //�ҳ����󼯺�������ߵĵ㣬�����ұߵĵ㣬����x����С�������
//    //������С��
//    //qDebug()<<QString("xuanzhong");
//    //qDebug()<<sobjs.size();
//    double xtemp1 = this->pano.cols;
//    double ytemp1 = this->pano.rows;
//    //��������
//    double xtemp2 = 0;
//    double ytemp2 = 0;

//    for(int i = 0; i < sobjs.size(); i++){
//        MyObject obj = sobjs[i];
//        if(xtemp1 > obj.getCenPoint().x){
//            xtemp1 = obj.getCenPoint().x;
//            ytemp1 = obj.getCenPoint().y;
//        }
//        if(xtemp2 < obj.getCenPoint().x){
//            xtemp2 = obj.getCenPoint().x;
//            ytemp2 = obj.getCenPoint().y;
//        }
//    }
//    //�������Ͽ���
//    if(xtemp1-5>=0 && ytemp1-5 >= 0){
//        xtemp1 -= 5;
//        ytemp1 -= 5;
//    }
//    //�������¿���
//    if(xtemp2+5<= this->pano.cols && ytemp2+5<= this->pano.rows){
//        xtemp2 += 5;
//        ytemp2 += 5;
//    }
//    //��������С��
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
//    Point p3 = Point(x0, y0);

    Point p11 = this->getPoint1(p1);
    Point p12 = this->getPoint2(p1);

    Point p21 = this->getPoint1(p2);
    Point p22 = this->getPoint2(p2);

    line(tmat,p11,p12,Scalar(0,0,255),1,8,0);

    line(tmat,p21,p22,Scalar(0,0,255),1,8,0);
    //p11��p22֮����һ��Բ��
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

    ellipse(tmat,p3,Size(r1, r1),0,angle1,angle2,Scalar(0,0,255));

    ellipse(tmat,p3,Size(r, r),0,angle1,angle2,Scalar(0,0,255));
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

    Mat tmat = this->mat.clone();//һ��Ҫ�ڿ�¡�ϻ�
    //�������
//    vector<Point> points = this->getPoints(mw->widget3->getObjects());
//    int count = points.size();
//    for (int i = 0; i <count;i+=2)
//    {
//        cv::Point point1 = points[i];
//        cv::Point point2 = points[i+1];
//        line(mat,point1,point2,Scalar(255,255,0),1,8,0);
//    }
//    if(mw->widget3->getObjects().size() > 0){
//        this->drawArc3(mw->widget3->getObjects(),tmat);
//    }

//    if(mw->widget4->getObjects().size() > 0){
//        this->drawArc4(mw->widget4->getObjects(),tmat);
//    }

//    if(mw->widget6->getObjects().size() > 0){
//        this->drawArc6(mw->widget6->getObjects(),tmat);
//    }
//    if(mw->widget3->getObjects().size() > 0){
        this->drawArc3(tmat, mw->widget3->rect);
//    }

//    if(mw->widget4->getObjects().size() > 0){
        this->drawArc4(tmat, mw->widget4->rect);
//    }

//    if(mw->widget6->getObjects().size() > 0){
        this->drawArc6(tmat, mw->widget6->rect);
//    }
    //��ͼ���ϻ�Բ��
    int count = objs.size();
    for (int i = 0; i < count; i++){
        cv::Point p = objs[i].getCenPoint();
//        qDebug()<<p.x;
//        qDebug()<<p.y;
//        qDebug()<<this->getDirectionPoint(p).x;
//        qDebug()<<this->getDirectionPoint(p).y;
        Scalar color = objs[i].getColor();
        circle(tmat, this->getDirectionPoint(p), 2, color,-1,8,2);//��ͼ���л��������㣬2��Բ�İ뾶
       // cv::cvtColor(tmat,tmat,CV_BGR2RGB);
    }
 //   cv::cvtColor(tmat,tmat,CV_BGR2RGB);
    mw->imgLabel5 = mw->MatToQImage(tmat, mw->imgLabel5);
 //   cv::cvtColor(tmat, tmat, CV_BGR2RGB);
    mw->loadPictureToLabel5();

}
