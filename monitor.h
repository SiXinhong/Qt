#ifndef MONITOR_H
#define MONITOR_H

#include <QMainWindow>
#include <QToolButton>
#include <QBoxLayout>
#include <QGroupBox>
#include <QToolBar>
#include <QDesktopWidget>
#include <QApplication>
#include <QObjectUserData>

class Monitor;
#include "qj1widget.h"
#include "qj2widget.h"
#include "zwidget.h"
#include "nwidget1.h"
#include "nwidget2.h"
#include "mainwindow.h"
#include "detailsofrg.h"
//#include "timecontrol.h"


class Monitor : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow *mw;

public:
    explicit Monitor(MainWindow *mw);



private:
    //QToolBar *mainToolBar;
    QGridLayout* layout;
    QWidget *cenWidget;




signals:
    
public slots:
    void widgetShow();
    void groupShow();
    void setAlert();
    void attributesModify();
    void editFunction();
    void onClickName();
    void createRG();
    void detailsShow();
    void timeControl();
};

#endif // MONITOR_H
