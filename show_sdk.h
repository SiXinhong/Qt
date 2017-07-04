#ifndef _SHOW_SDK_H
#define _SHOW_SDK_H
/*
  �ļ��������Կض�ͨ�Žӿ��ļ�
  ʱ�䣺2017.6.13
  ���ߣ�zc
*/

#include <iostream>
#include <vector>
#include <fstream>
#include <opencv.hpp>


#include <QDataStream>
using namespace std;

#define MIN_ID 0
#define MAX_ID 2

//����ֵ�궨��
#define SetParaSuccess 0
#define GetParaSuccess 0
#define GetDataSuccess 0

enum SYSTEM_ERROR
{
    ERROR_MODE,// = 1,//ģʽ����ֵ������Чֵ
	ERROR_SringIsNull,//����Ϊ�գ����
	ERROR_SetFail,//����ʧ�ܣ�������ø�ʽ
	ERROR_Id,//id������Чֵ
	ERROR_GetFail,//��ȡ����ʧ��
	ERROR_DataStructIsNull,//�ۺ����ݽṹ��ָ��Ϊ��
	ERROR_HasNoValidFile//���ز����ļ���ʧ
};


//���ݽṹ��
struct ImagePro
{
	int height;
	int width;
	int data_type_bit;
	int channel;
};

//ͼ��ɼ�buffer
struct ImageBuffer
{
    vector< vector < cv::Mat > > collectd_image;
	int processing_buffer_id;
	ImagePro image_pro;//ÿһ֡ͼ�������
	int num_of_buffer_pic;//ÿ��buffer��ŵ����֡��
};

struct Time
{
	int year;
	int month;
	int day;
	int hour;
	int minute;
	int seconds;
	int millisecond;
};

//СĿ�������ṹ��
struct SmallTarget
{

    int id;// = -1;
    cv::Point cenPoint;// = cv::Point(-1, -1);         // Ŀ����������
    cv::Size blocksize;// = cv::Size(0, 0);            // �����С
    double Velocity;// = 0;                    // �˶�����
    double MotionDerection;// = 0;             // �˶�����
    int area;// = 0;                           // Ŀ�����
    int horizontalAxisLength;// = 0;           // ˮƽ�᳤��
    int verticalAxisLength;// = 0;             // ��ֱ�᳤��
    double absoluteIntensity;// = 0;           // ����ǿ��
    double relativeIntensity;// = 0;           // ���ǿ��

	vector<cv::Point> contours;                 // Ŀ������
	cv::Mat Snapshoot;                          // Ŀ�����
	cv::Mat sihouette;                          // Ŀ���Ӱ

    double targetScale;// = 0;                 // Ŀ��߶�
    double CenSueEintensity;// = 0;            // ������Χ�Աȶȵ���Ӧǿ��
    double SCRValue;// = 0;                    // Ŀ�걳�����ӱ�
	vector<double> theFeatures;             // 13ά��СĿ����������

};

//�ۺ����ݽṹ��
struct IntegratedData
{
	Time time;
	cv::Mat panoImage;// 
	vector< SmallTarget> targets;
};



/*
  ��������SetSystemPara
  �������ܣ����ò����ӿ�
  ��������:
          id�������豸id����ֵ��С��MIN_ID��MAX_ID֮��
		  mode:���ò�����ģʽ��0Ϊ�㷨����(��ʱidΪ0),1Ϊת̨������2Ϊ����ͷ����
		  para_string���Կո�Ϊ�ָ����Ĳ���ָ����硰1 2 3����ʾ����ֵ�ֱ�Ϊ1��2 ��3
   �������أ�
          1.���󣺾���������ͼ�ERROR�ж���
		  2.�ɹ�������ֵΪ0
*/
int SetSystemPara(int mode, const char *para_string, int id = 0);



/*
  ��������GetSurveillanceData
  �������ܣ���ȡ�ۺ�����
  �������룺
          mode:��ȡ���������ͣ�0��ʾ����ͼ��1��ʾĿ������
  ���������
          data���ۺ����ݽṹ��
*/
int GetSurveillanceData(int mode, IntegratedData  *&data);



/*
  ��������GetSystemPara
  �������ܣ����ò����ӿ�
  ��������:
        id�������豸id����ֵ��С��MIN_ID��MAX_ID֮��
        mode:���ò�����ģʽ��0Ϊ�㷨����(��ʱidΪ0),1Ϊת̨������2Ϊ����ͷ����
        para_string���Կո�Ϊ�ָ����Ĳ���ָ����硰1 2 3����ʾ����ֵ�ֱ�Ϊ1��2 ��3
  �������أ�
        1.���󣺾���������ͼ�ERROR�ж���
        2.�ɹ�������ֵΪ0
*/
int GetSystemPara(int mode, char *&para_string, int id = 0);


#endif
