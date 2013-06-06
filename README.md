Intersection Simulator
=====================

Traffic simulator written in Win SDK for a school project, spring 2010.


![Intersection simulator][1]

## Project

* Date: Spring 2010
* Course: Programming with MS Windows, Bergen University College, TOD112
* Language: Win SDK (C++)
* IDE: Visual Studio
* Assignment: Assignment 3, TOD112, HiB, 2010

## Assignment

Cars shall arrive from west by pressing left mouse button down and cars from north by pressing the right button. The cars must follow the traffic rules, that is stop on red light at the crossing, and drive when the light is green. Use a timer for updating the position of the cars.
Cars from west arrive with a probability pv per second, and cars from north arrive with probability pn. You now have a traffic simulator and can study how queues build up in the traffic crossing.

## Video

http://www.youtube.com/watch?v=-CNuWuD4R7o

## Program

The program is a simulation of a traffic intersection. When the simulations starts three timers are created.

* One for every 10ms which moves the positions of the cars in the simulation.
* Another for every 100ms which adds a car according to the probability for each direction.
* The last for every 2000ms which changes the intersection state.
* The cars are drawn rectangles. The number indicates the speed of each car.

## Keys

Key up: Start
Key down: Stop
Numpad 8: Increase probability north
Numpad 9: Decrease probability north
Numpad 6: Increase probability east
Numpad 3: Decrease probability east
Numpad 2: Increase probability south
Numpad 1: Decrease probability south
Numpad 4: Increase probability west
Numpad 7: Decrease probability west

## Source code worth mentioning

### Repeat Bitmap

![Repeat bitmap][2]

Repeats a bitmap over a given area.

```c++
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
```

 [1]: http://i.imgur.com/xazVqjj.png
 [2]: http://i.imgur.com/9f6ieNd.png
