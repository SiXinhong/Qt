
#include "qjwidget.h"

QjWidget::QjWidget(QWidget *parent) :
    QWidget(parent){
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
