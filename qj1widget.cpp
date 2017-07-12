
#include "qj1widget.h"
#include "mainwindow.h"
#include "myobject.h"
#include "myobjecttrack.h"
#include "cvutil.h"


using namespace cv;
using namespace std;

Qj1Widget::Qj1Widget(QWidget *parent) :
    QWidget(parent){
        isDrag = false;
        isMove = false;
        isRect = false;

        isTo3 = true;
        isTo4 = false;

        Cancel_Select = new QAction(tr("ȡ��ѡ��"),this);
        To_Zhu= new QAction(tr("������ʾ��"), this);
        To_Ningshi = new QAction(tr("��������ʾ��"), this);
        //To_Tanchu = new QAction(tr("����������"),this);
        connect(Cancel_Select, SIGNAL(triggered()), this, SLOT(CancelSelect()));
        connect(To_Zhu, SIGNAL(triggered()), this, SLOT(ToZhu()));
        connect(To_Ningshi, SIGNAL(triggered()), this, SLOT(ToNingshi()));
        //connect(To_Tanchu, SIGNAL(triggered()), this, SLOT(ToTanchu()));

        rectan3 = Rect(1490,250,100,100);
        rectan4 = Rect(1490,250,100,100);
        newrect = Rect(1490,250,100,100);

        //paint=new QPainter;
    }

void Qj1Widget::setMat(Mat m){
    mat = m;
//    if(isRect){
//        MainWindow *mw = (MainWindow*)parentWidget()->parentWidget();
//        //mw->test();

//        rectangle(mat,newrect,Scalar(0,0,255),1,1,0);
//        cv::cvtColor(mat, mat, CV_BGR2RGB);
//        mw->loadPictureToLabel1();
//        isRect = true;
//    }
    MainWindow *mw = (MainWindow*)parentWidget()->parentWidget();
    mw->loadPictureToLabel1(isRect, qrect);
}

Mat Qj1Widget::getMat(){
    return mat;
}

void Qj1Widget::setPano(Mat p){
    this->pano = p;
}

Mat Qj1Widget::getPano(){
    return this->pano;
}


void Qj1Widget::setObjects(vector<MyObject> os){
    this->objs = os;
}

vector<MyObject> Qj1Widget::getObjects(){
    return this->objs;
}

void Qj1Widget::setTracks(vector<MyObjectTrack> ts){
    this->tracks =ts;
}

vector<MyObjectTrack> Qj1Widget::getTracks(){
    return this->tracks;
}

void Qj1Widget::contextMenuEvent(QContextMenuEvent *){
    QCursor cur=this->cursor();
    QMenu *menu=new QMenu(this);
    menu->addAction(Cancel_Select); //��Ӳ˵���1
    menu->addAction(To_Zhu); //��Ӳ˵���1
    menu->addAction(To_Ningshi); //��Ӳ˵���2
    //menu->addAction(To_Tanchu);//��Ӳ˵���3
    menu->exec(cur.pos()); //���������
}

void Qj1Widget::CancelSelect(){
    isRect = false;
}

void Qj1Widget::draw(){

    MainWindow *mw = (MainWindow*)parentWidget()->parentWidget();
    //qDebug()<<this->objs.size();
//    int count = this->objs.size();
//    for (int i = 0; i < count;i++)
//    {
//        //�������box
//        MyObject obj = objs[i];
//        rectangle(mat,obj.getRect(),obj.getColor(),2,1,0);
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
//            putText(mat,str,p,3,1,obj.getColor());
//        }
//        cv::cvtColor(mat, mat, CV_BGR2RGB);
//    }

    mw->imgLabel1 = mw->MatToQImage(mat,mw->imgLabel1);
    cv::cvtColor(mat, mat, CV_BGR2RGB);
    mw->loadPictureToLabel1(isRect, qrect);
}

boolean Qj1Widget::isObjSelected3(MyObject obj){
    boolean isSelected = false;
        if(this->rectan3.contains(obj.getCenPoint())){
            //����ѡ�����ʹ��Ŀ���box��ѡ���֮��
            if(obj.getRect().x<this->rectan3.x){
                this->rectan3.x = obj.getRect().x - 5;
                this->rectan3.width += this->rectan3.x - obj.getRect().x + 5;
            }
            if(obj.getRect().y<this->rectan3.y){
                this->rectan3.y = obj.getRect().y - 5;
                this->rectan3.height += this->rectan3.y - obj.getRect().y + 5;
            }
            if((obj.getRect().x+obj.getRect().width)>(this->rectan3.x+this->rectan3.width)){
                //this->rectan3.x = obj.getRect().x +obj.getRect().width + 5;

                this->rectan3.width = obj.getRect().x + obj.getRect().width - this->rectan3.x + 5;
            }
            if((obj.getRect().y+obj.getRect().height)>(this->rectan3.y+this->rectan3.height)){
                this->rectan3.height = this->rectan3.height + obj.getRect().y + obj.getRect().height- this->rectan3.y+ 5;
                //this->rectan3.y = obj.getRect().y +obj.getRect().height+ 5;
            }

            isSelected = true;
        }
    return isSelected;
}

