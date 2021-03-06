﻿#ifndef MONITOR_H
#define MONITOR_H

#include <QMainWindow>
#include <QToolButton>
#include <QBoxLayout>
#include <QGroupBox>
#include <QToolBar>
#include <QDesktopWidget>
#include <QApplication>
#include <QObjectUserData>
#include <QListWidget>
#include <QStackedLayout>
#include <QSplitter>

class Monitor;
#include "qj1widget.h"
#include "qj2widget.h"
#include "zwidget.h"
#include "nwidget1.h"
#include "nwidget2.h"
#include "mainwindow.h"
#include "hourwidget.h"


class Monitor : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow *mw;
    QStackedLayout *stackedLayout;
    QListWidget *listWidget;
     QWidget *mainWidget;
     QWidget *regionWidget;

     QVBoxLayout * mlayout;

public:
    explicit Monitor(MainWindow *mw);
    int timeIndex;
    void onSelectTime();
    HourWidget *hourWidget;

    void closeEvent(QCloseEvent *event);

private:
    //QToolBar *mainToolBar;
    QGridLayout* layout;
    QWidget *cenWidget;

    void regionWidgetShow(int i);


signals:
    
public slots:
    void widgetShow();
    void groupShow();
    void setAlert();
    void attributesModify();
    void editFunction();
    void onClickName();
    void createRG();
    //void detailsShow();
    void timeControl();
    void regionShow();
    void deleteRegion();
    void listWidgetChange(int);
    void addRegionID();
    void renameRegion();
    //优先级
    void inPri();
    void dePri();

    void deleteRegionG();
};

#endif // MONITOR_H
