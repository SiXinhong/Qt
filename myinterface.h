#ifndef MYINTERFACE_H
#define MYINTERFACE_H

#include "myobject.h"

#include <QString>

//OpenCVͷ�ļ�
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
    //��������ʱ������Ϊģ��ӽӿ����Ĳ�ͬ��ͼ��-------
    QString filename1;
    QString filename2;
    QString filename3;
    QString filename4;
    QString filename5;
    QString filename6;
    QString filename7;
    QString filename8;

    int index1;//��ȡ�ڼ���ͼƬ
    vector<QString> vc1;//�洢��һ����ͼƬ
    int index2;//��ȡ�ڶ����ڼ���ͼƬ
    vector<QString> vc2;//�洢�ڶ�����ͼƬ
    //��ʱ��������------------------------------

public:
    MyInterface();

    //ȫ����ʾ��1��ͼƬ��URL
    QString qj1;
    //ȫ����ʾ��2��ͼƬ��URL
    QString qj2;
    //������ʾ����ͼƬ��URL
    QString hd;
    //�״���ʾ����ͼƬ��URL
    QString ld;

    //���󼯺�
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
