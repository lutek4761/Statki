#pragma once
#include <vector>
#include "Field.h"
#include "Utils.h"
#include "Ship.h"
using namespace std;
class Board
{
private:

	int x_offset, y_offset, width, height;
	Utils& u;
	vector<Field> fields;
	vector<Ship> ships;

public:
	Board(Utils& u, int width, int height, int x_offset, int y_offset);
	void init_vec();
	void render();
	vector<Field> get_fields() { return fields; }
	int get_x_offset() { return x_offset; }
	int get_y_offset() { return y_offset; }
	int get_width() { return width; }
	int get_height() { return height; }
	Field* getFieldSelectedByMouse();
};

