
#include "qj2widget.h"
#include "mainwindow.h"
#include "myobject.h"
#include "myobjecttrack.h"
#include "region.h"
#include "regiongroup.h"

using namespace cv;
using namespace std;

Qj2Widget::Qj2Widget(QWidget *parent) :
    QWidget(parent){

   // completeRDefine = false;
     this->isShow = true;
    isGaojing = true;
    isDrag = false;
    isMove = false;
    isRect = false;

    isTo3 = false;
    isTo4 = false;
    isTo6 = false;
    isClicked = false;
    isFirstDoubleClick = false;

    Cancel_Select = new QAction(tr("ȡ��ѡ��"),this);
    To_Zhu= new QAction(tr("������ʾ��"), this);
    To_Ningshi1 = new QAction(tr("��������ʾ��1"), this);
    To_Ningshi2 = new QAction(tr("��������ʾ��2"), this);
    Define_Rect = new QAction(tr("������μ������"), this);
    Define_Poly = new QAction(tr("�������μ������"), this);

    Cancel_RDefining = new QAction(tr("ȡ�����������"), this);
    Cancel_RGDefining = new QAction(tr("ȡ����������鶨��"), this);
    Complete_RDefining = new QAction(tr("��ɼ��������"), this);
    Complete_RGDefining = new QAction(tr("��ɼ�������鶨��"), this);
    //To_Tanchu = new QAction(tr("����������"),this);
    connect(Cancel_Select, SIGNAL(triggered()), this, SLOT(CancelSelect()));
    connect(To_Zhu, SIGNAL(triggered()), this, SLOT(ToZhu()));
    connect(To_Ningshi1, SIGNAL(triggered()), this, SLOT(ToNingshi1()));
    connect(To_Ningshi2, SIGNAL(triggered()), this, SLOT(ToNingshi2()));
    //connect(To_Tanchu, SIGNAL(triggered()), this, SLOT(ToTanchu()));


    connect(Define_Rect, SIGNAL(triggered()), this, SLOT(DefineRect()));
    connect(Define_Poly, SIGNAL(triggered()), this, SLOT(DefinePoly()));

    connect(Cancel_RDefining, SIGNAL(triggered()), this, SLOT(CancelRDefining()));
    connect(Cancel_RGDefining, SIGNAL(triggered()), this, SLOT(CancelRGDefining()));
    connect(Complete_RDefining, SIGNAL(triggered()), this, SLOT(CompleteRDefining()));
    connect(Complete_RGDefining, SIGNAL(triggered()), this, SLOT(CompleteRGDefining()));


    this->rectRegion = Rect(0,0,0,0);

    rectan3 = Rect(1490,250,100,100);
    rectan4 = Rect(1490,250,100,100);
    rectan6 = Rect(1490,250,100,100);
    newrect = Rect(1490,250,100,100);
    //paint=new QPainter;
}

void Qj2Widget::setMat(Mat m){
    mat = m;
//    if(isRect){
//        MainWindow *mw = (MainWindow*)parentWidget()->parentWidget();
//        //mw->test();

//        rectangle(mat,newrect,Scalar(0,0,255),1,1,0);
//        cv::cvtColor(mat, mat, CV_BGR2RGB);
//        mw->loadPictureToLabel2();
//        isRect = true;
//    }
    MainWindow *mw = (MainWindow*)parentWidget()->parentWidget();
    //mw->loadPictureToLabel2(isRect, qrect);
    mw->loadPictureToLabel2(isRect, qrect, mw->rgs[mw->rgsIndex].color, QRect(rectRegion.x, rectRegion.y, rectRegion.width, rectRegion.height), points);

}

Mat Qj2Widget::getMat(){
    return mat;
}

void Qj2Widget::setPano(Mat p){
    this->pano = p;
}

Mat Qj2Widget::getPano(){
    return this->pano;
}

void Qj2Widget::setTwoPano(Mat tp){
    this->twoPano = tp;
}

Mat Qj2Widget::getTwoPano(){
    return this->twoPano;
}

void Qj2Widget::setObjects(vector<MyObject> os){
    this->objs = os;
}

vector<MyObject> Qj2Widget::getObjects(){
    return this->objs;
}

void Qj2Widget::setTracks(vector<MyObjectTrack> ts){
    this->tracks =ts;
}

vector<MyObjectTrack> Qj2Widget::getTracks(){
    return this->tracks;
}

void Qj2Widget::contextMenuEvent(QContextMenuEvent *){
    QCursor cur=this->cursor();
    QMenu *menu=new QMenu(this);
    menu->addAction(Cancel_Select); //��Ӳ˵���1
    menu->addAction(To_Zhu); //��Ӳ˵���1
    menu->addAction(To_Ningshi1); //��Ӳ˵���2
    menu->addAction(To_Ningshi2); //��Ӳ˵���2
    //menu->addAction(To_Tanchu);//��Ӳ˵���3
    menu->addSeparator();
    menu->addAction(Define_Rect);
    menu->addAction(Define_Poly);
    menu->addSeparator();
    menu->addAction(Cancel_RDefining);
    menu->addAction(Cancel_RGDefining);
    menu->addAction(Complete_RDefining);
    menu->addAction(Complete_RGDefining);
    menu->exec(cur.pos()); //���������
}

void Qj2Widget::CancelSelect(){
    isRect = false;
}

