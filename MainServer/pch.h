#pragma once

#define WIN32_LEAN_AND_MEAN // ���� ������ �ʴ� ������ Windows ������� �����մϴ�.

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
