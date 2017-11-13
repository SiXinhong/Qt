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

public:
    explicit Monitor(MainWindow *mw);

private:
    QToolBar *mainToolBar;
    QGridLayout* layout;
    QWidget *cenWidget;

signals:
    
public slots:
    void widgetShow();
    void groupShow();
    void setAlert();
    void attributesModify();
    void exitFunction();
    void onClickName();
    
};

#endif // MONITOR_H
