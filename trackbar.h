#ifndef TRACKBAR_H
#define TRACKBAR_H
#include "mainwindow.h"

class TrackBar: public QWidget
{
public:
    TrackBar(class MainWindow*);
    void setPosition(int position);
    void mouseReleaseEvent(QMouseEvent *);
    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *);
private:
    class MainWindow* mainWindow;
    int position;
    bool mousedown;
};

#endif // TRACKBAR_H
