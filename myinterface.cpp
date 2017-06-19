#include "myobject.h"
#include "myinterface.h";
#include "show_sdk.h"
#include "cvutil.h"


#include <QString>
#include <QImage>
#include <QRect>
#include <iostream>


//OpenCV头文件
#include <vector>
#include <highgui.h>
#include <cv.h>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace cv;
using namespace std;

//#pragma comment(lib,"DisplaySDK.lib")

MyInterface::MyInterface(){
    //存储第一栏
    filename1 = "./s1/1.bmp";
    filename2 = "./s1/2.bmp";
    filename3 = "./s1/3.bmp";
    filename4 = "./s1/4.bmp";
    //存储第二栏
    filename5 = "./s2/1.bmp";
    filename6 = "./s2/2.bmp";
    filename7 = "./s2/3.bmp";
    filename8 = "./s2/4.bmp";
    //将第一栏存储在vector中
    vc1.push_back(filename1);
    vc1.push_back(filename2);
    vc1.push_back(filename3);
    vc1.push_back(filename4);
    //将第二栏存储在vector中
    vc2.push_back(filename5);
    vc2.push_back(filename6);
    vc2.push_back(filename7);
    vc2.push_back(filename8);

    index1=0;//用于取第一栏的图片
    index2=0;//用于取第二栏的图片

    this->hd = "./0.png";
    this->ld = "./0.png";

}


QString MyInterface::getQJ1(){
    index1++;
    qj1 = vc1[(index1)%4];
    return qj1;
}

void MyInterface::setQJ1(QString q1){
    this->qj1 = q1;
}

QString MyInterface::getQJ2(){
    index2++;
    qj2 = vc2[(index2)%4];
    return qj2;
}

void MyInterface::setQJ2(QString q2){
    this->qj2 = q2;
}

QString MyInterface::getHD(){
    return hd;
}

void MyInterface::setHD(QString h){
    this->hd = h;
}

QString MyInterface::getLD(){
    return ld;
}

void MyInterface::setLD(QString l){
    this->ld = l;
}

void MyInterface::SetTime(Time t){
    this->timett = t;
}

Time MyInterface::getTime(){
    return this->timett;
}

void MyInterface::setPano(Mat pano){
    this->panoImage = pano;
}

Mat MyInterface::getPano(){
    return this->panoImage;
}

void MyInterface::setQJ1Mat(Mat qj1){
    this->qj1mat = qj1;
}

Mat MyInterface::getQJ1Mat(){
    return this->qj1mat;
}

void MyInterface::setQJ2Mat(Mat qj2){
    this->qj2mat = qj2;
}

Mat MyInterface::getQJ2Mat(){
    return this->qj2mat;
}

vector<MyObject> MyInterface::getObjs(){
    return this->objs;
}
//获得全景显示区1中的对象
vector<MyObject> MyInterface::getQj1Objs(){
    return this->objs1;
}

//获得全景显示区2中的对象
vector<MyObject> MyInterface::getQj2Objs(){
    return this->objs2;
}


