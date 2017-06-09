#ifndef QJWIDGET_H
#define QJWIDGET_H

#include <QWidget>
#include <QMenu>
#include <QCursor>
#include <QDebug>

class QjWidget : public QWidget
{
    Q_OBJECT

private:
//Ui::Widget *ui;
QAction* To_Zhu;
QAction* To_Ningshi;

public:
    explicit QjWidget(QWidget *parent = 0);
    void contextMenuEvent(QContextMenuEvent *);
signals:

public slots:
    void ToZhu()
    {
        qDebug()<<"������ʾ����";
    }
    void ToNingshi()
    {
        qDebug()<<"��������ʾ����";
    }
};

#endif // QJWIDGET_H
