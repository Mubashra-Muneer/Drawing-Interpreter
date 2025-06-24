#include <windows.h>
#include <cmath>
void gotoxy(int x, int y)
{
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);

}

void myLine(int x1, int y1, int x2, int y2, int color) //use three 3 integers if you want colored lines.
{
	HWND console_handle = GetConsoleWindow();
	HDC device_context = GetDC(console_handle);

	//change the color by changing the values in RGB (from 0-255) to get shades of gray. For other colors use 3 integers for colors.
	HPEN pen = CreatePen(PS_SOLID, 2, RGB(255, 255, 255)); //2 is the width of the pen
	SelectObject(device_context, pen);
	MoveToEx(device_context, x1, y1, NULL);
	LineTo(device_context, x2, y2);
	ReleaseDC(console_handle, device_context);
	DeleteObject(pen);

}
void myLine3(int x1, int y1, int x2, int y2, int color, int width) {
	HWND console_handle = GetConsoleWindow();
	HDC device_context = GetDC(console_handle);
	int R = 0;
	int G = 0;
	int B = 0;
	if(color == 0)
	{
		R = 0 ;
		G = 0 ;
		B = 0 ;
	}
	else if(color == 1)
	{
		R = 255 ;
	}
	else if(color == 2)
	{
		G = 255 ;
	}
	else if(color == 3)
	{
		B = 255 ;
	}
	else
	{
		R = 255 ;
		G = 255 ;
		B = 255 ;
	}
	//change the color by changing the values in RGB (from 0-255) to get shades of gray. For other colors use 3 integers for colors.
	HPEN pen = CreatePen(PS_SOLID, width, RGB(R, G, B));
	SelectObject(device_context, pen);
	MoveToEx(device_context, x1, y1, NULL);
	LineTo(device_context, x2, y2);
	ReleaseDC(console_handle, device_context);
	DeleteObject(pen);
}



void myRectangle(int x1, int y1, int x2, int y2, int R, int G, int B)
{
	HWND console_handle = GetConsoleWindow();
	HDC device_context = GetDC(console_handle);

	//change the color by changing the values in RGB (from 0-255)
	HPEN pen = CreatePen(PS_SOLID, 2, RGB(R, G, B));
	SelectObject(device_context, pen);
	HBRUSH brush = ::CreateSolidBrush(RGB(0, 0, 0)); //Fill color can also be passed as parameter to the function!!!

	SelectObject(device_context, brush);

	Rectangle(device_context, x1, y1, x2, y2);
	ReleaseDC(console_handle, device_context);
	DeleteObject(pen);
	DeleteObject(brush);
}
void myEllipse(int x1, int y1, int x2, int y2, int color, int width) {
	HWND console_handle = GetConsoleWindow();
	HDC device_context = GetDC(console_handle);
	int R = 0;
	int G = 0;
	int B = 0;
	if(color == 0)
	{
		R = 0 ;
		G = 0 ;
		B = 0;
	}
	else if(color == 1)
	{
		R = 255 ;
	}
	else if(color == 2)
	{
		G = 255 ;
	}
	else if(color == 3)
	{
		B = 255 ;
	}
	else
	{
		R = 255 ;
		G = 255 ;
		B = 255 ;
	}

	// Change the color by changing the values in RGB (from 0-255)
	HPEN pen = CreatePen(PS_SOLID, width, RGB(R, G, B));
	SelectObject(device_context, pen);
	HBRUSH brush = ::CreateSolidBrush(RGB(0, 0, 0));  // Fill color is black
	SelectObject(device_context, brush);

	Ellipse(device_context, x1, y1, x2, y2);

	ReleaseDC(console_handle, device_context);
	DeleteObject(pen);
	DeleteObject(brush);
}
