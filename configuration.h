#ifndef CONFIGURATION_H
#define CONFIGURATION_H

class Configuration;
#include <QMainWindow>
#include <QColorDialog>
#include "mainwindow.h"
#include <QLabel>
#include <QWidget>
#include <QStackedLayout>

class Configuration : public QMainWindow
{
    Q_OBJECT
public:
    explicit Configuration(MainWindow *mw);
    void configure();
    MainWindow* mw;
    QGridLayout* layoutCamera;
    QGridLayout* layoutAlgorithm;
    QGridLayout* layoutSoftWare;
    QStackedLayout *stackedLayout;
    QWidget *cenWidgetCamera;
    QWidget *cenWidgetAlgorithm;
    QWidget *cenWidgetSoftWare;
    QWidget *menuWidget;
    bool isStart;
     QToolButton *start;
     QColor color;
     int zRed;
     int zBlue;
     int zGreen;

     int n1Red;
     int n1Blue;
     int n1Green;

     int n2Red;
     int n2Blue;
     int n2Green;
      QToolButton *zhan ;
     QWidget *imageWidget;
     QLabel *imageLabel;
     void buildCenWidgetCamera();
     void buildCenWidgetAlgorithm();
     void buildCenWidgetSoftWare();
     void setCameraMat(Mat mat);

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
    void zhanModify();
    void resizeEvent(QResizeEvent *);
};

#endif // CONFIGURATION_H
