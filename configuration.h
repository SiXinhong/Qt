#ifndef CONFIGURATION_H
#define CONFIGURATION_H

class Configuration;
#include <QMainWindow>
#include <QColorDialog>
#include "mainwindow.h"

class Configuration : public QMainWindow
{
    Q_OBJECT
public:
    explicit Configuration(MainWindow *mw);
    void configure();
    MainWindow* mw;
    QGridLayout* layout;
    QWidget *cenWidget;
    QWidget *menuWidget;
    bool isStart;
     QToolButton *start;

public slots:
    void startF();
    void stateSearch();
    void minusF();
    void addF();
    void stopF();
    void backgroundCorrct();
    void shuttleCorrct();
    void okF();

    void cameraShow();
    void algorithmShow();
    void softwareShow();

    void colorSet();
};

#endif // CONFIGURATION_H
