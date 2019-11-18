#pragma once
#include "State.h"
#include "Board.h"
#include "Utils.h"
#include "Button.h"
#include "Icon.h"
#include "Ship.h"
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <iostream>
#include <time.h>
#include <vector>
using namespace std;
class GameState;
class MenuState;
class ShipSettingState : public State
{
private:
	vector<Icon> icons;
	Field* field_selected;
	vector<Button*>* buttonsToDisplay;
	vector<Button*> creationButtons;
	vector<Button*> shipSettingButtons;

	/***********BUTTONS************/
	Button menuButton;
	Button startGameButton;
	Button createShipButton;
	Button deleteShipButton;
	Button confirmButton;

	ALLEGRO_FONT* font30, * font20;
	ALLEGRO_SAMPLE* clicked, * selected;
	bool guard1, guard2, guard3;
	int last_mouse_pos_x, last_mouse_pos_y;
	int mouse_board_pos_x, mouse_board_pos_y;
	unsigned quantity1, quantity2, quantity3, quantity4, quantity5;
	Utils& u;
	Board& b;
	vector<Ship> ships;
	Ship* ship_selected;
	Board customBoard;
	vector<Field> last_ship_position;
	vector<Field> last_ship_adjacent_fields;
	State** state;
	MenuState* menuState;
	GameState* gameState;

	//****FUNKCJE*****
	void menuButtonOnClick();
	void startGameButtonOnClick();
	void createShipButtonOnClick();
	void deleteShipButtonOnClick();
	void confirmButtonOnClick();
	void assignCreationButtonsFunctions();
	void assignShipSettingButtonsFunctions();

	void handle_ship_creation();
	void handle_ship_setting();
	void handle_buttons_events();
	Ship* select_ship();
	bool can_place_ship() const;
	void drag();
	void set_ships_coords();
	void match_ship_screen_position();
	bool is_adjacent() const;
	bool is_placing_done() const;
	void calculate_mouse_board_pos();
	void rotate_ship();
	vector<Field*> create_array(int, int);
	void rotateArray(vector<Field*>&);
	void fitNewCoords(int, int, vector<Field*>);
	void replace_ships_vectors(Ship*, vector<Field*>);
	bool can_rotate_ship(vector<Field*>);
	void place_ships_randomly();
	int max_x(Ship*);
	int max_y(Ship*);
	int min_x(Ship*);
	int min_y(Ship*);
	bool can_append_field_to_ship(Field* f, Ship* s);
	unsigned max_ship_size_to_create();
	unsigned min_ship_size_to_create();
	void substract_ship_quantity();
	void manage_creation_buttons();
public:
	ShipSettingState(Utils& u, Board& b);
	~ShipSettingState();
	virtual void render();
	virtual void tick();
	void prepare_ships_for_setting();
	vector<Ship>& get_ships() { return ships; }
	Ship* get_ship_selected() { return ship_selected; }
	void delete_icons() { icons.clear(); Icon::set_y_position(40); }
	void set_ship_selected(Ship* val) { ship_selected = val; }
	void assignStates(State**, GameState*, MenuState*);
	void init_customizing_fields_vector();
	void set_ships_quantity();
	void set_buttons_to_display();

};
