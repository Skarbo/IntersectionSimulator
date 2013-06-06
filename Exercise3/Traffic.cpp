#include "stdafx.h"
#include "Traffic.h"
#include <math.h>

void Traffic::initIntersection() {

	//	INTERSECTION

	intersection.setSize(this->getSize());
	intersection.setX(this->getX());
	intersection.setY(this->getY());
	//intersection.setState(Intersection::STATE_EAST_WEST);

	//	/INTERSECTION

}

void Traffic::doBreakpoint() {

};

void Traffic::doDrive() {

	// Foreach direction
	for(int i = 0; i < 4; i++) {

		// Create car prev and empty
		Car car_prev, car_empty;

		// Foreach cars in direction
		for(int j = 0; j < (int) cars[i].size(); j++) {

			// Erase car if out of bounds
			if (cars[i].at(j).getState() == Car::STATE_OUT_OF_BOUND) {

				// Erase car
				cars[i].erase(cars[i].begin()+j);

				// Set prev car as empty
				car_prev = car_empty;

			}
			else {

				// Drive car
				cars[i].at(j).doDrive(car_prev, intersection.getTrafficLight(i).getState());

				// Set prev car
				car_prev = cars[i].at(j);

			}

		}

		// Set prev car as empty
		car_prev = car_empty;

	}

};

void Traffic::draw(HDC hdc) {

	// Draw intersection
	intersection.draw(hdc);

	// Draw Stats
	if (this->SHOW_STATS == 1) {
		this->doDrawStats(hdc);
	}

	// Draw Cars
	for(int i = 0; i < 4; i++) {

		for(int j = 0; j < (int) cars[i].size(); j++) {

			// Draw car
			cars[i].at(j).doDraw(hdc);

		}

	}

};

void Traffic::doAddCar(int direction) {

	// Probability
	if (Traffic::PROBABILITY_DO == 1) {
		
		// If random probability is not a number below 0-100
		if(((rand() % 100) + 1) > this->probability[direction]) {
			return;
		}

	}

	// Calculate the speed of the car, random between slow, normal and fast
	int car_speed = 0;
	switch(rand() % 3) {
		case Traffic::SPEED_RATE_SLOW:
			car_speed = (int) ((double) TRAFFIC_SPEED_RATE_SLOW * (double) this->getSize());
			break;
		case Traffic::SPEED_RATE_FAST:
			car_speed = (int) ((double) TRAFFIC_SPEED_RATE_FAST * (double) this->getSize());
			break;
		default:
			car_speed = (int) ((double) TRAFFIC_SPEED_RATE_NORMAL * (double) this->getSize());
			break;
	}

	POINT road_start = intersection.getRoadStart(direction);
	POINT road_end = intersection.getRoadEnd(direction);

	int road_width = Intersection::getRoadWidth(this->getSize());
	int car_width = Car::getStretchedWidth(road_width);

	Car car;

	car.setColor(RGB(rand() %255, rand() %255, rand() %255));
	car.setState(Car::STATE_WAITING);
	car.setSpeed(car_speed);
	car.setWidth(car_width);
	car.setStart(road_start);
	car.setStop(road_end);
	car.setAt(road_start);
	car.setDirection(direction);
	car.setIntersection(intersection.getIntersection(direction));

	// Add car to direction
	this->cars[direction].push_back(car);

}

int Traffic::getCarsCount(int direction) {
	return (int) this->cars[direction].size();
}

int Traffic::getCarsCount(int direction, int car_state) {

	int count = 0;

	for(int i = 0; i < (int) this->cars[direction].size(); i++) {

		// If car is in state; inc count
		if (this->cars[direction].at(i).getState() == car_state) {
			count++;
		}

	}

	return count;

}

void Traffic::doDrawStats(HDC hdc) {

	int lines_height_px = 15,
		lines_width = 150,
		lines_nr = 8;
	POINT start;
	WCHAR sz[8][100];

	// Foreach road direction
	for(int direction = 0; direction < 4; direction++) {

		wsprintf(sz[1], _T("Antall biler: %d"), this->getCarsCount(direction));
		wsprintf(sz[2], _T("Biler venter: %d"), this->getCarsCount(direction, Car::STATE_WAITING));
		wsprintf(sz[3], _T("Biler kjører: %d"), this->getCarsCount(direction, Car::STATE_DRIVING));
		wsprintf(sz[4], _T("Biler i kø: %d"), this->getCarsCount(direction, Car::STATE_STOPPED_QUE));
		wsprintf(sz[5], _T("Biler i lyskryss: %d"), this->getCarsCount(direction, Car::STATE_STOPPED_INTERSECTION));
		wsprintf(sz[6], _T("Biler ute fra skjerm: %d"), this->getCarsCount(direction, Car::STATE_OUT_OF_BOUND));
		wsprintf(sz[7], _T("Sannsynlighet: %d%%"), this->getProbability(direction));

		switch(direction) {
		case STATE_NORTH:
			wsprintf(sz[0], _T("Nord"));
			start.x = this->getSize() - lines_width;
			start.y = this->getSize() - (lines_height_px * lines_nr);
			break;
		case STATE_EAST:
			wsprintf(sz[0], _T("Øst"));
			start.x = 0;
			start.y = this->getSize() - (lines_height_px * lines_nr);
			break;
		case STATE_SOUTH:
			wsprintf(sz[0], _T("Sør"));
			start.x = 0;
			start.y = 0;
			break;
		case STATE_WEST:
			wsprintf(sz[0], _T("Vest"));
			start.x = this->getSize() - lines_width;
			start.y = 0;
			break;
		}

		for(int i = 0; i < lines_nr; i++) {
			TextOutW(hdc, start.x, start.y + (i * lines_height_px), sz[i], wcslen(sz[i]));
		}

	}

}

void Traffic::incProbability(int direction, int number) {
	this->probability[direction] = min(this->probability[direction] + number, 100);
}

void Traffic::decProbability(int direction, int number) {
	this->probability[direction] = max(0, this->probability[direction] - number);
}