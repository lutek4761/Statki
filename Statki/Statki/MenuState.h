#pragma once

#include "Utils.h"
#include "Button.h"
#include <string>
#include "State.h"
#include <vector>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <iostream>

class GameState;
class ShipSettingState;
class MenuState : public State
{
private:

	bool guard, optionState, changedSettings, runForTheFirstTime;
	Utils& u;
	ALLEGRO_FONT* font30, * font20;
	vector<Button*> mainMenuButtons;
	vector<Button*> optionsMenuButtons;
	vector<Button*>* buttonsToDisplay;
	State** state;
	GameState* gameState;
	ShipSettingState* shipSettingState;

	bool rCustomShip;
	unsigned rQuantity1, rQuantity2, rQuantity3, rQuantity4, rQuantity5;

	/***********BUTTONS**********/
	Button customCheckBox;
	Button soundCheckBox;
	Button resumeButton;
	Button applyButton;
	Button optionsButton;
	Button exitButton;
	Button backButton;
	Button inc1Button;
	Button dec1Button;
	Button inc2Button;
	Button dec2Button;
	Button inc3Button;
	Button dec3Button;
	Button inc4Button;
	Button dec4Button;
	Button inc5Button;
	Button dec5Button;

	ALLEGRO_SAMPLE* clicked, * selected;
	friend class Utils;

	void drawOtherMenuStuffs();
	void handleIncDecButtons();
	void rememberSettings();
	void applySettings();


	/*****ON CLICK FUNCTIONS******/
	void customCheckBoxOnClick();
	void soundCheckBoxOnClick();
	void resumeButtonOnClick();
	void optionsButtonOnClick();
	void applyButtonOnClick();
	void exitButtonOnClick();
	void backButtonOnClick();
	void inc1ButtonOnClick();
	void dec1ButtonOnClick();
	void inc2ButtonOnClick();
	void dec2ButtonOnClick();
	void inc3ButtonOnClick();
	void dec3ButtonOnClick();
	void inc4ButtonOnClick();
	void dec4ButtonOnClick();
	void inc5ButtonOnClick();
	void dec5ButtonOnClick();
public:
	MenuState(Utils& u);
	~MenuState();
	virtual void render();
	virtual void tick();

	void assingFunctions();
	void assignStates(State**, GameState*, ShipSettingState*);
	bool getChangedShips() { return changedSettings; }


};

