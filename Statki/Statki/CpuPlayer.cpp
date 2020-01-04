#include "CpuPlayer.h"
#include "HumanPlayer.h"
CpuPlayer::CpuPlayer(Board& opponents_board)
	:opponents_board(opponents_board), seekMode(false)
{
	font20 = al_load_font("Arial.ttf", 20, 0);
	set_scores_to_zero();
}

void CpuPlayer::render() {

}
void CpuPlayer::tick() {
	calcFieldsScores();
	int index = pickIndexOfFieldToHit();
	Field* f = &opponents_board.get_fields()[index];
	
		f->checked = true;
		if (check_for_hit(f, opponents_board)) {
			if(Utils::get_sounds_on())
				al_play_sample(Utils::get_hit_sound(), 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
			
			//przelaczenie na tryb szukania statku
			seekMode = true;
			destroyedFields.push_back(f);

			Field* ff = nullptr;
			Ship* hitShip = nullptr;
			//znajdz trafiony statek
			for (Ship& s : opponents_board.getShips())
				if (s.field_in_vec(*f, s.getFieldsVector()))
					hitShip = &s;

			//jesli zostal zniszczony to usun szablon z listy i uwzglednij okolice jesli trzeba 
			if (hitShip->is_destroyed()) {
				if (!Utils::get_show_adjacent_mode())
					for (Field& fff : hitShip->get_adjacent_fields())
						excludedFields.push_back(&fff);
				seekMode = false; // przerwanie trybu szukania
				destroyedFields.clear();
				list<ShipTemplate>::iterator it = templates.begin();
				bool found = false;
				while (it != templates.end()) {
					for (int z = 0; z < 4; z++) 
						if (*it == hitShip->get_template()) {
							found = true;
							templates.erase(it++);
							break;
						}
						else it->rotate();
						
					if (found) break;
					else it++;
				}

				if (Utils::get_show_adjacent_mode())
					for (Field& f : hitShip->get_adjacent_fields()) {
						ff = &opponents_board.get_fields()[f.y * opponents_board.get_width() + f.x];
						ff->set_color(32, 32, 128);
						ff->checked = true;
					}
				else {
					for (Field& f : hitShip->getFieldsVector())
						f.set_color(255, 32, 32);
				}
			}
		}
		else {
			f->set_color(32, 32, 128);
			if (Utils::get_sounds_on())
				al_play_sample(Utils::get_splash_sound(), 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
			*player_to_move = *human;
		}	
		
}

void CpuPlayer::assgin_players(Player** p, HumanPlayer** h) {
	player_to_move = p;
	human = h;
}

bool CpuPlayer::check_for_hit(Field* f, Board& b) const {
	for (Ship& s : b.getShips())
		for (Field& field : s.getFieldsVector())
			if (field == *f) {
				field.checked = true;
				field.set_color(255, 128, 128);
				return true;
			}

	return false;
}

void CpuPlayer::set_scores_to_zero() {
	scores.clear();
	for (int i = 0; i < opponents_board.get_fields().size(); i++)
		scores.push_back(0);
}

void CpuPlayer::print_scores() {
	int width = sqrt(opponents_board.get_fields().size());
	for (int y = 0; y < width; y++) {
		for (int x = 0; x < width; x++)
			al_draw_textf(font20, al_map_rgb(255, 255, 255), (x+1)*Utils::get_fSize(), (y+1)*Utils::get_fSize(), 0, "%d", scores[y * width + x]);
	}
	
}

void CpuPlayer::set_ship_templates(vector<Ship> ships) {
	templates.clear();
	for (Ship s : ships)
		if(!s.is_destroyed())
			templates.push_back(s.get_template());
}

void CpuPlayer::calcFieldsScores() {
	set_scores_to_zero();
	bool canBePlaced = true;

	for (ShipTemplate t : templates) {
		int numOfIterations = 0;
		vector<Field*>* vec = t.createFields();
		if (vec->size() == 1) numOfIterations = 1;
		else if (t.isStraight()) numOfIterations = 2;
		else numOfIterations = 4;
		for (int _ = 0; _ < numOfIterations; _++) {
			//calc max offset
			int xmax = 0, ymax = 0;
			for (Field* f : *vec) {
				if (f->x > xmax) xmax = f->x;
				if (f->y > ymax) ymax = f->y;
			}

			//calc fields values
			for (int y = 0; y < Utils::get_bSize() - ymax; y++)
				for (int x = 0; x < Utils::get_bSize() - xmax; x++) {
					for (Field* f : *vec) {
						if (!seekMode) {
							if (opponents_board.get_fields()[(f->y + y) * Utils::get_bSize() + f->x + x].checked) {
								canBePlaced = false;
								break;
							}
							else if(!Utils::get_show_adjacent_mode() and field_in_vec(*f, excludedFields, 0, 0, x, y)){
								canBePlaced = false;
								break;
							}
						}
						else {
							if (!Utils::get_show_adjacent_mode() and field_in_vec(*f, excludedFields, 0, 0, x, y)) {
								canBePlaced = false;
								break;
							}
							else if (!vec_in_vec(destroyedFields, vec, x, y, 0, 0)) {
								canBePlaced = false;
								break;
							}
						}
					}
					if (canBePlaced) 
						for (Field* f : *vec) 
							if(!field_in_vec(Field(f->x + x, f->y + y, 0, 0, 0), destroyedFields, 0, 0, 0, 0) and
								!opponents_board.get_fields()[(f->y + y) * Utils::get_bSize() + f->x + x].checked)
								scores[(f->y + y) * Utils::get_bSize() + f->x + x]++;
					
					canBePlaced = true;
				}
			t.rotate();
			delete vec;
			vec = t.createFields();
		}
		delete vec;
		
	}

}

bool CpuPlayer::field_in_vec(Field f, vector<Field*> vec, int xfoffset, int yfoffset, int xvecoffset, int yvecoffset) {
	for (Field* field : vec)
		if (field->x + xfoffset == f.x + xvecoffset and field->y + yfoffset == f.y + yvecoffset) {
			return true;
		}
			
	return false;
}
bool CpuPlayer::vec_in_vec(vector<Field*> innerVec, vector<Field*>* vec, int xoffset1, int yoffset1, int xoffset2, int yoffset2) {
	for (Field* f : innerVec)
		if (!field_in_vec(*f, *vec, xoffset1, yoffset1, xoffset2, yoffset2))
			return false;
	return true;
}

int CpuPlayer::pickIndexOfFieldToHit() {
	int max = 0;
	vector<int> maxIndexes;
	for (unsigned i = 0; i < scores.size(); i++) 
		if (scores[i] > max) {
			maxIndexes.clear();
			maxIndexes.push_back(i);
			max = scores[i];
		}
		else if (scores[i] == max) 
			maxIndexes.push_back(i);
		
	
	return maxIndexes[rand() % maxIndexes.size()];
}