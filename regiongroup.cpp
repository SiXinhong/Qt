//OpenCV头文件
#include <vector>
#include <highgui.h>
#include <cv.h>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

#include <QString>
#include <QDateTime>

#include "region.h"
#include "regiongroup.h"

using namespace cv;
using namespace std;

RegionGroup::RegionGroup(){
    this->isDrawLabel = false;
    this->isActive = true;
    this->isAlert = true;
    for(int i=0;i<7;i++){
        for(int j=0;j<48;j++){
            timeActive[i][j] = true;
        }
    }
}

RegionGroup::RegionGroup(QString name, Scalar c){
    this->isDrawLabel = false;
    this->name = name;
    this->color = c;
    this->isActive = true;
    this->isAlert = true;
    for(int i=0;i<7;i++){
        for(int j=0;j<48;j++){
            timeActive[i][j] = true;
        }
    }
}

RegionGroup::RegionGroup(QString name, Scalar c, vector<Region> rs){
    this->isDrawLabel = false;
    this->name = name;
    this->color = c;
    this->rs = rs;
    for(int i = 0; i < rs.size(); i++){
        rs[i].color = this->color;
    }
    this->isActive = true;
    this->isAlert = true;
    for(int i=0;i<7;i++){
        for(int j=0;j<48;j++){
            timeActive[i][j] = true;
        }
    }
}

void RegionGroup::draw(Mat &mat){

    for(int i = 0; i < this->rs.size(); i++){
        rs[i].draw(mat);
    }
    //qDebug()<<"isDrawingLabel:"<<this->isDrawLabel;
    this->drawLabel(mat);
    //    if(this->isActive){
    //        for(int i = 0; i < this->rs.size(); i++){
    //            rs[i].draw(mat);
    //        }
    //    }
}

bool RegionGroup::isInner(Point2f p){
    bool in = false;
    if(this->isAlert){
        if(!isTimeAlertTrue())
            return false;
        for(int i = 0; i< this->rs.size(); i++){
            Region r = rs[i];
            if(r.isInner(p)){
                in = true;
                break;
            }
        }
    }
    return in;
}

vector<Region> RegionGroup::hasObjects(){
    vector<Region> rss;
    for(int i = 0; i < this->rs.size(); i++){
        Region r = this->rs[i];
        if(r.hasObjects){
            rss.push_back(r);
        }
    }
    return rss;
}

void RegionGroup::addRegion(Region r){
    this->rs.push_back(r);
}

void RegionGroup::setColor(Scalar c){
    this->color = c;
    for(int i=0;i<rs.size();i++){
        rs[i].color = c;
    }
}

bool RegionGroup::isTimeAlertTrue(){
    QDateTime dt = QDateTime::currentDateTime();
    int i = dt.date().dayOfWeek()-1;
    int hour = dt.time().hour();
    int minute = dt.time().minute();
    int j = (hour-1)*2;
    if(minute>=30)
        j+=2;
    else
        j++;
    return timeActive[i][j];
}

void RegionGroup::drawLabel(Mat image){
    if(isDrawLabel){
        for(int i =0;i<rs.size();i++){
            if(rs.at(i).isRect){
                //qDebug()<<"drawlabel1";
                Point point = rs.at(i).leftPoint(rs.at(i).rect);
                putText(image,rs.at(i).name.toStdString(),point,FONT_HERSHEY_SCRIPT_SIMPLEX,0.40,this->color,1,8,0);
                Point point2 = Point(point.x+image.cols/2,point.y);
                putText(image,rs.at(i).name.toStdString(),point2,FONT_HERSHEY_SCRIPT_SIMPLEX,0.40,this->color,1,8,0);
            }
            else{
                //qDebug()<<"drawlabel2";
                Point point = rs.at(i).leftPoint(rs.at(i).poly);
                putText(image,rs.at(i).name.toStdString(),point,FONT_HERSHEY_SCRIPT_SIMPLEX,0.40,this->color,1,8,0);
                Point point2 = Point(point.x+image.cols/2,point.y);
                putText(image,rs.at(i).name.toStdString(),point2,FONT_HERSHEY_SCRIPT_SIMPLEX,0.40,this->color,1,8,0);
            }
        }
    }
}

