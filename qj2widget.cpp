
#include "qj2widget.h"
#include "mainwindow.h"
#include "myobject.h"
#include "myobjecttrack.h"


using namespace cv;
using namespace std;

Qj2Widget::Qj2Widget(QWidget *parent) :
    QWidget(parent){
        isDrag = false;
        isMove = false;
        isRect = false;

        Cancel_Select = new QAction(tr("取消选择"),this);
        To_Zhu= new QAction(tr("到主显示区"), this);
        To_Ningshi = new QAction(tr("到凝视显示区"), this);
        //To_Tanchu = new QAction(tr("到弹出窗口"),this);
        connect(Cancel_Select, SIGNAL(triggered()), this, SLOT(CancelSelect()));
        connect(To_Zhu, SIGNAL(triggered()), this, SLOT(ToZhu()));
        connect(To_Ningshi, SIGNAL(triggered()), this, SLOT(ToNingshi()));
        //connect(To_Tanchu, SIGNAL(triggered()), this, SLOT(ToTanchu()));

        rectan = Rect(1490,250,100,100);
        newrect = Rect(1490,250,100,100);
    }

void Qj2Widget::setMat(Mat m){
    mat = m;
    if(isRect){
        MainWindow *mw = (MainWindow*)parentWidget()->parentWidget();
        //mw->test();

        rectangle(mat,newrect,Scalar(0,0,255),1,1,0);
        cv::cvtColor(mat, mat, CV_BGR2RGB);
        mw->loadPictureToLabel2();
        isRect = true;
    }
}

Mat Qj2Widget::getMat(){
    return mat;
}

void Qj2Widget::setObjects(vector<MyObject> os){
    this->objs = os;
}

vector<MyObject> Qj2Widget::getObjects(){
    return this->objs;
}

void Qj2Widget::setTracks(vector<MyObjectTrack> ts){
    this->tracks =ts;
}

vector<MyObjectTrack> Qj2Widget::getTracks(){
    return this->tracks;
}

void Qj2Widget::contextMenuEvent(QContextMenuEvent *){
    QCursor cur=this->cursor();
    QMenu *menu=new QMenu(this);
    menu->addAction(Cancel_Select); //添加菜单项1
    menu->addAction(To_Zhu); //添加菜单项1
    menu->addAction(To_Ningshi); //添加菜单项2
    //menu->addAction(To_Tanchu);//添加菜单项3
    menu->exec(cur.pos()); //关联到光标
}

void Qj2Widget::CancelSelect(){
    isRect = false;
}

void Qj2Widget::draw(){

    MainWindow *mw = (MainWindow*)parentWidget()->parentWidget();

    int count = this->objs.size();
    for (int i = 0; i < count;i++)
    {
        //画对象的box
        MyObject obj = objs[i];
        rectangle(mat,obj.getRect(),obj.getColor(),2,1,0);
        //画轨迹
        for(int ii = 0; ii < this->tracks.size(); ii++){
            MyObjectTrack track = this->tracks[ii];
            int id = track.getId();
            vector<Point> points = track.getTrack();
            if(id == obj.getID()){
                for(int iii = 0; iii < points.size(); iii++){
                    Point point = points[iii];
                    circle(mat, point, 2, obj.getColor(),-1,8,2);//在图像中画出特征点，2是圆的半径
                }
            }
        }

        cv::cvtColor(mat, mat, CV_BGR2RGB);
    }
    cv::cvtColor(mat, mat, CV_BGR2RGB);
    mw->imgLabel2 = mw->MatToQImage(mat,mw->imgLabel2);
    mw->loadPictureToLabel2();

}

boolean Qj2Widget::isObjSelected(MyObject obj){
    boolean isSelected = false;
    if((obj.getCenPoint().x>this->rectan.x) && (obj.getCenPoint().y>this->rectan.y) && (obj.getCenPoint().x<this->rectan.x+this->rectan.width) && (obj.getCenPoint().y<this->rectan.y+this->rectan.height)){
        //调整选择框以使得目标的box在选择框之内
        if(obj.getRect().x<this->rectan.x){
            this->rectan.width = this->rectan.width + this->rectan.x - obj.getRect().x + 5;
            this->rectan.x = obj.getRect().x - 5;
        }
        if(obj.getRect().y<this->rectan.y){
            this->rectan.height = this->rectan.height + this->rectan.y - obj.getRect().y + 5;
            this->rectan.y = obj.getRect().y - 5;
        }
        if(obj.getRect().x+obj.getRect().width>this->rectan.x){
            this->rectan.width = this->rectan.width + obj.getRect().x + obj.getRect().width - this->rectan.x + 5;
            this->rectan.x = obj.getRect().x +obj.getRect().width + 5;
        }
        if(obj.getRect().y+obj.getRect().height>this->rectan.y){
            this->rectan.height = this->rectan.height + obj.getRect().y + obj.getRect().height- this->rectan.y+ 5;
            this->rectan.y = obj.getRect().y +obj.getRect().height+ 5;
        }
        isSelected = true;
    }
    return isSelected;
}

