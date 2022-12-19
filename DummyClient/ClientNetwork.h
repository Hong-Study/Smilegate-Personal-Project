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
	ClientNetwork();
	~ClientNetwork();

	bool Connect();
	int Recv();
	int Send(string data, int n);
	std::string getString();

public:
	void SetBind(wstring ip, short port);
	bool Init();
	void Clear();
	bool IsHttp(string& data);

private:
	SOCKET _socket;
	SOCKADDR_IN _address;
	PKT_Maker maker;

	BYTE* recvBuffer;
	char* str;
	bool h;

private:
	string http = "http://";
	string https = "https://";
};

