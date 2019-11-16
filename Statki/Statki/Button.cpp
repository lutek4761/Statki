#include "Button.h"
#include <iostream>
using namespace std;
Button::Button() {
	this->x = 0;
	this->y = 0;
	this->w = 0;
	this->y = 0;
	this->isActive = false;
	this->label = NULL;
	this->font24 = al_load_font("Arial.ttf", 24, 0);
}

Button::Button(int x, int y, int w, int h, const char* label, ID id)
	:isActive(false), canBeClicked(true)
{
	this->x = x;
	this->y = y;
	this->w = w;
	this->h = h;
	this->label = label;
	this->font24 = al_load_font("Arial.ttf", 24, 0);
	this->id = id;
}

Button::~Button() {}

void Button::render() {
	if (!canBeClicked)
		al_draw_rectangle(x, y, x + w, y + h, al_map_rgb(125, 125, 125), 2);
	else if (isActive)
		al_draw_rectangle(x, y, x + w, y + h, al_map_rgb(0, 255, 0), 2);
	else
		al_draw_rectangle(x, y, x + w, y + h, al_map_rgb(255, 0, 0), 2);
	al_draw_text(font24, al_map_rgb(255, 255, 255), (int)(x + w / 2 - strlen(label) * 5 + 3), y + h / 2 - 15, 0, label);

}

ID Button::getId() {
	return this->id;
}


