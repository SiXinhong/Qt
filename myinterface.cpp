#include "myobject.h"
#include "myinterface.h";
#include "cvutil.h"
#include "show_sdk.h"


#include <QString>
#include <QImage>
#include <QRect>
#include <iostream>
#include<QDebug>

//OpenCV头文件
#include <vector>
#include <highgui.h>
#include <cv.h>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <QtGlobal>
#include <QTime>
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

    //从金老师得来的图片
    f0 = "./s/0.bmp";
    f1 = "./s/1.bmp";
    f2 = "./s/2.bmp";
    f3 = "./s/3.bmp";
    f4 = "./s/4.bmp";
    f5 = "./s/5.bmp";
    f6 = "./s/6.bmp";
    f7 = "./s/7.bmp";
    f8 = "./s/8.bmp";
    f9 = "./s/9.bmp";
    f10 = "./s/10.bmp";
    f11 = "./s/11.bmp";
    f12 = "./s/12.bmp";

    vc.push_back(f0);
    vc.push_back(f1);
    vc.push_back(f2);
    vc.push_back(f3);
    vc.push_back(f4);
    vc.push_back(f5);
    vc.push_back(f6);
    vc.push_back(f7);
    vc.push_back(f8);
    vc.push_back(f9);
    vc.push_back(f10);
    vc.push_back(f11);
    vc.push_back(f12);


    index1=0;//用于取第一栏的图片
    index2=0;//用于取第二栏的图片

    indexx = 0;
    indexy = 0;

    this->hd = "./0.png";
    this->ld = "./0.png";

    MyObject mo1 = MyObject();
    //int x1 = this->panoImage.cols-150;
    int x1=500;//为了不让x小于0
    int y1 = 10;
    int w = 30;
    int h = 30;

    mo1.setRect(Rect(x1,y1,w,h));
    mo1.setCenPoint(Point(x1+w/2, y1+h/2));
    mo1.setID(12345);
    MyObject mo2 = MyObject();
    //int x2 = this->panoImage.cols-200;
    int x2=300;
    int y2 = 30;
    mo2.setRect(Rect(x2,y2,w,h));
    mo2.setCenPoint(Point(x2+w/2, y2+h/2));


    mo2.setID(12346);
    MyObject mo3 = MyObject();
    mo3.setID(12348);
    //int x3 = this->panoImage.cols-300;
    int x3=100;
    int y3 = 40;

    mo3.setRect(Rect(x3,y3,w,h));
    mo3.setCenPoint(Point(x3+w/2, y3+h/2));
    objs.push_back(mo1);
    objs.push_back(mo2);
    objs.push_back(mo3);
    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
    sizeOfobjs=qrand()%10;
    if(sizeOfobjs==0)
        sizeOfobjs=1;
}

void MyInterface::fillObjs(){
    if(sizeOfobjs == 3 || sizeOfobjs == 0)
        return;
    while(objs.size()>sizeOfobjs)
        objs.pop_back();

    while(objs.size()<sizeOfobjs){
        MyObject mo1 = objs.back();
        Rect r=mo1.getRect();
        int w=r.width;
        int h=r.height;
        int x=qrand()%this->panoImage.cols;
        int y=qrand()%this->panoImage.rows;
        mo1.setRect(Rect(x,y,w,h));
        mo1.setCenPoint(Point(x+w/2, y+h/2));
        mo1.setID(mo1.getID()+1);
        objs.push_back(mo1);
    }
}

vector<MyObjectTrack> MyInterface::getTracks(){
    return this->tracks;
}

vector<MyObjectTrack> MyInterface::getTracks1(){
    return this->tracks1;
}

