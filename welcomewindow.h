#ifndef WELCOMEWINDOW_H
#define WELCOMEWINDOW_H

#include <QWidget>
#include<QToolBar>
#include<QGridLayout>
#include<QLineEdit>
#include<QToolButton>
class WelcomeWindow;
#include "mainwindow.h"

class WelcomeWindow : public QWidget
{
    Q_OBJECT
public:
    explicit WelcomeWindow(QWidget *parent = 0);
    void paintEvent(QPaintEvent *);
    //void setMainwindow(MainWindow mainwindow);
    QLineEdit *usernameInput;
    QLineEdit *passwordInput;
    QToolButton *logIn;
    QToolButton *exit;
    MainWindow *mainwindow;
    bool start;

signals:
    
public slots:
    void exitClicked();
    void loginClicked();
};

#endif // WELCOMEWINDOW_H

