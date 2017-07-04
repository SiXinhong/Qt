#include "show_sdk.h"


/*
   设置三种参数
   1.mode=0:算法参数，此时id默认为0，无意义
   2.mode=1:转台参数
   3.mode=3:摄像头参数
*/
int SetAlgorithmPara(const char *para_string);
int SetControlPara(int id, const char *para_string);
int SetCameraPara(int id, const char *para_string);

int  Getpanorama(IntegratedData *&data);
int  GetObjectFeature(IntegratedData *&data);

int GetAlgorithmPara(char *&para_string);
int GetControlPara(int id,char *&para_string);
int GetCameraPara(int id, char *&para_string);


int SetSystemPara(int mode, const char *para_string, int id)
{
	//检查输入参数
	if (para_string == NULL)
        return 0;//SYSTEM_ERROR::ERROR_SringIsNull;
	if (mode != 0 && mode != 1 && mode != 2)
        return 1;//SYSTEM_ERROR::ERROR_MODE;
	if (id<MIN_ID || id>MAX_ID)
        return 2;//SYSTEM_ERROR::ERROR_Id;

	//根据mode分别设置参数
	switch (mode)
	{
	case 0:
		return SetAlgorithmPara(para_string);
		break;
	case 1:
		return SetControlPara(id,para_string);
		break;
	case 2:
		return SetCameraPara(id, para_string);
		break;
	default:
        return 3;//SYSTEM_ERROR::ERROR_MODE;
		break;
	}

}


int GetSurveillanceData(int mode, IntegratedData  *&data)
{
	//检查输入
	if (mode != 0 && mode != 1)
        return 0;//SYSTEM_ERROR::ERROR_MODE;
	switch (mode)
	{
	case 0:
		return Getpanorama(data);
		break;
	case 1:
		return GetObjectFeature(data);
		break;
	default:
        return 1;//SYSTEM_ERROR::ERROR_MODE;
		break;
	}

}


int GetSystemPara(int mode, char *&para_string, int id)
{
	//输入检查
	if (mode != 0 && mode != 1 && mode != 2)
        return 1;//SYSTEM_ERROR::ERROR_MODE;
	//获取参数
	switch (mode)
	{
	case 0:
		return GetAlgorithmPara(para_string);
		break;
	case 1:
		return GetControlPara(id, para_string);
		break;
	case 2:
		return GetCameraPara(id, para_string);
		break;
	default:
        return 3;//SYSTEM_ERROR::ERROR_MODE;
		break;
	}

}


/**************************************************************调用子函数************************************************************************/
int SetAlgorithmPara(const char *para_string)
{
	//检查输入参数
	if (para_string == NULL)
        return 0;//SYSTEM_ERROR::ERROR_SringIsNull;
    //检查string的内容是否符合标准
	return SetParaSuccess;
}

int SetControlPara(int id, const char *para_string)
{
	//检查输入参数
	if (id<MIN_ID || id>MAX_ID)
        return 1;//SYSTEM_ERROR::ERROR_Id;
	
	if (para_string == NULL)
        return 2;//SYSTEM_ERROR::ERROR_SringIsNull;
	//检查string的内容是否符合标准
	return SetParaSuccess;
}

int SetCameraPara(int id, const char *para_string)
{
	//检查输入参数
	if (id<MIN_ID || id>MAX_ID)
        return 3;//SYSTEM_ERROR::ERROR_Id;

	if (para_string == NULL)
        return 4;//SYSTEM_ERROR::ERROR_SringIsNull;
	//检查string的内容是否符合标准
	return SetParaSuccess;
 
}


int  Getpanorama(IntegratedData *&data)
{
	if (data == NULL)
        return 1;//SYSTEM_ERROR::ERROR_DataStructIsNull;
	std::ifstream t;
	t.open("image\\1.txt", ios::in);      // open input file
	if (t.fail())
        return 2;//SYSTEM_ERROR::ERROR_HasNoValidFile;
	int *p = new int[100];

	int d = 0;
	int i = 0;
	while (t >> d)
	{
		p[i] = d;
		i++;
	}
	int length = i;
	//time
	i = 0;
	data->time.year = p[i++];
	data->time.month = p[i++];
	data->time.day = p[i++];
	data->time.hour = p[i++];
	data->time.minute = p[i++];
	data->time.seconds = p[i++];
	cv::Mat pano = cv::imread("image\\pano.bmp");
	if (pano.empty())
        return 3;//SYSTEM_ERROR::ERROR_GetFail;
	data->panoImage = pano;
	return GetDataSuccess;
	
}

