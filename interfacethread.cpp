#include "interfacethread.h"
#include <QDebug>

InterfaceThread::InterfaceThread()
{
    isOk = false;
    bright_TrackbarValue = 0;
    alpha_contrast = 100;
    isPseudo = false;
}

int InterfaceThread::getIntegratedData(){
    mutex.lock();
    while(!isOk)
    {
        fullCond.wakeAll();
        emptyCond.wait(&mutex);
    }
    isOk = false;
    mutex.unlock();
    return v;
}

void InterfaceThread::run(){
    while(true){
        mutex.lock();
        fullCond.wait(&mutex);
        v = in.getIntegratedData();
        if(0!=v){
            qDebug()<<"interfaceThread getData2"<<currentThreadId();
            v = in.getIntegratedData2();
        }
        //避免函数运行时其他线程修改了值，比如bright，让mat的每一个都更新成同样的亮度
        bool isPseudoTmp = this->isPseudo;
        int bright = this->bright_TrackbarValue;
        int contrast = this->alpha_contrast;

       if(isPseudoTmp==true)
           in.panoImage=setPseudocolor(in.panoImage);
        updateBright(in.panoImage,bright);
        updateContrast(in.panoImage,contrast);
        isOk = true;
        emptyCond.wakeAll();
        mutex.unlock();
    }
}

Mat InterfaceThread::getPano(){
    return in.getPano();
}

vector<MyObject> InterfaceThread::getObjs(){
    return in.getObjs();
}

vector<TrackingPoint> InterfaceThread::GetTps(){
    return in.tps;
}

void InterfaceThread::getNext(){
    mutex.lock();
    fullCond.wakeAll();
    mutex.unlock();
}

Mat InterfaceThread::setPseudocolor(Mat& image){
    Mat img_pseudocolor(image.rows, image.cols, CV_8UC3);

    for (int y = 0; y < image.rows; y++)//转为伪彩色图像的具体算法
    {
        for (int x = 0; x < image.cols; x++)
        {
            int tmp = image.at<unsigned char>(y, x)  ;
            img_pseudocolor.at<Vec3b>(y, x)[0] = abs(255 - tmp); //blue
            img_pseudocolor.at<Vec3b>(y, x)[1] = abs(127 - tmp); //green
            img_pseudocolor.at<Vec3b>(y, x)[2] = abs(0 - tmp); //red
        }
    }
    return img_pseudocolor;
}

void InterfaceThread::updateBright(Mat &mat1,int bright)
{
    if(0 == bright)
        return;
    for (int y = 0; y <mat1.rows; y++)
    {
        for (int x = 0; x < mat1.cols; x++)
        {
            for (int c = 0; c < 3; c++)
            {
                //new_image.at<Vec3b>(y, x)[c] = saturate_cast<uchar>(alpha*(image.at<Vec3b>(y, x)[c]) + beta);
                mat1.at<Vec3b>(y, x)[c] = saturate_cast<uchar>((mat1.at<Vec3b>(y, x)[c]) +  bright);
                if (mat1.at<Vec3b>(y, x)[c] > 255)
                {
                    mat1.at<Vec3b>(y, x)[c] = 255;
                }
            }
        }
    }
}

void InterfaceThread::updateContrast(Mat &mat1,int contrast){
    if(100 == contrast)
        return;

    for (int y = 0; y < mat1.rows; y++)
    {
        for (int x = 0; x < mat1.cols; x++)
        {
            for (int c = 0; c < 3; c++)
            {
                //new_image.at<Vec3b>(y, x)[c] = saturate_cast<uchar>(alpha*(image.at<Vec3b>(y, x)[c]) + beta);
                //new_image.at<Vec3b>(y, x)[c] = saturate_cast<uchar>((image.at<Vec3b>(y, x)[c]) + beta_value);
                mat1.at<Vec3b>(y, x)[c] = saturate_cast<uchar>(0.01*contrast*(mat1.at<Vec3b>(y, x)[c]));

                if (mat1.at<Vec3b>(y, x)[c] > 255)
                {
                    mat1.at<Vec3b>(y, x)[c] = 255;
                }
            }
        }
    }

}
