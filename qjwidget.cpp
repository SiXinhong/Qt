
#include "qjwidget.h"

using namespace cv;
using namespace std;

QjWidget::QjWidget(QWidget *parent) :
    QWidget(parent){

        isDrag = false;

        To_Zhu= new QAction(tr("������ʾ��"), this);
        To_Ningshi = new QAction(tr("��������ʾ��"), this);
        //To_Tanchu = new QAction(tr("����������"),this);
        connect(To_Zhu, SIGNAL(triggered()), this, SLOT(ToZhu()));
        connect(To_Ningshi, SIGNAL(triggered()), this, SLOT(ToNingshi()));
        //connect(To_Tanchu, SIGNAL(triggered()), this, SLOT(ToTanchu()));
    }

void QjWidget::contextMenuEvent(QContextMenuEvent *){
    QCursor cur=this->cursor();
    QMenu *menu=new QMenu(this);
    menu->addAction(To_Zhu); //��Ӳ˵���1
    menu->addAction(To_Ningshi); //��Ӳ˵���2
    //menu->addAction(To_Tanchu);//��Ӳ˵���3
    menu->exec(cur.pos()); //���������
}
void QjWidget::ToZhu()
{
    qDebug()<<"������ʾ����";
}
//��������ʾ����ʾ�˵������¼�
void QjWidget::ToNingshi()
{
    qDebug()<<"��������ʾ����";
}
//������������ʾ�˵������¼�
//void ToTanchu(){
//    qDebug()<<"���������ڡ�";
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
