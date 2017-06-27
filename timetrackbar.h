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
    //��귽��
    void mouseReleaseEvent(QMouseEvent *);
    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *);
    QString position;//�жϻ�������ʲôλ��
    bool mousedown;
    int start;//��ʼʱ���
    int stop;//����ʱ���
    int cha;//���ŵ�ʱ�䳤��
    QString startTimes;//��ʼ��ʱ���ʽ����
    QString stopTimes;//������ʱ���ʽ����
    int pos;//��¼�������ʱ���
    int posi;//��¼x���λ��

private:
    Ui::timeTrackBar *ui;
//    class BackWindow* backWindow;

};

#endif // TIMETRACKBAR_H
