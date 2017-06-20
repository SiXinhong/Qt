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
    int icolor = (unsigned) RNG((int)time(0));
    return Scalar(icolor&255, (icolor>>8)&255, (icolor>>16)&255);
}

cv::Mat CVUtil::QImageToMat(QImage image)
{
    cv::Mat mat;
    switch (image.format())
    {
    case QImage::Format_ARGB32:
    case QImage::Format_RGB32:
    case QImage::Format_ARGB32_Premultiplied:
        mat = cv::Mat(image.height(), image.width(), CV_8UC4, (void*)image.constBits(), image.bytesPerLine());
        break;
    case QImage::Format_RGB888:
        mat = cv::Mat(image.height(), image.width(), CV_8UC3, (void*)image.constBits(), image.bytesPerLine());
        cv::cvtColor(mat, mat, CV_BGR2RGB);
        break;
    case QImage::Format_Indexed8:
        mat = cv::Mat(image.height(), image.width(), CV_8UC1, (void*)image.constBits(), image.bytesPerLine());
        break;
    default:
        break;
    }

    return mat;
}

QImage CVUtil::MatToQImage(const cv::Mat& mat, QImage imgLabel)
{
    // 8-bits unsigned, NO. OF CHANNELS = 1
    if(mat.type() == CV_8UC1)
    {
        //QImage image(mat.cols, mat.rows, QImage::Format_Indexed8);
        imgLabel = QImage(mat.cols, mat.rows, QImage::Format_Indexed8);
        // Set the color table (used to translate colour indexes to qRgb values)
        imgLabel.setColorCount(256);
        for(int i = 0; i < 256; i++)
        {
            //image.setColor(i, qRgb(i, i, i));
            imgLabel.setColor(i, qRgb(i, i, i));
        }
        // Copy input Mat
        uchar *pSrc = mat.data;
        for(int row = 0; row < mat.rows; row ++)
        {
            //uchar *pDest = image.scanLine(row);
            uchar *pDest = imgLabel.scanLine(row);
            memcpy(pDest, pSrc, mat.cols);
            pSrc += mat.step;
        }
        //return image;
        return imgLabel;
    }
    // 8-bits unsigned, NO. OF CHANNELS = 3
    else if(mat.type() == CV_8UC3)
    {
        // Copy input Mat
        const uchar *pSrc = (const uchar*)mat.data;
        // Create QImage with same dimensions as input Mat
        //QImage image(pSrc, mat.cols, mat.rows, mat.step, QImage::Format_RGB888);
        imgLabel = QImage(pSrc, mat.cols, mat.rows, mat.step, QImage::Format_RGB888);
        return imgLabel.rgbSwapped();
    }
    else if(mat.type() == CV_8UC4)
    {
        //qDebug() << "CV_8UC4";
        // Copy input Mat
        const uchar *pSrc = (const uchar*)mat.data;
        // Create QImage with same dimensions as input Mat
        //QImage image(pSrc, mat.cols, mat.rows, mat.step, QImage::Format_ARGB32);
        imgLabel = QImage(pSrc, mat.cols, mat.rows, mat.step, QImage::Format_ARGB32);
        return imgLabel.copy();
    }
    else
    {
        //qDebug() << "ERROR: Mat could not be converted to QImage.";
        return imgLabel;
    }
}
