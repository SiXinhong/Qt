#include "zwidget.h"
#include "mainwindow.h"
#include "myobject.h"
#include "cvutil.h"

using namespace cv;
using namespace std;

ZWidget::ZWidget(QWidget *parent) :
    QWidget(parent){

    this->from = 0;

}

void ZWidget::setMat(Mat m){
    mat = m;
}

Mat ZWidget::getMat(){
    return mat;
}

void ZWidget::setFrom(int f){
    this->from = f;
}

int ZWidget::getFrom(){
    return this->from;
}

//实现目标的跟踪，因为不同的目标的运动速度不同，所以原先设定的选择框需要动态调整
Rect ZWidget::getRectFromObjs(Rect r){
    Rect rr;
    rr.x = r.x;
    rr.y = r.y;
    rr.width = r.width;
    rr.height = r.height;
//    for(int i = 0; i < this->objs.size(); i++){
//        MyObject obj = this->objs[i];
//        if(obj.getRect().x<r.x){
//            rr.x = obj.getRect().x - 5;
//            rr.width += r.x - obj.getRect().x + 5;
//        }
//        if(obj.getRect().y<r.y){
//            rr.y = obj.getRect().y - 5;
//            rr.height += r.y - obj.getRect().y + 5;
//        }
//        if((obj.getRect().x+obj.getRect().width)>(r.x+r.width)){
//            rr.width = obj.getRect().x + obj.getRect().width - r.x + 5;
//            //rr.x = obj.getRect().x +obj.getRect().width + 5;
//        }
//        if((obj.getRect().y+obj.getRect().height)>(r.y+r.height)){
//            rr.height = obj.getRect().y + obj.getRect().height- r.y+ 5;
//            //rr.y = obj.getRect().y +obj.getRect().height+ 5;
//        }
//    }
    MainWindow *mw = (MainWindow*)parentWidget()->parentWidget();

    //找出对象集合中最左边的点，和最右边的点，就是x的最小点和最大点
    //先找最小点
    double xtemp1;
    double ytemp1;
    if(this->getFrom() == 1){
       xtemp1 = mw->widget1->getMat().cols;
       ytemp1 = mw->widget1->getMat().rows;
    }
    else if(this->getFrom() == 2){
        xtemp1 = mw->widget2->getMat().cols;
        ytemp1 = mw->widget2->getMat().rows;
    }
    //初始的时候不做处理
    else{

        return rr;
    }
    //再找最大点
    double xtemp2 = 0;
    double ytemp2 = 0;

    int count = objs.size();

    qDebug()<<count;

    for(int i = 0; i < count; i++){
        MyObject obj = objs[i];
        if(xtemp1 > obj.getRect().x){
            xtemp1 = obj.getRect().x;
            ytemp1 = obj.getRect().y;
        }
        if(xtemp2 < (obj.getRect().x + obj.getRect().width)){
            xtemp2 = obj.getRect().x + obj.getRect().width;
            ytemp2 = obj.getRect().y + obj.getRect().height;
        }
    }
    if (count > 0){
//    if(rr.x < xtemp1-50){

//    }
//    else{
        if(xtemp1-50>0){
            rr.x = xtemp1-50;
        }
        else{
            rr.x = xtemp1;
        }
//    }
//    if(rr.y < ytemp1-50){

//    }
//    else{
        if(ytemp1-20 > 0){
            rr.y = ytemp1-20;
        }
        else{
            rr.y = ytemp1;
        }
//    }
//    if(rr.width > (xtemp2-rr.x+100)){

//    }
//    else{
        if(xtemp1-50 > 0){
            rr.width = xtemp2-rr.x+100;
        }
        else{
            rr.width = xtemp2-rr.x;
        }
//    }
//    if(rr.height > (ytemp2-rr.y+100)){

//    }
//    else{
        if(ytemp1-20 > 0){
            rr.height = ytemp2-rr.y+40;
        }
        else{
            rr.height = ytemp2-rr.y;
        }
//    }
//        qDebug()<<xtemp1;
//        qDebug()<<ytemp1;
//        qDebug()<<xtemp2;
//        qDebug()<<ytemp2;
   }
    if(mw->isMubiao){
        rr.width += 100;
    }
   return rr;
}

void ZWidget::setObjects(vector<MyObject> os){
    this->objs = os;
}

vector<MyObject> ZWidget::getObjects(){
    return this->objs;
}

