#ifndef MYOBJECT_H
#define MYOBJECT_H

//OpenCVͷ�ļ�
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

    //����Ҫ�ľ���һ��box
    Rect box;

    //box�͹켣�ߵ���ɫ
    Scalar color;

    void setRect(Rect r);
    Rect getRect();

    void SetColor(Scalar co);
    Scalar getColor();

};

#endif // MYOBJECT_H
