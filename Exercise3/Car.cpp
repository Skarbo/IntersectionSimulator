#include "stdafx.h"
#include "Traffic.h"
#include "Car.h"

void Car::doDraw(HDC hdc) {

	int x = this->getAt().x;
	int y = this->getAt().y;
	int width = this->getWidth();

	// Calculate car width and height
	int car_width_max = 592;
	int car_width = (int) (car_width_max / 3);
	int car_length = 396;

	int car_stretched_width = width;
	int car_stretched_length = (int) ((double) car_stretched_width * ((double) car_length / (double) car_width));

	//	CHANGE X AND Y ACCORDING TO DIRECTION

	switch(this->direction) {

		case STATE_NORTH:
			break;

		case STATE_WEST:
			y -= car_stretched_width;
			break;

		case STATE_SOUTH:
			x -= car_stretched_width;
			y -= car_stretched_length;
			break;

		case STATE_EAST:
			x -= car_stretched_length;
			break;

	}

	//	/CHANGE X AND Y ACCORDING TO DIRECTION

	//	DONT DRAW BITMAPS

	if (this->BITMAP_DO == 0) {

		int rectangle_width = 0,
			rectangle_length = 0;

		switch(this->direction) {
		
			case STATE_NORTH:
			case STATE_SOUTH:
				rectangle_width = car_stretched_width;
				rectangle_length = car_stretched_length;
				break;

			case STATE_EAST:
			case STATE_WEST:
				rectangle_length = car_stretched_width;
				rectangle_width = car_stretched_length;
				break;

		}

		Draw::rectangle(hdc, x, y, rectangle_width, rectangle_length, this->getColor());

		
		WCHAR sz[100];
		wsprintf(sz, _T("%d"), this->getSpeed());
		TextOutW(hdc, x+1, y+1, sz, wcslen(sz));

		return;

	}

	//	/DONT DRAW BITMAPS

	//	LOAD CARS

	// Load bitmap cars
	HBITMAP bmpCars = LoadBitmap(GetModuleHandle(NULL), MAKEINTRESOURCE(this->BITMAP_CARS));

	// Create a memory device for bitmap cars
	HDC MemDCBmpCars = CreateCompatibleDC(hdc);

	// Select bitmap cars to bitmap cars DC
	SelectObject(MemDCBmpCars, bmpCars);

	//	LOAD CARS

	//	ROTATE

	// Calculate the rotation points
	POINT rotate_points[3];
	switch(this->direction) {

		case STATE_NORTH:
			rotate_points[0].x = 0;	// TL
			rotate_points[0].y = 0;
			rotate_points[1].x = 0;	// TR
			rotate_points[1].y = car_length;
			rotate_points[2].x = car_width_max;	// BL
			rotate_points[2].y = 0;
			break;

		case STATE_SOUTH:
			rotate_points[0].x = 0;	// TL
			rotate_points[0].y = car_length;
			rotate_points[1].x = 0;	// TR
			rotate_points[1].y = 0;
			rotate_points[2].x = car_width_max;	// BL
			rotate_points[2].y = car_length;
			break;

		case STATE_EAST:
			rotate_points[0].x = car_length;	// TL
			rotate_points[0].y = 0;
			rotate_points[1].x = 0;	// TR
			rotate_points[1].y = 0;
			rotate_points[2].x = car_length;	// BL
			rotate_points[2].y = car_width_max;
			break;

		case STATE_WEST:
			rotate_points[0].x = 0;	// TL
			rotate_points[0].y = 0;
			rotate_points[1].x = car_length;	// TR
			rotate_points[1].y = 0;
			rotate_points[2].x = 0;	// BL
			rotate_points[2].y = car_width_max;

			break;

	}

	// Calculate the bitmap size
	int bitmap_car_rotated_x = 0, bitmap_car_rotated_y = 0;
	switch(this->direction) {

		case STATE_NORTH:
		case STATE_SOUTH:
			bitmap_car_rotated_x = car_width_max;
			bitmap_car_rotated_y = car_length;
			break;

		case STATE_EAST:
		case STATE_WEST:
			bitmap_car_rotated_x = car_length;
			bitmap_car_rotated_y = car_width_max;
			break;

	}

	// Create a memory device for rotated bitmap
	HDC MemDCBmpCarsRotated = CreateCompatibleDC(hdc);

	// Create bitmap for rotated cars
	HBITMAP bmpCarsRotated = CreateCompatibleBitmap(hdc, bitmap_car_rotated_x, bitmap_car_rotated_y);

	// Select the new bitmap
	SelectObject(MemDCBmpCarsRotated, bmpCarsRotated);

	// Rotate it
	PlgBlt(MemDCBmpCarsRotated,
		rotate_points,
		MemDCBmpCars,
		0, 
		0, 
		car_length, 
		car_width_max, 
		0,
		0,
		0
		);

	//	ROTATE

	//	TRANSPARENT AND CUT

	// Calculate the cut points according to car type and source points
	POINT car_cut_points[2];
	POINT car_src_points;
	POINT bitmap_car_transparent;

	switch(this->direction) {

		case STATE_NORTH:
		case STATE_SOUTH:
			car_cut_points[0].x = (int) ((int) this->type * car_width);
			car_cut_points[0].y = 0;
			car_cut_points[1].x = car_width;
			car_cut_points[1].y = car_length;
			car_src_points.x = car_stretched_width; // car_width;
			car_src_points.y = car_stretched_length; // car_length;
			bitmap_car_transparent.x = car_width_max;
			bitmap_car_transparent.y = car_length;
			break;

		case STATE_EAST:
		case STATE_WEST:
			car_cut_points[0].x = 0;
			car_cut_points[0].y = (int) ((int) this->type * car_width);
			car_cut_points[1].x = car_length;
			car_cut_points[1].y = car_width;
			car_src_points.x = car_stretched_length; // car_length;
			car_src_points.y = car_stretched_width; //car_width;
			bitmap_car_transparent.x = car_length;
			bitmap_car_transparent.y = car_width_max;
			break;

	}

	// Create a memory device for rotated bitmap
	HDC MemDCBmpCarTransparent = CreateCompatibleDC(hdc);

	// Create bitmap for transparent cut car
	HBITMAP bmpCarTransparent = CreateCompatibleBitmap(hdc, bitmap_car_transparent.x, bitmap_car_transparent.y);

	// Select the new bitmap
	SelectObject(MemDCBmpCarTransparent, bmpCarTransparent);

	// Transparent and cut bitmap
	TransparentBlt(
		hdc, 
		x, 
		y, 
		car_src_points.x, 
		car_src_points.y,
		MemDCBmpCarsRotated, 
		car_cut_points[0].x, 
		car_cut_points[0].y,
		car_cut_points[1].x, 
		car_cut_points[1].y, 
		(UINT) RGB(255, 0, 128) 
		);

	//	/TRANSPARENT AND CUT

	// Delete DC
	DeleteDC(MemDCBmpCars);
	DeleteDC(MemDCBmpCarsRotated);
	DeleteDC(MemDCBmpCarTransparent);
	// Delete Objects
	DeleteObject(bmpCars);
	DeleteObject(bmpCarsRotated);
	DeleteObject(bmpCarTransparent);

}

