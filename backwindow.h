#ifndef BACKWINDOW_H
#define BACKWINDOW_H
#include "mainwindow.h"
#include <QTime>
#include <QFileInfo>
class BackWindow :public MainWindow
{
public:
    BackWindow();
    ~BackWindow();
    BackWindow(QTime start,QTime stop);
    void selfTimerout();
    QTime start;
    QTime stop;
    QList<QFileInfo> *fileInfo;
    int fileIndex;
};

#endif // BACKWINDOW_H
