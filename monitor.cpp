#include "monitor.h"
#include <QColorDialog>
#include <QColor>
#include <QInputDialog>
#include <QDebug>

Monitor::Monitor(MainWindow *mw) :
    QMainWindow()
{
    //addMyToolBar();
    cenWidget = 0;
    layout = 0;
    this->mw = mw;


}

//Monitor::~Monitor(){
//    if(detailsOfRG){delete detailsOfRG;}
//    if(layout){delete layout;}
//    if(cenWidget){delete cenWidget;}
//}
void Monitor::widgetShow(){
    QGridLayout* old=layout;
    layout=new QGridLayout;
    QWidget *oldWidget = cenWidget;
    cenWidget = new QWidget(this);

    QToolButton *create = new QToolButton(cenWidget);
    create->setText("创建监控区域组");
    connect(create,SIGNAL(clicked()),this,SLOT(createRG()));

    if(mw->rgs.size() <= 1){
        QLabel *label = new QLabel(QString("未定义监控区域"),cenWidget);
        layout->addWidget(label,0,0);
    }


    if(mw->rgs.size() == 0){
        QMessageBox::information(this,tr("错误"),tr("rgs最少有一个"));
        return;
    }

    for(int i = 0;i < mw->rgs.size()-1;i++){
        QString tip = QString::number(i);//让slot能够知道是第几个监控组
        //不使用QLabel的原因是QLabel没有click信号
        QToolButton *label=new QToolButton(cenWidget);
        label->setText(QString("监控区域组：").append(mw->rgs[i].name));
        label->setStyleSheet("border-style: flat;");//去掉边框，看起来像label，而不是按钮
        label->setToolTip(tip);
        connect(label,SIGNAL(clicked()),this,SLOT(onClickName()));

        QToolButton *regionGroup = new QToolButton(cenWidget);
        if(mw->rgs[i].isActive){
            regionGroup->setText(QString("隐藏该监控区域组"));
        }else{
            regionGroup->setText(QString("显示该监控区域组"));
        }
        regionGroup->setToolTip(tip);
        connect(regionGroup,SIGNAL(clicked()),this,SLOT(groupShow()));

        QToolButton *active = new QToolButton(cenWidget);
        if(mw->rgs[i].isAlert){
            active->setText(QString("取消报警"));
        }else{
            active->setText(QString("报警"));
        }
        active->setToolTip(tip);
        connect(active,SIGNAL(clicked()),this,SLOT(setAlert()));

        QToolButton *attributes = new QToolButton(cenWidget);
        attributes->setText(QString("颜色"));
        attributes->setToolTip(tip);
        Scalar color=mw->rgs[i].color;
        attributes->setStyleSheet(QString("background-color: rgb(%1, %2, %3);").arg(color.val[2]).arg(color.val[1]).arg(color.val[0]));
        connect(attributes,SIGNAL(clicked()),this,SLOT(attributesModify()));

        QToolButton *edit = new QToolButton(cenWidget);

//        User *user = new User();
//        user->nID = tip.toInt();
        edit->setText(QString("编辑"));

        edit->setToolTip(tip);
        //edit->setUserData(Qt::UserRole,user);
        connect(edit,SIGNAL(clicked()),this,SLOT(editFunction()));

        QToolButton *details = new QToolButton(cenWidget);

            details->setText(QString("详细信息"));


        details->setToolTip(tip);
        connect(details,SIGNAL(clicked()),this,SLOT(detailsShow()));

        layout->addWidget(label,i,0);
        layout->addWidget(regionGroup,i,1);
        layout->addWidget(active,i,2);
        layout->addWidget(attributes,i,3);
        layout->addWidget(edit,i,4);
        layout->addWidget(details,i,6);

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
    if( button->text()== "隐藏该监控区域组"){
        button->setText("显示该监控区域组");
    }else if(button->text()=="显示该监控区域组"){
        button->setText("隐藏该监控区域组");
    }
    int index = button->toolTip().toInt();
    mw->rgs[index].isActive = !mw->rgs[index].isActive;
}

void Monitor::setAlert(){

    QObject* obj = sender();
       QToolButton* button = dynamic_cast<QToolButton*>(obj);
       if( button->text()== "取消报警"){
            button->setText("报警");
       }else if(button->text()=="报警"){
           button->setText("取消报警");
       }

       int index = button->toolTip().toInt();
       mw->rgs[index].isAlert = !mw->rgs[index].isAlert;
}

void Monitor::attributesModify(){
    QObject* obj = sender();
    QToolButton* button = dynamic_cast<QToolButton*>(obj);
    int index = button->toolTip().toInt();
    QColor color = QColorDialog::getColor(Qt::black,this);

    if(!color.isValid()){
        return;
    }
    button->setStyleSheet(QString("background-color: rgb(%1, %2, %3);").arg(color.red()).arg(color.green()).arg(color.blue()));

    Scalar c(color.blue(),color.green(),color.red());
    mw->rgs[index].setColor(c);
}

void Monitor::editFunction(){
    QObject* obj = sender();
    QToolButton* button = dynamic_cast<QToolButton*>(obj);
        int index = button->toolTip().toInt();
        mw->rgsIndex = index;
        mw->isDefiningRegion = true;
        this->close();

}

void Monitor::onClickName(){
    QObject* obj = sender();
    QToolButton* button = dynamic_cast<QToolButton*>(obj);
    int index = button->toolTip().toInt();

    QString newName = QInputDialog::getText(this,QString("请输入新的组监控名字，按确定修改"),QString("新名字"));

    if(newName == "" || newName == mw->rgs[index].name){
        return;
    }
    button->setText(QString("监控区域组：").append(newName));
    mw->rgs[index].name = newName;
}

void Monitor::createRG(){
    this->close();
     mw->widget1->CompleteRGDefining();
     mw->isDefiningRegion = true;
}

void Monitor::detailsShow(){
    QObject* obj = sender();
    QToolButton* button = dynamic_cast<QToolButton*>(obj);
    int index = button->toolTip().toInt();

    // User *user = (User *)(button->userData(Qt::UserRole));
    //int index =user->nID;

//    if(detailsOfRG==NULL||detailsOfRG->index == index){
//        detailsOfRG   = new DetailsOfRG(mw,index);
//    }
//    else if(detailsOfRG!=NULL&&detailsOfRG->index==index){
//        return;
//    }

        DetailsOfRG  *detailsOfRG = new DetailsOfRG(mw,index);
        //detailsOfRG->setWindowFlags(Qt::WindowStaysOnTopHint);
        detailsOfRG->setWindowTitle(QString("监控区域组").append(mw->rgs[index].name).append("的详细信息"));
        detailsOfRG->activateWindow();
        QDesktopWidget *desktop= QApplication::desktop();
        QRect screenRect = desktop->screenGeometry();
        int width = screenRect.width();
        int height = screenRect.height();
        detailsOfRG->setGeometry(7*width/12,5*height/12,width/3,height/3);
        detailsOfRG->show();
        detailsOfRG->detailsShow();

}
