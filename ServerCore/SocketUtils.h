#pragma once
#include "NetAddress.h"

class SocketUtils
{
public:
	static LPFN_ACCEPTEX AcceptEX;
	static LPFN_CONNECTEX ConnectEX;
	static LPFN_DISCONNECTEX DisconnectEX;

public:
	static void Init();
	static void clear();

	static SOCKET CreateSocket();
	static void Close(SOCKET& socket);

	static bool BindWindowsFunction(SOCKET socket, GUID guid, LPVOID* fn);
	static bool Bind(SOCKET socket, NetAddress netAddr);
	static bool BindAnyAddress(SOCKET socket, uint16 port);
	static bool Listen(SOCKET socket, int32 backlog);
};

