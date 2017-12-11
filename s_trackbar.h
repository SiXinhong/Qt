#ifndef S_TRACKBAR_H
#define S_TRACKBAR_H

class STrackBar;
#include "configuration.h"

class STrackBar: public QWidget
{
    Q_OBJECT
public:
    STrackBar(Configuration *configuration);
    void setPosition(int position);
    void mouseReleaseEvent(QMouseEvent *);
    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *);

private:
    double position;
    bool mousedown;
    Configuration *configuration;
};

#endif // S_TRACKBAR_H
