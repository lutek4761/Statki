#include "Utils.h"

Utils::Utils()
	:quantity1(3), quantity2(2), quantity3(2), quantity4(1), quantity5(0), ship_setting_done(false), mouse_clicked1(false),
	mouse_clicked2(false), space_pressed(false), custom_ships_mode(true), sounds_on(true)
{
	//centralizacja myszki
	numberOfAvailableFields = bSize * bSize - quantity1 * 9 - quantity2 * 12 - quantity3 * 15 - quantity4 * 18 - quantity5 * 21;
	mouseX = (bSize + 1) * fSize / 2;
	mouseY = (bSize + 1) * fSize / 2;
	ship_pattern = vector<char>{ '1','1','1','2','2','3','3','4' };
	al_install_audio();
	al_init_acodec_addon();
	al_reserve_samples(2);
	clicked = al_load_sample("clicked.wav");
	selected = al_load_sample("selected.wav");

}

Utils::~Utils() {}

bool Utils::isMouseInRectangle(unsigned x, unsigned y, unsigned w, unsigned h) {
	if ((mouseX > x) && (mouseY > y) && (mouseX < x + w) && (mouseY < y + h)) return true;
	else return false;
}

void Utils::reset_ship_pattern() {
	ship_pattern.clear();
	for (unsigned i = 0; i < quantity1; i++) ship_pattern.push_back('1');
	for (unsigned i = 0; i < quantity2; i++) ship_pattern.push_back('2');
	for (unsigned i = 0; i < quantity3; i++) ship_pattern.push_back('3');
	for (unsigned i = 0; i < quantity4; i++) ship_pattern.push_back('4');
	for (unsigned i = 0; i < quantity5; i++) ship_pattern.push_back('5');
}

