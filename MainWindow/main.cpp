#define _CRT_SECURE_NO_WARNINGS
#include<Windows.h>
#include<cstdio>

CONST CHAR g_sz_MY_WINDOW_CLASS[] = "My Window"; //Имя класса окна

INT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpCmdLine, INT nCmdShow)
{
	//1.Регистрация класса окна
	WNDCLASSEX wc;
	ZeroMemory(&wc, sizeof(wc));

	wc.style = 0;
	wc.cbSize = sizeof(wc);
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0; //cb... - Count Bytes

	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)COLOR_WINDOW;

	wc.hInstance = hInstance;
	wc.lpszMenuName = NULL;
	wc.lpszClassName = g_sz_MY_WINDOW_CLASS;
	wc.lpfnWndProc = (WNDPROC)WndProc;


	if (!RegisterClassEx(&wc))
	{
		MessageBox(NULL, "Class registration faild", NULL, MB_OK | MB_ICONERROR);
		return 0;
	}

	//2. Создание окна:
	INT width = GetSystemMetrics(SM_CXSCREEN);
	INT height = GetSystemMetrics(SM_CYSCREEN);
	INT w_width = (width - (width * 3/4)) / 2;
	INT w_height = (height - (height * 3/4)) / 2;
	
	HWND hwnd = CreateWindowEx
	(
		NULL,   //ExStyles
		g_sz_MY_WINDOW_CLASS,   //Class name
		g_sz_MY_WINDOW_CLASS,   //Window title
		WS_OVERLAPPEDWINDOW,    //Window style
		//CW_USEDEFAULT, CW_USEDEFAULT, //Window position
		//CW_USEDEFAULT, CW_USEDEFAULT, //Window size
		w_width, w_height,
		width, height,
		NULL,    //Parent Window
		NULL,    //Main menu ResourceID for MainWindow or RecousceID foe ChildWindow
		hInstance,
		NULL
	);
	ShowWindow(hwnd, nCmdShow); //Задает режим отображения окна 
	                            //(Развернуто на весь экран, свернуто в окноб свернуто в панель задач)
	UpdateWindow(hwnd);         //Прорисовывает окно
	

	//3. Запуск цикла сообщений:

	MSG msg;   //Создаем сообщение
	while (GetMessage(&msg, NULL, 0, 0) > 0)
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.message;
}

INT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_CREATE:
		break;
	case WM_SIZE: 
	case WM_MOVE:
	{
		RECT rc;
		GetWindowRect(hwnd, &rc);
		//int xPos = (GetSystemMetrics(SM_CXSCREEN) - rc.right) / 2;
		//int yPos = (GetSystemMetrics(SM_CYSCREEN) - rc.bottom) / 2;
		//SetWindowPos(hwnd, 0, xPos, yPos, 0, 0, SWP_NOZORDER | SWP_NOSIZE);
		int xPos = rc.left;
		int yPos = rc.top;
		char sz_title[256];
		sprintf(sz_title, "Координаты: (%i, %i)", xPos, yPos);
		SetWindowText(hwnd, sz_title);
	}
		break;
	case WM_COMMAND:
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_CLOSE:
		DestroyWindow(hwnd);
		break;
	default: return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}
	return FALSE;
}