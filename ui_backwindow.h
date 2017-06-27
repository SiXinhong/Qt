/********************************************************************************
** Form generated from reading UI file 'backwindow.ui'
**
** Created: Tue Jun 27 18:36:29 2017
**      by: Qt User Interface Compiler version 4.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_BACKWINDOW_H
#define UI_BACKWINDOW_H

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

class Ui_BackWindow
{
public:
    QWidget *centralwidget;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *BackWindow)
    {
        if (BackWindow->objectName().isEmpty())
            BackWindow->setObjectName(QString::fromUtf8("BackWindow"));
        BackWindow->resize(800, 600);
        centralwidget = new QWidget(BackWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        BackWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(BackWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 26));
        BackWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(BackWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        BackWindow->setStatusBar(statusbar);

        retranslateUi(BackWindow);

        QMetaObject::connectSlotsByName(BackWindow);
    } // setupUi

    void retranslateUi(QMainWindow *BackWindow)
    {
        BackWindow->setWindowTitle(QApplication::translate("BackWindow", "MainWindow", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class BackWindow: public Ui_BackWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BACKWINDOW_H
