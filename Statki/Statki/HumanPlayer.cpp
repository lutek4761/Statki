#include "HumanPlayer.h"
#include "CpuPlayer.h"
#include <iostream>
using namespace std;
HumanPlayer::HumanPlayer(Board& opponents_board) 
	:opponents_board(opponents_board), field_selected(NULL)
{

}
void HumanPlayer::render() {
	draw_aim_icon(field_selected);
}

void HumanPlayer::tick() {
	field_selected = opponents_board.getFieldSelectedByMouse();
	if (field_selected != NULL and Utils::get_mouse_clicked1())
		if (!field_selected->checked) {
			field_selected->checked = true;
			if (check_for_hit(field_selected, opponents_board)) {
				if (Utils::get_sounds_on())
					al_play_sample(Utils::get_hit_sound(), 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
				// ogarniecie czy statek  zostal zniszczony
				
				Field* ff = NULL;
				for (Ship& s : opponents_board.getShips())
					if (s.is_destroyed()) {
						if (Utils::get_show_adjacent_mode()) {
							for (Field& f : s.get_adjacent_fields()) {
								ff = &opponents_board.get_fields()[f.y * opponents_board.get_width() + f.x];
								ff->set_color(32, 32, 128);
								ff->checked = true;
							}
						}
						else {
							for (Field& f : s.getFieldsVector())
								f.set_color(255, 32, 32);
						}
						
					}
					
			}
			else {
				field_selected->set_color(32, 32, 128);
				if (Utils::get_sounds_on())
					al_play_sample(Utils::get_splash_sound(), 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
				*player_to_move = *comp;
			}
			
		}
}

bool HumanPlayer::check_for_hit(Field* f, Board& b) const {
	for (Ship& s : b.getShips())
		for (Field& field : s.getFieldsVector())
			if (field == *f) {
				field.checked = true;
				field.set_color(255, 128, 128);
				return true;
			}
				
	return false;
}

void HumanPlayer::draw_aim_icon(Field* f) {
	if (f != NULL) {
		al_draw_circle(f->x_screen + Utils::get_fSize() / 2, f->y_screen + Utils::get_fSize() / 2, Utils::get_fSize() / 3, al_map_rgb(255, 64, 64), 3);
		al_draw_line(f->x_screen + Utils::get_fSize() / 2, f->y_screen, f->x_screen + Utils::get_fSize() / 2, f->y_screen + Utils::get_fSize(), al_map_rgb(255, 64, 64), 3);
		al_draw_line(f->x_screen, f->y_screen + Utils::get_fSize() / 2, f->x_screen + Utils::get_fSize(), f->y_screen + Utils::get_fSize() / 2, al_map_rgb(255, 64, 64), 3);
	}
}

void HumanPlayer::assgin_players(Player** p, CpuPlayer** c) {
	player_to_move = p;
	comp = c;
}