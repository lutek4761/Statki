#include "ShipSettingState.h"
#include "MenuState.h"
#include "GameState.h"
using namespace std;

ShipSettingState::ShipSettingState(Utils& u, Board& b)
	:u(u), b(b), last_mouse_pos_x(u.get_mouseX()), last_mouse_pos_y(u.get_mouseY()),
	ship_selected(NULL), guard1(true), guard2(true), guard3(true), customBoard(Board(u, 5, 5, 500, 75)),
	quantity1(0), quantity2(0), quantity3(0), quantity4(0), quantity5(0), field_selected(NULL)
{
	font30 = al_load_font("Arial.ttf", 30, 0);
	font20 = al_load_font("Arial.ttf", 20, 0);
	clicked = u.get_clicked_sound();
	selected = u.get_selected_sound();
	srand(time(NULL));

	/****************************************BUTTONS****************************************/
	menuButton = Button(750, 400, 150, 50, "Menu", ID::MENU);
	confirmButton = Button(750, 325, 150, 50, "Confirm", ID::CONFIRM);
	startGameButton = Button(550, 400, 150, 50, "Start game", ID::STARTGAME);
	createShipButton = Button(499, 300, 100, 50, "Create", ID::CREATESHIP);
	deleteShipButton = Button(601, 300, 100, 50, "Delete", ID::DELETESHIP);
	creationButtons = vector<Button*>{ &menuButton, &createShipButton, &deleteShipButton, &confirmButton };
	shipSettingButtons = vector<Button*>{ &menuButton, &startGameButton };

	buttonsToDisplay = &creationButtons;
	assignCreationButtonsFunctions();
	assignShipSettingButtonsFunctions();

	startGameButton.canBeClicked = false;
}

ShipSettingState::~ShipSettingState() {}

void ShipSettingState::render() {
	b.render();
	if (u.get_custom_ship_mode()) {
		customBoard.render();
		al_draw_textf(font30, al_map_rgb(255, 255, 255), 500, 25, 0, "%s", "CUSTOMIZING BOARD");
		al_draw_textf(font30, al_map_rgb(255, 255, 255), 750, 25, 0, "%s", "QUANTITY");
		al_draw_textf(font20, al_map_rgb(255, 255, 255), 750, 75, 0, "ONE-MASTED: %d", quantity1);
		al_draw_textf(font20, al_map_rgb(255, 255, 255), 750, 125, 0, "TWO-MASTED: %d", quantity2);
		al_draw_textf(font20, al_map_rgb(255, 255, 255), 750, 175, 0, "THREE-MASTED: %d", quantity3);
		al_draw_textf(font20, al_map_rgb(255, 255, 255), 750, 225, 0, "FOUR-MASTED: %d", quantity4);
		al_draw_textf(font20, al_map_rgb(255, 255, 255), 750, 275, 0, "FIIVE-MASTED: %d", quantity5);
		if (ship_selected != NULL)
			ship_selected->render();
	}
	else {
		for (Ship s : ships)
			s.render();
	}
	for (Button* button : *buttonsToDisplay)
		button->render();
	if (field_selected != NULL)
		al_draw_rectangle(field_selected->x_screen, field_selected->y_screen, field_selected->x_screen + u.get_fSize(),
			field_selected->y_screen + u.get_fSize(), al_map_rgb(255, 0, 0), 2);
}

void ShipSettingState::tick() {
	handle_buttons_events();
	if (u.get_custom_ship_mode()) {
		handle_ship_creation();
	}
	else {
		handle_ship_setting();
	}
	if (is_placing_done() && ships.size() != 0) {
		startGameButton.canBeClicked = true;
	}
	last_mouse_pos_x = u.get_mouseX();
	last_mouse_pos_y = u.get_mouseY();
}

Ship* ShipSettingState::select_ship() {
	for (Ship& s : ships) {
		for (Field& f : s.getFieldsVector()) {
			if (u.isMouseInRectangle(f.x_screen, f.y_screen, u.get_fSize(), u.get_fSize()))
				return &s;
		}
	}
	return NULL;
}

