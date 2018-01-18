#ifndef REGIONGROUP_H
#define REGIONGROUP_H
//OpenCV头文件
#include <vector>
#include <QMap>
#include <highgui.h>
#include <cv.h>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

#include <QString>
#include <QDebug>


#include "region.h"

using namespace cv;
using namespace std;

//监控区域组类
class RegionGroup
{
public:
    RegionGroup();

    RegionGroup(QString name, Scalar c);

    RegionGroup(QString name, Scalar c, vector<Region> rs);

    //颜色
    Scalar color;

    QString name;

    //是否显示
    bool isActive;

    //是否报警
    bool isAlert;
    //多边形
    vector<Region> rs;


    void draw(Mat &mat);

    bool isInner(Point2f p);

    vector<Region> hasObjects();

    void addRegion(Region r);

    void setColor(Scalar c);

    bool timeActive[7][48];

    bool isTimeAlertTrue();

    void drawLabel(Mat images);

    bool isDrawLabel;


};
#endif // REGIONGROUP_H
