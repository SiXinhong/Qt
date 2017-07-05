#ifndef BACKWINDOW_H
#define BACKWINDOW_H
#include "mainwindow.h"
#include <QTime>
#include <QFileInfo>
#include "timeline.h"
class BackWindow :public MainWindow
{
public:
    BackWindow();
    ~BackWindow();
    BackWindow(QDate date,QTime start,QTime stop);
    void selfTimerout();
    QDate date;
    QTime start;
    QTime stop;
    QList<QFileInfo> *fileInfo;
    int fileIndex;
    void exitFunction();
    void addMyToolBar_backWindow();

    class TimeLine *timeLine;
    void timeLineFunction();
};

#endif // BACKWINDOW_H
