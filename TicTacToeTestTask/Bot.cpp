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
}

std::pair<unsigned int, unsigned int> Bot::move()
{
	//////////////////////////////////////////////////////////////
	Sleep(100);
	switch (Bot::botLvl)
	{
	case BotLvl::LOW:
		return Bot::lowMove();
		break;
	case BotLvl::EXPERT:
		return Bot::expertMove();
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

std::pair<unsigned int, unsigned int> Bot::expertMove()
{
	return std::pair<unsigned int, unsigned int>();
}

Bot::Bot(BotLvl _botLvl = BotLvl::EXPERT)
{
	botLvl = _botLvl;
}
