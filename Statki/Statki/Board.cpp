#include "Board.h"
Board::Board(int width, int height, int x_offset, int y_offset)
	:x_offset(x_offset), y_offset(y_offset), width(width), height(height)
{
	init_vec();
}

void Board::init_vec() {
	fields.clear();
	for (unsigned y = 0; y < width; y++) {
		for (unsigned x = 0; x < height; x++) {
			fields.push_back(Field(x, y, x_offset, y_offset, Utils::get_fSize()));
		}
	}
}

void Board::render() {
	for (Field f : fields)
		f.render();
}

void Board::render_ships() {
	for (Ship s : ships)
		s.render();
}

Field* Board::getFieldSelectedByMouse() {
	int board_coord_x = (Utils::get_mouseX() - x_offset) / Utils::get_fSize();
	int board_coord_y = (Utils::get_mouseY() - y_offset) / Utils::get_fSize();
	if (board_coord_x >= 0 && board_coord_y >= 0 && board_coord_x < width && board_coord_y < height)
		return &fields.at(board_coord_y * width + board_coord_x);
	else return NULL;
}
void Board::reset() {
	init_vec();
	ships.clear();
}