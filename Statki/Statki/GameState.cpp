#include "GameState.h"
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <iostream>
using namespace std;

GameState::GameState(Utils& u)
	:u(u)
{

}

GameState::~GameState() {}

void GameState::render() {
	al_draw_rectangle(100, 100, 200, 200, al_map_rgb(255, 0, 255), 2);
}

void GameState::tick() {
	cout << "game state" << endl;
}
