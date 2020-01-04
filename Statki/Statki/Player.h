#pragma once
#include <Windows.h>
class Player
{
public:

	virtual void render() = 0;
	virtual void tick() = 0;
};

