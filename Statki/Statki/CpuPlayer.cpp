#include "CpuPlayer.h"
#include "HumanPlayer.h"
CpuPlayer::CpuPlayer(Utils& u, Board& opponents_board)
	:u(u), opponents_board(opponents_board)
{

}

void CpuPlayer::render() {

}
void CpuPlayer::tick() {
	Field* f = NULL;
	while (true) {
		f = &opponents_board.get_fields()[rand() % opponents_board.get_fields().size()];
		if (!f->checked) {
			f->checked = true;
			if (check_for_hit(f, opponents_board)) {
				al_play_sample(u.get_hit_sound(), 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
				// ogarniecie czy statek  zostal zniszczony
				if (u.get_show_adjacent_mode()) {
					Field* ff = NULL;
					for (Ship& s : opponents_board.getShips())
						if (s.is_destroyed()) {
							for (Field& f : s.get_adjacent_fields()) {
								ff = &opponents_board.get_fields()[f.y * opponents_board.get_width() + f.x];
								ff->set_color(32, 32, 128);
								ff->checked = true;
							}
						}
				}
				
			}
			else {
				f->set_color(32, 32, 128);
				al_play_sample(u.get_splash_sound(), 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
				*player_to_move = *human;
			}
			break;
		}
			
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