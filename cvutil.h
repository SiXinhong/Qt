#ifndef CVUTIL_H
#define CVUTIL_H

#include <QImage>

//OpenCVÍ·ÎÄ¼þ
#include <vector>
#include <highgui.h>
#include <cv.h>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace cv;
using namespace std;

class CVUtil
{
public:
    CVUtil();

    static Scalar getRandomColor();
    static cv::Mat QImageToMat(QImage image);
    static QImage MatToQImage(const cv::Mat& mat, QImage imgLabel);
    static void paintScale(Mat image,double startw,double starth, double endw, double endy);

};

#endif // CVUTIL_H
