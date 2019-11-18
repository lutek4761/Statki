#include "MenuState.h"
#include "GameState.h"
#include "ShipSettingState.h"
using namespace std;


MenuState::MenuState(Utils& u)
	:u(u), guard(true), optionState(false), rQuantity1(u.get_quantity1()), rQuantity2(u.get_quantity2()),
	rQuantity3(u.get_quantity3()), rQuantity4(u.get_quantity4()), rQuantity5(u.get_quantity5()), shipsQuantityChanged(false), runForTheFirstTime(true)
{
	al_init_font_addon();
	al_init_ttf_addon();
	font30 = al_load_font("Arial.ttf", 30, 0);
	font20 = al_load_font("Arial.ttf", 20, 0);
	clicked = u.get_clicked_sound();
	selected = u.get_selected_sound();

	/****************************************BUTTONS****************************************/
	customCheckBox = Button(500, 75, 150, 50, "Custom Ships", ID::CUSTOMCHECKBOX);
	soundCheckBox = Button(500, 150, 150, 50, "Sound", ID::SOUNDCHECKBOX);
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
	&inc5Button,&dec5Button,&backButton,&customCheckBox,&soundCheckBox,&applyButton };

	buttonsToDisplay = &mainMenuButtons;
	assingFunctions();
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
		if (b->isActive && b->canBeClicked && u.get_mouse_clicked1() && guard) {
			if (u.get_sounds_on())
				al_play_sample(clicked, 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
			b->onClickListener(b);
			handleIncDecButtons();
			guard = false;
		}

		if (!u.get_mouse_clicked1())
			guard = true;
	}
}

void MenuState::resumeButtonOnClick() {
	if (u.get_ship_setting_done())
		*state = gameState;
	else {
		*state = shipSettingState;
		shipSettingState->set_buttons_to_display();
		if (shipSettingState->get_ship_selected() == NULL)
			shipSettingState->set_ship_selected(new Ship(u, vector<Field>{}, 'i', 0, 0));

		if (u.get_custom_ship_mode()) {
			if (shipsQuantityChanged || runForTheFirstTime) {
				shipSettingState->init_customizing_fields_vector();
				shipSettingState->set_ships_quantity();
				shipSettingState->delete_icons();
			}
		}
		else {
			//shipSettingState->prepare_ships_for_setting(); // default
		}

		shipsQuantityChanged = false;

	}
	runForTheFirstTime = false;
}
void MenuState::applyButtonOnClick() {
	applySettings();
}

void MenuState::customCheckBoxOnClick() {
	u.set_custom_ship_mode(!u.get_custom_ship_mode());
}

void MenuState::soundCheckBoxOnClick() {
	u.set_sounds_on(!u.get_sounds_on());
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
	u.reset_ship_pattern();
}

void MenuState::inc1ButtonOnClick() {
	rQuantity1++;
	u.numberOfAvailableFields -= 9;
}

void MenuState::dec1ButtonOnClick() {
	rQuantity1--;
	u.numberOfAvailableFields += 9;
}

void MenuState::inc2ButtonOnClick() {
	rQuantity2++;
	u.numberOfAvailableFields -= 12;
}

void MenuState::dec2ButtonOnClick() {
	rQuantity2--;
	u.numberOfAvailableFields += 12;
}

void MenuState::inc3ButtonOnClick() {
	rQuantity3++;
	u.numberOfAvailableFields -= 15;
}

void MenuState::dec3ButtonOnClick() {
	rQuantity3--;
	u.numberOfAvailableFields += 15;
}

void MenuState::inc4ButtonOnClick() {
	rQuantity4++;
	u.numberOfAvailableFields -= 18;
}

void MenuState::dec4ButtonOnClick() {
	rQuantity4--;
	u.numberOfAvailableFields += 18;
}

void MenuState::inc5ButtonOnClick() {
	rQuantity5++;
	u.numberOfAvailableFields -= 21;
}

void MenuState::dec5ButtonOnClick() {
	rQuantity5--;
	u.numberOfAvailableFields += 21;
}


