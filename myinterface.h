#ifndef MYINTERFACE_H
#define MYINTERFACE_H


#include "myobjecttrack.h"
#include "show_sdk.h"
#include "socket.h"
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

    QString f0;
    QString f1;
    QString f2;
    QString f3;
    QString f4;
    QString f5;
    QString f6;
    QString f7;
    QString f8;
    QString f9;
    QString f10;
    QString f11;
    QString f12;

    int indexx;
    int indexy;

    int index1;//��ȡ�ڼ���ͼƬ

    vector<QString> vc1;//�洢��һ����ͼƬ
    int index2;//��ȡ�ڶ����ڼ���ͼƬ
    vector<QString> vc2;//�洢�ڶ�����ͼƬ
    vector<QString> vc;
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

    //�ӽ���ʦ��������panoImage�г�����ͼ��,ȫ��1��ȫ��2
    Mat qj1mat;

    Mat qj2mat;

    //���󼯺�
    vector<MyObject> objs;
    int sizeOfobjs;
    //λ��ȫ����ʾ��1�еĶ���
    vector<MyObject> objs1;

    //λ��ȫ����ʾ��2�еĶ���
    vector<MyObject> objs2;

    //����Ĺ켣����

    vector<MyObjectTrack> tracks;

    vector<MyObjectTrack> tracks1;

    vector<MyObjectTrack> tracks2;

    vector<MyObjectTrack> getTracks();

    vector<MyObjectTrack> getTracks1();

    vector<MyObjectTrack> getTracks2();

    double timett;
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

    void setTime(double t);
    double getTime();

    void setPano(Mat pano);
    Mat getPano();

    void setQJ1Mat(Mat qj1);
    Mat getQJ1Mat();

    void setQJ2Mat(Mat qj2);
    Mat getQJ2Mat();

    vector<MyObject> getObjs();
    void setObjs(vector<MyObject> os);
    //����Զ����ʵ������
    vector<MyObject> getObjs2();
    //�������������
    vector<MyObject> getRandomObjs();
    //��������obj��ʼ������
    void fillObjs();
    //���ȫ����ʾ��1�еĶ���
    vector<MyObject> getQj1Objs();
    //���ȫ����ʾ��2�еĶ���
    vector<MyObject> getQj2Objs();
    //����ۺ�����
    int getIntegratedData();

    int getIntegratedData2();
    //�洢ID
    vector<int> idSets;
//    //����ϵͳ����
//    int SetSysPara(int mode, const char *para_string, int id = 0);
//    //���ϵͳ����
//    int GetSysPara(int mode, char *para_string, int id = 0);

};

#endif // MYINTERFACE_H
