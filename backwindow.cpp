#include "backwindow.h"
#include <QFileInfo>
#include <QToolBar>
#include <map>
#include "myobject.h"
BackWindow::BackWindow():MainWindow()
{
    setWindowTitle("回放");
}
BackWindow::BackWindow(QDate date,QTime start,QTime stop):MainWindow(){
    setWindowTitle("回放");

    QString day=QString("./回放/")+date.toString("yyyy-MM-dd");
    QDir *dir=new QDir(day);
    QStringList filter;//创建过滤器，只看.dat结尾的文件
    filter<<"*.dat";
    dir->setNameFilters(filter);
    fileInfo=new QList<QFileInfo>(dir->entryInfoList(filter));
    fileIndex=0;
    panoIndex=0;
    while((!fileInfo->isEmpty()) && (fileInfo->first().lastModified().time()<start)){
        fileInfo->removeFirst();
    }
    while((!fileInfo->isEmpty())&&(fileInfo->last().lastModified().time()>stop)){
        fileInfo->removeLast();
    }
    delete dir;

    QStringList filter2;
    filter2<<"*.pan";
    QDir *dir2=new QDir(day);
    dir2->setNameFilters(filter2);

    filepano = new QList<QFileInfo>(dir2->entryInfoList(filter2));

    while((!filepano->isEmpty()) && (filepano->first().lastModified().time()<start)){
        filepano->removeFirst();
    }
    while((!filepano->isEmpty())&&(filepano->last().lastModified().time()>stop)){
        filepano->removeLast();
    }

    delete dir2;

    count =0;
    mainToolBar->clear();
    addMyToolBar_backWindow();
    timeLine=new TimeLine(this);
    this->start=start;
    this->stop=stop;
    this->date=date;


}
BackWindow::~BackWindow()
{
    delete fileInfo;
    map<int, MyObject*>::iterator iter;
    for(iter = objmap.begin(); iter != objmap.end(); ++iter)
    {
        delete iter->second;
    }
}
void BackWindow::selfTimerout(){
    if(!isJixu){
    return;
    }
    vector<MyObject> objs;


    QString currentFileTime;
    if(fileIndex<fileInfo->count()){
        currentFileTime=fileInfo->at(fileIndex).fileName().left(8);
       // qDebug()<<"filetime"<<currentFileTime;
    }


    while(fileIndex<fileInfo->count()){
        if(currentFileTime.compare(fileInfo->at(fileIndex).fileName().left(8)) != 0)
            break;
        QFile file(fileInfo->at(fileIndex).filePath());
        //qDebug()<<fileInfo->at(fileIndex).filePath();
        file.open(QIODevice::ReadOnly);
        QDataStream in(&file);
        int id;
        in>>id;
        MyObject *obj;
        map<int, MyObject*>::iterator iter;
        iter = objmap.find(id);
        if(iter != objmap.end()){
            obj=iter->second;
            //qDebug()<<"map.size"<<objmap.size();
        } else{
            obj=new MyObject();
            obj->setID(id);
            objmap.insert(pair<int,MyObject*>(id,obj));
        }
        in>>*obj;

        objs.push_back(*obj);
        file.close();
        fileIndex++;
    }


    Mat pano;
    if(panoIndex<filepano->count()){
        QFile file(filepano->at(panoIndex).filePath());
            //qDebug()<<filepano->at(fileIndex).filePath();
            file.open(QIODevice::ReadOnly);
            QDataStream din(&file);
            int flag;
            din >> flag;
            if(flag == 1){
                MyObject::readMat(din,pano);
            }
            file.close();
            panoIndex++;
    }else{
//        widget1->setObjects(objs);
//        widget1->draw();
//        widget2->setObjects(objs);
//        widget2->draw();
        widget5->setObjects(objs);
        widget5->draw();
        widget6->setObjects(objs);
        widget6->draw();
        return;
 }


    if(isGaojing)
    {
    if(objs.size()> count){
        this->sound->play();
        count = objs.size();
    }
    }
    count = objs.size();

    QDesktopWidget* desktopWidget = QApplication::desktop();
    QRect screenRect = desktopWidget->screenGeometry();
    const int buttonSize=(screenRect.width()*0.7)/21.6;
    QPixmap pixmap1("./icon/16_1.png");
    QPixmap pixmap2("./icon/16_2.png");
    QPixmap fitpixmap1=pixmap1.scaled(buttonSize,buttonSize, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    QPixmap fitpixmap2=pixmap2.scaled(buttonSize,buttonSize, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    if(isGaojing)
    {
        if(count==0)
        {
            light1->setPixmap(fitpixmap2);
            light2->setPixmap(fitpixmap2);
            light3->setPixmap(fitpixmap2);
            light4->setPixmap(fitpixmap2);
            light5->setPixmap(fitpixmap2);
        }
        else if(count==1)
        {
            light1->setPixmap(fitpixmap1);
            light2->setPixmap(fitpixmap2);
            light3->setPixmap(fitpixmap2);
            light4->setPixmap(fitpixmap2);
            light5->setPixmap(fitpixmap2);
        }
        else if(count==2)
        {
            light1->setPixmap(fitpixmap1);
            light2->setPixmap(fitpixmap1);
            light3->setPixmap(fitpixmap2);
            light4->setPixmap(fitpixmap2);
            light5->setPixmap(fitpixmap2);
        }
        else if(count==3)
        {
            light1->setPixmap(fitpixmap1);
            light2->setPixmap(fitpixmap1);
            light3->setPixmap(fitpixmap1);
            light4->setPixmap(fitpixmap2);
            light5->setPixmap(fitpixmap2);
        }
        else if(count==4)
        {
            light1->setPixmap(fitpixmap1);
            light2->setPixmap(fitpixmap1);
            light3->setPixmap(fitpixmap1);
            light4->setPixmap(fitpixmap1);
            light5->setPixmap(fitpixmap2);
        }
        else if(count>= 5 )
        {
            light1->setPixmap(fitpixmap1);
            light2->setPixmap(fitpixmap1);
            light3->setPixmap(fitpixmap1);
            light4->setPixmap(fitpixmap1);
            light5->setPixmap(fitpixmap1);
      }
    }
    else
    {
        light1->setPixmap(fitpixmap2);
        light2->setPixmap(fitpixmap2);
        light3->setPixmap(fitpixmap2);
        light4->setPixmap(fitpixmap2);
        light5->setPixmap(fitpixmap2);
   }

//    for(int i=0;i<3;i++){
//        if(fileIndex<fileInfo->count()){
//            qDebug()<<fileInfo->at(fileIndex).filePath();
//            MyObject *obj=new MyObject();
//            QFile file(fileInfo->at(fileIndex).filePath());
//            file.open(QIODevice::ReadOnly);
//            QDataStream in(&file);
//            in>>*obj;
//            objs.push_back(*obj);
//            file.close();
//            fileIndex++;
//        }
//    }


    //systime= QLabel();//时间

    //in.getIntegratedData2();
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

//    //图片1
//    QString s1=in.getQJ1();
//    imageurl=s1.toStdString();
//    Mat mat1 =imread(imageurl);
//    if(this->isPseudo==true)
//                        mat1=setPseudocolor(mat1);
//        updateBright(mat1);
//        updateContrast(mat1);
////        if(saturation1!=100){
////               hsl->channels[color].saturation1 = saturation1 - 100;
////               hsl->adjust(mat1, mat1);
////           }
//    widget1->setMat(mat1);
//    widget1->setObjects(objs);
//    widget1->setTracks(in.getTracks());
//    widget1->draw();
//    //qDebug()<<s1;
//    //图片2
//    QString s2=in.getQJ2();
//    imageurl2=s2.toStdString();
//    Mat mat2 =imread(imageurl2);
//    if(this->isPseudo==true)
//                        mat2=setPseudocolor(mat2);
//        updateBright(mat2);
//        updateContrast(mat2);
////        if(saturation1!=100){
////               hsl->channels[color].saturation1 = saturation1 - 100;
////               hsl->adjust(mat2, mat2);
////           }
//    widget2->setMat(mat2);
//    widget2->setObjects(objs);
//    widget2->setTracks(in.getTracks());
//    widget2->draw();
//    //qDebug()<<s2;
//    //drawUiLabel(mat2,2);
//    //图片3
//    //Mat mat3 =imread(imageurl);
//    widget3->draw();
//    //drawUiLabelByCopy(mat3,3);
//    //图片4
//    //Mat mat4 =imread(imageurl2);
//    //drawUiLabelByCopy(mat4,4);
//    widget4->draw();
//    //图片5
//    //QString imageurl5=in.getHD();
//    //Mat mat5 =imread(imageurl5.toStdString());
//    //widget5->setMat(mat5);
//    widget5->setPano(mat1);
//    widget5->setObjects(objs);
//    widget5->draw();
//    //drawUiLabel(mat5,5);
//    //图片6
//    //QString imageurl6= in.getLD();
//    //Mat mat6 =imread(imageurl6.toStdString());
//    //widget6->setMat(mat6);
//    widget6->setPano(mat1);
//    widget6->setObjects(objs);
//    widget6->draw();


    Mat pano1 = pano.clone();
    Mat pano2 = pano.clone();
    Mat mat;
    hconcat(pano1,pano2,mat);

   //vector<MyObject> objs = in.getObjs();
   vector<MyObjectTrack> tracks = in.getTracks();


   for (int i = 0; i < count;i++)
   {
       //画对象的box
       MyObject obj = objs[i];
       Rect rect2 = Rect(obj.getRect().x+pano.cols, obj.getRect().y, obj.getRect().width, obj.getRect().height);
       rectangle(mat,obj.getRect(),obj.getColor(),2,1,0);
       rectangle(mat,rect2,obj.getColor(),2,1,0);
       //cv::cvtColor(mat, mat, CV_BGR2RGB);

       //画轨迹
       for(int ii = 0; ii < tracks.size(); ii++){
           MyObjectTrack track = tracks[ii];
           int id = track.getId();
           vector<Point> points = track.getTrack();
           if(id == obj.getID()){
               for(int iii = 0; iii < points.size(); iii++){
                   Point point = points[iii];
                   Point point2 = Point(point.x+pano.cols, point.y);
                   circle(mat, point, 2, obj.getColor(),-1,8,2);//在图像中画出特征点，2是圆的半径
                   circle(mat, point2, 2, obj.getColor(),-1,8,2);//在图像中画出特征点，2是圆的半径
                   if(iii >= 1){
                       Point point3 = points[iii-1];
                       Point point4 = Point(point3.x+pano.cols, point3.y);
                       line(mat,point,point3,obj.getColor(),1,8,0);
                       line(mat,point2,point4,obj.getColor(),1,8,0);
                   }
                   //cv::cvtColor(mat, mat, CV_BGR2RGB);
               }
           }
       }

       //画对象中心点的位置
       if(isMubiao){
           int x = (int)(this->getDirectionX(obj.getCenPoint().x, pano));
           int y = (int)(10-this->getDirectionY(obj.getCenPoint().y, pano)/2);//(10-10*(this->getDirectionY(obj.getCenPoint().y)-this->getDirectionY())/(this->getDirectionY2()-this->getDirectionY()));//endh - i*(endh-starth)/10
           QString tx = QString::number(x,10);
           QString ty = QString::number(y,10);
           QString tstr = "x="+tx+",y="+ty;
           string str = tstr.toStdString();
           //qDebug()<<tstr;
           Point p = Point(obj.getRect().x+obj.getRect().width,obj.getRect().y+obj.getRect().height);
           Point p2 = Point(obj.getRect().x+obj.getRect().width+pano.cols,obj.getRect().y+obj.getRect().height);

           putText(mat,str,p,3,0.5,obj.getColor());
           putText(mat,str,p2,3,0.5,obj.getColor());
                   }
      // cv::cvtColor(mat, mat, CV_BGR2RGB);
   }
 //  cv::cvtColor(mat, mat, CV_BGR2RGB);

   //然后劈成2半

//    Size dsize ;
//    double scale = 1;
//    dsize = Size(mat.cols*scale,mat.rows*scale);
//    Mat image11 = Mat(dsize,CV_32S);
//    cv::resize(mat, image11,dsize);

//    QImage img = QImage((const unsigned char*)(image11.data),image11.cols,image11.rows, image11.cols*image11.channels(),  QImage::Format_RGB888);
//    QImage aa=(&img)->copy(QRect(0,0,mat.cols/2,mat.rows));
//    Mat image4 = CVUtil::QImageToMat(aa);
//    Mat image44 = Mat(dsize,CV_32S);
//    cv::resize(image4, image44,dsize);

//    //全景2Mat
//    QImage aa2=(&img)->copy(QRect(mat.cols/2,0,mat.cols/2,mat.rows));
//    Mat image5 = CVUtil::QImageToMat(aa2);
//    Mat image55 = Mat(dsize,CV_32S);
//    cv::resize(image5, image55,dsize);
   if(this->isPseudo==true)
                       mat=setPseudocolor(mat);
       updateBright(mat);
       updateContrast(mat);

       Mat mat1, mat2;
       mat(Rect(mat.cols/2,0,mat.cols/4,mat.rows)).copyTo(mat1);
       mat(Rect(mat.cols/4,0,mat.cols/4,mat.rows)).copyTo(mat2);

       Mat newpano;
       hconcat(mat1,mat2,newpano);

   //Mat mat1 = image44;
//   if(this->isPseudo==true)
//                       mat1=setPseudocolor(mat1);
//       updateBright(mat1);
//       updateContrast(mat1);
//        if(saturation1!=100){
//               hsl->channels[color].saturation1 = saturation1 - 100;
//               hsl->adjust(mat1, mat1);
//           }
   widget1->setMat(mat1);
   widget1->setPano(newpano);
   widget1->setObjects(objs);
   widget1->setTracks(in.getTracks());
   widget1->draw();

   //qDebug()<<s1;
   //图片2
   //图片1
//    QString s1=in.getQJ1();
//    imageurl=s1.toStdString();
//    Mat mat1 =imread(imageurl);

   //Mat mat2 = image55;
//   if(this->isPseudo==true)
//                       mat2=setPseudocolor(mat2);
//       updateBright(mat2);
//       updateContrast(mat2);
//        if(saturation1!=100){
//               hsl->channels[color].saturation1 = saturation1 - 100;
//               hsl->adjust(mat2, mat2);
//           }
   widget1->setPano(newpano);
   widget2->setMat(mat2);
   widget2->setObjects(objs);
   widget2->setTracks(in.getTracks());
   widget2->draw();
   //qDebug()<<s2;
   //drawUiLabel(mat2,2);
   //图片3
   //Mat mat3 =imread(imageurl);
   widget3->setPano(newpano);
   widget3->setTwoPanos(mat);
   //widget3->setPano(mat);
   widget3->setAllObjects(in.getObjs());
   widget3->draw();
   //drawUiLabelByCopy(mat3,3);
   //图片4
   //Mat mat4 =imread(imageurl2);
   //drawUiLabelByCopy(mat4,4);
   //widget4->setPano(mat);
   widget4->setPano(newpano);
   widget4->setTwoPanos(mat);
   widget4->setAllObjects(in.getObjs());
   widget4->draw();
   //图片5
   //QString imageurl5=in.getHD();
   //Mat mat5 =imread(imageurl5.toStdString());
   //widget5->setMat(mat5);
   widget5->setPano(newpano);
   //widget5->setPano(in.getPano());
   widget5->setObjects(objs);
   widget5->draw();
   //drawUiLabel(mat5,5);
   //图片6
   //QString imageurl6= in.getLD();
   //Mat mat6 =imread(imageurl6.toStdString());
   //widget6->setMat(mat6);
   //widget6->setPano(in.getPano());
   widget6->setPano(newpano);
   widget6->setObjects(objs);
   widget6->draw();
}

void BackWindow::exitFunction(){
    this->close();
}

void BackWindow::addMyToolBar_backWindow()
{
    qDebug()<<"---------------------------";
    //图标太大导致在小屏幕上显示不全，改为按照屏幕宽度自动调整图标的大小
    QDesktopWidget* desktopWidget = QApplication::desktop();
    QRect screenRect = desktopWidget->screenGeometry();  //屏幕区域
    int screenWidth=screenRect.width();
    const int buttonSize=(screenWidth*0.7)/21.6;

    QGroupBox *group1=new QGroupBox(this);
    QGroupBox *group2=new QGroupBox(this);
    QGroupBox *group3=new QGroupBox(this);
    QGroupBox *group4=new QGroupBox(this);
    QGroupBox *group5=new QGroupBox(this);
    QGroupBox *group6=new QGroupBox(this);

    QHBoxLayout *vbox1 = new QHBoxLayout;
    QHBoxLayout *vbox2 = new QHBoxLayout;
    QHBoxLayout *vbox3 = new QHBoxLayout;
    QVBoxLayout *vbox4 = new QVBoxLayout;
    QHBoxLayout *vbox5 = new QHBoxLayout;
     QHBoxLayout *vbox6 = new QHBoxLayout;

    //mainToolBar = addToolBar("monitoring");

    //加图标
    //mainToolBar->addWidget(new QLabel(""));
    QPixmap pixmap3("./icon/fujirui.png");
    QPixmap fitpixmap3=pixmap3.scaled(buttonSize*1.8,buttonSize*1.8, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    QLabel *tuBiao=new QLabel(this);
    tuBiao->setPixmap(fitpixmap3);
    mainToolBar->addWidget(tuBiao);
    mainToolBar->addWidget(new QLabel(" "));

    //回放文字
    QLabel *text = new QLabel(this);
    text->setText(" 回放 ");
    QFont font("宋体", 22, 87);
    text->setFont(font);
    text->setStyleSheet("color:white;");
    mainToolBar->addWidget(text);

    //第一组按钮：回放时间线,回放暂停,回放
    //回放时间线
    startStop = new QToolButton(this);
    startStop->setToolTip(tr("时间线"));
    startStop->setMinimumHeight(buttonSize);
    startStop->setMaximumHeight(buttonSize);
    startStop->setMinimumWidth(buttonSize);
    startStop->setMaximumWidth(buttonSize);
    startStop->setStyleSheet("border-style:flat;background-color:2E302D");
    startStopSet="./icon/时间线.png";
    startStop->setIcon(QPixmap(startStopSet));
    startStop->setIconSize(QSize(buttonSize,buttonSize));
    vbox1->addWidget(startStop);
    connect(startStop,SIGNAL(clicked()),this,SLOT(timeLineFunction()));
    //vbox1->addWidget(new QLabel(" "));

    //回放暂停
    mstop = new QToolButton(this);
    mstop->setToolTip(tr("暂停"));
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
   // vbox1->addWidget(new QLabel(" "));
    //回放
//    open = new QToolButton(this);
//    open->setToolTip(tr("回放"));
//    open->setMinimumHeight(buttonSize);
//    open->setMaximumHeight(buttonSize);
//    open->setMinimumWidth(buttonSize);
//    open->setMaximumWidth(buttonSize);
//    open->setStyleSheet("border-style:flat;background-color:2E302D");
//    openSet="./icon/3_1.png";
//    open->setIcon(QPixmap(openSet));
//    open->setIconSize(QSize(buttonSize,buttonSize));
//    vbox1->addWidget(open);
//    connect(open,SIGNAL(clicked()),this,SLOT(openFunction()));

    group1->setLayout(vbox1);
    mainToolBar->addWidget(group1);
    //mainToolBar->addWidget(new QLabel("    "));
    //第二组按钮：图像
    //自动
    autom = new QToolButton(this);
    autom->setToolTip(tr("自动"));
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

    //亮度
    brightness = new QToolButton(this);
    brightness->setToolTip(tr("亮度"));
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

    //对比度
    saturation = new QToolButton(this);
    saturation->setToolTip(tr("对比度"));
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

    //伪彩色
    pseudoColor = new QToolButton(this);
    pseudoColor->setToolTip(tr("伪彩色"));
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


    //第三组按钮，指示灯，五盏，一个目标一盏红灯；二个目标二盏红灯；三个目标三盏红灯；四个目标四盏红灯；五个目标及以上，五盏红灯
    QPixmap pixmap1("./icon/16_1.png");
    QPixmap pixmap2("./icon/16_2.png");
    QPixmap fitpixmap1=pixmap1.scaled(buttonSize,buttonSize, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    QPixmap fitpixmap2=pixmap2.scaled(buttonSize,buttonSize, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);

    vector<MyObject> vec = in.getObjs2();

    light1=new QLabel(this);
    light2=new QLabel(this);
    light3=new QLabel(this);
    light4=new QLabel(this);
    light5=new QLabel(this);

        if(!isGaojing)
        {
            light1->setPixmap(fitpixmap2);
            light2->setPixmap(fitpixmap2);
            light3->setPixmap(fitpixmap2);
            light4->setPixmap(fitpixmap2);
            light5->setPixmap(fitpixmap2);
        }
        else
        {
            if(vec.size()==0)
            {
                light1->setPixmap(fitpixmap2);
                light2->setPixmap(fitpixmap2);
                light3->setPixmap(fitpixmap2);
                light4->setPixmap(fitpixmap2);
                light5->setPixmap(fitpixmap2);
            }
            else if(vec.size()==1)
            {
                light1->setPixmap(fitpixmap1);
                light2->setPixmap(fitpixmap2);
                light3->setPixmap(fitpixmap2);
                light4->setPixmap(fitpixmap2);
                light5->setPixmap(fitpixmap2);
            }
            else if(vec.size()==2)
            {
                light1->setPixmap(fitpixmap1);
                light2->setPixmap(fitpixmap1);
                light3->setPixmap(fitpixmap2);
                light4->setPixmap(fitpixmap2);
                light5->setPixmap(fitpixmap2);
            }
            else if(vec.size()==3)
            {
                light1->setPixmap(fitpixmap1);
                light2->setPixmap(fitpixmap1);
                light3->setPixmap(fitpixmap1);
                light4->setPixmap(fitpixmap2);
                light5->setPixmap(fitpixmap2);
            }
            else if(vec.size()==4)
            {
                light1->setPixmap(fitpixmap1);
                light2->setPixmap(fitpixmap1);
                light3->setPixmap(fitpixmap1);
                light4->setPixmap(fitpixmap1);
                light5->setPixmap(fitpixmap2);
            }
            else if(vec.size()>= 5 )
            {
                light1->setPixmap(fitpixmap1);
                light2->setPixmap(fitpixmap1);
                light3->setPixmap(fitpixmap1);
                light4->setPixmap(fitpixmap1);
                light5->setPixmap(fitpixmap1);
            }
        }


        vbox3->addWidget(light1);
        vbox3->addWidget(light2);
        vbox3->addWidget(light3);
        vbox3->addWidget(light4);
        vbox3->addWidget(light5);

    group3->setLayout(vbox3);
    mainToolBar->addWidget(group3);
    //mainToolBar->addWidget(new QLabel("    "));

    //第四组，显示编号和系统当前时间
    serialNumber=new QLabel("    位置："+xtbh);//编号
    serialNumber->setStyleSheet("color:White");
    vbox4->addWidget(serialNumber);
    //vbox4->addWidget(new QLabel("   "));
    systime=new QLabel(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss ddd"));//时间

    QString datetime = fileInfo->at(fileIndex).filePath();
    QString backDate = datetime.right(datetime.length()-5).left(10);
    QString backHour = datetime.right(14).left(2);
    QString backMinute= datetime.right(11).left(2);
    QString backSec = datetime.right(8).left(2);
    systime->setText(backDate.append("  ").append(backHour).append(":").append(backMinute).append(":").append(backSec));


    //QString datetime = fileInfo->at(fileIndex).filePath();
    //qDebug()<<datetime.length();
    systime->setStyleSheet("color:White");
    vbox4->addWidget(systime);
    //vbox4->addWidget(new QLabel("   "));

    group4->setLayout(vbox4);
    mainToolBar->addWidget(group4);
    //mainToolBar->addWidget(new QLabel("    "));

    //第五组，告警
    //关闭告警
    openClose = new QToolButton(this);
    openClose->setToolTip(tr("关闭告警"));
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

    //对象属性
    objectAttribute = new QToolButton(this);
    objectAttribute->setToolTip(tr("对象属性"));
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


    //关闭目标属性跟随
    objects = new QToolButton(this);
    objects->setToolTip(tr("关闭目标属性跟随"));
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

    //设置
//    attribute = new QToolButton(this);
//    attribute->setToolTip(tr("设置"));
//    attribute->setMinimumHeight(buttonSize);
//    attribute->setMaximumHeight(buttonSize);
//    attribute->setMinimumWidth(buttonSize);
//    attribute->setMaximumWidth(buttonSize);
//    attribute->setStyleSheet("border-style:flat;background-color:2E302D");
//    attributeSet="./icon/14_1.png";
//    attribute->setIcon(QPixmap(attributeSet));
//    attribute->setIconSize(QSize(buttonSize,buttonSize));
//    vbox5->addWidget(attribute);
//    connect(attribute,SIGNAL(clicked()),this,SLOT(attributeFunction()));
//    //vbox5->addWidget(new QLabel(" "));

    //关闭声音
    voice = new QToolButton(this);
    voice->setToolTip(tr("关闭声音"));
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

    //第六组
    exitButton = new QToolButton(this);
    exitButton->setToolTip(tr("退出"));
    exitButton->setMinimumHeight(buttonSize);
    exitButton->setMaximumHeight(buttonSize);
    exitButton->setMinimumWidth(buttonSize);
    exitButton->setMaximumWidth(buttonSize);
    exitButton->setStyleSheet("border-style:flat;background-color:2E302D");
    exitSet="./icon/18.png";
    exitButton->setIcon(QPixmap(exitSet));
    exitButton->setIconSize(QSize(buttonSize,buttonSize));
   // mainToolBar->addWidget(exitButton);
      vbox6->addWidget(exitButton);
    connect(exitButton,SIGNAL(clicked()),this,SLOT(exitFunction()));

    mainToolBar->addWidget(group6);
    group6->setLayout(vbox6);

}

void BackWindow :: timeLineFunction(){
    timeLine->setTime(start,stop);
    timeLine->setWindowFlags(Qt::WindowStaysOnTopHint);
    timeLine->setWindowTitle("时间线");
    timeLine->activateWindow();
    timeLine->move(200,200);
    timeLine->move(timeLine->x(),timeLine->y());
    timeLine->show();
    timeLine->position= fileIndex*255/fileInfo->count();
   // backWindow->fileIndex=position*backWindow->fileInfo->count()/255;
}

void BackWindow::onTimerOut2(){
    //systime->setText(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss ddd"));//时间

    if(fileIndex < fileInfo->count())
    {
        QString datetime = fileInfo->at(fileIndex).filePath();
        QString backDate = datetime.right(datetime.length()-5).left(10);
        QString backHour = datetime.right(14).left(2);
        QString backMinute = datetime.right(11).left(2);
        QString backSec = datetime.right(8).left(2);
        systime->setText(backDate.append(" ").append(backHour).append(":").append(backMinute).append(":").append(backSec).append(" ").append(date.toString("ddd")));
    }
    else
        systime->setText("       当前无回放      ");


}
