#include <windows.h>
#include <tchar.h>
LRESULT CALLBACK
WndProc(HWND hwnd,
	UINT iMsg, WPARAM wParam,
	LPARAM lParam);
int WINAPI _tWinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine,int nCmdShow)
{
	//1.�����츦 ���̰�
	// ������ �Ӽ��� ����ϰ�
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
	wndClass.lpszClassName = _T("3��");
	wndClass.lpszMenuName = NULL;
	wndClass.style = CS_HREDRAW	| CS_VREDRAW; 
	
	RegisterClassEx(&wndClass);
	//RegisterClassEx
	HWND hwnd;
	hwnd = CreateWindow(_T("3��")
		, _T("3�� ���� ")
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
	//�����ϰ� ������.
	return 0;
}
LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	switch (iMsg)
	{
	case WM_CREATE:
		break;
		//x��ư�� ������ ���� �߻�
	case WM_DESTROY:
		//WM_QUIT����
		PostQuitMessage(0);
		break;
	}
	return DefWindowProc(hwnd, iMsg, wParam, lParam);
}