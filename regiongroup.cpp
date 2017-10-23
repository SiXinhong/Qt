//OpenCVÍ·ÎÄ¼þ
#include <vector>
#include <highgui.h>
#include <cv.h>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

#include <QString>

#include "region.h"
#include "regiongroup.h"

using namespace cv;
using namespace std;

RegionGroup::RegionGroup(){
    this->isActive = true;
}

RegionGroup::RegionGroup(QString name, Scalar c){
    this->name = name;
    this->color = c;
    this->isActive = true;
}

RegionGroup::RegionGroup(QString name, Scalar c, vector<Region> rs){
    this->name = name;
    this->color = c;
    this->rs = rs;
    for(int i = 0; i < rs.size(); i++){
        Region r = rs[i];
        r.color = this->color;
    }
    this->isActive = true;
}

void RegionGroup::draw(Mat mat){
    if(this->isActive){
        for(int i = 0; i < this->rs.size(); i++){
            Region r = rs[i];
            r.draw(mat);
        }
    }
}

boolean RegionGroup::isInner(Point2f p){
    boolean in = false;
    if(this->isActive){
        for(int i = 0; i< this->rs.size(); i++){
            Region r = rs[i];
            if(r.isInner(p)){
                in = true;
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
