#pragma once

#include "stdafx.h"

class Bitmap {
public: 

	// VARIABLES

	// CONSTRUCT
	Bitmap(int bitmap, int width, int height) : bitmap(bitmap), width(width), height(height) {  };

	// FUNCTIONS
	int getBitmap() { return this->bitmap; }
	int getHeight() { return this->height; }
	int getWidth() { return this->width; }

private:

	// VARIABLES

	int bitmap,
		height,
		width;

	// FUNCTIONS

};