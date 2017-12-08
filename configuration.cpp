#include "configuration.h"

Configuration::Configuration(MainWindow *mw)
{
    this->mw = mw;
    layout = 0;
    cenWidget = 0;
    isStart = false;
    start = NULL;
    menuWidget = new QWidget(this);


}

void Configuration::configure(){
    QGridLayout *leftLayout = new QGridLayout();

    QToolButton *camera = new QToolButton(menuWidget);
    camera->setText("转台配置");
    connect(camera,SIGNAL(clicked()),this,SLOT(cameraShow()));
     qDebug()<<"config33";
    QToolButton *algorithm = new QToolButton(menuWidget);
    algorithm->setText("算法配置");
    connect(algorithm,SIGNAL(clicked()),this,SLOT(algorithmShow()));

    QToolButton *software = new QToolButton(menuWidget);
    software->setText("软件配置");
    connect(software,SIGNAL(clicked()),this,SLOT(softwareShow()));


      leftLayout->addWidget(camera,0,0);
      leftLayout->addWidget(algorithm,0,1);
      leftLayout->addWidget(software,0,2);

      menuWidget->setLayout(leftLayout);
      //this->setCentralWidget(menuWidget);
        this->setMenuWidget(menuWidget);

}

void Configuration::cameraShow(){
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

void Configuration::softwareShow(){
    QGridLayout* old=layout;
    layout=new QGridLayout;
    QWidget *oldWidget = cenWidget;
    cenWidget = new QWidget(this);

//    QLabel * name = new QLabel("软件配置",this);
//     layout->addWidget(name,0,0);

    QToolButton *zColor = new QToolButton(cenWidget);
    zColor->setText("主显示区边框颜色");
    //zColor->setToolTip(QString::number(1));
    connect(zColor,SIGNAL(clicked()),this,SLOT(colorSet()));

    QToolButton *n1Color = new QToolButton(cenWidget);
    n1Color->setText("辅助显示区1边框颜色");
    //n1Color->setToolTip(QString::number(2));
    connect(n1Color,SIGNAL(clicked()),this,SLOT(colorSet()));

    QToolButton *n2Color = new QToolButton(cenWidget);
    n2Color->setText("辅助显示区2边框颜色");
   // n2Color->setToolTip(QString::number(3));
    connect(n2Color,SIGNAL(clicked()),this,SLOT(colorSet()));



    layout->addWidget(zColor,0,0);
    layout->addWidget(n1Color,0,1);
    layout->addWidget(n2Color,0,2);


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

void Configuration::algorithmShow(){
    QGridLayout* old=layout;
    layout=new QGridLayout;
    QWidget *oldWidget = cenWidget;
    cenWidget = new QWidget(this);

    QLabel * name = new QLabel("算法配置",this);

     layout->addWidget(name,0,0);
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
    QGridLayout* old=layout;
    layout=new QGridLayout;
    QWidget *oldWidget = cenWidget;
    cenWidget = new QWidget(this);

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


void Configuration::colorSet(){
    QObject* obj = sender();
    QToolButton* button = dynamic_cast<QToolButton*>(obj);
    //int index = button->toolTip().toInt();
    QColor color = QColorDialog::getColor(Qt::black,this);

    if(!color.isValid()){
        return;
    }
    button->setStyleSheet(QString("background-color: rgb(%1, %2, %3);").arg(color.red()).arg(color.green()).arg(color.blue()));

    //Scalar c(color.blue(),color.green(),color.red());
    if(button->text()=="主显示区边框颜色"){
      //mw->widget3->setStyleSheet(QString::fromUtf8("border:3px").append("background-color: rgb(%1, %2, %3);").arg(color.red()).arg(color.green()).arg(color.blue()));
    }
    else if(button->text()=="辅助显示区1边框颜色"){


    }
    else if (button->text() == "辅助显示区2边框颜色"){


    }
}
