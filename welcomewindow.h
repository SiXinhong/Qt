#ifndef WELCOMEWINDOW_H
#define WELCOMEWINDOW_H

#include <QWidget>

class WelcomeWindow : public QWidget
{
    Q_OBJECT
public:
    explicit WelcomeWindow(QWidget *parent = 0);
    void paintEvent(QPaintEvent *);
signals:
    
public slots:
    
};

#endif // WELCOMEWINDOW_H
