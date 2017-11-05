#ifndef MONITOR_H
#define MONITOR_H

#include <QMainWindow>
#include <QToolButton>
#include <QBoxLayout>
#include <QGroupBox>
#include <QToolBar>
#include <QDesktopWidget>
#include <QApplication>
class Monitor;
#include "qj1widget.h"
#include "qj2widget.h"
#include "zwidget.h"
#include "nwidget1.h"
#include "nwidget2.h"
#include "mainwindow.h"


class Monitor : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow *mw;
    Qj1Widget *qj1;
    Qj2Widget *qj2;
    ZWidget *z;
    NWidget1 *n1;
    NWidget2 *n2;
    int widget;


public:
    explicit Monitor(MainWindow *mw);
    void addMyToolBar();


private:
    QToolBar *mainToolBar;
    QMap< QString,vector<Region> > ::iterator ite;
    QMap< QString,vector<Region> > ::iterator end;
    QGridLayout* layout;
    QWidget *cenWidget;

signals:
    
public slots:
    void widgetShow();
    void groupShow();
    void isActive();
    void attributesModify();
    void exitFunction();
    void onClickName();
    
};

#endif // MONITOR_H