void MenuState::assingFunctions() {
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
	al_draw_textf(font30, al_map_rgb(255, 255, 255), 270, 60, 0, "%d", rQuantity1);
	al_draw_textf(font30, al_map_rgb(255, 255, 255), 270, 140, 0, "%d", rQuantity2);
	al_draw_textf(font30, al_map_rgb(255, 255, 255), 270, 220, 0, "%d", rQuantity3);
	al_draw_textf(font30, al_map_rgb(255, 255, 255), 270, 300, 0, "%d", rQuantity4);
	al_draw_textf(font30, al_map_rgb(255, 255, 255), 270, 380, 0, "%d", rQuantity5);

	al_draw_textf(font20, al_map_rgb(255, 255, 255), 550, 25, 0, "Available fields: %d", u.numberOfAvailableFields);
	al_draw_textf(font30, al_map_rgb(255, 255, 255), 675, 75, 0, "%s", u.get_custom_ship_mode() ? "ON" : "OFF");
	al_draw_textf(font30, al_map_rgb(255, 255, 255), 675, 150, 0, "%s", u.get_sounds_on() ? "ON" : "OFF");

	al_draw_text(font30, al_map_rgb(255, 255, 255), 40, 60, 0, "One-masted ship: "); // 1
	al_draw_text(font30, al_map_rgb(255, 255, 255), 40, 140, 0, "Two-masted ship: "); // 2
	al_draw_text(font30, al_map_rgb(255, 255, 255), 40, 220, 0, "Three-masted ship: "); // 3
	al_draw_text(font30, al_map_rgb(255, 255, 255), 40, 300, 0, "Four-masted ship: "); // 4
	al_draw_text(font30, al_map_rgb(255, 255, 255), 40, 380, 0, "Five-masted ship: "); // 5

	if (applyButton.isActive)
		al_draw_text(font20, al_map_rgb(255, 255, 255), 525, 450, 0, "This will reset your ships. ");

}

void MenuState::handleIncDecButtons() {
	dec1Button.canBeClicked = (u.get_quantity1() == 0) ? false : true;
	dec2Button.canBeClicked = (u.get_quantity2() == 0) ? false : true;
	dec3Button.canBeClicked = (u.get_quantity3() == 0) ? false : true;
	dec4Button.canBeClicked = (u.get_quantity4() == 0) ? false : true;
	dec5Button.canBeClicked = (u.get_quantity5() == 0) ? false : true;

	inc1Button.canBeClicked = (u.numberOfAvailableFields < 9) ? false : true;
	inc2Button.canBeClicked = (u.numberOfAvailableFields < 12) ? false : true;
	inc3Button.canBeClicked = (u.numberOfAvailableFields < 15) ? false : true;
	inc4Button.canBeClicked = (u.numberOfAvailableFields < 18) ? false : true;
	inc5Button.canBeClicked = (u.numberOfAvailableFields < 21) ? false : true;
}

void MenuState::assignStates(State** s, GameState* g, ShipSettingState* ss) {
	state = s;
	gameState = g;
	shipSettingState = ss;
}

void MenuState::rememberSettings() {
	rQuantity1 = u.get_quantity1();
	rQuantity2 = u.get_quantity2();
	rQuantity3 = u.get_quantity3();
	rQuantity4 = u.get_quantity4();
	rQuantity5 = u.get_quantity5();
}

void MenuState::applySettings() {
	if (rQuantity1 != u.get_quantity1() ||
		rQuantity2 != u.get_quantity2() ||
		rQuantity3 != u.get_quantity3() ||
		rQuantity4 != u.get_quantity4() ||
		rQuantity5 != u.get_quantity5()) {
		u.set_quantity1(rQuantity1);
		u.set_quantity2(rQuantity2);
		u.set_quantity3(rQuantity3);
		u.set_quantity4(rQuantity4);
		u.set_quantity5(rQuantity5);
		shipsQuantityChanged = true;
		shipSettingState->get_ships().clear();
		if (shipSettingState->get_ship_selected() != NULL)
			shipSettingState->get_ship_selected()->getFieldsVector().clear();
	}

}