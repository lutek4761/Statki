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
	vector<Field> fields;
	vector<Ship> ships;

public:
	Board(int width, int height, int x_offset, int y_offset);
	void init_vec();
	void render();
	void render_ships();
	vector<Field>& get_fields() { return fields; }
	int get_x_offset() { return x_offset; }
	int get_y_offset() { return y_offset; }
	int get_width() { return width; }
	int get_height() { return height; }
	vector<Ship>& getShips() { return ships; }
	void setShips(vector<Ship> val) { ships.clear(); for (Ship& s : val) ships.push_back(s); }
	Field* getFieldSelectedByMouse();
	void reset();
};