bool ShipSettingState::can_place_ship() const {
	//czy wszystkie pola statku sa na planszy
	for (Field& f : ship_selected->getFieldsVector()) {
		if (f.x_screen < b.get_x_offset() - (int)u.get_fSize() / 2 || f.y_screen < b.get_y_offset() - (int)u.get_fSize() / 2
			|| f.x_screen > b.get_x_offset() + (u.get_bSize() - 1) * u.get_fSize() + (int)u.get_fSize() / 2
			|| f.y_screen > b.get_y_offset() + (u.get_bSize() - 1) * u.get_fSize() + (int)u.get_fSize() / 2)
			return false;
	}
	return true;
}

void ShipSettingState::drag() {
	for (Field& f : ship_selected->getFieldsVector()) {
		f.x_screen -= last_mouse_pos_x - u.get_mouseX();
		f.y_screen -= last_mouse_pos_y - u.get_mouseY();
	}
}

void ShipSettingState::set_ships_coords() {
	for (Field& f : ship_selected->getFieldsVector()) {
		f.x = ((int)f.x_screen - (int)b.get_x_offset() + (int)u.get_fSize() / 2) / (int)u.get_fSize();
		f.y = ((int)f.y_screen - (int)b.get_y_offset() + (int)u.get_fSize() / 2) / (int)u.get_fSize();
	}
}

void ShipSettingState::match_ship_screen_position() {
	for (Field& f : ship_selected->getFieldsVector()) {
		f.x_screen = b.get_x_offset() + f.x * u.get_fSize();
		f.y_screen = b.get_y_offset() + f.y * u.get_fSize();
	}
}

void ShipSettingState::prepare_ships_for_setting() {
	ships.clear();
	int y = 0;
	int x = 11;
	char last_pattern = u.get_ship_pattern().at(0);
	for (char pattern : u.get_ship_pattern()) {
		if (pattern != last_pattern) {
			if (y > 6) {
				y = 1;
				x += 5;
			}
			else {
				y += 2;
				last_pattern = pattern;
			}
		}

		ships.push_back(Ship(u, b.get_fields(), pattern, x, y));

	}
}

bool ShipSettingState::is_adjacent() const {
	// czy statek przylega do innego statku
	for (Field f : ship_selected->getFieldsVector()) {
		for (Ship s : ships)
			if (*ship_selected != s and (s.field_in_vec(f, s.get_adjacent_fields()) or (s.field_in_vec(f, s.getFieldsVector()) && s.is_placed())))
				return true;
	}

	return false;
}

bool ShipSettingState::is_placing_done() const {
	for (Ship s : ships)
		if (!s.is_placed())
			return false;
	return true;
}

void ShipSettingState::calculate_mouse_board_pos() {
	mouse_board_pos_x = (u.get_mouseX() - b.get_x_offset()) / u.get_fSize();
	mouse_board_pos_y = (u.get_mouseY() - b.get_y_offset()) / u.get_fSize();
}

void ShipSettingState::rotate_ship() {
	vector<Field*> vec;
	calculate_mouse_board_pos();
	ship_selected = select_ship();
	if (ship_selected != NULL) {
		vec = create_array(mouse_board_pos_x, mouse_board_pos_y); // funkcja tworzy wektor wskaznikow NULL/Field* 9x9 z kliknietym punktem w srodku

		for (int i = 0; i < 3; i++) {
			rotateArray(vec);
			fitNewCoords(mouse_board_pos_x, mouse_board_pos_y, vec);
			if (can_rotate_ship(vec)) {
				replace_ships_vectors(ship_selected, vec);
				ship_selected->set_adjacent_fields();
				break;
			}

		}
	}
}

bool ShipSettingState::can_rotate_ship(vector<Field*> vec) {
	for (Field* f : vec) {
		if (f != NULL) {
			if (f->x < 0 or f->y < 0 or f->x >= u.get_bSize() or f->y >= u.get_bSize()) {
				return false;
			}
			for (Ship s : ships) {
				if (s.field_in_vec(*f, s.getFieldsVector()) and !s.field_in_vec(*f, ship_selected->getFieldsVector()))
					return false;
				if (s.field_in_vec(*f, s.get_adjacent_fields()) && s != *ship_selected) {
					return false;
				}
			}
		}
	}
	return true;
}

