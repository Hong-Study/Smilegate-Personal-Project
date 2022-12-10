#pragma once
#include <iostream>
#include <winsock2.h>
#include <mswsock.h>
#include <ws2tcpip.h>
#pragma comment(lib, "ws2_32.lib")

using namespace std;

class ClientNetwork
{
public:
	ClientNetwork(wstring ip, short port);
	~ClientNetwork();

	bool Connect();
	int Send(char* data, int len);
	int Recv(char* buf);

private:
	void SetBind(wstring ip, short port);
	bool Init();
	void Clear();

private:
	SOCKET _socket;
	SOCKADDR_IN _address;
};

