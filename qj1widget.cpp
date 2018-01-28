﻿
#include "qj1widget.h"
#include "mainwindow.h"
#include "myobject.h"
#include "myobjecttrack.h"
#include "cvutil.h"
#include "region.h"
#include "regiongroup.h"

using namespace cv;
using namespace std;

Qj1Widget::Qj1Widget(QWidget *parent) :
    QWidget(parent){
        hasRect3 = false;
        hasRect4 = false;
        hasRect6 = false;

        this->isShow = true;
        isGaojing = true;
       //completeRDefine = false;
        isDrag = false;
        isMove = false;
        isRect = false;

        isTo3 = false;
        isTo4 = false;
        isTo6 = false;
        isClicked = false;

        isFirstDoubleClick = false;

        //Cancel_Select = new QAction(tr("取消选择"),this);
        //To_Zhu= new QAction(tr("到主显示区"), this);
        //To_Ningshi1 = new QAction(tr("到辅助显示区1"), this);
        //To_Ningshi2 = new QAction(tr("到辅助显示区2"), this);
        //To_Tanchu = new QAction(tr("到弹出窗口"),this);

        Define_Rect = new QAction(tr("定义矩形监控区域"), this);
        Define_Poly = new QAction(tr("定义多边形监控区域"), this);

        Cancel_RDefining = new QAction(tr("取消监控区域定义"), this);
        Cancel_RGDefining = new QAction(tr("取消监控区域组定义"), this);
        Complete_RDefining = new QAction(tr("完成监控区域定义"), this);
        Complete_RGDefining = new QAction(tr("完成监控区域组定义"), this);

//        connect(Cancel_Select, SIGNAL(triggered()), this, SLOT(CancelSelect()));
//        connect(To_Zhu, SIGNAL(triggered()), this, SLOT(ToZhu()));
//        connect(To_Ningshi1, SIGNAL(triggered()), this, SLOT(ToNingshi1()));
//        connect(To_Ningshi2, SIGNAL(triggered()), this, SLOT(ToNingshi2()));
        //connect(To_Tanchu, SIGNAL(triggered()), this, SLOT(ToTanchu()));

        connect(Define_Rect, SIGNAL(triggered()), this, SLOT(DefineRect()));
        connect(Define_Poly, SIGNAL(triggered()), this, SLOT(DefinePoly()));

        connect(Cancel_RDefining, SIGNAL(triggered()), this, SLOT(CancelRDefining()));
        connect(Cancel_RGDefining, SIGNAL(triggered()), this, SLOT(CancelRGDefining()));
        connect(Complete_RDefining, SIGNAL(triggered()), this, SLOT(CompleteRDefining()));
        connect(Complete_RGDefining, SIGNAL(triggered()), this, SLOT(CompleteRGDefining()));

        this->rectRegion = Rect(0,0,0,0);

        rectan3 = Rect(1490,250,100,100);
        rectan4 = Rect(1490,250,100,100);
        rectan6 = Rect(1490,250,100,100);
        newrect = Rect(1490,250,100,100);



        //paint=new QPainter;
    }

void Qj1Widget::setMat(Mat m){
    mat = m;
//    if(isRect){
//        MainWindow *mw = (MainWindow*)parentWidget()->parentWidget();
//        //mw->test();

//        rectangle(mat,newrect,Scalar(0,0,255),1,1,0);
//        cv::cvtColor(mat, mat, CV_BGR2RGB);
//        mw->loadPictureToLabel1();
//        isRect = true;
//    }
    MainWindow *mw = (MainWindow*)parentWidget()->parentWidget();
    mw->loadPictureToLabel1(isRect, qrect, mw->rgs[mw->rgsIndex].color, QRect(rectRegion.x, rectRegion.y, rectRegion.width, rectRegion.height), points, rs);
}

Mat Qj1Widget::getMat(){
    return mat;
}

void Qj1Widget::setPano(Mat p){
    this->pano = p;
}

Mat Qj1Widget::getPano(){
    return this->pano;
}

void Qj1Widget::setTwoPano(Mat tp){
    this->twoPano = tp;
}

Mat Qj1Widget::getTwoPano(){
    return this->twoPano;
}

void Qj1Widget::setObjects(vector<MyObject> os){
    this->objs = os;
}

vector<MyObject> Qj1Widget::getObjects(){
    return this->objs;
}

void Qj1Widget::setTracks(vector<MyObjectTrack> ts){
    this->tracks =ts;
}

vector<MyObjectTrack> Qj1Widget::getTracks(){
    return this->tracks;
}

void Qj1Widget::contextMenuEvent(QContextMenuEvent *){
    MainWindow *mw = (MainWindow*)parentWidget()->parentWidget();
        if(mw->isDefiningRegion){
        QCursor cur=this->cursor();
        QMenu *menu=new QMenu(this);
       //menu->addAction(Cancel_Select); //添加菜单项1
       //menu->addAction(To_Zhu); //添加菜单项1
       //menu->addAction(To_Ningshi1); //添加菜单项2
       //menu->addAction(To_Ningshi2); //添加菜单项2
       //menu->addAction(To_Tanchu);//添加菜单项3
        //menu->addSeparator();
        menu->addAction(Define_Rect);
        menu->addAction(Define_Poly);
        menu->addSeparator();
        menu->addAction(Cancel_RDefining);
        menu->addAction(Cancel_RGDefining);
        menu->addSeparator();
        menu->addAction(Complete_RDefining);
        menu->addAction(Complete_RGDefining);
        menu->exec(cur.pos()); //关联到光标
        //menu->hide();
    }
}

void Qj1Widget::CancelSelect(){
    isRect = false;
}

