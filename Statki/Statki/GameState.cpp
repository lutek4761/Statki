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
}

GameState::~GameState() {}

void GameState::render() {
	player_board.render();
	player_board.render_ships();
	computer_board.render();
	//computer_board.render_ships();

	player_to_move->render();
	
}

void GameState::tick() {
	player_to_move->tick();
}


bool GameState::check_for_hit(Field* f, Board b) const {
	for (Ship s : b.getShips())
		for (Field field : s.getFieldsVector())
			if (field == *f)
				return true;
	return false;
}