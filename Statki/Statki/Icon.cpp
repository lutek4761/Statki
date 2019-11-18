#include "Icon.h"
int Icon::y_position = 40;
Icon::Icon(Ship* ship_pointer)
	:ship_pointer(ship_pointer), x(440), y(y_position)
{
	y_position += 40;
}

void Icon::render() {
	al_draw_rectangle(x, y, x + 40, y + 40, al_map_rgb(255, 0, 0), 2);
	if (ship_pointer != NULL) {
		vector<int> vec = ship_pointer->get_binary_representation();
		for (int yy = 0; yy < 5; yy++)
			for (int xx = 0; xx < 5; xx++)
				if (vec.at(yy * 5 + xx) == 1)
					al_draw_rectangle(x+ xx * 8, y+yy*8, x+(xx+1)*8, y+(yy+1)*8, al_map_rgb(255, 128, 128), 2);
	}
}