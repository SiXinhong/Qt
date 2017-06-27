/********************************************************************************
** Form generated from reading UI file 'objectattributes.ui'
**
** Created: Tue Jun 27 19:11:39 2017
**      by: Qt User Interface Compiler version 4.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_OBJECTATTRIBUTES_H
#define UI_OBJECTATTRIBUTES_H

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

class Ui_ObjectAttributes
{
public:
    QMenuBar *menubar;
    QWidget *centralwidget;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *ObjectAttributes)
    {
        if (ObjectAttributes->objectName().isEmpty())
            ObjectAttributes->setObjectName(QString::fromUtf8("ObjectAttributes"));
        ObjectAttributes->resize(800, 600);
        menubar = new QMenuBar(ObjectAttributes);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        ObjectAttributes->setMenuBar(menubar);
        centralwidget = new QWidget(ObjectAttributes);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        ObjectAttributes->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(ObjectAttributes);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        ObjectAttributes->setStatusBar(statusbar);

        retranslateUi(ObjectAttributes);

        QMetaObject::connectSlotsByName(ObjectAttributes);
    } // setupUi

    void retranslateUi(QMainWindow *ObjectAttributes)
    {
        ObjectAttributes->setWindowTitle(QApplication::translate("ObjectAttributes", "MainWindow", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class ObjectAttributes: public Ui_ObjectAttributes {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_OBJECTATTRIBUTES_H
