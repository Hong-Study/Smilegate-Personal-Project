#include <windows.h>
#include <tchar.h>
LRESULT CALLBACK
WndProc(HWND hwnd,
	UINT iMsg, WPARAM wParam,
	LPARAM lParam);
int WINAPI _tWinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine,int nCmdShow)
{
	//1.윈도우를 보이게
	// 잘잘한 속성은 등록하고
	WNDCLASSEX wndClass;
	wndClass.cbClsExtra = 0;
	wndClass.cbSize = sizeof(wndClass);
	wndClass.cbWndExtra = 0;
	wndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wndClass.hCursor = (HCURSOR)LoadCursor(NULL, IDC_ARROW);
	wndClass.hIcon = (HICON)LoadIcon(NULL, IDI_APPLICATION);
	wndClass.hIconSm = (HICON)LoadIcon(NULL, IDI_APPLICATION);
	wndClass.hInstance = hInstance;
	wndClass.lpfnWndProc = WndProc;
	wndClass.lpszClassName = _T("3장");
	wndClass.lpszMenuName = NULL;
	wndClass.style = CS_HREDRAW	| CS_VREDRAW; 
	
	RegisterClassEx(&wndClass);
	//RegisterClassEx
	HWND hwnd;
	hwnd = CreateWindow(_T("3장")
		, _T("3장 내용 ")
		,WS_OVERLAPPEDWINDOW
		,CW_USEDEFAULT
		,CW_USEDEFAULT
		,CW_USEDEFAULT
		,CW_USEDEFAULT
		,NULL
		,NULL
		,hInstance
		,NULL);
	ShowWindow(hwnd, nCmdShow);
	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	//번역하고 던진다.
	return 0;
}
LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	switch (iMsg)
	{
	case WM_CREATE:
		break;
		//x버튼을 누르는 순간 발생
	case WM_DESTROY:
		//WM_QUIT보냄
		PostQuitMessage(0);
		break;
	}
	return DefWindowProc(hwnd, iMsg, wParam, lParam);
}