﻿#include "configuration.h"

Configuration::Configuration(MainWindow *mw)
{
    this->mw = mw;
    layout = 0;
    cenWidget = 0;
    isStart = false;
    start = NULL;
}

void Configuration::configure(){
    QGridLayout* old=layout;
    layout=new QGridLayout;
    QWidget *oldWidget = cenWidget;
    cenWidget = new QWidget(this);

   start = new QToolButton(cenWidget);
    start->setText("启动");
    connect(start,SIGNAL(clicked()),this,SLOT(startF()));

    QToolButton *state = new QToolButton(cenWidget);
    state->setText("状态查询");
    connect(state,SIGNAL(clicked()),this,SLOT(stateSearch()));

    QToolButton *minus = new QToolButton(cenWidget);
    minus->setText("-");
    connect(minus,SIGNAL(clicked()),this,SLOT(minusF()));

    QToolButton *add = new QToolButton(cenWidget);
    add->setText("+");
    connect(add,SIGNAL(clicked()),this,SLOT(addF()));

     QToolButton *stop = new QToolButton(cenWidget);
     stop->setText("停止");
     connect(stop,SIGNAL(clicked()),this,SLOT(stopF()));

     QToolButton *background = new QToolButton(cenWidget);
     background->setText("背景校正");
     connect(background,SIGNAL(clicked()),this,SLOT(backgroundCorrct()));

             QToolButton *shuttle = new QToolButton(cenWidget);
             shuttle->setText("快门校正");
             connect(shuttle,SIGNAL(clicked()),this,SLOT(shuttleCorrct()));

             QToolButton *ok = new QToolButton(cenWidget);
             ok->setText("确定");
             connect(ok,SIGNAL(clicked()),this,SLOT(okF()));

      layout->addWidget(start,0,0);
      layout->addWidget(state,1,0);
      layout->addWidget(minus,2,0);
      layout->addWidget(add,2,1);
      layout->addWidget(stop,2,2);
      layout->addWidget(background,3,0);
      layout->addWidget(shuttle,4,0);
      layout->addWidget(ok,5,0);

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

void Configuration::startF(){
    isStart=!isStart;
    if(isStart){
        start->setText("停止");
         SetSystemPara(4,1);
    }else if(!isStart){
        start->setText("启动");
        SetSystemPara(4,0);

    }

}

void Configuration::stateSearch(){
    SetSystemPara(2,0);

}

void Configuration::addF(){
     SetSystemPara(2,1);
}

void Configuration::minusF(){
     SetSystemPara(2,2);
}

void Configuration::stopF(){
    std::cout<<"stop "<<std::endl;
     SetSystemPara(2,5);
}

void Configuration::shuttleCorrct(){
     SetSystemPara(2,4);
}

void Configuration::backgroundCorrct(){
     SetSystemPara(2,3);
}

void Configuration::okF(){
    this->close();
    //mw->init();
}