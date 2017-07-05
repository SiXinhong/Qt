#include "backwindow.h"
#include <QFileInfo>
#include <QToolBar>
BackWindow::BackWindow():MainWindow()
{
    setWindowTitle("�ط�");
}
BackWindow::BackWindow(QDate date,QTime start,QTime stop):MainWindow(){
    setWindowTitle("�ط�");
    mainToolBar->clear();
    addMyToolBar_backWindow();
    timeLine=new TimeLine(this);
    this->start=start;
    this->stop=stop;
    this->date=date;

    QString day=QString("./�ط�/")+date.toString("yyyy-MM-dd");
    QDir *dir=new QDir(day);
    QStringList filter;//�������������÷��������У�ֻ�뿴.dat��β�ģ���д��*.dat
    filter<<"*.dat";
    dir->setNameFilters(filter);
    fileInfo=new QList<QFileInfo>(dir->entryInfoList(filter));
    fileIndex=0;
    delete dir;
    while((!fileInfo->isEmpty()) && (fileInfo->first().lastModified().time()<start)){
        fileInfo->removeFirst();
    }
    while((!fileInfo->isEmpty())&&(fileInfo->last().lastModified().time()>stop)){
        fileInfo->removeLast();
    }
}
BackWindow::~BackWindow()
{
    delete fileInfo;
}
void BackWindow::selfTimerout(){
    if(!isJixu){
    return;
    }
    vector<MyObject> objs;
    for(int i=0;i<3;i++){
        if(fileIndex<fileInfo->count()){
            qDebug()<<fileInfo->at(fileIndex).filePath();
            MyObject *obj=new MyObject();
            QFile file(fileInfo->at(fileIndex).filePath());
            file.open(QIODevice::ReadOnly);
            QDataStream in(&file);
            in>>*obj;
            objs.push_back(*obj);
            file.close();
            fileIndex++;
        }
    }
//    for(int i = 0; i < objs.size(); i++){
//        MyObject obj = objs[i];
//        qDebug()<<i;
//        qDebug()<<obj.getID();
//        qDebug()<<obj.getCenPoint().x;
//        qDebug()<<obj.getCenPoint().y;
//        qDebug()<<obj.getRect().x;
//        qDebug()<<obj.getRect().y;
//        qDebug()<<obj.getRect().width;
//        qDebug()<<obj.getRect().height;
//    }

    //ͼƬ1
    QString s1=in.getQJ1();
    imageurl=s1.toStdString();
    Mat mat1 =imread(imageurl);
    if(this->isPseudo==true)
                        mat1=setPseudocolor(mat1);
        updateBright(mat1);
        updateContrast(mat1);
//        if(saturation1!=100){
//               hsl->channels[color].saturation1 = saturation1 - 100;
//               hsl->adjust(mat1, mat1);
//           }
    widget1->setMat(mat1);
    widget1->setObjects(objs);
    widget1->setTracks(in.getTracks());
    widget1->draw();
    //qDebug()<<s1;
    //ͼƬ2
    QString s2=in.getQJ2();
    imageurl2=s2.toStdString();
    Mat mat2 =imread(imageurl2);
    if(this->isPseudo==true)
                        mat2=setPseudocolor(mat2);
        updateBright(mat2);
        updateContrast(mat2);
//        if(saturation1!=100){
//               hsl->channels[color].saturation1 = saturation1 - 100;
//               hsl->adjust(mat2, mat2);
//           }
    widget2->setMat(mat2);
    widget2->setObjects(objs);
    widget2->setTracks(in.getTracks());
    widget2->draw();
    //qDebug()<<s2;
    //drawUiLabel(mat2,2);
    //ͼƬ3
    //Mat mat3 =imread(imageurl);
    widget3->draw();
    //drawUiLabelByCopy(mat3,3);
    //ͼƬ4
    //Mat mat4 =imread(imageurl2);
    //drawUiLabelByCopy(mat4,4);
    widget4->draw();
    //ͼƬ5
    //QString imageurl5=in.getHD();
    //Mat mat5 =imread(imageurl5.toStdString());
    //widget5->setMat(mat5);
    widget5->setPano(mat1);
    widget5->setObjects(objs);
    widget5->draw();
    //drawUiLabel(mat5,5);
    //ͼƬ6
    //QString imageurl6= in.getLD();
    //Mat mat6 =imread(imageurl6.toStdString());
    //widget6->setMat(mat6);
    widget6->setPano(mat1);
    widget6->setObjects(objs);
    widget6->draw();
}

void BackWindow::exitFunction(){
    this->close();
}

