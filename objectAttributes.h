#ifndef OBJECTATTRIBUTES_H
#define OBJECTATTRIBUTES_H

#include <QMainWindow>
#include <myobject.h>

class ObjectAttributes : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit ObjectAttributes(MyObject *obj);
    ~ObjectAttributes();
protected:
    void paintEvent(QPaintEvent *event);
    
private:
    MyObject *obj;
};

#endif // OBJECTATTRIBUTES_H