boolean Qj1Widget::isObjSelected4(MyObject obj){
    boolean isSelected = false;
    if(this->rectan4.contains(obj.getCenPoint())){
        //����ѡ�����ʹ��Ŀ���box��ѡ���֮��
        if(obj.getRect().x<this->rectan4.x){
            this->rectan4.x = obj.getRect().x - 5;
            this->rectan4.width += this->rectan4.x - obj.getRect().x + 5;
        }
        if(obj.getRect().y<this->rectan4.y){
            this->rectan4.y = obj.getRect().y - 5;
            this->rectan4.height += this->rectan4.y - obj.getRect().y + 5;
        }
        if((obj.getRect().x+obj.getRect().width)>(this->rectan4.x+this->rectan4.width)){
            //this->rectan4.x = obj.getRect().x +obj.getRect().width + 5;

            this->rectan4.width = obj.getRect().x + obj.getRect().width - this->rectan4.x + 5;
        }
        if((obj.getRect().y+obj.getRect().height)>(this->rectan4.y+this->rectan4.height)){
            this->rectan4.height = this->rectan4.height + obj.getRect().y + obj.getRect().height- this->rectan4.y+ 5;
            //this->rectan4.y = obj.getRect().y +obj.getRect().height+ 5;
        }

        isSelected = true;
    }
    return isSelected;
}

void Qj1Widget::ToZhu()
{
    //qDebug()<<"������ʾ����";

    this->isTo3 = true;
    MainWindow *mw = (MainWindow*)parentWidget()->parentWidget();

    mw->widget2->isTo3 = false;

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

//    this->rectan3.x = this->newrect.x;
//    this->rectan3.y = this->newrect.y;
//    this->rectan3.width = this->newrect.width;
//    this->rectan3.height = this->newrect.height;

    //������ѡ�ľ��ο���ʹ��������ʾ���е���ʾ������
    //this->rectan3.width = this->rectan3.height * mw->widget3->width() / mw->widget3->height();

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

    mw->widget3->setFrom(1);

    mw->widget3->setRect(rectan3);
    //mw->test();

    Mat mat = getPano();
    Size dsize ;
    double scale = 1;
    dsize = Size(mat.cols*scale,mat.rows*scale);
//    Mat image11 = Mat(dsize,CV_32S);
//    cv::resize(mat, image11,dsize);
//    mw->img = QImage((const unsigned char*)(image11.data),image11.cols,image11.rows, image11.cols*image11.channels(),  QImage::Format_RGB888);
//    //mw->img = CVUtil::MatToQImage(mat, mw->img);
//    //vector<Rectan> rectans;
//    mw->aa=(&(mw->img))->copy(getQRectan3());
//    Mat image3 = mw->QImageToMat(mw->aa);
//    Mat image33 = Mat(dsize,CV_32S);
//    cv::resize(image3, image33,dsize);
//    mw->widget3->setMat(image33);
    Mat image3;
    mat(rectan3).copyTo(image3);//mw->QImageToMat(mw->aa);
    Mat image33 = Mat(dsize,CV_32S);
    cv::resize(image3, image33,dsize);
    mw->widget3->setMat(image33);
    mw->widget3->draw();

    isRect = false;
}
//��������ʾ����ʾ�˵������¼�
void Qj1Widget::ToNingshi()
{
    //qDebug()<<"������ʾ����";

    this->isTo4 = true;

    MainWindow *mw = (MainWindow*)parentWidget()->parentWidget();

    mw->widget2->isTo4 = false;

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

    mw->widget4->setFrom(1);

    mw->widget4->setRect(rectan4);

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
    mat(rectan4).copyTo(image4);//mw->QImageToMat(mw->aa);
    Mat image44 = Mat(dsize,CV_32S);
    cv::resize(image4, image44,dsize);
    mw->widget4->setMat(image44);
    mw->widget4->draw();
    isRect = false;
}
//������������ʾ�˵������¼�
//void ToTanchu(){
//    qDebug()<<"���������ڡ�";
//}

//void QjWidget::mouseClickEvent(QMouseEvent *e){

//}

void Qj1Widget::mousePressEvent(QMouseEvent *e)
{
    //qDebug()<<"���ѹ���¼�����qj1widget";
    if(e->button() == Qt::LeftButton)
    {
        isDrag = true;
        //isRect = false;
        position1 = e->pos();//e->globalPos() - this->pos();
        //e->accept();
        //qDebug()<<position1;
    }
    e->ignore();//��������ǳ���Ҫ��ʹ�ø�����¼����������Ա�ִ��
}

