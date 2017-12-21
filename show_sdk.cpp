#include "socket.h"

#include "show_sdk.h"

#include <iostream>
#include <string>

#include <time.h>
using std::string;
using namespace std;

extern SOCKET hSocket;
extern char sendbuffer[SEND_BUFFER_SIZE];
extern char recvbuffer[RECV_BUFFER_SIZE];
extern WSANETWORKEVENTS netEvents;
extern int datalen;

extern int text;

int para_data_len = 40;

DetectorParams dp;
TrackingParameters tp;
StitchParmeters sp;

/*
   设置三种参数
   1.mode=0:算法参数，此时id默认为0，无意义
   2.mode=1:转台参数
   3.mode=3:摄像头参数
*/
int SetAlgorithmPara();
int SetControlPara(int id);
int SetCameraPara(int id,int mode);

int  Getpanorama(IntegratedData *&data);
int  GetObjectFeature(IntegratedData *&data);

int GetAlgorithmPara();
int GetControlPara(int id);
int GetCameraPara(int id);

int string_to_alg_para(char *data, int datalen);
void buff_to_target(char *buff, int datalen, vector<SmallTarget>& realtime_target);
int para_to_string(char *s, int &datalen);


int string_to_alg_para(char *data, int datalen);
void buff_to_target(char *buff, int datalen, vector<SmallTarget>& realtime_target);
int para_to_string(char *s, int &datalen);


int ROIPointsToChar(std::vector<std::vector<cv::Point> >, char *s, int &datalen);

int ParseTrackingPoints(std::vector<TrackingPoint>& _TrackPoints, char *s,const int &datalen);

/****************************************************************主接口**********************************************************************/
int SetSystemPara(int mode, int id)
{
    //检查输入参数
    if (mode>20)
        return ERROR_MODE;
    if (id<MIN_ID || id>MAX_ID)
        return ERROR_Id;

    //根据mode分别设置参数
    switch (mode)
    {
    case 0:
        return SetAlgorithmPara();//ok
        break;
    case 1:
        return SetControlPara(id);
        break;
    case 2:
        return SetCameraPara(0,id);//a
        break;
    case 3:
        return SetCameraPara(1,id);//b
        break;
    case 4:
        return SetCameraPara(2, id);//control
        break;
    default:
        return ERROR_MODE;
        break;
    }

}

int GetSurveillanceData(int mode, IntegratedData  *&data)//ok
{
	//检查输入
	if (mode != 0 && mode != 1)
        return ERROR_MODE;
	switch (mode)
	{
	case 0:
		return Getpanorama(data);
		break;
	case 1:
		return GetObjectFeature(data);
		break;
	default:
        return ERROR_MODE;
		break;
	}

}

int GetSystemPara(int mode, int id)
{
	//输入检查
	if (mode != 0 && mode != 1 && mode != 2)
        return ERROR_MODE;
	//获取参数
	switch (mode)
	{
	case 0:
		return GetAlgorithmPara();//ok
		break;
	case 1:
		return GetControlPara(id);
		break;
	case 2:
		return GetCameraPara(id);
		break;
	default:
        return ERROR_MODE;
		break;
	}

}

//12.10 加入上传标定界面内容

//调焦用 上传8位图像
int GetOriPerImg(cv::Mat &oriImage)
{
    //std::cout<<"begin"<<std::endl;
	char *buff = (char *)malloc(DATA_BUFFER_SIZE);

	int result = MySend(hSocket, 8, sendbuffer, SEND_BUFFER_SIZE, NULL, 0);
    int datalen = 0;
	if (ReadHanding(hSocket, netEvents, sendbuffer, SEND_BUFFER_SIZE, buff, &datalen) == 1)
	{
       // std::cout<<"begin"<<std::endl;
		int rows_length = (((uchar)buff[5] * 256 + (uchar)buff[6]) * 256 + (uchar)buff[7]) * 256 + (uchar)buff[8];
		int cols_length = (((uchar)buff[9] * 256 + (uchar)buff[10]) * 256 + (uchar)buff[11]) * 256 + (uchar)buff[12];
		oriImage = cv::Mat(rows_length, cols_length, CV_8UC1, &buff[13]).clone();
       // std::cout<<"begin"<<std::endl;
		free(buff);
		return 1;
	}
	else
	{
       // std::cout<<"error"<<std::endl;
		free(buff);
		return 0;
	}
}

