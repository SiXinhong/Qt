#include "backwindow.h"
#include "ui_backwindow.h"
#include<QDebug>
#include"mainwindow.h"

extern QDateTime dateTimeStart;
extern QDateTime dateTimeStop;
BackWindow::BackWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::BackWindow)
{
    ui->setupUi(this);
    barBtn=new QPushButton("Ê±¼äÏß",this);
    connect(barBtn,SIGNAL(clicked()),this,SLOT(barBtnFunction()));
}

BackWindow::~BackWindow()
{
    delete ui;
}
void BackWindow::barBtnFunction()
{
    ttbar=new timeTrackBar(this);
    ttbar->show();
}

