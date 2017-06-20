#include "zwidget.h"
#include "mainwindow.h"
#include "myobject.h"

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
    for(int i = 0; i < this->objs.size(); i++){
        MyObject obj = this->objs[i];
        if(obj.getRect().x<r.x){
            rr.width = r.width + r.x - obj.getRect().x + 5;
            rr.x = obj.getRect().x - 5;
        }
        if(obj.getRect().y<r.y){
            rr.height = r.height + r.y - obj.getRect().y + 5;
            rr.y = obj.getRect().y - 5;
        }
        if(obj.getRect().x+obj.getRect().width>r.x){
            rr.width = r.width + obj.getRect().x + obj.getRect().width - r.x + 5;
            rr.x = obj.getRect().x +obj.getRect().width + 5;
        }
        if(obj.getRect().y+obj.getRect().height>r.y){
            rr.height = r.height + obj.getRect().y + obj.getRect().height- r.y+ 5;
            rr.y = obj.getRect().y +obj.getRect().height+ 5;
        }
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
    qDebug()<<this->getFrom();
    //根据矩形框的变化，重新从全景显示区1或者全景显示区2拷贝获得mat。
    if(this->getFrom() == 1){
        Rect r1;
        r1.x = mw->widget1->rectan.x;
        r1.y = mw->widget1->rectan.y;
        r1.width = mw->widget1->rectan.width;
        r1.height = mw->widget1->rectan.height;
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
        mw->paintScale(mat, mw->widget1->getDirectionX(), mw->widget1->getDirectionY());
    }
    else if(this->from == 2){
        mw->paintScale(mat, mw->widget2->getDirectionX(), mw->widget2->getDirectionY());
    }
    else{
        mw->paintScale(mat, mw->widget1->getDirectionX(), mw->widget1->getDirectionY());
    }

    cv::cvtColor(mat,mat,CV_BGR2RGB);

    mw->imgLabel3 = mw->MatToQImage(mat,mw->imgLabel3);

    mw->loadPictureToLabel3();

}
