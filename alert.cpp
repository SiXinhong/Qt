#include "alert.h"

Alert::Alert(MainWindow *mw,vector<MyObject> os) :
    QMainWindow()
{
    this->mw = mw;
    this->os = os;
    cenWidget = 0;
    layout =0;

}

void Alert::alertInfo(){
    QGridLayout* old=layout;
    layout=new QGridLayout;
    QWidget *oldWidget = cenWidget;
    cenWidget = new QWidget(this);

    QString group;
    if(mw->isGaojing){
        boolean alert = false;
        for(int i = 0; i < os.size(); i++){
            MyObject mo = os[i];
            for(int j = 0; j < mw->rgs.size(); j++){
                if(mw->rgs[j].isInner(Point2f(mo.cenPoint.x, mo.cenPoint.y))){
                    if(!alert){
                         QLabel *title = new QLabel(QString("��Ŀ����룺"),cenWidget);
                         layout->addWidget(title,0,0);
                    }
                    alert = true;
                    group =mw->rgs.at(j).name;
                    for(int k = 0; k<mw->rgs[j].rs.size();k++){
                        if(mw->rgs[j].rs[k].isInner(Point2f(mo.cenPoint.x, mo.cenPoint.y))){
                            QString region = mw->rgs[j].rs[k].name;
                            QLabel *label = new QLabel(QString("���������").append(group).append(":").append(region),cenWidget);
                            layout->addWidget(label,j+k,0);
                         }

                    }

                }
            }
        }

        if(!alert){
            QLabel*label = new QLabel(QString("��Ŀ�����������"),cenWidget);
            layout->addWidget(label,0,0);
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
}

