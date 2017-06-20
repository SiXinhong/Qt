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
    r1 = 20;
    x0 = 150;
    y0 = 150;
}

void HWidget::setMat(Mat m){
    mat = m;
}

Mat HWidget::getMat(){
    return mat;
}

void HWidget::setPano(Mat p){
    this->pano = p;
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

//�����ڻ�����ʾ�������꣬�������˶�Ŀ����ȫ��ͼ���е�λ��
double HWidget::getDirectionX(double x, double y){
    double x2 = x0 + (r/r0)*((r1+y) * qCos(x/r0));
    return x2;}

double HWidget::getDirectionY(double x, double y){
    double y2 = y0 + (r/r0)*((r1+y) * qSin(x/r0));
    return y2;
}

Point HWidget::getDirectionPoint(Point p){
    double x1 = p.x;
    double y1 = p.y;
    double x2 = this->getDirectionX(x1, y1);
    double y2 = this->getDirectionY(x1, y1);
    return Point(x2,y2);
}


//��û�����εİ˸��㣬��Ҫ��������ʾ������ע�Ķ��󼯺ϵ�������ȷ����
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
    //��ͼ���ϻ�Բ��
    count = objs.size();
    for (int i = 0; i < count; i++){
        cv::Point p = objs[i].getCenPoint();
        Scalar color = objs[i].getColor();
        circle(mat, this->getDirectionPoint(p), 2, color,-1,8,2);//��ͼ���л��������㣬2��Բ�İ뾶
    }
    cv::cvtColor(mat,mat,CV_BGR2RGB);
    mw->imgLabel5 = mw->MatToQImage(mat, mw->imgLabel5);
    cv::cvtColor(mat, mat, CV_BGR2RGB);
    mw->loadPictureToLabel5();

}
