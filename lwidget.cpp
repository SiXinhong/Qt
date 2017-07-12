#include "lwidget.h"
#include "mainwindow.h"
#include "myobject.h"

#include <QtCore/qmath.h>
#include <math.h>

//opencv��ͷ�ļ�
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

//�����ڻ�����ʾ�������꣬�������˶�Ŀ����ȫ��ͼ���е�λ��
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

//������ʾ���ģ���û�����ε������㣬��Ҫ��������ʾ������ע�Ķ��󼯺ϵ�������ȷ����
void LWidget::drawArc4(vector<MyObject> sobjs, Mat tmat){
    //�ҳ����󼯺�������ߵĵ㣬�����ұߵĵ㣬����x����С�������
    //������С��
    double xtemp1 = this->pano.cols;
    double ytemp1 = this->pano.rows;
    //��������
    double xtemp2 = 0;
    double ytemp2 = 0;

    for(int i = 0; i < sobjs.size(); i++){
        MyObject obj = sobjs[i];
        if(xtemp1 > obj.getRect().x){
            xtemp1 = obj.getRect().x;
            //ytemp1 = obj.getRect().y;
        }
        if(ytemp1 > obj.getRect().y){
            ytemp1 = obj.getRect().y;
        }
        if(xtemp2 < (obj.getRect().x + obj.getRect().width)){
            xtemp2 = obj.getRect().x + obj.getRect().width;
            //ytemp2 = obj.getRect().y + obj.getRect().height;
        }
        if(ytemp2 < (obj.getRect().y + obj.getRect().height)){
            ytemp2 = obj.getRect().y + obj.getRect().height;
        }
    }
    //�������Ͽ���
    if(xtemp1-5>=0 && ytemp1-5 >= 0){
        xtemp1 -= 5;
        ytemp1 -= 5;
    }
    //�������¿���
    if(xtemp2+5<= this->pano.cols && ytemp2+5<= this->pano.rows){
        xtemp2 += 5;
        ytemp2 += 5;
    }


    Point p1 = getDirectionPoint(Point(xtemp1, ytemp1));
    Point p2 = getDirectionPoint(Point(xtemp2, ytemp2));
    //qDebug()<<"p1 & p2"<<p1.x<<p1.y<<p2.x<<p2.y;
    Point p3 = Point(x0, y0);

    Point p11 = this->getPoint(p1);
    Point p22 = this->getPoint(p2);

    line(tmat,p11,p3,Scalar(255,255,0),1,8,0);

    line(tmat,p22,p3,Scalar(255,255,0),1,8,0);
    //p11��p22֮����һ��Բ��
    double angle1 = 180*qAtan((p22.y-y0)/(p22.x-x0))/M_PI;
    double angle2 = 180*qAtan((p11.y-y0)/(p11.x-x0))/M_PI;

//    if(angle1 < 0){
//        angle1 += 360;
//    }
//    if(angle2 < 0){
//        angle2 += 360;
//    }

    ellipse(tmat,p3,Size(r, r),0,angle1+180,angle2+180,Scalar(255,255,0));
    cv::cvtColor(tmat,tmat,CV_BGR2RGB);

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

//����ʾ���ģ���û�����ε������㣬��Ҫ��������ʾ������ע�Ķ��󼯺ϵ�������ȷ����
void LWidget::drawArc3(vector<MyObject> sobjs, Mat tmat){
    //�ҳ����󼯺�������ߵĵ㣬�����ұߵĵ㣬����x����С�������
    //������С��
    double xtemp1 = this->pano.cols;
    double ytemp1 = this->pano.rows;
    //��������
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
    //�������Ͽ���
    if(xtemp1-5>=0 && ytemp1-5 >= 0){
        xtemp1 -= 5;
        ytemp1 -= 5;
    }
    //�������¿���
    if(xtemp2+5<= this->pano.cols && ytemp2+5<= this->pano.rows){
        xtemp2 += 5;
        ytemp2 += 5;
    }


    Point p1 = getDirectionPoint(Point(xtemp1, ytemp1));
    Point p2 = getDirectionPoint(Point(xtemp2, ytemp2));
    //qDebug()<<"p1 & p2"<<p1.x<<p1.y<<p2.x<<p2.y;
    Point p3 = Point(x0, y0);

    Point p11 = this->getPoint(p1);
    Point p22 = this->getPoint(p2);

    line(tmat,p11,p3,Scalar(255,0,0),1,8,0);

    line(tmat,p22,p3,Scalar(255,0,0),1,8,0);
    //p11��p22֮����һ��Բ��
    double angle1 = 180*qAtan((p22.y-y0)/(p22.x-x0))/M_PI;
    double angle2 = 180*qAtan((p11.y-y0)/(p11.x-x0))/M_PI;

//    if(angle1 < 0){
//        angle1 += 360;
//    }
//    if(angle2 < 0){
//        angle2 += 360;
//    }

    ellipse(tmat,p3,Size(r, r),0,angle1+180,angle2+180,Scalar(255,0,0));
    cv::cvtColor(tmat,tmat,CV_BGR2RGB);

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

    Mat tmat = this->mat.clone();//һ��Ҫ�ڿ�¡�ϻ�

    //��������
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
    //��ͼ���ϻ�Բ��
    int count = objs.size();
    for (int i = 0; i < count; i++){
        cv::Point p = objs[i].getCenPoint();
        Scalar color = objs[i].getColor();
        circle(tmat, this->getDirectionPoint(p), 2, color,-1,8,2);//��ͼ���л��������㣬2��Բ�İ뾶
        cv::cvtColor(tmat,tmat,CV_BGR2RGB);
    }
    cv::cvtColor(tmat,tmat,CV_BGR2RGB);
    mw->imgLabel6 = mw->MatToQImage(tmat, mw->imgLabel6);
    cv::cvtColor(tmat, tmat, CV_BGR2RGB);
    mw->loadPictureToLabel6();

}
