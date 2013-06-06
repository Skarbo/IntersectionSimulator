#pragma once

#include "stdafx.h"
#include "Resource.h"
#include "Draw.h"
#include "TrafficLight.h"
#include "Car.h"
#include "Bitmap.h"

class Intersection {
public:

	// VARIABLES

	const static int STATE_NORTH_SOUTH = 0,
		STATE_EAST_WEST = 1;

	// CONSTRUCT

	Intersection();

	// FUNCTIONS

	// ... GETTERS/SETTERS

	void setState(int state) { this->state = state; }
	int getState() { return this->state; }

	void setDirection(int direction) { this->direction = direction; }
	int getDirection() { return direction; }

	void setSize(int size) { this->size = size; }
	int getSize() { return size; }

	void setX(int x) { this->state = x; }
	int getX() { return x; }

	void setY(int y) { this->y = y; }
	int getY() { return y; }

	// ... /GETTERS/SETTERS

	void draw(HDC hdc);
	void incStates();

	//	GETTERS

	POINT getRoadStart(int direction);
	POINT getRoadEnd(int direction);
	POINT getIntersection(int direction);

	TrafficLight getTrafficLight(int direction) { return this->traffic_lights[direction]; }

	//	/GETTERS

	static int getRoadWidth(int size) { return (int) ((size / 2) - (int) (size * 0.41)); };
	static int getRoadHeight(int size) { return size; };

private:

	// VARIABLES

	TrafficLight traffic_lights[4];

	int state,
		direction,
		size,
		x,
		y;

	// FUNCTIONS

	void drawIntersection(HDC hdc);
	void drawBackground(HDC hdc);

};