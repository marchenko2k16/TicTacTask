#pragma once

enum class CellState { EMPTY, X, O };

class Cell
{
public:

	CellState cellState;
	Cell(CellState cs = CellState::EMPTY);

};

