﻿#include <QApplication>
#include "mainwindow.h"
#include <QTextCodec>

#pragma execution_character_set("utf-8")
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);



    //修改界面乱码
//    QTextCodec::setCodecForTr(QTextCodec::codecForLocale());
//    //Set Encode GBK
//    QTextCodec::setCodecForTr(QTextCodec::codecForName("system"));
//    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("system"));
//    QTextCodec::setCodecForLocale(QTextCodec::codecForName("system"));
//    QTextCodec::setCodecForTr(QTextCodec::codecForLocale());

    WelcomeWindow *welcome=new WelcomeWindow();
    //MainWindow w(welcome);
    //w.setA(a);
    // w.setWindowTitle("红外全景控制系统");
    //w.show();
    return a.exec();
}
