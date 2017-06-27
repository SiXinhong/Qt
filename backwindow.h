#ifndef BACKWINDOW_H
#define BACKWINDOW_H

#include <QMainWindow>
#include"mainwindow.h"
#include<QPushButton>
#include"timetrackbar.h"

namespace Ui {
class BackWindow;
}

class BackWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit BackWindow(QWidget *parent = 0);
    ~BackWindow();
//    BackWindow *back;
    QPushButton *barBtn;
    timeTrackBar *ttbar;

    
private:
    Ui::BackWindow *ui;
private slots:
    void barBtnFunction();

};

#endif // BACKWINDOW_H