void Qj1Widget::mouseMoveEvent(QMouseEvent *e)
{
    if(isDrag && (e->buttons() && Qt::LeftButton)){
        //move(e->globalPos() - position1);
        isMove = true;
        isRect = false;
        MainWindow *mw = (MainWindow*)parentWidget()->parentWidget();
        mw->widget2->CancelSelect();
        //e->accept();
        //position2 = e->pos();//e->globalPos() - this->pos();
    }
    e->ignore();
}

void Qj1Widget::mouseReleaseEvent(QMouseEvent *e)
{

    if(isDrag && isMove){
        position2 = e->pos();//e->globalPos() - this->pos();
        //qDebug()<<position2;
        //
        if(position2.x()<=this->width() && position2.y()<=this->height()){
            newrect.x=getMatX(position1.x());// = Rect(1490,250,100,100);
            newrect.y=getMatY(position1.y());
            newrect.width=getMatX(position2.x())-getMatX(position1.x());
            newrect.height=getMatY(position2.y())-getMatY(position1.y());

            qrect = QRect(newrect.x,newrect.y,newrect.width,newrect.height);

            MainWindow *mw = (MainWindow*)parentWidget()->parentWidget();
            //mw->test();

            //mw->drawRecOnPic2(mat,newrect);
//            rectangle(mat,newrect,Scalar(0,0,255),1,1,0);
//            cv::cvtColor(mat, mat, CV_BGR2RGB);
            isRect = true;
            mw->loadPictureToLabel1(isRect, qrect);

        }
        else if(isRect){

        }
        else{
            isDrag = false;
            isMove = false;
        }
    }
    isDrag = false;
    isMove = false;
    e->ignore();
}

//void Qj1Widget::paintEvent(QPaintEvent *){
//     paint->begin(this);
//     paint->setPen(QPen(Qt::red,4,Qt::SolidLine)); //���û�����ʽ
//     paint->setBrush(QBrush(Qt::red,Qt::SolidPattern)); //���û�ˢ��ʽ
//     paint->drawRect(20,20,160,160);
//     paint->end();
//}

Rect Qj1Widget::getRectan3(){
    return this->rectan3;
}

Rect Qj1Widget::getQRectan3(){
    return Rect(rectan3.x,rectan3.y,rectan3.width,rectan3.height);
}

Rect Qj1Widget::getRectan4(){
    return this->rectan4;
}

Rect Qj1Widget::getQRectan4(){
    return Rect(rectan4.x,rectan4.y,rectan4.width,rectan4.height);
}

//��Widget�����X���ͼ���е�X
double Qj1Widget::getMatX(double x){
    return x*mat.cols/this->width();
}

//��Widget�����Y���ͼ���е�Y
double Qj1Widget::getMatY(double y){
    return y*mat.rows/this->height();
}

//��ͼ���е�X���Widget�е�X
double Qj1Widget::getWidgetX(double x){
    return x*this->width()/mat.cols;
}

//��ͼ���е�Y���Widget�е�Y
double Qj1Widget::getWidgetY(double y){
    return y*this->height()/mat.rows;
}

double Qj1Widget::getDirectionX(double x){
    //double x = this->rectan.x;
    return 180*x/mat.cols -90;
}

double Qj1Widget::getDirectionY(double y){

    double yy = 20;
    //double y = this->rectan.y;
    return yy*y/mat.rows;

}

double Qj1Widget::getDirectionX3(){
    double x = this->rectan3.x;
    return 180*x/mat.cols -90;
}

double Qj1Widget::getDirectionY3(){

    double yy = 20;
    double y = this->rectan3.y;
    return yy*y/mat.rows;

}

double Qj1Widget::getDirectionX4(){
    double x = this->rectan4.x;
    return 180*x/mat.cols -90;
}

double Qj1Widget::getDirectionY4(){

    double yy = 20;
    double y = this->rectan4.y;
    return yy*y/mat.rows;

}

double Qj1Widget::getDirectionX32(){
    double x = this->rectan3.x+this->rectan3.width;
    return 180*x/mat.cols -90;
}

double Qj1Widget::getDirectionY32(){

    double yy = 20;
    double y = this->rectan3.y+this->rectan3.height;
    return yy*y/mat.rows;

}

double Qj1Widget::getDirectionX42(){
    double x = this->rectan4.x+this->rectan4.width;
    return 180*x/mat.cols -90;
}

double Qj1Widget::getDirectionY42(){

    double yy = 20;
    double y = this->rectan4.y+this->rectan4.height;
    return yy*y/mat.rows;

}

vector<MyObject> Qj1Widget::getSelectedObjects3(){
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

//ѡ���Ŀ�겻�����ϣ�ֻ�ܼ���
vector<MyObject> Qj1Widget::getSelectedObjects4(){
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