void Qj2Widget::draw(){

    MainWindow *mw = (MainWindow*)parentWidget()->parentWidget();

//    int count = this->objs.size();
//    for (int i = 0; i < count;i++)
//    {
//        //�������box
//        MyObject obj = objs[i];
//        int tempx = obj.getRect().x-this->mat.cols;
//        int tempy = obj.getRect().y;
//        //obj.setRect(Rect(tempx,tempy));
//        qDebug()<< tempx;
//        qDebug()<< tempy;
//        rectangle(mat,cv::Rect(tempx, tempy, obj.getRect().width, obj.getRect().height),obj.getColor(),2,1,0);
//        //���켣
//        for(int ii = 0; ii < this->tracks.size(); ii++){
//            MyObjectTrack track = this->tracks[ii];
//            int id = track.getId();
//            vector<Point> points = track.getTrack();
//            if(id == obj.getID()){
//                for(int iii = 0; iii < points.size(); iii++){
//                    Point point = points[iii];
//                    circle(mat, point, 2, obj.getColor(),-1,8,2);//��ͼ���л��������㣬2��Բ�İ뾶
//                    if(iii >= 1){
//                        Point point2 = points[iii-1];
//                        line(mat,point,point2,obj.getColor(),1,8,0);
//                    }
//                }
//            }
//        }
//        //���������ĵ��λ��
//        if(mw->isMubiao){
//            int x = (int)(this->getDirectionX(obj.getCenPoint().x));
//            int y = (int)(10-this->getDirectionY(obj.getCenPoint().y)/2);//(10-10*(this->getDirectionY(obj.getCenPoint().y)-this->getDirectionY())/(this->getDirectionY2()-this->getDirectionY()));//endh - i*(endh-starth)/10
//            QString tx = QString::number(x,10);
//            QString ty = QString::number(y,10);
//            QString tstr = "x="+tx+",y="+ty;
//            string str = tstr.toStdString();
//            //qDebug()<<tstr;
//            Point p = Point(obj.getRect().x+obj.getRect().width,obj.getRect().y+obj.getRect().height);
//            putText(mat,str,p,1,1,obj.getColor());
//        }
//        cv::cvtColor(mat, mat, CV_BGR2RGB);
//    }

//    for(int j = 0;j<rg.rs.size();j++){

//            int sizeOfPoints = rg.rs.at(j).poly.size();
//            if(sizeOfPoints == 0){
//                rectangle(mat,Rect(rg.rs.at(j).rect.x,rg.rs.at(j).rect.y,rg.rs.at(j).rect.width,rg.rs.at(j).rect.height),rg.color,1,8,0);

//        }
//            else{
//                Point pp[sizeOfPoints];
//                for(int i = 0; i < sizeOfPoints; i++){
//                    pp[i] = Point(rg.rs.at(j).poly[i].x, rg.rs.at(j).poly[i].y);

//                }
//                const Point *pt[1] ={ pp};
//                int npt[1] = {sizeOfPoints};

//                polylines(mat,pt,npt,1,true,rg.color,1,8,0);

//           }
//}
    for(int j=0;j<this->rs.size();j++){
        this->rs[j].draw1Time(mat);
    }
    mw->imgLabel2 = mw->MatToQImage(mat,mw->imgLabel2);
    //cv::cvtColor(mat, mat, CV_BGR2RGB);
    //mw->loadPictureToLabel2(isRect, qrect);
    mw->loadPictureToLabel2(isRect, qrect, mw->rgs[mw->rgsIndex].color, QRect(rectRegion.x, rectRegion.y, rectRegion.width, rectRegion.height), points);

}

boolean Qj2Widget::isObjSelected3(MyObject obj){
    boolean isSelected = false;
        if(this->rectan3.contains(Point(obj.getCenPoint().x-mat.cols,obj.getCenPoint().y))){
            //����ѡ�����ʹ��Ŀ���box��ѡ���֮��
            if(obj.getRect().x-mat.cols<this->rectan3.x){
                this->rectan3.x = obj.getRect().x - mat.cols - 5;
                this->rectan3.width += this->rectan3.x - (obj.getRect().x-mat.cols) + 5;
            }
            if(obj.getRect().y<this->rectan3.y){
                this->rectan3.y = obj.getRect().y - 5;
                this->rectan3.height += this->rectan3.y - obj.getRect().y + 5;
            }
            if((obj.getRect().x-mat.cols+obj.getRect().width)>(this->rectan3.x+this->rectan3.width)){
                //this->rectan3.x = obj.getRect().x +obj.getRect().width + 5;

                this->rectan3.width = obj.getRect().x-mat.cols + obj.getRect().width - this->rectan3.x + 5;
            }
            if((obj.getRect().y+obj.getRect().height)>(this->rectan3.y+this->rectan3.height)){
                this->rectan3.height = this->rectan3.height + obj.getRect().y + obj.getRect().height- this->rectan3.y+ 5;
                //this->rectan3.y = obj.getRect().y +obj.getRect().height+ 5;
            }

            isSelected = true;
        }
    return isSelected;
}

boolean Qj2Widget::isObjSelected4(MyObject obj){
    boolean isSelected = false;
    if(this->rectan4.contains(Point(obj.getCenPoint().x-mat.cols,obj.getCenPoint().y))){
        //����ѡ�����ʹ��Ŀ���box��ѡ���֮��
        if(obj.getRect().x-mat.cols<this->rectan4.x){
            this->rectan4.x = obj.getRect().x-mat.cols - 5;
            this->rectan4.width += this->rectan4.x - (obj.getRect().x-mat.cols) + 5;
        }
        if(obj.getRect().y<this->rectan4.y){
            this->rectan4.y = obj.getRect().y - 5;
            this->rectan4.height += this->rectan4.y - obj.getRect().y + 5;
        }
        if((obj.getRect().x-mat.cols+obj.getRect().width)>(this->rectan4.x+this->rectan4.width)){
            //this->rectan4.x = obj.getRect().x +obj.getRect().width + 5;

            this->rectan4.width = obj.getRect().x-mat.cols + obj.getRect().width - this->rectan4.x + 5;
        }
        if((obj.getRect().y+obj.getRect().height)>(this->rectan4.y+this->rectan4.height)){
            this->rectan4.height = this->rectan4.height + obj.getRect().y + obj.getRect().height- this->rectan4.y+ 5;
            //this->rectan4.y = obj.getRect().y +obj.getRect().height+ 5;
        }

        isSelected = true;
    }
    return isSelected;
}

