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
    hourWidget = new HourWidget(this);

    listWidget = 0;
    stackedLayout = 0;

}

//Monitor::~Monitor(){
//    if(detailsOfRG){delete detailsOfRG;}
//    if(layout){delete layout;}
//    if(cenWidget){delete cenWidget;}
//}
void Monitor::widgetShow(){
   listWidget = new QListWidget;
    for(int i = 0;i < mw->rgs.size()-1;i++){
        listWidget->addItem(QString("监控区域组：").append(mw->rgs[i].name));
    }
    listWidget->setMaximumWidth(this->width()/6);
    QVBoxLayout *leftLayout = new QVBoxLayout;

    QToolButton *create = new QToolButton(cenWidget);
    create->setText("创建新的监控区域组");
    connect(create,SIGNAL(clicked()),this,SLOT(createRG()));

    leftLayout->addWidget(create);

    leftLayout->addWidget(listWidget);

    stackedLayout = new QStackedLayout;
    for(int i = 0;i < mw->rgs.size()-1;i++){
        QString tip = QString::number(i);
        QVBoxLayout * mlayout = new QVBoxLayout;
        QGridLayout * layout = new QGridLayout;

//        QHBoxLayout *timelayout = new QHBoxLayout;
//        timelayout->addWidget(hourWidget);
        //hourWidget->setGeometry(this->width()/2,0,1050,400);
        hourWidget->resize(this->width()/2,this->height()/2);
        hourWidget->xStart = this->width()/17;
        hourWidget->yStart = 30;
        hourWidget->w = this->width()/65;
        hourWidget->h = 2*hourWidget->w;
//        qDebug()<<"hourWidget->xStart:"<<hourWidget->xStart;
//        qDebug()<<" hourWidget->yStart:"<< hourWidget->yStart;
//        qDebug()<<"hourWidget->w:"<<hourWidget->w;
//        qDebug()<<"hourWidget->h:"<<hourWidget->h;

        for(int ii=0;ii<7;ii++){
            for(int j=0;j<48;j++){
                hourWidget->isActive[ii][j] = mw->rgs[i].timeActive[ii][j];
            }
        }
        //hourWidget->raise();
        //mlayout->addLayout(timelayout);

//        hourWidget->show();
//        hourWidget->raise();
        QWidget *regionWidget = new QWidget;

        QToolButton *namelabel=new QToolButton(regionWidget);
        namelabel->setText(QString("修改组名字"));
        namelabel->setToolTip(tip);
        connect(namelabel,SIGNAL(clicked()),this,SLOT(onClickName()));


        QToolButton *regionGroup = new QToolButton(regionWidget);
        if(mw->rgs[i].isActive){
            regionGroup->setText(QString("隐藏该监控区域组"));
        }else{
            regionGroup->setText(QString("显示该监控区域组"));
        }
        regionGroup->setToolTip(tip);
        connect(regionGroup,SIGNAL(clicked()),this,SLOT(groupShow()));

        QToolButton *active = new QToolButton(regionWidget);
        if(mw->rgs[i].isAlert){
            active->setText(QString("取消报警"));
        }else{
            active->setText(QString("报警"));
        }
        active->setToolTip(tip);
        connect(active,SIGNAL(clicked()),this,SLOT(setAlert()));

        QToolButton *attributes = new QToolButton(regionWidget);
        attributes->setText(QString("颜色"));
        attributes->setToolTip(tip);
        Scalar color=mw->rgs[i].color;
        attributes->setStyleSheet(QString("background-color: rgb(%1, %2, %3);").arg(color.val[2]).arg(color.val[1]).arg(color.val[0]));
        connect(attributes,SIGNAL(clicked()),this,SLOT(attributesModify()));

        QToolButton *timeCon = new QToolButton(cenWidget);
        timeCon->setText("告警时间段设置");
        timeCon->setToolTip(tip);
        connect(timeCon,SIGNAL(clicked()),this,SLOT(timeControl()));

        QToolButton *edit = new QToolButton(cenWidget);
        edit->setText(QString("编辑"));
        edit->setToolTip(tip);
        connect(edit,SIGNAL(clicked()),this,SLOT(editFunction()));

        mlayout->addLayout(layout);


        layout->addWidget(namelabel,0,1);
        layout->addWidget(regionGroup,0,2);
        layout->addWidget(active,0,3);
        layout->addWidget(attributes,0,4);
//        layout->addWidget(regionGroup);
//        layout->addWidget(active);
//        layout->addWidget(attributes);
        layout->addWidget(edit,0,6);
        //layout->addWidget(details,i,5);
        layout->addWidget(timeCon,0,5);

        //layout->addStretch();
        QGridLayout * layout1 = new QGridLayout;

        for(int j = 0;j< mw->rgs[i].rs.size();j++){
            QString name= mw->rgs.at(i).rs[j].name;

            QString hasObjects;
            if(mw->rgs.at(i).rs[j].hasObjects){
                hasObjects ="有目标进入该区域";
            }else{
                 hasObjects ="无目标进入该区域";
            }

            QString type;
            if(mw->rgs.at(i).rs[j].isRect ){
                type ="该区域形状为矩形";

            }else
                type ="该区域形状为多边形";

            QToolButton *isShow = new QToolButton(regionWidget);
            if(mw->rgs.at(i).rs[j].isActive){
                isShow->setText("隐藏");
            }else
                isShow->setText("显示");

            connect(isShow,SIGNAL(clicked()),this,SLOT(regionShow()));
            isShow->setToolTip(QString::number(j));


           QLabel *label1 = new QLabel(QString("监控区域 ").append(name).append(":"),regionWidget);
           QLabel *label2 = new QLabel(type,regionWidget);
           QLabel *label4 = new QLabel(hasObjects,regionWidget);



            layout1->addWidget(label1,2+j,0);
            layout1->addWidget(isShow,2+j,1);
            layout1->addWidget(label2,2+j,2);
            layout1->addWidget(label4,2+j,3);

        }

        mlayout->addLayout(layout1);
        regionWidget->setLayout(mlayout);
        stackedLayout->addWidget(regionWidget);
    }

    //connect(listWidget,SIGNAL(currentRowChanged(int)),stackedLayout,SLOT(setCurrentIndex(int)));
    connect(listWidget,SIGNAL(currentRowChanged(int)),this,SLOT(listWidgetChange(int)));
    listWidget->setCurrentRow(0);
    timeIndex = 0;

    QGridLayout *mainLayout = new QGridLayout;
    mainLayout->addLayout(leftLayout,0,0,2,1);
    mainLayout->addWidget(hourWidget,0,1,1,1);
    mainLayout->addLayout(stackedLayout,1,1,1,1);

    mainLayout->setRowStretch(0, 2);
    mainLayout->setRowStretch(1, 1);

    mainLayout->setColumnStretch(0,1);
    mainLayout->setColumnStretch(1,4);


    QWidget *mainWidget = new QWidget;
    mainWidget->setLayout(mainLayout);

    setCentralWidget(mainWidget);


//    QGridLayout* old=layout;
//    layout=new QGridLayout;
//    QWidget *oldWidget = cenWidget;
//    cenWidget = new QWidget(this);

//    QToolButton *create = new QToolButton(cenWidget);
//    create->setText("创建监控区域组");
//    connect(create,SIGNAL(clicked()),this,SLOT(createRG()));

//    if(mw->rgs.size() <= 1){
//        QLabel *label = new QLabel(QString("未定义监控区域"),cenWidget);
//        layout->addWidget(label,0,0);
//    }


//    if(mw->rgs.size() == 0){
//        QMessageBox::information(this,tr("错误"),tr("rgs最少有一个"));
//        return;
//    }

//    for(int i = 0;i < mw->rgs.size()-1;i++){
//        QString tip = QString::number(i);//让slot能够知道是第几个监控组
//        //不使用QLabel的原因是QLabel没有click信号
//        QToolButton *label=new QToolButton(cenWidget);
//        label->setText(QString("监控区域组：").append(mw->rgs[i].name));
//        label->setStyleSheet("border-style: flat;");//去掉边框，看起来像label，而不是按钮
//        label->setToolTip(tip);
//        connect(label,SIGNAL(clicked()),this,SLOT(onClickName()));

//        QToolButton *regionGroup = new QToolButton(cenWidget);
//        if(mw->rgs[i].isActive){
//            regionGroup->setText(QString("隐藏该监控区域组"));
//        }else{
//            regionGroup->setText(QString("显示该监控区域组"));
//        }
//        regionGroup->setToolTip(tip);
//        connect(regionGroup,SIGNAL(clicked()),this,SLOT(groupShow()));

//        QToolButton *active = new QToolButton(cenWidget);
//        if(mw->rgs[i].isAlert){
//            active->setText(QString("取消报警"));
//        }else{
//            active->setText(QString("报警"));
//        }
//        active->setToolTip(tip);
//        connect(active,SIGNAL(clicked()),this,SLOT(setAlert()));

//        QToolButton *attributes = new QToolButton(cenWidget);
//        attributes->setText(QString("颜色"));
//        attributes->setToolTip(tip);
//        Scalar color=mw->rgs[i].color;
//        attributes->setStyleSheet(QString("background-color: rgb(%1, %2, %3);").arg(color.val[2]).arg(color.val[1]).arg(color.val[0]));
//        connect(attributes,SIGNAL(clicked()),this,SLOT(attributesModify()));

//        QToolButton *edit = new QToolButton(cenWidget);

//        //        User *user = new User();
//        //        user->nID = tip.toInt();
//        edit->setText(QString("编辑"));

//        edit->setToolTip(tip);
//        //edit->setUserData(Qt::UserRole,user);
//        connect(edit,SIGNAL(clicked()),this,SLOT(editFunction()));

//        QToolButton *details = new QToolButton(cenWidget);

//        details->setText(QString("详细信息"));
//        details->setToolTip(tip);
//        connect(details,SIGNAL(clicked()),this,SLOT(detailsShow()));

//        QToolButton *timeCon = new QToolButton(cenWidget);
//        timeCon->setText("告警时间段设置");
//        timeCon->setToolTip(tip);
//        connect(timeCon,SIGNAL(clicked()),this,SLOT(timeControl()));

//        layout->addWidget(label,i,0);
//        layout->addWidget(regionGroup,i,1);
//        layout->addWidget(active,i,2);
//        layout->addWidget(attributes,i,3);
//        layout->addWidget(edit,i,4);
//        layout->addWidget(details,i,5);
//        layout->addWidget(timeCon,i,6);

//    }
//    if(old!=0){
//        delete old;
//    }
//    if(oldWidget!=0){
//        QList<QWidget*> btns=oldWidget->findChildren<QWidget*>();
//        foreach (QWidget* btn, btns)
//        {
//            delete btn;
//        }
//        oldWidget->repaint();
//        delete oldWidget;
//    }
//    cenWidget->setLayout(layout);
//    this->setCentralWidget(cenWidget);

}