POINT Car::getBehind() {

	POINT behind;
	behind.x = this->getAt().x;
	behind.y = this->getAt().y;

	switch(this->getDirection()) {

		case STATE_NORTH:
			behind.y += this->getLength();
			break;

		case STATE_EAST:
			behind.x -= this->getLength();
			break;

		case STATE_SOUTH:
			behind.y -= this->getLength();
			break;

		case STATE_WEST:
			behind.x += this->getLength();
			break;

	}

	return behind;

}

void Car::doDrive(Car car_infront, int traffic_light_state) {

	//	CALCULATE NEW POINT

	POINT new_at;
	new_at.x = this->getAt().x;
	new_at.y = this->getAt().y;
	int speed = this->getSpeed();

	switch(this->getDirection()) {

		case STATE_NORTH:
			new_at.y -= speed;
			break;

		case STATE_EAST:
			new_at.x += speed;
			break;

		case STATE_SOUTH:
			new_at.y += speed;
			break;

		case STATE_WEST:
			new_at.x -= speed;
			break;

	}

	//	/CALCULATE NEW POINT

	switch(this->getState()) {

		case STATE_WAITING:
			this->setState(STATE_DRIVING);
			break;

		case STATE_DRIVING:

			// Is in que
			if (this->isStopQue(car_infront, new_at)) {
				this->setState(STATE_STOPPED_QUE);
				return;
			}
			// Is at intersection and not allowed to drive
			if (this->isStopIntersection(new_at) && (traffic_light_state != TrafficLight::STATE_GREEN)) {
				if (Traffic::DRIVE_ON_YELLOW == 0 || (Traffic::DRIVE_ON_YELLOW == 1 && traffic_light_state != TrafficLight::STATE_YELLOW)) {
				this->setState(STATE_STOPPED_INTERSECTION);
				return;
				}
			}
			// Is out of bound
			if (this->isOutOfBound()) {
				this->setState(STATE_OUT_OF_BOUND);
				return;
			}

			// Set new point
			this->setAt(new_at);

			break;

		case STATE_STOPPED_QUE:

			// Is out of que
			if (!this->isStopQue(car_infront, new_at)) {
				this->setState(STATE_DRIVING);
				return;
			}

			break;

		case STATE_STOPPED_INTERSECTION:

			// Traffic light switched
			if (traffic_light_state == TrafficLight::STATE_GREEN) {
				this->setState(STATE_DRIVING);
				return;
			}

			break;

		case STATE_OUT_OF_BOUND:
			// Car should be deleted out of stack
			break;

	}

}

