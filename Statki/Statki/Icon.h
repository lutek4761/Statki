#pragma once
#include "Square.h"
#include <vector>
#include "Field.h"
#include "Ship.h"
using namespace std;
class Icon
{
private:
	static int y_position;
	int y, x, w;
	Ship* ship_pointer;
public:
	Icon(Ship* ship_pointer);
	void render();
	static int& get_y_position() { return y_position; }
	static void set_y_position(int val) { y_position = val; }
};

