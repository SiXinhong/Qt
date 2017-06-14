
#include "qjwidget.h"

using namespace cv;
using namespace std;

QjWidget::QjWidget(QWidget *parent) :
    QWidget(parent){

        isDrag = false;

        To_Zhu= new QAction(tr("到主显示区"), this);
        To_Ningshi = new QAction(tr("到凝视显示区"), this);
        //To_Tanchu = new QAction(tr("到弹出窗口"),this);
        connect(To_Zhu, SIGNAL(triggered()), this, SLOT(ToZhu()));
        connect(To_Ningshi, SIGNAL(triggered()), this, SLOT(ToNingshi()));
        //connect(To_Tanchu, SIGNAL(triggered()), this, SLOT(ToTanchu()));
    }

void QjWidget::contextMenuEvent(QContextMenuEvent *){
    QCursor cur=this->cursor();
    QMenu *menu=new QMenu(this);
    menu->addAction(To_Zhu); //添加菜单项1
    menu->addAction(To_Ningshi); //添加菜单项2
    //menu->addAction(To_Tanchu);//添加菜单项3
    menu->exec(cur.pos()); //关联到光标
}
void QjWidget::ToZhu()
{
    qDebug()<<"到主显示区。";
}
//到凝视显示区显示菜单处理事件
void QjWidget::ToNingshi()
{
    qDebug()<<"到凝视显示区。";
}
//到弹出窗口显示菜单处理事件
//void ToTanchu(){
//    qDebug()<<"到弹出窗口。";
//}

//void QjWidget::mouseClickEvent(QMouseEvent *e){

//}

void QjWidget::mousePressEvent(QMouseEvent *e)
{
    if(e->button() == Qt::LeftButton)
    {
        isDrag = true;
        position1 = e->globalPos() - this->pos();
        e->accept();
        qDebug()<<position1;
    }
}

void QjWidget::mouseMoveEvent(QMouseEvent *e)
{
    if(isDrag && (e->buttons() && Qt::LeftButton)){
        //move(e->globalPos() - position1);
        e->accept();
    }
}

void QjWidget::mouseReleaseEvent(QMouseEvent *e)
{
    isDrag = false;
    position2 = e->globalPos() - this->pos();
    qDebug()<<position2;
    rectan = Rectan(position1.x(),position1.y(),position2.x()-position1.x(),position2.y()-position1.y());
}
