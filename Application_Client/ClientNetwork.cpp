#include "pch.h"
#include "ClientNetwork.h"

bool ClientNetwork::Init()
{
	WSADATA wsaData;
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
		return false;
	_socket = socket(AF_INET, SOCK_STREAM, 0);

	return INVALID_SOCKET != _socket;
}

ClientNetwork::ClientNetwork(wstring ip, short port)
{
	Init();
	SetBind(ip, port);
}

ClientNetwork::~ClientNetwork()
{
	Clear();
}

void ClientNetwork::Clear()
{
	::WSACleanup();
}

void ClientNetwork::SetBind(wstring ip, short port)
{
	ZeroMemory(&_address, sizeof(SOCKADDR_IN));
	IN_ADDR addr;
	::InetPtonW(AF_INET, ip.c_str(), &addr);

	_address.sin_family = AF_INET;
	_address.sin_port = htons(port);
	_address.sin_addr = addr;
}

bool ClientNetwork::Connect()
{
	return SOCKET_ERROR != ::connect(_socket, reinterpret_cast<SOCKADDR*>(&_address), sizeof(SOCKADDR));
}

int ClientNetwork::Send(char* data, int len)
{
	return send(_socket, data, len, 0);
}

int ClientNetwork::Recv(char* buf)
{
	return recv(_socket, buf, 100, 0);
}
