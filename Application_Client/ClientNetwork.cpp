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
	recvBuffer = new BYTE[100];
	string = new char[30];
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
	int size = sizeof(PKT_Header) + len;
	//BYTE* byte = maker.MakePacket_URLMAPPING(data, len);
	BYTE* byte = new BYTE[size];
	PKT_Header* head = reinterpret_cast<PKT_Header*>(&byte[0]);
	head->pkt_State = PKT_STATE::URL_MAPPING;
	head->pkt_Size = len; 
	memcpy(&byte[sizeof(PKT_Header)], data, len);

	int strlen =  send(_socket, (CHAR*)byte, size, 0);
	delete[] byte;

	return strlen;
}

char* ClientNetwork::getString()
{
	return string;
}

int ClientNetwork::Recv()
{
	ZeroMemory(string, 30);
	ZeroMemory(recvBuffer, 100);

	int len = recv(_socket, (char*)recvBuffer, 100, 0);
	PKT_Header* head = reinterpret_cast<PKT_Header*>(&recvBuffer[0]);
	
	memcpy(string, &recvBuffer[sizeof(PKT_Header)], head->pkt_Size);

	return len;
}
