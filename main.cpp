#include <QApplication>
#include "mainwindow.h"
#include <QTextCodec>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);



    //�޸Ľ�������
    QTextCodec::setCodecForTr(QTextCodec::codecForLocale());
    //Set Encode GBK
    QTextCodec::setCodecForTr(QTextCodec::codecForName("system"));
    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("system"));
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("system"));
    QTextCodec::setCodecForTr(QTextCodec::codecForLocale());

    MainWindow w;
    w.setWindowTitle("����ȫ������ϵͳ");
    w.show();
    return a.exec();
}