//上传一个16位图像 为了对比度亮度
int GetOri16Img(cv::Mat &oriImage)
{
    //std::cout<<"333"<<std::endl;
	char *buff = (char *)malloc(DATA_BUFFER_SIZE);

	int result = MySend(hSocket, 12, sendbuffer, SEND_BUFFER_SIZE, NULL, 0);
    //std::cout<<"result"<<result<<std::endl;
	datalen = 0;
	if (ReadHanding(hSocket, netEvents, sendbuffer, SEND_BUFFER_SIZE, buff, &datalen) == 1)
	{
		int rows_length = (((uchar)buff[5] * 256 + (uchar)buff[6]) * 256 + (uchar)buff[7]) * 256 + (uchar)buff[8];
		int cols_length = (((uchar)buff[9] * 256 + (uchar)buff[10]) * 256 + (uchar)buff[11]) * 256 + (uchar)buff[12];
		oriImage = cv::Mat(rows_length, cols_length, CV_16UC1, &buff[13]).clone();

		free(buff);
		return 1;
	}
	else
	{
		free(buff);
		return 0;
	}
}

//下发对比度亮度
int SetDuiBiDu(double alpha,double deta)
{
	char *p = (char*)&alpha;
	char a[16];
	a[0] = *p;
	a[1] = *(p + 1);
	a[2] = *(p + 2);
	a[3] = *(p + 3);
	a[4] = *(p + 4);
	a[5] = *(p + 5);
	a[6] = *(p + 6);
	a[7] = *(p + 7);
	p = (char*)&deta;
	a[8] = *p;
	a[9] = *(p + 1);
	a[10] = *(p + 2);
	a[11] = *(p + 3);
	a[12] = *(p + 4);
	a[13] = *(p + 5);
	a[14] = *(p + 6);
	a[15] = *(p + 7);

    std::cout<<alpha<<" "<<deta<<std::endl;

    int result = MySend(hSocket, 9, sendbuffer, SEND_BUFFER_SIZE, a, 16);
	return result;
}


//接收轨迹
int GetTrack(std::vector<TrackingPoint>& _TrackPoints)
{
    std::cout<<"send track "<<std::endl;
    char *buff = (char *)malloc(DATA_BUFFER_SIZE);

    int result = MySend(hSocket, 13, sendbuffer, SEND_BUFFER_SIZE, NULL, 0);
    //std::cout<<"result"<<result<<std::endl;
    datalen = 0;
    if (ReadHanding(hSocket, netEvents, sendbuffer, SEND_BUFFER_SIZE, buff, &datalen) == 1)
    {

        ParseTrackingPoints(_TrackPoints,&buff[5],datalen-9);
         //std::cout<<"ParseTrackingPoints "<<std::endl;
        free(buff);
        return 1;
    }
    else
    {
        free(buff);
        return 0;
    }
}



//下发兴趣区
int SetORIPoints(std::vector<std::vector<cv::Point> > _ROIPoints)
{
	char *s = (char *)malloc(1024 * 1024);
	int datalen = 0;

   // std::cout<<"point"<<std::endl;

	if (ROIPointsToChar(_ROIPoints, s, datalen) != 0)
	{
         std::cout<<"point1"<<std::endl;
		return -1;
	}

    // std::cout<<"point2 "<<datalen<<std::endl;

	MySend(hSocket, 10, sendbuffer, SEND_BUFFER_SIZE, s, datalen);
    return 0;
}

//标定结束
int END()
{
	MySend(hSocket, 11, sendbuffer, SEND_BUFFER_SIZE, NULL, 0);
}

