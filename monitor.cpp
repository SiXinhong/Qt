#include "monitor.h"
#include <QColorDialog>
#include <QColor>
#include <QInputDialog>

Monitor::Monitor(MainWindow *mw) :
    QMainWindow()
{
    addMyToolBar();
   this->mw = mw;
    qj1= mw->widget1;
    qj2= mw->widget2;
    z = mw->widget3;
    n1 = mw->widget4;
    n2 = mw->widget6;
    cenWidget = 0;
    layout = 0;
}



void Monitor::addMyToolBar(){


    QToolButton *qj1Widget = new QToolButton(this);
    QToolButton *qj2Widget = new QToolButton(this);
    QToolButton *zWidget = new QToolButton(this);
    QToolButton *nWidget1 = new QToolButton(this);
    QToolButton *nWidget2 = new QToolButton(this);
    QToolButton *exit = new QToolButton(this);

    qj1Widget->setText("ȫ����ʾ��1");
    qj2Widget->setText("ȫ����ʾ��2");
    zWidget->setText("����ʾ��");
    nWidget1->setText("������ʾ��1");
    nWidget2->setText("������ʾ��2");
    exit->setIcon(QPixmap("./icon/18.png"));

    qj1Widget->setToolTip("qj1");
    qj2Widget->setToolTip("qj2");
    zWidget->setToolTip("z");
    nWidget1->setToolTip("n1");
    nWidget2->setToolTip("n2");

    connect(qj1Widget,SIGNAL(clicked()),this,SLOT(widgetShow()));
    connect(qj2Widget,SIGNAL(clicked()),this,SLOT(widgetShow()));
    connect(zWidget,SIGNAL(clicked()),this,SLOT(widgetShow()));
    connect(nWidget1,SIGNAL(clicked()),this,SLOT(widgetShow()));
    connect(nWidget2,SIGNAL(clicked()),this,SLOT(widgetShow()));
    connect(exit,SIGNAL(clicked()),this,SLOT(exitFunction()));

    QHBoxLayout *vbox = new QHBoxLayout;
    vbox->addWidget(qj1Widget);
    vbox->addWidget(qj2Widget);
    vbox->addWidget(zWidget);
    vbox->addWidget(nWidget1);
    vbox->addWidget(nWidget2);
    vbox->addWidget(exit);

    QGroupBox *group = new QGroupBox(this);
    group->setLayout(vbox);

    mainToolBar = addToolBar("RegionGroups");
    mainToolBar->addWidget(group);


}

void Monitor::widgetShow(){
    QObject* obj = sender();
    QToolButton* button = dynamic_cast<QToolButton*>(obj);
    QString tipOfButton=button->toolTip();
    int size = 0;

    if(tipOfButton == "qj1"){
        ite = qj1->rg.rss.begin();
        end = qj1->rg.rss.end();
        widget = 1;
        size = qj1->rg.rss.size();
    }else if(tipOfButton == "qj2"){
        ite = qj2->rg.rss.begin();
        end = qj2->rg.rss.end();
        widget = 2;
        size = qj2->rg.rss.size();
    }else if(tipOfButton == "z"){
        ite = z->rg.rss.begin();
        end = z->rg.rss.end();
        widget = 3;
        size = z->rg.rss.size();
    }else if(tipOfButton =="n1"){
        ite = n1->rg.rss.begin();
        end = n1->rg.rss.end();
        widget = 4;
        size = n1->rg.rss.size();
    }else if(tipOfButton =="n2"){
        ite = n2->rg.rss.begin();
        end = n2->rg.rss.end();
        widget = 5;
        size = n2->rg.rss.size();
    }


    QGridLayout* old=layout;
    layout=new QGridLayout;

    QWidget *oldWidget = cenWidget;
    cenWidget = new QWidget(this);
    QDesktopWidget* desktopWidget = QApplication::desktop();
    QRect screenRect = desktopWidget->screenGeometry();
    int y = screenRect.height()/10;

    if(size == 0){
        QLabel *label = new QLabel(QString("δ����������"),cenWidget);
        layout->addWidget(label,0,0);
    }

    int i=0;
    for(;ite!=end;ite++){
        //��ʹ��QLabel��ԭ����QLabelû��click�ź�
        QToolButton *label=new QToolButton(cenWidget);
        label->setText(QString("��������飺").append(ite.value()[0].name));
        label->setStyleSheet("border-style: flat;");//ȥ���߿򣬿�������label�������ǰ�ť
        label->setToolTip(ite.key());
        connect(label,SIGNAL(clicked()),this,SLOT(onClickName()));

        QToolButton *regionGroup = new QToolButton(cenWidget);
        regionGroup->setText(QString("���ظü��������"));
        connect(regionGroup,SIGNAL(clicked()),this,SLOT(groupShow()));

        QToolButton *active = new QToolButton(cenWidget);
        active->setText(QString("����"));
        connect(active,SIGNAL(clicked()),this,SLOT(isActive()));

        QToolButton *attributes = new QToolButton(cenWidget);
        attributes->setText(QString("��ɫ"));
        attributes->setToolTip(ite.key());
        Scalar color=ite.value().at(0).color;
        attributes->setStyleSheet(QString("background-color: rgb(%1, %2, %3);").arg(color.val[2]).arg(color.val[1]).arg(color.val[0]));
        connect(attributes,SIGNAL(clicked()),this,SLOT(attributesModify()));

        layout->addWidget(label,i,0);
        layout->addWidget(regionGroup,i,1);
        layout->addWidget(active,i,2);
        layout->addWidget(attributes,i,3);
        i++;
    }
    if(old!=0){
        delete old;
    }
    if(oldWidget!=0){
        QList<QWidget*> btns=oldWidget->findChildren<QWidget*>();
        foreach (QWidget* btn, btns)
        {
            delete btn;
        }
        oldWidget->repaint();
        delete oldWidget;
    }
    cenWidget->setLayout(layout);
    this->setCentralWidget(cenWidget);
}