void ShipSettingState::replace_ships_vectors(Ship* s, vector<Field*> vec) {
	s->getFieldsVector().clear();
	for (Field* f : vec)
		if (f != NULL) {
			f->set_color(128, 255, 128);
			s->getFieldsVector().push_back(*f);
		}
}

void ShipSettingState::fitNewCoords(int middle_point_x, int middle_point_y, vector<Field*> vec) {
	for (int y = 0; y < 9; ++y) {
		for (int x = 0; x < 9; ++x) {
			if (vec.at(y * 9 + x) != NULL) {
				vec.at(y * 9 + x)->x = middle_point_x - 4 + x;
				vec.at(y * 9 + x)->y = middle_point_y - 4 + y;
				vec.at(y * 9 + x)->fit_render_coords();
			}
		}
	}
}

void ShipSettingState::rotateArray(vector<Field*>& vec) {
	vector<Field*>* rotatedVec = new vector<Field*>();
	for (int y = 8; y >= 0; --y) {
		for (int x = 0; x < 9; ++x) {
			rotatedVec->push_back(vec.at(x * 9 + y));
		}
	}
	for (int y = 0; y < 9; ++y)
		for (int x = 0; x < 9; ++x)
			vec.at(y * 9 + x) = rotatedVec->at(y * 9 + x);

	delete rotatedVec;
}

vector<Field*> ShipSettingState::create_array(int middle_point_x, int middle_point_y) {
	bool added = false;
	vector<Field*>* vec = new vector<Field*>();
	for (int y = middle_point_y - 4; y < middle_point_y + 5; ++y) {
		for (int x = middle_point_x - 4; x < middle_point_x + 5; ++x) {
			for (Field& f : ship_selected->getFieldsVector())
				if (f.x == x && f.y == y) {
					vec->push_back(new Field(f.x, f.y, b.get_x_offset(), b.get_y_offset(), u.get_fSize()));
					added = true;
					break;
				}

			if (!added) {
				vec->push_back(NULL);
			}
			added = false;
		}
	}
	return *vec;
}

void ShipSettingState::place_ships_randomly() {
	int x_val_to_sub = 0, y_val_to_sub = 0;							//losowe wartosci, ktore beda odejmowane od x,y pol staku aby statek znalazl sie na planszy
	for (Ship& s : ships)
		if (!s.is_placed()) {
			s.set_placed(true);
			ship_selected = &s;															//zaznacz statek
			Field* f = &s.getFieldsVector().at(rand() % s.getFieldsVector().size());	//wez losowe pole statku
			vector<Field*> vec = create_array(f->x, f->y);								//zrob tablice 9x9 wokol tego pola

			for (int i = 0; i < rand() % 4; ++i) {										//obroc statek kilka razy losowo
				rotateArray(vec);
				fitNewCoords(f->x, f->y, vec);
			}
			replace_ships_vectors(ship_selected, vec);									//podmien wektory
			while (true) {																//przemiesc statek o losowa wartosc tak aby byl na planszy
				x_val_to_sub = rand() % ((min_x(ship_selected)) - (max_x(ship_selected) - u.get_bSize() + 1)) + (max_x(ship_selected) - u.get_bSize() + 1);
				y_val_to_sub = rand() % ((min_y(ship_selected)) - (max_y(ship_selected) - u.get_bSize() + 1)) + (max_y(ship_selected) - u.get_bSize() + 1);
				for (Field& f : ship_selected->getFieldsVector()) {
					f.x -= x_val_to_sub;
					f.y -= y_val_to_sub;
					f.fit_render_coords();
				}
				if (is_adjacent()) {													//jesli statek jest na niedozwolonym polu to cofnij go z powrotem za plansze
					for (Field& f : ship_selected->getFieldsVector()) {
						f.x += x_val_to_sub;
						f.y += y_val_to_sub;
					}
				}
				else {
					s.set_adjacent_fields();
					s.set_placed(true);
					break;
				}

			}
		}
}

