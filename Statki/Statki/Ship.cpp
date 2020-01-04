#include "Ship.h"

unsigned Ship::counter = 0;

Ship::Ship(vector<Field> b, char category, int x_coord_offset, int y_coord_offset)
	:board_fields(b), category(category), x_coord_offset(x_coord_offset), y_coord_offset(y_coord_offset), 
	adjacent_fields(vector<Field>{}), placed(false), id(counter), binary_rep(ShipTemplate(category))
{
	set_template(category);
	create_ship_fields_depending_on_binary_representation();
	for (Field& f : fields)
		f.set_color(255, 128, 0);
	counter++;
}

void Ship::set_template(char pattern) {
	if (pattern == '1') binary_rep.setTemplateVector(vector<int>{ 0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0 });
	if (pattern == '2') binary_rep.setTemplateVector(vector<int>{ 0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0 });
	if (pattern == '3') binary_rep.setTemplateVector(vector<int>{ 0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0 });
	if (pattern == '4') binary_rep.setTemplateVector(vector<int>{ 0,0,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0 });
	if (pattern == '5') binary_rep.setTemplateVector(vector<int>{ 0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0 });
	if (pattern == 'i') binary_rep.setTemplateVector(vector<int>{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 });
}

void Ship::create_ship_fields_depending_on_binary_representation() {
	fields.clear();
	for (int y = 0; y < 5; y++)
		for (int x = 0; x < 5; x++)
			if (binary_rep[y * 5 + x] == 1)
				fields.push_back(Field(x, y, 0, 0, Utils::get_fSize()));
}

void Ship::render() {
	for (Field f : fields)
		f.render();
}

void Ship::render_adjacent_fields() {
	for (Field f : adjacent_fields)
		al_draw_line(f.x_screen, f.y_screen, f.x_screen + Utils::get_fSize(), f.y_screen + Utils::get_fSize(), al_map_rgb(255, 255, 255), 2);
}

void Ship::set_adjacent_fields() {
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
		if (f.x + 1 < Utils::get_bSize() && f.y - 1 >= 0) {
			Field* ff = &board_fields.at(coord(f.x + 1, f.y - 1));
			if (!field_in_vec(*ff, adjacent_fields) && !field_in_vec(*ff, fields)) adjacent_fields.push_back(*ff);
		}
		if (f.x + 1 < Utils::get_bSize()) {
			Field* ff = &board_fields.at(coord(f.x + 1, f.y));
			if (!field_in_vec(*ff, adjacent_fields) && !field_in_vec(*ff, fields)) adjacent_fields.push_back(*ff);
		}
		if (f.x + 1 < Utils::get_bSize() && f.y + 1 < Utils::get_bSize()) {
			Field* ff = &board_fields.at(coord(f.x + 1, f.y + 1));
			if (!field_in_vec(*ff, adjacent_fields) && !field_in_vec(*ff, fields)) adjacent_fields.push_back(*ff);
		}
		if (f.y + 1 < Utils::get_bSize()) {
			Field* ff = &board_fields.at(coord(f.x, f.y + 1));
			if (!field_in_vec(*ff, adjacent_fields) && !field_in_vec(*ff, fields)) adjacent_fields.push_back(*ff);
		}
		if (f.x - 1 >= 0 && f.y + 1 < Utils::get_bSize()) {
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

bool Ship::is_destroyed() const {
	for (Field f : fields)
		if (!f.checked)
			return false;
	return true;
}

int Ship::coord(int x, int y) {
	return y * Utils::get_bSize() + x;
}

void Ship::set_color(int r, int g, int b) {
	for (Field& f : fields)
		f.set_color(r, g, b);
}

void Ship::rotate_binary_representation() {
	vector<int>* rotatedVec = new vector<int>();
	for (int y = 4; y >= 0; --y) 
		for (int x = 0; x < 5; ++x) 
			rotatedVec->push_back(binary_rep[x * 5 + y]);

	binary_rep.setTemplateVector(*rotatedVec);
	delete rotatedVec;
}

bool Ship::operator==(const Ship& s) const {
	return s.id == id;
}

bool Ship::operator!=(const Ship& s) const {
	return !operator==(s);
}