boolean Qj2Widget::isObjSelected6(MyObject obj){
    boolean isSelected = false;
    if(this->rectan6.contains(Point(obj.getCenPoint().x-mat.cols,obj.getCenPoint().y))){
        //����ѡ�����ʹ��Ŀ���box��ѡ���֮��
        if(obj.getRect().x-mat.cols<this->rectan6.x){
            this->rectan6.x = obj.getRect().x-mat.cols - 5;
            this->rectan6.width += this->rectan6.x - (obj.getRect().x-mat.cols) + 5;
        }
        if(obj.getRect().y<this->rectan6.y){
            this->rectan6.y = obj.getRect().y - 5;
            this->rectan6.height += this->rectan6.y - obj.getRect().y + 5;
        }
        if((obj.getRect().x-mat.cols+obj.getRect().width)>(this->rectan6.x+this->rectan6.width)){
            //this->rectan4.x = obj.getRect().x +obj.getRect().width + 5;

            this->rectan6.width = obj.getRect().x-mat.cols + obj.getRect().width - this->rectan6.x + 5;
        }
        if((obj.getRect().y+obj.getRect().height)>(this->rectan6.y+this->rectan6.height)){
            this->rectan6.height = this->rectan6.height + obj.getRect().y + obj.getRect().height- this->rectan6.y+ 5;
            //this->rectan4.y = obj.getRect().y +obj.getRect().height+ 5;
        }

        isSelected = true;
    }
    return isSelected;
}

void Qj2Widget::ToZhu()
{
    this->isTo3 = true;
    MainWindow *mw = (MainWindow*)parentWidget()->parentWidget();

    mw->widget1->isTo3 = false;

    if(this->newrect.width<0){
        this->rectan3.width = -this->newrect.width;
        this->rectan3.height= -this->newrect.height;
        this->rectan3.x = this->newrect.x+this->newrect.width;
        this->rectan3.y = this->newrect.y+this->newrect.height;
    }
    else if(this->newrect.height<0){
        this->rectan3.width = -this->newrect.width;
        this->rectan3.height= -this->newrect.height;
        this->rectan3.x = this->newrect.x+this->newrect.width;
        this->rectan3.y = this->newrect.y+this->newrect.height;
    }
    else{
        this->rectan3.x = this->newrect.x;
        this->rectan3.y = this->newrect.y;
        this->rectan3.width = this->newrect.width;
        this->rectan3.height = this->newrect.height;
    }

    //������ѡ�ľ��ο���ʹ��������ʾ���е���ʾ������
    //this->rectan3.width = this->rectan3.height * mw->widget3->width() / mw->widget3->height();

//    this->rectan3.x = this->newrect.x;
//    this->rectan3.y = this->newrect.y;
//    this->rectan3.width = this->newrect.width;
//    this->rectan3.height = this->newrect.height;

    //��������ʾ����������Ŀ��
    vector<MyObject> objs3;
    int count = this->objs.size();
    for(int i = 0; i < count; i++){
        MyObject obj = objs[i];
        if(isObjSelected3(obj)){
            objs3.push_back(obj);
        }
    }

//    qDebug()<<rectan3.x;
//    qDebug()<<rectan3.y;
//    qDebug()<<rectan3.width;
//    qDebug()<<rectan3.height;
//    qDebug()<<getQRectan3();
    //qDebug()<<objs3.size();

    mw->widget3->setObjects(objs3);

    mw->widget3->setFrom(2);

    mw->widget3->setRect(this->getQRectan3());
    //mw->test();

    Mat mat = getPano();
    Size dsize ;
    double scale = 1;
    dsize = Size(mat.cols*scale,mat.rows*scale);
//    Mat image11 = Mat(dsize,CV_32S);
//    cv::resize(mat, image11,dsize);
//    mw->img = QImage((const unsigned char*)(image11.data),image11.cols,image11.rows, image11.cols*image11.channels(),  QImage::Format_RGB888);

//    //vector<Rectan> rectans;
//    mw->aa=(&(mw->img))->copy(getQRectan3());
//    Mat image3 = mw->QImageToMat(mw->aa);
//    Mat image33 = Mat(dsize,CV_32S);
//    cv::resize(image3, image33,dsize);
//    mw->widget3->setMat(image33);
    Mat image3;
    mat(getQRectan3()).copyTo(image3);//mw->QImageToMat(mw->aa);
    Mat image33 = Mat(dsize,CV_32S);
    cv::resize(image3, image33,dsize);
    mw->widget3->setMat(image33);
    mw->widget3->draw();

    isRect = false;
}
//��������ʾ��1��ʾ�˵������¼�
void Qj2Widget::ToNingshi1()
{
    //qDebug()<<"������ʾ����";

    this->isTo4 = true;

    MainWindow *mw = (MainWindow*)parentWidget()->parentWidget();

    mw->widget1->isTo4 = false;

    if(this->newrect.width<0){
        this->rectan4.width = -this->newrect.width;
        this->rectan4.height= -this->newrect.height;
        this->rectan4.x = this->newrect.x+this->newrect.width;
        this->rectan4.y = this->newrect.y+this->newrect.height;
    }
    else if(this->newrect.height<0){
        this->rectan4.width = -this->newrect.width;
        this->rectan4.height= -this->newrect.height;
        this->rectan4.x = this->newrect.x+this->newrect.width;
        this->rectan4.y = this->newrect.y+this->newrect.height;
    }
    else{
        this->rectan4.x = this->newrect.x;
        this->rectan4.y = this->newrect.y;
        this->rectan4.width = this->newrect.width;
        this->rectan4.height = this->newrect.height;
    }

    //������ѡ�ľ��ο���ʹ����������ʾ���е���ʾ������
    //this->rectan4.width = this->rectan4.height * mw->widget4->width() / mw->widget4->height();

    //����������ʾ����������Ŀ��

    vector<MyObject> objs4;
    int count = this->objs.size();
    for(int i = 0; i < count; i++){
        MyObject obj = objs[i];
        if(isObjSelected4(obj)){
            objs4.push_back(obj);
        }
    }

    mw->widget4->setObjects(objs4);

    mw->widget4->setFrom(2);

    mw->widget4->setRect(this->getQRectan4());

    Mat mat = getPano();
    Size dsize ;
    double scale = 1;
    dsize = Size(mat.cols*scale,mat.rows*scale);
//    Mat image11 = Mat(dsize,CV_32S);
//    cv::resize(mat, image11,dsize);
//    mw->img = QImage((const unsigned char*)(image11.data),image11.cols,image11.rows, image11.cols*image11.channels(),  QImage::Format_RGB888);

//    //vector<Rectan> rectans;
//    mw->aa=(&(mw->img))->copy(getQRectan4());
//    Mat image4 = mw->QImageToMat(mw->aa);
//    Mat image44 = Mat(dsize,CV_32S);
//    cv::resize(image4, image44,dsize);
//    mw->widget4->setMat(image44);
    Mat image4;
    mat(getQRectan4()).copyTo(image4);//mw->QImageToMat(mw->aa);
    Mat image44 = Mat(dsize,CV_32S);
    cv::resize(image4, image4,dsize);
    mw->widget4->setMat(image44);
    mw->widget4->draw();
    isRect = false;
}
//��������ʾ��1��ʾ�˵������¼�
void Qj2Widget::ToNingshi2()
{
    //qDebug()<<"������ʾ����";

    this->isTo6 = true;

    MainWindow *mw = (MainWindow*)parentWidget()->parentWidget();

    mw->widget1->isTo6 = false;

    if(this->newrect.width<0){
        this->rectan6.width = -this->newrect.width;
        this->rectan6.height= -this->newrect.height;
        this->rectan6.x = this->newrect.x+this->newrect.width;
        this->rectan6.y = this->newrect.y+this->newrect.height;
    }
    else if(this->newrect.height<0){
        this->rectan6.width = -this->newrect.width;
        this->rectan6.height= -this->newrect.height;
        this->rectan6.x = this->newrect.x+this->newrect.width;
        this->rectan6.y = this->newrect.y+this->newrect.height;
    }
    else{
        this->rectan6.x = this->newrect.x;
        this->rectan6.y = this->newrect.y;
        this->rectan6.width = this->newrect.width;
        this->rectan6.height = this->newrect.height;
    }

    //������ѡ�ľ��ο���ʹ����������ʾ���е���ʾ������
    //this->rectan4.width = this->rectan4.height * mw->widget4->width() / mw->widget4->height();

    //����������ʾ����������Ŀ��

    vector<MyObject> objs6;
    int count = this->objs.size();
    for(int i = 0; i < count; i++){
        MyObject obj = objs[i];
        if(isObjSelected6(obj)){
            objs6.push_back(obj);
        }
    }

    mw->widget6->setObjects(objs6);

    mw->widget6->setFrom(2);

    mw->widget6->setRect(this->getQRectan6());

    Mat mat = getPano();
    Size dsize ;
    double scale = 1;
    dsize = Size(mat.cols*scale,mat.rows*scale);
//    Mat image11 = Mat(dsize,CV_32S);
//    cv::resize(mat, image11,dsize);
//    mw->img = QImage((const unsigned char*)(image11.data),image11.cols,image11.rows, image11.cols*image11.channels(),  QImage::Format_RGB888);

//    //vector<Rectan> rectans;
//    mw->aa=(&(mw->img))->copy(getQRectan4());
//    Mat image4 = mw->QImageToMat(mw->aa);
//    Mat image44 = Mat(dsize,CV_32S);
//    cv::resize(image4, image44,dsize);
//    mw->widget4->setMat(image44);
    Mat image6;
    mat(getQRectan6()).copyTo(image6);//mw->QImageToMat(mw->aa);
    Mat image66 = Mat(dsize,CV_32S);
    cv::resize(image6, image6,dsize);
    mw->widget6->setMat(image66);
    mw->widget6->draw();
    isRect = false;
}
//������������ʾ�˵������¼�
//void ToTanchu(){
//    qDebug()<<"���������ڡ�";
//}

