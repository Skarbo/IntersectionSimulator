#include "stdafx.h"
#include "Intersection.h"

Intersection::Intersection() {
	this->setState(this->STATE_NORTH_SOUTH);
	
	this->traffic_lights[STATE_NORTH].setState(TrafficLight::STATE_GREEN);
	this->traffic_lights[STATE_SOUTH].setState(TrafficLight::STATE_GREEN);

}

void Intersection::incStates() {

	for(int direction = 0; direction < 4; direction++) {
		this->traffic_lights[direction].incState();
	}

/*
	// North east
	if (this->getState() == this->STATE_NORTH_SOUTH) {

		// Incease starte north south
		this->traffic_lights[STATE_NORTH].incState();
		this->traffic_lights[STATE_SOUTH].incState();


		// North south hit red
		if (this->getTrafficLight(STATE_NORTH).getState() == TrafficLight::STATE_RED) {

			// Change state to east west
			this->setState(this->STATE_EAST_WEST);

			int test = this->getState();
			test;

		}

	}
	// East west
	else {

		// Incease starte east west
		this->traffic_lights[STATE_EAST].incState();
		this->traffic_lights[STATE_WEST].incState();

		// East west hit red
		if (this->getTrafficLight(STATE_EAST).getState() == TrafficLight::STATE_RED) {

			// Change state to north south
			this->setState(this->STATE_NORTH_SOUTH);

		}

	}
*/
}

void Intersection::draw(HDC hdc) {

	// Set width and height
	int width = this->getSize(), 
		height = this->getSize();

	// Draw background (grass)
	this->drawBackground(hdc);

	// Draw intersection
	this->drawIntersection(hdc);

}

void Intersection::drawIntersection(HDC hdc) {

	int width = this->getSize(),
		height = this->getSize(),
		x = this->getX(),
		y = this->getY();

	// ROAD

	// Calculate
	int road_width = Intersection::getRoadWidth(this->getSize());	//(int) ((width / 2) - (int) (width * 0.30));
	int road_height = Intersection::getRoadHeight(this->getSize());	//height;

	int road_y_x = x + ((int) (this->getSize() / 2) - (int) (road_width / 2));
	int road_x_y = y + ((int) (this->getSize() / 2) - (int) (road_width / 2));

	// Road Y direction
	//Draw::rectangle(hdc, road_y_x, y, road_width, road_height, Draw::COLOR_ASPHALT);
	Draw::repeatBitmap(hdc, Bitmap(IDB_ASPHALT, 480, 480), road_y_x, y, road_width, road_height);

	// Road X direction
	//Draw::rectangle(hdc, x, road_x_y, road_height, road_width, Draw::COLOR_ASPHALT);
	Draw::repeatBitmap(hdc, Bitmap(IDB_ASPHALT, 480, 480), x, road_x_y, road_height, road_width);

	// /ROAD

	//	TRAFFIC LIGHT

	// Calculate traffic light height
	int traffic_light_height = (int) (road_width * 0.8);

	this->traffic_lights[STATE_NORTH].draw(hdc, x + (int) (width / 2) + (int) (road_width / 2), y + (int) (height / 2) + (int) (road_width / 2), traffic_light_height);
	this->traffic_lights[STATE_EAST].draw(hdc, x + (int) (width / 2) - (int) (road_width / 2) - TrafficLight::getWidth(traffic_light_height), y + (int) (height / 2) + (int) (road_width / 2), traffic_light_height);
	this->traffic_lights[STATE_SOUTH].draw(hdc, x + (int) (width / 2) - (int) (road_width / 2) - TrafficLight::getWidth(traffic_light_height), y + (int) (height / 2) - (int) (road_width / 2) - traffic_light_height, traffic_light_height);
	this->traffic_lights[STATE_WEST].draw(hdc, x + (int) (width / 2) + (int) (road_width / 2), y + (int) (height / 2) - (int) (road_width / 2) - traffic_light_height, traffic_light_height);

	//	/TRAFFIC LIGHT

}

void Intersection::drawBackground(HDC hdc) {

	// Repeat bitmap image
	Draw::repeatBitmap(hdc, Bitmap(IDB_GRASS, 256, 256), this->getX(), this->getY(), this->getSize(), this->getSize());

};


POINT Intersection::getRoadStart(int direction) {

	POINT p;

	switch(direction) {

		case STATE_NORTH:
			p.x = this->getX() + ((int) (this->getSize() / 2));
			p.y = this->getY() + this->getSize();
			break;

		case STATE_EAST:
			p.x = this->getX();
			p.y = this->getY() + ((int) (this->getSize() / 2));
			break;

		case STATE_SOUTH:
			p.x = this->getX() + ((int) (this->getSize() / 2));
			p.y = y;
			break;

		case STATE_WEST:
			p.x = this->getX() + this->getSize();
			p.y = this->getY() + ((int) (this->getSize() / 2));
			break;

	}

	// Return point
	return p;

};

POINT Intersection::getRoadEnd(int direction) {
	return getRoadStart((direction + 2) % 4);
};

POINT Intersection::getIntersection(int direction) {

	POINT p;

	// Get road width
	int road_width = Intersection::getRoadWidth(this->getSize());
	int road_width_half = (int) (road_width / 2);
	int center = (int) (this->getSize() / 2);

	switch(direction) {

		case STATE_NORTH:
			p.x = center;
			p.y = center + road_width_half;
			break;

		case STATE_EAST:
			p.x = center - road_width_half;;
			p.y = center;
			break;

		case STATE_SOUTH:
			p.x = center;
			p.y = center - road_width_half;;
			break;

		case STATE_WEST:
			p.x = center + road_width_half;;
			p.y = center;
			break;

	}

	// Return point
	return p;

};