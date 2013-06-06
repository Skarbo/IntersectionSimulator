#pragma once

#include "math.h"
#include "stdafx.h"
#include "Resource.h"
#include "Draw.h"
#include "TrafficLight.h"

class Car {
public: 

	// VARIABLES

	const static int TYPE_BLUE = 0,
		TYPE_RED = 1,
		TYPE_GREEN = 2;

	const static int BITMAP_CARS = IDB_CARS;

	const static int STATE_WAITING = 0,
		STATE_DRIVING = 1,
		STATE_STOPPED_QUE = 2,
		STATE_STOPPED_INTERSECTION = 3,
		STATE_OUT_OF_BOUND = 4;

	const static int BITMAP_DO = 0;

	/** In procent of car length */
	const static int DISTANCE = 30;

	// CONSTRUCT

	Car() {};

	// FUNCTIONS

	// ... GETTERS/SETTERS

	void setDirection(int d) { direction = d; }
	int getDirection() { return direction; }

	void setType(int t) { type = t; }
	int getType() { return type; }

	void setSpeed(int s) { speed = s; }
	int getSpeed() { return speed; }

	void setWidth(int w) { width = w; }
	int getWidth() { return width; }

	int getLength() { return Car::getStretchedLength(width); }

	void setState(int s) { state = s; }
	int getState() { return state; }

	void setColor(COLORREF color) { this->color = color; }
	COLORREF getColor() { return this->color; }

	// ... /GETTERS/SETTESR

	// ... IS

	bool isStateDriving() { return (this->state == STATE_DRIVING); }
	bool isStateOutOfBound() { return (this->state == STATE_OUT_OF_BOUND); }
	bool isStateStoppedQue() { return (this->state == STATE_STOPPED_QUE); }
	bool isStateStoppedIntersection() { return (this->state == STATE_STOPPED_INTERSECTION); }
	bool isStateLegal() { return (this->isStateDriving() || this->isStateOutOfBound() || this->isStateStoppedQue() || this->isStateStoppedIntersection()); }

	// ... /IS

	// ... POINTS

	POINT getAt() { return at; };
	void setAt(POINT const a) { at = a; }

	POINT getStart() { return start; }
	void setStart(POINT const s) { start = s; }

	POINT getStop() { return stop; }
	void setStop(POINT const s) { stop = s; }

	POINT getIntersection() { return intersection; }
	void setIntersection(POINT const i) { intersection = i; }

	POINT getBehind();

	// ... /POINTS

	//	DO

	void doDraw(HDC hdc);
	void doDrive(Car car_infront, int traffic_light_state);

	//	/DO

	//	IS

	bool isOutOfBound();
	bool isStopIntersection(POINT at_new);
	bool isStopQue(Car car_infront, POINT at_new);

	//	/IS

	//	STRING

	static int getStretchedWidth(int road_width) { return (int) ((road_width / 2) * 0.95); }
	static int getStretchedLength(int car_width) { return (int) ((double) car_width * ((double) 396 / (double) (592 / 3))); }

	static int absDiff(const int a, const int b);

	//	/STRING

private:

	// VARIABLES

	int direction,
		type,
		width,
		speed,
		state;

	POINT start,
		stop,
		at,
		intersection;

	COLORREF color;

	// FUNCTIONS

};