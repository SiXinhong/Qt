#include "myobjecttrack.h"
#include "cvutil.h";

MyObjectTrack::MyObjectTrack(){

}

void MyObjectTrack::setId(int id){
    this->id = id;
}

int MyObjectTrack::getId(){
    return this->id;
}

vector<Point> MyObjectTrack::getTrack(){

    return this->cenPoints;
}

void MyObjectTrack::setTrack(vector<Point> cps){
    this->cenPoints = cps;

}