void BackWindow::addMyToolBar_backWindow()
{
    qDebug()<<"---------------------------";
    //ͼ��̫������С��Ļ����ʾ��ȫ����Ϊ������Ļ����Զ�����ͼ��Ĵ�С
    QDesktopWidget* desktopWidget = QApplication::desktop();
    QRect screenRect = desktopWidget->screenGeometry();  //��Ļ����
    int screenWidth=screenRect.width();
    const int buttonSize=(screenWidth-466)/20;

    QGroupBox *group1=new QGroupBox(this);
    QGroupBox *group2=new QGroupBox(this);
    QGroupBox *group3=new QGroupBox(this);
    QGroupBox *group4=new QGroupBox(this);
    QGroupBox *group5=new QGroupBox(this);

    QHBoxLayout *vbox1 = new QHBoxLayout;
    QHBoxLayout *vbox2 = new QHBoxLayout;
    QHBoxLayout *vbox3 = new QHBoxLayout;
    QVBoxLayout *vbox4 = new QVBoxLayout;
    QHBoxLayout *vbox5 = new QHBoxLayout;
    //mainToolBar = addToolBar("monitoring");

    //��ͼ��
    //mainToolBar->addWidget(new QLabel(""));
    QPixmap pixmap3("./icon/fujirui.png");
    QPixmap fitpixmap3=pixmap3.scaled(70,70, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    QLabel *tuBiao=new QLabel(this);
    tuBiao->setPixmap(fitpixmap3);
    mainToolBar->addWidget(tuBiao);
    //mainToolBar->addWidget(new QLabel(" "));
    //��һ�鰴ť���ط�ʱ����,�ط���ͣ,�ط�
    //�ط�ʱ����
    startStop = new QToolButton(this);
    startStop->setToolTip(tr("ʱ����"));
    startStop->setMinimumHeight(buttonSize);
    startStop->setMaximumHeight(buttonSize);
    startStop->setMinimumWidth(buttonSize);
    startStop->setMaximumWidth(buttonSize);
    startStop->setStyleSheet("border-style:flat;background-color:2E302D");
    startStopSet="./icon/1_1.png";
    startStop->setIcon(QPixmap(startStopSet));
    startStop->setIconSize(QSize(buttonSize,buttonSize));
    vbox1->addWidget(startStop);
    connect(startStop,SIGNAL(clicked()),this,SLOT(timeLineFunction()));
    //vbox1->addWidget(new QLabel(" "));

    //�ط���ͣ
    mstop = new QToolButton(this);
    mstop->setToolTip(tr("��ͣ"));
    mstop->setMinimumHeight(buttonSize);
    mstop->setMaximumHeight(buttonSize);
    mstop->setMinimumWidth(buttonSize);
    mstop->setMaximumWidth(buttonSize);
    mstop->setStyleSheet("border-style:flat;background-color:2E302D");
    mstopSet="./icon/2_1.png";
    mstop->setIcon(QPixmap(mstopSet));
    mstop->setIconSize(QSize(buttonSize,buttonSize));
    vbox1->addWidget(mstop);
    connect(mstop,SIGNAL(clicked()),this,SLOT(mstopFunction()));
    //vbox1->addWidget(new QLabel(" "));
    //�ط�
    open = new QToolButton(this);
    open->setToolTip(tr("�ط�"));
    open->setMinimumHeight(buttonSize);
    open->setMaximumHeight(buttonSize);
    open->setMinimumWidth(buttonSize);
    open->setMaximumWidth(buttonSize);
    open->setStyleSheet("border-style:flat;background-color:2E302D");
    openSet="./icon/3_1.png";
    open->setIcon(QPixmap(openSet));
    open->setIconSize(QSize(buttonSize,buttonSize));
    vbox1->addWidget(open);
    connect(open,SIGNAL(clicked()),this,SLOT(openFunction()));

    group1->setLayout(vbox1);
    mainToolBar->addWidget(group1);
    //mainToolBar->addWidget(new QLabel("    "));
    //�ڶ��鰴ť��ͼ��
    //�Զ�
    autom = new QToolButton(this);
    autom->setToolTip(tr("�Զ�"));
    autom->setMinimumHeight(buttonSize);
    autom->setMaximumHeight(buttonSize);
    autom->setMinimumWidth(buttonSize);
    autom->setMaximumWidth(buttonSize);
    autom->setStyleSheet("border-style:flat;background-color:2E302D");
    automSet="./icon/6_1.png";
    autom->setIcon(QPixmap(automSet));
    autom->setIconSize(QSize(buttonSize,buttonSize));
    vbox2->addWidget(autom);
    connect(autom,SIGNAL(clicked()),this,SLOT(automFunction()));
    //vbox2->addWidget(new QLabel(" "));

    //����
    brightness = new QToolButton(this);
    brightness->setToolTip(tr("����"));
    brightness->setMinimumHeight(buttonSize);
    brightness->setMaximumHeight(buttonSize);
    brightness->setMinimumWidth(buttonSize);
    brightness->setMaximumWidth(buttonSize);
    brightness->setStyleSheet("border-style:flat;background-color:2E302D");
    brightnessSet="./icon/7_1.png";
    brightness->setIcon(QPixmap(brightnessSet));
    brightness->setIconSize(QSize(buttonSize,buttonSize));
    vbox2->addWidget(brightness);
    connect(brightness,SIGNAL(clicked()),this,SLOT(brightnessFunction()));
    //vbox2->addWidget(new QLabel(" "));

    //�Աȶ�
    saturation = new QToolButton(this);
    saturation->setToolTip(tr("�Աȶ�"));
    saturation->setMinimumHeight(buttonSize);
    saturation->setMaximumHeight(buttonSize);
    saturation->setMinimumWidth(buttonSize);
    saturation->setMaximumWidth(buttonSize);
    saturation->setStyleSheet("border-style:flat;background-color:2E302D");
    saturationSet="./icon/8_1.png";
    saturation->setIcon(QPixmap(saturationSet));
    saturation->setIconSize(QSize(buttonSize,buttonSize));
    vbox2->addWidget(saturation);
    connect(saturation,SIGNAL(clicked()),this,SLOT(saturationFunction()));
    //vbox2->addWidget(new QLabel(" "));

    //α��ɫ
    pseudoColor = new QToolButton(this);
    pseudoColor->setToolTip(tr("α��ɫ"));
    pseudoColor->setMinimumHeight(buttonSize);
    pseudoColor->setMaximumHeight(buttonSize);
    pseudoColor->setMinimumWidth(buttonSize);
    pseudoColor->setMaximumWidth(buttonSize);
    pseudoColor->setStyleSheet("border-style:flat;background-color:2E302D");
    pseudoColorSet="./icon/9_1.png";
    pseudoColor->setIcon(QPixmap(pseudoColorSet));
    pseudoColor->setIconSize(QSize(buttonSize,buttonSize));
    vbox2->addWidget(pseudoColor);
    connect(pseudoColor,SIGNAL(clicked()),this,SLOT(pseudoColorFunction()));

    group2->setLayout(vbox2);
    mainToolBar->addWidget(group2);
    //mainToolBar->addWidget(new QLabel("    "));


    //�����鰴ť��ָʾ�ƣ���յ��һ��Ŀ��һյ��ƣ�����Ŀ���յ��ƣ�����Ŀ����յ��ƣ��ĸ�Ŀ����յ��ƣ����Ŀ�꼰���ϣ���յ���
    QPixmap pixmap1("./icon/16_1.png");
    QPixmap pixmap2("./icon/16_2.png");
    QPixmap fitpixmap1=pixmap1.scaled(buttonSize,buttonSize, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    QPixmap fitpixmap2=pixmap2.scaled(buttonSize,buttonSize, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);

    light1=new QLabel(this);
    light1->setPixmap(fitpixmap1);
    vbox3->addWidget(light1);
    //vbox3->addWidget(new QLabel(" "));

    light2=new QLabel(this);
    light2->setPixmap(fitpixmap1);
    vbox3->addWidget(light2);
    //vbox3->addWidget(new QLabel(" "));

    light3=new QLabel(this);
    light3->setPixmap(fitpixmap1);
    vbox3->addWidget(light3);
    //vbox3->addWidget(new QLabel(" "));

    light4=new QLabel(this);
    light4->setPixmap(fitpixmap2);
    vbox3->addWidget(light4);
    //vbox3->addWidget(new QLabel(" "));

    light5=new QLabel(this);
    light5->setPixmap(fitpixmap2);
    vbox3->addWidget(light5);

    group3->setLayout(vbox3);
    mainToolBar->addWidget(group3);
    //mainToolBar->addWidget(new QLabel("    "));

    //�����飬��ʾ��ź�ϵͳ��ǰʱ��
    serialNumber=new QLabel("    λ�ã�"+xtbh);//���
    serialNumber->setStyleSheet("color:White");
    vbox4->addWidget(serialNumber);
    //vbox4->addWidget(new QLabel("   "));
    systime=new QLabel(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss ddd"));//ʱ��
    systime->setStyleSheet("color:White");
    vbox4->addWidget(systime);
    //vbox4->addWidget(new QLabel("   "));

    group4->setLayout(vbox4);
    mainToolBar->addWidget(group4);
    //mainToolBar->addWidget(new QLabel("    "));

    //�����飬�澯
    //�رո澯
    openClose = new QToolButton(this);
    openClose->setToolTip(tr("�رո澯"));
    openClose->setMinimumHeight(buttonSize);
    openClose->setMaximumHeight(buttonSize);
    openClose->setMinimumWidth(buttonSize);
    openClose->setMaximumWidth(buttonSize);
    openClose->setStyleSheet("border-style:flat;background-color:2E302D");
    openCloseSet="./icon/11_1.png";
    openClose->setIcon(QPixmap(openCloseSet));
    openClose->setIconSize(QSize(buttonSize,buttonSize));
    vbox5->addWidget(openClose);
    connect(openClose,SIGNAL(clicked()),this,SLOT(openCloseFunction()));
    //vbox5->addWidget(new QLabel(" "));

    //��������
    objectAttribute = new QToolButton(this);
    objectAttribute->setToolTip(tr("��������"));
    objectAttribute->setMinimumHeight(buttonSize);
    objectAttribute->setMaximumHeight(buttonSize);
    objectAttribute->setMinimumWidth(buttonSize);
    objectAttribute->setMaximumWidth(buttonSize);
    objectAttribute->setStyleSheet("border-style:flat;background-color:2E302D");
    objectAttributeSet="./icon/17_1.png";
    objectAttribute->setIcon(QPixmap(objectAttributeSet));
    objectAttribute->setIconSize(QSize(buttonSize,buttonSize));
    vbox5->addWidget(objectAttribute);
    connect(objectAttribute,SIGNAL(clicked()),this,SLOT(objectAttributeFunction()));
    //vbox5->addWidget(new QLabel(" "));


    //�ر�Ŀ�����Ը���
    objects = new QToolButton(this);
    objects->setToolTip(tr("�ر�Ŀ�����Ը���"));
    objects->setMinimumHeight(buttonSize);
    objects->setMaximumHeight(buttonSize);
    objects->setMinimumWidth(buttonSize);
    objects->setMaximumWidth(buttonSize);
    objects->setStyleSheet("border-style:flat;background-color:2E302D");
    objectSet="./icon/13_1.png";
    objects->setIcon(QPixmap(objectSet));
    objects->setIconSize(QSize(buttonSize,buttonSize));
    vbox5->addWidget(objects);
    connect(objects,SIGNAL(clicked()),this,SLOT(objectsFunction()));
    //vbox5->addWidget(new QLabel(" "));

    //����
    attribute = new QToolButton(this);
    attribute->setToolTip(tr("����"));
    attribute->setMinimumHeight(buttonSize);
    attribute->setMaximumHeight(buttonSize);
    attribute->setMinimumWidth(buttonSize);
    attribute->setMaximumWidth(buttonSize);
    attribute->setStyleSheet("border-style:flat;background-color:2E302D");
    attributeSet="./icon/14_1.png";
    attribute->setIcon(QPixmap(attributeSet));
    attribute->setIconSize(QSize(buttonSize,buttonSize));
    vbox5->addWidget(attribute);
    connect(attribute,SIGNAL(clicked()),this,SLOT(attributeFunction()));
    //vbox5->addWidget(new QLabel(" "));

    //�ر�����
    voice = new QToolButton(this);
    voice->setToolTip(tr("�ر�����"));
    voice->setMinimumHeight(buttonSize);
    voice->setMaximumHeight(buttonSize);
    voice->setMinimumWidth(buttonSize);
    voice->setMaximumWidth(buttonSize);
    voice->setStyleSheet("border-style:flat;background-color:2E302D");
    voiceSet="./icon/15_1.png";
    voice->setIcon(QPixmap(voiceSet));
    voice->setIconSize(QSize(buttonSize,buttonSize));
    vbox5->addWidget(voice);
    connect(voice,SIGNAL(clicked()),this,SLOT(voiceFunction()));

    group5->setLayout(vbox5);
    mainToolBar->addWidget(group5);
    //mainToolBar->addWidget(new QLabel("   "));

    //������
    exitButton = new QToolButton(this);
    exitButton->setToolTip(tr("�˳�"));
    exitButton->setMinimumHeight(buttonSize);
    exitButton->setMaximumHeight(buttonSize);
    exitButton->setMinimumWidth(buttonSize);
    exitButton->setMaximumWidth(buttonSize);
    exitButton->setStyleSheet("border-style:flat;background-color:2E302D");
    exitSet="./icon/18.png";
    exitButton->setIcon(QPixmap(exitSet));
    exitButton->setIconSize(QSize(buttonSize,buttonSize));
    mainToolBar->addWidget(exitButton);
    connect(exitButton,SIGNAL(clicked()),this,SLOT(exitFunction()));
}

void BackWindow :: timeLineFunction(){
    timeLine->setTime(start,stop);
    timeLine->setWindowFlags(Qt::WindowStaysOnTopHint);
    timeLine->setWindowTitle("ʱ����");
    timeLine->activateWindow();
    timeLine->move(200,200);
    timeLine->move(timeLine->x(),timeLine->y());
    timeLine->show();
}
