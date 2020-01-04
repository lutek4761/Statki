#include "MenuState.h"
#include "GameState.h"
#include "ShipSettingState.h"
using namespace std;


MenuState::MenuState()
	:guard(true), optionState(false), rQuantity1(Utils::get_quantity1()), rQuantity2(Utils::get_quantity2()),
	rQuantity3(Utils::get_quantity3()), rQuantity4(Utils::get_quantity4()), rQuantity5(Utils::get_quantity5()), changedSettings(false), runForTheFirstTime(true),
	rCustomShip(true)
{
	
	clicked = Utils::get_clicked_sound();
	selected = Utils::get_selected_sound();

	/****************************************BUTTONS****************************************/
	customCheckBox = Button(500, 75, 150, 50, "Custom Ships", ID::CUSTOMCHECKBOX);
	soundCheckBox = Button(500, 150, 150, 50, "Sound", ID::SOUNDCHECKBOX);
	showAdjacentFieldsCheckBox = Button(500, 225, 150, 50, "Show Adjacent", ID::ADJACENTCHECKBOX);
	resumeButton = Button(375, 100, 150, 50, "Play", ID::PLAY);
	optionsButton = Button(375, 200, 150, 50, "Options", ID::OPTIONS);
	exitButton = Button(375, 300, 150, 50, "Exit", ID::EXIT);
	backButton = Button(720, 400, 150, 50, "Back", ID::BACK);
	applyButton = Button(550, 400, 150, 50, "Apply", ID::APPLY);
	inc1Button = Button(320, 50, 25, 25, "/\\", ID::INC1);
	dec1Button = Button(320, 76, 25, 25, "\\/", ID::DEC1);
	inc2Button = Button(320, 130, 25, 25, "/\\", ID::INC2);
	dec2Button = Button(320, 156, 25, 25, "\\/", ID::DEC2);
	inc3Button = Button(320, 210, 25, 25, "/\\", ID::INC3);
	dec3Button = Button(320, 236, 25, 25, "\\/", ID::DEC3);
	inc4Button = Button(320, 290, 25, 25, "/\\", ID::INC4);
	dec4Button = Button(320, 316, 25, 25, "\\/", ID::DEC4);
	inc5Button = Button(320, 370, 25, 25, "/\\", ID::INC5);
	dec5Button = Button(320, 396, 25, 25, "\\/", ID::DEC5);

	mainMenuButtons = vector<Button*>{ &resumeButton , &optionsButton, &exitButton };
	optionsMenuButtons = vector<Button*>{ &inc1Button, &dec1Button, &inc2Button, &dec2Button, &inc3Button, &dec3Button, &inc4Button, &dec4Button,
	&inc5Button,&dec5Button,&backButton,&customCheckBox,&soundCheckBox,&applyButton, &showAdjacentFieldsCheckBox };

	buttonsToDisplay = &mainMenuButtons;
	assignFunctions();
	handleIncDecButtons();
}

MenuState::~MenuState() {}

void MenuState::render() {
	for (Button* button : *buttonsToDisplay)
		button->render();
	if (optionState)
		drawOtherMenuStuffs();
}