//获得综合数据
void MyInterface::getIntegratedData(){
//    IntegratedData  *data = new IntegratedData;
//        int isfail_getdata = GetSurveillanceData(0, data);//获取周试图
//        if (isfail_getdata == 0)
//        {
//            if (!data->panoImage.empty())
//            {
//                //cv::imshow("pano", data->panoImage);
//                this->timett = data->time;
//                this->panoImage = data->panoImage;
//                //下面将整个的图像切成两幅
//                //全景1Mat
//                Mat mat = this->panoImage;
//                Size dsize ;
//                double scale = 1;
//                dsize = Size(mat.cols*scale/2,mat.rows*scale);
//                Mat image11 = Mat(dsize,CV_32S);
//                cv::resize(mat, image11,dsize);
//                QImage img = QImage((const unsigned char*)(image11.data),image11.cols,mat.rows, image11.cols*image11.channels(),  QImage::Format_RGB888);

//                //vector<Rectan> rectans;
//                QImage aa=(&img)->copy(QRect(1,1,mat.cols/2,mat.rows));
//                Mat image4 = CVUtil::QImageToMat(aa);
//                Mat image44 = Mat(dsize,CV_32S);
//                cv::resize(image4, image44,dsize);
//                this->qj1mat = image44;
//                //全景2Mat
//                mat = this->panoImage;
//                //dsize ;
//                //double scale = 1;
//                dsize = Size(mat.cols*scale/2,mat.rows*scale);
//                image11 = Mat(dsize,CV_32S);
//                cv::resize(mat, image11,dsize);
//                img = QImage((const unsigned char*)(image11.data),image11.cols,mat.rows, image11.cols*image11.channels(),  QImage::Format_RGB888);

//                //vector<Rectan> rectans;
//                aa=(&img)->copy(QRect(mat.cols/2,1,mat.cols,mat.rows));
//                Mat image5 = CVUtil::QImageToMat(aa);
//                Mat image55 = Mat(dsize,CV_32S);
//                cv::resize(image5, image55,dsize);
//                this->qj1mat = image55;


//                //下面完成每个目标的构造
//                this->objs.clear();
//                this->objs1.clear();
//                this->objs2.clear();
//                this->targets = data->targets;
//                int count = this->targets.size();
//                for (int i = 0; i < count;i++)
//                {
//                    MyObject obj = MyObject();
//                    SmallTarget tar = targets[i];
//                    obj.setID(tar.id);
//                    obj.setCenPoint(tar.cenPoint);
//                    obj.setBlockSize(tar.blocksize);
//                    obj.setVelocity(tar.Velocity);
//                    obj.setMotionDerection(tar.MotionDerection);
//                    obj.setAbsoluteIntensity(tar.area);
//                    obj.setHorizontalAxisLength(tar.horizontalAxisLength);
//                    obj.setVerticalAxisLength(tar.verticalAxisLength);
//                    obj.setAbsoluteIntensity(tar.absoluteIntensity);
//                    obj.setRelativeIntensity(tar.relativeIntensity);
//                    obj.setContours(tar.contours);
//                    obj.setSnapshoot(tar.Snapshoot);
//                    obj.setSihouette(tar.sihouette);
//                    obj.setTargetScale(tar.targetScale);
//                    obj.setCenSueEintensity(tar.CenSueEintensity);
//                    obj.setSCRValue(tar.SCRValue);
//                    obj.setTheFeatures(tar.theFeatures);
//                    //设置矩形框
//                    obj.setRect(Rect(obj.getCenPoint().x-obj.getBlockSize().width/2,obj.getCenPoint().y-obj.getBlockSize().height/2,obj.getCenPoint().x+obj.getBlockSize().width/2,obj.getCenPoint().y+obj.getBlockSize().height/2));

//                    this->objs.push_back(obj);
//                    if(obj.getCenPoint().y<this->panoImage.cols/2){
//                        this->objs1.push_back(obj);
//                    }
//                    else{
//                        this->objs2.push_back(obj);
//                    }
//                }

//                cv::waitKey(0);
//            }
//            //qDebug() << "Success to get data" << endl;

//        }
//        else
//        {
//            //qDebug()<< "fail to get data" << endl;
//        }
}

//设置系统参数
//int MyInterface::SetSysPara(int mode, const char *para_string, int id){
//    //return SetSystemPara(mode,para_string,id);
//}

////获得系统参数
//int MyInterface::GetSysPara(int mode, char *para_string, int id){
//    //return GetSystemPara(mode,para_string,id);
//}

//随机生成3个对象
vector<MyObject> MyInterface::getObjs2(){
    int x1 = (unsigned) RNG((int)time(0))&1800;
    int y1 = (unsigned) RNG((int)time(0))&500;
    int w = 100;
    int h = 100;
    MyObject mo1 = MyObject();
    mo1.setRect(Rect(x1,y1,w,h));

    int x2 = (unsigned) RNG((int)time(0))&1800;
    int y2 = (unsigned) RNG((int)time(0))&500;
    MyObject mo2 = MyObject();
    mo2.setRect(Rect(x2,y2,w,h));

    int x3 = (unsigned) RNG((int)time(0))&1800;
    int y3 = (unsigned) RNG((int)time(0))&500;
    MyObject mo3 = MyObject();
    mo3.setRect(Rect(x3,y3,w,h));

    vector<MyObject> vc;
    vc.push_back(mo1);
    vc.push_back(mo2);
    vc.push_back(mo3);

    return vc;
}

void MyInterface::setObjs(vector<MyObject> os){
    this->objs = os;
}
