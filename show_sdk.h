#ifndef _SHOW_SDK_H
#define _SHOW_SDK_H
/*
  文件描述：显控端通信接口文件
  时间：2017.6.13
  作者：zc
*/

#include <iostream>
#include <vector>
#include <fstream>
#include <opencv.hpp>

//#include "socket.h"
//using namespace std;

using std::vector;
using cv::Point;
using cv::Size;
using cv::Mat;

#define MIN_ID 0
#define MAX_ID 2

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




//数据结构体

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

    double targetScale; // = 0;                 // 目标尺度            !!
    double CenSueEintensity; //= 0;            // 中央周围对比度的响应强度      !!
    double SCRValue ; //= 0;                    // 目标背景信杂比                 !!
    std::vector<double> theFeatures;             // 13维的小目标特征向量     !!
};

typedef SmallTarget Target;

struct imageInfo
{
    double timeInfo;                  // 时间戳
    cv::Mat oriIMG;                   // 16bit图
    cv::Mat oriIMG8bit;                   // 8bit图
    std::vector<int> directionInfo;        // 图像方位信息
    std::vector<Target> targets;           // 该帧图像的目标集合

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



//小目标描述结构体
//struct SmallTarget
//{

//    int id;// = -1;
//    cv::Point cenPoint;// = cv::Point(-1, -1);         // 目标中心坐标
//    cv::Size blocksize;// = cv::Size(0, 0);            // 检测框大小
//    double Velocity;// = 0;                    // 运动速率
//    double MotionDerection;// = 0;             // 运动方向
//    int area;// = 0;                           // 目标面积
//    int horizontalAxisLength;// = 0;           // 水平轴长度
//    int verticalAxisLength;// = 0;             // 竖直轴长度
//    double absoluteIntensity;// = 0;           // 绝对强度
//    double relativeIntensity;// = 0;           // 相对强度

//	vector<cv::Point> contours;                 // 目标轮廓
//	cv::Mat Snapshoot;                          // 目标快照
//	cv::Mat sihouette;                          // 目标剪影

//    double targetScale;// = 0;                 // 目标尺度
//    double CenSueEintensity;// = 0;            // 中央周围对比度的响应强度
//    double SCRValue;// = 0;                    // 目标背景信杂比
//	vector<double> theFeatures;             // 13维的小目标特征向量

//};

//综合数据结构体
struct IntegratedData
{
	Time time;
	cv::Mat panoImage;// 
	vector< SmallTarget> targets;
};



/*
  函数名：SetSystemPara
  函数功能：设置参数接口
  函数输入:
          id：输入设备id，其值大小在MIN_ID和MAX_ID之间
		  mode:设置参数的模式，0为算法参数(此时id为0),1为转台参数，2为摄像头参数
		  para_string：以空格为分隔符的参数指令，例如“1 2 3”表示参数值分别为1，2 ，3
   函数返回：
          1.错误：具体错误类型见ERROR中定义
		  2.成功：返回值为0
*/
int SetSystemPara(int mode, const char *para_string, int id = 0);



/*
  函数名：GetSurveillanceData
  函数功能：获取综合数据
  函数输入：
          mode:获取的数据类型，0表示周视图，1表示目标特征
  函数输出：
          data：综合数据结构体
*/
int GetSurveillanceData(int mode, IntegratedData  *&data);



/*
  函数名：GetSystemPara
  函数功能：设置参数接口
  函数输入:
        id：输入设备id，其值大小在MIN_ID和MAX_ID之间
        mode:设置参数的模式，0为算法参数(此时id为0),1为转台参数，2为摄像头参数
        para_string：以空格为分隔符的参数指令，例如“1 2 3”表示参数值分别为1，2 ，3
  函数返回：
        1.错误：具体错误类型见ERROR中定义
        2.成功：返回值为0
*/
int GetSystemPara(int mode, char *&para_string, int id = 0);


#endif
