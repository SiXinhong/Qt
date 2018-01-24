#include "interfacethread.h"
#include <QDebug>

InterfaceThread::InterfaceThread()
{
    isOk = false;
}

int InterfaceThread::getIntegratedData(){
    mutex.lock();
    while(!isOk)
    {
        fullCond.wakeAll();
        emptyCond.wait(&mutex);
    }
    isOk = false;
    mutex.unlock();
    return v;
}

void InterfaceThread::run(){
    while(true){
        mutex.lock();
        fullCond.wait(&mutex);
        v = in.getIntegratedData();
        if(0!=v){
            qDebug()<<"interfaceThread getData2"<<currentThreadId();
            v = in.getIntegratedData2();
        }
        isOk = true;
        emptyCond.wakeAll();
        mutex.unlock();
    }
}

Mat InterfaceThread::getPano(){
    return in.getPano();
}

vector<MyObject> InterfaceThread::getObjs(){
    return in.getObjs();
}

vector<TrackingPoint> InterfaceThread::GetTps(){
    return in.tps;
}

void InterfaceThread::getNext(){
    mutex.lock();
    fullCond.wakeAll();
    mutex.unlock();
}
