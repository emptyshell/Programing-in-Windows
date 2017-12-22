#include <windows.h>
#include <math.h>
#include "stdafx.h"
#include <cmath>
#pragma comment(lib, "Winmm.lib")

HBITMAP bitmap;
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	PSTR szCmdLine, int iCmdShow)
{
	
	HWND        hwnd;
	MSG         msg;
	WNDCLASSEX  wndclass;
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
	wndclass.lpszClassName = L"Laboratorul 3";
	wndclass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	RegisterClassEx(&wndclass);
	hwnd = CreateWindow(L"Laboratorul 3",         // window class name
		L"Labroratorul nr.3 la PW",     // window caption
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
	POINT Pt[7] = { { 200,100 },{ 250,300 },{ 300,300 },{ 350,500 },{ 400,300 },{ 450,300 },{ 500,100 } };
	POINT PT_fn[4] = { { 150,400 },{ 250,100 },{ 400,300 },{ 450,100 } };

	double t;
	double i;
	int x;
	int y;
	switch (iMsg)
	{
	case WM_CREATE:
		return 0;
	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);
		GetClientRect(hwnd, &rect);
		hPen = CreatePen(PS_SOLID, 3, RGB(150, 100, 205));
		hBrush = CreateSolidBrush(RGB(0, 150, 150));

		//Draw text
		rect.left = 220;
		rect.top = 70;
		DrawText(hdc, L"Curba Bezier utilizind functia standart", -1, &rect,
			DT_SINGLELINE);

		//Draw Bezier using standard
		SelectObject(hdc, hPen);
		PolyBezier(hdc, PT_fn, 4);

		//Draw Bezier using functions
		rect.left = 720;
		rect.top = 70;
		DrawText(hdc, L"Curba Bezier utilizind formula", -1, &rect,
			DT_SINGLELINE);
		MoveToEx(hdc, PT_fn[0].x + 500, PT_fn[0].y, NULL);
		for (t = 0; t<1; t = t + 0.000005) {
			x = pow((1 - t), 3) * PT_fn[0].x + 3 * t*pow((1 - t), 2) * PT_fn[1].x + 3 * t*t*(1 - t)*PT_fn[2].x + t*t*t*PT_fn[3].x;
			y = pow((1 - t), 3) * PT_fn[0].y + 3 * t*pow((1 - t), 2) * PT_fn[1].y + 3 * t*t*(1 - t)*PT_fn[2].y + t*t*t*PT_fn[3].y;
			LineTo(hdc, x + 500, y);
		}
		//end------------------------

		EndPaint(hwnd, &ps);
		return 0;
	case WM_DESTROY:

		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hwnd, iMsg, wParam, lParam);
}