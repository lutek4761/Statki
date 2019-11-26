#pragma once
#include "State.h"
#include "Utils.h"
#include "Board.h"
#include "Player.h"
#include "HumanPlayer.h"
#include "CpuPlayer.h"
class GameState : public State
{
private:
	Utils& u;
	Board& player_board;
	Board& computer_board;
	CpuPlayer* cpu_player;
	HumanPlayer* human_player;
	Player* player_to_move;
	Field* field_selected;
public:
	GameState(Utils& u, Board& b1, Board& b2);
	~GameState();
	virtual void render();
	virtual void tick();
};

