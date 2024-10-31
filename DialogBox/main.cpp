#include<Windows.h>
#include"resource.h"

CONST CHAR LOGIN_INVITATION[] = "Введите имя пользователя";
BOOL CALLBACK DlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpCmdLine, INT nCmdShow)
{
	DialogBoxParam(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), NULL, (DLGPROC)DlgProc, 0);
	return 0;
}

BOOL CALLBACK DlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	
	switch (uMsg)
	{
	case WM_INITDIALOG:
	{
		HICON hIcon = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_ICON1));
		SendMessage(hwnd, WM_SETICON, 0, (LPARAM)hIcon);
		HWND hEdit = GetDlgItem(hwnd, IDC_EDIT_LOGIN);
		SendMessage(hEdit, WM_SETTEXT, 0, (LPARAM)LOGIN_INVITATION);
	}
		break;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDC_EDIT_LOGIN:
		{
			CONST INT SIZE = 256;
			CHAR sz_buffer[SIZE] = {};
			SendMessage((HWND)lParam, WM_GETTEXT, SIZE, (LPARAM)sz_buffer);
			if (HIWORD(wParam) == EN_SETFOCUS && strcmp(sz_buffer, LOGIN_INVITATION) == 0)
				SendMessage((HWND)lParam, WM_SETTEXT, 0, (LPARAM)"");
			if (HIWORD(wParam) == EN_KILLFOCUS && strcmp(sz_buffer,"") == 0)
				SendMessage((HWND)lParam, WM_SETTEXT, 0, (LPARAM)LOGIN_INVITATION);
		}
		case IDC_BUTTON_Copy:
		{
			/*HWND hEditLogin = GetDlgItem(hwnd, IDC_EDIT_LOGIN);
			HWND hEditPassword = GetDlgItem(hwnd, IDC_EDIT_Password);*/
			//Функция GetDlgItem() возвращает HWND дочернего элемента окна по его ResourceID.
			//HWND - Handler to Window (Дискриптор окна) - это число при помощи которого можно обратиться к окну
			/*CONST INT SIZE = 256;
			CHAR sz_buffer[SIZE] = {};
			SendMessage(hEditLogin, WM_GETTEXT, SIZE, (LPARAM)sz_buffer);
			SendMessage(hEditPassword, WM_SETTEXT, 0, (LPARAM)sz_buffer);*/
			/*SendMessage(hwnd, WM_SETTEXT, 0, (LPARAM)sz_buffer);
			SendMessage(GetDlgItem(hwnd, IDC_BUTTON_Copy), WM_SETTEXT, 0, (LPARAM)sz_buffer);*/

		}
		break;
		case IDOK: MessageBox(hwnd, "Была нажата кнопка ОК!", "Info", MB_OK | MB_ICONINFORMATION); break;
		case IDCANCEL: EndDialog(hwnd, 0); break;
		}
		break;
	case WM_CLOSE:
		EndDialog(hwnd, 0);
		break;
	}
	return FALSE;
}