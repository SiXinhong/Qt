#include "cvutil.h"

//OpenCVÍ·ÎÄ¼þ
#include <vector>
#include <highgui.h>
#include <cv.h>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace cv;
using namespace std;

CVUtil::CVUtil(){

}

Scalar CVUtil::getRandomColor(){
    int icolor = (unsigned) RNG(time(NULL));
    return Scalar(icolor&255, (icolor>>8)&255, (icolor>>16)&255);
}

