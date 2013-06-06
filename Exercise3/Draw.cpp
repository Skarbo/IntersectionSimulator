#include "stdafx.h"
#include "Draw.h"

void Draw::rectangle(HDC hdc, int x, int y, int width, int height, COLORREF color) {

	//HPEN hPen;
	HBRUSH hBrush;
	HGDIOBJ hOrg;

	// Select brush 
	hBrush = CreateSolidBrush(color); 
	hOrg = SelectObject(hdc, hBrush); 
	//hPen = CreatePen(PS_NULL, 0, color); //CreateSolidBrush(color); 
	//hOrg = SelectObject(hdc, hPen); 

	// Rectangle
	Rectangle(hdc, x, y, x+width, y+height);

	// Reset original brush 
	SelectObject(hdc, hOrg); 
	DeleteObject(hBrush);
	//DeleteObject(hPen);

}

void Draw::circle(HDC hdc, int x, int y, int radius, COLORREF color) {

	HBRUSH hBrush;
	HGDIOBJ hOrg;

	// Select brush 
	hBrush = CreateSolidBrush(color); 
	hOrg = SelectObject(hdc, hBrush); 

	// Circle 
	Ellipse(hdc, x, y, (int) x + (radius * 2), (int) y + (radius * 2)); 

	// Reset original brush 
	SelectObject(hdc, hOrg); 
	DeleteObject(hBrush);

};

void Draw::line(HDC hdc, int x_start, int y_start, int x_end, int y_end) {

	MoveToEx(hdc, x_start, y_start, 0);
	LineTo(hdc, x_end, y_end);

};

void Draw::box(HDC hdc, int x, int y, int height, int width) {

	// Left side
	Draw::line(hdc, x, y, x, y+height);

	// Top side
	Draw::line(hdc, x, y, x+width, y);

	// Right side
	Draw::line(hdc, x+width, y, x+width, y+height);

	// Bottom side
	Draw::line(hdc, x, y+height, x+width, y+height);

};

void Draw::repeatBitmap(HDC hdc, Bitmap bitmap, int x, int y, int width, int height) {

	// Load Bitmap
	HBITMAP bmpExercising = LoadBitmap(GetModuleHandle(NULL), MAKEINTRESOURCE(bitmap.getBitmap()));

	// Create a memory device
	HDC MemDCExercising = CreateCompatibleDC(hdc);

	// Select the new bitmap
	SelectObject(MemDCExercising, bmpExercising);

	int bitmap_height = bitmap.getHeight(), 
		bitmap_width = bitmap.getWidth();

	for(int i = 0; i < (int) ceil((double) width/bitmap_width); i++) {

		for(int j = 0; j < (int) ceil((double) height/bitmap_height); j++) {

			// Calculate x, y, width and height destination
			int x_dest = (i * bitmap_width) + x,
				y_dest = (j * bitmap_height) + y,
				w_dest = x_dest + bitmap_width,
				h_dest = y_dest + bitmap_height;

			// Set bitmap new with
			int bitmap_width_new = bitmap_width,
				bitmap_height_new = bitmap_height;

			// 
			if (width > bitmap_width) {
				if (w_dest > width) {
					bitmap_width_new -= w_dest - width;
				}
			}
			else {
				bitmap_width_new = width;
			}
			if (height > bitmap_height) {
				if (h_dest > height) {
					bitmap_height_new -= h_dest - height;
				}
			}
			else {
				bitmap_height_new = height;
			}

			// Copy BMP to hdc
			StretchBlt(hdc, x_dest, y_dest, bitmap_width_new, bitmap_height_new, MemDCExercising, 0, 0, bitmap_width_new, bitmap_height_new, SRCCOPY);

		}

	}

	// Restore the old bitmap
	DeleteDC(MemDCExercising);
	DeleteObject(bmpExercising);

}