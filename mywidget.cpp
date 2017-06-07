#include "mywidget.h"
#include <QToolBar>
#include <QGridLayout>
#include <QPainter>
#include<QPalette>
#include<QPixmap>
#include<QImage>
#include<QLabel>

#include <QtGui/QPainter>
MyWidget::MyWidget(QWidget *parent) :
    QWidget(parent)
{
    //创建图片1
    QLabel *label=new QLabel(this);
    label-> setStyleSheet("QLabel{background:rgb(0,255,255);"
                            "image: url(./s1/1.bmp);}");
    label->setScaledContents(true);
    label->setScaledContents(true);
    QPainter *paint = new QPainter(label);
    paint->begin(label);
    paint->setPen(QPen(Qt::red,4,Qt::DashLine));
    paint->drawRect(20,20,50,30);
    paint->end();
    /*
    QString filename="./s1/1.bmp";
                QImage* img=new QImage,* scaledimg=new QImage;//分别保存原图和缩放之后的图片
                img->load(filename);
//                if(! ( img->load(filename) ) ) //加载图像
//                {
//                    QMessageBox::information(this,tr("打开图像失败"),tr("打开图像失败!"));
//                    delete img;
//                    return;
//                }
                int Owidth=img->width(),Oheight=img->height();
                int Fwidth,Fheight;       //缩放后的图片大小
//                label->setGeometry(0,0,400,300);
                int Mul;            //记录图片与label大小的比例，用于缩放图片
                if(Owidth/label->width()>=Oheight/label->height())
                    Mul=Owidth/label->width();
                else
                    Mul=Oheight/label->height();
                Fwidth=Owidth/Mul;
                Fheight=Oheight/Mul;
                *scaledimg=img->scaled(Fwidth,Fheight,Qt::KeepAspectRatio);

                label->setPixmap(QPixmap::fromImage(*scaledimg));
                label-> setStyleSheet("QLabel{background:rgb(255,255,255);");
*/
    //创建图片2
    QLabel *label2=new QLabel(this);
    label2-> setStyleSheet("QLabel{background:rgb(255,255,255);"
                            "image: url(./s1/1.bmp);}");
    //创建图片3
    QLabel *label3=new QLabel(this);
    label3-> setStyleSheet("QLabel{background:rgb(255,255,255);"
                            "image: url(./s1/1.bmp);}");
    //创建图片4
    QLabel *label4=new QLabel(this);
    label4-> setStyleSheet("QLabel{background:rgb(255,255,255);"
                            "image: url(./s1/1.bmp);}");
    //创建图片5
    QLabel *label5=new QLabel(this);
    label5-> setStyleSheet("QLabel{background:rgb(255,255,255);"
                            "image: url(./21.png);}");
    //创建图片6
    QLabel *label6=new QLabel(this);
    label6-> setStyleSheet("QLabel{background:rgb(255,255,255);"
                            "image: url(./21.png);}");


    // 创建工具栏，包含了播放、暂停和停止动作
    QToolBar *toolBar = new QToolBar(this);

    QGridLayout *gridlayout = new QGridLayout;

    gridlayout->setRowStretch(0, 1);
    gridlayout->setRowStretch(1, 1);
    gridlayout->setRowStretch(2, 1);
    gridlayout->setRowStretch(3, 6);
    gridlayout->setRowStretch(4, 5);

    gridlayout->setColumnStretch(0,3);
    gridlayout->setColumnStretch(1,1);
    gridlayout->setColumnStretch(2,1);

    gridlayout->addWidget(toolBar,0,0,1,3);

    gridlayout->addWidget(label,1,0,1,3);
    gridlayout->addWidget(label2,2,0,1,3);
    gridlayout->addWidget(label3,3,0,1,3);
    gridlayout->addWidget(label4,4,0);
    gridlayout->addWidget(label5,4,1);
    gridlayout->addWidget(label6,4,2);
    this->setLayout(gridlayout);
}

void MyWidget::paintEvent(QPaintEvent *){

}

