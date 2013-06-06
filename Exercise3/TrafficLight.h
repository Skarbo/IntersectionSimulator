#pragma once

#include "stdafx.h"
#include "Draw.h"

class TrafficLight {
public: 

	// VARIABLES

	void setState(int s) { this->state = s; }
	int getState() { return this->state; }
	void incState() { this->state = ((this->state+1) % 4); }

	// CONSTRUCT

	TrafficLight() : state(STATE_RED) {}

	// FUNCTIONS

	void draw(HDC hdc, int x, int y, int height);
	static int getWidth(int height) { return (int) (height * 0.35); }

	// CONSTANTS

	const static int STATE_RED = 0,
		STATE_RED_YELLOW = 1,
		STATE_GREEN = 2,
		STATE_YELLOW = 3;

private:

	int state;

};