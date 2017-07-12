#include "socket.h"

#include "show_sdk.h"

extern SOCKET hSocket;
extern char sendbuffer[SEND_BUFFER_SIZE];
extern WSANETWORKEVENTS netEvents;
extern int datalen;
/*
   �������ֲ���
   1.mode=0:�㷨��������ʱidĬ��Ϊ0��������
   2.mode=1:ת̨����
   3.mode=3:����ͷ����
*/
int SetAlgorithmPara(const char *para_string);
int SetControlPara(int id, const char *para_string);
int SetCameraPara(int id, const char *para_string);

int  Getpanorama(IntegratedData *&data);
int  GetObjectFeature(IntegratedData *&data);

int GetAlgorithmPara(char *&para_string);
int GetControlPara(int id,char *&para_string);
int GetCameraPara(int id, char *&para_string);

void buff_to_target(char *buff, int datalen, vector<SmallTarget>& realtime_target)
{
    realtime_target.clear();
    int index = 0;
    while(index<datalen)
    {
        SmallTarget temp;
        temp.cenPointACS.x = buff[index] * (256 * 256 * 256) + buff[index + 1] * 256 * 256 + buff[index + 2] * 256 + buff[index + 3];


        //temp.cenPointACS.y
        index += 4;
        temp.cenPointACS.y = buff[index] * (256 * 256 * 256) + buff[index + 1] * 256 * 256 + buff[index + 2] * 256 + buff[index + 3];


        //blocksize
        index += 4;

        temp.blocksize.height = buff[index];
        temp.blocksize.width = buff[index + 1];

        //Snapshoot
        index += 2;
        cv::Mat ori = cv::Mat(12, 12, CV_8UC1, &buff[index]);
        //memcpy(.data, &buff[index] temp.Snapshoot.rows*temp.Snapshoot.cols);
        temp.Snapshoot = ori.clone();
        index += 12 * 12;
        realtime_target.push_back(temp);
    }
}

int SetSystemPara(int mode, const char *para_string, int id)
{
	//����������
	if (para_string == NULL)
        return ERROR_SringIsNull;
	if (mode != 0 && mode != 1 && mode != 2)
        return ERROR_MODE;
	if (id<MIN_ID || id>MAX_ID)
        return ERROR_Id;

	//����mode�ֱ����ò���
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
        return ERROR_MODE;
		break;
	}

}


int GetSurveillanceData(int mode, IntegratedData  *&data)
{
	//�������
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


int GetSystemPara(int mode, char *&para_string, int id)
{
	//������
	if (mode != 0 && mode != 1 && mode != 2)
        return ERROR_MODE;
	//��ȡ����
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
        return ERROR_MODE;
		break;
	}

}


/**************************************************************�����Ӻ���************************************************************************/
int SetAlgorithmPara(const char *para_string)
{
	//����������
	if (para_string == NULL)
        return ERROR_SringIsNull;
	int result = 0;
	result=MySend(hSocket, 0, sendbuffer, SEND_BUFFER_SIZE, const_cast<char*>(para_string), strlen(para_string));
    //���string�������Ƿ���ϱ�׼
	if (result == 0){
		return SetParaSuccess;
	}
	else{
        return ERROR_SetFail;
	}
}

int SetControlPara(int id, const char *para_string)
{
	//����������
	if (id<MIN_ID || id>MAX_ID)
        return ERROR_Id;
	
	if (para_string == NULL)
        return ERROR_SringIsNull;
	//���string�������Ƿ���ϱ�׼
	int result = MySend(hSocket, 1, sendbuffer, SEND_BUFFER_SIZE, const_cast<char*>(para_string), strlen(para_string));
	//���string�������Ƿ���ϱ�׼
	if (result == 0){
		return SetParaSuccess;
	}
	else{
        return ERROR_SetFail;
	}
	
}

int SetCameraPara(int id, const char *para_string)
{
	//����������
	if (id<MIN_ID || id>MAX_ID)
        return ERROR_Id;

	if (para_string == NULL)
        return ERROR_SringIsNull;
	//���string�������Ƿ���ϱ�׼
	int result = MySend(hSocket, 2, sendbuffer, SEND_BUFFER_SIZE, const_cast<char*>(para_string), strlen(para_string));
	std::cout << "strlen(para_string) "<<strlen(para_string) << std::endl;
	//���string�������Ƿ���ϱ�׼
	if (result == 0){
		return SetParaSuccess;
	}
	else{
        return ERROR_SetFail;
	}
}


int  Getpanorama(IntegratedData *&data)
{
	if (data == NULL)
        return ERROR_DataStructIsNull;

	char *buff = (char *)malloc(DATA_BUFFER_SIZE);
   // std::cout<<"before mysend "<<std::endl;
	int result = MySend(hSocket, 3, sendbuffer, SEND_BUFFER_SIZE, 0, 0);
    //std::cout<<"after mysend "<<std::endl;
    //return 0;
#if 1
    datalen=0;
    if (ReadHanding(hSocket, netEvents, sendbuffer, SEND_BUFFER_SIZE, buff, &datalen) == 1)
    {
        int rows_length = (((uchar)buff[13] * 256 + (uchar)buff[14]) * 256 + (uchar)buff[15]) * 256 + (uchar)buff[16];
        int cols_length = (((uchar)buff[17] * 256 + (uchar)buff[18]) * 256 + (uchar)buff[19]) * 256 + (uchar)buff[20];
        cv::Mat c= cv::Mat(rows_length,cols_length, CV_8UC1, &buff[21]).clone();
        data->panoImage = c;
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
#endif
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
	//data->time.day = p[i++];
	//data->time.hour = p[i++];
	//data->time.minute = p[i++];
	//data->time.seconds = p[i++];
	//cv::Mat pano = cv::imread("image\\pano.bmp");
	//if (pano.empty())
	//	return SYSTEM_ERROR::ERROR_GetFail;
	//data->panoImage = pano;
	
	
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


	////Ŀ������
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


int GetAlgorithmPara(char *&para_string)
{
	int result = MySend(hSocket, 5, sendbuffer, SEND_BUFFER_SIZE, 0, 0);

	return GetParaSuccess;
}

int GetControlPara(int id,char *&para_string)
{
	//����������
	if (id<MIN_ID || id>MAX_ID)
        return ERROR_Id;

	int result = MySend(hSocket,6, sendbuffer, SEND_BUFFER_SIZE, 0, 0);

	return GetParaSuccess;
}

int GetCameraPara(int id,char *&para_string)
{
	//����������
	if (id<MIN_ID || id>MAX_ID)
        return ERROR_Id;

	int result = MySend(hSocket,7, sendbuffer, SEND_BUFFER_SIZE, 0, 0);

	return GetParaSuccess;
}
