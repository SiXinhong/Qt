#ifndef MYINTERFACE_H
#define MYINTERFACE_H

#include "myobject.h"

#include <QString>

//OpenCV头文件
#include <vector>
#include <highgui.h>
#include <cv.h>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace cv;
using namespace std;

class MyInterface
{
private:
    //以下是临时变量，为模拟从接口来的不同的图像-------
    QString filename1;
    QString filename2;
    QString filename3;
    QString filename4;
    QString filename5;
    QString filename6;
    QString filename7;
    QString filename8;

    int index1;//读取第几张图片
    vector<QString> vc1;//存储第一栏的图片
    int index2;//读取第二栏第几张图片
    vector<QString> vc2;//存储第二栏的图片
    //临时变量结束------------------------------

public:
    MyInterface();

    //全景显示区1的图片的URL
    QString qj1;
    //全景显示区2的图片的URL
    QString qj2;
    //环带显示区的图片的URL
    QString hd;
    //雷达显示区的图片的URL
    QString ld;

    //对象集合
    vector<MyObject> objs;

    QString getQJ1();
    void setQJ1(QString q1);

    QString getQJ2();
    void setQJ2(QString q2);

    QString getHD();
    void setHD(QString h);
    QString getLD();

    void setLD(QString l);

    vector<MyObject> getObjs();
    void setObjs(vector<MyObject> os);
};

#endif // MYINTERFACE_H
