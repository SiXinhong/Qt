#ifndef MYOBJECT_H
#define MYOBJECT_H

//OpenCV头文件
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

    //最主要的就是一个box
    Rect box;

    //box和轨迹线的颜色
    Scalar color;

    int oid;// = -1;
    cv::Point cenPoint;// = cv::Point(-1, -1);         // 目标中心坐标
    cv::Size blocksize;// = cv::Size(0, 0);            // 检测框大小
    double Velocity;// = 0;                    // 运动速率
    double MotionDerection;// = 0;             // 运动方向
    int area;// = 0;                           // 目标面积
    int horizontalAxisLength;// = 0;           // 水平轴长度
    int verticalAxisLength;// = 0;             // 竖直轴长度
    double absoluteIntensity;// = 0;           // 绝对强度
    double relativeIntensity;// = 0;           // 相对强度

    vector<cv::Point> contours;                 // 目标轮廓
    cv::Mat Snapshoot;                          // 目标快照
    cv::Mat sihouette;                          // 目标剪影

    double targetScale;// = 0;                 // 目标尺度
    double CenSueEintensity;// = 0;            // 中央周围对比度的响应强度
    double SCRValue;// = 0;                    // 目标背景信杂比
    vector<double> theFeatures;             // 13维的小目标特征向量

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
//    MyObject& DeSerializable(const QByteArray &datagram);
//    QByteArray& Serializable(const MyObject &myObject);
//private:
//    friend QDataStream& writeMat(QDataStream &out,Mat &m);
//    friend QDataStream& readMat(QDataStream &in,Mat &m);
};

#endif // MYOBJECT_H
