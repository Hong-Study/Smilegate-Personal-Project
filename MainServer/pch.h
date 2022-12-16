#pragma once

#define WIN32_LEAN_AND_MEAN // 거의 사용되지 않는 내용을 Windows 헤더에서 제외합니다.

#ifdef _DEBUG
#pragma comment(lib, "Debug\\ServerCore.lib")
#pragma comment(lib, "libmySQL.lib")
#else
#pragma comment(lib, "Release\\ServerCore.lib")
#pragma comment(lib, "libmySQL.lib")
#endif

#define THREAD_SIZE 10

#include <pch.h>
#include <mysql.h>
#include "Macro.h"
#include "DBConnectionPool.h"