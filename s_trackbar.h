#ifndef S_TRACKBAR_H
#define S_TRACKBAR_H
#include "mainwindow.h"

class STrackBar: public QWidget

{
public:
    STrackBar(class MainWindow*);
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

#endif // S_TRACKBAR_H
