#include "Bot.h"

BotLvl Bot::botLvl;

void Bot::setBotLvl()
{
	std::cout <<
		"Input 0 to choose random bot\n"
		"Or input 1 to choose the expert one\n"
		"And press enter...\n";
	bool botFlag;
	std::cin >> botFlag;
	switch (botFlag)
	{
	case false:
		Bot::botLvl = BotLvl::LOW;
		break;
	case true:
		Bot::botLvl = BotLvl::NORMAL;
		break;
	}
}
std::pair<unsigned int, unsigned int> Bot::move()
{
	//////////////////////////////////////////////////////////////
	Sleep(1000);
	switch (Bot::botLvl)
	{
	case BotLvl::LOW:
		return Bot::lowMove();
		break;
	case BotLvl::NORMAL:
		return Bot::normalMove();
		break;
	}
}


std::pair<unsigned int, unsigned int> Bot::lowMove()
{

	std::vector<std::pair<unsigned int, unsigned int>> emptyCells;

	for (auto i = 0; i < Field::fieldSize; ++i)
	{
		for (auto j = 0; j < Field::fieldSize; ++j)
		{
			if (Field::gameField[i][j].cellState == CellState::EMPTY)
				emptyCells.push_back(std::pair<unsigned int, unsigned int>(i,j));
		}
	}
	unsigned int randCell = Random::random(0, emptyCells.size());
	return emptyCells.at(randCell);

}

std::pair<unsigned int, unsigned int> Bot::normalMove()
{
	std::pair<unsigned int, unsigned int> moveVar;

	CellState fillCell;
	CellState currentOponentCell;
	GameDescription::isPlayerTurn ? 
		fillCell = GameDescription::playerSymbol, currentOponentCell = GameDescription::opponentSymbol :
		currentOponentCell = GameDescription::opponentSymbol, currentOponentCell = GameDescription::playerSymbol;

	if (GameDescription::moveCount < 2)
	{
		return Bot::lowMove();
	}

	unsigned int countOpponent = 0;
	unsigned int row, col;

	for (unsigned int i = 0, j; i < Field::fieldSize; ++i)
	{
		unsigned int innerCountOpponentRow = 0, countEmptyRow = 0;
		for (j = 0; j < Field::fieldSize; ++j)
		{
			if (Field::gameField[i][j].cellState == currentOponentCell)
			{
				++innerCountOpponentRow;
			}
			else if (Field::gameField[i][j].cellState == CellState::EMPTY)
			{
				++countEmptyRow;
				row = i;
				col = j;
			}
		}
			if (innerCountOpponentRow > countOpponent && countEmptyRow > 0)
			{
				moveVar.first = row;
				moveVar.second = col;
				countOpponent = innerCountOpponentRow;
			}
	}

	for (unsigned int i = 0, j; i < Field::fieldSize; ++i)
	{
		unsigned int innerCountOpponentRow = 0, countEmptyRow = 0;
		for (j = 0; j < Field::fieldSize; ++j)
		{
			if (Field::gameField[j][i].cellState == currentOponentCell)
			{
				++innerCountOpponentRow;
			}
			else if (Field::gameField[j][i].cellState == CellState::EMPTY)
			{
				++countEmptyRow;
				row = j;
				col = i;
			}
		}
		if (innerCountOpponentRow > countOpponent && countEmptyRow > 0)
		{
			moveVar.first = row;
			moveVar.second = col;
			countOpponent = innerCountOpponentRow;
		}
	}

	return moveVar;
}