//void QjWidget::mouseClickEvent(QMouseEvent *e){

//}
//������μ������
void Qj2Widget::DefineRect(){
    MainWindow *mw = (MainWindow*)parentWidget()->parentWidget();
    mw->isDefiningRegion = true;
    if(!mw->isDefiningRectRegion){

        this->points.clear();
        this->rectRegion.x = 0;
        this->rectRegion.y = 0;
        this->rectRegion.width = 0;
        this->rectRegion.height = 0;
        mw->isDefiningRectRegion = true;
        this->isFirstDoubleClick = false;
    }
    else{

    }
}

//�������μ������
void Qj2Widget::DefinePoly(){
    MainWindow *mw = (MainWindow*)parentWidget()->parentWidget();
    mw->isDefiningRegion = true;
    if(mw->isDefiningRectRegion){
        this->points.clear();
        this->rectRegion.x = 0;
        this->rectRegion.y = 0;
        this->rectRegion.width = 0;
        this->rectRegion.height = 0;
        mw->isDefiningRectRegion = false;
        this->isFirstDoubleClick = false;
    }
    else{

    }
}

//ȡ�����������
void Qj2Widget::CancelRDefining(){
    MainWindow *mw = (MainWindow*)parentWidget()->parentWidget();
    this->rectRegion.x = 0;
    this->rectRegion.y = 0;
    this->rectRegion.width = 0;
    this->rectRegion.height = 0;
    this->points.clear();
    this->isFirstDoubleClick = false;
    mw->isDefiningRegion =false;
}

//ȡ����������鶨��
void Qj2Widget::CancelRGDefining(){
    this->rectRegion.x = 0;
    this->rectRegion.y = 0;
    this->rectRegion.width = 0;
    this->rectRegion.height = 0;
    this->points.clear();
    MainWindow *mw = (MainWindow*)parentWidget()->parentWidget();
    mw->rs.clear();
    this->rs.clear();
    mw->isDefiningRegion = false;
    this->isFirstDoubleClick = false;
}

