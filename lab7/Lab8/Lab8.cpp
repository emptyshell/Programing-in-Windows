#include <windows.h>
#include <math.h>
#include "stdafx.h"
#include <stdlib.h>
#include <commdlg.h>
#include <wingdi.h>


#define IDM_FILE	   	  1000
#define IDM_FILE_NEW      1001
#define IDM_FILE_OPEN     1002
#define IDM_FILE_SAVE     1003
#define IDM_FILE_SAVEAS   1004
#define IDM_FILE_EXIT     1005
#define IDM_EDIT		  1006
#define IDM_EDIT_CUT	  1007
#define IDM_EDIT_COPY	  1008
#define IDM_EDIT_PASTE	  1009
#define IDM_FORMAT_FONT   1010
#define IDM_FORMAT		  1011
#define IDM_ABOUT		  1012
using namespace std;
UINT IDC_MAIN_EDIT = 101;
HWND g_hwnd;
HWND g_hEdit;
HFONT g_hFont;
COLORREF textCol = RGB(0, 0, 0);
bool isOpen = false;
bool saving = false;
TCHAR curfile[MAX_PATH];
void LoadFileToEdit() {
	curfile[0] = TEXT('\0');
	OPENFILENAME openfilename;
	ZeroMemory(&openfilename, sizeof(OPENFILENAME));
	openfilename.lStructSize = sizeof(OPENFILENAME);
	openfilename.hwndOwner = g_hwnd;
	openfilename.lpstrFilter = TEXT("Text Files(*.txt)\0*.txt\0All File(*.*)\0*.*\0");
	openfilename.lpstrFile = curfile;
	openfilename.nMaxFile = MAX_PATH;
	openfilename.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY;
	openfilename.lpstrDefExt = TEXT("txt");
	if (!GetOpenFileName(&openfilename))
		return;
	HANDLE hFile;
	bool bsucces = false;
	hFile = CreateFile(curfile, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL);
	if (hFile != INVALID_HANDLE_VALUE) {
		DWORD dwFileSize;
		dwFileSize = GetFileSize(hFile, NULL);
		if (dwFileSize != 0xFFFFFFFF) {
			TCHAR* tempftext;
			tempftext = (TCHAR*)GlobalAlloc(GPTR, dwFileSize + 1);
			if (tempftext != NULL) {
				DWORD dwRead;
				if (ReadFile(hFile, tempftext, dwFileSize, &dwRead, NULL)) {
					tempftext[dwFileSize] = 0;
					if (SetWindowText(g_hEdit, tempftext))
						bsucces = true;
				}
				GlobalFree(tempftext);
			}
		}
		CloseHandle(hFile);
	}
	if (!bsucces) {
		MessageBox(g_hwnd, TEXT("Eroare la incarcarea fisierului"), TEXT("Error"), MB_OK | MB_ICONERROR);
		return;
	}
	SetWindowText(g_hwnd, curfile);
	saving = false;
	isOpen = true;
}

void SaveTextFileFromEdit() {
	HANDLE hFile;
	bool bsucces = false;
	hFile = CreateFile(curfile, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hFile != INVALID_HANDLE_VALUE) {
		DWORD dwTextLength;
		dwTextLength = GetWindowTextLength(g_hEdit);
		TCHAR* pszText;
		DWORD dwBufferSize = dwTextLength + 1;
		pszText = (TCHAR*)GlobalAlloc(GPTR, dwBufferSize);
		if (pszText != NULL) {
			if (GetWindowText(g_hEdit, pszText, dwBufferSize)) {
				DWORD dwWritten;
				if (WriteFile(hFile, pszText, dwTextLength, &dwWritten, NULL))
					bsucces = true;
			}
			GlobalFree(pszText);
		}
		CloseHandle(hFile);
	}
	if (!bsucces) {
		MessageBox(g_hwnd, TEXT("Eroare la salvarea fisierului!"), TEXT("Error"), MB_OK | MB_ICONERROR);
		return;
	}
	isOpen = true;
	saving = false;
}
bool GetFileNameForSave() {
	OPENFILENAME openfilename;
	ZeroMemory(&openfilename, sizeof(OPENFILENAME));
	openfilename.lStructSize = sizeof(OPENFILENAME);
	openfilename.hwndOwner = g_hwnd;
	openfilename.lpstrFilter = TEXT("Text Files(*.txt)\0*.txt\0All File(*.*)\0*.*\0");
	openfilename.lpstrFile = curfile;
	openfilename.nMaxFile = MAX_PATH;
	openfilename.Flags = OFN_EXPLORER | OFN_PATHMUSTEXIST | OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT;
	openfilename.lpstrDefExt = TEXT("txt");
	if (!GetSaveFileName(&openfilename))
		return false;
	return true;
}

