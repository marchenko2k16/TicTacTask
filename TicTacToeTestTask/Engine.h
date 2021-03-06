#pragma once

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
protected:
	Field* engField;
	GameState gameState;
	PlayerType playerType;

	bool checkRows(CellState cs);
	bool checkColumn(CellState cs);
	bool checkDiagonal(CellState cs);
	void checkField();

	void playerMove();
	void opponentMove();
public:

	void initGame();
	void loop();
	void resultMsg();
	bool flipCoin();//if true - YOU START (IT ACTUALLY CAN BE YOUR OWN BOT) / if false - opponent bot starts

	Engine();
	~Engine();

};

