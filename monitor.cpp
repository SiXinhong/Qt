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
    create->setText("�������������");
    connect(create,SIGNAL(clicked()),this,SLOT(createRG()));

    if(mw->rgs.size() <= 1){
        QLabel *label = new QLabel(QString("δ����������"),cenWidget);
        layout->addWidget(label,0,0);
    }


    if(mw->rgs.size() == 0){
        QMessageBox::information(this,tr("����"),tr("rgs������һ��"));
        return;
    }

    for(int i = 0;i < mw->rgs.size()-1;i++){
        QString tip = QString::number(i);//��slot�ܹ�֪���ǵڼ��������
        //��ʹ��QLabel��ԭ����QLabelû��click�ź�
        QToolButton *label=new QToolButton(cenWidget);
        label->setText(QString("��������飺").append(mw->rgs[i].name));
        label->setStyleSheet("border-style: flat;");//ȥ���߿򣬿�������label�������ǰ�ť
        label->setToolTip(tip);
        connect(label,SIGNAL(clicked()),this,SLOT(onClickName()));

        QToolButton *regionGroup = new QToolButton(cenWidget);
        if(mw->rgs[i].isActive){
            regionGroup->setText(QString("���ظü��������"));
        }else{
            regionGroup->setText(QString("��ʾ�ü��������"));
        }
        regionGroup->setToolTip(tip);
        connect(regionGroup,SIGNAL(clicked()),this,SLOT(groupShow()));

        QToolButton *active = new QToolButton(cenWidget);
        if(mw->rgs[i].isAlert){
            active->setText(QString("ȡ������"));
        }else{
            active->setText(QString("����"));
        }
        active->setToolTip(tip);
        connect(active,SIGNAL(clicked()),this,SLOT(setAlert()));

        QToolButton *attributes = new QToolButton(cenWidget);
        attributes->setText(QString("��ɫ"));
        attributes->setToolTip(tip);
        Scalar color=mw->rgs[i].color;
        attributes->setStyleSheet(QString("background-color: rgb(%1, %2, %3);").arg(color.val[2]).arg(color.val[1]).arg(color.val[0]));
        connect(attributes,SIGNAL(clicked()),this,SLOT(attributesModify()));

        QToolButton *edit = new QToolButton(cenWidget);

//        User *user = new User();
//        user->nID = tip.toInt();
        edit->setText(QString("�༭"));

        edit->setToolTip(tip);
        //edit->setUserData(Qt::UserRole,user);
        connect(edit,SIGNAL(clicked()),this,SLOT(editFunction()));

        QToolButton *details = new QToolButton(cenWidget);

            details->setText(QString("��ϸ��Ϣ"));


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
    int index = button->toolTip().toInt();
    if( button->text()== "���ظü��������"){
        button->setText("��ʾ�ü��������");
        for(int k=0;k<mw->rgs[index].rs.size();k++){
            mw->rgs.at(index).rs[k].isActive = false;
        }

    }else if(button->text()=="��ʾ�ü��������"){
        button->setText("���ظü��������");
        for(int k=0;k<mw->rgs[index].rs.size();k++){
            mw->rgs.at(index).rs[k].isActive = true;
        }
    }

    mw->rgs[index].isActive = !mw->rgs[index].isActive;
}

void Monitor::setAlert(){

    QObject* obj = sender();
       QToolButton* button = dynamic_cast<QToolButton*>(obj);
       if( button->text()== "ȡ������"){
            button->setText("����");
       }else if(button->text()=="����"){
           button->setText("ȡ������");
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

    QString newName = QInputDialog::getText(this,QString("�������µ��������֣���ȷ���޸�"),QString("������"));

    if(newName == "" || newName == mw->rgs[index].name){
        return;
    }
    button->setText(QString("��������飺").append(newName));
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
        detailsOfRG->setWindowTitle(QString("���������").append(mw->rgs[index].name).append("����ϸ��Ϣ"));
        detailsOfRG->activateWindow();
        QDesktopWidget *desktop= QApplication::desktop();
        QRect screenRect = desktop->screenGeometry();
        int width = screenRect.width();
        int height = screenRect.height();
        detailsOfRG->setGeometry(7*width/12,5*height/12,width/3,height/3);
        detailsOfRG->show();
        detailsOfRG->detailsShow();

}
