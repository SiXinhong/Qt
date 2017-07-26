#include "cvutil.h"

//OpenCV头文件
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
//    int icolor = (unsigned) RNG((int)time(NULL));
//    return Scalar(icolor&255, (icolor>>8)&255, (icolor>>16)&255);

    cv::RNG rng(cvGetTickCount());
    return Scalar(rng.uniform(0,255),rng.uniform(0,255),rng.uniform(0,255));
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

//画标尺
void CVUtil::paintScale(Mat image,double startw,double starth, double endw, double endh)
{
    //QImage img;
    int c = image.cols/30;
    int r = image.rows/10;
    line(image,Point(0,0),Point(image.cols,0),Scalar(255,255,255),2,8,0);
    for(int t=startw; t<=startw+30; t++)
    {
     int i=t-startw;
     if(i%2 == 0){
        line(image,Point(i*c,0),Point(i*c,12),Scalar(255,255,255),2,8,0);
        //标尺上写字
        int ii = (int)(startw+i*(endw-startw)/30);
        if(ii > 270){
            ii = ii -360;
        }
        QString text = QString::number(ii,10);
        string str = text.toStdString();
        putText(image,str,Point(i*c-10,25),3,0.75,Scalar(255,255,255));
     }
     else{
         line(image,Point(i*c,0),Point(i*c,8),Scalar(255,255,255),2,8,0);
     }
    }
    line(image,Point(0,0),Point(0,image.rows),Scalar(255,255,255),2,8,0);
    for(int t=starth; t<=starth+10; t++)
    {
        int i=t-starth;
        if(i%2 == 0){
            line(image,Point(0,i*r),Point(12,i*r),Scalar(255,255,255),2,8,0);
            int ii = (int)(endh - i*(endh-starth)/10);
            QString text2 = QString::number(ii,10);
            string str2 = text2.toStdString();
            putText(image,str2,Point(20,i*r+10),3,0.75,Scalar(255,255,255));
        }
        else{
            line(image,Point(0,i*r),Point(8,i*r),Scalar(255,255,255),2,8,0);
        }
    }
    //return img;
}
