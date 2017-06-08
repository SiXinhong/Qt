/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created: Thu Jun 8 10:50:25 2017
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../mainwindow.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_MainWindow[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
      19,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      12,   11,   11,   11, 0x0a,
      25,   11,   11,   11, 0x09,
      45,   11,   11,   11, 0x09,
      61,   11,   11,   11, 0x09,
      76,   11,   11,   11, 0x09,
      91,   11,   11,   11, 0x09,
     107,   11,   11,   11, 0x09,
     126,   11,   11,   11, 0x09,
     142,   11,   11,   11, 0x09,
     163,   11,   11,   11, 0x09,
     184,   11,   11,   11, 0x09,
     206,   11,   11,   11, 0x09,
     229,   11,   11,   11, 0x09,
     244,   11,   11,   11, 0x09,
     264,   11,   11,   11, 0x09,
     281,   11,   11,   11, 0x09,
     301,   11,   11,   11, 0x09,
     317,   11,   11,   11, 0x09,
     333,   11,   11,   11, 0x09,

       0        // eod
};

static const char qt_meta_stringdata_MainWindow[] = {
    "MainWindow\0\0onTimerOut()\0startStopFunction()\0"
    "mstopFunction()\0openFunction()\0"
    "playFunction()\0rstopFunction()\0"
    "timeLineFunction()\0automFunction()\0"
    "brightnessFunction()\0saturationFunction()\0"
    "pseudoColorFunction()\0serialNumberFunction()\0"
    "timeFunction()\0openCloseFunction()\0"
    "manualFunction()\0attributeFunction()\0"
    "setUpFunction()\0voiceFunction()\0"
    "lightFunction()\0"
};

const QMetaObject MainWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_MainWindow,
      qt_meta_data_MainWindow, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &MainWindow::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow))
        return static_cast<void*>(const_cast< MainWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: onTimerOut(); break;
        case 1: startStopFunction(); break;
        case 2: mstopFunction(); break;
        case 3: openFunction(); break;
        case 4: playFunction(); break;
        case 5: rstopFunction(); break;
        case 6: timeLineFunction(); break;
        case 7: automFunction(); break;
        case 8: brightnessFunction(); break;
        case 9: saturationFunction(); break;
        case 10: pseudoColorFunction(); break;
        case 11: serialNumberFunction(); break;
        case 12: timeFunction(); break;
        case 13: openCloseFunction(); break;
        case 14: manualFunction(); break;
        case 15: attributeFunction(); break;
        case 16: setUpFunction(); break;
        case 17: voiceFunction(); break;
        case 18: lightFunction(); break;
        default: ;
        }
        _id -= 19;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
