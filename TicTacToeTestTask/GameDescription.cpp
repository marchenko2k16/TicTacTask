#include "GameDescription.h"

bool GameDescription::isPlayerTurn;

unsigned int GameDescription::moveCount;

std::pair<unsigned int, unsigned int> GameDescription::score;

CellState GameDescription::playerSymbol;

CellState GameDescription::opponentSymbol;


void GameDescription::chooseSide()
{
	std::string sideFlag;
	bool wrongInput = true;
	
	std::cout << "Choose your side destiny" << std::endl
		<< R"(Input "x" to play for X)" << std::endl
		<< R"(Input "o" to play for O)" << std::endl;

	while (wrongInput) {
		std::getline(std::cin, sideFlag);
		if (sideFlag == "o")
		{
			playerSymbol = CellState::O;
			opponentSymbol = CellState::X;
			wrongInput = false;
		}
		else if (sideFlag == "x")
		{
			playerSymbol = CellState::X;
			opponentSymbol = CellState::O;
			wrongInput = false;
		}
		else
		{
			std::cout << "Wrong input, try again:\n";
		}
	}
	Render::clearCmd();
}

void GameDescription::rules()
{

	std::ifstream readFrom("assets//preview");
	std::stringstream ss;
	ss << readFrom.rdbuf();
	std::string printStr = ss.str();

	for (int i = 0; i < printStr.length(); i++)
	{
		std::cout << printStr[i];
		Sleep(1);
	}
	std::cin.get();
	Render::clearCmd();
}
