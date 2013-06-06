#include "stdafx.h"
#include "TrafficLight.h"

void TrafficLight::draw(HDC hdc, int x, int y, int height) {

	// Draw the box
	//Draw::box(hdc, x, y, this->getHeight(), this->getWidth());
	Draw::rectangle(hdc, x, y, getWidth(height), height, Draw::COLOR_WHITE);

	// Calcule the sircle colors
	int sircle_colors[3];

	switch (this->getState()) {

		case this->STATE_RED:
			// Red light
			sircle_colors[0] = Draw::COLOR_RED;
			sircle_colors[1] = Draw::COLOR_GRAY;
			sircle_colors[2] = Draw::COLOR_GRAY;
			break;

		case this->STATE_RED_YELLOW:
			// Red yellow light
			sircle_colors[0] = Draw::COLOR_RED;
			sircle_colors[1] = Draw::COLOR_YELLOW;
			sircle_colors[2] = Draw::COLOR_GRAY;
			break;

		case this->STATE_GREEN:
			// Green light
			sircle_colors[0] = Draw::COLOR_GRAY;
			sircle_colors[1] = Draw::COLOR_GRAY;
			sircle_colors[2] = Draw::COLOR_GREEN;
			break;

		case this->STATE_YELLOW:
			// Yellow light
			sircle_colors[0] = Draw::COLOR_GRAY;
			sircle_colors[1] = Draw::COLOR_YELLOW;
			sircle_colors[2] = Draw::COLOR_GRAY;
			break;

	}

	// Draw the sircles
	int sircle_height = (int) (height / 3);

	for(int i = 0; i < 3; i++) {
		Draw::circle(hdc, x, y + (sircle_height * i), (getWidth(height) / 2), sircle_colors[i]);
	}

};