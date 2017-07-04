#include "backwindow.h"
#include <QFileInfo>
BackWindow::BackWindow():MainWindow()
{
    setWindowTitle("�ط�");
}
BackWindow::BackWindow(QTime start,QTime stop):MainWindow(){
    setWindowTitle("�ط�");
    this->start=start;
    this->stop=stop;

    QString today=QString("./huifang/")+QDate::currentDate().toString("yyyy-MM-dd");
    QDir *dir=new QDir(today);
    fileInfo=new QList<QFileInfo>(dir->entryInfoList());
    fileIndex=0;
    delete dir;
}
BackWindow::~BackWindow()
{
    delete fileInfo;
}
void BackWindow::selfTimerout(){
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
        if(saturation1!=100){
               hsl->channels[color].saturation1 = saturation1 - 100;
               hsl->adjust(mat1, mat1);
           }
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
        if(saturation1!=100){
               hsl->channels[color].saturation1 = saturation1 - 100;
               hsl->adjust(mat2, mat2);
           }
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
