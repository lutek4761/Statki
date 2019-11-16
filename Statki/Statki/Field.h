#pragma once
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
class Field {
public:
	int x, y, x_screen, y_screen, fSize, r, g, b, x_offset, y_offset;
	bool checked, is_part_of_ship;
	Field();
	Field(int, int, int, int, int);
	void render();
	void set_color(int, int, int);
	bool operator==(const Field&) const;
	bool operator!=(const Field&) const;
	void fit_render_coords();
};