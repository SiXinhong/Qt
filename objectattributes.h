#ifndef OBJECTATTRIBUTES_H
#define OBJECTATTRIBUTES_H

#include <QMainWindow>
#include <myobject.h>
#include "myinterface.h"
#include <cv.h>
//#include "mainwindow.h"
#include<QImage>

class ObjectAttributes : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit ObjectAttributes(MyInterface *objectInterface);
    ~ObjectAttributes();
protected:
    void paintEvent(QPaintEvent *event);

    
private:
    MyInterface *objectInterface;
};

#endif // OBJECTATTRIBUTES_H