//��ɼ��������
void Qj2Widget::CompleteRDefining(){
     // this->completeRDefine = true;
    MainWindow *mw = (MainWindow*)parentWidget()->parentWidget();
    if(mw->isDefiningRectRegion && this->rectRegion.width == 0&&isFirstDoubleClick){
        QMessageBox::information(this,tr("���������"),tr("���μ������Ķ�����δ��ɣ���Ҫ�����������㡣"));
    }
    else if(mw->isDefiningRectRegion && !(this->rectRegion.width == 0)){
        QString name = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss ddd");
        Region r = Region(name, mw->rgs[mw->rgsIndex].color, this->rectRegion.x + this->mat.cols, this->rectRegion.y, this->rectRegion.width, this->rectRegion.height);
        mw->rs.push_back(r);
        //Ϊ���ڵ���ɼ�������timeroutˢ�»���ʱ��������ʾ�ոջ��������ȱ�������ʱrs�У���Ϊ��δ����飬���Բ�������mat�л�
        this->rs.push_back(Region(name,mw->rgs[mw->rgsIndex].color,rectRegion));
        this->rectRegion.x = 0;
        this->rectRegion.y = 0;
        this->rectRegion.width = 0;
        this->rectRegion.height = 0;
        this->isFirstDoubleClick = false;
    }
    else if(!(mw->isDefiningRectRegion) && (this->points.size() <= 2)&&isFirstDoubleClick){
        QMessageBox::information(this,tr("���������"),tr("����μ������Ķ�����δ��ɣ�������Ҫ������������"));
        this->isFirstDoubleClick = false;
    }
    else if(!(mw->isDefiningRectRegion) && (this->points.size() > 2)){
        QString name = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss ddd");
        vector<Point> points1;
        for(int i = 0; i < points.size(); i++){
            Point pp2 = Point(points[i].x + mat.cols, points[i].y);
            points1.push_back(pp2);
        }
        Region r = Region(name, mw->rgs[mw->rgsIndex].color, points1);
        mw->rs.push_back(r);
        this->rs.push_back(Region(name, mw->rgs[mw->rgsIndex].color, points));
        this->points.clear();
        this->isFirstDoubleClick = false;
    }
    else{

    }

}

//��ɼ�������鶨��
void Qj2Widget::CompleteRGDefining(){
    MainWindow *mw = (MainWindow*)parentWidget()->parentWidget();
    if(mw->isDefiningRegion == false)
        return;
    mw->isDefiningRegion = false;
   this->CompleteRDefining();
    if(mw->rs.size() == 0)
        return;
   for(int i = 0; i < mw->rs.size(); i++){
       mw->rgs[mw->rgsIndex].addRegion(mw->rs[i]);
   }

   mw->rs.clear();
   this->rs.clear();
   //�����������Ȼ�ı༭�����һ�����һ���飬index�������һ����
   //�ڶ�������Ǵ����ý���ѡ��һ������б༭����ôindexָ������飬����rgs���һ����δ��ɱ༭

   if(mw->rgsIndex + 1 == mw->rgs.size()){
       mw->rgsIndex++;
       char name  = 'a' + mw->rgsIndex;
       RegionGroup *rg = new RegionGroup((QString)name, Scalar(0,255,0));
       mw->rgs.push_back(*rg);
   }else{
       mw->rgsIndex = mw->rgs.size()-1;
   }
}

