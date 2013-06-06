#pragma once

#include "stdafx.h"
#include <math.h>
#include "Resource.h"
#include "Bitmap.h"

class Draw {
public: 
	
	static void rectangle(HDC hdc, int x, int y, int width, int height, COLORREF color);
	static void circle(HDC hdc, int x, int y, int radius, COLORREF color);
	static void line(HDC hdc, int x_start, int y_start, int x_end, int y_end);
	static void box(HDC hdc, int x, int y, int height, int width);
	static void repeatBitmap(HDC hdc, Bitmap bitmap, int x, int y, int width, int height);

	const static COLORREF COLOR_RED = RGB(255,0,0), 
		COLOR_YELLOW = RGB(255,255,0),
		COLOR_GREEN = RGB(0,255,0),
		COLOR_GRAY = RGB(100,100,100),
		COLOR_WHITE = RGB(255,255,255),
		COLOR_ASPHALT = RGB(200,200,200);

};