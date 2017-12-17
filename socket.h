#ifndef _SOCKET_H
#define _SOCKET_H

//#define socket_debug
#include <winsock2.h>
#include <opencv2/opencv.hpp>

#pragma comment(lib, "ws2_32.lib")

#define SEND_BUFFER_SIZE 1024
#define RECV_BUFFER_SIZE 2048
#define DATA_BUFFER_SIZE 40*1024*1024

//������������ɾ��ǰ��̶����ȵ����ݣ������������������ǰ��
void AdjustBuffer(char data[], int *pdatalen, int number);
/****************************************************************************************************/
//ͨ���������ַ���ȷ��Ҫɾ�����ֽ���
int FindSubStringIndex(char data[], int length, char substring[], int substringlength);
//ͨ������֡β, У�������Ƿ���ȷ
int CheckData(char data[], int length, char substring[], int substringlength);
/****************************************************************************************************/
//������Ϣ���
void ErrorHandling(char *pdata);

//��־��Ϣ���
void LogRecording(char *pdata);

int HasOneFrame(char buf[], int* pbuflen);
//������������еõ���һ֡���ݵĳ���
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
