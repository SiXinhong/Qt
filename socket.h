#ifndef _SOCKET_H
#define _SOCKET_H

//#define socket_debug
#include <winsock2.h>
#include <opencv2/opencv.hpp>

#pragma comment(lib, "ws2_32.lib")

#define SEND_BUFFER_SIZE 2048
#define RECV_BUFFER_SIZE 2048
#define DATA_BUFFER_SIZE 40*1024*1024

//调整缓冲区，删除前面固定长度的数据，并将后面的数据依次前移
void AdjustBuffer(char data[], int *pdatalen, int number);
/****************************************************************************************************/
//通过查找子字符串确定要删除的字节数
int FindSubStringIndex(char data[], int length, char substring[], int substringlength);
//通过数据帧尾, 校验数据是否正确
int CheckData(char data[], int length, char substring[], int substringlength);
/****************************************************************************************************/
//错误消息输出
void ErrorHandling(char *pdata);

//日志消息输出
void LogRecording(char *pdata);

int HasOneFrame(char buf[], int* pbuflen);
//计算从数据中中得到的一帧数据的长度
int CountDataLength(char data[]);

cv::Mat GetImageFromBuffer(char *data, int rows, int cols);

int MySocketInitial(void);
int MySend(SOCKET s, char mode, char buf[], int buflen, char data[], int datalen);
int MyRecv(SOCKET s, char buf[], int buflen);
int MySocketClose(SOCKET s, WSAEVENT event);
int DataAnalyze(char buf[], int* pbuflen);
int ReadHanding(SOCKET s, WSANETWORKEVENTS netEvents, char buf[], int buflen, char data[], int *pdatalen);
int CloseHanding(SOCKET s, WSAEVENT hEvent, WSANETWORKEVENTS netEvents);

#endif
