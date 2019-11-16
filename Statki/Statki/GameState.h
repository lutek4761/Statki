#pragma once
#include "State.h"
#include "Utils.h"
class GameState : public State
{
private:
	Utils& u;
public:
	GameState(Utils& u);
	~GameState();
	virtual void render();
	virtual void tick();
};

