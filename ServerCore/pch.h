#pragma once
#pragma comment(lib, "ws2_32.lib")

#include "Types.h"

#include <winsock2.h>
#include <mswsock.h>
#include <ws2tcpip.h>
#include <windows.h>
#include <iostream>
using namespace std;

#include<vector>
#include<queue>
#include<thread>
#include<mutex>
#include<condition_variable>
#include<future>
#include<functional>
#include<chrono>

#include "SocketUtils.h"
#include "Listener.h"
#include "IocpCore.h"


inline void HandleError(string error) { cout << error << endl; }