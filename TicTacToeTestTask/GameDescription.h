#pragma once

#include "Cell.h"
#include <utility>
#include <iostream>
#include <string>
#include <fstream>
#include "Render.h"

class GameDescription
{
public:
	//your score -- //opponent score
	static std::pair<unsigned int, unsigned int> score;
	static bool isPlayerTurn;
	static unsigned int moveCount;
	static CellState playerSymbol;
	static CellState opponentSymbol;
	static void chooseSide();
	static void rules();

};