void Qj1Widget::draw(){

    MainWindow *mw = (MainWindow*)parentWidget()->parentWidget();
    //qDebug()<<this->objs.size();
//    int count = this->objs.size();
//    for (int i = 0; i < count;i++)
//    {
//        //画对象的box
//        MyObject obj = objs[i];
//        rectangle(mat,obj.getRect(),obj.getColor(),2,1,0);
//        //画轨迹
//        for(int ii = 0; ii < this->tracks.size(); ii++){
//            MyObjectTrack track = this->tracks[ii];
//            int id = track.getId();
//            vector<Point> points = track.getTrack();
//            if(id == obj.getID()){
//                for(int iii = 0; iii < points.size(); iii++){
//                    Point point = points[iii];
//                    circle(mat, point, 2, obj.getColor(),-1,8,2);//在图像中画出特征点，2是圆的半径
//                    if(iii >= 1){
//                        Point point2 = points[iii-1];
//                        line(mat,point,point2,obj.getColor(),1,8,0);
//                    }
//                }
//            }
//        }
//        //画对象中心点的位置
//        if(mw->isMubiao){
//            int x = (int)(this->getDirectionX(obj.getCenPoint().x));
//            int y = (int)(10-this->getDirectionY(obj.getCenPoint().y)/2);//(10-10*(this->getDirectionY(obj.getCenPoint().y)-this->getDirectionY())/(this->getDirectionY2()-this->getDirectionY()));//endh - i*(endh-starth)/10
//            QString tx = QString::number(x,10);
//            QString ty = QString::number(y,10);
//            QString tstr = "x="+tx+",y="+ty;
//            string str = tstr.toStdString();
//            //qDebug()<<tstr;
//            Point p = Point(obj.getRect().x+obj.getRect().width,obj.getRect().y+obj.getRect().height);
//            putText(mat,str,p,3,1,obj.getColor());
//        }
//        cv::cvtColor(mat, mat, CV_BGR2RGB);
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
//    for(int j=0;j<this->rs.size();j++){
//        this->rs[j].draw1Time(mat);
//    }

    clock_t tt1=clock();
    mw->imgLabel1 = mw->MatToQImage(mat,mw->imgLabel1);
    //cv::cvtColor(mat, mat, CV_BGR2RGB);
    clock_t tt2=clock();
    mw->loadPictureToLabel1(isRect, qrect, mw->rgs[mw->rgsIndex].color, QRect(rectRegion.x, rectRegion.y, rectRegion.width, rectRegion.height), points, rs);
    clock_t tt3=clock();
    printf("\t\t\t\tfunction MatToQImage costs time:%d\n",tt2-tt1);
    printf("\t\t\t\tfunction loadPictureToLabel1 costs time:%d\n",tt3-tt2);
}

boolean Qj1Widget::isObjSelected3(MyObject obj){
    boolean isSelected = false;
        if(this->rectan3.contains(obj.getCenPoint())){
            //调整选择框以使得目标的box在选择框之内
            if(obj.getRect().x<this->rectan3.x){
                this->rectan3.x = obj.getRect().x - 5;
                this->rectan3.width += this->rectan3.x - obj.getRect().x + 5;
            }
            if(obj.getRect().y<this->rectan3.y){
                this->rectan3.y = obj.getRect().y - 5;
                this->rectan3.height += this->rectan3.y - obj.getRect().y + 5;
            }
            if((obj.getRect().x+obj.getRect().width)>(this->rectan3.x+this->rectan3.width)){
                //this->rectan3.x = obj.getRect().x +obj.getRect().width + 5;

                this->rectan3.width = obj.getRect().x + obj.getRect().width - this->rectan3.x + 5;
            }
            if((obj.getRect().y+obj.getRect().height)>(this->rectan3.y+this->rectan3.height)){
                this->rectan3.height = this->rectan3.height + obj.getRect().y + obj.getRect().height- this->rectan3.y+ 5;
                //this->rectan3.y = obj.getRect().y +obj.getRect().height+ 5;
            }

            isSelected = true;
        }
    return isSelected;
}

boolean Qj1Widget::isObjSelected4(MyObject obj){
    boolean isSelected = false;
    if(this->rectan4.contains(obj.getCenPoint())){
        //调整选择框以使得目标的box在选择框之内
        if(obj.getRect().x<this->rectan4.x){
            this->rectan4.x = obj.getRect().x - 5;
            this->rectan4.width += this->rectan4.x - obj.getRect().x + 5;
        }
        if(obj.getRect().y<this->rectan4.y){
            this->rectan4.y = obj.getRect().y - 5;
            this->rectan4.height += this->rectan4.y - obj.getRect().y + 5;
        }
        if((obj.getRect().x+obj.getRect().width)>(this->rectan4.x+this->rectan4.width)){
            //this->rectan4.x = obj.getRect().x +obj.getRect().width + 5;

            this->rectan4.width = obj.getRect().x + obj.getRect().width - this->rectan4.x + 5;
        }
        if((obj.getRect().y+obj.getRect().height)>(this->rectan4.y+this->rectan4.height)){
            this->rectan4.height = this->rectan4.height + obj.getRect().y + obj.getRect().height- this->rectan4.y+ 5;
            //this->rectan4.y = obj.getRect().y +obj.getRect().height+ 5;
        }

        isSelected = true;
    }
    return isSelected;
}

