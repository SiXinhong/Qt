#include "myobject.h"
#include "cvutil.h";

MyObject::MyObject(){
    this->color = CVUtil::getRandomColor();
}

void MyObject::setRect(Rect r){
    this->box = r;
}

Rect MyObject::getRect(){
    return this->box;
}

void MyObject::SetColor(Scalar co){
    this->color = co;
}

Scalar MyObject::getColor(){
    return this->color;
}
