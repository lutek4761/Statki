#include "Utils.h"

Utils::Utils()
	:quantity1(1), quantity2(1), quantity3(3), quantity4(0), quantity5(0), ship_setting_done(false), mouse_clicked1(false),
	mouse_clicked2(false), space_pressed(false), custom_ships_mode(false), sounds_on(true), show_adjacent_mode(true)
{
	//centralizacja myszki
	numberOfAvailableFields = bSize * bSize - quantity1 * 9 - quantity2 * 12 - quantity3 * 15 - quantity4 * 18 - quantity5 * 21;
	mouseX = (bSize + 1) * fSize / 2;
	mouseY = (bSize + 1) * fSize / 2;
	ship_pattern = vector<char>{ '1','2','3' ,'3' ,'3' ,'3' };
	al_install_audio();
	al_init_acodec_addon();
	al_reserve_samples(4);
	clicked = al_load_sample("clicked.wav");
	selected = al_load_sample("selected.wav");
	hit = al_load_sample("Explosion1.wav");
	splash = al_load_sample("Splash.wav");

}

Utils::~Utils() {}

bool Utils::isMouseInRectangle(unsigned x, unsigned y, unsigned w, unsigned h) {
	if ((mouseX > (int)x) && (mouseY > (int)y) && (mouseX < (int)x + w) && (mouseY < (int)y + h)) return true;
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

