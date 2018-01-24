#ifndef INTERFACETHREAD_H
#define INTERFACETHREAD_H
#include <QThread>
#include "myinterface.h"
#include <QMutex>
#include <QWaitCondition>


class InterfaceThread : public QThread
{
public:
    InterfaceThread();
    void run();
    MyInterface in;
    bool isOk;//通信是否已经结束，可以取出pano和objs
    int v;//getIntegratedData的返回值
    QMutex mutex;
    QWaitCondition fullCond;
    QWaitCondition emptyCond;
    int getIntegratedData();
    Mat getPano();
    vector<MyObject> getObjs();
    vector<TrackingPoint> GetTps();
    void getNext();
};

#endif // INTERFACETHREAD_H
