//OpenCV头文件
#include <vector>
#include <highgui.h>
#include <cv.h>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

#include <QString>
#include "region.h"

using namespace cv;
using namespace std;

Region::Region(){
    this->isActive = true;
    this->hasObjects = false;
}

Region::Region(QString name, Scalar c){
    this->name = name;
    this->color = c;
    this->isActive = true;
    this->hasObjects = false;

}

Region::Region(QString name, Scalar c, double x, double y, double width, double height){
    this->name = name;
    this->color = c;
    this->isRect = true;
    this->rect = Rect(x, y, width, height);
    this->isActive = true;
    this->hasObjects = false;
}

Region::Region(QString name, Scalar c, Rect re){
    this->name = name;
    this->color = c;
    this->isRect = true;
    this->rect = re;
    this->isActive = true;
    this->hasObjects = false;
}

Region::Region(QString name, Scalar c, vector<Point> ps){
    this->name = name;
    this->color = c;
    this->isRect = false;
    this->poly = ps;
    this->isActive = true;
    this->hasObjects = false;
}

void Region::draw(Mat &mat){
    if(this->isRect && this->isActive){
        if(this->hasObjects){
            rectangle(mat,this->rect,this->color,5,1,0);
            Rect rect2 = Rect(this->rect.x+mat.cols/2, this->rect.y, this->rect.width, this->rect.height);
            rectangle(mat,rect2,this->color,5,1,0);
        }
        else{
            rectangle(mat,this->rect,this->color,3,1,0);
            Rect rect2 = Rect(this->rect.x+mat.cols/2, this->rect.y, this->rect.width, this->rect.height);
            rectangle(mat,rect2,this->color,3,1,0);
        }

    }
    else if(!this->isRect && this->isActive){
        int size = this->poly.size();
        Point points[1][size];
        Point points2[1][size];
        for(int i = 0; i < size; i++){
            points[0][i] = this->poly[i];
            Point p2 = Point(poly[i].x+mat.cols/2,poly[i].y);
            points2[0][i] = p2;
        }

        const Point* ppt[1] = {points[0]};
        int npt[] = {size};
        const Point* ppt2[1] = {points2[0]};
        int npt2[] = {size};
        if(this->hasObjects){
            polylines(mat, ppt, npt, 1, true, this->color, 3);
            polylines(mat, ppt2, npt2, 1, true, this->color, 3);
        }
        else{
            polylines(mat, ppt, npt, 1, true, this->color, 3);
            polylines(mat, ppt2, npt2, 1, true, this->color, 3);
        }
    }
    else{

    }
}
void Region::draw1Time(Mat &mat){
    if(this->isRect && this->isActive){
        if(this->hasObjects){
            rectangle(mat,this->rect,this->color,5,1,0);
        }
        else{
            rectangle(mat,this->rect,this->color,3,1,0);
        }

    }
    else if(!this->isRect && this->isActive){
        int size = this->poly.size();
        Point points[1][size];
        for(int i = 0; i < size; i++){
            points[0][i] = this->poly[i];
        }

        const Point* ppt[1] = {points[0]};
        int npt[] = {size};
        if(this->hasObjects){
            polylines(mat, ppt, npt, 1, true, this->color, 3);
        }
        else{
            polylines(mat, ppt, npt, 1, true, this->color, 3);
        }
    }
    else{

    }
}
bool Region::isInner(Point2f p){
    bool in = false;
    if(isRect && this->isActive){
        in = this->rect.contains(p);
        this->hasObjects = this->rect.contains(p);
    }
    else if(!this->isRect && this->isActive){
        int inner = pointPolygonTest(this->poly, p, false);
        if (inner >= 0){
            in = true;
            this->hasObjects = true;
        }
        else{
            in = false;
            this->hasObjects = false;
        }
    }
    else{

    }

    return in;
}
