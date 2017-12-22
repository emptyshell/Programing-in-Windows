
#include <windows.h>
#include "stdafx.h"
#include <math.h>
#include <Unknwn.h>
#include <objidl.h>
#include <gdiplus.h>


#pragma comment(lib, "Winmm.lib")
#pragma comment(lib,"gdiplus.lib")






using namespace Gdiplus;
using namespace std;

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
int pos_x = 150, pos_y = 100, stretch_x = 1, stretch_y = 1, rotate_x = 0, x, y, z = 0;
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	PSTR szCmdLine, int iCmdShow)
{
	
	HWND        hwnd;
	MSG         msg;
	WNDCLASSEX  wndclass;
	WNDCLASS            wndClass;
	GdiplusStartupInput gdiplusStartupInput;
	ULONG_PTR           gdiplusToken;

	GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);
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
	wndclass.lpszClassName = L"Laboratorul 4";
	wndclass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	RegisterClassEx(&wndclass);
	hwnd = CreateWindow(L"Laboratorul 4",         // window class name
		L"Labroratorul nr.4 la PW",     // window caption
		WS_OVERLAPPEDWINDOW,     // window style
		CW_USEDEFAULT,           // initial x position
		CW_USEDEFAULT,           // initial y position
		CW_USEDEFAULT,           // initial x size
		CW_USEDEFAULT,           // initial y size
		NULL,                    // parent window handle
		NULL,                    // window menu handle
		hInstance,               // program instance handle
		NULL);		             // creation parameters
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
	HDC hMemDC;
	PAINTSTRUCT ps;
	RECT        rect;
	HPEN hPen;
	HBRUSH hBrush;

	switch (iMsg)
	{
	case WM_CREATE: {

		return 0;
	}
	case WM_KEYDOWN:
	{
		switch (wParam)
		{
		case VK_RIGHT:
		{
			pos_x = pos_x + 10;
			InvalidateRect(hwnd, NULL, TRUE);

			break;
		}
		case VK_LEFT:
		{
			pos_x = pos_x - 10;
			InvalidateRect(hwnd, NULL, TRUE);
			break;
		}
		case VK_UP:
		{
			pos_y = pos_y - 10;
			InvalidateRect(hwnd, NULL, TRUE);
			break;
		}
		case VK_DOWN:
		{
			pos_y = pos_y + 10;
			InvalidateRect(hwnd, NULL, TRUE);
			break;
		}
		case VK_END:
		{
			rotate_x -= 45;
			InvalidateRect(hwnd, NULL, TRUE);
			break;
		}
		case VK_NEXT:
		{
			rotate_x += 45;
			InvalidateRect(hwnd, NULL, TRUE);
			break;
		}
		}
		break;
	}
	case WM_PAINT: {
		hdc = BeginPaint(hwnd, &ps);
		GetClientRect(hwnd, &rect);
		DrawText(hdc, L"Controlarea imaginii conform tastaturii", -1, &rect,
			DT_SINGLELINE | DT_CENTER);
		rect.top = 20;
		DrawText(hdc, L"Control Keys(Up,Down,Left,Right) & End(Rotate left) & Page Down(Rotate right)", -1, &rect,
			DT_SINGLELINE | DT_CENTER);
		//Draw image
		Graphics graphics(hdc);
		ImageAttributes IAttr;
		RectF destination(25, 80, rect.right, rect.bottom);
		Image image(L"BMP.bmp");
		graphics.TranslateTransform(pos_x, pos_y + 100);
		graphics.RotateTransform(rotate_x);
		graphics.TranslateTransform(-170, -220);
		graphics.ScaleTransform(stretch_x, stretch_y);
		graphics.DrawImage(&image, destination, 0, 0, 1200, 600, UnitPixel);
		EndPaint(hwnd, &ps);
		return 0;
	}

	case WM_DESTROY:

		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hwnd, iMsg, wParam, lParam);
}
