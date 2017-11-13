#ifndef REGIONGROUP_H
#define REGIONGROUP_H
//OpenCVͷ�ļ�
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

    //�Ƿ���ʾ
    boolean isActive;

    //�Ƿ񱨾�
    boolean isAlert;
    //�����
    vector<Region> rs;


    void draw(Mat &mat);

    boolean isInner(Point2f p);

    vector<Region> hasObjects();

    void addRegion(Region r);

    void setColor(Scalar c);


};
#endif // REGIONGROUP_H
