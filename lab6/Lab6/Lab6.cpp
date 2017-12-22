#include <windows.h>
#include "stdafx.h"
#include <math.h>
#include <Unknwn.h>
#include <objidl.h>
#include <gdiplus.h>
#include <string>
#include <iostream>
#include <iomanip>
#include <ctime>
#include <time.h>
#include <atlbase.h>
#include <atlconv.h>
#include "atlbase.h"

#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable : 4996)
//#include <gdiplusflat.h>
#pragma comment(lib, "Winmm.lib")
#pragma comment(lib,"gdiplus.lib")
using namespace Gdiplus;
using namespace std;
void Rotate_Sec(double deg90InRad);
void Rotate_Min(double deg90InRad);
void Rotate_Hour(double deg90InRad);
void Create_clock(HWND hwnd, HDC hdc, PAINTSTRUCT ps, RECT rect);
const UINT ID_TIMER_SEC = 1;
const UINT ID_TIMER_MIN = 2;
const UINT ID_TIMER_HOUR = 3;
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

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
	wndclass.lpszClassName = L"Laboratorul 6";
	wndclass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	RegisterClassEx(&wndclass);
	hwnd = CreateWindow(L"Laboratorul 6",         // window class name
		L"Labroratorul nr.6 la PW",     // window caption
		WS_OVERLAPPEDWINDOW,     // window style
		CW_USEDEFAULT,           // initial x position
		CW_USEDEFAULT,           // initial y position
		1400,           // initial x size
		850,           // initial y size
		NULL,                    // parent window handle
		NULL,                    // window menu handle
		hInstance,               // program instance handle
		NULL);                   // creation parameters
	ShowWindow(hwnd, iCmdShow);
	UpdateWindow(hwnd);
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;
}
bool clock_make = false;
int i = 0;
static double deg90InRad = 3.14159265358979324 / 30;
bool make_once_sec = false;
bool make_once_min = false;
bool make_once_h = false;
//--move seconds//
double startX = 700, startY = 450.0;
double sec_endX = 700.0, sec_endY = 180.0;
double const_sec_endX = 700.0, const_sec_endY = 180.0;

double sec_endX_old = 700.0, sec_endY_old = 180.0;

//--move minutes//
double min_endX = 700.0, min_endY = 210.0;
double const_min_endX = 700.0, const_min_endY = 210.0;

double min_endX_old = 700.0, min_endY_old = 210.0;
//--move hours//
double h_endX = 700.0, h_endY = 280.0;
double const_h_endX = 700.0, const_h_endY = 280.0;

double h_endX_old = 700.0, h_endY_old = 280.0;

//------------------------------

