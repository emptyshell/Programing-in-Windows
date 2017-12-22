#include <windows.h>
#include "stdafx.h"
#include <math.h>
#include <Unknwn.h>
#include <objidl.h>
#include <gdiplus.h>
//#include <gdiplusflat.h>
#pragma comment(lib, "Winmm.lib")
#pragma comment(lib,"gdiplus.lib")
using namespace Gdiplus;
using namespace std;

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
static int pos_x = 150, pos_y = 100, stretch_x = 1, stretch_y = 1, rotate_x = 0, x, y, z = 0;
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
	wndclass.lpszClassName = L"Laboratorul 5";
	wndclass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	RegisterClassEx(&wndclass);
	hwnd = CreateWindow(L"Laboratorul 5",         // window class name
		L"Labroratorul nr.5 la PW",     // window caption
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
	HPEN hPen = CreatePen(PS_SOLID, 3, RGB(150, 100, 205));
	HBRUSH hBrush;
	static POINT PT_fn[4] = { { 150,300 },{ 250,0 },{ 400,700 },{ 450,200 } };
	switch (iMsg)
	{
	case WM_CREATE: {

		return 0;
	}
	case WM_PAINT: {


		hdc = BeginPaint(hwnd, &ps);
		GetClientRect(hwnd, &rect);
		DrawText(hdc, L"Controlarea curbei Bezier si imaginii cu ajutorul Mouse-ului", -1, &rect, DT_SINGLELINE | DT_CENTER);
		SelectObject(hdc, hPen);
		MoveToEx(hdc, rect.right / 2, 40, NULL);
		LineTo(hdc, rect.right / 2, rect.bottom);
		//Bezier
		PolyBezier(hdc, PT_fn, 4);
		//Draw image
		Graphics graphics(hdc);
		ImageAttributes IAttr;
		RectF destination(25, 80, rect.right, rect.bottom);
		Image image(L"BMP.bmp");
		graphics.TranslateTransform(pos_x + rect.right / 2+rect.right / 4, pos_y + rect.bottom/ 2);
		graphics.RotateTransform(rotate_x);
		graphics.TranslateTransform(-170, -220);
		graphics.ScaleTransform(stretch_x, stretch_y);
		graphics.DrawImage(&image, destination, 0, 0, 1200, 600, UnitPixel);
		EndPaint(hwnd, &ps);
		break;
	}
	case WM_MOUSEMOVE: {
		if (wParam & MK_LBUTTON || wParam & MK_RBUTTON) {
			hdc = GetDC(hwnd);
			GetClientRect(hwnd, &rect);
			SelectObject(hdc, hPen);
			PolyBezier(hdc, PT_fn, 4);

			if (wParam & MK_LBUTTON) {
				PT_fn[1].x = LOWORD(lParam);
				PT_fn[1].y = HIWORD(lParam);
				rect.right = rect.right / 2;
				InvalidateRect(hwnd, &rect, TRUE);
				UpdateWindow(hwnd);

			}
			if (wParam & MK_RBUTTON) {
				pos_x = LOWORD(lParam) - rect.right /1.5;
				pos_y = HIWORD(lParam) - 250;
				InvalidateRect(hwnd, NULL, TRUE);
				UpdateWindow(hwnd);
			}
			SelectObject(hdc, hPen);
			PolyBezier(hdc, PT_fn, 4);

		}}
					   break;
					   return 0;

	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hwnd, iMsg, wParam, lParam);
}