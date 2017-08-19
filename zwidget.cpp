#include "zwidget.h"
#include "mainwindow.h"
#include "myobject.h"
#include "cvutil.h"

using namespace cv;
using namespace std;

ZWidget::ZWidget(QWidget *parent) :
    QWidget(parent){

    this->from = 0;

    isYuan = true;

    Yuan_Xuanze = new QAction(tr("原选择"),this);
    Wu_Bianxing = new QAction(tr("无变形"), this);
    //To_Tanchu = new QAction(tr("到弹出窗口"),this);
    connect(Yuan_Xuanze, SIGNAL(triggered()), this, SLOT(Yuanxuanze()));
    connect(Wu_Bianxing, SIGNAL(triggered()), this, SLOT(Wubianxing()));


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
    menu->addAction(Yuan_Xuanze); //添加菜单项1
    menu->addAction(Wu_Bianxing); //添加菜单项1
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
        dsize = Size(mat1.cols*scale,mat1.rows*scale);
//        Mat image11 = Mat(dsize,CV_32S);
//        cv::resize(mat1, image11,dsize);
//        mw->img = QImage((const unsigned char*)(image11.data),image11.cols,image11.rows, image11.cols*image11.channels(),  QImage::Format_RGB888);
//        //mw->img = CVUtil::MatToQImage(mat, mw->img);
//        //vector<Rectan> rectans;
//        mw->aa=(&(mw->img))->copy(mw->widget1->getQRectan3());
        Mat image3;
        if(isYuan){
            mat1(rect).copyTo(image3);//mw->QImageToMat(mw->aa);
            Mat image33 = Mat(dsize,CV_32S);
            cv::resize(image3, image33,dsize);
            setMat(image33);
            CVUtil::paintScale(mat, getDirectionX((double)rect.x), getDirectionY((double)rect.y), getDirectionX2(), getDirectionY2());
        }
        else{
            Rect trect;
            trect.x = rect.x;
            trect.y = rect.y;
            trect.height = rect.height;
            trect.width = trect.height * this->width() / this->height();
            mat1(trect).copyTo(image3);
            Mat image33 = Mat(dsize,CV_32S);
            cv::resize(image3, image33,dsize);
            setMat(image33);
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
          mat1(Rect(0,0,mat1.cols/4,mat1.rows)).copyTo(image3);//mw->QImageToMat(mw->aa);
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
//    if(this->from == 1){
//        CVUtil::paintScale(mat, mw->widget1->getDirectionX3(), mw->widget1->getDirectionY3(), mw->widget1->getDirectionX32(), mw->widget1->getDirectionY32());
//    }
//    else if(this->from == 2){
//        CVUtil::paintScale(mat, mw->widget2->getDirectionX3(), mw->widget2->getDirectionY3(), mw->widget2->getDirectionX32(), mw->widget2->getDirectionY32());
//    }
//    else{
//        CVUtil::paintScale(mat, mw->widget1->getDirectionX3(), mw->widget1->getDirectionY3(), mw->widget1->getDirectionX32(), mw->widget1->getDirectionY32());
//    }




    mw->imgLabel3 = mw->MatToQImage(mat,mw->imgLabel3);
    //cv::cvtColor(mat,mat,CV_BGR2RGB);
    mw->loadPictureToLabel3();

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
    return 360*x/pano.cols -90;
}

double ZWidget::getDirectionY(double y){

    double yy = 10;
    //double y = this->rectan.y;
    return 10-yy*y/pano.rows;

}

double ZWidget::getDirectionX2(){
    double x = this->rect.x+this->rect.width;
    return 360*x/pano.cols -90;
}

double ZWidget::getDirectionY2(){

    double yy = 10;
    double y = this->rect.y+this->rect.height;
    return 10-yy*y/pano.rows;

}
