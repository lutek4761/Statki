#include "HumanPlayer.h"
#include "CpuPlayer.h"
#include <iostream>
using namespace std;
HumanPlayer::HumanPlayer(Utils& u, Board& opponents_board) 
	:u(u), opponents_board(opponents_board), field_selected(NULL)
{

}
void HumanPlayer::render() {
	draw_aim_icon(field_selected);
}

void HumanPlayer::tick() {
	field_selected = opponents_board.getFieldSelectedByMouse();
	if(field_selected!=NULL)cout << "not null'  ";
	cout << "mouse " << u.get_mouse_clicked1() << endl;
	if (field_selected != NULL and u.get_mouse_clicked1())
		if (!field_selected->checked) {
			field_selected->checked = true;
			if (check_for_hit(field_selected, opponents_board)) {
				field_selected->set_color(128, 255, 128);
				al_play_sample(u.get_hit_sound(), 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
			}
			else {
				field_selected->set_color(32, 32, 128);
				al_play_sample(u.get_splash_sound(), 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
			}
		}
}

bool HumanPlayer::check_for_hit(Field* f, Board b) const {
	for (Ship s : b.getShips())
		for (Field field : s.getFieldsVector())
			if (field == *f)
				return true;
	return false;
}

void HumanPlayer::draw_aim_icon(Field* f) {
	if (f != NULL) {
		al_draw_circle(f->x_screen + u.get_fSize() / 2, f->y_screen + u.get_fSize() / 2, u.get_fSize() / 3, al_map_rgb(255, 64, 64), 3);
		al_draw_line(f->x_screen + u.get_fSize() / 2, f->y_screen, f->x_screen + u.get_fSize() / 2, f->y_screen + u.get_fSize(), al_map_rgb(255, 64, 64), 3);
		al_draw_line(f->x_screen, f->y_screen + u.get_fSize() / 2, f->x_screen + u.get_fSize(), f->y_screen + u.get_fSize() / 2, al_map_rgb(255, 64, 64), 3);
	}
}