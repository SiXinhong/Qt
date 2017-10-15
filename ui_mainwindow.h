/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created: Sun Oct 15 23:10:27 2017
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
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *action;
    QAction *action_2;
    QAction *action_3;
    QAction *action_4;
    QAction *action_5;
    QAction *action_6;
    QAction *action_7;
    QAction *action_8;
    QAction *action_9;
    QAction *action_10;
    QAction *action_11;
    QAction *action_13;
    QAction *action_14;
    QAction *action_15;
    QAction *action_16;
    QAction *action_17;
    QWidget *centralWidget;
    QMenuBar *menuBar;
    QMenu *menu;
    QMenu *menu_2;
    QMenu *menu_3;
    QMenu *menu_4;
    QMenu *menu_5;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1400, 900);
        action = new QAction(MainWindow);
        action->setObjectName(QString::fromUtf8("action"));
        action_2 = new QAction(MainWindow);
        action_2->setObjectName(QString::fromUtf8("action_2"));
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
        action_8 = new QAction(MainWindow);
        action_8->setObjectName(QString::fromUtf8("action_8"));
        action_9 = new QAction(MainWindow);
        action_9->setObjectName(QString::fromUtf8("action_9"));
        action_10 = new QAction(MainWindow);
        action_10->setObjectName(QString::fromUtf8("action_10"));
        action_11 = new QAction(MainWindow);
        action_11->setObjectName(QString::fromUtf8("action_11"));
        action_13 = new QAction(MainWindow);
        action_13->setObjectName(QString::fromUtf8("action_13"));
        action_14 = new QAction(MainWindow);
        action_14->setObjectName(QString::fromUtf8("action_14"));
        action_15 = new QAction(MainWindow);
        action_15->setObjectName(QString::fromUtf8("action_15"));
        action_16 = new QAction(MainWindow);
        action_16->setObjectName(QString::fromUtf8("action_16"));
        action_17 = new QAction(MainWindow);
        action_17->setObjectName(QString::fromUtf8("action_17"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1400, 23));
        menu = new QMenu(menuBar);
        menu->setObjectName(QString::fromUtf8("menu"));
        menu_2 = new QMenu(menuBar);
        menu_2->setObjectName(QString::fromUtf8("menu_2"));
        menu_3 = new QMenu(menuBar);
        menu_3->setObjectName(QString::fromUtf8("menu_3"));
        menu_4 = new QMenu(menuBar);
        menu_4->setObjectName(QString::fromUtf8("menu_4"));
        menu_5 = new QMenu(menuBar);
        menu_5->setObjectName(QString::fromUtf8("menu_5"));
        MainWindow->setMenuBar(menuBar);

        menuBar->addAction(menu->menuAction());
        menuBar->addAction(menu_2->menuAction());
        menuBar->addAction(menu_3->menuAction());
        menuBar->addAction(menu_4->menuAction());
        menuBar->addAction(menu_5->menuAction());
        menu->addAction(action);
        menu->addAction(action_2);
        menu->addAction(action_3);
        menu->addAction(action_4);
        menu->addAction(action_5);
        menu->addAction(action_6);
        menu->addAction(action_7);
        menu->addAction(action_8);
        menu->addAction(action_9);
        menu_2->addAction(action_10);
        menu_2->addAction(action_11);
        menu_2->addSeparator();
        menu_2->addAction(action_13);
        menu_3->addAction(action_14);
        menu_3->addAction(action_15);
        menu_4->addAction(action_16);
        menu_4->addAction(action_17);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0, QApplication::UnicodeUTF8));
        action->setText(QApplication::translate("MainWindow", "\350\277\236\346\216\245", 0, QApplication::UnicodeUTF8));
        action_2->setText(QApplication::translate("MainWindow", "\346\226\255\345\274\200", 0, QApplication::UnicodeUTF8));
        action_3->setText(QApplication::translate("MainWindow", "\346\211\223\345\274\200", 0, QApplication::UnicodeUTF8));
        action_4->setText(QApplication::translate("MainWindow", "\345\233\236\346\224\276", 0, QApplication::UnicodeUTF8));
        action_5->setText(QApplication::translate("MainWindow", "\345\205\263\351\227\255", 0, QApplication::UnicodeUTF8));
        action_6->setText(QApplication::translate("MainWindow", "\346\234\200\350\277\221\350\247\206\351\242\221", 0, QApplication::UnicodeUTF8));
        action_7->setText(QApplication::translate("MainWindow", "\345\210\207\346\215\242\347\224\250\346\210\267", 0, QApplication::UnicodeUTF8));
        action_8->setText(QApplication::translate("MainWindow", "\345\220\257\345\212\250\345\256\211\350\243\205\345\220\221\345\257\274", 0, QApplication::UnicodeUTF8));
        action_9->setText(QApplication::translate("MainWindow", "\351\200\200\345\207\272", 0, QApplication::UnicodeUTF8));
        action_10->setText(QApplication::translate("MainWindow", "\351\205\215\347\275\256", 0, QApplication::UnicodeUTF8));
        action_11->setText(QApplication::translate("MainWindow", "\344\277\235\345\255\230\345\275\223\345\211\215\350\256\276\347\275\256", 0, QApplication::UnicodeUTF8));
        action_13->setText(QApplication::translate("MainWindow", "\345\210\233\345\273\272\346\210\226\347\274\226\350\276\221\345\214\272\345\237\237", 0, QApplication::UnicodeUTF8));
        action_14->setText(QApplication::translate("MainWindow", "\345\261\217\345\271\225\346\210\252\345\233\276", 0, QApplication::UnicodeUTF8));
        action_15->setText(QApplication::translate("MainWindow", "\346\270\205\346\264\227\351\225\234\345\244\264", 0, QApplication::UnicodeUTF8));
        action_16->setText(QApplication::translate("MainWindow", "\351\232\220\350\227\217\346\212\245\350\255\246\344\277\241\346\201\257", 0, QApplication::UnicodeUTF8));
        action_17->setText(QApplication::translate("MainWindow", "\346\230\276\347\244\272\346\212\245\350\255\246\344\277\241\346\201\257", 0, QApplication::UnicodeUTF8));
        menu->setTitle(QApplication::translate("MainWindow", "\346\226\207\344\273\266", 0, QApplication::UnicodeUTF8));
        menu_2->setTitle(QApplication::translate("MainWindow", "\351\200\211\351\241\271", 0, QApplication::UnicodeUTF8));
        menu_3->setTitle(QApplication::translate("MainWindow", "\345\267\245\345\205\267", 0, QApplication::UnicodeUTF8));
        menu_4->setTitle(QApplication::translate("MainWindow", "\346\230\276\347\244\272", 0, QApplication::UnicodeUTF8));
        menu_5->setTitle(QApplication::translate("MainWindow", "\345\270\256\345\212\251", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
