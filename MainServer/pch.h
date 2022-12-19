#pragma once

#define WIN32_LEAN_AND_MEAN // ���� ������ �ʴ� ������ Windows ������� �����մϴ�.

#ifdef _DEBUG
#pragma comment(lib, "Debug\\ServerCore.lib")
#pragma comment(lib, "libmySQL.lib")
#pragma warning(disable:4996)
#else
#pragma comment(lib, "Release\\ServerCore.lib")
#pragma comment(lib, "libmySQL.lib")
#pragma warning(disable:4996)
#endif

#define THREAD_SIZE 10

#include <pch.h>
#include <mysql.h>
#include <vector>
#include "Macro.h"
#include "DBConnectionPool.h"