/**************************************************************调用子函数************************************************************************/
int SetAlgorithmPara()
{
	//检查输入参数
	
	int result = 0;
	char *data = (char *)malloc(para_data_len+1);
	memset(data, 0, para_data_len + 1);
	int datalen = 0;
	para_to_string(data,datalen);
	result=MySend(hSocket, 0, sendbuffer, SEND_BUFFER_SIZE, data, datalen);
	free(data);
    //检查string的内容是否符合标准
	if (result == 0){
		return SetParaSuccess;
	}
	else{
        return ERROR_SetFail;
	}
}

int SetControlPara(int id)
{
	//检查输入参数
	if (id<MIN_ID || id>MAX_ID)
        return ERROR_Id;
	
	//检查string的内容是否符合标准
	int result=0; //= MySend(hSocket, 1, sendbuffer, SEND_BUFFER_SIZE, const_cast<char*>(para_string), strlen(para_string));
	//检查string的内容是否符合标准
	if (result == 0){
		return SetParaSuccess;
	}
	else{
        return ERROR_SetFail;
	}
	
}

//11.11修改
/*
id=0代表A相机
	mode=0:状态查询
	mode=1:调焦近处
	mode=2:调焦远处
	mode=3:背景校正
	mode=4:快门校正
	mode=5:调焦停止
id=1代表B相机
	mode=0:状态查询
	mode=1:调焦近处
	mode=2:调焦远处
	mode=3:背景校正
	mode=4:快门校正
	mode=5:调焦停止
id=2代表转台
	mode=0:停止周视
	mode=1:启动周视
*/
int SetCameraPara(int id,int mode)
{
     std::cout<<"..................................."<<std::endl;
	//检查输入参数
	if (id<MIN_ID || id>MAX_ID)
		return ERROR_Id;
	int result = 0;
	if (id == 0){
		//相机A参数设置
		if (mode == 0){
			//状态查询
			char send_mode = 0;
			result = MySend(hSocket, 2, sendbuffer, SEND_BUFFER_SIZE, &send_mode, 1);
		}
		else if (mode == 1){
			//调焦近处
			char send_mode = 1;
			result = MySend(hSocket, 2, sendbuffer, SEND_BUFFER_SIZE, &send_mode, 1);
		}
		else if (mode == 2){
			//调焦远处
			char send_mode = 2;
			result = MySend(hSocket, 2, sendbuffer, SEND_BUFFER_SIZE, &send_mode, 1);
		}
		else if (mode == 3){
			//背景校正
			char send_mode = 3;
			result = MySend(hSocket, 2, sendbuffer, SEND_BUFFER_SIZE, &send_mode, 1);
		}
		else if (mode == 4){
			//快门校正
			char send_mode = 4;
			result = MySend(hSocket, 2, sendbuffer, SEND_BUFFER_SIZE, &send_mode, 1);
		}
		else if (mode == 5){
			//调焦停止
			char send_mode =5;
			result = MySend(hSocket, 2, sendbuffer, SEND_BUFFER_SIZE, &send_mode, 1);
		}
	}
	else if (id == 1){
		//相机B参数设置
		if (mode == 0){
			//状态查询
			char send_mode = 6;
			result = MySend(hSocket, 2, sendbuffer, SEND_BUFFER_SIZE, &send_mode, 1);
		}
		else if (mode == 1){
			//调焦近处
			char send_mode = 7;
			result = MySend(hSocket, 2, sendbuffer, SEND_BUFFER_SIZE, &send_mode, 1);
		}
		else if (mode == 2){
			//调焦远处
			char send_mode = 8;
			result = MySend(hSocket, 2, sendbuffer, SEND_BUFFER_SIZE, &send_mode, 1);
		}
		else if (mode == 3){
			//背景校正
			char send_mode = 9;
			result = MySend(hSocket, 2, sendbuffer, SEND_BUFFER_SIZE, &send_mode, 1);
		}
		else if (mode == 4){
			//快门校正
			char send_mode = 10;
			result = MySend(hSocket, 2, sendbuffer, SEND_BUFFER_SIZE, &send_mode, 1);
		}
		else if (mode == 5){
			//调焦停止
			char send_mode = 11;
			result = MySend(hSocket, 2, sendbuffer, SEND_BUFFER_SIZE, &send_mode, 1);
		}
	}
	else if (id == 2 ){
		//转台参数设置
		if (mode == 0){
			//停止周视
			char send_mode = 12;
			result = MySend(hSocket, 1, sendbuffer, SEND_BUFFER_SIZE, &send_mode, 1);
		}
		else if (mode == 1){
			//启动周视
			char send_mode = 13;
            char data[5];
            data[0]=send_mode;
            data[1]=(char)(text>>24);
            data[2]=(char)(text>>16);
            data[3]=(char)(text>>8);
            data[4]=(char)(text);
            std::cout<<"text..................................."<<text<<std::endl;
            result = MySend(hSocket, 1, sendbuffer, SEND_BUFFER_SIZE, data, 5);
		}
	}
	
	//检查string的内容是否符合标准
	if (result == 0){
		return SetParaSuccess;
	}
	else{
		return ERROR_SetFail;
	}
}


