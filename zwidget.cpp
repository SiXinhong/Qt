#include "zwidget.h"
#include "mainwindow.h"
#include "myobject.h"

using namespace cv;
using namespace std;

ZWidget::ZWidget(QWidget *parent) :
    QWidget(parent){


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
    for(int i = 0; i < this->objs.size(); i++){
        MyObject obj = this->objs[i];
        if(obj.getRect().x<r.x){
            r.width = r.width + r.x - obj.getRect().x + 5;
            r.x = obj.getRect().x - 5;
        }
        if(obj.getRect().y<r.y){
            r.height = r.height + r.y - obj.getRect().y + 5;
            r.y = obj.getRect().y - 5;
        }
        if(obj.getRect().x+obj.getRect().width>r.x){
            r.width = r.width + obj.getRect().x + obj.getRect().width - r.x + 5;
            r.x = obj.getRect().x +obj.getRect().width + 5;
        }
        if(obj.getRect().y+obj.getRect().height>r.y){
            r.height = r.height + obj.getRect().y + obj.getRect().height- r.y+ 5;
            r.y = obj.getRect().y +obj.getRect().height+ 5;
        }
    }
    return r;
}


void ZWidget::setObjects(vector<MyObject> os){
    this->objs = os;
}

vector<MyObject> ZWidget::getObjects(){
    return this->objs;
}

void ZWidget::draw(){
    MainWindow *mw = (MainWindow*)parentWidget()->parentWidget();

    //根据矩形框的变化，重新从全景显示区1或者全景显示区2拷贝获得mat。
    if(this->getFrom() == 1){
        Rect r1 = mw->widget1->rectan;
        Rect r2 = this->getRectFromObjs(r1);
        mw->widget1->rectan = r2;
        Mat mat = mw->widget1->getMat();
        Size dsize ;
        double scale = 1;
        dsize = Size(mat.cols*scale,mat.rows*scale);
        Mat image11 = Mat(dsize,CV_32S);
        cv::resize(mat, image11,dsize);
        mw->img = QImage((const unsigned char*)(image11.data),image11.cols,mat.rows, image11.cols*image11.channels(),  QImage::Format_RGB888);

        //vector<Rectan> rectans;
        mw->aa=(&(mw->img))->copy(mw->widget1->getQRectan());
        Mat image3 = mw->QImageToMat(mw->aa);
        Mat image33 = Mat(dsize,CV_32S);
        cv::resize(image3, image33,dsize);
        setMat(image33);
    }
    else{
        Rect r1 = mw->widget2->rectan;
        Rect r2 = this->getRectFromObjs(r1);
        mw->widget2->rectan = r2;
        Mat mat = mw->widget2->getMat();
        Size dsize ;
        double scale = 1;
        dsize = Size(mat.cols*scale,mat.rows*scale);
        Mat image11 = Mat(dsize,CV_32S);
        cv::resize(mat, image11,dsize);
        mw->img = QImage((const unsigned char*)(image11.data),image11.cols,mat.rows, image11.cols*image11.channels(),  QImage::Format_RGB888);

        //vector<Rectan> rectans;
        mw->aa=(&(mw->img))->copy(mw->widget2->getQRectan());
        Mat image3 = mw->QImageToMat(mw->aa);
        Mat image33 = Mat(dsize,CV_32S);
        cv::resize(image3, image33,dsize);
        setMat(image33);
    }

    int count = objs.size();
    for (int i = 0; i < count;i++)
    {
        Rect rect = objs[i].getRect();
        Scalar color = objs[i].getColor();
        rectangle(mat,rect,color,2,1,0);
        cv::cvtColor(mat, mat, CV_BGR2RGB);
    }
//    mw->paintScale(mat, 1.0, 1.0);
    if(this->from == 1){
        mw->paintScale(mat, mw->widget1->getDirectionX(), mw->widget1->getDirectionY());
    }
    else{
        mw->paintScale(mat, mw->widget2->getDirectionX(), mw->widget2->getDirectionY());
    }

    cv::cvtColor(mat,mat,CV_BGR2RGB);

    mw->imgLabel3 = mw->MatToQImage(mat,mw->imgLabel3);

    mw->loadPictureToLabel3();

}
