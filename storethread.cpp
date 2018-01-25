#include "storethread.h"

StoreThread::StoreThread(MainWindow *mw)
{
    this->mw = mw;
}

void StoreThread::run(){
    long long maxSize = 1024L;
    maxSize*=1024L*2000;
//    maxSize*=1024L*1024L*100L;
    bool isReachMax = false;


    QString dirName = QString("./回放/");
    QDir dir(dirName);
    if(!dir.exists(dirName)){
        dir.mkdir(dirName);
    }
    while(true){
        mutex.lock();
        con.wait(&mutex);
        if(mw->isJixu == false){
            mutex.unlock();
            continue;
        }
qDebug()<<"++++++++++++++++++++++++++++++++++++++++++++++++++++thread:"<<QThread::currentThreadId();
        if(!isReachMax){
            mw->unitSize = mw->getMemory(dirName);
            if(mw->unitSize > maxSize){
                isReachMax = true;
            }
            while( mw->unitSize > maxSize){
                qDebug()<<" inremove";
                mw->removeFile(dirName);
            }
        }else{
            mw->removeFile(dirName);
        }


        QString today=dirName+QDate::currentDate().toString("yyyy-MM-dd");
        bool exist= mw->directory->exists(today);
        if(!exist){
            mw->directory->mkdir(today);
        }



        if(mw->isJixu == true){
            vector<MyObject> objs;
            for(int i=0;i<objs.size();i++){
                QString current_time=QTime::currentTime().toString("hh-mm-ss");
                QString current_path=QString("").append(today).append("/").append(current_time).append("-").append(QString::number(i)).append(".dat");
                QFile file(current_path);
                file.open(QIODevice::WriteOnly);
                QDataStream out(&file);
                out<<objs.at(i);
                file.close();
                current_time.clear();
                current_path.clear();
            }
        }

        if(mw->isJixu == true){
            Mat pano = mw->mainPano;//mw->in.getPano();
            QString current_time=QTime::currentTime().toString("hh-mm-ss");
            QString current_path=QString("").append(today).append("/").append(current_time).append(".pan");
            QFile file(current_path);
            qDebug()<<"filePath:"<<current_path;
            file.open(QIODevice::WriteOnly);
            QDataStream out(&file);
            if(pano.empty()){
                out<<-1;
            }else{
                out<<1;
                MyObject::writeMat(out,pano);
            }
            file.close();
            current_time.clear();
            current_path.clear();
        }
        mutex.unlock();
    }
}



