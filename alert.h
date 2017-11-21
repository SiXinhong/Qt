#ifndef ALERT_H
#define ALERT_H

#include <QMainWindow>
#include "mainwindow.h"
#include "myobject.h"

class Alert : public QMainWindow
{
    Q_OBJECT
public:
    explicit Alert(MainWindow *mw, vector<MyObject> os);
    void alertInfo();
    MainWindow* mw;
    vector<MyObject> os;
    QGridLayout* layout;
    QWidget *cenWidget;


signals:
    
public slots:
    
};

#endif // ALERT_H