boolean Qj1Widget::isObjSelected6(MyObject obj){
    boolean isSelected = false;
    if(this->rectan6.contains(obj.getCenPoint())){
        //调整选择框以使得目标的box在选择框之内
        if(obj.getRect().x<this->rectan6.x){
            this->rectan6.x = obj.getRect().x - 5;
            this->rectan6.width += this->rectan6.x - obj.getRect().x + 5;
        }
        if(obj.getRect().y<this->rectan6.y){
            this->rectan6.y = obj.getRect().y - 5;
            this->rectan6.height += this->rectan6.y - obj.getRect().y + 5;
        }
        if((obj.getRect().x+obj.getRect().width)>(this->rectan6.x+this->rectan6.width)){
            //this->rectan4.x = obj.getRect().x +obj.getRect().width + 5;

            this->rectan6.width = obj.getRect().x + obj.getRect().width - this->rectan6.x + 5;
        }
        if((obj.getRect().y+obj.getRect().height)>(this->rectan6.y+this->rectan6.height)){
            this->rectan6.height = this->rectan6.height + obj.getRect().y + obj.getRect().height- this->rectan6.y+ 5;

            //this->rectan4.y = obj.getRect().y +obj.getRect().height+ 5;
        }

        isSelected = true;
    }
    return isSelected;
}

void Qj1Widget::ToZhu()
{
    //qDebug()<<"到主显示区。";

    this->isTo3 = true;
    MainWindow *mw = (MainWindow*)parentWidget()->parentWidget();

    mw->widget2->isTo3 = false;

    if(this->newrect.width<0){
        this->rectan3.width = -this->newrect.width;
        this->rectan3.height= -this->newrect.height;
        this->rectan3.x = this->newrect.x+this->newrect.width;
        this->rectan3.y = this->newrect.y+this->newrect.height;
    }
    else if(this->newrect.height<0){
        this->rectan3.width = -this->newrect.width;
        this->rectan3.height= -this->newrect.height;
        this->rectan3.x = this->newrect.x+this->newrect.width;
        this->rectan3.y = this->newrect.y+this->newrect.height;
    }
    else{
        this->rectan3.x = this->newrect.x;
        this->rectan3.y = this->newrect.y;
        this->rectan3.width = this->newrect.width;
        this->rectan3.height = this->newrect.height;
    }

//    this->rectan3.x = this->newrect.x;
//    this->rectan3.y = this->newrect.y;
//    this->rectan3.width = this->newrect.width;
//    this->rectan3.height = this->newrect.height;

    //调整所选的矩形框，以使得在主显示区中的显示不变形
    //this->rectan3.width = this->rectan3.height * mw->widget3->width() / mw->widget3->height();

    //更新主显示区所包含的目标
    vector<MyObject> objs3;
    int count = this->objs.size();
    for(int i = 0; i < count; i++){
        MyObject obj = objs[i];
        if(isObjSelected3(obj)){
            objs3.push_back(obj);
        }
    }
//    qDebug()<<rectan3.x;
//    qDebug()<<rectan3.y;
//    qDebug()<<rectan3.width;
//    qDebug()<<rectan3.height;
//    qDebug()<<getQRectan3();
    //qDebug()<<objs3.size();

    mw->widget3->setObjects(objs3);

    mw->widget3->setFrom(1);

    mw->widget3->setRect(rectan3);
    //mw->test();

    Mat mat = getPano();
    Size dsize ;
    double scale = 1;
    dsize = Size(mat.cols*scale,mat.rows*scale);
//    Mat image11 = Mat(dsize,CV_32S);
//    cv::resize(mat, image11,dsize);
//    mw->img = QImage((const unsigned char*)(image11.data),image11.cols,image11.rows, image11.cols*image11.channels(),  QImage::Format_RGB888);
//    //mw->img = CVUtil::MatToQImage(mat, mw->img);
//    //vector<Rectan> rectans;
//    mw->aa=(&(mw->img))->copy(getQRectan3());
//    Mat image3 = mw->QImageToMat(mw->aa);
//    Mat image33 = Mat(dsize,CV_32S);
//    cv::resize(image3, image33,dsize);
//    mw->widget3->setMat(image33);
    Mat image3;
    mat(rectan3).copyTo(image3);//mw->QImageToMat(mw->aa);
    Mat image33 = Mat(dsize,CV_32S);
    cv::resize(image3, image33,dsize);
    mw->widget3->setMat(image33);
    mw->widget3->draw();

    isRect = false;
}
//到辅助显示区1显示菜单处理事件
void Qj1Widget::ToNingshi1()
{
    //qDebug()<<"到主显示区。";

    this->isTo4 = true;

    MainWindow *mw = (MainWindow*)parentWidget()->parentWidget();

    mw->widget2->isTo4 = false;

    if(this->newrect.width<0){
        this->rectan4.width = -this->newrect.width;
        this->rectan4.height= -this->newrect.height;
        this->rectan4.x = this->newrect.x+this->newrect.width;
        this->rectan4.y = this->newrect.y+this->newrect.height;
    }
    else if(this->newrect.height<0){
        this->rectan4.width = -this->newrect.width;
        this->rectan4.height= -this->newrect.height;
        this->rectan4.x = this->newrect.x+this->newrect.width;
        this->rectan4.y = this->newrect.y+this->newrect.height;
    }
    else{
        this->rectan4.x = this->newrect.x;
        this->rectan4.y = this->newrect.y;
        this->rectan4.width = this->newrect.width;
        this->rectan4.height = this->newrect.height;
    }

    //调整所选的矩形框，以使得在凝视显示区中的显示不变形
    //this->rectan4.width = this->rectan4.height * mw->widget4->width() / mw->widget4->height();
    //更新凝视显示区所包含的目标

    vector<MyObject> objs4;
    int count = this->objs.size();
    for(int i = 0; i < count; i++){
        MyObject obj = objs[i];
        if(isObjSelected4(obj)){
            objs4.push_back(obj);
        }
    }

    mw->widget4->setObjects(objs4);

    mw->widget4->setFrom(1);

    mw->widget4->setRect(rectan4);

    Mat mat = getPano();
    Size dsize ;
    double scale = 1;
    dsize = Size(mat.cols*scale,mat.rows*scale);
//    Mat image11 = Mat(dsize,CV_32S);
//    cv::resize(mat, image11,dsize);
//    mw->img = QImage((const unsigned char*)(image11.data),image11.cols,image11.rows, image11.cols*image11.channels(),  QImage::Format_RGB888);

//    //vector<Rectan> rectans;
//    mw->aa=(&(mw->img))->copy(getQRectan4());
//    Mat image4 = mw->QImageToMat(mw->aa);
//    Mat image44 = Mat(dsize,CV_32S);
//    cv::resize(image4, image44,dsize);
//    mw->widget4->setMat(image44);
    Mat image4;
    mat(rectan4).copyTo(image4);//mw->QImageToMat(mw->aa);
    Mat image44 = Mat(dsize,CV_32S);
    cv::resize(image4, image44,dsize);
    mw->widget4->setMat(image44);
    mw->widget4->draw();
    isRect = false;
}

