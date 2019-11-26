#pragma once
#include "field.h"


Field::Field(int x, int y, int x_offset, int y_offset, int fSize)
	:x_offset(x_offset), y_offset(y_offset), x(x), y(y), r(20), g(120), b(200), checked(false), is_part_of_ship(false), fSize(fSize)
{
	this->x_screen = x * fSize + x_offset;
	this->y_screen = y * fSize + y_offset;
}

Field::Field() {}

void Field::render() {
	al_draw_filled_rectangle(x_screen, y_screen, x_screen + fSize, y_screen + fSize, al_map_rgb(r, g, b));
	al_draw_rectangle(x_screen, y_screen, x_screen + fSize, y_screen + fSize, al_map_rgb(25, 25, 25), 2);
}

bool Field::operator==(const Field& f) const {
	return f.x == this->x && f.y == this->y;
}
bool Field::operator!=(const Field& f) const {
	return !operator==(f);
}
void Field::set_color(int r, int g, int b) {
	this->r = r;
	this->g = g;
	this->b = b;
}
void Field::fit_render_coords(int x_offset, int y_offset) {
	this->x_screen = x * fSize + x_offset;
	this->y_screen = y * fSize + y_offset;
}