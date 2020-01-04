#pragma once
#include "Player.h"
#include "Board.h"
#include "Utils.h"
#include <vector>
#include <list>
#include "ShipTemplate.h"
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
class HumanPlayer;
class CpuPlayer : public Player
{
	Player** player_to_move;
	HumanPlayer** human;
	Board& opponents_board;
	vector<int> scores;
	list<ShipTemplate> templates;
	bool seekMode;
	vector<Field*> destroyedFields;
	vector<Field*> excludedFields; //jesli adjacent mode jest wylaczony
	ALLEGRO_FONT* font20;
public:
	CpuPlayer(Board& opponents_board);
	virtual void render();
	virtual void tick();
	bool check_for_hit(Field* f, Board& b) const;
	void assgin_players(Player**, HumanPlayer**);
	void set_scores_to_zero();
	void print_scores();
	void set_ship_templates(vector<Ship> ships);
	void calcFieldsScores();
	int pickIndexOfFieldToHit();
	bool field_in_vec(Field f, vector<Field*> vec, int xfoffset, int yfoffset, int xvecoffset, int yvecoffset);
	bool vec_in_vec(vector<Field*> innerVec, vector<Field*>* vec, int xoffset1, int yoffset1, int xoffset2, int yoffset2);
	
};

