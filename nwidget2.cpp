
#include "nwidget2.h"
#include "mainwindow.h"
#include "myobject.h"
#include "cvutil.h"
#include "region.h"
#include "regiongroup.h"

using namespace cv;
using namespace std;

NWidget2::NWidget2(QWidget *parent) :
    QWidget(parent){
    setStyleSheet(QString::fromUtf8("border:3px solid blue"));
     this->isShow = true;
    this->from = 0;
   //completeRDefine = false;
    isYuan = true;
    isFirstDoubleClick = false;
    isClicked = false;

    Yuan_Xuanze = new QAction(tr("ԭѡ��"),this);
    Wu_Bianxing = new QAction(tr("�ޱ���"), this);
    Define_Rect = new QAction(tr("������μ������"), this);
    Define_Poly = new QAction(tr("�������μ������"), this);

    Zoom_In = new QAction(tr("�Ŵ�"), this);
    Zoom_Out = new QAction(tr("��С"),this);

    Cancel_RDefining = new QAction(tr("ȡ�����������"), this);
    Cancel_RGDefining = new QAction(tr("ȡ����������鶨��"), this);
    Complete_RDefining = new QAction(tr("��ɼ��������"), this);
    Complete_RGDefining = new QAction(tr("��ɼ�������鶨��"), this);
    //To_Tanchu = new QAction(tr("����������"),this);
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
    MainWindow *mw = (MainWindow*)parentWidget()->parentWidget();
    this->rg = mw->rg;
    this->rs = mw->rs;

    this->color  = Scalar(255,0,0);
}

void NWidget2::setColor(Scalar c){
    this->color = c;
}

Scalar NWidget2::getColor(){
    return this->color;
}

void NWidget2::setTwoPanos(Mat tps){
    twopanos = tps;
}

Mat NWidget2::getTwoPanos(){
    return twopanos;
}

void NWidget2::setPano(Mat p){
    pano = p;
}

Mat NWidget2::getPano(){
    return pano;
}

void NWidget2::setRect(Rect r){
    this->rect = r;
}

Rect NWidget2::getRect(){
    return this->rect;
}


void NWidget2::setMat(Mat m){
    mat = m;
    MainWindow *mw = (MainWindow*)parentWidget()->parentWidget();
    mw->loadPictureToLabel6(rg.color, QRect(rectRegion.x, rectRegion.y, rectRegion.width, rectRegion.height), points);

}

Mat NWidget2::getMat(){
    return mat;
}

void NWidget2::setObjects(vector<MyObject> os){
    this->objs = os;
}

vector<MyObject> NWidget2::getObjects(){
    return this->objs;
}

void NWidget2::setFrom(int f){
    this->from = f;
}

int NWidget2::getFrom(){
    return this->from;
}

void NWidget2::Yuanxuanze(){
    isYuan = true;
}

void NWidget2::Wubianxing(){
    isYuan = false;
}

void NWidget2::contextMenuEvent(QContextMenuEvent *){
    QCursor cur=this->cursor();
    QMenu *menu=new QMenu(this);

      menu->setStyleSheet(QString::fromUtf8("border:opx"));
    menu->addAction(Yuan_Xuanze); //��Ӳ˵���1
    menu->addAction(Wu_Bianxing); //��Ӳ˵���1
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
    menu->exec(cur.pos()); //���������
}