void MenuState::tick() {
	for (Button* b : *buttonsToDisplay) {
		//je�li myszka najedzie na button
		if (Utils::isMouseInRectangle(b->x, b->y, b->w, b->h) && !b->isActive && b->canBeClicked) {
			if (Utils::get_sounds_on())
				al_play_sample(selected, 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
			b->isActive = true;
		}
		//je�li myszka zjedzie z buttona
		if (!Utils::isMouseInRectangle(b->x, b->y, b->w, b->h) && b->isActive) {
			b->isActive = false;
		}
		//je�li button zosanie wcisniety
		if (b->isActive && b->canBeClicked && Utils::get_mouse_clicked1() && guard) {
			if (Utils::get_sounds_on())
				al_play_sample(clicked, 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
			b->onClickListener(b);
			handleIncDecButtons();
			guard = false;
		}

		if (!Utils::get_mouse_clicked1())
			guard = true;
	}
}

void MenuState::resumeButtonOnClick() {
	
	*state = shipSettingState;
	shipSettingState->set_buttons_to_display();
	if (shipSettingState->get_ship_selected() == NULL)
		shipSettingState->set_ship_selected(new Ship(vector<Field>{}, 'i', 0, 0));

	if (Utils::get_custom_ship_mode() and (changedSettings or runForTheFirstTime)) {
		shipSettingState->init_customizing_fields_vector();
		shipSettingState->set_ships_quantity();
		shipSettingState->delete_icons();
	}
	else if (changedSettings or runForTheFirstTime) {
		shipSettingState->delete_icons();
		shipSettingState->prepare_ships_for_setting();
	}	
	changedSettings = false;
	runForTheFirstTime = false;
}
void MenuState::showAdjacentFieldsCheckBoxOnClick() {
	Utils::set_show_adjacent_mode(!Utils::get_show_adjacent_mode());
}
void MenuState::applyButtonOnClick() {
	applySettings();
}

void MenuState::customCheckBoxOnClick() {
	rCustomShip = !rCustomShip;
}

void MenuState::soundCheckBoxOnClick() {
	Utils::set_sounds_on(!Utils::get_sounds_on());
}

void MenuState::optionsButtonOnClick() {
	buttonsToDisplay = &optionsMenuButtons;
	optionState = true;
	rememberSettings();
}

void MenuState::exitButtonOnClick() {
	exit(0);
}

void MenuState::backButtonOnClick() {
	buttonsToDisplay = &mainMenuButtons;
	optionState = false;
	Utils::reset_ship_pattern();
}

void MenuState::inc1ButtonOnClick() {
	rQuantity1++;
	Utils::numberOfAvailableFields -= 9;
}

void MenuState::dec1ButtonOnClick() {
	rQuantity1--;
	Utils::numberOfAvailableFields += 9;
}

void MenuState::inc2ButtonOnClick() {
	rQuantity2++;
	Utils::numberOfAvailableFields -= 12;
}

void MenuState::dec2ButtonOnClick() {
	rQuantity2--;
	Utils::numberOfAvailableFields += 12;
}

void MenuState::inc3ButtonOnClick() {
	rQuantity3++;
	Utils::numberOfAvailableFields -= 15;
}

void MenuState::dec3ButtonOnClick() {
	rQuantity3--;
	Utils::numberOfAvailableFields += 15;
}

void MenuState::inc4ButtonOnClick() {
	rQuantity4++;
	Utils::numberOfAvailableFields -= 18;
}

void MenuState::dec4ButtonOnClick() {
	rQuantity4--;
	Utils::numberOfAvailableFields += 18;
}

void MenuState::inc5ButtonOnClick() {
	rQuantity5++;
	Utils::numberOfAvailableFields -= 21;
}

void MenuState::dec5ButtonOnClick() {
	rQuantity5--;
	Utils::numberOfAvailableFields += 21;
}


void MenuState::assignFunctions() {
	for (auto button : mainMenuButtons) {
		button->onClickListener = [this](Button* btn) {
			switch (btn->getId()) {
			case ID::PLAY:
				resumeButtonOnClick();
				break;
			case ID::OPTIONS:
				optionsButtonOnClick();
				break;
			case ID::EXIT:
				exitButtonOnClick();
				break;
			}
		};
	}

	for (Button* button : optionsMenuButtons) {
		button->onClickListener = [this](Button* btn) {
			switch (btn->getId()) {
			case ID::ADJACENTCHECKBOX:
				showAdjacentFieldsCheckBoxOnClick();
				break;
			case ID::APPLY:
				applyButtonOnClick();
				break;
			case ID::BACK:
				backButtonOnClick();
				break;
			case ID::CUSTOMCHECKBOX:
				customCheckBoxOnClick();
				break;
			case ID::SOUNDCHECKBOX:
				soundCheckBoxOnClick();
				break;
			case ID::INC1:
				inc1ButtonOnClick();
				break;
			case ID::DEC1:
				dec1ButtonOnClick();
				break;
			case ID::INC2:
				inc2ButtonOnClick();
				break;
			case ID::DEC2:
				dec2ButtonOnClick();
				break;
			case ID::INC3:
				inc3ButtonOnClick();
				break;
			case ID::DEC3:
				dec3ButtonOnClick();
				break;
			case ID::INC4:
				inc4ButtonOnClick();
				break;
			case ID::DEC4:
				dec4ButtonOnClick();
				break;
			case ID::INC5:
				inc5ButtonOnClick();
				break;
			case ID::DEC5:
				dec5ButtonOnClick();
				break;
			}
		};
	}
}

void MenuState::drawOtherMenuStuffs() {
	al_draw_rectangle(25, 25, 475, 450, al_map_rgb(255, 0, 0), 2);
	al_draw_textf(Utils::get_font_30(), al_map_rgb(255, 255, 255), 270, 60, 0, "%d", rQuantity1);
	al_draw_textf(Utils::get_font_30(), al_map_rgb(255, 255, 255), 270, 140, 0, "%d", rQuantity2);
	al_draw_textf(Utils::get_font_30(), al_map_rgb(255, 255, 255), 270, 220, 0, "%d", rQuantity3);
	al_draw_textf(Utils::get_font_30(), al_map_rgb(255, 255, 255), 270, 300, 0, "%d", rQuantity4);
	al_draw_textf(Utils::get_font_30(), al_map_rgb(255, 255, 255), 270, 380, 0, "%d", rQuantity5);

	al_draw_textf(Utils::get_font_20(), al_map_rgb(255, 255, 255), 550, 25, 0, "Available fields: %d", Utils::numberOfAvailableFields);
	al_draw_textf(Utils::get_font_30(), al_map_rgb(255, 255, 255), 675, 75, 0, "%s", rCustomShip ? "ON" : "OFF");
	al_draw_textf(Utils::get_font_30(), al_map_rgb(255, 255, 255), 675, 150, 0, "%s", Utils::get_sounds_on() ? "ON" : "OFF");
	al_draw_textf(Utils::get_font_30(), al_map_rgb(255, 255, 255), 675, 225, 0, "%s", Utils::get_show_adjacent_mode() ? "ON" : "OFF");

	al_draw_text(Utils::get_font_30(), al_map_rgb(255, 255, 255), 40, 60, 0, "One-masted ship: "); // 1
	al_draw_text(Utils::get_font_30(), al_map_rgb(255, 255, 255), 40, 140, 0, "Two-masted ship: "); // 2
	al_draw_text(Utils::get_font_30(), al_map_rgb(255, 255, 255), 40, 220, 0, "Three-masted ship: "); // 3
	al_draw_text(Utils::get_font_30(), al_map_rgb(255, 255, 255), 40, 300, 0, "Four-masted ship: "); // 4
	al_draw_text(Utils::get_font_30(), al_map_rgb(255, 255, 255), 40, 380, 0, "Five-masted ship: "); // 5

	if (applyButton.isActive)
		al_draw_text(Utils::get_font_20(), al_map_rgb(255, 255, 255), 525, 450, 0, "This will reset your ships. ");

}

void MenuState::handleIncDecButtons() {
	dec1Button.canBeClicked = (rQuantity1 == 0) ? false : true;
	dec2Button.canBeClicked = (rQuantity2 == 0) ? false : true;
	dec3Button.canBeClicked = (rQuantity3 == 0) ? false : true;
	dec4Button.canBeClicked = (rQuantity4 == 0) ? false : true;
	dec5Button.canBeClicked = (rQuantity5 == 0) ? false : true;

	inc1Button.canBeClicked = (Utils::numberOfAvailableFields < 9) ? false : true;
	inc2Button.canBeClicked = (Utils::numberOfAvailableFields < 12) ? false : true;
	inc3Button.canBeClicked = (Utils::numberOfAvailableFields < 15) ? false : true;
	inc4Button.canBeClicked = (Utils::numberOfAvailableFields < 18) ? false : true;
	inc5Button.canBeClicked = (Utils::numberOfAvailableFields < 21) ? false : true;
}

void MenuState::assignStates(State** s, GameState* g, ShipSettingState* ss) {
	state = s;
	gameState = g;
	shipSettingState = ss;
}

void MenuState::rememberSettings() {
	rQuantity1 = Utils::get_quantity1();
	rQuantity2 = Utils::get_quantity2();
	rQuantity3 = Utils::get_quantity3();
	rQuantity4 = Utils::get_quantity4();
	rQuantity5 = Utils::get_quantity5();
	rCustomShip = Utils::get_custom_ship_mode();
}

void MenuState::applySettings() {
	if (rQuantity1 != Utils::get_quantity1() ||
		rQuantity2 != Utils::get_quantity2() ||
		rQuantity3 != Utils::get_quantity3() ||
		rQuantity4 != Utils::get_quantity4() ||
		rQuantity4 != Utils::get_quantity4() ||
		rQuantity5 != Utils::get_quantity5() ||
		rCustomShip != Utils::get_custom_ship_mode()) {
		Utils::set_quantity1(rQuantity1);
		Utils::set_quantity2(rQuantity2);
		Utils::set_quantity3(rQuantity3);
		Utils::set_quantity4(rQuantity4);
		Utils::set_quantity5(rQuantity5);
		Utils::set_custom_ship_mode(rCustomShip);
		changedSettings = true;
		shipSettingState->get_ships().clear();
		if (shipSettingState->get_ship_selected() != NULL)
			shipSettingState->get_ship_selected()->getFieldsVector().clear();
	}

}