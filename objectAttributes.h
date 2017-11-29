#ifndef OBJECTATTRIBUTES_H
#define OBJECTATTRIBUTES_H

#include <QMainWindow>
#include <myobject.h>
#include "myinterface.h"
#include <cv.h>
//#include "mainwindow.h"
#include<QImage>
#include<QToolButton>
#include <QToolBar>

class ObjectAttributes : public QMainWindow
{
    Q_OBJECT
public slots:
    void objectsShow();
    void exitFunction();
private:
    QToolButton *existButton;
    QToolBar *mainToolBar;
    int index2Show;
    
public:
    explicit ObjectAttributes(vector<MyObject> objs);
    void addMyToolBar();
    ~ObjectAttributes();
protected:
    void paintEvent(QPaintEvent *event);

    
private:
   // MyInterface *objectInterface;
    vector<MyObject> objs;
};

#endif // OBJECTATTRIBUTES_H
