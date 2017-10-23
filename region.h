#ifndef REGION_H
#define REGION_H

//OpenCVͷ�ļ�
#include <vector>
#include <highgui.h>
#include <cv.h>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

#include <QString>

using namespace cv;
using namespace std;

//���������
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

    //�Ǿ��λ��Ƕ���εı�־
    boolean isRect;

    //��ɫ
    Scalar color;

    //����
    Rect rect;

    //�����
    vector<Point> poly;

    void draw(Mat mat);

    boolean isInner(Point2f p);

};
#endif // REGION_H
