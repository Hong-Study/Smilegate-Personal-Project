#include <iostream>

#include "pch.h"

void HandleError(const char* cause)
{
	int errCode = ::WSAGetLastError();
	cout << cause << " ErrorCode : " << errCode << endl;
}

int main()
{
	WSAData wsaData;
	if (::WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
		return 0;

	SOCKET clientSocket = ::socket(AF_INET, SOCK_STREAM, 0);
	if (clientSocket == INVALID_SOCKET)
		return 0;

	/*u_long on = 1;
	if (::ioctlsocket(clientSocket, FIONBIO, &on) == INVALID_SOCKET)
		return 0;*/

	SOCKADDR_IN serverAddr;
	::memset(&serverAddr, 0, sizeof(serverAddr));
	serverAddr.sin_family = AF_INET;
	::inet_pton(AF_INET, "127.0.0.1", &serverAddr.sin_addr);
	serverAddr.sin_port = ::htons(5000);

	// Connect
	//while (true)
	{
		if (::connect(clientSocket, (SOCKADDR*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR)
		{
			
		}
	}

	// 소켓 리소스 반환
	::closesocket(clientSocket);

	// 윈속 종료
	::WSACleanup();
}