int ShipSettingState::max_x(Ship* s) {
	int max_x = s->getFieldsVector().at(0).x;
	for (Field f : s->getFieldsVector())
		if (f.x > max_x) max_x = f.x;
	return max_x;
}
int ShipSettingState::max_y(Ship* s) {
	int max_y = s->getFieldsVector().at(0).y;
	for (Field f : s->getFieldsVector())
		if (f.y > max_y) max_y = f.y;
	return max_y;
}
int ShipSettingState::min_x(Ship* s) {
	int min_x = s->getFieldsVector().at(0).x;
	for (Field f : s->getFieldsVector())
		if (f.x < min_x) min_x = f.x;
	return min_x;
}
int ShipSettingState::min_y(Ship* s) {
	int min_y = s->getFieldsVector().at(0).y;
	for (Field f : s->getFieldsVector())
		if (f.y < min_y) min_y = f.y;
	return min_y;
}

void ShipSettingState::assignStates(State** s, GameState* g, MenuState* m) {
	state = s;
	menuState = m;
	gameState = g;
}

void ShipSettingState::handle_ship_setting() {
	if (u.get_space_pressed())
		place_ships_randomly();

	// obracanie statku
	if (u.get_mouse_clicked2() && guard2) {
		rotate_ship();
		guard2 = false;
	}
	else if (!u.get_mouse_clicked2()) {
		guard2 = true;
	}

	// if wywolany tylko raz podczas klikniecia
	if (u.get_mouse_clicked1() && guard1) { // jak nie jest zaznaczony statek i zostanie kliknieta myszka
		ship_selected = select_ship(); // sproboj zaznaczyc statek
		if (ship_selected != NULL) {
			last_ship_position = ship_selected->getFieldsVector();
			last_ship_adjacent_fields = ship_selected->get_adjacent_fields();
			ship_selected->get_adjacent_fields().clear();
			ship_selected->set_color(255, 128, 0);
		}
		guard1 = false;
	}
	// wywolywane wieloktrotnie podczas przesuwania gdy myszka jest kliknieta
	else if (ship_selected != NULL && u.get_mouse_clicked1()) {// jesli udalo sie zaznaczyc statek to przeciagaj go po ekranie
		drag();
		set_ships_coords();


	}
	//wywolywane raz gdy myszka zostanie puszczona
	else if (ship_selected != NULL && !guard1) {
		if (can_place_ship() && !is_adjacent()) { // jesli statek mozna umiescic
			match_ship_screen_position();
			ship_selected->set_adjacent_fields();
			ship_selected->set_color(128, 255, 128);
			ship_selected->set_placed(true);
		}
		else { // jesli statku nie mozna umiescic
			ship_selected->setFieldsVector(last_ship_position);
			ship_selected->set_adjacent_fields(last_ship_adjacent_fields);
		}

		guard1 = true;
	}
	else
		guard1 = true;
}

void ShipSettingState::init_customizing_fields_vector() {
	customBoard.init_vec();
}

/*****************************BUTTONS FUNCTIONS**************************************/
void ShipSettingState::startGameButtonOnClick() {
	*state = gameState;
}

void ShipSettingState::menuButtonOnClick() {
	*state = menuState;
}

void ShipSettingState::confirmButtonOnClick() {
	u.set_custom_ship_mode(false);
}

void ShipSettingState::createShipButtonOnClick() {
	if (ship_selected->getFieldsVector().size() != 0) {
		substract_ship_quantity();
		ships.push_back(*ship_selected);
		ship_selected = new Ship(u, vector<Field>{}, 'i', 0, 0);
	}
}

void ShipSettingState::deleteShipButtonOnClick() {
	if (ship_selected != NULL)
		ship_selected->getFieldsVector().clear();
}

void ShipSettingState::assignCreationButtonsFunctions() {
	for (auto button : creationButtons) {
		button->onClickListener = [this](Button* btn) {
			switch (btn->getId()) {
			case ID::CREATESHIP:
				createShipButtonOnClick();
				break;
			case ID::DELETESHIP:
				deleteShipButtonOnClick();
				break;
			case ID::CONFIRM:
				confirmButtonOnClick();
				break;
			}
		};
	}
}

void ShipSettingState::assignShipSettingButtonsFunctions() {
	for (auto button : shipSettingButtons) {
		button->onClickListener = [this](Button* btn) {
			switch (btn->getId()) {
			case ID::MENU:
				menuButtonOnClick();
				break;
			case ID::STARTGAME:
				startGameButtonOnClick();
				break;
			}
		};
	}
}

