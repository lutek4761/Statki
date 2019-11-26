#pragma once
#include "Player.h"
#include "Board.h"
#include "Field.h"
class CpuPlayer;
class HumanPlayer : public Player
{
	Player** player_to_move;
	CpuPlayer** comp;
	Field* field_selected;
	Board& opponents_board;
	Utils& u;

	void draw_aim_icon(Field* f);
public:

	bool check_for_hit(Field* f, Board& b) const;
	HumanPlayer(Utils& u, Board& opponents_board);
	virtual void render();
	virtual void tick();
	void assgin_players(Player**, CpuPlayer**);
};

