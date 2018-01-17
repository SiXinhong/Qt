#ifndef SENSITIVITY_H
#define SENSITIVITY_H

#include <QWidget>
class Sensitivity;
#include "mainwindow.h"

class Sensitivity : public QWidget
{
    Q_OBJECT
public:
    explicit Sensitivity(MainWindow *mw);

    void mouseReleaseEvent(QMouseEvent *event);
    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *event);

    MainWindow *mw;
    int position;
    bool mousedown;

signals:

public slots:

};

#endif // SENSITIVITY_H
