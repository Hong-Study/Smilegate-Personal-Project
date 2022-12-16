#pragma once

#ifndef PCH_H
#define PCH_H

#ifdef _DEBUG
#pragma comment(lib, "Debug\\ServerCore.lib")
#else
#pragma comment(lib, "Release\\ServerCore.lib")
#endif

#endif //PCH_H