void ChooseFontForEdit() {
	CHOOSEFONT choosefont = { sizeof(CHOOSEFONT) };
	LOGFONT lf;
	GetObject(g_hFont, sizeof(LOGFONT), &lf);
	choosefont.Flags = CF_EFFECTS | CF_SCREENFONTS | CF_INITTOLOGFONTSTRUCT;
	choosefont.hwndOwner = g_hwnd;
	choosefont.lpLogFont = &lf;
	choosefont.rgbColors = textCol;
	if (!ChooseFont(&choosefont))
		return;
	HFONT hf = CreateFontIndirect(&lf);
	if (hf) {
		g_hFont = hf;
		SendMessage(g_hEdit, WM_SETFONT, (WPARAM)g_hFont, TRUE);
	}
	textCol = choosefont.rgbColors;
}


LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
static int pos_x = 150, pos_y = 100, stretch_x = 1, stretch_y = 1, rotate_x = 0, x, y, z = 0;
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	PSTR szCmdLine, int iCmdShow)
{
	
	HWND        hwnd;
	MSG         msg;
	WNDCLASSEX  wndclass;
	WNDCLASS            wndClass;
	wndclass.cbSize = sizeof(wndclass);
	wndclass.style = CS_HREDRAW | CS_VREDRAW;
	wndclass.lpfnWndProc = WndProc;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.hInstance = hInstance;
	wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wndclass.lpszMenuName = NULL;
	wndclass.lpszClassName = L"Laboratorul 8";
	wndclass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	RegisterClassEx(&wndclass);
	HMENU hMenu = CreateMenu();
	HMENU hFileMenu = CreateMenu();
	HMENU hFormatMenu = CreateMenu();
	HMENU hEditMenu = CreateMenu();
	AppendMenu(hFileMenu, MF_STRING, IDM_FILE_NEW, L"&New");
	AppendMenu(hFileMenu, MF_STRING, IDM_FILE_OPEN, L"&Open");
	AppendMenu(hFileMenu, MF_STRING, IDM_FILE_SAVE, L"&Save");
	AppendMenu(hFileMenu, MF_STRING, IDM_FILE_SAVEAS, L"Save &As...");
	AppendMenu(hFileMenu, MF_SEPARATOR, 0, NULL);
	AppendMenu(hFileMenu, MF_STRING, IDM_FILE_EXIT, L"&Exit");
	AppendMenu(hMenu, MF_POPUP, (UINT_PTR)hFileMenu, L"&File");
	AppendMenu(hFormatMenu, MF_STRING, IDM_FORMAT_FONT, L"&Font...");
	AppendMenu(hMenu, MF_POPUP, (UINT_PTR)hEditMenu, L"&Edit");
	AppendMenu(hEditMenu, MF_STRING, IDM_EDIT_CUT, L"&Cut");
	AppendMenu(hEditMenu, MF_STRING, IDM_EDIT_COPY, L"&Copy");
	AppendMenu(hEditMenu, MF_STRING, IDM_EDIT_PASTE, L"&Paste");
	AppendMenu(hMenu, MF_POPUP, (UINT_PTR)hFormatMenu, L"F&ormat");
	AppendMenu(hMenu, MF_STRING, IDM_ABOUT, L"&About");
	hwnd = CreateWindow(L"Laboratorul 8",         // window class name
		L"Typer",     // window caption
		WS_OVERLAPPEDWINDOW,     // window style
		CW_USEDEFAULT,           // initial x position
		CW_USEDEFAULT,           // initial y position
		CW_USEDEFAULT,           // initial x size
		CW_USEDEFAULT,           // initial y size
		NULL,                    // parent window handle
		hMenu,                    // window menu handle
		hInstance,               // program instance handle
		NULL);		             // creation parameters
	g_hwnd = hwnd;
	ShowWindow(hwnd, iCmdShow);
	UpdateWindow(hwnd);
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	HDC         hdc;
	PAINTSTRUCT ps;
	RECT        rect;
	HBRUSH hbr;
	HFONT hFont;

	static HWND hEdit;
	switch (iMsg)
	{
	case WM_CREATE: {

		hEdit = CreateWindowEx(WS_EX_CLIENTEDGE, L"EDIT", L"",
			WS_CHILD | WS_VISIBLE | ES_LEFT | WS_VSCROLL | ES_MULTILINE | ES_AUTOVSCROLL,
			0, 0, 0, 0, hwnd, (HMENU)IDC_MAIN_EDIT, (HINSTANCE)GetWindowLong(hwnd, GWL_HINSTANCE), NULL);
		g_hEdit = hEdit;
		hFont = CreateFont(30, 0, 0, 0, FW_DONTCARE, FALSE, FALSE, FALSE, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, L"Arial");
		SendMessage(hEdit, WM_SETFONT, WPARAM(hFont), TRUE);
		if (hEdit == NULL)
			MessageBox(hwnd, L"Could not create edit box.", L"Error", MB_OK | MB_ICONERROR);

		return 0;
		break;
	}
	case WM_SETFOCUS: {
		SetFocus(hEdit);
		break;
	}

	case WM_CTLCOLOREDIT:
	{
		hbr = CreateSolidBrush(RGB(255, 255, 255));
		HDC hdc = (HDC)wParam;
		SetTextColor(hdc, textCol);
		return (LRESULT)hbr; /*this brush used by system to paint control background */
	}

	case WM_SIZE: {
		HFONT hFont;
		GetClientRect(hwnd, &rect);
		hEdit = GetDlgItem(hwnd, IDC_MAIN_EDIT);
		SetWindowPos(hEdit, NULL, 0, 0, rect.right, rect.bottom, SWP_NOZORDER);



	}

	case WM_PAINT: {
		break;
	}
	case WM_CLOSE: {
		DestroyWindow(hwnd);
		break;
	}
	case WM_COMMAND: {
		switch (LOWORD(wParam)) {
		case IDM_FILE_NEW: {
			SetWindowText(g_hEdit, TEXT(""));
			SetWindowText(g_hwnd, TEXT("Typer"));
		}
						   break;
		case IDM_FILE_OPEN: {
			LoadFileToEdit();
		}
							break;
		case IDM_FILE_SAVE: {

			if (isOpen)
				SaveTextFileFromEdit();
			else if (GetFileNameForSave())
				SaveTextFileFromEdit();

		}
							break;
		case IDM_FILE_SAVEAS: {
			if (GetFileNameForSave())
				SaveTextFileFromEdit();
		}
							  break;
		case IDM_FILE_EXIT: {
			DestroyWindow(hwnd);
			break;
		}
		case IDM_EDIT_CUT:
			SendMessage(g_hEdit, WM_CUT, 0, 0);
			break;
		case IDM_EDIT_COPY:
			SendMessage(g_hEdit, WM_COPY, 0, 0);
			break;
		case IDM_EDIT_PASTE:
			SendMessage(g_hEdit, WM_PASTE, 0, 0);
			break;
		case IDM_FORMAT_FONT: {
			ChooseFontForEdit();
			break;
		}
		case IDM_ABOUT: {
			MessageBox(hwnd, L"Typer By Valentin. 2017.",
				L"Typer", MB_ICONINFORMATION | MB_OK);
			break;
		}
		default:
			return DefWindowProc(hwnd, iMsg, wParam, lParam);
			break;


		}
		break;
	}
	case WM_MOUSEMOVE:
		break;
		return 0;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}
	return DefWindowProc(hwnd, iMsg, wParam, lParam);
}
