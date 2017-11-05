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

    boolean isActive;

    //多边形
    vector<Region> rs;

    QMap < QString,vector<Region> > rss;

    void draw(Mat mat);

    boolean isInner(Point2f p);

    vector<Region> hasObjects();

    void addRegion(Region r);

    void addRegionGroup(QString name,vector<Region> rs);


};
#endif // REGIONGROUP_H
