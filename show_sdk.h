#ifndef _SHOW_SDK_H
#define _SHOW_SDK_H
/*
  文件描述：显控端通信接口文件
  时间：2017.6.13
  作者：zc
  更新：2017.12.10
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

//返回值宏定义
#define SetParaSuccess 0
#define GetParaSuccess 0
#define GetDataSuccess 0


    #define ERROR_MODE 1//模式设置值不是有效值
    #define ERROR_SringIsNull 2//参数为空，检查
    #define ERROR_SetFail 3//设置失败，检查设置格式
    #define ERROR_Id 4 //id不是有效值
    #define ERROR_GetFail 5//获取数据失败
    #define ERROR_DataStructIsNull 6//综合数据结构体指针为空
    #define ERROR_HasNoValidFile 7//本地测试文件丢失



///////////////////////////////////////注意：新加一个时间戳timeInfo 
//目标数据结构体
struct SmallTarget
{

    int id;// = -1;                            //                  !!
    Point cenPoint; //= Point(-1, -1);         // 目标中心坐标     !!
    Point cenPointACS; //= Point(-1, -1);      // 目标的绝对坐标
    Size blocksize ; //= Size(0, 0);            // 检测框大小
    double Velocity ; //= 0;                    // 运动速率         !!
    double MotionDerection; // = 0;             // 运动方向         !!
    int area ; //= 0;                           // 目标面积          !!
    int horizontalAxisLength ; //= 0;           // 水平轴长度        !!
    int verticalAxisLength ; //= 0;             // 竖直轴长度         !!
    double absoluteIntensity ; //= 0;           // 绝对强度           !!
    double relativeIntensity; // = 0;           // 相对强度            !!

    std::vector<Point> contours;            // 目标轮廓          !!
    Mat Snapshoot;                          // 目标快照
    Mat sihouette;                         // 目标剪影          !!
    
	double timeInfo = 0.0;                  //时间戳√ 新加
	
    double targetScale; // = 0;                 // 目标尺度            !!
    double CenSueEintensity; //= 0;            // 中央周围对比度的响应强度      !!
    double SCRValue ; //= 0;                    // 目标背景信杂比                 !!
    std::vector<double> theFeatures;             // 13维的小目标特征向量     !!
};

typedef SmallTarget Target;

struct TrackingPoint
{
    int id;
    vector<Point> track;
};

struct imageInfo
{
    double timeInfo;                  // 时间戳
    cv::Mat oriIMG;                   // 16bit图
    cv::Mat oriIMG8bit;                   // 8bit图
    std::vector<int> directionInfo;        // 图像方位信息
    std::vector<Target> targets;           // 该帧图像的目标集合

};

///////////////////////////////////////注意：timeinfo 类型的修改
//综合数据结构体
struct IntegratedData
{
    double timeinfo;//修改时间
	cv::Mat panoImage;// 
	vector< SmallTarget> targets;
    //1.12 update
    std::vector<TrackingPoint> _TrackPoints;

};

///////////////////////////////////////注意：算法参数添加
//参数结构体

//拼接参数
struct StitchParmeters
{
	int ZERO_ANGLE;// = 165;//零点角度
};

//StitchParmeters sp;
struct DetectorParams
{
	// 滤波方法啊
	int filtermode = 0; // 0 - 中值滤波； 1 - 保护带中值滤波； 2 - 均值滤波； 3 - 快速中值滤波； 4 - 保护带均值滤波

	//  缩放系数，系数为1表示不动，
	double ScaleDown_x = 1;
	double ScaleDown_y = 1;

	size_t blurkersize = 5;//5
	// 目标背景分割模式
	int segMode = 1; // 0 - 大津阈值分割； 1 - 高斯统计分割
	double blurthresh = 2;
	double spatialthresh = 2;   // 没用上

	int contourSizeThresh = 10;   // 没用上
	// 目标长宽阈值
	int targetsizeL = 3;
	int targetsizeH = 12;
	// 目标长宽比
	double W_H_ratio = 3;
	double H_W_ratio = 3;
	// 中央周围对比度阈值
	double MeanDiffThresh = 3;

	double targetSCRthresh = 1;  // 没用上
	double hessianThresh = 10;   // 没用上
	int disThresh = 10;//检测滤波算法阈值   没用上
};//小目标检测参数

//DetectorParams dp;



//track参数
struct TrackingParameters
{
	int tracking_para = 80;
	int PeriodDisThre = 80;   //跨周期的运动距离阈值; 程序中怎么更新？ 
	int PeriodDisThre_400To640 = 180;
	int PeriodDisThre_0To400 = 60;
	int yThre = 400;

	int RealObjCountThre = 3;
	double minSpeed = 0.12; //10/84 = 0.119

	double maxAngleChange = 90;
	int StartSpeedCheckPeriodNum = 2; //目标轨迹累计到这个数量后，开始进行速度预测的验证

	double areaRatioDownThre = 0.7;
	double areaRatiorUpThre = 1.3;

	double maxLWRatio = 1.3; //不同项目可能不一样。。。
	double LW_ratio_diff_down = 0.7;
	double LW_ratio_diff_up = 1.3;
};

//TrackingParameters tp;


//界面轮廓点
struct DetectROI
{
	int num;
	std::vector<cv::Point> mask;
};





///////////////////////////////////////注意：SetSystemPara接口改变
/*
  函数名：SetSystemPara
  函数功能：设置参数接口
  函数输入:
          id：输入设备id，其值大小在MIN_ID和MAX_ID之间
		  mode:设置参数的模式，0为算法参数(此时id为0),1为转台参数，2为摄像头参数
   函数返回：
          1.错误：具体错误类型见ERROR中定义
		  2.成功：返回值为0
   用法：设置算法参数时调用语句SetSystemPara（0）;
*/
int SetSystemPara(int mode, int id = 0);



/*
  函数名：GetSurveillanceData
  函数功能：获取综合数据
  函数输入：
          mode:获取的数据类型，0表示周视图，1表示目标特征
  函数输出：
          data：综合数据结构体
*/
int GetSurveillanceData(int mode, IntegratedData  *&data);


///////////////////////////////////////注意：GetSystemPara接口改变
/*
  函数名：GetSystemPara
  函数功能：设置参数接口
  函数输入:
        id：输入设备id，其值大小在MIN_ID和MAX_ID之间
        mode:设置参数的模式，0为算法参数(此时id为0),1为转台参数，2为摄像头参数
  函数返回：
        1.错误：具体错误类型见ERROR中定义
        2.成功：返回值为0
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
