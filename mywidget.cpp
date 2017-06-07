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
    //����ͼƬ1
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
                QImage* img=new QImage,* scaledimg=new QImage;//�ֱ𱣴�ԭͼ������֮���ͼƬ
                img->load(filename);
//                if(! ( img->load(filename) ) ) //����ͼ��
//                {
//                    QMessageBox::information(this,tr("��ͼ��ʧ��"),tr("��ͼ��ʧ��!"));
//                    delete img;
//                    return;
//                }
                int Owidth=img->width(),Oheight=img->height();
                int Fwidth,Fheight;       //���ź��ͼƬ��С
//                label->setGeometry(0,0,400,300);
                int Mul;            //��¼ͼƬ��label��С�ı�������������ͼƬ
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
    //����ͼƬ2
    QLabel *label2=new QLabel(this);
    label2-> setStyleSheet("QLabel{background:rgb(255,255,255);"
                            "image: url(./s1/1.bmp);}");
    //����ͼƬ3
    QLabel *label3=new QLabel(this);
    label3-> setStyleSheet("QLabel{background:rgb(255,255,255);"
                            "image: url(./s1/1.bmp);}");
    //����ͼƬ4
    QLabel *label4=new QLabel(this);
    label4-> setStyleSheet("QLabel{background:rgb(255,255,255);"
                            "image: url(./s1/1.bmp);}");
    //����ͼƬ5
    QLabel *label5=new QLabel(this);
    label5-> setStyleSheet("QLabel{background:rgb(255,255,255);"
                            "image: url(./21.png);}");
    //����ͼƬ6
    QLabel *label6=new QLabel(this);
    label6-> setStyleSheet("QLabel{background:rgb(255,255,255);"
                            "image: url(./21.png);}");


    // �����������������˲��š���ͣ��ֹͣ����
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

