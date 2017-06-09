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
    //������ʾ����ʾ�˵������¼�
    void ToZhu()
    {
        qDebug()<<"������ʾ����";
    }
    //��������ʾ����ʾ�˵������¼�
    void ToNingshi()
    {
        qDebug()<<"��������ʾ����";
    }
    //������������ʾ�˵������¼�
    void ToTanchu(){
        qDebug()<<"���������ڡ�";
    }
};

#endif // QJWIDGET_H