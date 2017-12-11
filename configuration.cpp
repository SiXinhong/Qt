#include "configuration.h"
#include <QInputDialog>

Configuration::Configuration(MainWindow *mw)
{
    this->mw = mw;
    isStart = false;
    start = NULL;
    menuWidget = new QWidget(this);
    zRed = 0;
    zBlue = 0;
    zGreen = 0;
    n1Red = 0;
    n1Blue = 0;
    n1Green = 0;
    n2Red = 0;
    n2Blue = 0;
    n2Green = 0;
    zhan = 0;

    strackbar = new STrackBar(this);
    trackbar = new TrackBar(this);

    buildCenWidgetCamera();
    buildCenWidgetSoftWare();
    buildCenWidgetAlgorithm();
    stackedLayout = new QStackedLayout();

    stackedLayout->addWidget(new QWidget(this));//先显示空白的
    stackedLayout->addWidget(cenWidgetCamera);
    stackedLayout->addWidget(cenWidgetSoftWare);
    stackedLayout->addWidget(cenWidgetAlgorithm);

    QWidget *cenWidget = new QWidget();
    cenWidget->setLayout(stackedLayout);

    this->setCentralWidget(cenWidget);
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
void Configuration::buildCenWidgetCamera(){
    layoutCamera=new QGridLayout;
    cenWidgetCamera = new QWidget(this);

    start = new QToolButton(cenWidgetCamera);
    start->setText("启动");
    connect(start,SIGNAL(clicked()),this,SLOT(startF()));

    QToolButton *state = new QToolButton(cenWidgetCamera);
    state->setText("状态查询");
    connect(state,SIGNAL(clicked()),this,SLOT(stateSearch()));

    QToolButton *minus = new QToolButton(cenWidgetCamera);
    minus->setText("-");
    connect(minus,SIGNAL(clicked()),this,SLOT(minusF()));

    QToolButton *add = new QToolButton(cenWidgetCamera);
    add->setText("+");
    connect(add,SIGNAL(clicked()),this,SLOT(addF()));

     QToolButton *stop = new QToolButton(cenWidgetCamera);
     stop->setText("停止");
     connect(stop,SIGNAL(clicked()),this,SLOT(stopF()));

     QToolButton *background = new QToolButton(cenWidgetCamera);
     background->setText("背景校正");
     connect(background,SIGNAL(clicked()),this,SLOT(backgroundCorrct()));

     QToolButton *shuttle = new QToolButton(cenWidgetCamera);
     shuttle->setText("快门校正");
     connect(shuttle,SIGNAL(clicked()),this,SLOT(shuttleCorrct()));

     QToolButton *ok = new QToolButton(cenWidgetCamera);
     ok->setText("确定");
     connect(ok,SIGNAL(clicked()),this,SLOT(okF()));

     imageWidget = new QWidget();
     imageLabel = new QLabel(imageWidget);

     //先从全景图截取了一块显示看看效果，以后这里要改
     Mat mat1;
     mw->widget1->pano(Rect(0,0,imageWidget->width(),imageWidget->height())).copyTo(mat1);

     setCameraMat(mat1);



     layoutCamera->addWidget(start,0,0);
     layoutCamera->addWidget(state,1,0);
     layoutCamera->addWidget(minus,2,0);
     layoutCamera->addWidget(add,2,1);
     layoutCamera->addWidget(stop,2,2);
     layoutCamera->addWidget(background,3,0);
     layoutCamera->addWidget(shuttle,4,0);
     layoutCamera->addWidget(ok,5,0);

     layoutCamera->addWidget(imageWidget,0,3,6,1);
     layoutCamera->setColumnStretch(0,1);
     layoutCamera->setColumnStretch(1,1);
     layoutCamera->setColumnStretch(2,1);
     layoutCamera->setColumnStretch(3,7);

     cenWidgetCamera->setLayout(layoutCamera);
}

void Configuration::cameraShow(){
    stackedLayout->setCurrentIndex(1);
    imageLabel->resize(imageWidget->size());
}

void Configuration::buildCenWidgetSoftWare(){
    layoutSoftWare=new QGridLayout;
    cenWidgetSoftWare = new QWidget(this);

    QVBoxLayout *zhanlayout = new QVBoxLayout(cenWidgetSoftWare);

    QLabel * zhanwei = new QLabel("站位配置：",this);
    zhanlayout->addWidget(zhanwei);

    zhan = new QToolButton;
    zhan->setText(mw->zhanwei.append("(点击可修改)"));
    connect(zhan,SIGNAL(clicked()),this,SLOT(zhanModify()));
    zhan->setStyleSheet("border-style: flat;");
    zhanlayout->addWidget(zhan);

    QLabel *color = new QLabel("边框颜色配置：",this);
    zhanlayout->addWidget(color);

    QToolButton *zColor = new QToolButton(cenWidgetSoftWare);
    zColor->setText("主显示区边框颜色");
    //zColor->setToolTip(QString::number(1));
    connect(zColor,SIGNAL(clicked()),this,SLOT(colorSet()));

    QToolButton *n1Color = new QToolButton(cenWidgetSoftWare);
    n1Color->setText("辅助显示区1边框颜色");
    //n1Color->setToolTip(QString::number(2));
    connect(n1Color,SIGNAL(clicked()),this,SLOT(colorSet()));

    QToolButton *n2Color = new QToolButton(cenWidgetSoftWare);
    n2Color->setText("辅助显示区2边框颜色");
   // n2Color->setToolTip(QString::number(3));
    connect(n2Color,SIGNAL(clicked()),this,SLOT(colorSet()));

    layoutSoftWare->addWidget(zColor,1,0);
    layoutSoftWare->addWidget(n1Color,1,1);
    layoutSoftWare->addWidget(n2Color,1,2);

    zhanlayout->addLayout(layoutSoftWare);
    zhanlayout->addStretch();

    cenWidgetSoftWare->setLayout(layoutSoftWare);
}

void Configuration::softwareShow(){
    stackedLayout->setCurrentIndex(2);
}

void Configuration::buildCenWidgetAlgorithm(){
    layoutAlgorithm=new QGridLayout;
    cenWidgetAlgorithm = new QWidget(this);
    QLabel * contrast = new QLabel("对比度调节(0到2):");
    QLabel *light = new QLabel("亮度调节(-500到500):");
   // strackbar->resize(this->width()/4,this->height()/10);

    layoutAlgorithm->addWidget(contrast,0,0);
    layoutAlgorithm->addWidget(strackbar,1,0);
    layoutAlgorithm->addWidget(light,2,0);
    layoutAlgorithm->addWidget(trackbar,3,0);

    imageWidgetAlgorithm = new QWidget();
    imageLabelAlgorithm = new QLabel(imageWidgetAlgorithm);

    //先从全景图截取了一块显示看看效果，以后这里要改
    Mat mat1;
    mw->widget1->pano(Rect(0,0,imageWidgetAlgorithm->width(),imageWidgetAlgorithm->height())).copyTo(mat1);

    setAlgorithmMat(mat1);

    layoutAlgorithm->addWidget(imageWidgetAlgorithm,0,1,4,1);

    layoutAlgorithm->setColumnStretch(0,1);
    layoutAlgorithm->setColumnStretch(1,2);

    cenWidgetAlgorithm->setLayout(layoutAlgorithm);

}

void Configuration::algorithmShow(){

    stackedLayout->setCurrentIndex(3);
    imageLabelAlgorithm->resize(imageWidgetAlgorithm->size());

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
    stackedLayout->setCurrentIndex(0);
}


void Configuration::colorSet(){
    QObject* obj = sender();
    QToolButton* button = dynamic_cast<QToolButton*>(obj);
    //int index = button->toolTip().toInt();
    color = QColorDialog::getColor(Qt::black,this);

    if(!color.isValid()){
        return;
    }
    button->setStyleSheet(QString("background-color: rgb(%1, %2, %3);").arg(color.red()).arg(color.green()).arg(color.blue()));

    if(button->text()=="主显示区边框颜色"){
      mw->widget3->setStyleSheet(QString("border-width:3px;border-style:solid;border-color: rgb(%1, %2, %3);").arg(color.red()).arg(color.green()).arg(color.blue()));
      zRed = color.red();
      zBlue = color.blue();
      zGreen = color.green();
      mw->widget3->setColor(Scalar(zBlue,zGreen,zRed));
      mw->widget4->setColor(mw->widget4->getColor());
      mw->widget6->setColor(mw->widget6->getColor());
    }
    else if(button->text()=="辅助显示区1边框颜色"){
        mw->widget4->setStyleSheet(QString("border-width:3px;border-style:solid;border-color: rgb(%1, %2, %3);").arg(color.red()).arg(color.green()).arg(color.blue()));
        n1Red = color.red();
        n1Blue = color.blue();
        n1Green = color.green();
        mw->widget4->setColor(Scalar(n1Blue,n1Green,n1Red));
        mw->widget3->setColor(mw->widget3->getColor());
        mw->widget6->setColor(mw->widget6->getColor());

    }
    else if (button->text() == "辅助显示区2边框颜色"){
       mw->widget6->setStyleSheet(QString("border-width:3px;border-style:solid;border-color: rgb(%1, %2, %3);").arg(color.red()).arg(color.green()).arg(color.blue()));
       n2Red = color.red();
       n2Blue = color.blue();
       n2Green = color.green();
       mw->widget6->setColor(Scalar(n2Blue,n2Green,n2Red));
       mw->widget3->setColor(mw->widget3->getColor());
       mw->widget4->setColor(mw->widget4->getColor());
    }
}

void Configuration::zhanModify(){
    QString newName = QInputDialog::getText(this,QString("请输入新的站位"),QString("新站位"));

    if(newName == ""){
        return;
    }

    zhan->setText(newName.append("站位"));
    mw->zhanweiLabel->setText(newName);



}
void Configuration::setCameraMat(Mat mat){
    QImage image;
    image = mw->MatToQImage(mat,image);
    QPixmap pixmap = QPixmap::fromImage(image);
    imageLabel->setScaledContents(true);
    imageLabel->setPixmap(pixmap);
}



void Configuration::setAlgorithmMat(Mat mat){
    QImage image;
    image = mw->MatToQImage(mat,image);
    QPixmap pixmap = QPixmap::fromImage(image);
    imageLabelAlgorithm->setScaledContents(true);
    imageLabelAlgorithm->setPixmap(pixmap);
}

void Configuration::resizeEvent(QResizeEvent *){
    imageLabel->resize(imageWidget->size());
    imageLabelAlgorithm->resize(imageWidgetAlgorithm->size());
}
