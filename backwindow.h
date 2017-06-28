//#ifndef BACKWINDOW_H
//#define BACKWINDOW_H

//#include <QMainWindow>
//#include"mainwindow.h"
//#include<QPushButton>
//#include"timetrackbar.h"

//namespace Ui {
//class BackWindow;
//}

//class BackWindow : public QMainWindow
//{
//    Q_OBJECT
    
//public:
//    explicit BackWindow(QWidget *parent = 0);
//    ~BackWindow();
////    BackWindow *back;
//    QPushButton *barBtn;
//    timeTrackBar *ttbar;

    
//private:
//    Ui::BackWindow *ui;
//private slots:
//    void barBtnFunction();

//};

//#endif // BACKWINDOW_H
#ifndef BACKWINDOW_H
#define BACKWINDOW_H

#include <QMainWindow>

#include <QImage>
#include <QPixmap>
#include <QLabel>
#include "mylabel.h"
#include "qj1widget.h"
#include "qj2widget.h"
#include "zwidget.h"
#include "nwidget.h"
#include "hwidget.h"
#include "lwidget.h"
#include "myinterface.h"
#include "myobject.h"
#include <QGridLayout>
#include <cv.h>
#include <phonon>
#include <QToolButton>
#include <QApplication>

//OpenCVͷ�ļ�
#include <vector>
#include <highgui.h>
#include <cv.h>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

#include <QtGui/QPainter>
#include "rectan.h"
//#define arraySize 10;
//SLOGͷ�ļ�

#include <QFileDialog>
//�Ի�������Ҫ��ͷ�ļ�
#include <QLineEdit>
#include <QMessageBox>

//ͼ������Ҫ��ͷ�ļ�
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <QSlider>
#include<QLineEdit>
#include<QWidgetAction>
#include "trackbar.h"
//#include"ltrackbar.h"
//�ط�����Ҫ��ͷ�ļ�
//#include"backwindow.h"
#include<QDateEdit>
#include<QDateTimeEdit>
#include<QPushButton>
#include <QDesktopWidget>
//ʱ������Ҫ��ͷ�ļ�
#include"timetrackbar.h"

using namespace cv;
using namespace std;

#include"mainwindow.h"
#include<QPushButton>
#include"timetrackbar.h"

namespace Ui {
class BackWindow;
}

class BackWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit BackWindow(QWidget *parent = 0);
    ~BackWindow();
//    BackWindow *back;
    QPushButton *barBtn;
    timeTrackBar *ttbar;


private:
    Ui::BackWindow *ui;
private slots:
    void barBtnFunction();

};

#endif // BACKWINDOW_H