double x, y, x2, y2;
LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	HDC         hdc;
	PAINTSTRUCT ps;
	RECT        rect;
	HPEN hPenSec = CreatePen(PS_SOLID, 1, RGB(0, 0, 150));
	HPEN hPenSecErase = CreatePen(PS_SOLID, 1, RGB(255, 255, 255));
	HPEN hPenMin = CreatePen(PS_SOLID, 3, RGB(0, 0, 0));
	HPEN hPenMinErase = CreatePen(PS_SOLID, 3, RGB(255, 255, 255));
	HPEN hPenHour = CreatePen(PS_SOLID, 7, RGB(0, 0, 0));
	HPEN hPenHourErase = CreatePen(PS_SOLID, 7, RGB(255, 255, 255));
	HFONT font = CreateFont(100, 0, 0, 0, 300, false, false, false, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, L"Arial");
	time_t rawtime = time(0);
	struct tm timeinfo;
	char buffer[80];
	char seconds[80];
	char minutes[80];
	char hours[80];
	time(&rawtime);
	localtime_s(&timeinfo, &rawtime);
	strftime(buffer, sizeof(buffer), "%H:%M:%S", &timeinfo);
	strftime(seconds, sizeof(seconds), "%S", &timeinfo);
	strftime(minutes, sizeof(minutes), "%M", &timeinfo);
	strftime(hours, sizeof(hours), "%H", &timeinfo);
	string str(buffer);
	string str_seconds(seconds);
	string str_minutes(minutes);
	string str_hours(hours);
	CA2W unicodeStr(str.c_str());
	switch (iMsg)
	{
	case WM_CREATE: {
		SetTimer(hwnd, ID_TIMER_SEC, 300, (TIMERPROC)NULL);
		return 0;
	}
	case WM_PAINT: {


		hdc = BeginPaint(hwnd, &ps);
		KillTimer(hwnd, ID_TIMER_SEC);

		SelectObject(hdc, font);
		GetClientRect(hwnd, &rect);
		
		DrawText(hdc, unicodeStr, -1, &rect, DT_SINGLELINE | DT_CENTER);
		
		//Create Clock Panel
		Create_clock(hwnd, hdc, ps, rect);
		//FillRect(hdc, &rect, (HBRUSH)(COLOR_WINDOW + 1));
		//Seconds Line-----------------------------------
		
		double temp;
		temp = atoi(str_seconds.c_str());
		while (temp > 0) {
			Rotate_Sec(deg90InRad);
			temp--;
		}
		SelectObject(hdc, hPenSecErase);
		MoveToEx(hdc, startX, startY, NULL);
		LineTo(hdc, sec_endX_old, sec_endY_old);

		SelectObject(hdc, hPenSec);
		MoveToEx(hdc, startX, startY, NULL);
		LineTo(hdc, sec_endX, sec_endY);

		sec_endX = const_sec_endX;
		sec_endY = const_sec_endY;
		//Minutes Line--------------------------------------------
		
		temp = atoi(str_minutes.c_str());
		while (temp > 0) {
			Rotate_Min(deg90InRad);
			temp--;
		}

		SelectObject(hdc, hPenMinErase);
		MoveToEx(hdc, startX, startY, NULL);
		LineTo(hdc, min_endX_old, min_endY_old);

		SelectObject(hdc, hPenMin);
		MoveToEx(hdc, startX, startY, NULL);
		LineTo(hdc, min_endX, min_endY);

		min_endX = const_min_endX;
		min_endY = const_min_endY;
		//END MINUTES LINE -----------------------------------------
		//Hour Line-------------------------------------------------
		temp = atoi(str_hours.c_str());
		if (temp >12) temp = temp - 12;
		while (temp > 0) {
			Rotate_Hour(deg90InRad * 5);
			temp--;
		}
		SelectObject(hdc, hPenHourErase);
		MoveToEx(hdc, startX, startY, NULL);
		LineTo(hdc, h_endX_old, h_endY_old);

		SelectObject(hdc, hPenHour);
		MoveToEx(hdc, startX, startY, NULL);
		LineTo(hdc, h_endX, h_endY);
		
		h_endX = const_h_endX;
		h_endY = const_h_endY;
		DeleteObject(font);
		DeleteObject(hPenSec);
		DeleteObject(hPenMin);
		DeleteObject(hPenHour);
		ReleaseDC(hwnd, hdc);
		SetTimer(hwnd, ID_TIMER_SEC, 300, (TIMERPROC)NULL);
		EndPaint(hwnd, &ps);
		
		return 0;
	}
	case WM_TIMER: {
		switch (wParam) {
		case ID_TIMER_SEC: {

			InvalidateRect(hwnd, NULL, FALSE);
			UpdateWindow(hwnd);

			return 0;
		}
		}}
	case WM_DESTROY:
		KillTimer(hwnd, ID_TIMER_SEC);
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hwnd, iMsg, wParam, lParam);
}
void Rotate_Sec(double deg90InRad) {
	x = sec_endX;
	y = sec_endY;
	sec_endX_old = sec_endX;
	sec_endY_old = sec_endY;
	x -= startX;
	y -= startY;
	sec_endX = (x * cos(deg90InRad)) - (y * sin(deg90InRad));
	sec_endY = (x * sin(deg90InRad)) + (y * cos(deg90InRad));
	sec_endX += startX;
	sec_endY += startY;
}

void Rotate_Min(double deg90InRad) {
	x = min_endX;
	y = min_endY;
	min_endX_old = min_endX;
	min_endY_old = min_endY;
	x -= startX;
	y -= startY;
	min_endX = (x * cos(deg90InRad)) - (y * sin(deg90InRad));
	min_endY = (x * sin(deg90InRad)) + (y * cos(deg90InRad));
	min_endX += startX;
	min_endY += startY;
}
void Rotate_Hour(double deg90InRad) {
	x = h_endX;
	y = h_endY;
	h_endX_old = h_endX;
	h_endX_old = h_endX;
	x -= startX;
	y -= startY;
	h_endX = (x * cos(deg90InRad)) - (y * sin(deg90InRad));
	h_endY = (x * sin(deg90InRad)) + (y * cos(deg90InRad));
	h_endX += startX;
	h_endY += startY;
}
void Create_clock(HWND hwnd, HDC hdc, PAINTSTRUCT ps, RECT rect) {
	Graphics graphics(hdc);
	Image image(L"clock.png");
	graphics.DrawImage(&image, 360, 110, 680, 680);
	
}


