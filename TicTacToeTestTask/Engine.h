#pragma once

#include <chrono>
#include <fstream>
#include <sstream>
#include "Field.h"
#include "Render.h"
#include "Random.h"
#include "Bot.h"

enum class GameState { Playing, Win, Lose, Draw};
enum class PlayerType { Human, Bot };

const std::string winMsg("You win");
const std::string loseMsg("You lose");
const std::string drawMsg("DRAW");

class Engine
{
private:
	Field* engField;
	GameState gameState;
	PlayerType playerType;
	PlayerType firstPlayer;
	PlayerType secondPlayer;
	bool turnIdentifier;

	bool checkRaws(CellState cs);
	bool checkColumn(CellState cs);
	bool checkDiagonal(CellState cs);

	void checkField();

public:

	static std::pair<short int, short int> score;
	static std::chrono::steady_clock clock;

	void rules();

	void initGame();
	
	void loop();
	
	void resultMsg();
	bool flipCoin();//if true - YOU START (IT ACTUALLY CAN BE YOUR OWN BOT) / if false - opponent bot starts

	Engine();
	~Engine();

};

