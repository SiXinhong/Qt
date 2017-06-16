
#include "qj1widget.h"
#include "mainwindow.h"

using namespace cv;
using namespace std;

Qj1Widget::Qj1Widget(QWidget *parent) :
    QWidget(parent){
        isDrag = false;
        isMove = false;
        isRect = false;

        Cancel_Select = new QAction(tr("ȡ��ѡ��"),this);
        To_Zhu= new QAction(tr("������ʾ��"), this);
        To_Ningshi = new QAction(tr("��������ʾ��"), this);
        //To_Tanchu = new QAction(tr("����������"),this);
        connect(Cancel_Select, SIGNAL(triggered()), this, SLOT(CancelSelect()));
        connect(To_Zhu, SIGNAL(triggered()), this, SLOT(ToZhu()));
        connect(To_Ningshi, SIGNAL(triggered()), this, SLOT(ToNingshi()));
        //connect(To_Tanchu, SIGNAL(triggered()), this, SLOT(ToTanchu()));

        rectan = Rect(1490,250,100,100);
    }

void Qj1Widget::setMat(Mat m){
    mat = m;
    if(isRect){
        MainWindow *mw = (MainWindow*)parentWidget()->parentWidget();
        //mw->test();

        mw->drawRecOnPic2(mat,rectan);
        cv::cvtColor(mat, mat, CV_BGR2RGB);
        mw->loadPictureToLabel1();
        isRect = true;
    }
}

Mat Qj1Widget::getMat(){
    return mat;
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

void Qj1Widget::ToZhu()
{
    //qDebug()<<"������ʾ����";
    MainWindow *mw = (MainWindow*)parentWidget()->parentWidget();
    Mat mat = getMat();
    Size dsize ;
    double scale = 1;
    dsize = Size(mat.cols*scale,mat.rows*scale);
    Mat image11 = Mat(dsize,CV_32S);
    cv::resize(mat, image11,dsize);
    mw->img = QImage((const unsigned char*)(image11.data),image11.cols,mat.rows, image11.cols*image11.channels(),  QImage::Format_RGB888);

    //vector<Rectan> rectans;
    mw->aa=(&(mw->img))->copy(getQRectan());
    Mat image3 = mw->QImageToMat(mw->aa);
    Mat image33 = Mat(dsize,CV_32S);
    cv::resize(image3, image33,dsize);
    mw->widget3->setMat(image33);
    mw->widget3->draw();
    isRect = false;
}
//��������ʾ����ʾ�˵������¼�
void Qj1Widget::ToNingshi()
{
    MainWindow *mw = (MainWindow*)parentWidget()->parentWidget();
    Mat mat = getMat();
    Size dsize ;
    double scale = 1;
    dsize = Size(mat.cols*scale,mat.rows*scale);
    Mat image11 = Mat(dsize,CV_32S);
    cv::resize(mat, image11,dsize);
    mw->img = QImage((const unsigned char*)(image11.data),image11.cols,mat.rows, image11.cols*image11.channels(),  QImage::Format_RGB888);

    //vector<Rectan> rectans;
    mw->aa=(&(mw->img))->copy(getQRectan());
    Mat image4 = mw->QImageToMat(mw->aa);
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
    qDebug()<<"���ѹ���¼�����qj1widget";
    if(e->button() == Qt::LeftButton)
    {
        isDrag = true;
        //isRect = false;
        position1 = e->pos();//e->globalPos() - this->pos();
        //e->accept();
        qDebug()<<position1;
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
        qDebug()<<position2;
        //
        if(position2.x()<=this->width() && position2.y()<=this->height()){
            //qrectan = QRect(position1.x(),position1.y(),position2.x()-position1.x(),position2.y()-position1.y());

            rectan.x=getMatX(position1.x());// = Rect(1490,250,100,100);
            rectan.y=getMatY(position1.y());
            rectan.width=getMatX(position2.x())-getMatX(position1.x());
            rectan.height=getMatY(position2.y())-getMatY(position1.y());

            MainWindow *mw = (MainWindow*)parentWidget()->parentWidget();
            //mw->test();

            mw->drawRecOnPic2(mat,rectan);
            cv::cvtColor(mat, mat, CV_BGR2RGB);
            mw->loadPictureToLabel1();
            isRect = true;
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

Rect Qj1Widget::getRectan(){
    return this->rectan;
}

QRect Qj1Widget::getQRectan(){
    return QRect(rectan.x+2,rectan.y+2,rectan.width-2,rectan.height-2);
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
