/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created: Thu Jun 8 10:30:25 2017
**      by: Qt User Interface Compiler version 4.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QStatusBar>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QMenuBar *menuBar;
    QMenu *monitoring;
    QMenu *playback;
    QMenu *image;
    QMenu *alarm;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1400, 900);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1400, 26));
        monitoring = new QMenu(menuBar);
        monitoring->setObjectName(QString::fromUtf8("monitoring"));
        playback = new QMenu(menuBar);
        playback->setObjectName(QString::fromUtf8("playback"));
        image = new QMenu(menuBar);
        image->setObjectName(QString::fromUtf8("image"));
        alarm = new QMenu(menuBar);
        alarm->setObjectName(QString::fromUtf8("alarm"));
        MainWindow->setMenuBar(menuBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(monitoring->menuAction());
        menuBar->addAction(playback->menuAction());
        menuBar->addAction(image->menuAction());
        menuBar->addAction(alarm->menuAction());

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0, QApplication::UnicodeUTF8));
        monitoring->setTitle(QApplication::translate("MainWindow", "\347\233\221\346\216\247", 0, QApplication::UnicodeUTF8));
        playback->setTitle(QApplication::translate("MainWindow", "\345\233\236\346\224\276", 0, QApplication::UnicodeUTF8));
        image->setTitle(QApplication::translate("MainWindow", "\345\233\276\345\203\217", 0, QApplication::UnicodeUTF8));
        alarm->setTitle(QApplication::translate("MainWindow", "\345\221\212\350\255\246", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
