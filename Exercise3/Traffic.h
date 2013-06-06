#pragma once

#include "stdafx.h"
#include "Intersection.h"
#include "Car.h"
#include <vector>
using namespace std;

static double TRAFFIC_SPEED_RATE_SLOW = 0.004,
	TRAFFIC_SPEED_RATE_NORMAL = 0.005,
	TRAFFIC_SPEED_RATE_FAST = 0.002;

class Traffic {
public: 

	// VARIABLES

	const static int SPEED_RATE_SLOW = 0,
		SPEED_RATE_NORMAL = 1,
		SPEED_RATE_FAST = 2;

	const static int DRIVE_ON_YELLOW = 0;
	const static int SHOW_STATS = 1;
	const static int PROBABILITY_DO = 1;

	// CONSTRUCT

	Traffic() {};

	// FUNCTIONS

	void initIntersection();
	void doBreakpoint();
	void draw(HDC hdc);
	void doDrawStats(HDC hdc);

	// ... GETTERS/SETTERS

	int getX() { return x; }
	void setX(int x) { this->x = x; }

	int getY() { return y; }
	void setY(int y) { this->y = y; }

	int getSize() { return size; }
	void setSize(int s) { size = s; }

	int getSpeedRate() { return speed_rate; }
	void setSpeedRate(int r) { speed_rate = r; }

	int getCarsCount(int direction);
	int getCarsCount(int direction, int car_state);

	void incProbability(int direction, int number);
	void decProbability(int direction, int number);
	int getProbability(int direction) { return this->probability[direction]; }

	// ... /GETTERS/SETTERS

	// ... DO

	void doDrive();
	void doIncreaseTrafficLight() {	this->intersection.incStates(); }
	void doAddCar(int direction);

	// ... /DO

private:

	// VARIABLES

	Intersection intersection;

	int probability[4];

	int x,
		y,
		size,
		speed_rate;

	vector<Car> cars[4];

	// FUNCTIONS

};