#include "Engine.h"

std::chrono::steady_clock Engine::clock;
std::pair<short int, short int> Engine::score;




bool Engine::checkRaws(CellState cs)
{
	bool check = false;
	unsigned int count = 0;
	for (auto i = 0; i < Field::fieldSize; ++i)
	{
		for (auto j = 0; j < Field::fieldSize - 1; ++j)
		{
			if (cs == Field::gameField[j][i].cellState &&
				Field::gameField[i][j].cellState == Field::gameField[i][j + 1].cellState)
			{
				++count;
			}
			if (count == Field::fieldSize) check = true;
			else
			{
				count = 0;
			}
		}
	}
	return check;
}

bool Engine::checkColumn(CellState cs)
{
	bool check = false;
	unsigned int count = 0;
	for (auto i = 0; i < Field::fieldSize; ++i)
	{
		for (auto j = 0; j < Field::fieldSize - 1; ++j)
		{
			if (cs == Field::gameField[j][i].cellState &&
				Field::gameField[j][i].cellState == Field::gameField[j + 1][i].cellState)
			{
				++count;
			}
			else
			{
				count = 0;
			}
			if (count == Field::fieldSize) { check = true; }
		}
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
	if (count == Field::fieldSize) { check = true; }
	
	count = 0;

	for (auto i = 0; i < Field::fieldSize; ++i)
	{
		if (cs == Field::gameField[i][Field::fieldSize - i].cellState) ++count;
	}
	if (count == Field::fieldSize) { check = true; }
	
	return check;
}

void Engine::checkField()
{
	unsigned int count = 0;
	for (auto i = 0; i < Field::fieldSize; ++i)
		for (auto j = 0; j < Field::fieldSize; ++j)
			if (Field::gameField[i][j].cellState != CellState::EMPTY)
				++count;

	if (checkColumn(CellState::X) ||
		checkRaws(CellState::X) ||
		checkDiagonal(CellState::X))
	{
		gameState = GameState::Win;
	}
	else if ((checkColumn(CellState::O) ||
		checkDiagonal(CellState::O) ||
		checkRaws(CellState::O)))
	{
		gameState = GameState::Lose;
	}
	else if (count == Field::fieldSize * Field::fieldSize)
		gameState = GameState::Draw;
}




void Engine::rules()
{

	std::ifstream readFrom("assets//preview");
	std::stringstream ss;
	ss << readFrom.rdbuf();
	std::string printStr = ss.str();

	for (int i = 0; i < printStr.length(); i++)
	{
		std::cout << printStr[i];
		Sleep(5);
	}
	std::cin.get();
	Render::clearCmd();
}

void Engine::initGame()
{
	
	std::cout <<
		"Please, enter the size of field (from 3x3 to 20x20 cells)\n"
		"If you will input wrong symbol or number that is out of given range,\n"
		"The game will be automatically set to 8x8\n"
		"Input number and press enter: ";

	unsigned short int size;
	std::cin >> size;
	if (2 < size && size < 21)
	{
		engField = new Field(size);
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
	while (gameState == GameState::Playing)
	{

		Render::renderField(Field::gameField);

		if (gameState != GameState::Playing) break;
		
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
						Field::gameField[x][y] = CellState::X;
						break;
					}
					std::cout << "Wrong input, try again...";
		
				}
				break;
			case PlayerType::Bot:
				std::cout << "Your bot turn..." << std::endl;
				std::pair<unsigned int, unsigned int>fill = Bot::move();
				Field::gameField[fill.first][fill.second] = CellState::X;
				turnIdentifier = false;
				break;
			}
			
		}
		checkField();
		Render::renderField(Field::gameField);
		if (gameState != GameState::Playing)
		{
			break;
		}
		
		if(turnIdentifier == false)
		{
			std::cout << "Opponent bot turn..." << std::endl;
			std::pair<unsigned int, unsigned int>fill = Bot::move();
			Field::gameField[fill.first][fill.second] = CellState::O;
			turnIdentifier = true;
		}
		checkField();

		Render::renderField(Field::gameField);
	}
	resultMsg();
}

void Engine::resultMsg()
{

	char* endMsg{};
	if (gameState == GameState::Lose)
	{
		endMsg = const_cast<char*>(loseMsg.c_str());
	}
	else if(gameState == GameState::Win)
	{
		endMsg = const_cast<char*>(winMsg.c_str());
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