void Qj2Widget::mouseDoubleClickEvent(QMouseEvent *e){
    MainWindow *mw = (MainWindow*)parentWidget()->parentWidget();
    Rect nrect;
    if(e->button() == Qt::LeftButton && mw->isDefiningRectRegion && !isFirstDoubleClick){
       isFirstDoubleClick = true;
       position11 = e->pos();
    }
    else if(e->button() == Qt::LeftButton && mw->isDefiningRectRegion && isFirstDoubleClick){
        isFirstDoubleClick = false;
        int posX = e->x();
        int posY = e->y();
        int x_position22;
        int y_position22;
        if(posX>this->width())
        {
            x_position22 = e->x();
        }
        else if( posX< 0)
        {
            x_position22 =0;
        }
        else
        {
            x_position22 = e->x();
        }
        if( posY>this->height())
        {
            y_position22 = e->y();
        }

        else if ( posY < 0)
        {
            y_position22=0;
        }
        else
        {
            y_position22=posY;
        }
        if(x_position22<=this->width() && y_position22<=this->height()){
            if(position11.x()<x_position22 && position11.y()<y_position22)
            {
                nrect.x=getMatX(position11.x());
                nrect.y=getMatY(position11.y());
                nrect.width=getMatX(x_position22)-getMatX(position11.x());
                nrect.height=getMatY(y_position22)-getMatY(position11.y());
            }
            else if(position11.x()<x_position22 && position11.y()> y_position22)
            {
                nrect.x=getMatX(position11.x());
                nrect.y=getMatY(y_position22);
                nrect.width=getMatX(x_position22)-getMatX(position11.x());
                nrect.height=getMatY(position11.y())-getMatY(y_position22);
            }
            else if(position11.x()>x_position22 && position11.y()< y_position22)
            {
                nrect.x=getMatX(x_position22);
                nrect.y=getMatY(position11.y());
                nrect.width=getMatX(position11.x())-getMatX(x_position22);
                nrect.height=getMatY(y_position22)-getMatY(position11.y());
            }
            else if(position11.x()>x_position22 && position11.y()> y_position22)
            {
                nrect.x=getMatX(x_position22);
                nrect.y=getMatY(y_position22);
                nrect.width=getMatX(position11.x())-getMatX(x_position22);
                nrect.height=getMatY(position11.y())-getMatY(y_position22);
            }
        }
        if(nrect.width<0){
            this->rectRegion.width = -nrect.width;
            this->rectRegion.height= -nrect.height;
            this->rectRegion.x = nrect.x+nrect.width;
            this->rectRegion.y = nrect.y+nrect.height;
        }
        else if(nrect.height<0){
            this->rectRegion.width = -nrect.width;
            this->rectRegion.height= -nrect.height;
            this->rectRegion.x = nrect.x+nrect.width;
            this->rectRegion.y = nrect.y+nrect.height;
        }
        else{
            this->rectRegion.x = nrect.x;
            this->rectRegion.y = nrect.y;
            this->rectRegion.width = nrect.width;
            this->rectRegion.height = nrect.height;

        }
        //this->rectRegion.x += this->mat.cols;

        MainWindow *mw = (MainWindow*)parentWidget()->parentWidget();
        mw->loadPictureToLabel2(isRect, qrect, mw->rgs[mw->rgsIndex].color, QRect(rectRegion.x, rectRegion.y, rectRegion.width, rectRegion.height), points);
    }
    else if(e->button() == Qt::LeftButton && !mw->isDefiningRectRegion){
        QPoint qp = e->pos();
        Point p = Point(getMatX(qp.x()),getMatY(qp.y()));
        this->points.push_back(p);
        MainWindow *mw = (MainWindow*)parentWidget()->parentWidget();
        mw->loadPictureToLabel2(isRect, qrect, mw->rgs[mw->rgsIndex].color, QRect(rectRegion.x, rectRegion.y, rectRegion.width, rectRegion.height), points);
    }
    else{

    }


    e->ignore();
}
void Qj2Widget::mousePressEvent(QMouseEvent *e)
{
    //qDebug()<<"���ѹ���¼�����qj1widget";
    if(e->button() == Qt::LeftButton)
    {
        //isDrag = true;
        //isRect = false;
        position1 = e->pos();//e->globalPos() - this->pos();
        //e->accept();
        qDebug()<<position1;
    }

    MainWindow *mw = (MainWindow*)parentWidget()->parentWidget();
    if(mw->location){
    double locationX,locationY;
    locationX = this->getMatX(position1.x());
    locationY = this->getMatY(position1.y());
        QPixmap pixmap1 = QPixmap::fromImage(mw->imgLabel2);
        QPainter p(&pixmap1);
        QPen pen;
        pen.setColor(QColor(255,255,255,255));
        QFont font("��Բ", 80, QFont::Bold);
        p.setFont(font);
        p.setPen(pen);
        //p.drawRect(QRect(position1.x()-2,position1.y()+2,1000,100));
        p.drawText(locationX-2,locationY+2,QString("x:").append(QString::number(locationX)).append("  ").append(QString("y:")).append(QString::number(locationY)));

        mw->label2->setScaledContents(true);
        mw->label2->setPixmap(pixmap1);
        }
    e->ignore();//��������ǳ���Ҫ��ʹ�ø�����¼����������Ա�ִ��
}

void Qj2Widget::mouseMoveEvent(QMouseEvent *e)
{
//    if(isDrag && (e->buttons() && Qt::LeftButton)){
//        //move(e->globalPos() - position1);
//        isMove = true;
//        isRect = false;
//        MainWindow *mw = (MainWindow*)parentWidget()->parentWidget();
//        mw->widget2->CancelSelect();
//        //e->accept();
//        //position2 = e->pos();//e->globalPos() - this->pos();
//    }
//    e->ignore();
}