void ZWidget::draw(){
    MainWindow *mw = (MainWindow*)parentWidget()->parentWidget();
    //qDebug()<<this->getFrom();
    //根据矩形框的变化，重新从全景显示区1或者全景显示区2拷贝获得mat。
    if(this->getFrom() == 1){
        Rect r1;
        r1.x = mw->widget1->rectan.x;
        r1.y = mw->widget1->rectan.y;
        r1.width = mw->widget1->rectan.width;
        r1.height = mw->widget1->rectan.height;
        this->objs = mw->widget1->getSelectedObjects();
        Rect r2 = this->getRectFromObjs(r1);
        mw->widget1->rectan.x = r2.x;
        mw->widget1->rectan.y = r2.y;
        mw->widget1->rectan.width = r2.width;
        mw->widget1->rectan.height = r2.height;
        Mat mat1 = mw->widget1->getMat();
        Size dsize ;
        double scale = 1;
        dsize = Size(mat1.cols*scale,mat1.rows*scale);
        Mat image11 = Mat(dsize,CV_32S);
        cv::resize(mat1, image11,dsize);
        mw->img = QImage((const unsigned char*)(image11.data),image11.cols,mat1.rows, image11.cols*image11.channels(),  QImage::Format_RGB888);

        //vector<Rectan> rectans;
        mw->aa=(&(mw->img))->copy(mw->widget1->getQRectan());
        Mat image3 = mw->QImageToMat(mw->aa);
        Mat image33 = Mat(dsize,CV_32S);
        cv::resize(image3, image33,dsize);
        setMat(image33);
    }
    else if(this->getFrom() == 2){
        Rect r1;
        r1.x = mw->widget2->rectan.x;
        r1.y = mw->widget2->rectan.y;
        r1.width = mw->widget2->rectan.width;
        r1.height = mw->widget2->rectan.height;
        this->objs = mw->widget2->getSelectedObjects();

        Rect r2 = this->getRectFromObjs(r1);
        mw->widget2->rectan.x = r2.x;
        mw->widget2->rectan.y = r2.y;
        mw->widget2->rectan.width = r2.width;
        mw->widget2->rectan.height = r2.height;
        Mat mat2 = mw->widget2->getMat();
        Size dsize ;
        double scale = 1;
        dsize = Size(mat2.cols*scale,mat2.rows*scale);
        Mat image11 = Mat(dsize,CV_32S);
        cv::resize(mat2, image11,dsize);
        mw->img = QImage((const unsigned char*)(image11.data),image11.cols,mat2.rows, image11.cols*image11.channels(),  QImage::Format_RGB888);

        //vector<Rectan> rectans;
        mw->aa=(&(mw->img))->copy(mw->widget2->getQRectan());
        Mat image3 = mw->QImageToMat(mw->aa);
        Mat image33 = Mat(dsize,CV_32S);
        cv::resize(image3, image33,dsize);
        setMat(image33);
    }
    else{//初始的时候，切全景显示区1中的一段固定区域
//        Rect r1;
//        r1.x = mw->widget1->rectan.x;
//        r1.y = mw->widget1->rectan.y;
//        r1.width = mw->widget1->rectan.width;
//        r1.height = mw->widget1->rectan.height;
//        Rect r2 = this->getRectFromObjs(r1);
//        mw->widget1->rectan.x = r2.x;
//        mw->widget1->rectan.y = r2.y;
//        mw->widget1->rectan.width = r2.width;
//        mw->widget1->rectan.height = r2.height;
        Mat mat1 = mw->widget1->getMat();
        Size dsize ;
        double scale = 1;
        dsize = Size(mat1.cols*scale,mat1.rows*scale);
        Mat image11 = Mat(dsize,CV_32S);
        cv::resize(mat1, image11,dsize);
        mw->img = QImage((const unsigned char*)(image11.data),image11.cols,mat1.rows, image11.cols*image11.channels(),  QImage::Format_RGB888);

        //vector<Rectan> rectans;
        mw->aa=(&(mw->img))->copy(QRect(1490,250,100,100));
        Mat image3 = mw->QImageToMat(mw->aa);
        Mat image33 = Mat(dsize,CV_32S);
        cv::resize(image3, image33,dsize);
        setMat(image33);
    }

//    int count = objs.size();
//    for (int i = 0; i < count;i++)
//    {
//        Rect rect = objs[i].getRect();
//        Scalar color = objs[i].getColor();
//        rectangle(mat,rect,color,2,1,0);
//        cv::cvtColor(mat, mat, CV_BGR2RGB);
//    }
//    mw->paintScale(mat, 1.0, 1.0);
    if(this->from == 1){
        CVUtil::paintScale(mat, mw->widget1->getDirectionX(), mw->widget1->getDirectionY(), mw->widget1->getDirectionX2(), mw->widget1->getDirectionY2());
    }
    else if(this->from == 2){
        CVUtil::paintScale(mat, mw->widget2->getDirectionX(), mw->widget2->getDirectionY(), mw->widget2->getDirectionX2(), mw->widget2->getDirectionY2());
    }
    else{
        CVUtil::paintScale(mat, mw->widget1->getDirectionX(), mw->widget1->getDirectionY(), mw->widget1->getDirectionX2(), mw->widget1->getDirectionY2());
    }

    cv::cvtColor(mat,mat,CV_BGR2RGB);

    mw->imgLabel3 = mw->MatToQImage(mat,mw->imgLabel3);

    mw->loadPictureToLabel3();

}
