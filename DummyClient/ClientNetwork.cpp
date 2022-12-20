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

ClientNetwork::ClientNetwork()
{
	Init();
	recvBuffer.resize(100);
	str = new char[100];
}

ClientNetwork::~ClientNetwork()
{
	delete[] str;
	Clear();
}

void ClientNetwork::Clear()
{
	::WSACleanup();
}

bool ClientNetwork::IsHttp(string& data)
{	
	if (data.compare(http) == 0)
		return false;
	else if (data.compare(https) == 0)
		return false;
	else if (data.compare(0, http.length(), http) == 0) {
		data = data.substr(http.length(), data.length());
		h = true;
		return true;
	}
	else if (data.compare(0, https.length(), https) == 0) {
		data = data.substr(https.length(), data.length());
		h = false;
		return true;
	}

	return false;
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

int ClientNetwork::Send(string data, int n)
{
	if (data.length() <= 8)
		return -1;
	if (!IsHttp(data))
		return -1;

	int len = data.length() + 1;

	int size = sizeof(PKT_Header) + len;
	//BYTE* byte = maker.MakePacket_URLMAPPING(data, len);
	BYTE* byte = new BYTE[size];
	PKT_Header* head = reinterpret_cast<PKT_Header*>(&byte[0]);

	if (n == 0)
		head->pkt_State = PKT_STATE::URL_MAKING;
	else
		head->pkt_State = PKT_STATE::URL_MAPPING;
	
	head->pkt_Size = len;
	memcpy(&byte[sizeof(PKT_Header)], data.data(), len);

	int strlen =  send(_socket, (CHAR*)byte, size, 0);
	delete[] byte;

	return strlen;
}

string ClientNetwork::getString()
{
	if (h)
		return http + str;
	return https + str;
}

int ClientNetwork::Recv()
{
	ZeroMemory(str, 100);
	recvBuffer.clear();

	int len = recv(_socket, (char*)recvBuffer.data(), 100, 0);
	PKT_Header* head = reinterpret_cast<PKT_Header*>(&recvBuffer[0]);
	
	memcpy(str, &recvBuffer[sizeof(PKT_Header)], head->pkt_Size);

	return len;
}
