﻿#include "zwidget.h"
#include "mainwindow.h"
#include "myobject.h"
#include "cvutil.h"

using namespace cv;
using namespace std;

ZWidget::ZWidget(QWidget *parent) :
    QWidget(parent){
    setStyleSheet(QString::fromUtf8("border:3px solid red"));
    //setStyleSheet(QString::fromUtf8("border:3px solid red"));
     this->isShow = true;
    isGaojing = true;
    this->from = 0;
  //  completeRDefine = false;
    isYuan = true;
    isFirstDoubleClick = false;
    isClicked = false;

    Yuan_Xuanze = new QAction(tr("原选择"),this);
    Wu_Bianxing = new QAction(tr("无变形"), this);
    Define_Rect = new QAction(tr("定义矩形监控区域"), this);
    Define_Poly = new QAction(tr("定义多边形监控区域"), this);

    Cancel_RDefining = new QAction(tr("取消监控区域定义"), this);
    Cancel_RGDefining = new QAction(tr("取消监控区域组定义"), this);
    Complete_RDefining = new QAction(tr("完成监控区域定义"), this);
    Complete_RGDefining = new QAction(tr("完成监控区域组定义"), this);
    Zoom_In = new QAction(tr("放大"), this);
    Zoom_Out = new QAction(tr("缩小"),this);

    //To_Tanchu = new QAction(tr("到弹出窗口"),this);
    connect(Yuan_Xuanze, SIGNAL(triggered()), this, SLOT(Yuanxuanze()));
    connect(Wu_Bianxing, SIGNAL(triggered()), this, SLOT(Wubianxing()));
    connect(Define_Rect, SIGNAL(triggered()), this, SLOT(DefineRect()));
    connect(Define_Poly, SIGNAL(triggered()), this, SLOT(DefinePoly()));

    connect(Cancel_RDefining, SIGNAL(triggered()), this, SLOT(CancelRDefining()));
    connect(Cancel_RGDefining, SIGNAL(triggered()), this, SLOT(CancelRGDefining()));
    connect(Complete_RDefining, SIGNAL(triggered()), this, SLOT(CompleteRDefining()));
    connect(Complete_RGDefining, SIGNAL(triggered()), this, SLOT(CompleteRGDefining()));

    connect(Zoom_In, SIGNAL(triggered()), this, SLOT(ZoomIn()));
    connect(Zoom_Out, SIGNAL(triggered()), this, SLOT(ZoomOut()));
    this->rectRegion = Rect(0,0,0,0);

    color = Scalar(0,0,255);
}

void ZWidget::setColor(Scalar c){
    this->color = c;
}

Scalar ZWidget::getColor(){
    return this->color;
}

void ZWidget::setPano(Mat p){
    pano = p;
}

Mat ZWidget::getPano(){
    return pano;
}

void ZWidget::setTwoPanos(Mat tps){
    twopanos = tps;
}

Mat ZWidget::getTwoPanos(){
    return twopanos;
}

void ZWidget::setRect(Rect r){
    this->rect = r;
}

Rect ZWidget::getRect(){
    return this->rect;
}

