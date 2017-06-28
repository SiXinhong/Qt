//#ifndef BACKWINDOW_H
//#define BACKWINDOW_H

//#include <QMainWindow>
//#include"mainwindow.h"
//#include<QPushButton>
//#include"timetrackbar.h"

//namespace Ui {
//class BackWindow;
//}

//class BackWindow : public QMainWindow
//{
//    Q_OBJECT
    
//public:
//    explicit BackWindow(QWidget *parent = 0);
//    ~BackWindow();
////    BackWindow *back;
//    QPushButton *barBtn;
//    timeTrackBar *ttbar;

    
//private:
//    Ui::BackWindow *ui;
//private slots:
//    void barBtnFunction();

//};

//#endif // BACKWINDOW_H
#ifndef BACKWINDOW_H
#define BACKWINDOW_H

#include <QMainWindow>
#include"mainwindow.h"
#include<QPushButton>
#include"timetrackbar.h"

<<<<<<< HEAD
using namespace cv;
using namespace std;

#include"mainwindow.h"
#include<QPushButton>
#include"timetrackbar.h"

=======
>>>>>>> 03404bf2174822342ad3e06de98c11bd47e45174
namespace Ui {
class BackWindow;
}

class BackWindow : public QMainWindow
{
    Q_OBJECT
<<<<<<< HEAD

=======
    
>>>>>>> 03404bf2174822342ad3e06de98c11bd47e45174
public:
    explicit BackWindow(QWidget *parent = 0);
    ~BackWindow();
//    BackWindow *back;
    QPushButton *barBtn;
    timeTrackBar *ttbar;

<<<<<<< HEAD

=======
    
>>>>>>> 03404bf2174822342ad3e06de98c11bd47e45174
private:
    Ui::BackWindow *ui;
private slots:
    void barBtnFunction();

};

#endif // BACKWINDOW_H
<<<<<<< HEAD
=======

>>>>>>> 03404bf2174822342ad3e06de98c11bd47e45174
