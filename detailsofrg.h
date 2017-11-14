#ifndef DETAILSOFRG_H
#define DETAILSOFRG_H

#include <QMainWindow>
class DetailsOfRG;
#include "mainwindow.h"



class DetailsOfRG : public QMainWindow
{
    Q_OBJECT
public:
    explicit DetailsOfRG(MainWindow *mw,int index);
    void closeEvent(QCloseEvent *);
    void detailsShow();
     MainWindow *mw;
     int index;
     QGridLayout* layout;
     QWidget *cenWidget;


signals:
    
public slots:
    
};

#endif // DETAILSOFRG_H
