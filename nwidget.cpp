#include "nwidget.h"
#include "mainwindow.h"

using namespace cv;
using namespace std;

NWidget::NWidget(QWidget *parent) :
    QWidget(parent){


}

void NWidget::setMat(Mat m){
    mat = m;
}

Mat NWidget::getMat(){
    return mat;
}

void NWidget::draw(){
    MainWindow *mw = (MainWindow*)parentWidget()->parentWidget();

    int count = rects.size();
    for (int i = 0; i < count;i++)
    {
        Rect rect = rects[i];
        rectangle(mat,rect,Scalar(0,0,255),4,1,0);
        cv::cvtColor(mat, mat, CV_BGR2RGB);
    }
    //mw->paintScale(mat, 1.0, 1.0);
    cv::cvtColor(mat,mat,CV_BGR2RGB);

    mw->imgLabel4 = mw->MatToQImage(mat,mw->imgLabel4);

    mw->loadPictureToLabel4();

}
