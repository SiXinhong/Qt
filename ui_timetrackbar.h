/********************************************************************************
** Form generated from reading UI file 'timetrackbar.ui'
**
** Created by: Qt User Interface Compiler version 5.2.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TIMETRACKBAR_H
#define UI_TIMETRACKBAR_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

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
            timeTrackBar->setObjectName(QStringLiteral("timeTrackBar"));
        timeTrackBar->resize(800, 600);
        menubar = new QMenuBar(timeTrackBar);
        menubar->setObjectName(QStringLiteral("menubar"));
        timeTrackBar->setMenuBar(menubar);
        centralwidget = new QWidget(timeTrackBar);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        timeTrackBar->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(timeTrackBar);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        timeTrackBar->setStatusBar(statusbar);

        retranslateUi(timeTrackBar);

        QMetaObject::connectSlotsByName(timeTrackBar);
    } // setupUi

    void retranslateUi(QMainWindow *timeTrackBar)
    {
        timeTrackBar->setWindowTitle(QApplication::translate("timeTrackBar", "MainWindow", 0));
    } // retranslateUi

};

namespace Ui {
    class timeTrackBar: public Ui_timeTrackBar {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TIMETRACKBAR_H
