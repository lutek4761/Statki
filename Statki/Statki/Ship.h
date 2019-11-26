#pragma once
#include <vector>
#include "Field.h"
#include "Utils.h"
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
using namespace std;
class Ship
{
private:
	unsigned id;
	Utils& u;
	vector<int> binary_representation;
	vector<Field> adjacent_fields;
	vector<Field> fields;
	vector<Field> board_fields;
	bool placed;
	char category;
	int x_coord_offset, y_coord_offset;

public:
	static unsigned counter;
	Ship(Utils& u, vector<Field> b, char pattern, int x_render_offset, int y_render_offset);
	vector<Field>& getFieldsVector() { return fields; }
	void set_fields_vector(vector<Field> val) { fields = val; }
	void set_adjacent_fields();
	void set_adjacent_fields(vector<Field> val) { adjacent_fields = val; }
	void render();
	void render_adjacent_fields();
	void set_board_fields(vector<Field> val) { board_fields = val; }
	vector<Field>& get_board_fields() { return board_fields; }
	int coord(int x, int y);
	unsigned getId() { return id; }
	bool field_in_vec(Field f, vector<Field> fields) const;
	void set_placed(bool val) { placed = val; }
	bool is_placed() { return placed; }
	bool is_destroyed() const;
	vector<Field>& get_adjacent_fields() { return adjacent_fields; }
	void set_color(int r, int g, int b);
	vector<int>& get_binary_representation() { return binary_representation; }
	void set_binary_representation(char pattern);
	void set_binary_representation(vector<int> val) { binary_representation = val; }
	void reset_binary_representation() { binary_representation = vector<int>{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 }; }
	void rotate_binary_representation();
	void create_ship_fields_depending_on_binary_representation();
	bool operator==(const Ship&) const;
	bool operator!=(const Ship&) const;
};