//到辅助显示区2显示菜单处理事件
void Qj1Widget::ToNingshi2()
{
    //qDebug()<<"到主显示区。";

    this->isTo6 = true;

    MainWindow *mw = (MainWindow*)parentWidget()->parentWidget();

    mw->widget2->isTo6 = false;

    if(this->newrect.width<0){
        this->rectan6.width = -this->newrect.width;
        this->rectan6.height= -this->newrect.height;
        this->rectan6.x = this->newrect.x+this->newrect.width;
        this->rectan6.y = this->newrect.y+this->newrect.height;
    }
    else if(this->newrect.height<0){
        this->rectan6.width = -this->newrect.width;
        this->rectan6.height= -this->newrect.height;
        this->rectan6.x = this->newrect.x+this->newrect.width;
        this->rectan6.y = this->newrect.y+this->newrect.height;
    }
    else{
        this->rectan6.x = this->newrect.x;
        this->rectan6.y = this->newrect.y;
        this->rectan6.width = this->newrect.width;
        this->rectan6.height = this->newrect.height;

    }

    //调整所选的矩形框，以使得在凝视显示区中的显示不变形
    //this->rectan4.width = this->rectan4.height * mw->widget4->width() / mw->widget4->height();
    //更新凝视显示区所包含的目标

    vector<MyObject> objs6;
    int count = this->objs.size();
    for(int i = 0; i < count; i++){
        MyObject obj = objs[i];
        if(isObjSelected6(obj)){
            objs6.push_back(obj);
        }
    }

    mw->widget6->setObjects(objs6);

    mw->widget6->setFrom(1);

    mw->widget6->setRect(rectan6);


    Mat mat = getPano();
    Size dsize ;
    double scale = 1;
    dsize = Size(mat.cols*scale,mat.rows*scale);
//    Mat image11 = Mat(dsize,CV_32S);
//    cv::resize(mat, image11,dsize);
//    mw->img = QImage((const unsigned char*)(image11.data),image11.cols,image11.rows, image11.cols*image11.channels(),  QImage::Format_RGB888);

//    //vector<Rectan> rectans;
//    mw->aa=(&(mw->img))->copy(getQRectan4());
//    Mat image4 = mw->QImageToMat(mw->aa);
//    Mat image44 = Mat(dsize,CV_32S);
//    cv::resize(image4, image44,dsize);
//    mw->widget4->setMat(image44);
    Mat image6;
    mat(rectan6).copyTo(image6);//mw->QImageToMat(mw->aa);
    Mat image66 = Mat(dsize,CV_32S);
    cv::resize(image6, image66,dsize);
    mw->widget6->setMat(image66);
    mw->widget6->draw();
    isRect = false;
}

//到弹出窗口显示菜单处理事件
//void ToTanchu(){
//    qDebug()<<"到弹出窗口。";
//}

//void QjWidget::mouseClickEvent(QMouseEvent *e){

//}

