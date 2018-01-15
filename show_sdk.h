#ifndef _SHOW_SDK_H
#define _SHOW_SDK_H
/*
  �ļ��������Կض�ͨ�Žӿ��ļ�
  ʱ�䣺2017.6.13
  ���ߣ�zc
  ���£�2017.12.10
*/

#include <iostream>
#include <vector>
#include <fstream>
#include <opencv2/opencv.hpp>

//#include "socket.h"
//using namespace std;

using std::vector;
using cv::Point;
using cv::Size;
using cv::Mat;

#define MIN_ID 0
#define MAX_ID 10

//����ֵ�궨��
#define SetParaSuccess 0
#define GetParaSuccess 0
#define GetDataSuccess 0


    #define ERROR_MODE 1//ģʽ����ֵ������Чֵ
    #define ERROR_SringIsNull 2//����Ϊ�գ����
    #define ERROR_SetFail 3//����ʧ�ܣ�������ø�ʽ
    #define ERROR_Id 4 //id������Чֵ
    #define ERROR_GetFail 5//��ȡ����ʧ��
    #define ERROR_DataStructIsNull 6//�ۺ����ݽṹ��ָ��Ϊ��
    #define ERROR_HasNoValidFile 7//���ز����ļ���ʧ



///////////////////////////////////////ע�⣺�¼�һ��ʱ���timeInfo 
//Ŀ�����ݽṹ��
struct SmallTarget
{

    int id;// = -1;                            //                  !!
    Point cenPoint; //= Point(-1, -1);         // Ŀ����������     !!
    Point cenPointACS; //= Point(-1, -1);      // Ŀ��ľ�������
    Size blocksize ; //= Size(0, 0);            // �����С
    double Velocity ; //= 0;                    // �˶�����         !!
    double MotionDerection; // = 0;             // �˶�����         !!
    int area ; //= 0;                           // Ŀ�����          !!
    int horizontalAxisLength ; //= 0;           // ˮƽ�᳤��        !!
    int verticalAxisLength ; //= 0;             // ��ֱ�᳤��         !!
    double absoluteIntensity ; //= 0;           // ����ǿ��           !!
    double relativeIntensity; // = 0;           // ���ǿ��            !!

    std::vector<Point> contours;            // Ŀ������          !!
    Mat Snapshoot;                          // Ŀ�����
    Mat sihouette;                         // Ŀ���Ӱ          !!
    
	double timeInfo = 0.0;                  //ʱ����� �¼�
	
    double targetScale; // = 0;                 // Ŀ��߶�            !!
    double CenSueEintensity; //= 0;            // ������Χ�Աȶȵ���Ӧǿ��      !!
    double SCRValue ; //= 0;                    // Ŀ�걳�����ӱ�                 !!
    std::vector<double> theFeatures;             // 13ά��СĿ����������     !!
};

typedef SmallTarget Target;

struct TrackingPoint
{
    int id;
    vector<Point> track;
};

struct imageInfo
{
    double timeInfo;                  // ʱ���
    cv::Mat oriIMG;                   // 16bitͼ
    cv::Mat oriIMG8bit;                   // 8bitͼ
    std::vector<int> directionInfo;        // ͼ��λ��Ϣ
    std::vector<Target> targets;           // ��֡ͼ���Ŀ�꼯��

};

///////////////////////////////////////ע�⣺timeinfo ���͵��޸�
//�ۺ����ݽṹ��
struct IntegratedData
{
    double timeinfo;//�޸�ʱ��
	cv::Mat panoImage;// 
	vector< SmallTarget> targets;
    //1.12 update
    std::vector<TrackingPoint> _TrackPoints;

};

///////////////////////////////////////ע�⣺�㷨�������
//�����ṹ��

//ƴ�Ӳ���
struct StitchParmeters
{
	int ZERO_ANGLE;// = 165;//���Ƕ�
};

//StitchParmeters sp;
struct DetectorParams
{
	// �˲�������
	int filtermode = 0; // 0 - ��ֵ�˲��� 1 - ��������ֵ�˲��� 2 - ��ֵ�˲��� 3 - ������ֵ�˲��� 4 - ��������ֵ�˲�

