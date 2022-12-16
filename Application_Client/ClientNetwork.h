#pragma once
#include <iostream>
#include <winsock2.h>
#include <mswsock.h>
#include <ws2tcpip.h>
#include <Types.h>
#include <PKT_Maker.h>
#pragma comment(lib, "ws2_32.lib")

using namespace std;

class ClientNetwork
{
public:
	ClientNetwork(wstring ip, short port);
	~ClientNetwork();

	bool Connect();
	int Recv();
	int Send(char* data, int len);
	char* getString();

private:
	void SetBind(wstring ip, short port);
	bool Init();
	void Clear();

private:
	SOCKET _socket;
	SOCKADDR_IN _address;
	PKT_Maker maker;

	BYTE* recvBuffer;
	char* string;
};

