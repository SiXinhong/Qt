#include "socket.h"

#include "show_sdk.h"

extern SOCKET hSocket;
extern char sendbuffer[SEND_BUFFER_SIZE];
extern WSANETWORKEVENTS netEvents;
extern int datalen;

int para_data_len = 40;

DetectorParams dp;
TrackingParameters tp;
StitchParmeters sp;
/*
   �������ֲ���
   1.mode=0:�㷨��������ʱidĬ��Ϊ0��������
   2.mode=1:ת̨����
   3.mode=3:����ͷ����
*/
int SetAlgorithmPara();
int SetControlPara(int id);
int SetCameraPara(int id);

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

/****************************************************************���ӿ�**********************************************************************/
int SetSystemPara(int mode, int id)
{
	//����������
	if (mode != 0 && mode != 1 && mode != 2)
        return ERROR_MODE;
	if (id<MIN_ID || id>MAX_ID)
        return ERROR_Id;

	//����mode�ֱ����ò���
	switch (mode)
	{
	case 0:
		return SetAlgorithmPara();//ok
		break;
	case 1:
		return SetControlPara(id);
		break;
	case 2:
		return SetCameraPara(id);
		break;
	default:
        return ERROR_MODE;
		break;
	}

}


int GetSurveillanceData(int mode, IntegratedData  *&data)//ok
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


int GetSystemPara(int mode, int id)
{
	//������
	if (mode != 0 && mode != 1 && mode != 2)
        return ERROR_MODE;
	//��ȡ����
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


/**************************************************************�����Ӻ���************************************************************************/
int SetAlgorithmPara()
{
	//����������
	
	int result = 0;
	char *data = (char *)malloc(para_data_len+1);
	memset(data, 0, para_data_len + 1);
	int datalen = 0;
	para_to_string(data,datalen);
	result=MySend(hSocket, 0, sendbuffer, SEND_BUFFER_SIZE, data, datalen);
	free(data);
    //���string�������Ƿ���ϱ�׼
	if (result == 0){
		return SetParaSuccess;
	}
	else{
        return ERROR_SetFail;
	}
}

int SetControlPara(int id)
{
	//����������
	if (id<MIN_ID || id>MAX_ID)
        return ERROR_Id;
	
	//���string�������Ƿ���ϱ�׼
	int result=0; //= MySend(hSocket, 1, sendbuffer, SEND_BUFFER_SIZE, const_cast<char*>(para_string), strlen(para_string));
	//���string�������Ƿ���ϱ�׼
	if (result == 0){
		return SetParaSuccess;
	}
	else{
        return ERROR_SetFail;
	}
	
}

int SetCameraPara(int id)
{
	//����������
	if (id<MIN_ID || id>MAX_ID)
        return ERROR_Id;

	//���string�������Ƿ���ϱ�׼
	int result=0;// = MySend(hSocket, 2, sendbuffer, SEND_BUFFER_SIZE, const_cast<char*>(para_string), strlen(para_string));
	//std::cout << "strlen(para_string) "<<strlen(para_string) << std::endl;
	//���string�������Ƿ���ϱ�׼
	if (result == 0){
		return SetParaSuccess;
	}
	else{
        return ERROR_SetFail;
	}
}

//���£�����ʱ��
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
		data->timeinfo=(((uchar)buff[9] * 256 + (uchar)buff[10]) * 256 + (uchar)buff[11]) * 256 + (uchar)buff[12];
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
	//����������
	if (id<MIN_ID || id>MAX_ID)
        return ERROR_Id;

	int result = MySend(hSocket,6, sendbuffer, SEND_BUFFER_SIZE, 0, 0);

	return GetParaSuccess;
}

int GetCameraPara(int id)
{
	//����������
	if (id<MIN_ID || id>MAX_ID)
        return ERROR_Id;

	int result = MySend(hSocket,7, sendbuffer, SEND_BUFFER_SIZE, 0, 0);

	return GetParaSuccess;
}


/**************************************************************�����Ӻ���************************************************************************/
//������ת��Ϊ�㷨���� �����㷨����
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


//���� ������ת��ΪĿ�꼯�� 
void buff_to_target(char *buff, int datalen, vector<SmallTarget>& realtime_target)
{
    realtime_target.clear();
		int index = 0;
		while(index<datalen)
		{
						Target temp;
			temp.cenPointACS.x = (uchar)buff[index] * (256 * 256 * 256) + (uchar)buff[index + 1] * 256 * 256 + (uchar)buff[index + 2] * 256 + (uchar)buff[index + 3];
			

			//temp.cenPointACS.y
			index += 4;
			temp.cenPointACS.y = (uchar)buff[index] * (256 * 256 * 256) + (uchar)buff[index + 1] * 256 * 256 + (uchar)buff[index + 2] * 256 + (uchar)buff[index + 3];
			

			//blocksize
			index += 4;

			temp.blocksize.height = (uchar)buff[index];
			temp.blocksize.width = (uchar)buff[index + 1];

			//area
			index += 2;
			temp.area = (uchar)buff[index] * (256 * 256 * 256) + (uchar)buff[index + 1] * 256 * 256 + (uchar)buff[index + 2] * 256 + (uchar)buff[index + 3];

			//horizontalAxisLength
			index += 4;
			temp.horizontalAxisLength = (uchar)buff[index] * (256 * 256 * 256) + (uchar)buff[index + 1] * 256 * 256 + (uchar)buff[index + 2] * 256 + (uchar)buff[index + 3];

			//verticalAxisLength 
			index += 4;
			temp.verticalAxisLength = (uchar)buff[index] * (256 * 256 * 256) + (uchar)buff[index + 1] * 256 * 256 + (uchar)buff[index + 2] * 256 + (uchar)buff[index + 3];

			//Snapshoot
			index += 4;
			cv::Mat ori = cv::Mat(12, 12, CV_8UC1, &buff[index]);
			//memcpy(.data, &buff[index] temp.Snapshoot.rows*temp.Snapshoot.cols);
			temp.Snapshoot = ori.clone();
			index += 12 * 12;
			realtime_target.push_back(temp);
		}
}

//���㷨����ת��Ϊ������ʽ
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
