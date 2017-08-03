#ifndef MYOBJECT_H
#define MYOBJECT_H

//OpenCVͷ�ļ�
#include <vector>
#include <highgui.h>
#include <cv.h>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <QDataStream>
#include <QByteArray>


using namespace cv;
using namespace std;

class MyObject
{
public:
    MyObject();

    //����Ҫ�ľ���һ��box
    Rect box;

    //box�͹켣�ߵ���ɫ
    Scalar color;

    int oid;// = -1;
    cv::Point cenPoint;// = cv::Point(-1, -1);         // Ŀ����������
    cv::Size blocksize;// = cv::Size(0, 0);            // �����С
    double Velocity;// = 0;                    // �˶�����
    double MotionDerection;// = 0;             // �˶�����
    int area;// = 0;                           // Ŀ�����
    int horizontalAxisLength;// = 0;           // ˮƽ�᳤��
    int verticalAxisLength;// = 0;             // ��ֱ�᳤��
    double absoluteIntensity;// = 0;           // ����ǿ��
    double relativeIntensity;// = 0;           // ���ǿ��

    vector<cv::Point> contours;                 // Ŀ������
    cv::Mat Snapshoot;                          // Ŀ�����
    cv::Mat sihouette;                          // Ŀ���Ӱ

    double targetScale;// = 0;                 // Ŀ��߶�
    double CenSueEintensity;// = 0;            // ������Χ�Աȶȵ���Ӧǿ��
    double SCRValue;// = 0;                    // Ŀ�걳�����ӱ�
    vector<double> theFeatures;             // 13ά��СĿ����������


    cv::Mat pano;

    void setID(int id1);
    int getID();

    void setCenPoint(Point p);
    Point getCenPoint();

    void setBlockSize(Size s);
    Size getBlockSize();

    void setVelocity(double v);
    double getVelocity();

    void setMotionDerection(double md);
    double getMotionDerection();

    void setArea(int a);
    int getArea();

    void setHorizontalAxisLength(int hal);
    int getHorizontalAxisLength();

    void setVerticalAxisLength(int val);
    int getVerticalAxisLength();

    void setAbsoluteIntensity (double ai);
    double getAbsoluteIntensity();

    void setRelativeIntensity(double ri);
    double getRelativeIntensity();

    void setContours(vector<Point> con);
    vector<Point> getContours();

    void setSnapshoot(Mat ss);
    Mat getSnapshoot();

    void setSihouette(Mat si);
    Mat getSihouette();

    void setTargetScale(double ts);
    double getTargetScale();

    void setCenSueEintensity(double cse);
    double getCenSueEintensity();

    void setSCRValue(double scrv);
    double getSCRValue();

    void setTheFeatures(vector<double> fea);
    vector<double> getTheFeatures();

    void setRect(Rect r);
    Rect getRect();

    void SetColor(Scalar co);
    Scalar getColor();
    friend QDataStream& operator>>(QDataStream &in,MyObject& data);
    friend QDataStream& operator<<(QDataStream &out,MyObject& data);

    static QDataStream& writeMat(QDataStream &out,Mat &m);
    static QDataStream& readMat(QDataStream &in,Mat &m);
//    MyObject& DeSerializable(const QByteArray &datagram);
//    QByteArray& Serializable(const MyObject &myObject);
//private:
//    friend QDataStream& writeMat(QDataStream &out,Mat &m);
//    friend QDataStream& readMat(QDataStream &in,Mat &m);
};

#include "myinterface.h"
#endif // MYOBJECT_H
