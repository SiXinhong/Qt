#ifndef MYLABEL_H
#define MYLABEL_H

#include <QLabel>

class MyLabel : public QLabel
{
    Q_OBJECT
public:
    explicit MyLabel(QWidget *parent = 0);
    void paintEvent(QPaintEvent *);
signals:
    
public slots:
    
};

#endif // MYLABEL_H