//更新，加入时间
int  Getpanorama(IntegratedData *&data)
{

   // std::cout<<"the time is "<<t1<<std::endl;
    static int index=0;
    char name[2];
	if (data == NULL)
        return ERROR_DataStructIsNull;

    char *buff = (char *)malloc(DATA_BUFFER_SIZE);

	int result = MySend(hSocket, 3, sendbuffer, SEND_BUFFER_SIZE, 0, 0);
#if 1
    datalen=0;

    clock_t t2;
       clock_t t1=clock();

    if (ReadHanding(hSocket, netEvents, recvbuffer, RECV_BUFFER_SIZE, buff, &datalen) == 1)
    {
        t2=clock();
        std::cout<<"the time is "<<t2-t1<<std::endl;
		data->timeinfo=(((uchar)buff[9] * 256 + (uchar)buff[10]) * 256 + (uchar)buff[11]) * 256 + (uchar)buff[12];
        int rows_length = (((uchar)buff[13] * 256 + (uchar)buff[14]) * 256 + (uchar)buff[15]) * 256 + (uchar)buff[16];
        int cols_length = (((uchar)buff[17] * 256 + (uchar)buff[18]) * 256 + (uchar)buff[19]) * 256 + (uchar)buff[20];
        cv::Mat c= cv::Mat(rows_length,cols_length, CV_8UC1, &buff[21]).clone();
        data->panoImage = c;

        //std::cout<<rows_length<<" "<<cols_length<<std::endl;
        //sprintf(name,"pic\\%d.bmp",index++);
        //cv::imwrite(name,c);
		free(buff);

		return GetDataSuccess;
	}
	else
	{
        free(buff);
        return ERROR_GetFail;
	}

#endif
}

int  GetObjectFeature(IntegratedData *&data)
{

	if (data == NULL)
        return ERROR_DataStructIsNull;

	int result = MySend(hSocket,4, sendbuffer, SEND_BUFFER_SIZE,0, 0);

    datalen=0;
    char *buff = (char *)malloc(DATA_BUFFER_SIZE);
    if (ReadHanding(hSocket, netEvents, sendbuffer, SEND_BUFFER_SIZE, buff, &datalen) == 1)
    {

        buff_to_target(&buff[13],datalen-17,data->targets);
        //std::cout<<"recive buff to target "<<std::endl;
//        if(data->targets.size()>0)
//        {
//            std::cout<<data->targets[0].cenPointACS.x<<std::endl;
//        }
//        else
//        {
//            std::cout<<"error number"<<std::endl;
//        }
       // cv::Mat c= cv::Mat(640,512, CV_8UC1, &buff[21]).clone();
       // data->panoImage = c;
   //        cv::imshow("pic", c);
//        cv::waitKey(10);

        free(buff);
        return GetDataSuccess;
    }
    else
    {
        free(buff);
        return ERROR_GetFail;
        //std::cout << "error " << std::endl;
    }

	//std::ifstream t;
	//t.open("image\\1.txt", std::ios::in);      // open input file  
	//if (t.fail())
	//	return SYSTEM_ERROR::ERROR_HasNoValidFile;
	//int *p = new int[100];

	//int d = 0;
	//int i = 0;
	//while (t >> d)
	//{
	//	p[i] = d;
	//	i++;
	//}
	//int length = i;
	////time
	//i = 0;
	//data->time.year = p[i++];
	//data->time.month = p[i++];
	//data->time.day= p[i++];
	//data->time.hour = p[i++];
	//data->time.minute = p[i++];
	//data->time.seconds = p[i++];
	//

	//
	////id
	//SmallTarget target;
	//target.id = p[i++];

	////point
	//target.cenPoint.x = p[i++];
	//target.cenPoint.y = p[i++];

 //   //blocksize 
	//target.blocksize.height = p[i++];
	//target.blocksize.width = p[i++];
	//
	////others
	//target.Velocity = p[i++];
	//target.MotionDerection = p[i++];
	//target.area = p[i++];
	//target.horizontalAxisLength = p[i++];
	//target.verticalAxisLength = p[i++];
	//target.absoluteIntensity = p[i++];
	//target.relativeIntensity = p[i++];


	////目标轮廓
	//int index = i;
	//vector<cv::Point> continus;
	//for (; i < length; i=i+2)
	//{
	//	cv::Point point;
	//	point.x = p[i];
	//	point.y = p[i + 1];
	//	continus.push_back(point);
	//}
	//
	//target.contours = continus;
	//target.Snapshoot = cv::imread("image\\1.jpg");
	//target.sihouette = cv::imread("image\\2.jpg");
	//data->targets.push_back(target);


	return GetDataSuccess;
}


