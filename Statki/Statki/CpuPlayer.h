#pragma once
#include "Player.h"
#include "Board.h"
#include "Utils.h"
class HumanPlayer;
class CpuPlayer : public Player
{
	Player** player_to_move;
	HumanPlayer** human;
	Board& opponents_board;
	Utils& u;
public:
	CpuPlayer(Utils& u, Board& opponents_board);
	virtual void render();
	virtual void tick();
	bool check_for_hit(Field* f, Board& b) const;
	void assgin_players(Player**, HumanPlayer**);
};

