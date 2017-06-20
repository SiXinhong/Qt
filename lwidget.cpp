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

//�����ڻ�����ʾ�������꣬�������˶�Ŀ����ȫ��ͼ���е�λ��
double LWidget::getDirectionX(double x, double y){
    double x2 = x0 + (r/r0)*(y * qCos(x/r0));
    return x2;
}

double LWidget::getDirectionY(double x, double y){
    double y2 = y0 + (r/r0)*(y * qSin(x/r0));
    return y2;
}

Point LWidget::getDirectionPoint(Point p){
    double x1 = p.x;
    double y1 = p.y;
    double x2 = this->getDirectionX(x1, y1);
    double y2 = this->getDirectionY(x1, y1);
    return Point(x2,y2);
}


//��û�����ε������㣬��Ҫ��������ʾ������ע�Ķ��󼯺ϵ�������ȷ����
vector<Point> LWidget::getPoints(vector<MyObject> objs){
    //�ҳ����󼯺�������ߵĵ㣬�����ұߵĵ㣬����x����С�������
    //������С��
    double xtemp1 = this->pano.cols;
    double ytemp1 = this->pano.rows;
    //��������
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
    //�����󿿿�
    xtemp1 -= 5;
    //�����ҿ���
    xtemp2 += 5;



    vector<Point> ps;
    Point point1(75,60);
    Point point2(110,39);
    Point point3(75,60);
    Point point4(150,150);
    Point point5(110,40);
    Point point6(150,150);
    ps.push_back(point1);
    ps.push_back(point2);
    ps.push_back(point3);
    ps.push_back(point4);
    ps.push_back(point5);
    ps.push_back(point6);
    return ps;
}

void LWidget::draw(){

    MainWindow *mw = (MainWindow*)parentWidget()->parentWidget();

    vector<Point> points = this->getPoints(mw->widget3->getObjects());
    int count = points.size();
    for (int i = 0; i <count;i+=2)
    {
        cv::Point point1 = points[i];
        cv::Point point2 = points[i+1];
        line(mat,point1,point2,Scalar(255,255,0),1,8,0);
    }
    //��ͼ���ϻ�Բ��
    count = objs.size();
    for (int i = 0; i < count; i++){
        cv::Point p = objs[i].getCenPoint();
        Scalar color = objs[i].getColor();
        circle(mat, this->getDirectionPoint(p), 2, color,-1,8,2);//��ͼ���л��������㣬2��Բ�İ뾶
    }
    cv::cvtColor(mat,mat,CV_BGR2RGB);
    mw->imgLabel6 = mw->MatToQImage(mat, mw->imgLabel6);
    cv::cvtColor(mat, mat, CV_BGR2RGB);
    mw->loadPictureToLabel6();

}
