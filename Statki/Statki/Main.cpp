#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_audio.h>
#include "Utils.h"
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
	al_install_audio();
	al_init_acodec_addon();
	al_reserve_samples(4);
	al_init_font_addon();
	al_init_ttf_addon();
	ALLEGRO_SAMPLE* clicked = al_load_sample("clicked.wav");
	ALLEGRO_SAMPLE* selected = al_load_sample("selected.wav");
	ALLEGRO_SAMPLE* hit = al_load_sample("Explosion1.wav");
	ALLEGRO_SAMPLE* splash = al_load_sample("Splash.wav");
	ALLEGRO_FONT* font30 = al_load_font("Arial.ttf", 30, 0);
	ALLEGRO_FONT* font20 = al_load_font("Arial.ttf", 20, 0);

	Utils::set_clicked_sound(clicked);
	Utils::set_selected_sound(selected);
	Utils::set_hit_sound(hit);
	Utils::set_splash_sound(splash);
	Utils::set_font20(font20);
	Utils::set_font30(font30);
	Board b1(Utils::get_bSize(), Utils::get_bSize(), Utils::get_fSize(), Utils::get_fSize());
	Board b2(Utils::get_bSize(), Utils::get_bSize(), (Utils::get_bSize() +2) * Utils::get_fSize(), Utils::get_fSize());

	ALLEGRO_DISPLAY* display = al_create_display(Utils::get_dispWidth(), Utils::get_dispHeight()); //Obraz
	ALLEGRO_EVENT_QUEUE* queue = al_create_event_queue(); //Kolejka zdarzeñ
	ALLEGRO_TIMER* timer = al_create_timer(1.0 / FPS); //Zegarek
	al_register_event_source(queue, al_get_keyboard_event_source());
	al_register_event_source(queue, al_get_mouse_event_source());
	al_register_event_source(queue, al_get_display_event_source(display));
	al_register_event_source(queue, al_get_timer_event_source(timer));

	State* s;
	GameState s_game(b1, b2);
	MenuState s_menu;
	ShipSettingState s_shipSet(b1, b2);

	s = &s_menu;

	s_menu.assignStates(&s, &s_game, &s_shipSet);
	s_shipSet.assignStates(&s, &s_game, &s_menu);
	s_game.assignStates(&s, &s_menu, &s_shipSet);

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
			Utils::set_mouse_clicked1(true);
		if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP && event.mouse.button & 1) 
			Utils::set_mouse_clicked1(false);
		if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN && event.mouse.button & 2)
			Utils::set_mouse_clicked2(true);
		if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP && event.mouse.button & 2)
			Utils::set_mouse_clicked2(false);
		if (al_key_down(&keyState, ALLEGRO_KEY_SPACE))
			Utils::set_space_pressed(true);
		else
			Utils::set_space_pressed(false);
		if (al_key_down(&keyState, ALLEGRO_KEY_ESCAPE))
			Utils::set_esc_pressed(true);
		else
			Utils::set_esc_pressed(false);
		if (event.type == ALLEGRO_EVENT_MOUSE_AXES) {
			Utils::set_mouseX(event.mouse.x);
			Utils::set_mouseY(event.mouse.y);
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

	return 0;
}