vector<MyObjectTrack> MyInterface::getTracks2(){
    return this->tracks2;
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

int MyInterface::getIntegratedData2(){
    index1++;
    QString qj = vc[(index1)%13];

    this->panoImage = imread(qj.toStdString());
    //    Mat mat = this->panoImage;
    //    Size dsize ;
    //    double scale = 1;
    //    dsize = Size(mat.cols*scale,mat.rows*scale);
    //    Mat image11 = Mat(dsize,CV_32S);
    //    cv::resize(mat, image11,dsize);

    //    QImage img = QImage((const unsigned char*)(image11.data),image11.cols,image11.rows, image11.cols*image11.channels(),  QImage::Format_RGB888);
    //    QImage aa=(&img)->copy(QRect(0,0,mat.cols/2,mat.rows));
    //    Mat image4 = CVUtil::QImageToMat(aa);
    //    Mat image44 = Mat(dsize,CV_32S);
    //    cv::resize(image4, image44,dsize);
    //    this->qj1mat = image44;

    //    //全景2Mat
    //    QImage aa2=(&img)->copy(QRect(mat.cols/2,0,mat.cols/2,mat.rows));
    //    Mat image5 = CVUtil::QImageToMat(aa2);
    //    Mat image55 = Mat(dsize,CV_32S);
    //    cv::resize(image5, image55,dsize);
    //    this->qj2mat = image55;
}

//获得综合数据
int MyInterface::getIntegratedData(){
    IntegratedData  *data = new IntegratedData;
    int isfail_getdata = GetSurveillanceData(0, data);//获取周试图
    isfail_getdata = isfail_getdata&GetSurveillanceData(1, data);//获取周试图
    if (isfail_getdata == 0)
    {
        if (!data->panoImage.empty())
        {
            //                cv::imshow("pano", data->panoImage);
            //                cv::waitKey(10);
            this->timett = data->time;
            cv::Mat pano_temp=cv::Mat(data->panoImage.rows,data->panoImage.cols,CV_8UC3);
            vector<cv::Mat> v_mat(3);
            cv::split(pano_temp,v_mat);
            v_mat[0]=data->panoImage.clone();
            v_mat[1]=data->panoImage.clone();
            v_mat[2]=data->panoImage.clone();
            cv::merge(v_mat,pano_temp);
            //cv::imshow(pano_image);
            data->panoImage=pano_temp;

            this->panoImage = data->panoImage;
            //std::cout<<panoImage.channels()<<std::endl;
            //                //下面将整个的图像切成两幅
            //                //全景1Mat
            //                Mat mat = this->panoImage;
            //                Size dsize ;
            //                double scale = 1;
            //                dsize = Size(mat.cols*scale,mat.rows*scale);
            //                Mat image11 = Mat(dsize,CV_32S);
            //                cv::resize(mat, image11,dsize);
            //                //std::cout<<"resize 1"<<std::endl;
            //                 //std::cout<<"image1"<<image11.empty()<<std::endl;

            //                QImage img = QImage((const unsigned char*)(image11.data),image11.cols,image11.rows, image11.cols*image11.channels(),  QImage::Format_RGB888);
            //                //QImage img = QImage((const unsigned char*)(image11.data),image11.cols,image11.rows, image11.cols*image11.channels(),  QImage::Format_Indexed8);

            //                //std::cout<<"img "<<img.height()<<std::endl;
            //                QImage aa=(&img)->copy(QRect(0,0,mat.cols/2,mat.rows));
            //                //std::cout<<"aa "<<aa.height()<<std::endl;
            //                Mat image4 = CVUtil::QImageToMat(aa);
            //                Mat image44 = Mat(dsize,CV_32S);
            //               // std::cout<<"image1"<<image4.empty()<<std::endl;
            //                //std::cout<<"4 "<<image44.empty()<<std::endl;
            //                //std::cout<<dsize.height<<std::endl;
            //                cv::resize(image4, image44,dsize);
            //                // std::cout<<"resize 2"<<std::endl;
            //                this->qj1mat = image44;

            //                //this->qj1mat = mat;
            //                //全景2Mat
            //                //mat = this->panoImage;
            //                //dsize ;
            //                //double scale = 1;
            //                //dsize = Size(mat.cols*scale,mat.rows*scale);
            //                //Mat image12 = Mat(dsize,CV_32S);
            //                //cv::resize(mat, image12,dsize);
            //                //QImage img2 = QImage((const unsigned char*)(image12.data),image12.cols,mat.rows, image12.cols*image12.channels(),  QImage::Format_RGB888);

            //                QImage aa2=(&img)->copy(QRect(mat.cols/2,0,mat.cols/2,mat.rows));
            //                Mat image5 = CVUtil::QImageToMat(aa2);
            //                Mat image55 = Mat(dsize,CV_32S);
            //                cv::resize(image5, image55,dsize);
            //                //std::cout<<"resize 3"<<std::endl;
            //                this->qj2mat = image55;
            //this->qj2mat = mat;


            //下面完成每个目标的构造
            //this->objs.clear();
            this->objs1.clear();
            this->objs2.clear();
            this->targets = data->targets;
            //qDebug()<<QString("target:");
            //qDebug()<<data->targets.size();
            int count = this->targets.size();
            for (int i = 0; i < count;i++)
            {
                SmallTarget tar = targets[i];
                //先判断目标是不是已经存在
                boolean isObjExisted = false;
                MyObject obj;
                for(int i = 0; i < this->objs.size(); i++){
                    obj = objs[i];
                    if(obj.getID() == tar.id){
                        isObjExisted = true;
                    }
                }

                if(!isObjExisted){
                    obj = MyObject();
                }


                obj.setID(tar.id);
                obj.setCenPoint(tar.cenPointACS);
                obj.setBlockSize(tar.blocksize);
                obj.setVelocity(tar.Velocity);
                obj.setMotionDerection(tar.MotionDerection);
                obj.setAbsoluteIntensity(tar.area);
                obj.setHorizontalAxisLength(tar.horizontalAxisLength);
                obj.setVerticalAxisLength(tar.verticalAxisLength);
                obj.setAbsoluteIntensity(tar.absoluteIntensity);
                obj.setRelativeIntensity(tar.relativeIntensity);
                obj.setContours(tar.contours);
                obj.setSnapshoot(tar.Snapshoot);
                obj.setSihouette(tar.sihouette);
                obj.setTargetScale(tar.targetScale);
                obj.setCenSueEintensity(tar.CenSueEintensity);
                obj.setSCRValue(tar.SCRValue);
                obj.setTheFeatures(tar.theFeatures);
                //设置矩形框
                obj.setRect(Rect(obj.getCenPoint().x-obj.getBlockSize().width/2,obj.getCenPoint().y-obj.getBlockSize().height/2,obj.getBlockSize().width,obj.getBlockSize().height));
                if(!isObjExisted){
                    this->objs.push_back(obj);
                }



                //设置轨迹
                boolean isExisted = false;
                for(int i = 0; i < this->tracks.size(); i++){
                    MyObjectTrack track = tracks[i];
                    if(obj.getID() == track.getId()){
                        vector<Point> ps = track.getTrack();
                        ps.push_back(obj.getCenPoint());
                        track.setTrack(ps);
                        isExisted = true;
                    }
                }

                if(!isExisted){
                    MyObjectTrack track1 = MyObjectTrack();
                    track1.setId(obj.getID());
                    vector<Point> ps = track1.getTrack();
                    ps.push_back(obj.getCenPoint());
                    track1.setTrack(ps);
                    tracks.push_back(track1);
                }

                if(obj.getCenPoint().y<this->panoImage.cols/2){
                    this->objs1.push_back(obj);
                    //设置轨迹
                    boolean isExisted1 = false;
                    for(int i = 0; i < this->tracks1.size(); i++){
                        MyObjectTrack track2 = tracks1[i];
                        if(obj.getID() == track2.getId()){
                            vector<Point> ps = track2.getTrack();
                            ps.push_back(obj.getCenPoint());
                            track2.setTrack(ps);
                            isExisted1 = true;
                        }
                    }

                    if(!isExisted1){
                        MyObjectTrack track3 = MyObjectTrack();
                        track3.setId(obj.getID());
                        vector<Point> ps = track3.getTrack();
                        ps.push_back(obj.getCenPoint());
                        track3.setTrack(ps);
                        tracks1.push_back(track3);
                    }
                }
                else{
                    this->objs2.push_back(obj);
                    //设置轨迹
                    boolean isExisted2 = false;
                    for(int i = 0; i < this->tracks2.size(); i++){
                        MyObjectTrack track4 = tracks2[i];
                        if(obj.getID() == track4.getId()){
                            vector<Point> ps = track4.getTrack();
                            ps.push_back(obj.getCenPoint());
                            track4.setTrack(ps);
                            isExisted2 = true;
                        }
                    }

                    if(!isExisted2){
                        MyObjectTrack track5 = MyObjectTrack();
                        track5.setId(obj.getID());
                        vector<Point> ps = track5.getTrack();
                        ps.push_back(obj.getCenPoint());
                        track5.setTrack(ps);
                        tracks2.push_back(track5);
                    }
                }
            }

            cv::waitKey(0);
        }
        //qDebug() << "Success to get data" << endl;

    }
    else
    {
        //qDebug()<< "fail to get data" << endl;
    }
    delete data;
    return isfail_getdata;
}

////设置系统参数
//int MyInterface::SetSysPara(int mode, const char *para_string, int id){
//    //return SetSystemPara(mode,para_string,id);
//}

////获得系统参数
//int MyInterface::GetSysPara(int mode, char *para_string, int id){
//    //return GetSystemPara(mode,para_string,id);
//}

//随机生成3个对象
vector<MyObject> MyInterface::getObjs2(){
    if(1){
        return getRandomObjs();
    }

    indexx++;
    indexy++;
    const float y_increace_ratio=1.2;
    //    if(100+index*5 >= this->panoImage.cols/2){
    //        index = 0;
    //    }
    //    else if (100+index*2 >= this->panoImage.rows){
    //        index = 0;
    //    }

    MyObject mo1 = (MyObject)objs[0];
    MyObject mo2 = (MyObject)objs[1];
    MyObject mo3 = (MyObject)objs[2];
    int x1=mo1.getRect().x;// = this->panoImage.cols-150+indexx*15;
    int y1=mo1.getRect().y;// = 10+indexy*2;
    int w = 30;
    int h = 30;
    x1 = x1+indexx*5;
    //y1 = y1+indexy*2;
    y1*=y_increace_ratio;
    if(x1+mo1.getRect().width >= this->panoImage.cols){
        indexx = 0;
        x1 = 500;////////

    }
    if(y1+mo1.getRect().height>= this->panoImage.rows){
        indexy = 0;
        y1 = 10;
    }

    mo1.setRect(Rect(x1,y1,w,h));
    mo1.setCenPoint(Point(x1+w/2, y1+h/2));
    //    mo1.getRect().x = x1;
    //    mo1.getRect().y =  y1;
    //    mo1.getRect().width =  w;
    //    mo1.getRect().height = h;
    //    mo1.getCenPoint().x = (x1+w/2);
    //    mo1.getCenPoint().y = (y1+h/2);


    int x2=mo2.getRect().x;// = this->panoImage.cols-200+indexx*20;
    int y2=mo2.getRect().y;// = 30+indexy*2;
    x2 = x2+indexx*5;
    //y2 = y2+indexy*2;
    y2*=y_increace_ratio;
    //这里x和y跟长度和宽度比较，但是下面mo2.setCenPoint(Point(x2+w/2, y2+h/2))
    //设置的时候又给加上了w/2和h/2，导致会超出界限，让其比较时加上了mo2.getRect().width
    if(x2+mo2.getRect().width >= this->panoImage.cols){
        indexx = 0;
        x2 = 300;

    }
    if(y2+mo2.getRect().height>= this->panoImage.rows){
        indexy = 0;
        y2 = 30;
    }


    //    mo2.getRect().x = x2;
    //    mo2.getRect().y = y2;
    //    mo2.getRect().width = w;
    //    mo2.getRect().height =h;
    //    mo2.getCenPoint().x = x2+w/2;
    //    mo2.getCenPoint().y = y2+h/2;
    mo2.setRect(Rect(x2,y2,w,h));
    mo2.setCenPoint(Point(x2+w/2, y2+h/2));

    int x3=mo3.getRect().x;// = this->panoImage.cols-300+indexx*25;
    int y3=mo3.getRect().y;// = 100+indexy*2;
    x3 = x3+indexx*5;
    //y3 = y3+indexy*2;
    y3*=y_increace_ratio;
    if(x3+mo3.getRect().width >= this->panoImage.cols){
        indexx = 0;
        x3 = 100;

    }
    if(y3+mo3.getRect().height>= this->panoImage.rows){
        indexy = 0;
        y3 = 40;
    }
    if(x1<x3){
        x2=300;
        x3=100;
    }
    //    mo3.getRect().x = x3;
    //    mo3.getRect().y = y3;
    //    mo3.getRect().width = w;
    //    mo3.getRect().height =h;
    //    mo3.getCenPoint().x = x3+w/2;
    //    mo3.getCenPoint().y = y3+h/2;
    mo3.setRect(Rect(x3,y3,w,h));
    mo3.setCenPoint(Point(x3+w/2, y3+h/2));

    //设置轨迹
    boolean isExisted = false;
    for(int i = 0; i < this->tracks.size(); i++){
        MyObjectTrack track = tracks[i];
        if(mo1.getID() == track.getId()){
            vector<Point> ps = track.getTrack();
            ps.push_back(mo1.getCenPoint());
            track.setTrack(ps);
            isExisted = true;
        }
    }

    if(!isExisted){
        MyObjectTrack track1 = MyObjectTrack();
        track1.setId(mo1.getID());
        vector<Point> ps = track1.getTrack();
        ps.push_back(mo1.getCenPoint());
        track1.setTrack(ps);
        tracks.push_back(track1);
    }



    isExisted = false;
    for(int i = 0; i < this->tracks.size(); i++){
        MyObjectTrack track = tracks[i];
        if(mo2.getID() == track.getId()){
            vector<Point> ps = track.getTrack();
            ps.push_back(mo2.getCenPoint());
            track.setTrack(ps);
            isExisted = true;
        }
    }

    if(!isExisted){
        MyObjectTrack track1 = MyObjectTrack();
        track1.setId(mo2.getID());
        vector<Point> ps = track1.getTrack();
        ps.push_back(mo2.getCenPoint());
        track1.setTrack(ps);
        tracks.push_back(track1);
    }



    isExisted = false;
    for(int i = 0; i < this->tracks.size(); i++){
        MyObjectTrack track = tracks[i];
        if(mo3.getID() == track.getId()){
            vector<Point> ps = track.getTrack();
            ps.push_back(mo3.getCenPoint());
            track.setTrack(ps);
            isExisted = true;
        }
    }

    if(!isExisted){
        MyObjectTrack track1 = MyObjectTrack();
        track1.setId(mo3.getID());
        vector<Point> ps = track1.getTrack();
        ps.push_back(mo3.getCenPoint());
        track1.setTrack(ps);
        tracks.push_back(track1);
    }

    //vector<MyObject> vc;
    objs.clear();
    objs.push_back(mo1);
    objs.push_back(mo2);
    objs.push_back(mo3);

    return objs;
}

void MyInterface::setObjs(vector<MyObject> os){
    this->objs = os;
}
//生成随机个对象
vector<MyObject> MyInterface::getRandomObjs(){
    if(this->panoImage.cols==0)
        return objs;
    if(sizeOfobjs!=objs.size())
        fillObjs();
    this->panoImage.cols;
    int indexx=10;
    const float y_increace_ratio=1.2;
    for(int idx=0;idx<objs.size();idx++){
        MyObject mo1 = (MyObject)objs[idx];
        int x1=mo1.getRect().x;
        int y1=mo1.getRect().y;
        int w = 30;
        int h = 30;
        x1 = x1+indexx*5;
        y1*=y_increace_ratio;
        if(x1+mo1.getRect().width >= this->panoImage.cols){
            x1 = x1 % this->panoImage.cols;

        }
        if(y1+mo1.getRect().height>= this->panoImage.rows){
            y1 = y1 % panoImage.rows;
        }

        mo1.setRect(Rect(x1,y1,w,h));
        mo1.setCenPoint(Point(x1+w/2, y1+h/2));
        //设置轨迹
        boolean isExisted = false;
        for(int i = 0; i < this->tracks.size(); i++){
            MyObjectTrack track = tracks[i];
            if(mo1.getID() == track.getId()){
                vector<Point> ps = track.getTrack();
                ps.push_back(mo1.getCenPoint());
                track.setTrack(ps);
                tracks[i]=track;
                isExisted = true;
                //qDebug()<<"tracks"<<mo1.getID()<<":"<<track.getTrack().size();
            }
        }
        if(!isExisted){
            MyObjectTrack track1 = MyObjectTrack();
            track1.setId(mo1.getID());
            vector<Point> ps = track1.getTrack();
            ps.push_back(mo1.getCenPoint());
            track1.setTrack(ps);
            tracks.push_back(track1);
        }


        objs[idx]=mo1;
    }
    return objs;
}
