#pragma once
#include <allegro5/allegro.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_audio.h>
#include <iostream>
#include "Player.h"
#include <vector>

using namespace std;
class Utils
{
private:
	unsigned const fSize = 40; // szerokosc jednego pola (kwadratu)
	unsigned const bSize = 10; // liczba pol, 10x10
	unsigned const dispWidth = 3 * fSize + 2 * bSize * fSize;
	unsigned const dispHeight = 2 * fSize + bSize * fSize;
	unsigned const fps = 60;
	int mouseX, mouseY;
	bool mouse_clicked1, mouse_clicked2, space_pressed, ship_setting_done, custom_ships_mode, sounds_on;
	vector<char> ship_pattern;
	ALLEGRO_SAMPLE* clicked, * selected, * hit, * splash;
	unsigned quantity1, quantity2, quantity3, quantity4, quantity5;
public:
	ALLEGRO_SAMPLE* get_clicked_sound() { return clicked; }
	ALLEGRO_SAMPLE* get_selected_sound() { return selected; }
	ALLEGRO_SAMPLE* get_hit_sound() { return hit; }
	ALLEGRO_SAMPLE* get_splash_sound() { return splash; }
	unsigned get_quantity1() { return quantity1; }
	unsigned get_quantity2() { return quantity2; }
	unsigned get_quantity3() { return quantity3; }
	unsigned get_quantity4() { return quantity4; }
	unsigned get_quantity5() { return quantity5; }
	void set_quantity1(unsigned val) { quantity1 = val; }
	void set_quantity2(unsigned val) { quantity2 = val; }
	void set_quantity3(unsigned val) { quantity3 = val; }
	void set_quantity4(unsigned val) { quantity4 = val; }
	void set_quantity5(unsigned val) { quantity5 = val; }
	unsigned numberOfAvailableFields;
	Utils();
	~Utils();
	vector<char> get_ship_pattern() { return ship_pattern; }
	unsigned get_fSize() { return fSize; }
	int get_bSize() { return bSize; }
	unsigned get_dispWidth() { return dispWidth; }
	unsigned get_dispHeight() { return dispHeight; }
	unsigned get_fps() { return fps; }
	int get_mouseX() { return mouseX; }
	int get_mouseY() { return mouseY; }
	bool get_sounds_on() { return sounds_on; }
	bool get_custom_ship_mode() { return custom_ships_mode; }
	bool get_mouse_clicked1() { return mouse_clicked1; }
	bool get_mouse_clicked2() { return mouse_clicked2; }
	bool get_space_pressed() { return space_pressed; }
	bool get_ship_setting_done() { return ship_setting_done; }
	void set_sounds_on(bool val) { sounds_on = val; }
	void set_custom_ship_mode(bool val) { custom_ships_mode = val; }
	void set_mouseX(unsigned val) { mouseX = val; }
	void set_mouseY(unsigned val) { mouseY = val; }
	void set_mouse_clicked1(bool val) { mouse_clicked1 = val; }
	void set_mouse_clicked2(bool val) { mouse_clicked2 = val; }
	void set_space_pressed(bool val) { space_pressed = val; }
	void set_ship_setting_done(bool val) { ship_setting_done = val; }

	bool isMouseInRectangle(unsigned x, unsigned y, unsigned w, unsigned h);
	void reset_ship_pattern();
};

