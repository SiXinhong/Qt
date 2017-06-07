/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created: Wed Jun 7 11:44:59 2017
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
    QAction *start_stop1;
    QAction *open;
    QAction *stop1;
    QAction *action_3;
    QAction *action_4;
    QAction *action_5;
    QAction *action_6;
    QAction *action_7;
    QAction *automatic;
    QAction *brightness;
    QAction *saturation;
    QAction *pseudoColor;
    QAction *start_stop2;
    QAction *manual;
    QAction *attribute;
    QAction *set;
    QAction *action_16;
    QAction *action_17;
    QAction *play;
    QAction *stop2;
    QAction *action;
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
        start_stop1 = new QAction(MainWindow);
        start_stop1->setObjectName(QString::fromUtf8("start_stop1"));
        open = new QAction(MainWindow);
        open->setObjectName(QString::fromUtf8("open"));
        stop1 = new QAction(MainWindow);
        stop1->setObjectName(QString::fromUtf8("stop1"));
        action_3 = new QAction(MainWindow);
        action_3->setObjectName(QString::fromUtf8("action_3"));
        action_4 = new QAction(MainWindow);
        action_4->setObjectName(QString::fromUtf8("action_4"));
        action_5 = new QAction(MainWindow);
        action_5->setObjectName(QString::fromUtf8("action_5"));
        action_6 = new QAction(MainWindow);
        action_6->setObjectName(QString::fromUtf8("action_6"));
        action_7 = new QAction(MainWindow);
        action_7->setObjectName(QString::fromUtf8("action_7"));
        automatic = new QAction(MainWindow);
        automatic->setObjectName(QString::fromUtf8("automatic"));
        brightness = new QAction(MainWindow);
        brightness->setObjectName(QString::fromUtf8("brightness"));
        saturation = new QAction(MainWindow);
        saturation->setObjectName(QString::fromUtf8("saturation"));
        pseudoColor = new QAction(MainWindow);
        pseudoColor->setObjectName(QString::fromUtf8("pseudoColor"));
        start_stop2 = new QAction(MainWindow);
        start_stop2->setObjectName(QString::fromUtf8("start_stop2"));
        manual = new QAction(MainWindow);
        manual->setObjectName(QString::fromUtf8("manual"));
        attribute = new QAction(MainWindow);
        attribute->setObjectName(QString::fromUtf8("attribute"));
        set = new QAction(MainWindow);
        set->setObjectName(QString::fromUtf8("set"));
        action_16 = new QAction(MainWindow);
        action_16->setObjectName(QString::fromUtf8("action_16"));
        action_17 = new QAction(MainWindow);
        action_17->setObjectName(QString::fromUtf8("action_17"));
        play = new QAction(MainWindow);
        play->setObjectName(QString::fromUtf8("play"));
        stop2 = new QAction(MainWindow);
        stop2->setObjectName(QString::fromUtf8("stop2"));
        action = new QAction(MainWindow);
        action->setObjectName(QString::fromUtf8("action"));
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
        monitoring->addAction(start_stop1);
        monitoring->addAction(stop1);
        playback->addAction(open);
        playback->addAction(play);
        playback->addAction(stop2);
        image->addAction(automatic);
        image->addAction(brightness);
        image->addAction(saturation);
        image->addAction(pseudoColor);
        image->addAction(action);
        alarm->addAction(start_stop2);
        alarm->addAction(manual);
        alarm->addAction(attribute);
        alarm->addAction(set);
        alarm->addAction(action_16);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0, QApplication::UnicodeUTF8));
        start_stop1->setText(QApplication::translate("MainWindow", "\345\220\257/\345\201\234", 0, QApplication::UnicodeUTF8));
        open->setText(QApplication::translate("MainWindow", "\346\211\223\345\274\200", 0, QApplication::UnicodeUTF8));
        stop1->setText(QApplication::translate("MainWindow", "\346\232\202\345\201\234", 0, QApplication::UnicodeUTF8));
        action_3->setText(QApplication::translate("MainWindow", "\351\200\200\345\207\272\345\256\236\346\227\266\347\233\221\346\216\247", 0, QApplication::UnicodeUTF8));
        action_4->setText(QApplication::translate("MainWindow", "\346\240\241\346\255\243\347\233\270\346\234\272", 0, QApplication::UnicodeUTF8));
        action_5->setText(QApplication::translate("MainWindow", "\347\233\270\346\234\272\350\260\203\347\204\246", 0, QApplication::UnicodeUTF8));
        action_6->setText(QApplication::translate("MainWindow", "\345\217\202\346\225\260\350\256\276\347\275\256", 0, QApplication::UnicodeUTF8));
        action_7->setText(QApplication::translate("MainWindow", "\347\233\270\346\234\272\347\212\266\346\200\201", 0, QApplication::UnicodeUTF8));
        automatic->setText(QApplication::translate("MainWindow", "\350\207\252\345\212\250", 0, QApplication::UnicodeUTF8));
        brightness->setText(QApplication::translate("MainWindow", "\344\272\256\345\272\246", 0, QApplication::UnicodeUTF8));
        saturation->setText(QApplication::translate("MainWindow", "\351\245\261\345\222\214\345\272\246", 0, QApplication::UnicodeUTF8));
        pseudoColor->setText(QApplication::translate("MainWindow", "\344\274\252\345\275\251\350\211\262", 0, QApplication::UnicodeUTF8));
        start_stop2->setText(QApplication::translate("MainWindow", "\345\274\200/\345\205\263", 0, QApplication::UnicodeUTF8));
        manual->setText(QApplication::translate("MainWindow", "\346\211\213\345\212\250", 0, QApplication::UnicodeUTF8));
        attribute->setText(QApplication::translate("MainWindow", "\345\261\236\346\200\247", 0, QApplication::UnicodeUTF8));
        set->setText(QApplication::translate("MainWindow", "\350\256\276\347\275\256", 0, QApplication::UnicodeUTF8));
        action_16->setText(QApplication::translate("MainWindow", "\345\243\260\351\237\263", 0, QApplication::UnicodeUTF8));
        action_17->setText(QApplication::translate("MainWindow", "\345\205\263\344\272\216", 0, QApplication::UnicodeUTF8));
        play->setText(QApplication::translate("MainWindow", "\346\222\255\346\224\276", 0, QApplication::UnicodeUTF8));
        stop2->setText(QApplication::translate("MainWindow", "\346\232\202\345\201\234", 0, QApplication::UnicodeUTF8));
        action->setText(QApplication::translate("MainWindow", "\347\274\226\345\217\267", 0, QApplication::UnicodeUTF8));
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
