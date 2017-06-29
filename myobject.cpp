#include "myobject.h"
#include "cvutil.h";

MyObject::MyObject(){
    this->color = CVUtil::getRandomColor();

    oid = -1;
    cenPoint = cv::Point(-1, -1);         // Ŀ����������
    blocksize = cv::Size(0, 0);            // �����С
    Velocity = 0;                    // �˶�����
    MotionDerection = 0;             // �˶�����
    area = 0;                           // Ŀ�����
    horizontalAxisLength = 0;           // ˮƽ�᳤��
    verticalAxisLength = 0;             // ��ֱ�᳤��
    absoluteIntensity = 0;           // ����ǿ��
    relativeIntensity = 0;           // ���ǿ��

    vector<cv::Point> contours;                 // Ŀ������
    cv::Mat Snapshoot;                          // Ŀ�����
    cv::Mat sihouette;                          // Ŀ���Ӱ

    targetScale = 0;                 // Ŀ��߶�
    CenSueEintensity = 0;            // ������Χ�Աȶȵ���Ӧǿ��
    SCRValue = 0;                    // Ŀ�걳�����ӱ�
    vector<double> theFeatures;             // 13ά��СĿ����������
}

void MyObject::setID(int id1){
    this->oid = id1;
}

int MyObject::getID(){
    return this->oid;
}

void MyObject::setCenPoint(Point p){
    this->cenPoint = p;
}

Point MyObject::getCenPoint(){
    return this->cenPoint;
}

void MyObject::setBlockSize(Size s){
    this->blocksize = s;
}

Size MyObject::getBlockSize(){
    return this->blocksize;
}

void MyObject::setVelocity(double v){
    this->Velocity = v;
}

double MyObject::getVelocity(){
    return this->Velocity;
}

void MyObject::setMotionDerection(double md){
    this->MotionDerection = md;
}

double MyObject::getMotionDerection(){
    return this->MotionDerection;
}

void MyObject::setArea(int a){
    this->area = a;
}

int MyObject::getArea(){
    return this->area;
}

void MyObject::setHorizontalAxisLength(int hal){
    this->horizontalAxisLength = hal;
}

int MyObject::getHorizontalAxisLength(){
    return this->horizontalAxisLength;
}

void MyObject::setVerticalAxisLength(int val){
    this->verticalAxisLength = val;
}

int MyObject::getVerticalAxisLength(){
    return this->verticalAxisLength;
}

void MyObject::setAbsoluteIntensity (double ai){
    this->absoluteIntensity = ai;
}

double MyObject::getAbsoluteIntensity(){
    return this->absoluteIntensity;
}

void MyObject::setRelativeIntensity(double ri){
    this->relativeIntensity = ri;
}

double MyObject::getRelativeIntensity(){
    return this->relativeIntensity;
}

void MyObject::setContours(vector<Point> con){
    this->contours = con;
}

vector<Point> MyObject::getContours(){
    return this->contours;
}

void MyObject::setSnapshoot(Mat ss){
    this->Snapshoot = ss;
}

Mat MyObject::getSnapshoot(){
    return this->Snapshoot;
}

void MyObject::setSihouette(Mat si){
    this->sihouette = si;
}

Mat MyObject::getSihouette(){
    return this->sihouette;
}

void MyObject::setTargetScale(double ts){
    this->targetScale = ts;
}

double MyObject::getTargetScale(){
    return this->targetScale;
}

void MyObject::setCenSueEintensity(double cse){
    this->CenSueEintensity = cse;
}

double MyObject::getCenSueEintensity(){
    return this->CenSueEintensity;
}

void MyObject::setSCRValue(double scrv){
    this->SCRValue = scrv;
}

double MyObject::getSCRValue(){
    return this->SCRValue;
}

void MyObject::setTheFeatures(vector<double> fea){
    this->theFeatures = fea;
}

vector<double> MyObject::getTheFeatures(){
    return this->theFeatures;
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
