#ifndef TRACKBAR_H
#define TRACKBAR_H

class TrackBar;
#include "configuration.h"

class TrackBar: public QWidget
{
public:
    TrackBar(Configuration *configuration);
    void setPosition(int position);
    void mouseReleaseEvent(QMouseEvent *);
    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *);
private:
    Configuration *configuration;
    int position;
    bool mousedown;
};

#endif // TRACKBAR_H
