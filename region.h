#ifndef REGION_H
#define REGION_H

//OpenCV头文件
#include <vector>
#include <highgui.h>
#include <cv.h>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

#include <QString>

using namespace cv;
using namespace std;

//监控区域类
class Region
{
public:
    Region();

    Region(QString name, Scalar c);

    Region(QString name, Scalar c, double x, double y, double width, double height);

    Region(QString name, Scalar c, Rect re);

    Region(QString name, Scalar c, vector<Point> ps);

    QString name;

    boolean hasObjects;

    boolean isActive;

    //是矩形还是多边形的标志
    boolean isRect;

    //颜色
    Scalar color;

    //矩形
    Rect rect;

    //多边形
    vector<Point> poly;

    void draw(Mat &mat);

    //在显示区画，只画一变，draw在主mat中（两个全景图拼接）画两份
    void draw1Time(Mat &mat);
    boolean isInner(Point2f p);

};
#endif // REGION_H
