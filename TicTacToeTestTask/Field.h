#pragma once
#include "Cell.h"


class Field
{
public:
	
	static Cell** gameField;
	static unsigned short int fieldSize;
	static void resetField();
	
	Field(short int _fieldSize = 8);
	~Field();

};