int GetAlgorithmPara()
{
	char *buff = (char *)malloc(DATA_BUFFER_SIZE);
	int result = MySend(hSocket, 5, sendbuffer, SEND_BUFFER_SIZE, 0, 0);
    if(result==0)
	{
		 if (ReadHanding(hSocket, netEvents, sendbuffer, SEND_BUFFER_SIZE, buff, &datalen) == 1)
        {
		   string_to_alg_para(&buff[5], datalen-9);

		   free(buff);
		   return GetParaSuccess;
	    }
	   else
	   {
        free(buff);
        return ERROR_GetFail;
		//std::cout << "error " << std::endl;
	   }
		
	}
	free(buff);
	return GetParaSuccess;
}

int GetControlPara(int id)
{
	//检查输入参数
	if (id<MIN_ID || id>MAX_ID)
        return ERROR_Id;

	int result = MySend(hSocket,6, sendbuffer, SEND_BUFFER_SIZE, 0, 0);

	return GetParaSuccess;
}

int GetCameraPara(int id)
{
	//检查输入参数
	if (id<MIN_ID || id>MAX_ID)
        return ERROR_Id;

	int result = MySend(hSocket,7, sendbuffer, SEND_BUFFER_SIZE, 0, 0);

	return GetParaSuccess;
}


