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
QAction* To_Tanchu;

public:
    explicit QjWidget(QWidget *parent = 0);
    void contextMenuEvent(QContextMenuEvent *);
signals:

public slots:
    //到主显示区显示菜单处理事件
    void ToZhu();
    //到凝视显示区显示菜单处理事件
    void ToNingshi();
    //到弹出窗口显示菜单处理事件
    //void ToTanchu();
};

#endif // QJWIDGET_H
