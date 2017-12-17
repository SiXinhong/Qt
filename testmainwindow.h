#ifndef TESTMAINWINDOW_H
#define TESTMAINWINDOW_H
#include "mainwindow.h"

class testMainWindow : public MainWindow
{
public:
    testMainWindow();
    void selfProcessing();
    void selfTimerout();
};

#endif // TESTMAINWINDOW_H
