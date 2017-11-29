#include "rectan.h"

Rectan::Rectan(){

}


Rectan::Rectan(double x,double y,double width,double height)
{
    this->x = x;
    this->y = y;
    this->width = width;
    this->height = height;
}

double Rectan::getX(){
    return x;
}
double Rectan::getY(){
    return y;
}
double Rectan::getWidth(){
    return width;
}
double Rectan::getHeight(){
    return height;
}

void Rectan::setX(double x){
    this->x = x;
}

void Rectan::setY(double y){
    this->y = y;
}

void Rectan::setWidth(double width){
    this->width = width;
}

void Rectan::setHeight(double height){
    this->height = height;
}