	//  ����ϵ����ϵ��Ϊ1��ʾ������
	double ScaleDown_x = 1;
	double ScaleDown_y = 1;

	size_t blurkersize = 5;//5
	// Ŀ�걳���ָ�ģʽ
	int segMode = 1; // 0 - �����ֵ�ָ 1 - ��˹ͳ�Ʒָ�
	double blurthresh = 2;
	double spatialthresh = 2;   // û����

	int contourSizeThresh = 10;   // û����
	// Ŀ�곤����ֵ
	int targetsizeL = 3;
	int targetsizeH = 12;
	// Ŀ�곤���
	double W_H_ratio = 3;
	double H_W_ratio = 3;
	// ������Χ�Աȶ���ֵ
	double MeanDiffThresh = 3;

	double targetSCRthresh = 1;  // û����
	double hessianThresh = 10;   // û����
	int disThresh = 10;//����˲��㷨��ֵ   û����
};//СĿ�������

//DetectorParams dp;



//track����
struct TrackingParameters
{
	int tracking_para = 80;
	int PeriodDisThre = 80;   //�����ڵ��˶�������ֵ; ��������ô���£� 
	int PeriodDisThre_400To640 = 180;
	int PeriodDisThre_0To400 = 60;
	int yThre = 400;

	int RealObjCountThre = 3;
	double minSpeed = 0.12; //10/84 = 0.119

	double maxAngleChange = 90;
	int StartSpeedCheckPeriodNum = 2; //Ŀ��켣�ۼƵ���������󣬿�ʼ�����ٶ�Ԥ�����֤

	double areaRatioDownThre = 0.7;
	double areaRatiorUpThre = 1.3;

	double maxLWRatio = 1.3; //��ͬ��Ŀ���ܲ�һ��������
	double LW_ratio_diff_down = 0.7;
	double LW_ratio_diff_up = 1.3;
};

//TrackingParameters tp;


//����������
struct DetectROI
{
	int num;
	std::vector<cv::Point> mask;
};





///////////////////////////////////////ע�⣺SetSystemPara�ӿڸı�
/*
  ��������SetSystemPara
  �������ܣ����ò����ӿ�
  ��������:
          id�������豸id����ֵ��С��MIN_ID��MAX_ID֮��
		  mode:���ò�����ģʽ��0Ϊ�㷨����(��ʱidΪ0),1Ϊת̨������2Ϊ����ͷ����
   �������أ�
          1.���󣺾���������ͼ�ERROR�ж���
		  2.�ɹ�������ֵΪ0
   �÷��������㷨����ʱ�������SetSystemPara��0��;
*/
int SetSystemPara(int mode, int id = 0);



/*
  ��������GetSurveillanceData
  �������ܣ���ȡ�ۺ�����
  �������룺
          mode:��ȡ���������ͣ�0��ʾ����ͼ��1��ʾĿ������
  ���������
          data���ۺ����ݽṹ��
*/
int GetSurveillanceData(int mode, IntegratedData  *&data);


///////////////////////////////////////ע�⣺GetSystemPara�ӿڸı�
/*
  ��������GetSystemPara
  �������ܣ����ò����ӿ�
  ��������:
        id�������豸id����ֵ��С��MIN_ID��MAX_ID֮��
        mode:���ò�����ģʽ��0Ϊ�㷨����(��ʱidΪ0),1Ϊת̨������2Ϊ����ͷ����
  �������أ�
        1.���󣺾���������ͼ�ERROR�ж���
        2.�ɹ�������ֵΪ0
*/
int GetSystemPara(int mode, int id = 0);


//12.10
int GetOriPerImg(cv::Mat &oriImage);

int GetOri16Img(cv::Mat &oriImage);

int SetDuiBiDu(double alpha, double deta);

int SetORIPoints(std::vector<std::vector<cv::Point> > _ROIPoints);

int END();


int GetTrack(std::vector<TrackingPoint>& _TrackPoints);


#endif