void Monitor::groupShow(){

    QObject* obj = sender();
    QToolButton* button = dynamic_cast<QToolButton*>(obj);
    int index = button->toolTip().toInt();
    if( button->text()== "隐藏该监控区域组"){
        button->setText("显示该监控区域组");
        for(int k=0;k<mw->rgs[index].rs.size();k++){
            mw->rgs.at(index).rs[k].isActive = false;
        }

    }else if(button->text()=="显示该监控区域组"){
        button->setText("隐藏该监控区域组");
        for(int k=0;k<mw->rgs[index].rs.size();k++){
            mw->rgs.at(index).rs[k].isActive = true;
        }
    }

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
    listWidget->currentItem()->setText(QString("监控区域组：").append(newName));
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

void Monitor::timeControl(){
    QObject* obj = sender();
    QToolButton* button = dynamic_cast<QToolButton*>(obj);
    int index = button->toolTip().toInt();
    timeIndex = index;
    for(int i=0;i<7;i++){
        for(int j=0;j<48;j++){
            hourWidget->isActive[i][j] = mw->rgs[index].timeActive[i][j];
        }
    }
    hourWidget->setWindowTitle(QString("监控区域组").append(mw->rgs[index].name).append("的告警时间设置"));
    hourWidget->activateWindow();
    hourWidget->show();
}

void Monitor::onSelectTime(){
    for(int i=0;i<7;i++){
        for(int j=0;j<48;j++){
            mw->rgs[timeIndex].timeActive[i][j] = hourWidget->isActive[i][j];
        }
    }
    hourWidget->repaint();
}

void Monitor::regionShow(){
    QObject* obj = sender();
    QToolButton* button = dynamic_cast<QToolButton*>(obj);
    int index = stackedLayout->currentIndex();
    int rNo = button->toolTip().toInt();

    if(button->text()=="显示"){
        mw->rgs.at(index).rs[rNo].isActive =true;
        button->setText("隐藏");
    }
    else if(button->text()=="隐藏"){
        mw->rgs.at(index).rs[rNo].isActive =false;
        button->setText("显示");
    }

}
void Monitor::listWidgetChange(int i){
    timeIndex = i;
    for(int ii=0;ii<7;ii++){
        for(int j=0;j<48;j++){
            hourWidget->isActive[ii][j] = mw->rgs[i].timeActive[ii][j];
        }
    }
    hourWidget->repaint();
    stackedLayout->setCurrentIndex(i);
}