void ShipSettingState::handle_buttons_events() {
	for (Button* b : *buttonsToDisplay) {
		//jeœli myszka najedzie na button
		if (u.isMouseInRectangle(b->x, b->y, b->w, b->h) && !b->isActive && b->canBeClicked) {
			if (u.get_sounds_on())
				al_play_sample(selected, 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
			b->isActive = true;
		}
		//jeœli myszka zjedzie z buttona
		if (!u.isMouseInRectangle(b->x, b->y, b->w, b->h) && b->isActive) {
			b->isActive = false;
		}
		//jeœli button zosanie wcisniety
		if (b->isActive && b->canBeClicked && u.get_mouse_clicked1() && guard3) {
			if (u.get_sounds_on())
				al_play_sample(clicked, 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
			b->onClickListener(b);
			guard3 = false;
		}

		if (!u.get_mouse_clicked1())
			guard3 = true;
	}
}

void ShipSettingState::handle_ship_creation() {
	field_selected = customBoard.getFieldSelectedByMouse();
	createShipButton.canBeClicked = ship_selected->getFieldsVector().size() < min_ship_size_to_create() ? false : true;
	deleteShipButton.canBeClicked = ship_selected->getFieldsVector().size() == 0 ? false : true;
	if (field_selected != NULL && u.get_mouse_clicked1() && can_append_field_to_ship(field_selected, ship_selected)) {
		if (!ship_selected->field_in_vec(*field_selected, ship_selected->getFieldsVector())) {
			Field* newField = new Field(field_selected->x, field_selected->y, customBoard.get_x_offset(), customBoard.get_y_offset(), u.get_fSize());
			newField->set_color(255, 128, 0);
			ship_selected->getFieldsVector().push_back(*newField);
		}
	}

}

bool ShipSettingState::can_append_field_to_ship(Field* f, Ship* s) {
	if (f == NULL or s == NULL)
		return false;

	if (s->getFieldsVector().size() == 0)
		return true;

	if (s->getFieldsVector().size() == max_ship_size_to_create())
		return false;

	if (s->field_in_vec(*f, s->getFieldsVector()))
		return false;

	int x = f->x, y = f->y, w = customBoard.get_width();

	if (y + 1 < customBoard.get_height())
		if (s->field_in_vec(customBoard.get_fields().at((y + 1) * w + x), s->getFieldsVector()))
			return true;

	if (x + 1 < customBoard.get_width())
		if (s->field_in_vec(customBoard.get_fields().at(y * w + x + 1), s->getFieldsVector()))
			return true;

	if (y - 1 >= 0)
		if (s->field_in_vec(customBoard.get_fields().at((y - 1) * w + x), s->getFieldsVector()))
			return true;

	if (x - 1 >= 0)
		if (s->field_in_vec(customBoard.get_fields().at(y * w + x - 1), s->getFieldsVector()))
			return true;

	return false;
}

void ShipSettingState::set_ships_quantity() {
	quantity1 = u.get_quantity1();
	quantity2 = u.get_quantity2();
	quantity3 = u.get_quantity3();
	quantity4 = u.get_quantity4();
	quantity5 = u.get_quantity5();
}

unsigned ShipSettingState::max_ship_size_to_create() {
	if (quantity5 > 0) return 5;
	if (quantity4 > 0) return 4;
	if (quantity3 > 0) return 3;
	if (quantity2 > 0) return 2;
	if (quantity1 > 0) return 1;
	return 0;
}
unsigned ShipSettingState::min_ship_size_to_create() {
	if (quantity1 > 0) return 1;
	if (quantity2 > 0) return 2;
	if (quantity3 > 0) return 3;
	if (quantity4 > 0) return 4;
	if (quantity5 > 0) return 5;
	return 0;
}
void ShipSettingState::substract_ship_quantity() {
	if (ship_selected->getFieldsVector().size() == 5) quantity5--;
	if (ship_selected->getFieldsVector().size() == 4) quantity4--;
	if (ship_selected->getFieldsVector().size() == 3) quantity3--;
	if (ship_selected->getFieldsVector().size() == 2) quantity2--;
	if (ship_selected->getFieldsVector().size() == 1) quantity1--;
}

void ShipSettingState::set_buttons_to_display() {
	buttonsToDisplay = u.get_custom_ship_mode() ? &creationButtons : &shipSettingButtons;
}