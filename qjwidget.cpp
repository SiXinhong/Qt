
#include "qjwidget.h"

QjWidget::QjWidget(QWidget *parent) :
    QWidget(parent){
        To_Zhu= new QAction(tr("������ʾ��"), this);
        To_Ningshi = new QAction(tr("��������ʾ��"), this);
        To_Tanchu = new QAction(tr("����������"),this);
        connect(To_Zhu, SIGNAL(triggered()), this, SLOT(ToZhu()));
        connect(To_Ningshi, SIGNAL(triggered()), this, SLOT(ToNingshi()));
        connect(To_Tanchu, SIGNAL(triggered()), this, SLOT(ToTanchu()));
    }

void QjWidget::contextMenuEvent(QContextMenuEvent *){
    QCursor cur=this->cursor();
    QMenu *menu=new QMenu(this);
    menu->addAction(To_Zhu); //��Ӳ˵���1
    menu->addAction(To_Ningshi); //��Ӳ˵���2
    menu->addAction(To_Tanchu);//��Ӳ˵���3
    menu->exec(cur.pos()); //���������
}

