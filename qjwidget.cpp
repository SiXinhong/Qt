
#include "qjwidget.h"

QjWidget::QjWidget(QWidget *parent) :
    QWidget(parent)
    //ui(new Ui::Widget)
    {
    //ui->setupUi(this);
    To_Zhu= new QAction(tr("到主显示区"), this);
    To_Ningshi = new QAction(tr("到凝视显示区"), this);
    connect(To_Zhu, SIGNAL(triggered()), this, SLOT(ToZhu()));
    connect(To_Ningshi, SIGNAL(triggered()), this, SLOT(ToNingshi()));
    }

void QjWidget::contextMenuEvent(QContextMenuEvent *){
    QCursor cur=this->cursor();
    QMenu *menu=new QMenu(this);
    menu->addAction(To_Zhu); //添加菜单项1
    menu->addAction(To_Ningshi); //添加菜单项2
    menu->exec(cur.pos()); //关联到光标
}