//ʵ��Ŀ��ĸ��٣���Ϊ��ͬ��Ŀ����˶��ٶȲ�ͬ������ԭ���趨��ѡ�����Ҫ��̬����
Rect NWidget2::getRectFromObjs(Rect r){
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

    //�ҳ����󼯺�������ߵĵ㣬�����ұߵĵ㣬����x����С�������
    //������С��
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
//    //��ʼ��ʱ��������
//    else{

//        return rr;
//    }
    xtemp1 = pano.cols;
    ytemp1 = pano.rows;
    //��������
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
        //��������
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
    //ʹ�ò�����
    //rr.width = rr.height * this->width() / this->height();
    //ʹ��Ŀ��λ���м�
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

void NWidget2::setAllObjects(vector<MyObject> aos){
    this->allobjs = aos;
}

vector<MyObject> NWidget2::getAllObjects(){
    return this->allobjs;
}

void NWidget2::draw(){
        MainWindow *mw = (MainWindow*)parentWidget()->parentWidget();
        //qDebug()<<this->getFrom();
        //���ݾ��ο�ı仯�����´�ȫ����ʾ��1����ȫ����ʾ��2�������mat��
        if(this->getFrom() == 1 || this->getFrom() == 2){
            /*****************************���ٸ���****************************************************
            Rect r1;
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
            *********************************���ٸ��ٽ���*********************************************/
            Mat mat1 = this->twopanos;
            Size dsize ;
            double scale = 0.5;
            dsize = Size(mat1.cols*scale,mat1.rows*scale);
    //        Mat image11 = Mat(dsize,CV_32S);
    //        cv::resize(mat1, image11,dsize);
    //        mw->img = QImage((const unsigned char*)(image11.data),image11.cols,image11.rows, image11.cols*image11.channels(),  QImage::Format_RGB888);
    //        //mw->img = CVUtil::MatToQImage(mat, mw->img);
    //        //vector<Rectan> rectans;
    //        mw->aa=(&(mw->img))->copy(mw->widget1->getQRectan3());
            Mat image4;
            if(isYuan){
                mat1(rect).copyTo(image4);//mw->QImageToMat(mw->aa);
                realRect =rect;
                Mat image44 = Mat(dsize,CV_32S);
                cv::resize(image4, image44,dsize);
                setMat(image44);
                //rectangle(mat,Rect(5,0,mat.cols-5,mat.rows),Scalar(255,0,0),5,1,0);
                CVUtil::paintScale(mat, getDirectionX((double)rect.x), getDirectionY((double)rect.y), getDirectionX2(), getDirectionY2());
            }
            else{
                Rect trect;
                trect.x = rect.x;
                trect.y = rect.y;
                trect.height = rect.height;
                trect.width = trect.height * this->width() / this->height();
                mat1(trect).copyTo(image4);
                 realRect=trect;
                Mat image44 = Mat(dsize,CV_32S);
                cv::resize(image4, image44,dsize);
                setMat(image44);
                //rectangle(mat,Rect(5,0,mat.cols-5,mat.rows),Scalar(255,0,0),5,1,0);
                CVUtil::paintScale(mat, getDirectionX((double)trect.x), getDirectionY((double)trect.y), getDirectionX(trect.x+trect.width), getDirectionY(trect.y+trect.height));
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
        else{//��ʼ��ʱ����ȫ����ʾ��1�е�һ�ι̶�����
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
              Mat image4;
              Rect trect = Rect(0,0,mat1.cols/4,mat1.rows);
              mat1(trect).copyTo(image4);//mw->QImageToMat(mw->aa);
              realRect =trect;
              Mat image44 = Mat(dsize,CV_32S);
              cv::resize(image4, image44,dsize);
              setMat(image44);
            //  rectangle(mat,Rect(5,0,mat.cols-5,mat.rows),Scalar(255,0,0),5,1,0);
              CVUtil::paintScale(mat, getDirectionX((double)trect.x), getDirectionY((double)trect.y), getDirectionX(trect.x+trect.width), getDirectionY(trect.y+trect.height));
        }
        if(isShow){
           QMap<QString, vector<Region> >::iterator ite = rg.rss.begin();
           for(;ite!=rg.rss.end();ite++){
             //  for(int k = 0;k<rg.rss.value((QString)((char)j)).size();k++){
               for(int k = 0;k<ite.value().size();k++){
                   //int sizeOfPoints = rg.rss.value((QString)((char)j)).at(k).poly.size();
                   int sizeOfPoints = ite.value().at(k).poly.size();
                   if(sizeOfPoints == 0){
                       //rectangle(mat,Rect(rg.rss.value((QString)((char)j)).at(k).rect.x,rg.rss.value((QString)((char)j)).at(k).rect.y,rg.rss.value((QString)((char)j)).at(k).rect.width,rg.rss.value((QString)((char)j)).at(k).rect.height),rg.color,1,8,0);
                       rectangle(mat,Rect(ite.value().at(k).rect.x,ite.value().at(k).rect.y,ite.value().at(k).rect.width,ite.value().at(k).rect.height),ite.value().at(k).color,1,8,0);
               }
                   else{
                       Point pp[sizeOfPoints];
                       for(int i = 0; i < sizeOfPoints; i++){
                          // pp[i] = Point(rg.rss.value((QString)((char)j)).at(k).poly[i].x, rg.rss.value((QString)((char)j)).at(k).poly[i].y);
                           pp[i] = Point(ite.value().at(k).poly[i].x,ite.value().at(k).poly[i].y);

                       }
                       const Point *pt[1] ={ pp};
                       int npt[1] = {sizeOfPoints};

                       polylines(mat,pt,npt,1,true,ite.value().at(0).color,1,8,0);

                  }
    }
    }
}
//        for(int j = 0;j<rg.rs.size();j++){

//                int sizeOfPoints = rg.rs.at(j).poly.size();
//                if(sizeOfPoints == 0){
//                    rectangle(mat,Rect(rg.rs.at(j).rect.x,rg.rs.at(j).rect.y,rg.rs.at(j).rect.width,rg.rs.at(j).rect.height),rg.color,1,8,0);

//            }
//                else{
//                    Point pp[sizeOfPoints];
//                    for(int i = 0; i < sizeOfPoints; i++){
//                        pp[i] = Point(rg.rs.at(j).poly[i].x, rg.rs.at(j).poly[i].y);

//                    }
//                    const Point *pt[1] ={ pp};
//                    int npt[1] = {sizeOfPoints};

//                    polylines(mat,pt,npt,1,true,rg.color,1,8,0);

//               }
// }


    mw->imgLabel6 = mw->MatToQImage(mat,mw->imgLabel6);
 //   cv::cvtColor(mat,mat,CV_BGR2RGB);
    //mw->loadPictureToLabel6();
    mw->loadPictureToLabel6(rg.color, QRect(rectRegion.x, rectRegion.y, rectRegion.width, rectRegion.height), points);

}
void NWidget2::ZoomIn(){
//    if(this->rect.x + 1/8 * this->rect.width >= 0){
        this->rect.x = this->rect.x + 1/8 * this->rect.width;
        this->rect.width = this->rect.width *3/4;
//    }
//    if(this->rect.y + 1/8 * this->rect.height >= 0){
        this->rect.y = this->rect.y + 1/8 * this->rect.height;
        this->rect.height = this->rect.height *3/4;
//    }
}

void NWidget2::ZoomOut(){
    if((this->rect.x - 1/6 * this->rect.width >= 0)&&(this->rect.x + this->rect.width *7/6 < pano.cols)){
        this->rect.x = this->rect.x - 1/6 * this->rect.width;
        this->rect.width = this->rect.width *4/3;
    }
    if((this->rect.y - 1/6 * this->rect.height >= 0)&&(this->rect.y + this->rect.height *7/6 < pano.rows)){
        this->rect.y = this->rect.y - 1/6 * this->rect.height;
        this->rect.height = this->rect.height *4/3;
    }
}

//������μ������
void NWidget2::DefineRect(){
    MainWindow *mw = (MainWindow*)parentWidget()->parentWidget();
    mw->isDefiningRegion =true;
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

//�������μ������
void NWidget2::DefinePoly(){
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

//ȡ�����������
void NWidget2::CancelRDefining(){
    MainWindow *mw = (MainWindow*)parentWidget()->parentWidget();
    this->rectRegion.x = 0;
    this->rectRegion.y = 0;
    this->rectRegion.width = 0;
    this->rectRegion.height = 0;
    this->points.clear();
    this->isFirstDoubleClick = false;
    mw->isDefiningRegion =false;
}

//ȡ����������鶨��
void NWidget2::CancelRGDefining(){
    this->rectRegion.x = 0;
    this->rectRegion.y = 0;
    this->rectRegion.width = 0;
    this->rectRegion.height = 0;
    this->points.clear();
    this->rs.clear();
    MainWindow *mw = (MainWindow*)parentWidget()->parentWidget();
    mw->isDefiningRegion = false;
    this->isFirstDoubleClick = false;
}

//��ɼ��������
void NWidget2::CompleteRDefining(){
   // this->completeRDefine = true;
    MainWindow *mw = (MainWindow*)parentWidget()->parentWidget();
    if(mw->isDefiningRectRegion && this->rectRegion.width == 0&&isFirstDoubleClick){
        QMessageBox::information(this,tr("���������"),tr("���μ������Ķ�����δ��ɣ���Ҫ�����������㡣"));
    }
    else if(mw->isDefiningRectRegion && !(this->rectRegion.width == 0)){
        QString name = rg.name + QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss ddd");
        Region r = Region(name, rg.color, this->rectRegion.x+this->rect.x, this->rectRegion.y+this->rect.y, this->rectRegion.width, this->rectRegion.height);
        this->rs.push_back(r);
        this->rectRegion.x = 0;
        this->rectRegion.y = 0;
        this->rectRegion.width = 0;
        this->rectRegion.height = 0;
        this->isFirstDoubleClick = false;
    }
    else if(!(mw->isDefiningRectRegion) && (this->points.size() <= 2)&&isFirstDoubleClick){
        QMessageBox::information(this,tr("���������"),tr("����μ������Ķ�����δ��ɣ�������Ҫ������������"));
        this->isFirstDoubleClick = false;
    }
    else if(!(mw->isDefiningRectRegion) && (this->points.size() > 2)){
        QString name = rg.name + QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss ddd");
        vector<Point> points1;
        for(int i = 0; i < points.size(); i++){
            Point pp = points[i];
            Point pp2 = Point(pp.x+this->rect.x, pp.y+this->rect.y);
            points1.push_back(pp2);
        }
        Region r = Region(name, rg.color, this->points);
        this->rs.push_back(r);
        this->points.clear();
        this->isFirstDoubleClick = false;
    }
    else{

    }

}

//��ɼ�������鶨��
void NWidget2::CompleteRGDefining(){
     MainWindow *mw = (MainWindow*)parentWidget()->parentWidget();
     mw->isDefiningRegion = false;
    this->CompleteRDefining();
    for(int i = 0; i < rs.size(); i++){
        Region r = rs[i];
        rg.addRegion(r);
    }
    rs.clear();
    int sizeOfGroup = rg.rss.size();
    char name  = 'a'+sizeOfGroup;
    rg.rs[0].name=(QString)name;
    rg.addRegionGroup((QString)name,rg.rs);
    rg.rs.clear();
    mw->isDefiningRegion = false;
}

void NWidget2::mousePressEvent(QMouseEvent *e){
    e->ignore();
}

void NWidget2::mouseMoveEvent(QMouseEvent *e){
    e->ignore();
}

void NWidget2::mouseReleaseEvent(QMouseEvent *e){
    if(e->button() == Qt::LeftButton){
        this->isClicked = true;
        MainWindow *mw = (MainWindow*)parentWidget()->parentWidget();
        mw->widget3->isClicked = false;
        mw->widget4->isClicked = false;
    }
    e->ignore();
}


void NWidget2::mouseDoubleClickEvent(QMouseEvent *e){
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
        mw->loadPictureToLabel6(rg.color, QRect(rectRegion.x, rectRegion.y, rectRegion.width, rectRegion.height), points);
    }
    else if(e->button() == Qt::LeftButton && !mw->isDefiningRectRegion){
        QPoint qp = e->pos();
        Point p = Point(getMatX(qp.x()),getMatY(qp.y()));
        this->points.push_back(p);
        MainWindow *mw = (MainWindow*)parentWidget()->parentWidget();
        mw->loadPictureToLabel6(rg.color, QRect(rectRegion.x, rectRegion.y, rectRegion.width, rectRegion.height), points);
    }
    else{

    }


    e->ignore();
}

boolean NWidget2::isObjSelected(MyObject obj){
    boolean isSelected = false;
        if(this->rect.contains(obj.getCenPoint())){
            //����ѡ�����ʹ��Ŀ���box��ѡ���֮��
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

//ѡ���Ŀ�겻�����ϣ�ֻ�ܼ���
vector<MyObject> NWidget2::getSelectedObjects(){
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

        //�Ѿ����ֹ��ģ�Ҳ����

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

double NWidget2::getDirectionX(double x){
    //double x = this->rectan.x;
    return 360*x/pano.cols -90;
}

double NWidget2::getDirectionY(double y){

    double yy = 20;
    //double y = this->rectan.y;
    return yy*y/pano.rows;

}

double NWidget2::getDirectionX2(){
    double x = this->rect.x+this->rect.width;
    return 360*x/pano.cols -90;
}

double NWidget2::getDirectionY2(){

    double yy = 20;
    double y = this->rect.y+this->rect.height;
    return yy*y/pano.rows;

}
//��Widget�����X���ͼ���е�X
double NWidget2::getMatX(double x){
    return x*mat.cols/this->width();
}

//��Widget�����Y���ͼ���е�Y
double NWidget2::getMatY(double y){
    return y*mat.rows/this->height();
}

//��ͼ���е�X���Widget�е�X
double NWidget2::getWidgetX(double x){
    return x*this->width()/mat.cols;
}

//��ͼ���е�Y���Widget�е�Y
double NWidget2::getWidgetY(double y){
    return y*this->height()/mat.rows;
}

void NWidget2::alertProcessing(vector<MyObject> os){
    boolean alert = false;
    double xRatio = mat.cols/realRect.width;
    double yRatio = mat.rows/realRect.height;
    for(int i = 0; i < os.size(); i++){
        MyObject mo = os[i];
        QMap<QString,vector<Region> > ::iterator ite = rg.rss.begin();
        for(; ite!= rg.rss.end(); ite++){
            RegionGroup rgg;
            rgg.rs = ite.value();
            if(rgg.isInner(Point2f((mo.cenPoint.x-realRect.x)*xRatio, (mo.cenPoint.y-realRect.y)*yRatio))){
                alert = true;
                break;
            }
        }
        if(alert){
            break;
        }
    }
    if(alert && isGaojing){
        QMessageBox::information(this,tr("�澯"),tr("������ʾ��2����Ŀ�����������"));
    }
}
