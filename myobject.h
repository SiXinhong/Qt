#ifndef MYOBJECT_H
#define MYOBJECT_H

//OpenCV头文件
#include <vector>
#include <highgui.h>
#include <cv.h>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

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

    void setRect(Rect r);
    Rect getRect();

    void SetColor(Scalar co);
    Scalar getColor();

};

#endif // MYOBJECT_H
