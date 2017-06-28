#ifndef TIMETRACKBAR_H
#define TIMETRACKBAR_H

#include <QMainWindow>
#include <QPainter>
#include <QMouseEvent>
#include<QDateTime>
#include<QString>

namespace Ui {
class timeTrackBar;
}

class timeTrackBar : public QMainWindow
{
    Q_OBJECT

public:
    explicit timeTrackBar(QWidget *parent = 0);
    ~timeTrackBar();
    //鼠标方法
    void mouseReleaseEvent(QMouseEvent *);
    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *);
    QString position;//判断滑动条在什么位置
    bool mousedown;
    int start;//开始时间戳
    int stop;//结束时间戳
    int cha;//播放的时间长度
    QString startTimes;//开始的时间格式化后
    QString stopTimes;//结束的时间格式化后
    int pos;//记录滑动后的时间戳
    int posi;//记录x轴的位置

private:
    Ui::timeTrackBar *ui;
//    class BackWindow* backWindow;

};

#endif // TIMETRACKBAR_H
