#include "lwidget.h"
#include "mainwindow.h"
#include "myobject.h"

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


}

void LWidget::setMat(Mat m){
    mat = m;
}

Mat LWidget::getMat(){
    return mat;
}

void LWidget::setObjects(vector<MyObject> os){
    this->objs = os;
}

vector<MyObject> LWidget::getObjects(){
    return this->objs;
}

//�����ڻ�����ʾ�������꣬�������˶�Ŀ����ȫ��ͼ���е�λ��
double LWidget::getDirectionX(double x){
    return x;
}

double LWidget::getDirectionY(double y){
    return y;
}

Point LWidget::getDirectionPoint(Point p){
    double x1 = p.x;
    double y1 = p.y;
    double x2 = this->getDirectionX(x1);
    double y2 = this->getDirectionY(y1);
    return Point(x2,y2);
}


//��û�����ε������㣬��Ҫ��������ʾ������ע�Ķ��󼯺ϵ�������ȷ����
vector<Point> LWidget::getPoints(vector<MyObject> objs){
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
