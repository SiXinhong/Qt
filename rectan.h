#ifndef RECTAN_H
#define RECTAN_H

class Rectan
{
public:
    Rectan();

    double x;
    double y;
    double width;
    double height;

    Rectan(double x,double y,double width,double height);

    double getX();
    void setX(double x);
    double getY();
    void setY(double y);
    double getWidth();
    void setWidth(double width);
    double getHeight();
    void setHeight(double height);
};

#endif // RECTAN_H
