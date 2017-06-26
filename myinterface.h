#ifndef MYINTERFACE_H
#define MYINTERFACE_H

#include "myobject.h"
#include "myobjecttrack.h"
#include "show_sdk.h"

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

    int index;

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

    //从金老师传过来的panoImage切成两幅图像,全景1和全景2
    Mat qj1mat;

    Mat qj2mat;

    //对象集合
    vector<MyObject> objs;

    //位于全景显示区1中的对象
    vector<MyObject> objs1;

    //位于全景显示区2中的对象
    vector<MyObject> objs2;

    //对象的轨迹集合

    vector<MyObjectTrack> tracks;

    vector<MyObjectTrack> tracks1;

    vector<MyObjectTrack> tracks2;

    vector<MyObjectTrack> getTracks();

    vector<MyObjectTrack> getTracks1();

    vector<MyObjectTrack> getTracks2();

    Time timett;
    cv::Mat panoImage;//
    vector< SmallTarget> targets;

    QString getQJ1();
    void setQJ1(QString q1);

    QString getQJ2();
    void setQJ2(QString q2);

    QString getHD();
    void setHD(QString h);
    QString getLD();

    void setLD(QString l);

    void SetTime(Time t);
    Time getTime();

    void setPano(Mat pano);
    Mat getPano();

    void setQJ1Mat(Mat qj1);
    Mat getQJ1Mat();

    void setQJ2Mat(Mat qj2);
    Mat getQJ2Mat();

    vector<MyObject> getObjs();
    void setObjs(vector<MyObject> os);
    //获得自定义的实验数据
    vector<MyObject> getObjs2();

    //获得全景显示区1中的对象
    vector<MyObject> getQj1Objs();
    //获得全景显示区2中的对象
    vector<MyObject> getQj2Objs();
    //获得综合数据
    int getIntegratedData();
//    //设置系统参数
//    int SetSysPara(int mode, const char *para_string, int id = 0);
//    //获得系统参数
//    int GetSysPara(int mode, char *para_string, int id = 0);

};

#endif // MYINTERFACE_H
