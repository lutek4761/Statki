#include "Utils.h"

ALLEGRO_SAMPLE* Utils::hit = nullptr;
ALLEGRO_SAMPLE* Utils::splash = nullptr;
ALLEGRO_SAMPLE* Utils::clicked = nullptr;
ALLEGRO_SAMPLE* Utils::selected = nullptr;
ALLEGRO_FONT* Utils::font30 = nullptr;
ALLEGRO_FONT* Utils:: font20 = nullptr;

unsigned Utils::quantity1 = 0;
unsigned Utils::quantity2 = 0;
unsigned Utils::quantity3 = 2;
unsigned Utils::quantity4 = 1;
unsigned Utils::quantity5 = 1;
unsigned Utils::numberOfAvailableFields = Utils::bSize * Utils::bSize - Utils::quantity1 * 9 - 
Utils::quantity2 * 12 - Utils::quantity3 * 15 - Utils::quantity4 * 18 - Utils::quantity5 * 21;

vector<char> Utils::ship_pattern = vector<char>{ '3' ,'3' ,'4', '5' };
bool Utils::ship_setting_done = false;
bool Utils::mouse_clicked1 = false;
bool Utils::mouse_clicked2 = false;
bool Utils::space_pressed = false;
bool Utils::esc_clicked = false;
bool Utils::custom_ships_mode = true;
bool Utils::sounds_on = false;
bool Utils::show_adjacent_mode = false;

int Utils::mouseX = 0;
int Utils::mouseY = 0;

bool Utils::isMouseInRectangle(unsigned x, unsigned y, unsigned w, unsigned h) {
	if ((Utils::get_mouseX() > (int)x) && (Utils::get_mouseY() > (int)y) && (Utils::get_mouseX() < (int)x + w) && (Utils::get_mouseY() < (int)y + h)) return true;
	else return false;
}

void Utils::reset_ship_pattern() {
	Utils::get_ship_pattern().clear();
	for (unsigned i = 0; i < Utils::get_quantity1(); i++) Utils::get_ship_pattern().push_back('1');
	for (unsigned i = 0; i < Utils::get_quantity2(); i++) Utils::get_ship_pattern().push_back('2');
	for (unsigned i = 0; i < Utils::get_quantity3(); i++) Utils::get_ship_pattern().push_back('3');
	for (unsigned i = 0; i < Utils::get_quantity4(); i++) Utils::get_ship_pattern().push_back('4');
	for (unsigned i = 0; i < Utils::get_quantity5(); i++) Utils::get_ship_pattern().push_back('5');
}

void Utils::set_default_settings() {
	Utils::quantity1 = 0;
	Utils::quantity2 = 0;
	Utils::quantity3 = 2;
	Utils::quantity4 = 1;
	Utils::quantity5 = 1;
	Utils::numberOfAvailableFields = Utils::bSize * Utils::bSize - Utils::quantity1 * 9 -
		Utils::quantity2 * 12 - Utils::quantity3 * 15 - Utils::quantity4 * 18 - Utils::quantity5 * 21;

	Utils::custom_ships_mode = true;
	Utils::show_adjacent_mode = false;
}