void Qj2Widget::mouseReleaseEvent(QMouseEvent *e)
{
    int posX = e->x();
    int posY = e->y();
    MainWindow *mw = (MainWindow*)parentWidget()->parentWidget();
//    if(isDrag && isMove){
//        if(posX>this->width())
//        {
//             x_position2 = e->x();
//        }
//        else if( posX< 0)
//        {
//           x_position2 =0;
//        }
//        else
//        {
//            x_position2 = e->x();
//        }
//       if( posY>this->height())
//        {
//           y_position2 = e->y();
//        }

//        else if ( posY < 0)
//        {
//            y_position2=0;
//        }
//       else
//       {
//            y_position2=posY;
//       }
//        //e->globalPos() - this->pos();
//        //qDebug()<<position2;
//        //
//        if(x_position2<=this->width() && y_position2<=this->height()){
//            if(position1.x()<x_position2 && position1.y()<y_position2)
//            {
//                newrect.x=getMatX(position1.x());
//                newrect.y=getMatY(position1.y());
//                newrect.width=getMatX(x_position2)-getMatX(position1.x());
//                newrect.height=getMatY(y_position2)-getMatY(position1.y());
//                qrect = QRect(newrect.x,newrect.y,newrect.width,newrect.height);
//            }
//            else if(position1.x()<x_position2 && position1.y()> y_position2)
//            {
//                newrect.x=getMatX(position1.x());
//                newrect.y=getMatY(y_position2);
//                newrect.width=getMatX(x_position2)-getMatX(position1.x());
//                newrect.height=getMatY(position1.y())-getMatY(y_position2);
//                qrect = QRect(newrect.x,newrect.y,newrect.width,newrect.height);
//            }
//            else if(position1.x()>x_position2 && position1.y()< y_position2)
//            {
//                newrect.x=getMatX(x_position2);
//                newrect.y=getMatY(position1.y());
//                newrect.width=getMatX(position1.x())-getMatX(x_position2);
//                newrect.height=getMatY(y_position2)-getMatY(position1.y());
//                qrect = QRect(newrect.x,newrect.y,newrect.width,newrect.height);
//            }
//            else if(position1.x()>x_position2 && position1.y()> y_position2)
//            {
//                newrect.x=getMatX(x_position2);
//                newrect.y=getMatY(y_position2);
//                newrect.width=getMatX(position1.x())-getMatX(x_position2);
//                newrect.height=getMatY(position1.y())-getMatY(y_position2);

//                qrect = QRect(newrect.x,newrect.y,newrect.width,newrect.height);
//            }
//            MainWindow *mw = (MainWindow*)parentWidget()->parentWidget();
//            //mw->test();
//            //rectangle(mat,newrect,Scalar(0,0,255),1,1,0);
//            //cv::cvtColor(mat, mat, CV_BGR2RGB);
//            isRect = true;
//            mw->loadPictureToLabel2(isRect, qrect, mw->rgs[mw->rgsIndex].color, QRect(rectRegion.x-mat.cols, rectRegion.y, rectRegion.width, rectRegion.height), points);

//        }
//        else if(isRect){

//        }
//        else{
//            isDrag = false;
//            isMove = false;
//        }
//    }
     if((!mw->isDefiningRegion) && (e->button() == Qt::LeftButton)){
        this->isClicked = true;
        mw->widget2->isClicked = false;
        if(mw->widget3->isClicked){
            this->isTo3 = true;
            mw->widget1->isTo3 = false;
            int xx = this->getMatX(posX);
            int yy = this->getMatY(posY);
            int height = this->mat.rows;
            int width = height * mw->widget3->width() / mw->widget3->height();
            int xx2, yy2;
            if(xx-width/2 >= 0){
                xx2 = xx- width/2;
                yy2 = 0;
            }
            else{
                xx2 = xx- width/2 + this->pano.cols;
                yy2 = 0;
            }
            this->rectan3 = Rect(xx2, yy2, width, height);

            mw->widget3->setFrom(2);

            mw->widget3->setRect(getQRectan3());

            Mat mat1 = getTwoPano();
            Size dsize ;
            double scale = 1;
            dsize = Size(mat1.cols*scale,mat1.rows*scale);
            Mat image3;
            mat1(getQRectan3()).copyTo(image3);//mw->QImageToMat(mw->aa);
            Mat image33 = Mat(dsize,CV_32S);
            cv::resize(image3, image33,dsize);
            mw->widget3->setMat(image33);
            mw->widget3->draw();

            mw->widget3->isClicked =false;
            mw->widget4->isClicked = false;
            mw->widget6->isClicked = false;
        }
        else if(mw->widget4->isClicked){
            this->isTo4 = true;
            mw->widget1->isTo4 = false;
            int xx = this->getMatX(posX);
            int yy = this->getMatY(posY);
            int height = this->mat.rows/2;
            int width = height * mw->widget4->width() / mw->widget4->height();
            int xx2, yy2;
            if(xx-width/2 >= 0){
                xx2 = xx- width/2;
                //yy2 = 0;
            }
            else{
                xx2 = xx- width/2 + this->pano.cols;
                //yy2 = 0;
            }
            if((yy - height/2 >=0) && (yy + height/2 <= mat.rows)){
                yy2 = yy - height / 2;
            }
            else if(yy - height/2 <=0){
                yy2 = 0;
            }
            else if(yy + height/2 >= mat.rows){
                yy2 = mat.rows / 2;
            }
            this->rectan4 = Rect(xx2, yy2, width, height);

            mw->widget4->setFrom(2);

            mw->widget4->setRect(getQRectan4());

            Mat mat1 = getTwoPano();
            Size dsize ;
            double scale = 1;
            dsize = Size(mat1.cols*scale,mat1.rows*scale);
            Mat image4;
            mat1(getQRectan4()).copyTo(image4);//mw->QImageToMat(mw->aa);
            Mat image44 = Mat(dsize,CV_32S);
            cv::resize(image4, image44,dsize);
            mw->widget4->setMat(image44);
            mw->widget4->draw();

            mw->widget3->isClicked =false;
            mw->widget4->isClicked = false;
            mw->widget6->isClicked = false;
        }
        else if(mw->widget6->isClicked){
            this->isTo6 = true;
            mw->widget1->isTo6 = false;
            int xx = this->getMatX(posX);
            int yy = this->getMatY(posY);
            int height = this->mat.rows/2;
            int width = height * mw->widget6->width() / mw->widget6->height();
            int xx2, yy2;
            if(xx-width/2 >= 0){
                xx2 = xx- width/2;
                //yy2 = 0;
            }
            else{
                xx2 = xx- width/2 + this->pano.cols;
                //yy2 = 0;
            }
            if((yy - height/2 >=0) && (yy + height/2 <= mat.rows)){
                yy2 = yy - height / 2;
            }
            else if(yy - height/2 <=0){
                yy2 = 0;
            }
            else if(yy + height/2 >= mat.rows){
                yy2 = mat.rows / 2;
            }
            this->rectan6 = Rect(xx2, yy2, width, height);

            mw->widget6->setFrom(2);

            mw->widget6->setRect(getQRectan6());

            Mat mat1 = getTwoPano();
            Size dsize ;
            double scale = 1;
            dsize = Size(mat1.cols*scale,mat1.rows*scale);
            Mat image6;
            mat1(getQRectan6()).copyTo(image6);//mw->QImageToMat(mw->aa);
            Mat image66 = Mat(dsize,CV_32S);
            cv::resize(image6, image66,dsize);
            mw->widget6->setMat(image66);
            mw->widget6->draw();
            mw->widget3->isClicked =false;
            mw->widget4->isClicked = false;
            mw->widget6->isClicked = false;
        }
        else{

        }
    }
    isDrag = false;
    isMove = false;
    e->ignore();
}

//void Qj2Widget::paintEvent(QPaintEvent *){
//     paint->begin(this);
//     paint->setPen(QPen(Qt::red,4,Qt::SolidLine)); //���û�����ʽ
//     paint->setBrush(QBrush(Qt::red,Qt::SolidPattern)); //���û�ˢ��ʽ
//     paint->drawRect(20,20,160,160);
//     paint->end();
//}

Rect Qj2Widget::getRectan3(){
    return this->rectan3;
}

Rect Qj2Widget::getQRectan3(){
    return Rect(rectan3.x+mat.cols,rectan3.y,rectan3.width,rectan3.height);
}

Rect Qj2Widget::getRectan4(){
    return this->rectan4;
}

Rect Qj2Widget::getQRectan4(){
    return Rect(rectan4.x+mat.cols,rectan4.y,rectan4.width,rectan4.height);
}
Rect Qj2Widget::getRectan6(){
    return this->rectan6;
}

