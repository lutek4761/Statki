#pragma once
#include <allegro5/allegro.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <iostream>
#include "Player.h"
#include <vector>

using namespace std;
class Utils
{
private:
	unsigned static const fSize = 40; // szerokosc jednego pola (kwadratu)
	unsigned static const bSize = 10; // liczba pol, 10x10
	unsigned static const dispWidth = 3 * fSize + 2 * bSize * fSize;
	unsigned static const dispHeight = 2 * fSize + bSize * fSize;
	unsigned static const fps = 60;
	int static mouseX, mouseY;
	bool static mouse_clicked1, mouse_clicked2, space_pressed, ship_setting_done, custom_ships_mode, sounds_on, show_adjacent_mode;
	bool static esc_clicked;
	vector<char> static ship_pattern;
	ALLEGRO_SAMPLE static* clicked, * selected, * hit, * splash;
	ALLEGRO_FONT static* font30, * font20;
	unsigned static quantity1, quantity2, quantity3, quantity4, quantity5;
public:
	
	ALLEGRO_SAMPLE static* get_clicked_sound() { return clicked; }
	ALLEGRO_SAMPLE static* get_selected_sound() { return selected; }
	ALLEGRO_SAMPLE static* get_hit_sound() { return hit; }
	ALLEGRO_SAMPLE static* get_splash_sound() { return splash; }
	ALLEGRO_FONT static* get_font_30() { return font30; }
	ALLEGRO_FONT static* get_font_20() { return font20; }
	static void set_clicked_sound(ALLEGRO_SAMPLE* val) { clicked = val; }
	static void set_selected_sound(ALLEGRO_SAMPLE* val) { selected = val; }
	static void set_hit_sound(ALLEGRO_SAMPLE* val) { hit = val; }
	static void set_splash_sound(ALLEGRO_SAMPLE* val) { splash = val; }
	static void set_font30(ALLEGRO_FONT* val) { font30 = val; }
	static void set_font20(ALLEGRO_FONT* val) { font20 = val; }
	unsigned static get_quantity1() { return quantity1; }
	unsigned static get_quantity2() { return quantity2; }
	unsigned static get_quantity3() { return quantity3; }
	unsigned static get_quantity4() { return quantity4; }
	unsigned static get_quantity5() { return quantity5; }
	void static set_quantity1(unsigned val) { quantity1 = val; }
	void static set_quantity2(unsigned val) { quantity2 = val; }
	void static set_quantity3(unsigned val) { quantity3 = val; }
	void static set_quantity4(unsigned val) { quantity4 = val; }
	void static set_quantity5(unsigned val) { quantity5 = val; }
	unsigned static numberOfAvailableFields;
	vector<char> static& get_ship_pattern() { return ship_pattern; }
	unsigned static get_fSize() { return fSize; }
	int static get_bSize() { return bSize; }
	unsigned static get_dispWidth() { return dispWidth; }
	unsigned static get_dispHeight() { return dispHeight; }
	unsigned static get_fps() { return fps; }
	int static get_mouseX() { return mouseX; }
	int static get_mouseY() { return mouseY; }
	bool static get_sounds_on() { return sounds_on; }
	bool static get_show_adjacent_mode() { return show_adjacent_mode; }
	void static set_show_adjacent_mode(bool val) { show_adjacent_mode = val; }
	bool static get_custom_ship_mode() { return custom_ships_mode; }
	bool static get_mouse_clicked1() { return mouse_clicked1; }
	bool static get_mouse_clicked2() { return mouse_clicked2; }
	bool static get_space_pressed() { return space_pressed; }
	bool static get_esc_clicked() { return esc_clicked; }
	bool static get_ship_setting_done() { return ship_setting_done; }
	void static set_sounds_on(bool val) { sounds_on = val; }
	void static set_custom_ship_mode(bool val) { custom_ships_mode = val; }
	void static set_mouseX(unsigned val) { mouseX = val; }
	void static set_mouseY(unsigned val) { mouseY = val; }
	void static set_mouse_clicked1(bool val) { mouse_clicked1 = val; }
	void static set_mouse_clicked2(bool val) { mouse_clicked2 = val; }
	void static set_space_pressed(bool val) { space_pressed = val; }
	void static set_esc_pressed(bool val) { esc_clicked = val; }
	void static set_ship_setting_done(bool val) { ship_setting_done = val; }

	bool static isMouseInRectangle(unsigned x, unsigned y, unsigned w, unsigned h);
	void static reset_ship_pattern();
	void static set_default_settings();
};

