/********************************************************************************
** Form generated from reading UI file 'backwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.2.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_BACKWINDOW_H
#define UI_BACKWINDOW_H

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

class Ui_BackWindow
{
public:
    QWidget *centralwidget;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *BackWindow)
    {
        if (BackWindow->objectName().isEmpty())
            BackWindow->setObjectName(QStringLiteral("BackWindow"));
        BackWindow->resize(800, 600);
        centralwidget = new QWidget(BackWindow);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        BackWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(BackWindow);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 26));
        BackWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(BackWindow);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        BackWindow->setStatusBar(statusbar);

        retranslateUi(BackWindow);

        QMetaObject::connectSlotsByName(BackWindow);
    } // setupUi

    void retranslateUi(QMainWindow *BackWindow)
    {
        BackWindow->setWindowTitle(QApplication::translate("BackWindow", "MainWindow", 0));
    } // retranslateUi

};

namespace Ui {
    class BackWindow: public Ui_BackWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BACKWINDOW_H
