#ifndef OBJECTATTRIBUTES_H
#define OBJECTATTRIBUTES_H

#include <QMainWindow>

namespace Ui {
class ObjectAttributes;
}

class ObjectAttributes : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit ObjectAttributes(QWidget *parent = 0);
    ~ObjectAttributes();
protected:
    void paintEvent(QPaintEvent *event);
    
private:
    Ui::ObjectAttributes *ui;
};

#endif // OBJECTATTRIBUTES_H
