#ifndef MYOBJECTTRACK_H
#define MYOBJECTTRACK_H

//OpenCV头文件
#include <vector>
#include <highgui.h>
#include <cv.h>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace cv;
using namespace std;

class MyObjectTrack
{
public:
    MyObjectTrack();

    int id;// = -1;
    vector<cv::Point> cenPoints;// = cv::Point(-1, -1);         // 目标中心坐标

    void setId(int id);
    int getId();

    vector<Point> getTrack();
    void setTrack(vector<Point> cps);

};

#endif // MYOBJECTTRACK_H
