#ifndef HOURWIDGET_H
#define HOURWIDGET_H

#include <QWidget>
#include <QToolButton>
class HourWidget;
#include "monitor.h"


class HourWidget : public QWidget
{
    Q_OBJECT
public:
    explicit HourWidget(Monitor *monitor);
    bool isActive[7][48];
    void paintEvent(QPaintEvent *);
    void mouseReleaseEvent(QMouseEvent *e);


    int xStart;
    int yStart;
    int w;
    int h;
private:

    QString stringOfDay[7];
    QToolButton *btn;
    Monitor *monitor;
    QLabel *use;
    QLabel *noUse;
    QLabel *unit;


signals:

public slots:
    void saveTime();

};

#endif // HOURWIDGET_H