/** If is out of bound */
bool Car::isOutOfBound() {

	switch(this->getDirection()) {

		case STATE_NORTH:
			return (this->getStop().y > this->getBehind().y);
			break;

		case STATE_EAST:
			return (this->getStop().x < this->getBehind().x);
			break;

		case STATE_SOUTH:
			return (this->getStop().y < this->getBehind().y);
			break;

		case STATE_WEST:
			return (this->getStop().x > this->getBehind().x);
			break;

	}

	return false;

}

/** If to stop at intersection */
bool Car::isStopIntersection(POINT at_new) {

	// Represents the area within to stop
	int intersection_start = 0,
		intersection_stop = 0;

	switch(this->getDirection()) {

		case STATE_NORTH:
			intersection_start = this->getIntersection().y + this->getSpeed(),
				intersection_stop = this->getIntersection().y - this->getSpeed();

			return (at_new.y < intersection_start && at_new.y > intersection_stop);
			break;

		case STATE_EAST:
			intersection_start = this->getIntersection().x - this->getSpeed(),
				intersection_stop = this->getIntersection().x + this->getSpeed();

			return (at_new.x > intersection_start && at_new.x < intersection_stop);
			break;

		case STATE_SOUTH:
			intersection_start = this->getIntersection().y - this->getSpeed(),
				intersection_stop = this->getIntersection().y + this->getSpeed();

			return (at_new.y > intersection_start && at_new.y < intersection_stop);
			break;

		case STATE_WEST:
			intersection_start = this->getIntersection().x + this->getSpeed(),
				intersection_stop = this->getIntersection().x - this->getSpeed();

			return (at_new.x < intersection_start && at_new.x > intersection_stop);
			break;

	}

	return false;

}

/** If is in que */
bool Car::isStopQue(Car car_infront, POINT at_new) {

	// Only if car infront is legal and not out of bounds
	if (!car_infront.isStateLegal() || car_infront.isOutOfBound()) {
		return false;
	}

	// Car infront must drive in same direction
	if (car_infront.getDirection() != this->getDirection()) {
		return false;
	}

	// Calculate the distance
	int distance_pixel = (int) (this->getLength() * (double) (Car::DISTANCE / 100.0));

	switch(this->getDirection()) {

		case STATE_NORTH:
			return (at_new.y <= (car_infront.getBehind().y + distance_pixel));
			break;

		case STATE_EAST:
			return (at_new.x >= (car_infront.getBehind().x - distance_pixel));
			break;

		case STATE_SOUTH:
			return (at_new.y >= (car_infront.getBehind().y - distance_pixel));
			break;

		case STATE_WEST:
			return (at_new.x <= (car_infront.getBehind().x + distance_pixel));
			break;

	}

	return false;

}