/**************************************************************辅助子函数************************************************************************/
//将数组转化为算法参数 更新算法参数
int string_to_alg_para(char *data, int datalen)
{
	if (datalen != 40)
	{
		return 1;
	}
	//sp
	int index = 0;
	sp.ZERO_ANGLE = (unsigned char)data[index] * (256 * 256 * 256) + (unsigned char)data[index + 1] * 256 * 256 + (unsigned char)data[index + 2] * 256 + (unsigned char)data[index + 3];
	//std::cout << ".............." << sp.ZERO_ANGLE << std::endl;
	//dp
	//blurkersize 
	index += 4;
	dp.blurkersize = (unsigned char)data[index] * (256 * 256 * 256) + (unsigned char)data[index + 1] * 256 * 256 + (unsigned char)data[index + 2] * 256 + (unsigned char)data[index + 3];
	//std::cout << ".............." << dp.blurkersize << std::endl;
	//blurthresh
	index += 4;
	int temp1 = (unsigned char)data[index] * (256 * 256 * 256) + (unsigned char)data[index + 1] * 256 * 256 + (unsigned char)data[index + 2] * 256 + (unsigned char)data[index + 3];
	index += 4;
	int temp2 = (unsigned char)data[index];
	dp.blurthresh = temp1 + temp2 / 10.0;
	//std::cout << ".............." << dp.blurthresh << std::endl;
	//spatialthresh 
	index += 1;
	temp1 = (unsigned char)data[index] * (256 * 256 * 256) + (unsigned char)data[index + 1] * 256 * 256 + (unsigned char)data[index + 2] * 256 + (unsigned char)data[index + 3];
	index += 4;
	temp2 = (unsigned char)data[index];
	dp.spatialthresh = temp1 + temp2 / 10.0;
	//std::cout << ".............." << dp.spatialthresh << std::endl;
	//contourSizeThresh 
	index += 1;
	dp.contourSizeThresh = (unsigned char)data[index] * (256 * 256 * 256) + (unsigned char)data[index + 1] * 256 * 256 + (unsigned char)data[index + 2] * 256 + (unsigned char)data[index + 3];
	//std::cout << ".............." << dp.contourSizeThresh << std::endl;
	//targetSCRthresh
	index += 4;
	temp1 = (unsigned char)data[index] * (256 * 256 * 256) + (unsigned char)data[index + 1] * 256 * 256 + (unsigned char)data[index + 2] * 256 + (unsigned char)data[index + 3];
	index += 4;
	temp2 = (unsigned char)data[index];
	dp.targetSCRthresh = temp1 + temp2 / 10.0;
	//std::cout << ".............." << dp.targetSCRthresh << std::endl;
	//hessianThresh 
	index += 1;
	temp1 = (unsigned char)data[index] * (256 * 256 * 256) + (unsigned char)data[index + 1] * 256 * 256 + (unsigned char)data[index + 2] * 256 + (unsigned char)data[index + 3];
	index += 4;
	temp2 = (unsigned char)data[index];
	dp.hessianThresh = temp1 + temp2 / 10.0;
	//std::cout << ".............." << dp.hessianThresh << std::endl;
	//disThresh
	index += 1;
	dp.disThresh = (unsigned char)data[index] * (256 * 256 * 256) + (unsigned char)data[index + 1] * 256 * 256 + (unsigned char)data[index + 2] * 256 + (unsigned char)data[index + 3];
	//std::cout << ".............." << dp.disThresh << std::endl;
	//tp
	index += 4;
	tp.tracking_para = (unsigned char)data[index] * (256 * 256 * 256) + (unsigned char)data[index + 1] * 256 * 256 + (unsigned char)data[index + 2] * 256 + (unsigned char)data[index + 3];
	//std::cout << ".............." << tp.tracking_para << std::endl;
	return 0;
}


