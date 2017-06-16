#include "zwidget.h"
#include "mainwindow.h"

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

void ZWidget::draw(){
    MainWindow *mw = (MainWindow*)parentWidget()->parentWidget();

    int count = rects.size();
    for (int i = 0; i < count;i++)
    {
        Rect rect = rects[i];
        rectangle(mat,rect,Scalar(0,0,255),4,1,0);
        cv::cvtColor(mat, mat, CV_BGR2RGB);
    }
    mw->paintScale(mat, 1.0, 1.0);
    cv::cvtColor(mat,mat,CV_BGR2RGB);

    mw->imgLabel3 = mw->MatToQImage(mat,mw->imgLabel3);

    mw->loadPictureToLabel3();

}