Rect Qj2Widget::getQRectan6(){
    return Rect(rectan6.x+mat.cols,rectan6.y,rectan6.width,rectan6.height);
}
//��Widget�����X���ͼ���е�X
double Qj2Widget::getMatX(double x){
    return x*mat.cols/this->width();
}

//��Widget�����Y���ͼ���е�Y
double Qj2Widget::getMatY(double y){
    return y*mat.rows/this->height();
}

//��ͼ���е�X���Widget�е�X
double Qj2Widget::getWidgetX(double x){
    return (x)*this->width()/mat.cols;
}

//��ͼ���е�Y���Widget�е�Y
double Qj2Widget::getWidgetY(double y){
    return y*this->height()/mat.rows;
}

double Qj2Widget::getDirectionX(double x){
    //double x = this->rectan.x;
    return 180*(x)/mat.cols +90;
}

double Qj2Widget::getDirectionY(double y){

    double yy = 20;
    //double y = this->rectan.y;
    return yy*y/mat.rows;

}

double Qj2Widget::getDirectionX3(){
    double x = this->rectan3.x;
    return 180*(x)/mat.cols +90;
}

double Qj2Widget::getDirectionY3(){

    double yy = 20;
    double y = this->rectan3.y;
    return yy*y/mat.rows;

}

double Qj2Widget::getDirectionX4(){
    double x = this->rectan4.x;
    return 180*(x)/mat.cols +90;
}

double Qj2Widget::getDirectionY4(){

    double yy = 20;
    double y = this->rectan4.y;
    return yy*y/mat.rows;

}

double Qj2Widget::getDirectionX6(){
    double x = this->rectan6.x;
    return 180*(x)/mat.cols +90;
}

double Qj2Widget::getDirectionY6(){

    double yy = 20;
    double y = this->rectan6.y;
    return yy*y/mat.rows;

}

double Qj2Widget::getDirectionX32(){
    double x = this->rectan3.x+this->rectan3.width;
    return 180*(x)/mat.cols +90;
}

double Qj2Widget::getDirectionY32(){

    double yy = 20;
    double y = this->rectan3.y+this->rectan3.height;
    return yy*y/mat.rows;

}

double Qj2Widget::getDirectionX42(){
    double x = this->rectan4.x+this->rectan4.width;
    return 180*(x)/mat.cols +90;
}

double Qj2Widget::getDirectionY42(){

    double yy = 20;
    double y = this->rectan4.y+this->rectan4.height;
    return yy*y/mat.rows;

}

double Qj2Widget::getDirectionX62(){
    double x = this->rectan6.x+this->rectan6.width;
    return 180*(x)/mat.cols +90;
}

double Qj2Widget::getDirectionY62(){

    double yy = 20;
    double y = this->rectan6.y+this->rectan6.height;
    return yy*y/mat.rows;

}

vector<MyObject> Qj2Widget::getSelectedObjects3(){
    vector<MyObject> os;
    int count = this->objs.size();
    for(int i = 0; i < count; i++){
        MyObject obj = objs[i];
        if(isObjSelected3(obj)){
            os.push_back(obj);
        }

    }

    for(int i = 0; i < count; i++){
        MyObject obj = objs[i];

        //�Ѿ����ֹ��ģ�Ҳ����
        MainWindow *mw = (MainWindow*)parentWidget()->parentWidget();

        vector<MyObject> aos = mw->widget3->objs;
        for(int j = 0; j < aos.size(); j++){
            MyObject aobj = aos[j];
            if(obj.getID() == aobj.getID()){
                boolean all = false;
                for(int k = 0; k < os.size(); k++){
                    MyObject bobj = os[k];
                    if(aobj.getID() == bobj.getID()){
                        all = true;
                    }
                }
                if(!all){
                    os.push_back(obj);
                    all = false;
                }
            }
        }
    }


    return os;
}

vector<MyObject> Qj2Widget::getSelectedObjects4(){
    vector<MyObject> os;
    int count = this->objs.size();
    for(int i = 0; i < count; i++){
        MyObject obj = objs[i];
        if(isObjSelected4(obj)){
            os.push_back(obj);
        }
    }

    for(int i = 0; i < count; i++){
        MyObject obj = objs[i];

        //�Ѿ����ֹ��ģ�Ҳ����
        MainWindow *mw = (MainWindow*)parentWidget()->parentWidget();

        vector<MyObject> aos = mw->widget4->objs;
        for(int j = 0; j < aos.size(); j++){
            MyObject aobj = aos[j];
            if(obj.getID() == aobj.getID()){
                boolean all = false;
                for(int k = 0; k < os.size(); k++){
                    MyObject bobj = os[k];
                    if(aobj.getID() == bobj.getID()){
                        all = true;
                    }
                }
                if(!all){
                    os.push_back(obj);
                    all = false;
                }
            }
        }
    }

    return os;
}

vector<MyObject> Qj2Widget::getSelectedObjects6(){
    vector<MyObject> os;
    int count = this->objs.size();
    for(int i = 0; i < count; i++){
        MyObject obj = objs[i];
        if(isObjSelected6(obj)){
            os.push_back(obj);
        }
    }

    for(int i = 0; i < count; i++){
        MyObject obj = objs[i];

        //�Ѿ����ֹ��ģ�Ҳ����
        MainWindow *mw = (MainWindow*)parentWidget()->parentWidget();

        vector<MyObject> aos = mw->widget6->objs;
        for(int j = 0; j < aos.size(); j++){
            MyObject aobj = aos[j];
            if(obj.getID() == aobj.getID()){
                boolean all = false;
                for(int k = 0; k < os.size(); k++){
                    MyObject bobj = os[k];
                    if(aobj.getID() == bobj.getID()){
                        all = true;
                    }
                }
                if(!all){
                    os.push_back(obj);
                    all = false;
                }
            }
        }
    }

    return os;
}
