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
    volatile int bright_TrackbarValue;
    volatile int alpha_contrast;
    volatile bool isPseudo;
private:
    void updateBright(Mat &mat1,int bright);
    void updateContrast(Mat &mat1,int contrast);
    Mat setPseudocolor(Mat& image);

};

#endif // INTERFACETHREAD_H
