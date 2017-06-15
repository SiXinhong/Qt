
#include "qj2widget.h"
#include "mainwindow.h"

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
    }

void Qj2Widget::setMat(Mat m){
    mat = m;
    if(isRect){
        MainWindow *mw = (MainWindow*)parentWidget()->parentWidget();
        //mw->test();

        mw->drawRecOnPic2(mat,rectan);
        cv::cvtColor(mat, mat, CV_BGR2RGB);
        mw->loadPictureToLabel1();
        isRect = true;
    }
}

Mat Qj2Widget::getMat(){
    return mat;
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

void Qj2Widget::ToZhu()
{
    qDebug()<<"������ʾ����";
    MainWindow *mw = (MainWindow*)parentWidget()->parentWidget();
    mw->test();
}
//��������ʾ����ʾ�˵������¼�
void Qj2Widget::ToNingshi()
{
    qDebug()<<"��������ʾ����";
}
//������������ʾ�˵������¼�
//void ToTanchu(){
//    qDebug()<<"���������ڡ�";
//}

//void QjWidget::mouseClickEvent(QMouseEvent *e){

//}

void Qj2Widget::mousePressEvent(QMouseEvent *e)
{
    if(e->button() == Qt::LeftButton)
    {
        isDrag = true;
        //isRect = false;
        position1 = e->pos();//e->globalPos() - this->pos();
        e->accept();
        qDebug()<<position1;
    }
}

void Qj2Widget::mouseMoveEvent(QMouseEvent *e)
{
    if(isDrag && (e->buttons() && Qt::LeftButton)){
        //move(e->globalPos() - position1);
        isMove = true;
        isRect = false;
        MainWindow *mw = (MainWindow*)parentWidget()->parentWidget();
        mw->widget1->CancelSelect();
        e->accept();
        //position2 = e->pos();//e->globalPos() - this->pos();
    }
}

void Qj2Widget::mouseReleaseEvent(QMouseEvent *e)
{
    if(isDrag && isMove){
        position2 = e->pos();//e->globalPos() - this->pos();
        qDebug()<<position2;
        //rectan = Rect(position1.x(),position1.y(),position2.x()-position1.x(),position2.y()-position1.y());

        //string imageurl="./s1/1.bmp";
        //Mat mat1 =imread(imageurl);

        //Rect rectan;
//        rectan.x=1690;// = Rect(1490,250,100,100);
//        rectan.y=350;
//        rectan.width=200;
//        rectan.height=200;
        rectan.x=getMatX(position1.x());// = Rect(1490,250,100,100);
        rectan.y=getMatY(position1.y());
        rectan.width=getMatX(position2.x())-getMatX(position1.x());
        rectan.height=getMatY(position2.y())-getMatY(position1.y());

        MainWindow *mw = (MainWindow*)parentWidget()->parentWidget();
        //mw->test();

        mw->drawRecOnPic2(mat,rectan);
        cv::cvtColor(mat, mat, CV_BGR2RGB);
        mw->loadPictureToLabel2();
        isRect = true;
    }
    isDrag = false;
    isMove = false;
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
