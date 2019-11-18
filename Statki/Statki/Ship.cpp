#include "Ship.h"

unsigned Ship::counter = 0;

Ship::Ship(Utils& u, vector<Field> b, char category, int x_coord_offset, int y_coord_offset)
	:u(u), board_fields(b), category(category), x_coord_offset(x_coord_offset), y_coord_offset(y_coord_offset), adjacent_fields(vector<Field>{}), placed(false),
	id(counter)
{
	init_fields();
	for (Field& f : fields)
		f.set_color(255, 128, 0);
	counter++;

	set_binary_representation(category);
}

void Ship::init_fields() {
	if (category == '1') {
		fields.push_back(Field(x_coord_offset, y_coord_offset, u.get_fSize(), u.get_fSize(), u.get_fSize()));
	}
	else if (category == '2') {
		for (unsigned i = 0; i < 2; ++i)
			fields.push_back(Field(x_coord_offset + i, y_coord_offset, u.get_fSize(), u.get_fSize(), u.get_fSize()));
	}
	else if (category == '3') {
		for (unsigned i = 0; i < 3; ++i)
			fields.push_back(Field(x_coord_offset + i, y_coord_offset, u.get_fSize(), u.get_fSize(), u.get_fSize()));
	}
	else if (category == '4') {
		for (unsigned i = 0; i < 4; ++i)
			fields.push_back(Field(x_coord_offset + i, y_coord_offset, u.get_fSize(), u.get_fSize(), u.get_fSize()));
	}
	else if (category == '5') {
		for (unsigned i = 0; i < 5; ++i)
			fields.push_back(Field(x_coord_offset + i, y_coord_offset, u.get_fSize(), u.get_fSize(), u.get_fSize()));
	}
}

void Ship::render() {
	for (Field f : fields)
		f.render();
	for (Field f : adjacent_fields)
		al_draw_line(f.x_screen, f.y_screen, f.x_screen + u.get_fSize(), f.y_screen + u.get_fSize(), al_map_rgb(255, 255, 255), 2);
}

void Ship::set_adjacent_fields() {
	// cout << board_fields.size();
	adjacent_fields.clear();
	for (Field f : fields) {
		if (f.x - 1 >= 0 && f.y - 1 >= 0) {
			Field* ff = &board_fields.at(coord(f.x - 1, f.y - 1));
			if (!field_in_vec(*ff, adjacent_fields) && !field_in_vec(*ff, fields)) adjacent_fields.push_back(*ff);
		}
		if (f.y - 1 >= 0) {
			Field* ff = &board_fields.at(coord(f.x, f.y - 1));
			if (!field_in_vec(*ff, adjacent_fields) && !field_in_vec(*ff, fields)) adjacent_fields.push_back(*ff);
		}
		if (f.x + 1 < u.get_bSize() && f.y - 1 >= 0) {
			Field* ff = &board_fields.at(coord(f.x + 1, f.y - 1));
			if (!field_in_vec(*ff, adjacent_fields) && !field_in_vec(*ff, fields)) adjacent_fields.push_back(*ff);
		}
		if (f.x + 1 < u.get_bSize()) {
			Field* ff = &board_fields.at(coord(f.x + 1, f.y));
			if (!field_in_vec(*ff, adjacent_fields) && !field_in_vec(*ff, fields)) adjacent_fields.push_back(*ff);
		}
		if (f.x + 1 < u.get_bSize() && f.y + 1 < u.get_bSize()) {
			Field* ff = &board_fields.at(coord(f.x + 1, f.y + 1));
			if (!field_in_vec(*ff, adjacent_fields) && !field_in_vec(*ff, fields)) adjacent_fields.push_back(*ff);
		}
		if (f.y + 1 < u.get_bSize()) {
			Field* ff = &board_fields.at(coord(f.x, f.y + 1));
			if (!field_in_vec(*ff, adjacent_fields) && !field_in_vec(*ff, fields)) adjacent_fields.push_back(*ff);
		}
		if (f.x - 1 >= 0 && f.y + 1 < u.get_bSize()) {
			Field* ff = &board_fields.at(coord(f.x - 1, f.y + 1));
			if (!field_in_vec(*ff, adjacent_fields) && !field_in_vec(*ff, fields)) adjacent_fields.push_back(*ff);
		}
		if (f.x - 1 >= 0) {
			Field* ff = &board_fields.at(coord(f.x - 1, f.y));
			if (!field_in_vec(*ff, adjacent_fields) && !field_in_vec(*ff, fields)) adjacent_fields.push_back(*ff);
		}
	}
}

bool Ship::field_in_vec(Field f, std::vector<Field> vec) const {
	for (unsigned i = 0; i < vec.size(); i++)
		if (f == vec.at(i)) return true;
	return false;
}

int Ship::coord(int x, int y) {
	return y * u.get_bSize() + x;
}

void Ship::set_color(int r, int g, int b) {
	for (Field& f : fields)
		f.set_color(r, g, b);
}

void Ship::set_binary_representation(char pattern) {
	if (pattern == '1') binary_representation = vector<int>{ 0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0 };
	if (pattern == '2') binary_representation = vector<int>{ 0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0 };
	if (pattern == '3') binary_representation = vector<int>{ 0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0 };
	if (pattern == '4') binary_representation = vector<int>{ 0,0,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0 };
	if (pattern == '5') binary_representation = vector<int>{ 0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0 };
	if (pattern == 'i') binary_representation = vector<int>{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };
}

void Ship::rotate_binary_representation() {
	vector<int>* rotatedVec = new vector<int>();
	for (int y = 4; y >= 0; --y) 
		for (int x = 0; x < 5; ++x) 
			rotatedVec->push_back(binary_representation.at(x * 5 + y));

	binary_representation = *rotatedVec;
	delete rotatedVec;
}

bool Ship::operator==(const Ship& s) const {
	if (s.id != id)
		return false;
	return true;
}

bool Ship::operator!=(const Ship& s) const {
	return !operator==(s);
}