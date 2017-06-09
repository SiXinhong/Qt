
#include "qjwidget.h"

QjWidget::QjWidget(QWidget *parent) :
    QWidget(parent)
    //ui(new Ui::Widget)
    {
    //ui->setupUi(this);
    To_Zhu= new QAction(tr("������ʾ��"), this);
    To_Ningshi = new QAction(tr("��������ʾ��"), this);
    connect(To_Zhu, SIGNAL(triggered()), this, SLOT(ToZhu()));
    connect(To_Ningshi, SIGNAL(triggered()), this, SLOT(ToNingshi()));
    }

void QjWidget::contextMenuEvent(QContextMenuEvent *){
    QCursor cur=this->cursor();
    QMenu *menu=new QMenu(this);
    menu->addAction(To_Zhu); //��Ӳ˵���1
    menu->addAction(To_Ningshi); //��Ӳ˵���2
    menu->exec(cur.pos()); //���������
}

