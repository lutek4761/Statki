#include "GameState.h"
#include "MenuState.h"
#include "ShipSettingState.h"
using namespace std;

GameState::GameState(Board& b1, Board& b2)
	:player_board(b1), computer_board(b2), field_selected(NULL)
{
	cpu_player = new CpuPlayer(b1);
	human_player = new HumanPlayer(b2);
	player_to_move = human_player;

	human_player->assgin_players(&player_to_move, &cpu_player);
	cpu_player->assgin_players(&player_to_move, &human_player);
}

GameState::~GameState() {}

void GameState::render() {
	player_board.render();
	player_board.render_ships();
	computer_board.render();
	//computer_board.render_ships();
	for (Ship& s : computer_board.getShips()) {
		for (Field& f : s.getFieldsVector())
			if (f.checked)
				f.render();
	}
		
		

	player_to_move->render();
	cpu_player->print_scores();
	al_draw_textf(Utils::get_font_20(), al_map_rgb(255, 255, 255), 40, 5, 0, "%s", "ESC - menu (zaczyna gre od nowa)");
}

void GameState::tick() {
	player_to_move->tick();
	if (Utils::get_esc_clicked()) {
		*state = menuState;
		player_board.reset();
		computer_board.reset();
		shipSettingState->reset();
	}
}

void GameState::assignStates(State** s, MenuState* m, ShipSettingState* ss) {
	state = s;
	menuState = m;
	shipSettingState = ss;
}