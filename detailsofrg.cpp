#include "detailsofrg.h"


DetailsOfRG::DetailsOfRG(MainWindow *mw,int index) :
    QMainWindow()
{
    this->mw = mw;
    this->index = index;
    //detailsShow();
    cenWidget = 0;
    layout = 0;

}



void DetailsOfRG::detailsShow(){
    QGridLayout* old=layout;
    layout=new QGridLayout;
    QWidget *oldWidget = cenWidget;
    cenWidget = new QWidget(this);

    QString name[mw->rgs[index].rs.size()];
    QString hasObjects[mw->rgs[index].rs.size()];

    QString type[mw->rgs[index].rs.size()];

    QToolButton *isShow[mw->rgs[index].rs.size()];



    QLabel *label1[mw->rgs[index].rs.size()];
    QLabel *label2[mw->rgs[index].rs.size()];

    QLabel *label4[mw->rgs[index].rs.size()];
    QLabel *label5[mw->rgs[index].rs.size()];
    for(int i = 0;i< mw->rgs[index].rs.size();i++){
        name[i]= mw->rgs.at(index).rs[i].name;
        Scalar color = mw->rgs.at(index).rs[i].color;
        if(mw->rgs.at(index).rs[i].hasObjects){
             hasObjects[i] ="有目标进入该区域";
        }else{
             hasObjects[i] ="无目标进入该区域";
        }

        if(mw->rgs.at(index).rs[i].isRect ){
            type[i] ="矩形";

        }else
            type[i] ="多边形";

         isShow[i] = new QToolButton(cenWidget);

        if(mw->rgs.at(index).rs[i].isActive){
            isShow[i]->setText("隐藏");
        }else
            isShow[i]->setText("显示");

        connect(isShow[i],SIGNAL(clicked()),this,SLOT(regionShow()));
        isShow[i]->setToolTip(  QString::number(i));
        label1[i] = new QLabel(QString("监控区域 ").append(name[i]).append(":"),cenWidget);
        label2[i] = new QLabel(type[i],cenWidget);

        label4[i] = new QLabel(hasObjects[i],cenWidget);
        label5[i] = new QLabel("颜色",cenWidget);
        label5[i]->setStyleSheet(QString("background-color: rgb(%1, %2, %3);").arg(color.val[2]).arg(color.val[1]).arg(color.val[0]));

        layout->addWidget(label1[i],i,0);
        layout->addWidget(isShow[i],i,1);
        layout->addWidget(label2[i],i,2);

        layout->addWidget(label4[i],i,3);
        layout->addWidget(label5[i],i,4);
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

void DetailsOfRG::closeEvent(QCloseEvent *){

}

void DetailsOfRG::regionShow(){
    QObject* obj = sender();
    QToolButton* button = dynamic_cast<QToolButton*>(obj);
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
