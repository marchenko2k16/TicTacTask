#include "Field.h"

unsigned short int Field::fieldSize;
Cell** Field::gameField;


void Field::resetField()
{
	
	for (auto i = 0; i < Field::fieldSize; ++i)
	{
		for (auto j = 0; j < Field::fieldSize; ++j)
		{
			Field::gameField[i][j] = CellState::EMPTY;
		}
	}

}


Field::Field(short int _fueldSize)
{
	
	fieldSize = _fueldSize;

	Field::gameField = new Cell*[Field::fieldSize];
	for (auto i = 0; i < Field::fieldSize; i++)
	{
		gameField[i] = new Cell[Field::fieldSize];
	}

}



Field::~Field()
{
	for(auto i = 0; i < Field::fieldSize; ++i)
	{
		delete[] gameField[i];
	}
	delete[] gameField;
}
