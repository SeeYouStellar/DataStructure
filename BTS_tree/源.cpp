#include <winsock2.h>
#include <windows.h>
#include <string.h>
#include <mstcpip.h>
#include<_dbdao.h>
#include<iostream>
using namespace std;
struct IP_HEAD              //IP首部
{
	//IP协议版本和IP首部长度。高4位为版本，低4位为首部的长度
	BYTE ver_hlen;
	BYTE byTOS;       //服务类型 
	WORD wPacketLen; 	//总长度
	WORD wSequence;    //标识 
	union
	{
		WORD Flags; 	//标志
		WORD FragOf;//分段偏移
	};
	BYTE byTTL;         //生存时间 
	BYTE byProtocolType; 	//协议类型
	WORD wHeadCheckSum;  //IP首部校验和
	DWORD dwIPSrc;        //源地址
	DWORD dwIPDes;        //目的地址
	BYTE Options;          	//选项
}
int cnt;    //全局变量
void AutoWSACleanup()
{
	::WSACleanup();
}
int PrintIP(char* buf, int len)  //输出抓包结果，即每个数据报的首部各项
{
	int n = len;
	if (n >= sizeof(IP_HEAD))
	{
		IP_HEAD  iphead;   //IP头部
		iphead = *(IP_HEAD*)buf;
		cout << "第 " << cnt++ << " 个IP数据包信息：" << endl;
		cout << "协议版本:" << (iphead.ver_hlen >> 4) << endl;
		cout << "首部长度:" << ((iphead.ver_hlen & 0x0F) << 2) << endl;//单位为4字节
		cout << "服务类型:Priority: " << (iphead.byTOS >> 5) << ",Service: " << ((iphead.byTOS >> 1) & 0x0f) << endl;
		cout << "IP包总长度:" << ntohs(iphead.wPacketLen) << endl; //网络字节序转为主机字节序
		cout << "标识:" << ntohs(iphead.wSequence) << endl;
		cout << "标志位:" << "DF=" << ((iphead.Flags >> 14) & 0x01) << ",MF=" << ((iphead.Flags >> 13) & 0x01) << endl;
		cout << "片偏移:" << (iphead.FragOf & 0x1fff) << endl;
		cout << "生存周期:" << (int)iphead.byTTL << endl;
		cout << "协议类型:" << int(iphead.byProtocolType) << endl;
		cout << "首部校验和:" << ntohs(iphead.wHeadCheckSum) << endl;
		cout << "源地址:" << inet_ntoa(*(in_addr*)&iphead.dwIPSrc) << endl;
		cout << "目的地址:" << inet_ntoa(*(in_addr*)&iphead.dwIPDes) << endl;
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
		cout << "WSAStartup函数错误！" << endl;
		return -1;
	}
	atexit(AutoWSACleanup);
	//创建SOCKET
	SOCKET sock = socket(AF_INET, SOCK_RAW, IPPROTO_IP);
	if (sock == INVALID_SOCKET)
	{
		cout << WSAGetLastError();
		return 0;
	}
	//获取本机地址
	char  host_ip[128];
	if (-1 == gethostname(host_ip, sizeof(host_ip)))
	{
		closesocket(sock);
		cout << WSAGetLastError();
		return 0;
	}
	struct hostent* pHostent;
	pHostent = gethostbyname(host_ip);
	//绑定本地地址到SOCKET句柄
	sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_addr = *(in_addr*)pHostent->h_addr_list[0]; //IP
	addr.sin_port = 8888; //端口，IP层端口可随意填
	if (SOCKET_ERROR == bind(sock, (sockaddr*)&addr, sizeof(addr)))
	{
		closesocket(sock);
		cout << WSAGetLastError();
		return 0;
	}
	//设置该SOCKET为接收所有流经绑定的IP的网卡的所有数据，包括接收和发送的数据包
	u_long sioarg = 1;
	DWORD wt = 0;
	if (SOCKET_ERROR == WSAIoctl(sock, SIO_RCVALL, &sioarg, sizeof(sioarg), NULL, 0, &wt, NULL, NULL))
	{
		closesocket(sock);
		cout << WSAGetLastError();
		return 0;
	}
	//我们只需要接收数据，因此设置为阻塞IO，使用最简单的IO模型
	u_long bioarg = 0;
	if (SOCKET_ERROR == ioctlsocket(sock, FIONBIO, &bioarg))
	{
		closesocket(sock);
		cout << WSAGetLastError();
		return 0;
	}
	//开始接收数据
	//因为前面已经设置为阻塞IO，recv在接收到数据前不会返回。
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
