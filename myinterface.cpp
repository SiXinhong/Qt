#include "myobject.h"
#include "myinterface.h";

#include <QString>

//OpenCV头文件
#include <vector>
#include <highgui.h>
#include <cv.h>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace cv;
using namespace std;

MyInterface::MyInterface(){
    //存储第一栏
    filename1 = "./s1/1.bmp";
    filename2 = "./s1/2.bmp";
    filename3 = "./s1/3.bmp";
    filename4 = "./s1/4.bmp";
    //存储第二栏
    filename5 = "./s2/1.bmp";
    filename6 = "./s2/2.bmp";
    filename7 = "./s2/3.bmp";
    filename8 = "./s2/4.bmp";
    //将第一栏存储在vector中
    vc1.push_back(filename1);
    vc1.push_back(filename2);
    vc1.push_back(filename3);
    vc1.push_back(filename4);
    //将第二栏存储在vector中
    vc2.push_back(filename5);
    vc2.push_back(filename6);
    vc2.push_back(filename7);
    vc2.push_back(filename8);

    index1=0;//用于取第一栏的图片
    index2=0;//用于取第二栏的图片

    this->hd = "./0.png";
    this->ld = "./0.png";

}


QString MyInterface::getQJ1(){
    index1++;
    qj1 = vc1[(index1)%4];
    return qj1;
}

void MyInterface::setQJ1(QString q1){
    this->qj1 = q1;
}

QString MyInterface::getQJ2(){
    index2++;
    qj2 = vc2[(index2)%4];
    return qj2;
}

void MyInterface::setQJ2(QString q2){
    this->qj2 = q2;
}

QString MyInterface::getHD(){
    return hd;
}

void MyInterface::setHD(QString h){
    this->hd = h;
}

QString MyInterface::getLD(){
    return ld;
}

void MyInterface::setLD(QString l){
    this->ld = l;
}

//随机生成3个对象
vector<MyObject> MyInterface::getObjs(){
    int x1 = (unsigned) RNG(time(NULL))&1800;
    int y1 = (unsigned) RNG(time(NULL))&500;
    int w = 100;
    int h = 100;
    MyObject mo1 = MyObject();
    mo1.setRect(Rect(x1,y1,w,h));

    int x2 = (unsigned) RNG(time(NULL))&1800;
    int y2 = (unsigned) RNG(time(NULL))&500;
    MyObject mo2 = MyObject();
    mo2.setRect(Rect(x2,y2,w,h));

    int x3 = (unsigned) RNG(time(NULL))&1800;
    int y3 = (unsigned) RNG(time(NULL))&500;
    MyObject mo3 = MyObject();
    mo3.setRect(Rect(x3,y3,w,h));

    vector<MyObject> vc;
    vc.push_back(mo1);
    vc.push_back(mo2);
    vc.push_back(mo3);

    return vc;
}

void MyInterface::setObjs(vector<MyObject> os){
    this->objs = os;
}
