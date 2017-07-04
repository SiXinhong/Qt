#include "myobject.h"
#include "cvutil.h";
#include <QBuffer>
MyObject::MyObject(){
    this->color = CVUtil::getRandomColor();

    oid = -1;
    cenPoint = cv::Point(-1, -1);         // 目标中心坐标
    blocksize = cv::Size(0, 0);            // 检测框大小
    Velocity = 0;                    // 运动速率
    MotionDerection = 0;             // 运动方向
    area = 0;                           // 目标面积
    horizontalAxisLength = 0;           // 水平轴长度
    verticalAxisLength = 0;             // 竖直轴长度
    absoluteIntensity = 0;           // 绝对强度
    relativeIntensity = 0;           // 相对强度

    vector<cv::Point> contours;                 // 目标轮廓
    cv::Mat Snapshoot;                          // 目标快照
    cv::Mat sihouette;                          // 目标剪影

    targetScale = 0;                 // 目标尺度
    CenSueEintensity = 0;            // 中央周围对比度的响应强度
    SCRValue = 0;                    // 目标背景信杂比
    vector<double> theFeatures;             // 13维的小目标特征向量
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
QDataStream& writeMat(QDataStream &out,Mat &m){
    size_t elem_size = m.elemSize();
    size_t elem_type = m.type();
    const size_t data_size = m.cols * m.rows * elem_size;

    out << elem_size<<elem_type <<m.cols<<m.rows;

    uchar *p=m.ptr();
    for(size_t i=0;i<data_size;i++){
        out<<*(p++);
    }
    return out;
}

QDataStream& readMat(QDataStream &in,Mat &m){
    size_t elem_size,elem_type;
    int cols,rows;
    in>> elem_size >> elem_type >> cols >> rows;

    const size_t data_size = cols * rows * elem_size;

    m.create(rows, cols, elem_type);
    uchar *p=m.ptr();
    for(size_t i=0;i<data_size;i++){
        in>>*(p++);
    }

    return in;
}
QDataStream& operator>>(QDataStream &in,MyObject& data){
    in>>data.box.x>>data.box.y>>data.box.height>>data.box.width;

//    int c1,c2,c3;
//    in>>c1>>c2>>c3;
//    data.SetColor(Scalar(c1,c2,c3));
//    color初始化的代码是随机生成的颜色,也就是每次看到的物体的颜色是不同的,应该无需序列化,如果需要,上面三行可能能用
    in>>data.oid;
    in>>data.cenPoint.x>>data.cenPoint.y;
    in>>data.blocksize.width>>data.blocksize.height;
    in>>data.Velocity;
    in>>data.MotionDerection;
    in>>data.area;
    in>>data.horizontalAxisLength;
    in>>data.verticalAxisLength;
    in>>data.absoluteIntensity;
    in>>data.relativeIntensity;

    int size;
    in>>size;
    if(size>0){
        for(int i=0;i<size;i++){
            cv::Point p;
            in >>p.x>>p.y;
            data.contours.push_back(p);
        }
    }
    int flag;
    in >> flag;
    if(flag==1){
        readMat(in,data.Snapshoot);
    }
    in >> flag;
    if(flag==1){
        readMat(in,data.sihouette);
    }
    in>>data.targetScale;
    in>>data.CenSueEintensity;
    in>>data.SCRValue;

    in >> size;
    double d;
    if(size>0){
        for(int i=0;i<size;i++){
            in>>d;
            data.theFeatures.push_back(d);
        }
    }
    return in;
}

QDataStream& operator<<(QDataStream &out,MyObject& data){
    out<<data.box.x<<data.box.y<<data.box.height<<data.box.width;//box

//    out<<data.color.val[0];
//    out<<data.color.val[1];
//    out<<data.color.val[2];
//    color初始化的代码是随机生成的颜色,也就是每次看到的物体的颜色是不同的,应该无需序列化,如果需要,上面三行可能能用
    out<<data.oid;
    out<<data.cenPoint.x<<data.cenPoint.y;
    out<<data.blocksize.width<<data.blocksize.height;
    out<<data.Velocity;
    out<<data.MotionDerection;
    out<<data.area;
    out<<data.horizontalAxisLength;
    out<<data.verticalAxisLength;
    out<<data.absoluteIntensity;
    out<<data.relativeIntensity;
    int size=data.contours.size();
    out<<size;
    if(size>0){
        for(int i=0;i<size;i++){
            cv::Point p= data.contours.at(i);
            out<<p.x<<p.y;
        }
    }
    if(data.Snapshoot.empty()){
        out<<-1;
    }else{
        out<<1;
        writeMat(out,data.Snapshoot);
    }
    if(data.sihouette.empty()){
        out<<-1;
    }else{
        out<<1;
        writeMat(out,data.sihouette);
    }
    out<<data.targetScale;
    out<<data.CenSueEintensity;
    out<<data.SCRValue;
    size=data.theFeatures.size();
    out<<size;
    if(size>0){
        for(int j=0;j<size;j++){
            double d=data.theFeatures.at(j);
            out<<d;
        }
    }
    return out;
}
//MyObject& DeSerializable(const QByteArray &datagram){
//    QByteArray tmp_array = datagram;
//    QBuffer buffer(&tmp_array);
//    buffer.open(QIODevice::ReadOnly);

//    QDataStream in(&buffer);
//    //反序列化，获取对象信息
//    MyObject obj;
//    in>>obj;
//    buffer.close();
//    return obj;
//}
//QByteArray& Serializable(const MyObject &myObject){
//        QByteArray tmp_array;
//        QBuffer buffer(&tmp_array);
//        buffer.open(QIODevice::WriteOnly);

//        QDataStream out(&buffer);
//        //序列化对象信息
//        //out<<myObject;
//        buffer.close();
//        return tmp_array;
//}

