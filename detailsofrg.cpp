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
    QString isActive[mw->rgs[index].rs.size()];
    QString type[mw->rgs[index].rs.size()];


    QLabel *label1[mw->rgs[index].rs.size()];
    QLabel *label2[mw->rgs[index].rs.size()];
    QLabel *label3[mw->rgs[index].rs.size()];
    QLabel *label4[mw->rgs[index].rs.size()];
    QLabel *label5[mw->rgs[index].rs.size()];
    for(int i = 0;i< mw->rgs[index].rs.size();i++){
        name[i]= mw->rgs.at(index).rs[i].name;
        Scalar color = mw->rgs.at(index).rs[i].color;
        if(mw->rgs.at(index).rs[i].hasObjects){
             hasObjects[i] ="��Ŀ����������";
        }else{
             hasObjects[i] ="��Ŀ����������";
        }
        if( mw->rgs.at(index).rs[i].isActive){
            isActive[i] ="����״̬";
        }
       else{
            isActive[i] = "δ����״̬";
        }
        if(mw->rgs.at(index).rs[i].isRect ){
            type[i] ="����";

        }else
            type[i] ="�����";

        label1[i] = new QLabel(QString("������� ").append(name[i]).append(":"),cenWidget);
        label2[i] = new QLabel(type[i],cenWidget);
        label3[i] = new QLabel(isActive[i],cenWidget);
        label4[i] = new QLabel(hasObjects[i],cenWidget);
        label5[i] = new QLabel("��ɫ",cenWidget);
        label5[i]->setStyleSheet(QString("background-color: rgb(%1, %2, %3);").arg(color.val[2]).arg(color.val[1]).arg(color.val[0]));

        layout->addWidget(label1[i],i,0);
        layout->addWidget(label2[i],i,1);
        layout->addWidget(label3[i],i,2);
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