int  GetObjectFeature(IntegratedData *&data)
{

	if (data == NULL)
        return 1;//SYSTEM_ERROR::ERROR_DataStructIsNull;

	std::ifstream t;
	t.open("image\\1.txt", ios::in);      // open input file  
	if (t.fail())
        return 2;//SYSTEM_ERROR::ERROR_HasNoValidFile;
	int *p = new int[100];

	int d = 0;
	int i = 0;
	while (t >> d)
	{
		p[i] = d;
		i++;
	}
	int length = i;
	//time
	i = 0;
	data->time.year = p[i++];
	data->time.month = p[i++];
	data->time.day= p[i++];
	data->time.hour = p[i++];
	data->time.minute = p[i++];
	data->time.seconds = p[i++];
	

	
	//id
	SmallTarget target;
	target.id = p[i++];

	//point
	target.cenPoint.x = p[i++];
	target.cenPoint.y = p[i++];

    //blocksize 
	target.blocksize.height = p[i++];
	target.blocksize.width = p[i++];
	
	//others
	target.Velocity = p[i++];
	target.MotionDerection = p[i++];
	target.area = p[i++];
	target.horizontalAxisLength = p[i++];
	target.verticalAxisLength = p[i++];
	target.absoluteIntensity = p[i++];
	target.relativeIntensity = p[i++];


	//目标轮廓
	int index = i;
	vector<cv::Point> continus;
	for (; i < length; i=i+2)
	{
		cv::Point point;
		point.x = p[i];
		point.y = p[i + 1];
		continus.push_back(point);
	}
	
	target.contours = continus;
	target.Snapshoot = cv::imread("image\\1.jpg");
	target.sihouette = cv::imread("image\\2.jpg");
	data->targets.push_back(target);


	return GetDataSuccess;
}


int GetAlgorithmPara(char *&para_string)
{
	para_string = "this is algorithm parameter";

	return GetParaSuccess;
}

int GetControlPara(int id,char *&para_string)
{
	//检查输入参数
	if (id<MIN_ID || id>MAX_ID)
        return 1;//SYSTEM_ERROR::ERROR_Id;
	para_string = "this is control parameter";

	return GetParaSuccess;
}

int GetCameraPara(int id,char *&para_string)
{
	//检查输入参数
	if (id<MIN_ID || id>MAX_ID)
        return 2;//SYSTEM_ERROR::ERROR_Id;
	para_string = "this is camera parameter";

	return GetParaSuccess;
}

QDataStream& writeMat2(QDataStream &out,cv::Mat &m){
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

QDataStream& readMat2(QDataStream &in,cv::Mat &m){
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
QDataStream& readSmallTarget(QDataStream &in,SmallTarget& data){
    in>>data.id;
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
        cv::Point p;
        in >>p.x>>p.y;
        data.contours.push_back(p);
    }
    int flag;
    in >> flag;
    if(flag==1){
        readMat2(in,data.Snapshoot);
    }
    in >> flag;
    if(flag==1){
        readMat2(in,data.sihouette);
    }
    in>>data.targetScale;
    in>>data.CenSueEintensity;
    in>>data.SCRValue;

    in >> size;
    double d;
    if(size>0){
        in>>d;
        data.theFeatures.push_back(d);
    }
    return in;
}

QDataStream& writeSmallTarget(QDataStream &out,SmallTarget& data){
    out<<data.id;
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
        writeMat2(out,data.Snapshoot);
    }
    if(data.sihouette.empty()){
        out<<-1;
    }else{
        out<<1;
        writeMat2(out,data.sihouette);
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

QDataStream& writeIntegratedData(QDataStream &out,IntegratedData& data){
    out<<data.time.year<<data.time.month<<data.time.day<<data.time.hour<<data.time.minute<<data.time.seconds<<data.time.millisecond;
    if(data.panoImage.empty()){
        out<<-1;
    }else{
        out<<1;
        writeMat2(out,data.panoImage);
    }
    int size=data.targets.size();
    out<<size;
    if(size>0){
        for(int j=0;j<size;j++){
            SmallTarget smallTarget=data.targets.at(j);
            writeSmallTarget(out,smallTarget);
        }
    }
    return out;
}

QDataStream& readIntegratedData(QDataStream &in,IntegratedData& data){
    in>>data.time.year>>data.time.month>>data.time.day>>data.time.hour>>data.time.minute>>data.time.seconds>>data.time.millisecond;
    int flag;
    in>>flag;
    if(flag==1){
        readMat2(in,data.panoImage);
    }
    int size;
    in>>size;
    if(size>0){
        for(int j=0;j<size;j++){
            SmallTarget smallTarget;
            data.targets.push_back(smallTarget);
        }
    }
    return in;
}
