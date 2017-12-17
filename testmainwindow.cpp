#include "testmainwindow.h"
#include <QDebug>

testMainWindow::testMainWindow():MainWindow()
{

}
void testMainWindow::selfProcessing(){
    qDebug()<<"testtest";
}
void testMainWindow::selfTimerout(){
    qDebug()<<"nihao";
}
