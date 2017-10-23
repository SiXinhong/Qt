#ifndef REGIONGROUP_H
#define REGIONGROUP_H
//OpenCVͷ�ļ�
#include <vector>
#include <highgui.h>
#include <cv.h>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

#include <QString>

#include "region.h"

using namespace cv;
using namespace std;

//�����������
class RegionGroup
{
public:
    RegionGroup();

    RegionGroup(QString name, Scalar c);

    RegionGroup(QString name, Scalar c, vector<Region> rs);

    //��ɫ
    Scalar color;

    QString name;

    boolean isActive;

    //�����
    vector<Region> rs;

    void draw(Mat mat);

    boolean isInner(Point2f p);

    vector<Region> hasObjects();

    void addRegion(Region r);

};
#endif // REGIONGROUP_H
