#include "Engine.h"

std::chrono::steady_clock Engine::clock;
std::pair<short int, short int> Engine::score;



bool Engine::checkRows(CellState cs)
{
	bool check = false;
	unsigned int count = 1;
	for (auto i = 0; i < Field::fieldSize; ++i)
	{
		for (auto j = 0; j < Field::fieldSize - 1; ++j)
		{
			if (cs == Field::gameField[i][j].cellState &&
				Field::gameField[i][j].cellState == Field::gameField[i][j + 1].cellState)
			{
				++count;
 				if (count == Field::fieldSize)
				{
					check = true;
				}
			}
		}
		count = 1;
	}
	return check;
}

bool Engine::checkColumn(CellState cs)
{
	bool check = false;
	unsigned int count = 1;
	for (auto i = 0; i < Field::fieldSize; ++i)
	{
		for (auto j = 0; j < Field::fieldSize - 1; ++j)
		{
			if (cs == Field::gameField[j][i].cellState &&
				Field::gameField[j][i].cellState == Field::gameField[j + 1][i].cellState)
			{
				++count;
				if (count == Field::fieldSize) 
				{
					check = true; 
				}
			}
		}
		count = 1;
	}
	return check;
}

bool Engine::checkDiagonal(CellState cs)
{
	bool check = false;
	unsigned int count = 0;
	for (auto i = 0; i < Field::fieldSize; ++i)
	{
		if (cs == Field::gameField[i][i].cellState) ++count;
	}
	if (count == Field::fieldSize) 
	{
		check = true; 
	}
	
	count = 0;

	for (auto i = 0; i < Field::fieldSize; ++i)
	{
		if (cs == Field::gameField[i][Field::fieldSize - 1 - i].cellState) ++count;
	}
	if (count == Field::fieldSize) 
	{
		check = true; 
	}
	
	return check;
}

void Engine::checkField()
{
	if (checkRows(GameDescription::playerSymbol) ||
		checkColumn(GameDescription::playerSymbol) ||
		checkDiagonal(GameDescription::playerSymbol))
	{
		gameState = GameState::Win;
	}
	else if ((checkColumn(GameDescription::opponentSymbol) ||
		checkRows(GameDescription::opponentSymbol) ||
		checkDiagonal(GameDescription::opponentSymbol)))
	{
		gameState = GameState::Lose;
	}
	else if (GameDescription::moveCount == Field::fieldSize * Field::fieldSize)
		gameState = GameState::Draw;
	
	//check for out
	try
	{
		if (GameDescription::moveCount > Field::fieldSize * Field::fieldSize)
		{
			throw "Potential out of range";
		}
	}
	catch (char *str)
	{
		std::cout << str << std::endl;
	}
}

void Engine::playerMove()
{
	if (turnIdentifier == true)
	{
		switch (playerType)
		{
		case PlayerType::Human:
			std::cout << "Enter the cell (x and y coordinates) to fill: " << std::endl;
			signed short int x, y;

			while (std::cin >> x >> y)
			{
				if (x < Field::fieldSize && y < Field::fieldSize && Field::gameField[x][y].cellState == CellState::EMPTY)
				{
					turnIdentifier = false;
					Field::gameField[x][y] = GameDescription::playerSymbol;
					break;
				}
				std::cout << "Wrong input, try again...";

			}
			break;
		case PlayerType::Bot:
			std::cout << "Your bot turn..." << std::endl;
			std::pair<unsigned int, unsigned int>fill = Bot::move();
			Field::gameField[fill.first][fill.second] = GameDescription::playerSymbol;
			turnIdentifier = false;
			break;
		}
		++GameDescription::moveCount;
	}
}

void Engine::opponentMove()
{
	if (turnIdentifier == false)
	{
		std::cout << "Opponent bot turn..." << std::endl;
		std::pair<unsigned int, unsigned int>fill = Bot::move();
		Field::gameField[fill.first][fill.second] = GameDescription::opponentSymbol;
		turnIdentifier = true;
		++GameDescription::moveCount;
	}
}



void Engine::initGame()
{
	
	std::cout <<
		"Please, enter the size of field (from 3x3 to 20x20 cells)\n"
		"If you will input wrong symbol or number that is out of given range,\n"
		"The game will be automatically set to 8x8\n"
		"Input number and press enter: ";

	unsigned short int fieldSize;
	std::cin >> fieldSize;
	if (2 < fieldSize && fieldSize < 21)
	{
		engField = new Field(fieldSize);
	}
	else
	{
		engField = new Field();
	}
	Render::clearCmd();

	Bot::setBotLvl();
	Render::clearCmd();

	std::cout << 
		"If you want to play yourself, input 1 \n"
		"If you want bot to play instead of you, input 0 \n"
		"(In case of wrong input you will play by yourself)\n";
	bool botOrHum;
	std::cin >> botOrHum;
	if (botOrHum == false)
	{
		playerType = PlayerType::Bot;
	}
	else
	{
		playerType = PlayerType::Human;
	}
}

void Engine::loop()
{
	flipCoin();
	gameState = GameState::Playing;
	Render::renderField(Field::gameField);
	
	
	while (gameState == GameState::Playing)
	{

		playerMove();
		checkField();
		Render::renderField(Field::gameField);
		
		if (gameState != GameState::Playing)
		{
			break;
		}
		
		opponentMove();
		checkField();
		Render::renderField(Field::gameField);
	}
	GameDescription::moveCount = 0;
	resultMsg(); 
	Field::resetField();

}

void Engine::resultMsg()
{

	char* endMsg{};
	if (gameState == GameState::Lose)
	{
		endMsg = const_cast<char*>(loseMsg.c_str());
		++GameDescription::score.second;
	}
	else if(gameState == GameState::Win)
	{
		endMsg = const_cast<char*>(winMsg.c_str());
		++GameDescription::score.first;
	}
	else
	{
		endMsg = const_cast<char*>(drawMsg.c_str());
	}

	MessageBox(0, endMsg, "Game", MB_OK);

}

bool Engine::flipCoin()
{
	return Random::random(0, 1) > 0.5 ? true : false;
}


Engine::Engine()
{
}

Engine::~Engine()
{
}
