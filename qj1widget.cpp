
#include "qj1widget.h"
#include "mainwindow.h"

using namespace cv;
using namespace std;

Qj1Widget::Qj1Widget(QWidget *parent) :
    QWidget(parent){
        isDrag = false;

        To_Zhu= new QAction(tr("到主显示区"), this);
        To_Ningshi = new QAction(tr("到凝视显示区"), this);
        //To_Tanchu = new QAction(tr("到弹出窗口"),this);
        connect(To_Zhu, SIGNAL(triggered()), this, SLOT(ToZhu()));
        connect(To_Ningshi, SIGNAL(triggered()), this, SLOT(ToNingshi()));
        //connect(To_Tanchu, SIGNAL(triggered()), this, SLOT(ToTanchu()));
    }

void Qj1Widget::setMat(Mat m){
    mat = m;
}

Mat Qj1Widget::getMat(){
    return mat;
}

void Qj1Widget::contextMenuEvent(QContextMenuEvent *){
    QCursor cur=this->cursor();
    QMenu *menu=new QMenu(this);
    menu->addAction(To_Zhu); //添加菜单项1
    menu->addAction(To_Ningshi); //添加菜单项2
    //menu->addAction(To_Tanchu);//添加菜单项3
    menu->exec(cur.pos()); //关联到光标
}

void Qj1Widget::ToZhu()
{
    qDebug()<<"到主显示区。";
    MainWindow *mw = (MainWindow*)parentWidget();
    mw->test();
}
//到凝视显示区显示菜单处理事件
void Qj1Widget::ToNingshi()
{
    qDebug()<<"到凝视显示区。";
}
//到弹出窗口显示菜单处理事件
//void ToTanchu(){
//    qDebug()<<"到弹出窗口。";
//}

//void QjWidget::mouseClickEvent(QMouseEvent *e){

//}

void Qj1Widget::mousePressEvent(QMouseEvent *e)
{
    if(e->button() == Qt::LeftButton)
    {
        isDrag = true;
        position1 = e->globalPos() - this->pos();
        e->accept();
        qDebug()<<position1;
    }
}

void Qj1Widget::mouseMoveEvent(QMouseEvent *e)
{
    if(isDrag && (e->buttons() && Qt::LeftButton)){
        //move(e->globalPos() - position1);
        e->accept();
    }
}

void Qj1Widget::mouseReleaseEvent(QMouseEvent *e)
{
    if(isDrag){
        position2 = e->globalPos() - this->pos();
        qDebug()<<position2;
        //rectan = Rect(position1.x(),position1.y(),position2.x()-position1.x(),position2.y()-position1.y());

        string imageurl="./s1/1.bmp";
        Mat mat1 =imread(imageurl);

        Rect rectan;
        rectan.x=1690;// = Rect(1490,250,100,100);
        rectan.y=350;
        rectan.width=200;
        rectan.height=200;


        MainWindow *mw = (MainWindow*)parentWidget()->parentWidget();
        //mw->test();

        mw->drawRecOnPic2(mat1,rectan);
        cv::cvtColor(mat1, mat1, CV_BGR2RGB);
        mw->loadPictureToLabel1();
    }
    isDrag = false;
}
