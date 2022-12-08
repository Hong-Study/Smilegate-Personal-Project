#pragma once
#include "NetAddress.h"

class SocketUtils
{
public:
	static LPFN_ACCEPTEX AcceptEx;
	static LPFN_CONNECTEX ConnectEx;
	static LPFN_DISCONNECTEX DisconnectEx;

public:
	static void Init();
	static void Clear();

	static SOCKET CreateSocket();
	static void Close(SOCKET& socket);

	static bool Bind(SOCKET socket, NetAddress netAddr);
	static bool BindAnyAddress(SOCKET socket, uint16 port);
	static bool Listen(SOCKET socket, int32 backlog);
	static bool SetUpdateAcceptSocket(SOCKET socket, SOCKET listenSocket);
private:
	static bool BindWindowsFunction(SOCKET socket, GUID guid, LPVOID* fn);
};

template<typename T>
static inline bool SetSockOpt(SOCKET socket, int32 level, int32 optName, T optVal)
{
	return SOCKET_ERROR != ::setsockopt(socket, level, optName, reinterpret_cast<char*>(&optVal), sizeof(T));
}