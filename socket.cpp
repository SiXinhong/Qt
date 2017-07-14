#include "socket.h"

/****************************�����ȫ�ֱ���***************************************/
extern SOCKET hSocket;			//�¼��������ӵ��׽���
 extern WSAEVENT hEvent;			//�׽����������¼�����	
//int datalen;			//����һ����������ʾ�ӵ�ǰ����������еõ������ݳ���
extern char sendbuffer[SEND_BUFFER_SIZE];				//�����һ��socket�ķ��ͻ�����
//char recvbuffer[RECV_BUFFER_SIZE];				//�����һ��socket�Ľ��ջ�����		
//char* databuffer = (char *)malloc(DATA_BUFFER_SIZE);//������ݵľ�̬������
//
#define DATA_LENGTH_MAX     10*1024*1024
#define DATA_LENGTH_MIN     9

//char sendbuffer[SEND_BUFFER_SIZE];				//�����һ��socket�ķ��ͻ�����
//char recvbuffer[RECV_BUFFER_SIZE];				//�����һ��socket�Ľ��ջ�����		

//////////////////////////////////////////////////////////////////////////////////////////////////////
/*���ã�������������ɾ��ǰ��̶����ȵ����ݣ������������������ǰ��
*���������data[]��	ԭʼ����
*		    pdatalen:	ԭʼ���ݵĳ���
*		    number:		Ҫɾ�������ݸ���
*����ֵ�� ��
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
/*���ã�ͨ���������ַ���ȷ��Ҫɾ�����ֽ���
*���������data[]��		ԭʼ����
*			length:			ԭʼ���ݵĳ���
*			substring[]:	���ַ���
*			substringlength:���ַ����ĳ���
*����ֵ��	����ֵΪҪɾ�����ֽ���
*/
int FindSubStringIndex(char data[], int length, char substring[], int substringlength)
{
	int i = 0;
	int j = 0;

	if (length < substringlength){
		//ԭʼ���ݳ���С�����ַ������ȣ����Է���0
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
/*���ã�ͨ������֡β,У�������Ƿ���ȷ
*���������data[]��		ԭʼ����
*			length:			ԭʼ���ݳ���
*			substring[]:	���ַ���
*			substringlength:���ַ����ĳ���
*����ֵ��У��ͨ������1��
*		  У��δͨ������0
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
//������Ϣ���
void ErrorHandling(char *pdata)
{
    //fputs(pdata, stderr);
    std::cout<<pdata<<std::endl;
}
/*****************************************************************************************************/
//��־��Ϣ���
void LogRecording(char *pdata)
{
    //fputs(pdata, stdout);
     std::cout<<pdata<<std::endl;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////
/*���ã��ó����������Ƿ���һ֡����
*���������data[]��		���ջ�����
*			pdatalen:		���ջ������е����ݳ���
*
*����ֵ�� 0����ʾ����ȡ����ȷ�ĳ�����Ϣ����������δ����ȫ
*		  -1����ʾ���ݳ��Ȳ������޷���ȡ��������Ϣ
*        -2����ʾ���ݵĳ�����Ϣ��ȡ���󣬲���һ����Χ��
*        ��������ʾһ֡���ݵĳ���
*/
int HasOneFrame(char data[], int* pdatalen){

	int data_len = *pdatalen;	//�����������ݳ���
	int frame_len = 0;			//һ֡���ݵĳ���

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

/*���ã��ó�һ֡���ݵĳ���
*���������data[]��	ÿ��Socket�׽���ר�е�socket���ջ�����
*����ֵ�����ؽ����һ֡���ݵĳ���
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

	hSocket = socket(PF_INET, SOCK_STREAM, 0);		//������socket
	if (hSocket == INVALID_SOCKET){
		return 2;
	}

//	std::cout << "�����������IP��ַ" << std::endl;
//	fgets(server_ip, sizeof(server_ip), stdin);

//	std::cout << "����˿ں�" << std::endl;
//	fgets(server_port, sizeof(server_port), stdin);

	memset(&servAdr, 0, sizeof(servAdr));
	servAdr.sin_family = AF_INET;
    servAdr.sin_addr.s_addr = inet_addr("192.168.1.1");
    servAdr.sin_port = htons(atoi("8080"));


	if (connect(hSocket, (SOCKADDR*)&servAdr, sizeof(servAdr)) == SOCKET_ERROR){	//���׽��ְ󶨵��������������ַ��
		return 3;
	}

    int iMode = 1;
    ioctlsocket(hSocket, FIONBIO, (u_long FAR*) &iMode);
	hEvent = WSACreateEvent();			//�����¼�����
	if (hEvent == WSA_INVALID_EVENT){
		return 4;
	}

	if (WSAEventSelect(hSocket, hEvent, FD_READ | FD_CLOSE) == SOCKET_ERROR){		//���ӵ��¼�����Ϊ�Ƿ����µ���������
		return 5;
	}
	return 0;
}
/*���ã�������ͨ�����緢�͵���Ӧ�˿�
*���������s:				�׽���
*			mode��			ģʽ
*			buf[]��			socket���ͻ�����
*			buflen:			socket���ͻ������Ĵ�С
*			data[]��		�跢�͵�����
*			datalen:		�跢�͵����ݳ���
*����ֵ��  0��				����ɹ�����
*			������		����ʧ�ܣ���ֵΪ��Ӧ������
*/
int MySend(SOCKET s, char mode, char buf[], int buflen, char data[], int datalen){
	int wt_cnt = 0;			//ÿ�ε���send�����ķ���ֵ
	int total_len = 0;		//�ܹ�Ҫ���͵����ݳ���
	int str_len = 0;		//ʣ��Ҫ���͵����ݳ���
	int buf_len = buflen;	//���ͻ����������ݳ���
	int data_len = datalen;	//Ҫ���͵����ݵĳ���

	memset(buf, 0, buf_len);
	total_len = data_len + 9;

	//��λ���ݳ���
	buf[0] = total_len / (256 * 256 * 256);
	buf[1] = (total_len / (256 * 256)) % 256;
	buf[2] = (total_len / 256) % 256;
	buf[3] = total_len%256;

	//һλģʽ
	buf[4] = mode;

	if (data_len > 0){
		for (int i = 0; i < data_len; i++){
			buf[i + 5] = data[i];
		}
	}

	//��λ���ݽ�β
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


/*���ã�������ͨ�����緢�͵���Ӧ�˿�
*���������s:				�׽���
*			buf[]��			socket���ջ�����
*			buflen:			socket���ջ������Ĵ�С
*����ֵ��	recv�����ķ���ֵ
*/

int MyRecv(SOCKET s, char buf[], int buflen){
	int result = 0;
	result = recv(s, buf, buflen, 0);
	return result;
}

/*���ã�������ͨ�����緢�͵���Ӧ�˿�
*���������	s:			�׽���
*				event��		�׽����������¼�����
*����ֵ��		0��			�̶�ֵ
*/
int MySocketClose(SOCKET s, WSAEVENT event){
	WSACloseEvent(event);
	closesocket(s);
	return 0;
}

/*���ã��Ի������е����ݽ��н���
*���������buf[]��			Socket�׽���ר�е�socket���ջ�����
*			pbuflen:		ָ��Socket�׽���ר�е�socket���ջ������е����ݳ���
*			pdatalen:		ָ��һ֡��Ϣ�ĳ���
*����ֵ�� 0����ʾ����ȡ����ȷ�ĳ�����Ϣ����������δ����ȫ����Ҫ��������
*         1����Ҫ������������
*/
int DataAnalyze(char data[], int* pdatalen){
	int data_len = *pdatalen;	//datalenΪ�����������ݵĳ���
	int frame_len = 0;	//pframelenΪһ֡���������ݶ�Ӧ�ĳ���

	//�ж����ݻ��������Ƿ���һ֡У��ͨ������Ϣ
	frame_len = HasOneFrame(data, pdatalen);
	if (frame_len == 0){
		//��ʾ����ȡ����ȷ�ĳ�����Ϣ����������δ����ȫ
		return 0;
	}
	else if (frame_len == -1){
		//��ʾ���ݳ��Ȳ������޷���ȡ��������Ϣ
		return 0;
	}
	else if (frame_len == -2){
		//��ʾ���ݵĳ�����Ϣ��ȡ���󣬲���һ����Χ��,�������ݿ�ͷ�ʹ��ˣ������������
		int index = 0;
		index = FindSubStringIndex(data, data_len, "####", 4);
		AdjustBuffer(data, pdatalen, index);						//�������ջ�����������������ǰ�����õ�����ɾ����ͬʱ���������ǰ��
		return 1;
	}
	else{
		//�ó���һ֡�����ݳ���
		if (CheckData(data, frame_len, "####", 4) == TRUE){
        //std::cout << "����У��ͨ��" << std::endl;
            if (data[4] == 3){
                //std::cout << "�յ�һ֡����" << std::endl;
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
				std::cout << "����ָ��" << std::endl;
				AdjustBuffer(data, pdatalen, frame_len);						//�������ջ�����������������ǰ�����õ�����ɾ����ͬʱ���������ǰ��
				return 3;
			}
			//AdjustBuffer(data, pdatalen, frame_len);						//�������ջ�����������������ǰ�����õ�����ɾ����ͬʱ���������ǰ��
			return 2;
		}
		else{
            //std::cout << "����δУ��ͨ��" << std::endl;
			int index = 0;
			index = FindSubStringIndex(data, data_len, "####", 4);
			AdjustBuffer(data, pdatalen, index);						//�������ջ�����������������ǰ�����õ�����ɾ����ͬʱ���������ǰ��
		}
		return 1;
	}
}


/*���ã���ȡ��������
*���������s:				�׽���
*			netEvents		�׽��ֶ�Ӧ���¼�����
*			buf[]��			���ջ�����
*			pbuflen:		���ջ������е����ݳ���
*			data��			���ڴ洢һ֡���ݵĻ�����
*			pdatalen:		ָ��һ֡��Ϣ�ĳ���
*����ֵ�� 0������������Ҫ�Ͽ�����
*         1����ȷ����
*/
int ReadHanding(SOCKET s, WSANETWORKEVENTS netEvents, char buf[], int buflen, char data[], int *pdatalen){
	int str_len = 0;				//����MyRecv()��ķ���ֵ
	int buf_len = buflen;			//���ջ������е����ݳ���
	int data_len = *pdatalen;		//�������е����ݳ���

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
			//����������Ҫ�Դ���������
			if (WSAGetLastError() == 10035){
				continue;
			}
			if (errno == EAGAIN){
				//��ʾ��ǰ�������������ݿɶ�
				;
			}
			else{
				//std::cout << "3333" << std::endl;
				//����ԭ��
				return 0;
			}
		}

		if (DataAnalyze(data, pdatalen) == 2){
			break;
		}

	}

	return 1;
}

/*���ã��Ͽ���������
*���������	s:				�׽���
*			hEvent��		�׽��ֶ�Ӧ���¼�����
*			netEvents		�¼������Ӧ���¼�����
*����ֵ��	0��				�̶�����ֵ
*/
int CloseHanding(SOCKET s, WSAEVENT hEvent, WSANETWORKEVENTS netEvents){
	//FD_CLOSE�¼��Ĵ���
	if (netEvents.iErrorCode[FD_CLOSE_BIT] != 0)  //�������FD_CLOSE��ش�������iErrorCode[FD_CLOSE_BIT]�б����0���������ֵ
	{
		ErrorHandling("�ر��¼�����ʱ��������FD_CLOSE��ش���");
	}

	WSACloseEvent(hEvent);
	closesocket(s);
	return 0;
}