void ZWidget::setMat(Mat m){
    mat = m;
    MainWindow *mw = (MainWindow*)parentWidget()->parentWidget();
    mw->loadPictureToLabel3(mw->rgs[mw->rgsIndex].color, QRect(rectRegion.x, rectRegion.y, rectRegion.width, rectRegion.height), points);
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

void ZWidget::Yuanxuanze(){
    isYuan = true;
}

void ZWidget::Wubianxing(){
    isYuan = false;
}

void ZWidget::contextMenuEvent(QContextMenuEvent *){

    QCursor cur=this->cursor();
    QMenu *menu=new QMenu(this);
     menu->setStyleSheet(QString::fromUtf8("border:0px"));
    menu->addAction(Yuan_Xuanze); //添加菜单项1
    menu->addAction(Wu_Bianxing); //添加菜单项1
    menu->addSeparator();
    menu->addAction(Define_Rect);
    menu->addAction(Define_Poly);
    menu->addSeparator();
    menu->addAction(Cancel_RDefining);
    menu->addAction(Cancel_RGDefining);
    menu->addAction(Complete_RDefining);
    menu->addAction(Complete_RGDefining);
    menu->addSeparator();
    menu->addAction(Zoom_In);
    menu->addAction(Zoom_Out);
    menu->exec(cur.pos()); //关联到光标
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
//    if(this->getFrom() == 1){
//       xtemp1 = mw->widget1->getPano().cols;
//       ytemp1 = mw->widget1->getPano().rows;
//    }
//    else if(this->getFrom() == 2){
//        xtemp1 = mw->widget2->getPano().cols;
//        ytemp1 = mw->widget2->getPano().rows;
//    }
//    //初始的时候不做处理
//    else{

//        return rr;
//    }
    xtemp1 = pano.cols;
    ytemp1 = pano.rows;
    //再找最大点
    double xtemp2 = 0;
    double ytemp2 = 0;

    int count = objs.size();

    //qDebug()<<count;

    for(int i = 0; i < count; i++){
        MyObject obj = objs[i];
        if(xtemp1 > obj.getRect().x){
            xtemp1 = obj.getRect().x;
            //ytemp1 = obj.getRect().y;
        }
        if(ytemp1 > obj.getRect().y){
            ytemp1 = obj.getRect().y;
        }
        if(xtemp2 < (obj.getRect().x + obj.getRect().width)){
            xtemp2 = obj.getRect().x + obj.getRect().width;
            //ytemp2 = obj.getRect().y + obj.getRect().height;
        }
        if(ytemp2 < (obj.getRect().y + obj.getRect().height)){
            ytemp2 = obj.getRect().y + obj.getRect().height;
        }
    }

    if((count > 0) && (xtemp2 - xtemp1 > this->pano.cols/2)){
        xtemp1 = pano.cols;
        //ytemp1 = pano.rows;
        //再找最大点
        xtemp2 = 0;
        //double ytemp2 = 0;
        for(int i = 0; i < count; i++){
            MyObject obj = objs[i];
            if(obj.getRect().x > this->pano.cols/2){
                if(xtemp1 > obj.getRect().x){
                    xtemp1 = obj.getRect().x;
                    //ytemp1 = obj.getRect().y;
                }
//                if(ytemp1 > obj.getRect().y){
//                    ytemp1 = obj.getRect().y;
//                }
//                if(xtemp2 < (obj.getRect().x + obj.getRect().width)){
//                    xtemp2 = obj.getRect().x + obj.getRect().width;
//                    //ytemp2 = obj.getRect().y + obj.getRect().height;
//                }
//                if(ytemp2 < (obj.getRect().y + obj.getRect().height)){
//                    ytemp2 = obj.getRect().y + obj.getRect().height;
//                }
            }
            else{
//                if(xtemp1 > obj.getRect().x+this->pano.cols){
//                    xtemp1 = obj.getRect().x+this->pano.cols;
//                    //ytemp1 = obj.getRect().y;
//                }
//                if(ytemp1 > obj.getRect().y){
//                    ytemp1 = obj.getRect().y;
//                }
                if(xtemp2 < (obj.getRect().x + obj.getRect().width+this->pano.cols)){
                    xtemp2 = obj.getRect().x + obj.getRect().width+this->pano.cols;
                    //ytemp2 = obj.getRect().y + obj.getRect().height;
                }
//                if(ytemp2 < (obj.getRect().y + obj.getRect().height)){
//                    ytemp2 = obj.getRect().y + obj.getRect().height;
//                }
            }
        }
//        qDebug()<<QString("xtemp2");
//        qDebug()<<xtemp2;
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
//        qDebug()<<QString("xtemp2");
//        qDebug()<<xtemp2;
        if(xtemp1-50 > 0){
            rr.width = xtemp2-rr.x+100;
        }
        else{
            rr.width = xtemp2-rr.x;
        }
//        qDebug()<<QString("xtemp2");
//        qDebug()<<xtemp2;
//        qDebug()<<rr.x+rr.width;
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
    //使得不变形
    //rr.width = rr.height * this->width() / this->height();
    //使得目标位于中间
    rr.x = (xtemp1+xtemp2-rr.width)/2;
    rr.y = (ytemp1+ytemp2-rr.height)/2;
    if(rr.x<0){
        rr.x=0;
    }
    if(rr.y<0){
        rr.y = 0;
    }
//    if(rr.x>=pano.cols){
//        rr.x=0;
//    }
    if(rr.y>=pano.rows){
        rr.y = 0;
    }
//    if(rr.x+rr.width > pano.cols){
//        rr.width = pano.cols - rr.x;
//    }
    if(rr.y+rr.height > pano.rows){
        rr.height = pano.rows - rr.y;
    }
   return rr;
}

////实现目标的跟踪，因为不同的目标的运动速度不同，所以原先设定的选择框需要动态调整
//Rect ZWidget::getRectFromObjs2(Rect r){
//    Rect rr;
//    rr.x = r.x;
//    rr.y = r.y;
//    rr.width = r.width;
//    rr.height = r.height;
////    for(int i = 0; i < this->objs.size(); i++){
////        MyObject obj = this->objs[i];
////        if(obj.getRect().x<r.x){
////            rr.x = obj.getRect().x - 5;
////            rr.width += r.x - obj.getRect().x + 5;
////        }
////        if(obj.getRect().y<r.y){
////            rr.y = obj.getRect().y - 5;
////            rr.height += r.y - obj.getRect().y + 5;
////        }
////        if((obj.getRect().x+obj.getRect().width)>(r.x+r.width)){
////            rr.width = obj.getRect().x + obj.getRect().width - r.x + 5;
////            //rr.x = obj.getRect().x +obj.getRect().width + 5;
////        }
////        if((obj.getRect().y+obj.getRect().height)>(r.y+r.height)){
////            rr.height = obj.getRect().y + obj.getRect().height- r.y+ 5;
////            //rr.y = obj.getRect().y +obj.getRect().height+ 5;
////        }
////    }
//    MainWindow *mw = (MainWindow*)parentWidget()->parentWidget();

//    //找出对象集合中最左边的点，和最右边的点，就是x的最小点和最大点
//    //先找最小点
//    double xtemp1;
//    double ytemp1;
//    if(this->getFrom() == 1){
//       xtemp1 = mw->widget1->getPano().cols;
//       ytemp1 = mw->widget1->getPano().rows;
//    }
//    else if(this->getFrom() == 2){
//        xtemp1 = mw->widget2->getPano().cols;
//        ytemp1 = mw->widget2->getPano().rows;
//    }
//    //初始的时候不做处理
//    else{

//        return rr;
//    }
//    //再找最大点
//    double xtemp2 = 0;
//    double ytemp2 = 0;

//    int count = objs.size();

//    //qDebug()<<count;

//    for(int i = 0; i < count; i++){
//        MyObject obj = objs[i];
//        if(xtemp1 > obj.getRect().x){
//            xtemp1 = obj.getRect().x;
//            ytemp1 = obj.getRect().y;
//        }
//        if(xtemp2 < (obj.getRect().x + obj.getRect().width)){
//            xtemp2 = obj.getRect().x + obj.getRect().width;
//            ytemp2 = obj.getRect().y + obj.getRect().height;
//        }
//    }
//    if (count > 0){
////    if(rr.x < xtemp1-50){

////    }
////    else{
//        if(xtemp1-50>0){
//            rr.x = xtemp1-mw->widget1->getMat().cols-50;
//        }
//        else{
//            rr.x = xtemp1-mw->widget1->getMat().cols;
//        }
////    }
////    if(rr.y < ytemp1-50){

////    }
////    else{
//        if(ytemp1-20 > 0){
//            rr.y = ytemp1-20;
//        }
//        else{
//            rr.y = ytemp1;
//        }
////    }
////    if(rr.width > (xtemp2-rr.x+100)){

////    }
////    else{
//        if(xtemp1-50 > 0){
//            rr.width = xtemp2-mw->widget1->getMat().cols-rr.x+100;
//        }
//        else{
//            rr.width = xtemp2-mw->widget1->getMat().cols-rr.x;
//        }
////    }
////    if(rr.height > (ytemp2-rr.y+100)){

////    }
////    else{
//        if(ytemp1-20 > 0){
//            rr.height = ytemp2-rr.y+40;
//        }
//        else{
//            rr.height = ytemp2-rr.y;
//        }
////    }
////        qDebug()<<xtemp1;
////        qDebug()<<ytemp1;
////        qDebug()<<xtemp2;
////        qDebug()<<ytemp2;
//   }
//    if(mw->isMubiao){
//        rr.width += 100;
//    }
//    //使得不变形
//    rr.width = rr.height * this->width() / this->height();
//    //使得目标位于中间
//    rr.x = (xtemp1-mw->widget1->getMat().cols+xtemp2-mw->widget1->getMat().cols-rr.width)/2;
//    rr.y = (ytemp1+ytemp2-rr.height)/2;
//    if(rr.x<0){
//        rr.x = 0;
//    }
//    if(rr.y<0){
//        rr.y = 0;
//    }
//   return rr;
//}

void ZWidget::setObjects(vector<MyObject> os){
    this->objs = os;
}

vector<MyObject> ZWidget::getObjects(){
    return this->objs;
}

void ZWidget::setAllObjects(vector<MyObject> aos){
    this->allobjs = aos;
}

vector<MyObject> ZWidget::getAllObjects(){
    return this->allobjs;
}

void ZWidget::draw(){
    MainWindow *mw = (MainWindow*)parentWidget()->parentWidget();
    //qDebug()<<this->getFrom();
    //根据矩形框的变化，重新从全景显示区1或者全景显示区2拷贝获得mat。
    if(this->getFrom() == 1 || this->getFrom() == 2){
        /**********************不再跟踪******************************************
        Rect r1;
//        qDebug()<<QString("here1!");
//        qDebug()<<this->rect.x;
//        qDebug()<<this->rect.y;
//        qDebug()<<this->rect.width;
//        qDebug()<<this->rect.height;
        r1.x = this->rect.x;
        r1.y = this->rect.y;
        r1.width = this->rect.width;
        r1.height = this->rect.height;
        this->objs = getSelectedObjects();

        Rect r2;
        if(!objs.empty()){
            r2 = this->getRectFromObjs(r1);
        }
        else{
            r2 = r1;
        }
        rect.x = r2.x;
        rect.y = r2.y;
        rect.width = r2.width;
        rect.height = r2.height;
        ************************不再跟踪结束************************************/
//        qDebug()<<QString("here2!");
//        qDebug()<<this->pano.cols;
//        qDebug()<<this->rect.x + this->rect.width;
//        qDebug()<<this->rect.x;
//        qDebug()<<this->rect.y;
//        qDebug()<<this->rect.width;
//        qDebug()<<this->rect.height;
        Mat mat1 = this->twopanos;
        Size dsize ;
        double scale = 0.5;
        dsize = Size(mw->widget3->width(),mw->widget3->height());
//        Mat image11 = Mat(dsize,CV_32S);
//        cv::resize(mat1, image11,dsize);
//        mw->img = QImage((const unsigned char*)(image11.data),image11.cols,image11.rows, image11.cols*image11.channels(),  QImage::Format_RGB888);
//        //mw->img = CVUtil::MatToQImage(mat, mw->img);
//        //vector<Rectan> rectans;
//        mw->aa=(&(mw->img))->copy(mw->widget1->getQRectan3());
        Mat image3;
        if(isYuan){
            mat1(rect).copyTo(image3);//mw->QImageToMat(mw->aa);
            realRect=rect;
            Mat image33 = Mat(dsize,CV_32S);
            cv::resize(image3, image33,dsize);
            setMat(image33);
            //setMat(image3);
            //rectangle(mat,Rect(5,0,mat.cols-5,mat.rows),Scalar(0,0,255),5,1,0);
            CVUtil::paintScale(mat, getDirectionX((double)rect.x), getDirectionY((double)rect.y), getDirectionX2(), getDirectionY2(),2);
        }
        else{
            Rect trect;
            trect.x = rect.x;
            trect.y = rect.y;
            trect.height = rect.height;
            trect.width = trect.height * this->width() / this->height();
            mat1(trect).copyTo(image3);
            realRect=trect;
            Mat image33 = Mat(dsize,CV_32S);
            cv::resize(image3, image33,dsize);
            setMat(image33);
            //setMat(image3);
            //rectangle(mat,Rect(5,0,mat.cols-5,mat.rows),Scalar(0,0,255),5,1,0);
            CVUtil::paintScale(mat, getDirectionX((double)trect.x), getDirectionY((double)trect.y), getDirectionX(trect.x+trect.width), getDirectionY(trect.y+trect.height),2);
        }

    }
//    else if(this->getFrom() == 2){
//        Rect r1;
//        r1.x = mw->widget2->rectan3.x;
//        r1.y = mw->widget2->rectan3.y;
//        r1.width = mw->widget2->rectan3.width;
//        r1.height = mw->widget2->rectan3.height;
//        this->objs = mw->widget2->getSelectedObjects3();

//        Rect r2;
//        if(!objs.empty()){
//            r2 = this->getRectFromObjs2(r1);
//        }
//        else{
//            r2 = r1;
//        }
//        mw->widget2->rectan3.x = r2.x;
//        mw->widget2->rectan3.y = r2.y;
//        mw->widget2->rectan3.width = r2.width;
//        mw->widget2->rectan3.height = r2.height;
//        Mat mat2 = mw->widget2->getPano();
//        Size dsize ;
//        double scale = 1;
//        dsize = Size(mat2.cols*scale,mat2.rows*scale);
////        Mat image11 = Mat(dsize,CV_32S);
////        cv::resize(mat2, image11,dsize);
////        mw->img = QImage((const unsigned char*)(image11.data),image11.cols,image11.rows, image11.cols*image11.channels(),  QImage::Format_RGB888);

////        //vector<Rectan> rectans;
////        mw->aa=(&(mw->img))->copy(mw->widget2->getQRectan3());
////        Mat image3 = mw->QImageToMat(mw->aa);
////        Mat image33 = Mat(dsize,CV_32S);
////        cv::resize(image3, image33,dsize);
////        setMat(image33);
//        Mat image3;
//        mat2(mw->widget2->getQRectan3()).copyTo(image3);//mw->QImageToMat(mw->aa);
//        Mat image33 = Mat(dsize,CV_32S);
//        cv::resize(image3, image33,dsize);
//        setMat(image33);
//    }
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
        Mat mat1 = pano;
        Size dsize ;
        double scale = 1;
        dsize = Size(mat1.cols*scale,mat1.rows*scale);
//        Mat image11 = Mat(dsize,CV_32S);
//        cv::resize(mat1, image11,dsize);
//        mw->img = QImage((const unsigned char*)(image11.data),image11.cols,image11.rows, image11.cols*image11.channels(),  QImage::Format_RGB888);

//        //vector<Rectan> rectans;
//        mw->aa=(&(mw->img))->copy(QRect(1490,250,100,100));
//        Mat image3 = mw->QImageToMat(mw->aa);
//        Mat image33 = Mat(dsize,CV_32S);
//        cv::resize(image3, image33,dsize);
//        setMat(image33);
          Mat image3;

          QDesktopWidget* desktopWidget = QApplication::desktop();
          QRect screenRect = desktopWidget->screenGeometry();
          int screenWidth=screenRect.width();
          int screenHeight  = screenRect.height()*0.46;
          Rect trect = Rect(0,0,mat1.rows*screenWidth/screenHeight,mat1.rows);

          //Rect trect = Rect(0,0,mat1.cols/4,mat1.rows);
          mat1(trect).copyTo(image3);//mw->QImageToMat(mw->aa);
          realRect=trect;
//          Mat image33 = Mat(dsize,CV_32S);
//          cv::resize(image3, image33,dsize);
//          setMat(image33);
          setMat(image3);
         // rectangle(mat,Rect(5,0,mat.cols-5,mat.rows),Scalar(0,0,255),5,1,0);
          CVUtil::paintScale(mat, getDirectionX((double)trect.x), getDirectionY((double)trect.y), getDirectionX(trect.x+trect.width), getDirectionY(trect.y+trect.height),2);
    }
    for(int j=0;j<this->rs.size();j++){
        this->rs[j].draw1Time(mat);
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
//    if(this->from == 1){
//        CVUtil::paintScale(mat, mw->widget1->getDirectionX3(), mw->widget1->getDirectionY3(), mw->widget1->getDirectionX32(), mw->widget1->getDirectionY32());
//    }
//    else if(this->from == 2){
//        CVUtil::paintScale(mat, mw->widget2->getDirectionX3(), mw->widget2->getDirectionY3(), mw->widget2->getDirectionX32(), mw->widget2->getDirectionY32());
//    }
//    else{
//        CVUtil::paintScale(mat, mw->widget1->getDirectionX3(), mw->widget1->getDirectionY3(), mw->widget1->getDirectionX32(), mw->widget1->getDirectionY32());
//    }

//    for(int j = 0;j<rg.rs.size();j++){

//            int sizeOfPoints = rg.rs.at(j).poly.size();
//            if(sizeOfPoints == 0){
//                rectangle(mat,Rect(rg.rs.at(j).rect.x,rg.rs.at(j).rect.y,rg.rs.at(j).rect.width,rg.rs.at(j).rect.height),rg.color,1,8,0);

//        }
//            else{
//                Point pp[sizeOfPoints];
//                for(int i = 0; i < sizeOfPoints; i++){
//                    pp[i] = Point(rg.rs.at(j).poly[i].x, rg.rs.at(j).poly[i].y);

//                }
//                const Point *pt[1] ={ pp};
//                int npt[1] = {sizeOfPoints};

//                polylines(mat,pt,npt,1,true,rg.color,1,8,0);

//           }
//}



    mw->imgLabel3 = mw->MatToQImage(mat,mw->imgLabel3);
    //cv::cvtColor(mat,mat,CV_BGR2RGB);
    //mw->loadPictureToLabel3(rg.color, );
    mw->loadPictureToLabel3(mw->rgs[mw->rgsIndex].color, QRect(rectRegion.x, rectRegion.y, rectRegion.width, rectRegion.height), points);

}

void ZWidget::ZoomIn(){
    qDebug()<<"zwidget:zoomin";
    if(/*this->rect.x + this->rect.width/8 <= pano.cols && */this->rect.width*3/4>0){
        //this->rect.x = this->rect.x + this->rect.width/8;
        this->rect.width = this->rect.width *3/4;
    }
    if(/*this->rect.y + this->rect.height/8 <=pano.rows && */this->rect.height*3/4>0){
        //this->rect.y = this->rect.y + this->rect.height/8;
        this->rect.height = this->rect.height *3/4;
    }
    //qDebug()<<"zwidget.zoomin.x:"<<this->rect.x<<"y:"<<this->rect.y<<"h:"<<this->rect.height<<"w:"<<this->rect.width;
}

void ZWidget::ZoomOut(){
    if(/*(this->rect.x - this->rect.width/6 >= 0)&&*/(this->rect.x + this->rect.width *4/3 < pano.cols)){
        //this->rect.x = this->rect.x - this->rect.width/6;
        this->rect.width = this->rect.width *4/3;
    }
    if(/*(this->rect.y - 1/6 * this->rect.height >= 0)&&*/(this->rect.y + this->rect.height *4/3 < pano.rows)){
        //this->rect.y = this->rect.y - this->rect.height/6;
        this->rect.height = this->rect.height *4/3;
    }
    qDebug()<<rect.x<<","<<rect.y<<"width:"<<rect.width<<"heigth"<<rect.height;
    //qDebug()<<"rect:x="<<rect.x<<",y="<<rect.y<<",width="<<rect.width<<",height="<<rect.height;
}

//定义矩形监控区域
void ZWidget::DefineRect(){
    MainWindow *mw = (MainWindow*)parentWidget()->parentWidget();
    mw->isDefiningRegion = true;
    if(!mw->isDefiningRectRegion){

        this->points.clear();
        this->rectRegion.x = 0;
        this->rectRegion.y = 0;
        this->rectRegion.width = 0;
        this->rectRegion.height = 0;
        mw->isDefiningRectRegion = true;
        this->isFirstDoubleClick = false;
    }
    else{

    }
}

//定义多边形监控区域
void ZWidget::DefinePoly(){
    MainWindow *mw = (MainWindow*)parentWidget()->parentWidget();
    mw->isDefiningRegion = true;
    if(mw->isDefiningRectRegion){
        this->points.clear();
        this->rectRegion.x = 0;
        this->rectRegion.y = 0;
        this->rectRegion.width = 0;
        this->rectRegion.height = 0;
        mw->isDefiningRectRegion = false;
        this->isFirstDoubleClick = false;
    }
    else{

    }
}

//取消监控区域定义
void ZWidget::CancelRDefining(){
    MainWindow *mw = (MainWindow*)parentWidget()->parentWidget();
    this->rectRegion.x = 0;
    this->rectRegion.y = 0;
    this->rectRegion.width = 0;
    this->rectRegion.height = 0;
    this->points.clear();
    this->isFirstDoubleClick = false;
    mw->isDefiningRegion =false;
}

//取消监控区域组定义
void ZWidget::CancelRGDefining(){
    this->rectRegion.x = 0;
    this->rectRegion.y = 0;
    this->rectRegion.width = 0;
    this->rectRegion.height = 0;
    this->points.clear();
    MainWindow *mw = (MainWindow*)parentWidget()->parentWidget();
    mw->rs.clear();
    this->rs.clear();
    mw->isDefiningRegion = false;
    this->isFirstDoubleClick = false;
}

//完成监控区域定义
void ZWidget::CompleteRDefining(){
    // this->completeRDefine = true;
     MainWindow *mw = (MainWindow*)parentWidget()->parentWidget();
     if(mw->isDefiningRectRegion && this->rectRegion.width == 0&&isFirstDoubleClick){
         QMessageBox::information(this,tr("监控区域定义"),tr("矩形监控区域的定义尚未完成，需要定义两个顶点。"));
     }
     else if(mw->isDefiningRectRegion && !(this->rectRegion.width == 0)){
         QString name = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss ddd");
         Region r = Region(name, mw->rgs[mw->rgsIndex].color, convertToOriginX(rectRegion.x), convertToOriginY(rectRegion.y), convertToOriginWidth(rectRegion.width), convertToOriginHeight(rectRegion.height));
         mw->rs.push_back(r);

         this->rs.push_back(Region(name,mw->rgs[mw->rgsIndex].color,rectRegion));
         this->rectRegion.x = 0;
         this->rectRegion.y = 0;
         this->rectRegion.width = 0;
         this->rectRegion.height = 0;
         this->isFirstDoubleClick = false;
     }
     else if(!(mw->isDefiningRectRegion) && (this->points.size() <= 2)&&isFirstDoubleClick){
         QMessageBox::information(this,tr("监控区域定义"),tr("多边形监控区域的定义尚未完成，至少需要定义三个顶点"));
         this->isFirstDoubleClick = false;
     }
     else if(!(mw->isDefiningRectRegion) && (this->points.size() > 2)){
         QString name = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss ddd");
         vector<Point> points1;
         for(int i = 0; i < points.size(); i++){
             Point pp2 = Point(convertToOriginX(points[i].x), convertToOriginY(points[i].y));
             points1.push_back(pp2);
         }
         Region r = Region(name, mw->rgs[mw->rgsIndex].color, points1);
         mw->rs.push_back(r);
         this->rs.push_back(Region(name, mw->rgs[mw->rgsIndex].color, points));
         this->points.clear();
         this->isFirstDoubleClick = false;
     }
     else{

     }

}

//完成监控区域组定义
void ZWidget::CompleteRGDefining(){
    MainWindow *mw = (MainWindow*)parentWidget()->parentWidget();
    if(mw->isDefiningRegion == false)
        return;
    mw->isDefiningRegion = false;
   this->CompleteRDefining();
    if(mw->rs.size() == 0)
        return;
   for(int i = 0; i < mw->rs.size(); i++){
       mw->rgs[mw->rgsIndex].addRegion(mw->rs[i]);
   }

   mw->rs.clear();
   this->rs.clear();

   if(mw->rgsIndex + 1 == mw->rgs.size()){
       mw->rgsIndex++;
       char name  = 'a' + mw->rgsIndex;
       RegionGroup *rg = new RegionGroup((QString)name, Scalar(0,255,0));
       mw->rgs.push_back(*rg);
   }else{
       mw->rgsIndex = mw->rgs.size()-1;
   }
}

void ZWidget::mouseDoubleClickEvent(QMouseEvent *e){
    MainWindow *mw = (MainWindow*)parentWidget()->parentWidget();
    Rect nrect;
    if(e->button() == Qt::LeftButton && mw->isDefiningRectRegion && !isFirstDoubleClick){
       isFirstDoubleClick = true;
       position11 = e->pos();
    }
    else if(e->button() == Qt::LeftButton && mw->isDefiningRectRegion && isFirstDoubleClick){
        isFirstDoubleClick = false;
        int posX = e->x();
        int posY = e->y();
        int x_position22;
        int y_position22;
        if(posX>this->width())
        {
            x_position22 = e->x();
        }
        else if( posX< 0)
        {
            x_position22 =0;
        }
        else
        {
            x_position22 = e->x();
        }
        if( posY>this->height())
        {
            y_position22 = e->y();
        }

        else if ( posY < 0)
        {
            y_position22=0;
        }
        else
        {
            y_position22=posY;
        }
        if(x_position22<=this->width() && y_position22<=this->height()){
            if(position11.x()<x_position22 && position11.y()<y_position22)
            {
                nrect.x=getMatX(position11.x());
                nrect.y=getMatY(position11.y());
                nrect.width=getMatX(x_position22)-getMatX(position11.x());
                nrect.height=getMatY(y_position22)-getMatY(position11.y());
            }
            else if(position11.x()<x_position22 && position11.y()> y_position22)
            {
                nrect.x=getMatX(position11.x());
                nrect.y=getMatY(y_position22);
                nrect.width=getMatX(x_position22)-getMatX(position11.x());
                nrect.height=getMatY(position11.y())-getMatY(y_position22);
            }
            else if(position11.x()>x_position22 && position11.y()< y_position22)
            {
                nrect.x=getMatX(x_position22);
                nrect.y=getMatY(position11.y());
                nrect.width=getMatX(position11.x())-getMatX(x_position22);
                nrect.height=getMatY(y_position22)-getMatY(position11.y());
            }
            else if(position11.x()>x_position22 && position11.y()> y_position22)
            {
                nrect.x=getMatX(x_position22);
                nrect.y=getMatY(y_position22);
                nrect.width=getMatX(position11.x())-getMatX(x_position22);
                nrect.height=getMatY(position11.y())-getMatY(y_position22);
            }
        }
        if(nrect.width<0){
            this->rectRegion.width = -nrect.width;
            this->rectRegion.height= -nrect.height;
            this->rectRegion.x = nrect.x+nrect.width;
            this->rectRegion.y = nrect.y+nrect.height;
        }
        else if(nrect.height<0){
            this->rectRegion.width = -nrect.width;
            this->rectRegion.height= -nrect.height;
            this->rectRegion.x = nrect.x+nrect.width;
            this->rectRegion.y = nrect.y+nrect.height;
        }
        else{
            this->rectRegion.x = nrect.x;
            this->rectRegion.y = nrect.y;
            this->rectRegion.width = nrect.width;
            this->rectRegion.height = nrect.height;

        }
        MainWindow *mw = (MainWindow*)parentWidget()->parentWidget();
        mw->loadPictureToLabel3(mw->rgs[mw->rgsIndex].color, QRect(rectRegion.x, rectRegion.y, rectRegion.width, rectRegion.height), points);
    }
    else if(e->button() == Qt::LeftButton && !mw->isDefiningRectRegion){
        QPoint qp = e->pos();
        Point p = Point(getMatX(qp.x()),getMatY(qp.y()));
        this->points.push_back(p);
        MainWindow *mw = (MainWindow*)parentWidget()->parentWidget();
        mw->loadPictureToLabel3(mw->rgs[mw->rgsIndex].color, QRect(rectRegion.x, rectRegion.y, rectRegion.width, rectRegion.height), points);
    }
    else{

    }


    e->ignore();
}

void ZWidget::mousePressEvent(QMouseEvent *e){
    e->ignore();
}

void ZWidget::mouseMoveEvent(QMouseEvent *e){
    e->ignore();
}

void ZWidget::mouseReleaseEvent(QMouseEvent *e){
    MainWindow *mw = (MainWindow*)parentWidget()->parentWidget();
    if(e->button() == Qt::LeftButton){
        this->isClicked = true;

        mw->widget4->isClicked = false;
        mw->widget6->isClicked = false;
    }
    e->ignore();

    if(mw->widget5->isClicked == true && this->isClicked == true){


    }
}

boolean ZWidget::isObjSelected(MyObject obj){
    boolean isSelected = false;
        if(this->rect.contains(obj.getCenPoint())){
            //调整选择框以使得目标的box在选择框之内
            if(obj.getRect().x<this->rect.x){
                this->rect.x = obj.getRect().x - 5;
                this->rect.width += this->rect.x - obj.getRect().x + 5;
            }
            if(obj.getRect().y<this->rect.y){
                this->rect.y = obj.getRect().y - 5;
                this->rect.height += this->rect.y - obj.getRect().y + 5;
            }
            if((obj.getRect().x+obj.getRect().width)>(this->rect.x+this->rect.width)){
                //this->rectan3.x = obj.getRect().x +obj.getRect().width + 5;

                this->rect.width = obj.getRect().x + obj.getRect().width - this->rect.x + 5;
            }
            if((obj.getRect().y+obj.getRect().height)>(this->rect.y+this->rect.height)){
                this->rect.height = this->rect.height + obj.getRect().y + obj.getRect().height- this->rect.y+ 5;
                //this->rectan3.y = obj.getRect().y +obj.getRect().height+ 5;
            }

            isSelected = true;
        }
    return isSelected;
}

//选择的目标不能捎上，只能减少
vector<MyObject> ZWidget::getSelectedObjects(){
    vector<MyObject> os;
    int count = this->allobjs.size();
//    for(int i = 0; i < count; i++){
//        MyObject obj = allobjs[i];
//        if(isObjSelected(obj)){
//            os.push_back(obj);
//        }

//    }

    for(int i = 0; i < count; i++){
        MyObject obj = allobjs[i];

        //已经出现过的，也跟上

        vector<MyObject> aos = this->objs;
        for(int j = 0; j < aos.size(); j++){
            MyObject aobj = aos[j];
            if(obj.getID() == aobj.getID()){
                boolean all = false;
                for(int k = 0; k < os.size(); k++){
                    MyObject bobj = os[k];
                    if(aobj.getID() == bobj.getID()){
                        all = true;
                    }
                }
                if(!all){
                    os.push_back(obj);
                    all = false;
                }
            }
        }
    }


    return os;
}

double ZWidget::getDirectionX(double x){
    //double x = this->rectan.x;
    //return 360*x/pano.cols -90;
      return 360*x/pano.cols;
}

double ZWidget::getDirectionY(double y){

    double yy = 10;
    //double y = this->rectan.y;
    return 10-yy*y/pano.rows;

}

double ZWidget::getDirectionX2(){
    double x = this->rect.x+this->rect.width;
   // return 360*x/pano.cols -90;
    return 360*x/pano.cols;
}

double ZWidget::getDirectionY2(){

    double yy = 10;
    double y = this->rect.y+this->rect.height;
    return 10-yy*y/pano.rows;

}

//由Widget坐标的X获得图像中的X
double ZWidget::getMatX(double x){
    return x*mat.cols/this->width();
}

//由Widget坐标的Y获得图像中的Y
double ZWidget::getMatY(double y){
    return y*mat.rows/this->height();
}

//由图像中的X获得Widget中的X
double ZWidget::getWidgetX(double x){
    return x*this->width()/mat.cols;
}

//由图像中的Y获得Widget中的Y
double ZWidget::getWidgetY(double y){
    return y*this->height()/mat.rows;
}


//把监控区的坐标转换成在全景视图的坐标
int ZWidget::convertToOriginX(int x){
    double ratio = ((double)realRect.width)/mat.cols;
    return x*ratio + realRect.x;
}

//把监控区的坐标转换成在全景视图的坐标
int ZWidget::convertToOriginY(int y){
    double ratio = ((double)realRect.height)/mat.rows;
    return y*ratio + realRect.y;
}

//把监控区的宽转换成在全景视图的宽度
int ZWidget::convertToOriginWidth(int width){
    double ratio = ((double)realRect.width)/mat.cols;
    return width*ratio;
}
//把监控区的长转换成在全景视图的长度
int ZWidget::convertToOriginHeight(int height){
    double ratio = ((double)realRect.height)/mat.rows;
    return height*ratio;
}