//定义矩形监控区域
void Qj1Widget::DefineRect(){
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
void Qj1Widget::DefinePoly(){
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
void Qj1Widget::CancelRDefining(){
    MainWindow *mw = (MainWindow*)parentWidget()->parentWidget();
    this->rectRegion.x = 0;
    this->rectRegion.y = 0;
    this->rectRegion.width = 0;
    this->rectRegion.height = 0;
    this->points.clear();
    this->isFirstDoubleClick = false;
    //mw->isDefiningRegion = false;
}

//取消监控区域组定义
void Qj1Widget::CancelRGDefining(){
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
void Qj1Widget::CompleteRDefining(){
   // this->completeRDefine = true;
    MainWindow *mw = (MainWindow*)parentWidget()->parentWidget();
    if(mw->isDefiningRectRegion && this->rectRegion.width == 0&&isFirstDoubleClick){
        QMessageBox::information(this,tr("监控区域定义"),tr("矩形监控区域的定义尚未完成，需要定义两个顶点。"));
    }
    else if(mw->isDefiningRectRegion && !(this->rectRegion.width == 0)){
        QString name = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
        Region r = Region(name, mw->rgs[mw->rgsIndex].color, this->rectRegion.x, this->rectRegion.y, this->rectRegion.width, this->rectRegion.height);
        mw->rs.push_back(r);

        this->rs.push_back(Region(name,mw->rgs[mw->rgsIndex].color,rectRegion));
        this->rectRegion.x = 0;
        this->rectRegion.y = 0;
        this->rectRegion.width = 0;
        this->rectRegion.height = 0;
        this->isFirstDoubleClick = false;
    }
    else if(!(mw->isDefiningRectRegion) && (this->points.size() <= 2&&isFirstDoubleClick)){
        QMessageBox::information(this,tr("监控区域定义"),tr("多边形监控区域的定义尚未完成，至少需要定义三个顶点"));
        this->isFirstDoubleClick = false;
    }
    else if(!(mw->isDefiningRectRegion) && (this->points.size() > 2)){
        QString name = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
        vector<Point> points1;
        for(int i = 0; i < points.size(); i++){
            Point pp2 = Point(points[i].x, points[i].y);
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
    mw->loadPictureToLabel1(isRect, qrect, mw->rgs[mw->rgsIndex].color, QRect(rectRegion.x, rectRegion.y, rectRegion.width, rectRegion.height), points, rs);

}

//完成监控区域组定义
void Qj1Widget::CompleteRGDefining(){

    MainWindow *mw = (MainWindow*)parentWidget()->parentWidget();
    if(mw->isDefiningRegion == false)
        return;

    this->CompleteRDefining();
     mw->isDefiningRegion = false;
    if(mw->rs.size() == 0)
        return;
   for(int i = 0; i < mw->rs.size(); i++){
       mw->rgs[mw->rgsIndex].addRegion(mw->rs[i]);
   }
   vector <vector<cv::Point> > polys;

  for(int i= 0;i<mw->rs.size();i++){
     //qDebug()<<"zwidget";
       polys.push_back(mw->rs[i].getPoly());
      for(int j = 0; j<mw->rs[i].getPoly().size();j++){
          //qDebug()<<"x,y:"<<mw->rs[i].poly[j].x<<mw->rs[i].poly[j].y;
      }
  }

   SetORIPoints(polys);

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

   mw->writeRgs();
}

void Qj1Widget::mouseDoubleClickEvent(QMouseEvent *e){
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
        mw->loadPictureToLabel1(isRect, qrect, mw->rgs[mw->rgsIndex].color, QRect(rectRegion.x, rectRegion.y, rectRegion.width, rectRegion.height), points, rs);
    }
    else if(e->button() == Qt::LeftButton && !mw->isDefiningRectRegion){
        QPoint qp = e->pos();
        Point p = Point(getMatX(qp.x()),getMatY(qp.y()));
        this->points.push_back(p);
        MainWindow *mw = (MainWindow*)parentWidget()->parentWidget();
        mw->loadPictureToLabel1(isRect, qrect, mw->rgs[mw->rgsIndex].color, QRect(rectRegion.x, rectRegion.y, rectRegion.width, rectRegion.height), points, rs);
    }
    else{

    }


    e->ignore();
}

void Qj1Widget::mousePressEvent(QMouseEvent *e)
{
    //qDebug()<<"鼠标压下事件来自qj1widget";
    if(e->button() == Qt::LeftButton)
    {
      //  isDrag = true;
        //isRect = false;
//       int posX = e->x();
//       int posY = e->y();
//        if(posX>this->width())
//        {
//             position1.x() = this->width();
//        }
//        else if( posX< 0)
//        {
//            position1.x() =0;
//        }
//        else
//        {
//            position1.x() = e->x();
//        }
//       if( posY>this->height())
//        {
//           position1.y() = this->height();
//        }

//        else if ( posY < 0)
//        {
//            position1.y()=0;
//        }
//       else
//       {
//            position1.y()=posY;
//       }
        position1 = e->pos();//e->globalPos() - this->pos();

        //e->accept();
        //qDebug()<<position1;
    }
//    qDebug()<<position1.x();
//    qDebug()<<position1.y();
    //QLabel *label = new QLabel(this);
    MainWindow *mw = (MainWindow*)parentWidget()->parentWidget();
    if(mw->location){
   locationX = this->getMatX(position1.x());
   locationY = this->getMatY(position1.y());
   int angleX = mw->widget4->getDirectionX(locationX);
   int angleY = mw->widget4->getDirectionY(locationY);
        QPixmap pixmap1 = QPixmap::fromImage(mw->imgLabel1);
        QPainter p(&pixmap1);
        QPen pen;
        pen.setColor(QColor(255,255,255,255));
        QFont font("幼圆", 80, QFont::Bold);
        p.setFont(font);
        p.setPen(pen);
//       if(locationX*this->width()>3*mat.cols/10){
//         p.drawText(locationX-20,locationY+2,QString("x:").append(QString::number(position1.x()).append("  ")).append(QString("y:")).append(QString::number(position1.y())));
//       }
//       else
        // p.drawText(locationX-2,locationY+2,QString("x:").append(QString::number(position1.x()).append("  ")).append(QString("y:")).append(QString::number(position1.y())));
      // p.drawText(locationX-2,locationY+2,QString("x:").append(QString::number(this->locationX)).append("  ").append(QString("y:")).append(QString::number(this->locationY)));
     p.drawText(locationX-2,locationY+2,QString("x:").append(QString::number(angleX)).append("  ").append(QString("y:")).append(QString::number(angleY)));
        mw->label->setScaledContents(true);
        mw->label->setPixmap(pixmap1);
    }
    e->ignore();//这个东西非常重要，使得父类的事件处理函数可以被执行
}

void Qj1Widget::mouseMoveEvent(QMouseEvent *e)
{
//    if(isDrag && (e->buttons() && Qt::LeftButton)){
//        //move(e->globalPos() - position1);
//        isMove = true;
//        isRect = false;
//        MainWindow *mw = (MainWindow*)parentWidget()->parentWidget();
//        mw->widget2->CancelSelect();
//        //e->accept();
//        //position2 = e->pos();//e->globalPos() - this->pos();
//    }
//    e->ignore();
}

void Qj1Widget::mouseReleaseEvent(QMouseEvent *e)
{
    int posX = e->x();
    int posY = e->y();
    MainWindow *mw = (MainWindow*)parentWidget()->parentWidget();
     mw->widget5->isClicked = false;
//    if(isDrag && isMove){

//        if(posX>this->width())
//        {
//             x_position2 = e->x();
//        }
//        else if( posX< 0)
//        {
//           x_position2 =0;
//        }
//        else
//        {
//            x_position2 = e->x();
//        }
//       if( posY>this->height())
//        {
//           y_position2 = e->y();
//        }

//        else if ( posY < 0)
//        {
//            y_position2=0;
//        }
//       else
//       {
//            y_position2=posY;
//       }
//        //e->globalPos() - this->pos();
//        //qDebug()<<position2;
//        //
//        if(x_position2<=this->width() && y_position2<=this->height()){
//            if(position1.x()<x_position2 && position1.y()<y_position2)
//            {
//                newrect.x=getMatX(position1.x());
//                newrect.y=getMatY(position1.y());
//                newrect.width=getMatX(x_position2)-getMatX(position1.x());
//                newrect.height=getMatY(y_position2)-getMatY(position1.y());
//                qrect = QRect(newrect.x,newrect.y,newrect.width,newrect.height);
//            }
//            else if(position1.x()<x_position2 && position1.y()> y_position2)
//            {
//                newrect.x=getMatX(position1.x());
//                newrect.y=getMatY(y_position2);
//                newrect.width=getMatX(x_position2)-getMatX(position1.x());
//                newrect.height=getMatY(position1.y())-getMatY(y_position2);
//                qrect = QRect(newrect.x,newrect.y,newrect.width,newrect.height);
//            }
//            else if(position1.x()>x_position2 && position1.y()< y_position2)
//            {
//                newrect.x=getMatX(x_position2);
//                newrect.y=getMatY(position1.y());
//                newrect.width=getMatX(position1.x())-getMatX(x_position2);
//                newrect.height=getMatY(y_position2)-getMatY(position1.y());
//                qrect = QRect(newrect.x,newrect.y,newrect.width,newrect.height);
//            }
//            else if(position1.x()>x_position2 && position1.y()> y_position2)
//            {
//                newrect.x=getMatX(x_position2);
//                newrect.y=getMatY(y_position2);
//                newrect.width=getMatX(position1.x())-getMatX(x_position2);
//                newrect.height=getMatY(position1.y())-getMatY(y_position2);
////                newrect.width=position1.x()-x_position2;
////                newrect.height=position1.y()-y_position2;
//                qrect = QRect(newrect.x,newrect.y,newrect.width,newrect.height);
//            }


//            //mw->test();

//            //mw->drawRecOnPic2(mat,newrect);
////            rectangle(mat,newrect,Scalar(0,0,255),1,1,0);
////            cv::cvtColor(mat, mat, CV_BGR2RGB);
//            isRect = true;
//            mw->loadPictureToLabel1(isRect, qrect, mw->rgs[mw->rgsIndex].color, QRect(rectRegion.x, rectRegion.y, rectRegion.width, rectRegion.height), points);

//        }
//        else if(isRect){

//        }
//        else{
//            isDrag = false;
//            isMove = false;
//        }
 //   }
   if( e->button() == Qt::LeftButton){
  // if((!mw->isDefiningRegion) && (e->button() == Qt::LeftButton)){
        this->isClicked = true;
        mw->widget2->isClicked = false;
        if(mw->widget3->isClicked){
            this->isTo3 = true;
            mw->widget2->isTo3 = false;
            int xx = this->getMatX(posX);
            int yy = this->getMatY(posY);
            if(hasRect3){
                int height = mw->widget3->rect.height;
                int width = mw->widget3->rect.width;

                int xx2, yy2;
                if(xx-width/2 >= 0){
                    xx2 = xx- width/2;
                    //yy2 = 0;
                }
                else{
                    xx2 = xx- width/2 + this->pano.cols;
                    //yy2 = 0;
                }

                yy2 = yy-height/2;
                if(yy2 < 0){
                    yy2 = 0;
                }
                if(yy2+height > this->pano.rows){
                    yy2 = pano.rows-height;
                }


                this->rectan3 = Rect(xx2, yy2, width, height);
            }
            else{
                int height = this->mat.rows;
                int width = height * mw->widget3->width() / mw->widget3->height();
                hasRect3 = true;

                int xx2, yy2;
                if(xx-width/2 >= 0){
                    xx2 = xx- width/2;
                    yy2 = 0;
                }
                else{
                    xx2 = xx- width/2 + this->pano.cols;
                    yy2 = 0;
                }
                this->rectan3 = Rect(xx2, yy2, width, height);
            }

//            int height = this->mat.rows;
//            int width = height * mw->widget3->width() / mw->widget3->height();

//            int xx2, yy2;
//            if(xx-width/2 >= 0){
//                xx2 = xx- width/2;
//                yy2 = 0;
//            }
//            else{
//                xx2 = xx- width/2 + this->pano.cols;
//                yy2 = 0;
//            }
//            this->rectan3 = Rect(xx2, yy2, width, height);

            mw->widget3->setFrom(1);

            mw->widget3->setRect(rectan3);

            Mat mat1 = getTwoPano();
            Size dsize ;
            double scale = 1;
            dsize = Size(mat1.cols*scale,mat1.rows*scale);
            Mat image3;
            mat1(rectan3).copyTo(image3);//mw->QImageToMat(mw->aa);
            Mat image33 = Mat(dsize,CV_32S);
            cv::resize(image3, image33,dsize);
            mw->widget3->setMat(image33);
            mw->widget3->draw();


            mw->widget3->isClicked =false;
            mw->widget4->isClicked = false;
            mw->widget6->isClicked = false;
        }
        else if(mw->widget4->isClicked){
            this->isTo4 = true;
            mw->widget2->isTo4 = false;
            int xx = this->getMatX(posX);
            int yy = this->getMatY(posY);
            if(hasRect4){
                int height = mw->widget4->rect.height;
                int width = mw->widget4->rect.width;
                int xx2, yy2;
                if(xx-width/2 >= 0){
                    xx2 = xx- width/2;
                    //yy2 = 0;
                }
                else{
                    xx2 = xx- width/2 + this->pano.cols;
                    //yy2 = 0;
                }
                if((yy - height/2 >=0) && (yy + height/2 <= mat.rows)){
                    yy2 = yy - height / 2;
                }
                else if(yy - height/2 <=0){
                    yy2 = 0;
                }
                else if(yy + height/2 >= mat.rows){
                    yy2 = mat.rows / 2;
                }
                this->rectan4 = Rect(xx2, yy2, width, height);
}
            else{
                hasRect4 = true;
                int height = this->mat.rows/2;
                int width = height * mw->widget4->width() / mw->widget4->height();
                int xx2, yy2;
                if(xx-width/2 >= 0){
                    xx2 = xx- width/2;
                    //yy2 = 0;
                }
                else{
                    xx2 = xx- width/2 + this->pano.cols;
                    //yy2 = 0;
                }
                if((yy - height/2 >=0) && (yy + height/2 <= mat.rows)){
                    yy2 = yy - height / 2;
                }
                else if(yy - height/2 <=0){
                    yy2 = 0;
                }
                else if(yy + height/2 >= mat.rows){
                    yy2 = mat.rows / 2;
                }
                this->rectan4 = Rect(xx2, yy2, width, height);
            }
//            int height = this->mat.rows/2;
//            int width = height * mw->widget4->width() / mw->widget4->height();
//            int xx2, yy2;
//            if(xx-width/2 >= 0){
//                xx2 = xx- width/2;
//                //yy2 = 0;
//            }
//            else{
//                xx2 = xx- width/2 + this->pano.cols;
//                //yy2 = 0;
//            }
//            if((yy - height/2 >=0) && (yy + height/2 <= mat.rows)){
//                yy2 = yy - height / 2;
//            }
//            else if(yy - height/2 <=0){
//                yy2 = 0;
//            }
//            else if(yy + height/2 >= mat.rows){
//                yy2 = mat.rows / 2;
//            }
//            this->rectan4 = Rect(xx2, yy2, width, height);

            mw->widget4->setFrom(1);

            mw->widget4->setRect(rectan4);

            Mat mat1 = getTwoPano();
            Size dsize ;
            double scale = 1;
            dsize = Size(mat1.cols*scale,mat1.rows*scale);
            Mat image4;
            mat1(rectan4).copyTo(image4);//mw->QImageToMat(mw->aa);
            Mat image44 = Mat(dsize,CV_32S);
            cv::resize(image4, image44,dsize);
            mw->widget4->setMat(image44);
            mw->widget4->draw();

            mw->widget3->isClicked =false;
            mw->widget4->isClicked = false;
            mw->widget6->isClicked = false;
        }
        else if(mw->widget6->isClicked){
            this->isTo6 = true;
            mw->widget2->isTo6 = false;
            int xx = this->getMatX(posX);
            int yy = this->getMatY(posY);

            if(hasRect6){
                int height = mw->widget6->rect.height;
                int width = mw->widget6->rect.width;
                int xx2, yy2;
                if(xx-width/2 >= 0){
                    xx2 = xx- width/2;
                    //yy2 = 0;
                }
                else{
                    xx2 = xx- width/2 + this->pano.cols;
                    //yy2 = 0;
                }
                if((yy - height/2 >=0) && (yy + height/2 <= mat.rows)){
                    yy2 = yy - height / 2;
                }
                else if(yy - height/2 <=0){
                    yy2 = 0;
                }
                else if(yy + height/2 >= mat.rows){
                    yy2 = mat.rows / 2;
                }
                this->rectan6 = Rect(xx2, yy2, width, height);

            }
            else{
                hasRect6 = true;
                int height = this->mat.rows/2;
                int width = height * mw->widget6->width() / mw->widget6->height();
                int xx2, yy2;
                if(xx-width/2 >= 0){
                    xx2 = xx- width/2;
                    //yy2 = 0;
                }
                else{
                    xx2 = xx- width/2 + this->pano.cols;
                    //yy2 = 0;
                }
                if((yy - height/2 >=0) && (yy + height/2 <= mat.rows)){
                    yy2 = yy - height / 2;
                }
                else if(yy - height/2 <=0){
                    yy2 = 0;
                }
                else if(yy + height/2 >= mat.rows){
                    yy2 = mat.rows / 2;
                }
                this->rectan6 = Rect(xx2, yy2, width, height);

            }

//            int height = this->mat.rows/2;
//            int width = height * mw->widget6->width() / mw->widget6->height();
//            int xx2, yy2;
//            if(xx-width/2 >= 0){
//                xx2 = xx- width/2;
//                //yy2 = 0;
//            }
//            else{
//                xx2 = xx- width/2 + this->pano.cols;
//                //yy2 = 0;
//            }
//            if((yy - height/2 >=0) && (yy + height/2 <= mat.rows)){
//                yy2 = yy - height / 2;
//            }
//            else if(yy - height/2 <=0){
//                yy2 = 0;
//            }
//            else if(yy + height/2 >= mat.rows){
//                yy2 = mat.rows / 2;
//            }
//            this->rectan6 = Rect(xx2, yy2, width, height);

            mw->widget6->setFrom(1);

            mw->widget6->setRect(rectan6);

            Mat mat1 = getTwoPano();
            Size dsize ;
            double scale = 1;
            dsize = Size(mat1.cols*scale,mat1.rows*scale);
            Mat image6;
            mat1(rectan6).copyTo(image6);//mw->QImageToMat(mw->aa);
            Mat image66 = Mat(dsize,CV_32S);
            cv::resize(image6, image66,dsize);
            mw->widget6->setMat(image66);
            mw->widget6->draw();
            mw->widget3->isClicked =false;
            mw->widget4->isClicked = false;
            mw->widget6->isClicked = false;
        }
        else{

        }
    }
    qDebug()<<x_position2;
    qDebug()<<y_position2;
    isDrag = false;
    isMove = false;
    e->ignore();
}

//void Qj1Widget::paintEvent(QPaintEvent *){
//     paint->begin(this);
//     paint->setPen(QPen(Qt::red,4,Qt::SolidLine)); //设置画笔形式
//     paint->setBrush(QBrush(Qt::red,Qt::SolidPattern)); //设置画刷形式
//     paint->drawRect(20,20,160,160);
//     paint->end();
//}

Rect Qj1Widget::getRectan3(){
    return this->rectan3;
}

Rect Qj1Widget::getQRectan3(){
    return Rect(rectan3.x,rectan3.y,rectan3.width,rectan3.height);
}

Rect Qj1Widget::getRectan4(){
    return this->rectan4;
}

Rect Qj1Widget::getQRectan4(){
    return Rect(rectan4.x,rectan4.y,rectan4.width,rectan4.height);
}

Rect Qj1Widget::getRectan6(){
    return this->rectan6;
}

Rect Qj1Widget::getQRectan6(){
    return Rect(rectan6.x,rectan6.y,rectan6.width,rectan6.height);

}

//由Widget坐标的X获得图像中的X
double Qj1Widget::getMatX(double x){
    return x*mat.cols/this->width();
}

//由Widget坐标的Y获得图像中的Y
double Qj1Widget::getMatY(double y){
    return y*mat.rows/this->height();
}

//由图像中的X获得Widget中的X
double Qj1Widget::getWidgetX(double x){
    return x*this->width()/mat.cols;
}

//由图像中的Y获得Widget中的Y
double Qj1Widget::getWidgetY(double y){
    return y*this->height()/mat.rows;
}

double Qj1Widget::getDirectionX(double x){
    //double x = this->rectan.x;
    return 180*x/mat.cols -90;
}

double Qj1Widget::getDirectionY(double y){

    double yy = 20;
    //double y = this->rectan.y;
    return yy*y/mat.rows;

}

double Qj1Widget::getDirectionX3(){
    double x = this->rectan3.x;
    return 180*x/mat.cols -90;
}

double Qj1Widget::getDirectionY3(){

    double yy = 20;
    double y = this->rectan3.y;
    return yy*y/mat.rows;

}

double Qj1Widget::getDirectionX4(){
    double x = this->rectan4.x;
    return 180*x/mat.cols -90;
}

double Qj1Widget::getDirectionY4(){

    double yy = 20;
    double y = this->rectan4.y;
    return yy*y/mat.rows;

}

double Qj1Widget::getDirectionX6(){
    double x = this->rectan6.x;
    return 180*x/mat.cols -90;
}

double Qj1Widget::getDirectionY6(){

    double yy = 20;
    double y = this->rectan6.y;

    return yy*y/mat.rows;

}

double Qj1Widget::getDirectionX32(){
    double x = this->rectan3.x+this->rectan3.width;
    return 180*x/mat.cols -90;
}

double Qj1Widget::getDirectionY32(){

    double yy = 20;
    double y = this->rectan3.y+this->rectan3.height;
    return yy*y/mat.rows;

}

double Qj1Widget::getDirectionX42(){
    double x = this->rectan4.x+this->rectan4.width;
    return 180*x/mat.cols -90;
}

double Qj1Widget::getDirectionY42(){

    double yy = 20;
    double y = this->rectan4.y+this->rectan4.height;
    return yy*y/mat.rows;

}

double Qj1Widget::getDirectionX62(){
    double x = this->rectan6.x+this->rectan6.width;
    return 180*x/mat.cols -90;
}

double Qj1Widget::getDirectionY62(){

    double yy = 20;
    double y = this->rectan6.y+this->rectan6.height;

    return yy*y/mat.rows;

}

vector<MyObject> Qj1Widget::getSelectedObjects3(){
    vector<MyObject> os;
    int count = this->objs.size();
    for(int i = 0; i < count; i++){
        MyObject obj = objs[i];
        if(isObjSelected3(obj)){
            os.push_back(obj);
        }
    }

    for(int i = 0; i < count; i++){
        MyObject obj = objs[i];

        //已经出现过的，也跟上
        MainWindow *mw = (MainWindow*)parentWidget()->parentWidget();

        vector<MyObject> aos = mw->widget3->objs;
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

//选择的目标不能捎上，只能减少
vector<MyObject> Qj1Widget::getSelectedObjects4(){
    vector<MyObject> os;
    int count = this->objs.size();
    for(int i = 0; i < count; i++){
        MyObject obj = objs[i];
        if(isObjSelected4(obj)){
            os.push_back(obj);
        }

    }

    for(int i = 0; i < count; i++){
        MyObject obj = objs[i];

        //已经出现过的，也跟上
        MainWindow *mw = (MainWindow*)parentWidget()->parentWidget();

        vector<MyObject> aos = mw->widget4->objs;
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

//选择的目标不能捎上，只能减少
vector<MyObject> Qj1Widget::getSelectedObjects6(){
    vector<MyObject> os;
    int count = this->objs.size();
    for(int i = 0; i < count; i++){
        MyObject obj = objs[i];
        if(isObjSelected6(obj)){
            os.push_back(obj);
        }

    }

    for(int i = 0; i < count; i++){
        MyObject obj = objs[i];

        //已经出现过的，也跟上
        MainWindow *mw = (MainWindow*)parentWidget()->parentWidget();

        vector<MyObject> aos = mw->widget6->objs;
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
