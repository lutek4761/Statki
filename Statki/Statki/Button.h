#pragma once
#include "Utils.h"
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <iostream>
#include <string.h>
#include "ID.h"
#include <functional>
using namespace std;

class Button
{
private:
	ID id;
	ALLEGRO_FONT* font24;
	int x, y, w, h;
	bool isActive, canBeClicked;
	const char* label;
	friend class MenuState;
	friend class ShipSettingState;
	friend class GameState;
public:
	ID getId();
	Button();
	Button(int x, int y, int w, int h, const char* labelm, ID id);
	~Button();
	void render();
	std::function<void(Button*)> onClickListener;


};