void Monitor::groupShow(){

    QObject* obj = sender();
       QToolButton* button = dynamic_cast<QToolButton*>(obj);
       if( button->text()== "���ظü��������"){
            button->setText("��ʾ�ü��������");
       }else if(button->text()=="��ʾ�ü��������"){
           button->setText("���ظü��������");
       }

    if(widget ==1){
        qj1->isShow = !qj1->isShow;
    }else if(widget ==2){
        qj2->isShow = !qj2->isShow;
    }else if (widget ==3){
        z->isShow = !z->isShow;
    }else if(widget ==4){
        n1->isShow = !n1->isShow;
    }else if(widget ==5){
        n2->isShow = !n2->isShow;
    }
}

void Monitor::isActive(){

    QObject* obj = sender();
       QToolButton* button = dynamic_cast<QToolButton*>(obj);
       if( button->text()== "ȡ������"){
            button->setText("����");
       }else if(button->text()=="����"){
           button->setText("ȡ������");
       }

    if(widget ==1){
        qj1->isGaojing = !qj1->isGaojing;
    }else if(widget ==2){
        qj2->isGaojing = !qj2->isGaojing;
    }else if (widget ==3){
        z->isGaojing = !z->isGaojing;
    }else if(widget ==4){
        n1->isGaojing = !n1->isGaojing;
    }else if(widget ==5){
        n2->isGaojing = !n2->isGaojing;
    }
}

void Monitor::attributesModify(){
    QObject* obj = sender();
    QToolButton* button = dynamic_cast<QToolButton*>(obj);
    QString tipOfButton=button->toolTip();
    QColor color = QColorDialog::getColor(Qt::black,this);

    button->setStyleSheet(QString("background-color: rgb(%1, %2, %3);").arg(color.red()).arg(color.green()).arg(color.blue()));

    QMap< QString,vector<Region> > ::iterator iter;
    if(1 == widget){
        iter = qj1->rg.rss.find(tipOfButton);
    }else if(2 == widget){
        iter = qj2->rg.rss.find(tipOfButton);
    }else if(3 == widget){
        iter = z->rg.rss.find(tipOfButton);
    }else if(4 == widget){
        iter = n1->rg.rss.find(tipOfButton);
    }else if(5 == widget){
        iter = n2->rg.rss.find(tipOfButton);
    }
    Scalar c(color.blue(),color.green(),color.red());
    for(int i=0;i<iter.value().size();i++){
        iter.value()[i].color = c;
    }
}

void Monitor::exitFunction(){
    this->close();
    mw->isDefiningRegion = false;
}

void Monitor::onClickName(){
    QObject* obj = sender();
    QToolButton* button = dynamic_cast<QToolButton*>(obj);
    QString tipOfButton=button->toolTip();

    QString newName = QInputDialog::getText(this,QString("�������µ��������֣���ȷ���޸�"),QString("������"));

    if(newName == "" || newName == tipOfButton){
        return;
    }
    button->setText(QString("��������飺").append(newName));
    QMap< QString,vector<Region> > ::iterator iter;
    if(1 == widget){
        iter = qj1->rg.rss.find(tipOfButton);
        iter.value()[0].name=newName;
    }else if(2 == widget){
        iter = qj2->rg.rss.find(tipOfButton);
        iter.value()[0].name=newName;
    }else if(3 == widget){
        iter = z->rg.rss.find(tipOfButton);
        iter.value()[0].name=newName;
    }else if(4 == widget){
        iter = n1->rg.rss.find(tipOfButton);
        iter.value()[0].name=newName;
    }else if(5 == widget){
        iter = n2->rg.rss.find(tipOfButton);
        iter.value()[0].name=newName;
    }
}
