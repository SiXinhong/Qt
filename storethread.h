#ifndef STORETHREAD_H
#define STORETHREAD_H

class StoreThread;
#include<QThread>
#include<QWaitCondition>
#include<QMutex>
#include"mainwindow.h"

class StoreThread:public QThread
{

public:
    StoreThread(MainWindow *mw);
    void run();
    quint64 getDiskFreeSpace(QString driver);//获取某个盘的剩余空间
    MainWindow *mw;
    QWaitCondition  con;
    QMutex mutex;
};

#endif // STORETHREAD_H