void Qj2Widget::ToZhu()
{
    //qDebug()<<"到主显示区。";
    //更新主显示区所包含的目标
    vector<MyObject> objs3;
    int count = this->objs.size();
    for(int i = 0; i < count; i++){
        MyObject obj = objs[i];
        if(isObjSelected(obj)){
            objs3.push_back(obj);
        }
    }

    MainWindow *mw = (MainWindow*)parentWidget()->parentWidget();

    mw->widget3->setObjects(objs3);

    mw->widget3->setFrom(2);
    this->rectan.x = this->newrect.x;
    this->rectan.y = this->newrect.y;
    this->rectan.width = this->newrect.width;
    this->rectan.height = this->newrect.height;

    Mat mat = getMat();
    Size dsize ;
    double scale = 1;
    dsize = Size(mat.cols*scale,mat.rows*scale);
    Mat image11 = Mat(dsize,CV_32S);
    cv::resize(mat, image11,dsize);
    mw->img = QImage((const unsigned char*)(image11.data),image11.cols,mat.rows, image11.cols*image11.channels(),  QImage::Format_RGB888);

    //vector<Rectan> rectans;
    mw->aa=(&(mw->img))->copy(getQRectan());
    Mat image3 = mw->QImageToMat(mw->aa);
    Mat image33 = Mat(dsize,CV_32S);
    cv::resize(image3, image33,dsize);
    mw->widget3->setMat(image33);
    mw->widget3->draw();

    isRect = false;
}
//到凝视显示区显示菜单处理事件
void Qj2Widget::ToNingshi()
{
    //qDebug()<<"到主显示区。";
    //更新凝视显示区所包含的目标
    vector<MyObject> objs4;
    int count = this->objs.size();
    for(int i = 0; i < count; i++){
        MyObject obj = objs[i];
        if(isObjSelected(obj)){
            objs4.push_back(obj);
        }
    }

    MainWindow *mw = (MainWindow*)parentWidget()->parentWidget();

    mw->widget4->setObjects(objs4);

    mw->widget4->setFrom(2);
    this->rectan.x = this->newrect.x;
    this->rectan.y = this->newrect.y;
    this->rectan.width = this->newrect.width;
    this->rectan.height = this->newrect.height;

    Mat mat = getMat();
    Size dsize ;
    double scale = 1;
    dsize = Size(mat.cols*scale,mat.rows*scale);
    Mat image11 = Mat(dsize,CV_32S);
    cv::resize(mat, image11,dsize);
    mw->img = QImage((const unsigned char*)(image11.data),image11.cols,mat.rows, image11.cols*image11.channels(),  QImage::Format_RGB888);

    //vector<Rectan> rectans;
    mw->aa=(&(mw->img))->copy(getQRectan());
    Mat image4 = mw->QImageToMat(mw->aa);
    Mat image44 = Mat(dsize,CV_32S);
    cv::resize(image4, image44,dsize);
    mw->widget4->setMat(image44);
    mw->widget4->draw();
    isRect = false;
}
//到弹出窗口显示菜单处理事件
//void ToTanchu(){
//    qDebug()<<"到弹出窗口。";
//}

//void QjWidget::mouseClickEvent(QMouseEvent *e){

//}

void Qj2Widget::mousePressEvent(QMouseEvent *e)
{
    qDebug()<<"鼠标压下事件来自qj1widget";
    if(e->button() == Qt::LeftButton)
    {
        isDrag = true;
        //isRect = false;
        position1 = e->pos();//e->globalPos() - this->pos();
        //e->accept();
        qDebug()<<position1;
    }
    e->ignore();//这个东西非常重要，使得父类的事件处理函数可以被执行
}

void Qj2Widget::mouseMoveEvent(QMouseEvent *e)
{
    if(isDrag && (e->buttons() && Qt::LeftButton)){
        //move(e->globalPos() - position1);
        isMove = true;
        isRect = false;
        MainWindow *mw = (MainWindow*)parentWidget()->parentWidget();
        mw->widget2->CancelSelect();
        //e->accept();
        //position2 = e->pos();//e->globalPos() - this->pos();
    }
    e->ignore();
}

void Qj2Widget::mouseReleaseEvent(QMouseEvent *e)
{

    if(isDrag && isMove){
        position2 = e->pos();//e->globalPos() - this->pos();
        qDebug()<<position2;
        //
        if(position2.x()<=this->width() && position2.y()<=this->height()){
            //qrectan = QRect(position1.x(),position1.y(),position2.x()-position1.x(),position2.y()-position1.y());

            newrect.x=getMatX(position1.x());// = Rect(1490,250,100,100);
            newrect.y=getMatY(position1.y());
            newrect.width=getMatX(position2.x())-getMatX(position1.x());
            newrect.height=getMatY(position2.y())-getMatY(position1.y());

            MainWindow *mw = (MainWindow*)parentWidget()->parentWidget();
            //mw->test();

            rectangle(mat,newrect,Scalar(0,0,255),1,1,0);
            cv::cvtColor(mat, mat, CV_BGR2RGB);
            mw->loadPictureToLabel2();
            isRect = true;
        }
        else if(isRect){

        }
        else{
            isDrag = false;
            isMove = false;
        }
    }
    isDrag = false;
    isMove = false;
    e->ignore();
}

Rect Qj2Widget::getRectan(){
    return this->rectan;
}

QRect Qj2Widget::getQRectan(){
    return QRect(rectan.x+2,rectan.y+2,rectan.width-2,rectan.height-2);
}

//由Widget坐标的X获得图像中的X
double Qj2Widget::getMatX(double x){
    return x*mat.cols/this->width();
}

//由Widget坐标的Y获得图像中的Y
double Qj2Widget::getMatY(double y){
    return y*mat.rows/this->height();
}

//由图像中的X获得Widget中的X
double Qj2Widget::getWidgetX(double x){
    return x*this->width()/mat.cols;
}

//由图像中的Y获得Widget中的Y
double Qj2Widget::getWidgetY(double y){
    return y*this->height()/mat.rows;
}

double Qj2Widget::getDirectionX(){
    double x = this->rectan.x;
    return 180*x/mat.cols +90;
}

double Qj2Widget::getDirectionY(){

    double yy = 10;
    double y = this->rectan.y;
    return yy*y/mat.rows;

}
