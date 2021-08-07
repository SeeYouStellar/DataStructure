#include <winsock2.h>
#include <windows.h>
#include <string.h>
#include <mstcpip.h>
#include<_dbdao.h>
#include<iostream>
using namespace std;
struct IP_HEAD              //IP�ײ�
{
	//IPЭ��汾��IP�ײ����ȡ���4λΪ�汾����4λΪ�ײ��ĳ���
	BYTE ver_hlen;
	BYTE byTOS;       //�������� 
	WORD wPacketLen; 	//�ܳ���
	WORD wSequence;    //��ʶ 
	union
	{
		WORD Flags; 	//��־
		WORD FragOf;//�ֶ�ƫ��
	};
	BYTE byTTL;         //����ʱ�� 
	BYTE byProtocolType; 	//Э������
	WORD wHeadCheckSum;  //IP�ײ�У���
	DWORD dwIPSrc;        //Դ��ַ
	DWORD dwIPDes;        //Ŀ�ĵ�ַ
	BYTE Options;          	//ѡ��
}
int cnt;    //ȫ�ֱ���
void AutoWSACleanup()
{
	::WSACleanup();
}
int PrintIP(char* buf, int len)  //���ץ���������ÿ�����ݱ����ײ�����
{
	int n = len;
	if (n >= sizeof(IP_HEAD))
	{
		IP_HEAD  iphead;   //IPͷ��
		iphead = *(IP_HEAD*)buf;
		cout << "�� " << cnt++ << " ��IP���ݰ���Ϣ��" << endl;
		cout << "Э��汾:" << (iphead.ver_hlen >> 4) << endl;
		cout << "�ײ�����:" << ((iphead.ver_hlen & 0x0F) << 2) << endl;//��λΪ4�ֽ�
		cout << "��������:Priority: " << (iphead.byTOS >> 5) << ",Service: " << ((iphead.byTOS >> 1) & 0x0f) << endl;
		cout << "IP���ܳ���:" << ntohs(iphead.wPacketLen) << endl; //�����ֽ���תΪ�����ֽ���
		cout << "��ʶ:" << ntohs(iphead.wSequence) << endl;
		cout << "��־λ:" << "DF=" << ((iphead.Flags >> 14) & 0x01) << ",MF=" << ((iphead.Flags >> 13) & 0x01) << endl;
		cout << "Ƭƫ��:" << (iphead.FragOf & 0x1fff) << endl;
		cout << "��������:" << (int)iphead.byTTL << endl;
		cout << "Э������:" << int(iphead.byProtocolType) << endl;
		cout << "�ײ�У���:" << ntohs(iphead.wHeadCheckSum) << endl;
		cout << "Դ��ַ:" << inet_ntoa(*(in_addr*)&iphead.dwIPSrc) << endl;
		cout << "Ŀ�ĵ�ַ:" << inet_ntoa(*(in_addr*)&iphead.dwIPDes) << endl;
		cout << "==============================================================" << endl << endl;
	}
	return 0;
}

int main()
{
	int n;
	WSADATA wd;
	n = WSAStartup(MAKEWORD(2, 2), &wd);
	if (n)
	{
		cout << "WSAStartup��������" << endl;
		return -1;
	}
	atexit(AutoWSACleanup);
	//����SOCKET
	SOCKET sock = socket(AF_INET, SOCK_RAW, IPPROTO_IP);
	if (sock == INVALID_SOCKET)
	{
		cout << WSAGetLastError();
		return 0;
	}
	//��ȡ������ַ
	char  host_ip[128];
	if (-1 == gethostname(host_ip, sizeof(host_ip)))
	{
		closesocket(sock);
		cout << WSAGetLastError();
		return 0;
	}
	struct hostent* pHostent;
	pHostent = gethostbyname(host_ip);
	//�󶨱��ص�ַ��SOCKET���
	sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_addr = *(in_addr*)pHostent->h_addr_list[0]; //IP
	addr.sin_port = 8888; //�˿ڣ�IP��˿ڿ�������
	if (SOCKET_ERROR == bind(sock, (sockaddr*)&addr, sizeof(addr)))
	{
		closesocket(sock);
		cout << WSAGetLastError();
		return 0;
	}
	//���ø�SOCKETΪ�������������󶨵�IP���������������ݣ��������պͷ��͵����ݰ�
	u_long sioarg = 1;
	DWORD wt = 0;
	if (SOCKET_ERROR == WSAIoctl(sock, SIO_RCVALL, &sioarg, sizeof(sioarg), NULL, 0, &wt, NULL, NULL))
	{
		closesocket(sock);
		cout << WSAGetLastError();
		return 0;
	}
	//����ֻ��Ҫ�������ݣ��������Ϊ����IO��ʹ����򵥵�IOģ��
	u_long bioarg = 0;
	if (SOCKET_ERROR == ioctlsocket(sock, FIONBIO, &bioarg))
	{
		closesocket(sock);
		cout << WSAGetLastError();
		return 0;
	}
	//��ʼ��������
	//��Ϊǰ���Ѿ�����Ϊ����IO��recv�ڽ��յ�����ǰ���᷵�ء�
	cnt = 1;
	char buf[65535];
	int len = 0;
	do
	{
		len = recv(sock, buf, sizeof(buf), 0);
		if (len > 0)
		{
			PrintIP(buf, len);
		}
	} while (len > 0);
	closesocket(sock);
	return 0;
}
