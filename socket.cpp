#include "socket.h"

/****************************定义的全局变量***************************************/
extern SOCKET hSocket;			//事件对象连接的套接字
 extern WSAEVENT hEvent;			//套接字相连的事件对象	
//int datalen;			//定义一个整数，表示从当前传输的数据中得到的数据长度
extern char sendbuffer[SEND_BUFFER_SIZE];				//定义的一个socket的发送缓冲区
//char recvbuffer[RECV_BUFFER_SIZE];				//定义的一个socket的接收缓冲区		
//char* databuffer = (char *)malloc(DATA_BUFFER_SIZE);//存放数据的静态缓冲区
//
#define DATA_LENGTH_MAX     10*1024*1024
#define DATA_LENGTH_MIN     9

//char sendbuffer[SEND_BUFFER_SIZE];				//定义的一个socket的发送缓冲区
//char recvbuffer[RECV_BUFFER_SIZE];				//定义的一个socket的接收缓冲区		

//////////////////////////////////////////////////////////////////////////////////////////////////////
/*作用：调整缓冲区，删除前面固定长度的数据，并将后面的数据依次前移
*输入参数：data[]：	原始数据
*		    pdatalen:	原始数据的长度
*		    number:		要删除的数据个数
*返回值： 无
*/
void AdjustBuffer(char data[], int *pdatalen, int number){
	int i = 0;
	int total = *pdatalen;

	for (i = number; i < total; i++){
		data[i - number] = data[i];
	}
	*pdatalen = total - number;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////
/*作用：通过查找子字符串确定要删除的字节数
*输入参数：data[]：		原始数据
*			length:			原始数据的长度
*			substring[]:	子字符串
*			substringlength:子字符串的长度
*返回值：	返回值为要删除的字节数
*/
int FindSubStringIndex(char data[], int length, char substring[], int substringlength)
{
	int i = 0;
	int j = 0;

	if (length < substringlength){
		//原始数据长度小于子字符串长度，所以返回0
		return 0;
	}

	for (i = 0; i < length - substringlength; ++i){
		for (j = 0; j < substringlength; j++){
			if (data[i + j] != substring[j]){
				break;
			}
		}

		if (j == substringlength){
			return i + substringlength;
		}
	}
	return i + substringlength;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////
/*作用：通过数据帧尾,校验数据是否正确
*输入参数：data[]：		原始数据
*			length:			原始数据长度
*			substring[]:	子字符串
*			substringlength:子字符串的长度
*返回值：校验通过返回1，
*		  校验未通过返回0
*/
int CheckData(char data[], int length, char substring[], int substringlength)
{
	int j = 1;
	for (j = 1; j <= substringlength; ++j){
		if (data[length - j] != substring[substringlength - j]){
			return 0;
		}
	}
	if (j == substringlength + 1){
		return 1;
	}
	return 0;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////
//错误消息输出
void ErrorHandling(char *pdata)
{
    //fputs(pdata, stderr);
    std::cout<<pdata<<std::endl;
}
/*****************************************************************************************************/
//日志消息输出
void LogRecording(char *pdata)
{
    //fputs(pdata, stdout);
     std::cout<<pdata<<std::endl;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////
/*作用：得出缓冲区中是否有一帧数据
*输入参数：data[]：		接收缓冲区
*			pdatalen:		接收缓冲区中的数据长度
*
*返回值： 0：表示已提取出正确的长度信息，但是数据未接收全
*		  -1：表示数据长度不够，无法提取出长度信息
*        -2：表示数据的长度信息提取有误，不在一个范围内
*        正数：表示一帧数据的长度
*/
int HasOneFrame(char data[], int* pdatalen){

	int data_len = *pdatalen;	//缓冲区中数据长度
	int frame_len = 0;			//一帧数据的长度

	if (data_len < 4){
		return  -1;
	}
	else{
		frame_len = CountDataLength(data);
		if (frame_len >= DATA_LENGTH_MIN && frame_len <= DATA_LENGTH_MAX){
			if (frame_len <= data_len){
				return frame_len;
			}
			else{
				return 0;
			}
		}
		else{
			return -2;
		}
	}
}

/*作用：得出一帧数据的长度
*输入参数：data[]：	每个Socket套接字专有的socket接收缓冲区
*返回值：返回结果是一帧数据的长度
*/
int CountDataLength(char data[]){
	int result;
	result = (((unsigned char)data[0] * 256 + (unsigned char)data[1]) * 256 + (unsigned char)data[2]) * 256 + (unsigned char)data[3];
	return result;
}

cv::Mat GetImageFromBuffer(char *data, int rows, int cols)
{
    cv::Mat c = cv::Mat(rows, cols, CV_8UC1, data).clone();
	return c;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int MySocketInitial(void){
	WSADATA wsaData;
	SOCKADDR_IN servAdr;
	char server_ip[16];

	char server_port[6];

	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0){
		return 1;
	}

	hSocket = socket(PF_INET, SOCK_STREAM, 0);		//创建流socket
	if (hSocket == INVALID_SOCKET){
		return 2;
	}

//	std::cout << "输入服务器端IP地址" << std::endl;
//	fgets(server_ip, sizeof(server_ip), stdin);

//	std::cout << "输入端口号" << std::endl;
//	fgets(server_port, sizeof(server_port), stdin);

	memset(&servAdr, 0, sizeof(servAdr));
	servAdr.sin_family = AF_INET;
    servAdr.sin_addr.s_addr = inet_addr("192.168.1.1");
    servAdr.sin_port = htons(atoi("8080"));


	if (connect(hSocket, (SOCKADDR*)&servAdr, sizeof(servAdr)) == SOCKET_ERROR){	//将套接字绑定到服务器的网络地址上
		return 3;
	}

    int iMode = 1;
    ioctlsocket(hSocket, FIONBIO, (u_long FAR*) &iMode);
	hEvent = WSACreateEvent();			//创建事件对象
	if (hEvent == WSA_INVALID_EVENT){
		return 4;
	}

	if (WSAEventSelect(hSocket, hEvent, FD_READ | FD_CLOSE) == SOCKET_ERROR){		//监视的事件类型为是否有新的连接请求
		return 5;
	}
	return 0;
}
/*作用：将数据通过网络发送到对应端口
*输入参数：s:				套接字
*			mode：			模式
*			buf[]：			socket发送缓冲区
*			buflen:			socket发送缓冲区的大小
*			data[]：		需发送的数据
*			datalen:		需发送的数据长度
*返回值：  0：				代表成功发送
*			正数：		发送失败，其值为对应错误码
*/
int MySend(SOCKET s, char mode, char buf[], int buflen, char data[], int datalen){
	int wt_cnt = 0;			//每次调用send函数的返回值
	int total_len = 0;		//总共要发送的数据长度
	int str_len = 0;		//剩余要发送的数据长度
	int buf_len = buflen;	//发送缓冲区的数据长度
	int data_len = datalen;	//要发送的数据的长度

	memset(buf, 0, buf_len);
	total_len = data_len + 9;

	//四位数据长度
	buf[0] = total_len / (256 * 256 * 256);
	buf[1] = (total_len / (256 * 256)) % 256;
	buf[2] = (total_len / 256) % 256;
	buf[3] = total_len%256;

	//一位模式
	buf[4] = mode;

	if (data_len > 0){
		for (int i = 0; i < data_len; i++){
			buf[i + 5] = data[i];
		}
	}

	//四位数据结尾
	buf[total_len - 4] = '#';
	buf[total_len - 3] = '#';
	buf[total_len - 2] = '#';
	buf[total_len - 1] = '#';

	str_len = total_len;

	while (str_len>0)
	{
		wt_cnt = send(s, buf, str_len, 0);
		if (wt_cnt >= 0){
			str_len = str_len - wt_cnt;
		}
		else{
			int error_result = 0;
			error_result = WSAGetLastError();
			if (error_result == WSAEWOULDBLOCK){
				error_result = 0;
				continue;
			}
			return error_result;
		}
	}
	return 0;
}


/*作用：将数据通过网络发送到对应端口
*输入参数：s:				套接字
*			buf[]：			socket接收缓冲区
*			buflen:			socket接收缓冲区的大小
*返回值：	recv函数的返回值
*/

int MyRecv(SOCKET s, char buf[], int buflen){
	int result = 0;
	result = recv(s, buf, buflen, 0);
	return result;
}

/*作用：将数据通过网络发送到对应端口
*输入参数：	s:			套接字
*				event：		套接字相连的事件对象
*返回值：		0：			固定值
*/
int MySocketClose(SOCKET s, WSAEVENT event){
	WSACloseEvent(event);
	closesocket(s);
	return 0;
}

/*作用：对缓冲区中的数据进行解析
*输入参数：buf[]：			Socket套接字专有的socket接收缓冲区
*			pbuflen:		指向Socket套接字专有的socket接收缓冲区中的数据长度
*			pdatalen:		指向一帧信息的长度
*返回值： 0：表示已提取出正确的长度信息，但是数据未接收全，需要继续接收
*         1：需要继续解析数据
*/
int DataAnalyze(char data[], int* pdatalen){
	int data_len = *pdatalen;	//datalen为缓冲区中数据的长度
	int frame_len = 0;	//pframelen为一帧完整的数据对应的长度

	//判断数据缓冲区中是否有一帧校验通过的信息
	frame_len = HasOneFrame(data, pdatalen);
	if (frame_len == 0){
		//表示已提取出正确的长度信息，但是数据未接收全
		return 0;
	}
	else if (frame_len == -1){
		//表示数据长度不够，无法提取出长度信息
		return 0;
	}
	else if (frame_len == -2){
		//表示数据的长度信息提取有误，不在一个范围内,所以数据开头就错了，需调整缓冲区
		int index = 0;
		index = FindSubStringIndex(data, data_len, "####", 4);
		AdjustBuffer(data, pdatalen, index);						//调整接收缓冲区，将缓冲区中前面无用的数据删除，同时后面的数据前移
		return 1;
	}
	else{
		//得出了一帧的数据长度
		if (CheckData(data, frame_len, "####", 4) == TRUE){
        //std::cout << "数据校验通过" << std::endl;
            if (data[4] == 3){
                //std::cout << "收到一帧数据" << std::endl;
				//int rows_length = (((uchar)data[13] * 256 + (uchar)data[14]) * 256 + (uchar)data[15]) * 256 + (uchar)data[16];
				//int cols_length = (((uchar)data[17] * 256 + (uchar)data[18]) * 256 + (uchar)data[19]) * 256 + (uchar)data[20];
				//cv::Mat or = GetImageFromBuffer(&data[21], rows_length, cols_length);
                //imshow("pic", or);
				//cv::waitKey(10000);
				//cv::destroyWindow("pic");
				return 2;
				
			}
            else if(data[4]==4)
            {
                return 2;
            }
			else{
				std::cout << "其他指令" << std::endl;
				AdjustBuffer(data, pdatalen, frame_len);						//调整接收缓冲区，将缓冲区中前面无用的数据删除，同时后面的数据前移
				return 3;
			}
			//AdjustBuffer(data, pdatalen, frame_len);						//调整接收缓冲区，将缓冲区中前面无用的数据删除，同时后面的数据前移
			return 2;
		}
		else{
            //std::cout << "数据未校验通过" << std::endl;
			int index = 0;
			index = FindSubStringIndex(data, data_len, "####", 4);
			AdjustBuffer(data, pdatalen, index);						//调整接收缓冲区，将缓冲区中前面无用的数据删除，同时后面的数据前移
		}
		return 1;
	}
}


/*作用：读取网络数据
*输入参数：s:				套接字
*			netEvents		套接字对应的事件类型
*			buf[]：			接收缓冲区
*			pbuflen:		接收缓冲区中的数据长度
*			data：			用于存储一帧数据的缓冲区
*			pdatalen:		指向一帧信息的长度
*返回值： 0：遇到错误，需要断开连接
*         1：正确处理
*/
int ReadHanding(SOCKET s, WSANETWORKEVENTS netEvents, char buf[], int buflen, char data[], int *pdatalen){
	int str_len = 0;				//调用MyRecv()后的返回值
	int buf_len = buflen;			//接收缓冲区中的数据长度
	int data_len = *pdatalen;		//缓冲区中的数据长度

	while (1){
		memset(buf, 0, buf_len);
#ifdef socket_debug
        std::cout<<" myreceve before"<<std::endl;
#endif
		str_len = MyRecv(s, buf, buf_len);
//#ifdef socket_debug
//        std::cout<<" myreceve after"<<std::endl;
//        std::cout<<data_len<<std::endl;
//#endif
		if (str_len > 0){
			for (int j = 0; j < str_len; ++j){
				data[data_len] = buf[j];
				++data_len;
			}
			*pdatalen = data_len;
#ifdef socket_debug
        std::cout<<" myreceve after"<<std::endl;
        std::cout<<data_len<<std::endl;
#endif
		}
		else if (str_len == 0){
			//std::cout << "22222" << std::endl;
			return 0;
		}
		else{
			//发生错误，需要对错误代码分析
			if (WSAGetLastError() == 10035){
				continue;
			}
			if (errno == EAGAIN){
				//表示当前缓冲区已无数据可读
				;
			}
			else{
				//std::cout << "3333" << std::endl;
				//其他原因
				return 0;
			}
		}

		if (DataAnalyze(data, pdatalen) == 2){
			break;
		}

	}

	return 1;
}

/*作用：断开网络连接
*输入参数：	s:				套接字
*			hEvent：		套接字对应的事件对象
*			netEvents		事件对象对应的事件类型
*返回值：	0：				固定返回值
*/
int CloseHanding(SOCKET s, WSAEVENT hEvent, WSANETWORKEVENTS netEvents){
	//FD_CLOSE事件的处理
	if (netEvents.iErrorCode[FD_CLOSE_BIT] != 0)  //如果发生FD_CLOSE相关错误，则在iErrorCode[FD_CLOSE_BIT]中保存除0以外的其他值
	{
		ErrorHandling("关闭事件对象时出错：发生FD_CLOSE相关错误");
	}

	WSACloseEvent(hEvent);
	closesocket(s);
	return 0;
}

