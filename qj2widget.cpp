
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

        Cancel_Select = new QAction(tr("ȡ��ѡ��"),this);
        To_Zhu= new QAction(tr("������ʾ��"), this);
        To_Ningshi = new QAction(tr("��������ʾ��"), this);
        //To_Tanchu = new QAction(tr("����������"),this);
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
    menu->addAction(Cancel_Select); //��Ӳ˵���1
    menu->addAction(To_Zhu); //��Ӳ˵���1
    menu->addAction(To_Ningshi); //��Ӳ˵���2
    //menu->addAction(To_Tanchu);//��Ӳ˵���3
    menu->exec(cur.pos()); //���������
}

void Qj2Widget::CancelSelect(){
    isRect = false;
}

void Qj2Widget::draw(){

    MainWindow *mw = (MainWindow*)parentWidget()->parentWidget();

    int count = this->objs.size();
    for (int i = 0; i < count;i++)
    {
        //�������box
        MyObject obj = objs[i];
        rectangle(mat,obj.getRect(),obj.getColor(),2,1,0);
        //���켣
        for(int ii = 0; ii < this->tracks.size(); ii++){
            MyObjectTrack track = this->tracks[ii];
            int id = track.getId();
            vector<Point> points = track.getTrack();
            if(id == obj.getID()){
                for(int iii = 0; iii < points.size(); iii++){
                    Point point = points[iii];
                    circle(mat, point, 2, obj.getColor(),-1,8,2);//��ͼ���л��������㣬2��Բ�İ뾶
                }
            }
        }
        //���������ĵ��λ��
        if(mw->isMubiao){
            int x = (int)(obj.getCenPoint().x);
            int y = (int)(obj.getCenPoint().y);
            QString tx = QString::number(x,10);
            QString ty = QString::number(y,10);
            QString tstr = "x="+tx+",y="+ty;
            string str = tstr.toStdString();
            //qDebug()<<tstr;
            Point p = Point(obj.getRect().x+obj.getRect().width,obj.getRect().y+obj.getRect().height);
            putText(mat,str,p,3,1,obj.getColor());
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
        //����ѡ�����ʹ��Ŀ���box��ѡ���֮��
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
    //qDebug()<<"������ʾ����";
    //��������ʾ����������Ŀ��
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
//��������ʾ����ʾ�˵������¼�
void Qj2Widget::ToNingshi()
{
    //qDebug()<<"������ʾ����";
    //����������ʾ����������Ŀ��
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
//������������ʾ�˵������¼�
//void ToTanchu(){
//    qDebug()<<"���������ڡ�";
//}

//void QjWidget::mouseClickEvent(QMouseEvent *e){

//}

void Qj2Widget::mousePressEvent(QMouseEvent *e)
{
    qDebug()<<"���ѹ���¼�����qj1widget";
    if(e->button() == Qt::LeftButton)
    {
        isDrag = true;
        //isRect = false;
        position1 = e->pos();//e->globalPos() - this->pos();
        //e->accept();
        qDebug()<<position1;
    }
    e->ignore();//��������ǳ���Ҫ��ʹ�ø�����¼����������Ա�ִ��
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

//��Widget�����X���ͼ���е�X
double Qj2Widget::getMatX(double x){
    return x*mat.cols/this->width();
}

//��Widget�����Y���ͼ���е�Y
double Qj2Widget::getMatY(double y){
    return y*mat.rows/this->height();
}

//��ͼ���е�X���Widget�е�X
double Qj2Widget::getWidgetX(double x){
    return x*this->width()/mat.cols;
}

//��ͼ���е�Y���Widget�е�Y
double Qj2Widget::getWidgetY(double y){
    return y*this->height()/mat.rows;
}

double Qj2Widget::getDirectionX(){
    double x = this->rectan.x;
    return 180*x/mat.cols +90;
}

double Qj2Widget::getDirectionY(){

    double yy = 20;
    double y = this->rectan.y;
    return yy*y/mat.rows;

}

double Qj2Widget::getDirectionX2(){
    double x = this->rectan.x+this->rectan.width;
    return 180*x/mat.cols +90;
}

double Qj2Widget::getDirectionY2(){

    double yy = 20;
    double y = this->rectan.y+this->rectan.height;
    return yy*y/mat.rows;

}