//更新 将数组转换为目标集合 
void buff_to_target(char *buff, int datalen, vector<SmallTarget>& realtime_target)
{
    realtime_target.clear();
		int index = 0;
		while(index<datalen)
		{
            Target temp;

            //id
            temp.id=*(int *)&buff[index];
            index+=4;
            //std::cout<<"sdk id "<<temp.id<<std::endl;
            temp.cenPointACS.x = (uchar)buff[index] * (256 * 256 * 256) + (uchar)buff[index + 1] * 256 * 256 + (uchar)buff[index + 2] * 256 + (uchar)buff[index + 3];

            //temp.cenPointACS.y
            index += 4;
            temp.cenPointACS.y = (uchar)buff[index] * (256 * 256 * 256) + (uchar)buff[index + 1] * 256 * 256 + (uchar)buff[index + 2] * 256 + (uchar)buff[index + 3];

           // std::cout<<"sdk point "<<temp.cenPointACS.x<<" "<<temp.cenPointACS.y<<std::endl;
            //blocksize
            index += 4;

			//temp.cenPointACS.y
			index += 4;
			temp.cenPointACS.y = (uchar)buff[index] * (256 * 256 * 256) + (uchar)buff[index + 1] * 256 * 256 + (uchar)buff[index + 2] * 256 + (uchar)buff[index + 3];
			
            std::cout<<"point："<<temp.cenPointACS.x<<" "<<temp.cenPointACS.y<<std::endl;
			//blocksize
			index += 4;

            temp.blocksize.height = (uchar)buff[index] * (256 * 256 * 256) + (uchar)buff[index + 1] * 256 * 256 + (uchar)buff[index + 2] * 256 + (uchar)buff[index + 3];
            index+=4;
            temp.blocksize.width = (uchar)buff[index] * (256 * 256 * 256) + (uchar)buff[index + 1] * 256 * 256 + (uchar)buff[index + 2] * 256 + (uchar)buff[index + 3];

			//area
            index += 4;
			temp.area = (uchar)buff[index] * (256 * 256 * 256) + (uchar)buff[index + 1] * 256 * 256 + (uchar)buff[index + 2] * 256 + (uchar)buff[index + 3];

			//horizontalAxisLength
			index += 4;
			temp.horizontalAxisLength = (uchar)buff[index] * (256 * 256 * 256) + (uchar)buff[index + 1] * 256 * 256 + (uchar)buff[index + 2] * 256 + (uchar)buff[index + 3];

			//verticalAxisLength 
			index += 4;
			temp.verticalAxisLength = (uchar)buff[index] * (256 * 256 * 256) + (uchar)buff[index + 1] * 256 * 256 + (uchar)buff[index + 2] * 256 + (uchar)buff[index + 3];

			//Snapshoot
			index += 4;

            int rows=(uchar)buff[index] * (256 * 256 * 256) + (uchar)buff[index + 1] * 256 * 256 + (uchar)buff[index + 2] * 256 + (uchar)buff[index + 3];
            index+=4;
            int cols=(uchar)buff[index] * (256 * 256 * 256) + (uchar)buff[index + 1] * 256 * 256 + (uchar)buff[index + 2] * 256 + (uchar)buff[index + 3];
            index+=4;
            cv::Mat ori = cv::Mat(rows, cols, CV_8UC1, &buff[index]);
			//memcpy(.data, &buff[index] temp.Snapshoot.rows*temp.Snapshoot.cols);
			temp.Snapshoot = ori.clone();
            index += cols*rows;
			realtime_target.push_back(temp);
		}
}

//将算法参数转化为数组形式
int para_to_string(char *s, int &datalen)
	{
		//sp
		int a = sp.ZERO_ANGLE;
		int index = 0;
		s[index] = a / (256 * 256 * 256);;
		s[index + 1] = (a/ (256 * 256)) % 256;
		s[index + 2] = (a / 256) % 256;
		s[index + 3] = a % 256;
		
		int temp= s[index] * (256 * 256 * 256) + s[index + 1] * 256 * 256 + s[index + 2] * 256 +s[index + 3];
		//std::cout << temp << std::endl;


		//dp
		a = dp.blurkersize;
		index += 4;
		s[index] = a / (256 * 256 * 256);;
		s[index + 1] = (a / (256 * 256)) % 256;
		s[index + 2] = (a / 256) % 256;
		s[index + 3] = a % 256;
		index += 4;

		a = int(dp.blurthresh*10);
		int b = a % 10;
		a = a / 10;
		
		s[index] = a / (256 * 256 * 256);;
		s[index + 1] = (a / (256 * 256)) % 256;
		s[index + 2] = (a / 256) % 256;
		s[index + 3] = a % 256;
		s[index + 4] = b;
		index += 5;

		a = int(dp.spatialthresh * 10);
	    b = a % 10;
		a = a / 10;
		s[index] = a / (256 * 256 * 256);;
		s[index + 1] = (a / (256 * 256)) % 256;
		s[index + 2] = (a / 256) % 256;
		s[index + 3] = a % 256;
		s[index + 4] = b;
		index += 5;

		a = dp.contourSizeThresh;
		s[index] = a / (256 * 256 * 256);;
		s[index + 1] = (a / (256 * 256)) % 256;
		s[index + 2] = (a / 256) % 256;
		s[index + 3] = a % 256;
		index += 4;

		a = int(dp.targetSCRthresh* 10);
		b = a % 10;
		a = a / 10;
		s[index] = a / (256 * 256 * 256);;
		s[index + 1] = (a / (256 * 256)) % 256;
		s[index + 2] = (a / 256) % 256;
		s[index + 3] = a % 256;
		s[index + 4] = b;

		a = int(dp.hessianThresh * 10);
		b = a % 10;
		a = a / 10;
		index += 5;
		s[index] = a / (256 * 256 * 256);;
		s[index + 1] = (a / (256 * 256)) % 256;
		s[index + 2] = (a / 256) % 256;
		s[index + 3] = a % 256;
		s[index + 4] = b;

		a = dp.disThresh ;
		index += 5;
		s[index] = a / (256 * 256 * 256);;
		s[index + 1] = (a / (256 * 256)) % 256;
		s[index + 2] = (a / 256) % 256;
		s[index + 3] = a % 256;

		//tp
		a = tp.tracking_para;
		index += 4;
		s[index] = a / (256 * 256 * 256);;
		s[index + 1] = (a / (256 * 256)) % 256;
		s[index + 2] = (a / 256) % 256;
		s[index + 3] = a % 256;

		datalen = index + 4;
		return 0;
	}


