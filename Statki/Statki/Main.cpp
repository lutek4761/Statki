#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include"Utils.h"
#include "State.h"
#include "MenuState.h"
#include "GameState.h"
#include "ShipSettingState.h"
#include "Board.h"
#include<iostream>

using namespace std;

int main()
{
	int FPS = 60;
	al_init();
	al_init_primitives_addon(); //Rysowanie kresek
	al_install_keyboard();
	al_install_mouse();

	Utils u;
	Board b1(u, u.get_bSize(), u.get_bSize(), u.get_fSize(), u.get_fSize());

	ALLEGRO_DISPLAY* display = al_create_display(u.get_dispWidth(), u.get_dispHeight()); //Obraz
	ALLEGRO_EVENT_QUEUE* queue = al_create_event_queue(); //Kolejka zdarzeñ
	ALLEGRO_TIMER* timer = al_create_timer(1.0 / FPS); //Zegarek
	al_register_event_source(queue, al_get_keyboard_event_source());
	al_register_event_source(queue, al_get_mouse_event_source());
	al_register_event_source(queue, al_get_display_event_source(display));
	al_register_event_source(queue, al_get_timer_event_source(timer));

	State* s;
	GameState s_game(u);
	MenuState s_menu(u);
	ShipSettingState s_shipSet(u, b1);

	s = &s_menu;

	s_menu.assignStates(&s, &s_game, &s_shipSet);
	s_shipSet.assignStates(&s, &s_game, &s_menu);

	al_start_timer(timer);
	while (true) {
		ALLEGRO_EVENT event;
		ALLEGRO_KEYBOARD_STATE keyState;
		ALLEGRO_MOUSE_STATE mouseState;
		al_wait_for_event(queue, &event);

		if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
			exit(0);

		al_get_keyboard_state(&keyState);
		al_get_mouse_state(&mouseState);

		//**************INPUT********************
		if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN && event.mouse.button & 1)
			u.set_mouse_clicked1(true);
		if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP && event.mouse.button & 1)
			u.set_mouse_clicked1(false);
		if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN && event.mouse.button & 2)
			u.set_mouse_clicked2(true);
		if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP && event.mouse.button & 2)
			u.set_mouse_clicked2(false);
		if (al_key_down(&keyState, ALLEGRO_KEY_SPACE))
			u.set_space_pressed(true);
		else
			u.set_space_pressed(false);
		if (event.type == ALLEGRO_EVENT_MOUSE_AXES) {
			u.set_mouseX(event.mouse.x);
			u.set_mouseY(event.mouse.y);
		}
		//******KONIEC INPUTU***********************

		if (event.type == ALLEGRO_EVENT_TIMER) {
			s->tick();
			al_clear_to_color(al_map_rgb(0, 0, 0));
			s->render();
			al_flip_display();
		}
	}
	al_destroy_display(display);
	al_uninstall_keyboard();
	al_uninstall_mouse();
	al_destroy_timer(timer);
	u.~Utils();

	return 0;
}