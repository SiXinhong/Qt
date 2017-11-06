#include "objectAttributes.h"
#include <QPainter>
#include<QString>
#include "myinterface.h"
#include "QMainWindow.h"
#include <cv.h>
#include "mainwindow.h"
#include <QImage>

ObjectAttributes::ObjectAttributes(vector<MyObject> objs) :
    QMainWindow()
{

    //this->objectInterface=objectInterface;
    index2Show=-1;
    this->objs =objs;
    addMyToolBar();

}

ObjectAttributes::~ObjectAttributes()
{
    
}

void ObjectAttributes::paintEvent(QPaintEvent *event)
{
    if(index2Show<0)
        return;
    //vector<MyObject> vec = objectInterface->getObjs2();
    MyObject *obj = &objs.at(index2Show);
    QDesktopWidget* desktopWidget = QApplication::desktop();
    QRect screenRect = desktopWidget->screenGeometry();
    int width = screenRect.width();
    int height = screenRect.height();

    int y = height/13, x=30;
    QPainter painter(this);

    painter.drawText(x,y,QString("目标").append(QString::number(index2Show+1)).append(":"));
    y+=height/45;
    painter.drawText(x,y,QString("oid:").append(QString::number(obj->oid)));
    x+=width/10;
    painter.drawText(x,y,QString("目标中心坐标：<").append(QString::number(obj->cenPoint.x)).append(",").append(QString::number(obj->cenPoint.y)).append(">"));
    x+=width/10;
    painter.drawText(x,y,QString("检测框大小：<").append(QString::number(obj->blocksize.width)).append(",").append(QString::number(obj->blocksize.height)).append(">"));
    y+=height/45;
    x=30;
    painter.drawText(x,y,QString("运动速率：").append(QString::number(obj->Velocity)));
    x+=width/10;
    painter.drawText(x,y,QString("运动方向：").append(QString::number(obj->MotionDerection)));
    x+=width/10;
    painter.drawText(x,y,QString("目标面积：").append(QString::number(obj->area)));
    y+=height/45;
    x=30;
    painter.drawText(x,y,QString("水平轴长度：").append(QString::number(obj->horizontalAxisLength)));
    x+=width/10;
    painter.drawText(x,y,QString("竖直轴长度：").append(QString::number(obj->verticalAxisLength)));
    x+=width/10;
    painter.drawText(x,y,QString("绝对强度：").append(QString::number(obj->absoluteIntensity)));
    y+=height/45;
    x=30;
    painter.drawText(x,y,QString("相对强度：").append(QString::number(obj->relativeIntensity)));
    x+=width/10;
    painter.drawText(x,y,QString("目标尺度：").append(QString::number(obj->targetScale)));
    x+=width/10;
    painter.drawText(x,y,QString("中央周围对比度的响应强度：").append(QString::number(obj->CenSueEintensity)));
    x=30;
    y+=height/45;
    painter.drawText(x,y,QString("目标背景信杂比：").append(QString::number(obj->SCRValue)));
    x=30;
    y+=height/45;
    painter.drawText(x,y,QString("目标轮廓："));
    if (!obj->contours.empty())
    {
        x+=width/10;
        for(int k = 0; k <= obj->contours.size();k++)
        {
            //qDebug()<<k;
            painter.drawText(x,y,QString::number(obj->contours.at(k).x).append(QString::number(obj->contours.at(k).y)));
        }
    }
    else {
        x+=width/10;
        painter.drawText(x,y,QString("无"));
    }
    x=30;
    y+=height/45;
    painter.drawText(x,y,QString("目标快照："));
    if(!obj->Snapshoot.empty())
    {

        x+=width/10;
        cv::resize(obj->Snapshoot, obj->Snapshoot, cv::Size(50,50));
        QImage qimage = MainWindow::MatToQImage(obj->Snapshoot,QImage());
        painter.drawImage(x,y,qimage);
    }
    else{
        x+=width/10;
        painter.drawText(x,y,QString("无"));
    }

    x=30;
    y+=height/45;
    painter.drawText(x,y,QString("目标剪影："));
    if(!obj->sihouette.empty())
    {
        x+=width/10;
        cv::resize(obj->Snapshoot, obj->Snapshoot, cv::Size(50,50));
        QImage qimage = MainWindow::MatToQImage(obj->Snapshoot,QImage());
        painter.drawImage(x,y,qimage);
    }
    else{
        x+=width/10;
        painter.drawText(x,y,QString("无"));
    }

//    QFont font("宋体", 15, QFont::Bold, true);
//    //设置下划线
//    font.setUnderline(true);
//    //设置上划线
//    font.setOverline(true);
//    //设置字母大小写
//    font.setCapitalization(QFont::SmallCaps);
//    //设置字符间的间距
//    font.setLetterSpacing(QFont::AbsoluteSpacing, 10);
}
void ObjectAttributes::addMyToolBar()
{
    mainToolBar = addToolBar("objs");
    //vector<MyObject> vec = objectInterface->getObjs2();
   // qDebug()<< vec.size();
    for(int i = 0; i < objs.size();i++){
        MyObject *obj = &objs.at(i);

        QGroupBox *group = new QGroupBox(this);
        QHBoxLayout *vbox = new QHBoxLayout;

        QToolButton *object = new QToolButton(this);

        object->setToolTip(tr("目标").append(QString::number(i+1)));
        object->setText(QString("obj").append(QString::number(i+1)));
        vbox->addWidget(object);
        connect(object,SIGNAL(clicked()),this,SLOT(objectsShow()));

        QLabel *snapshot = new QLabel(this);

        QImage objImage = MainWindow::MatToQImage(obj->Snapshoot,QImage());
        QPixmap pixmap=QPixmap::fromImage(objImage);


        snapshot->setPixmap(pixmap);
        vbox->addWidget(snapshot);

        group->setLayout(vbox);
        mainToolBar->addWidget(group);
    }



    QGroupBox *group4=new QGroupBox(this);
    QVBoxLayout *vbox4 = new QVBoxLayout;
    QToolButton *exitButton = new QToolButton(this);
    exitButton->setToolTip(tr("退出"));
    //    exitButton->setMinimumHeight(buttonSize);
    //    exitButton->setMaximumHeight(buttonSize);
    //    exitButton->setMinimumWidth(buttonSize);
    //    exitButton->setMaximumWidth(buttonSize);
    exitButton->setStyleSheet("border-style:flat;background-color:2E302D");
    exitButton->setIcon(QPixmap("./icon/18.png"));
    //exitButton->setIconSize(QSize(buttonSize,buttonSize));
    //mainToolBar->addWidget(exitButton);
    vbox4->addWidget(exitButton);
    connect(exitButton,SIGNAL(clicked()),this,SLOT(exitFunction()));

    mainToolBar->addWidget(group4);
    group4->setLayout(vbox4);


}



void ObjectAttributes::exitFunction()
{
    this->close();
}

void ObjectAttributes::objectsShow()
{
    QObject* obj = sender();
    // 把基类对象强制转换成子类对象
    QToolButton* button = dynamic_cast<QToolButton*>(obj);

    QString textOfButton=button->text();//根据button显示的内容看是第几个
    if(textOfButton.length()<4)
        return;
    index2Show=textOfButton.right(textOfButton.length()-3).left(textOfButton.length()-3).toInt()-1;//第几个object
    this->repaint();
}
