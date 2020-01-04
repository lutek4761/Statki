#pragma once
#include "State.h"
#include "Utils.h"
#include "Board.h"
#include "Player.h"
#include "HumanPlayer.h"
#include "CpuPlayer.h"
class MenuState;
class ShipSettingState;
class GameState : public State
{
private:
	State** state;
	MenuState* menuState;
	ShipSettingState* shipSettingState;

	Board& player_board;
	Board& computer_board;
	CpuPlayer* cpu_player;
	HumanPlayer* human_player;
	Player* player_to_move;
	Field* field_selected;
public:
	GameState(Board& b1, Board& b2);
	~GameState();
	virtual void render();
	virtual void tick();
	CpuPlayer* get_cpu_player() { return cpu_player; }
	void assignStates(State**, MenuState*, ShipSettingState*);
};

