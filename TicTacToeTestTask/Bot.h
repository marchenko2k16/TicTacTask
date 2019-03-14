#pragma once

#include <iostream>
#include <vector>
#include "Engine.h"


enum class BotLvl{LOW, NORMAL};



class Bot
{
protected:
	static std::pair<unsigned int, unsigned int> lowMove();
	static std::pair<unsigned int, unsigned int> normalMove(); //in progres


public:

	static BotLvl botLvl;
	static void setBotLvl();
	static std::pair<unsigned int, unsigned int> move();
	
};

