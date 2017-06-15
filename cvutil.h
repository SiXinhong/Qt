#ifndef CVUTIL_H
#define CVUTIL_H

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

};

#endif // CVUTIL_H
