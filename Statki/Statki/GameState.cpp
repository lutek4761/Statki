#include "GameState.h"
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <iostream>
using namespace std;

GameState::GameState(Utils& u, Board& b1, Board& b2)
	:u(u), player_board(b1), computer_board(b2), field_selected(NULL)
{
	cpu_player = new CpuPlayer(u, b1);
	human_player = new HumanPlayer(u, b2);
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
	
}

void GameState::tick() {
	player_to_move->tick();
}

