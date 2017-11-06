/********************************************************************************
** Form generated from reading UI file 'timetrackbar.ui'
**
** Created: Sat Nov 4 15:41:16 2017
**      by: Qt User Interface Compiler version 4.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TIMETRACKBAR_H
#define UI_TIMETRACKBAR_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QMainWindow>
#include <QtGui/QMenuBar>
#include <QtGui/QStatusBar>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_timeTrackBar
{
public:
    QMenuBar *menubar;
    QWidget *centralwidget;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *timeTrackBar)
    {
        if (timeTrackBar->objectName().isEmpty())
            timeTrackBar->setObjectName(QString::fromUtf8("timeTrackBar"));
        timeTrackBar->resize(800, 600);
        menubar = new QMenuBar(timeTrackBar);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        timeTrackBar->setMenuBar(menubar);
        centralwidget = new QWidget(timeTrackBar);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        timeTrackBar->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(timeTrackBar);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        timeTrackBar->setStatusBar(statusbar);

        retranslateUi(timeTrackBar);

        QMetaObject::connectSlotsByName(timeTrackBar);
    } // setupUi

    void retranslateUi(QMainWindow *timeTrackBar)
    {
        timeTrackBar->setWindowTitle(QApplication::translate("timeTrackBar", "MainWindow", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class timeTrackBar: public Ui_timeTrackBar {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TIMETRACKBAR_H