int ROIPointsToChar(std::vector<std::vector<cv::Point> > _ROIPoints, char *s, int &datalen)
{
	//首先解析总数
	int index = 0;
	int numOfAllPoints = _ROIPoints.size();
	char *pINT = (char *)&numOfAllPoints;
	int _i = 0;
	for (; _i < sizeof(int); _i++)
	{
		s[index + _i] = *(pINT + _i);
	}
	index += sizeof(int);

	//依次解析点
	int _num = 0;
	for (; _num < numOfAllPoints; _num++)
	{
		//序号
        int n=0;
        pINT = (char *)&n;
		_i = 0;
		for (; _i < sizeof(int); _i++)
		{
			s[index + _i] = *(pINT + _i);
		}
		index += sizeof(int);

		//点数
        int sz = _ROIPoints[_num].size();
		pINT = (char *)&sz;
		_i = 0;
		for (; _i < sizeof(int); _i++)
		{
			s[index + _i] = *(pINT + _i);
		}
		index += sizeof(int);

		//x，y
		int _j = 0;
		for (; _j < sz; _j++)
		{
            int x = _ROIPoints[_num][_j].x;
            int y = _ROIPoints[_num][_j].y;

			//x
			pINT = (char *)&x;
			_i = 0;
			for (; _i < sizeof(int); _i++)
			{
				s[index + _i] = *(pINT + _i);
			}
			index += sizeof(int);

			//y
			pINT = (char *)&y;
			_i = 0;
			for (; _i < sizeof(int); _i++)
			{
				s[index + _i] = *(pINT + _i);
			}
			index += sizeof(int);
		}
	}//for (; _num < numOfAllPoints; _num++)

	//len
	datalen = index;
	return 0;
}


//for show_sdk
int ParseTrackingPoints(std::vector<TrackingPoint>& _TrackPoints, char *s,const int &datalen)
    {
      //std::cout<<"begin parse"<<std::endl;
      if(datalen==0)
      {
          return 1;
      }
        _TrackPoints.clear();//swap(std::vector<TrackingPoint>());
        int index = 0;

        //解析点数
        int numOfTrack = *(int *)&s[index];
        index += sizeof(int);

        std::cout<<"numOfTrack "<<numOfTrack<<std::endl;
        int j=0;
        //解析轨迹
        for (; j<numOfTrack; j++)
        {
            //std::cout<<"j "<<j<<" ";
            TrackingPoint temp;

            //parse id
            temp.id = *(int *)&s[index];
            index += sizeof(int);

            //parse num
            int numOfPoints = *(int *)&s[index];
            index += sizeof(int);

            //std::cout<<"numOfPoints "<<numOfPoints<<std::endl;
            temp.track.clear();

            //parse point
            int jOfNum = 0;
            for (; jOfNum < numOfPoints; jOfNum++)
            {
                Point p;
                //x
                p.x = *(int *)&s[index];
                index += sizeof(int);

                //std::cout<<"point x "<<p.x<<" ";
                //y
                p.y = *(int *)&s[index];
                index += sizeof(int);

                //std::cout<<"point y "<<p.y<<std::endl;
                temp.track.push_back(p);
            }
            _TrackPoints.push_back(temp);

        }

    }

