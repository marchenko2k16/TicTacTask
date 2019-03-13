#include "Render.h"


void Render::clearCmd()
{
	HANDLE                     hStdOut;
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	DWORD                      count;
	DWORD                      cellCount;
	COORD                      homeCoords = { 0, 0 };

	hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	if (hStdOut == INVALID_HANDLE_VALUE) return;

	/* Get the number of cells in the current buffer */
	if (!GetConsoleScreenBufferInfo(hStdOut, &csbi)) return;
	cellCount = csbi.dwSize.X *csbi.dwSize.Y;

	/* Fill the entire buffer with spaces */
	if (!FillConsoleOutputCharacter(
		hStdOut,
		(TCHAR) ' ',
		cellCount,
		homeCoords,
		&count
	)) return;

	/* Fill the entire buffer with the current colors and attributes */
	if (!FillConsoleOutputAttribute(
		hStdOut,
		csbi.wAttributes,
		cellCount,
		homeCoords,
		&count
	)) return;

	/* Move the cursor home */
	SetConsoleCursorPosition(hStdOut, homeCoords);
}

void Render::renderField(Cell ** _gField)
{
	clearCmd();
	std::cout << "SCRORE" << std::endl
		<< "YOU: " << GameDescription::score.first
		<< "  OPPONENT" << GameDescription::score.second
		<< std::endl;

	for (auto i = 0; i < Field::fieldSize; ++i)
	{
		std::cout << "----";
	}
	std::cout << std::endl;
	for (auto i = 0; i < Field::fieldSize; ++i)
	{
		std::cout << "|";
		for (auto j = 0; j < Field::fieldSize; ++j)
		{
			switch (Field::gameField[i][j].cellState)
			{
			case CellState::EMPTY:
				std::cout << "   ";
				break;
			case CellState::X:
				std::cout << " X ";
				break;
			case CellState::O:
				std::cout << " O ";
				break;
			};
			std::cout << "|";
		}
		std::cout << std::endl;
		for (auto i = 0; i < Field::fieldSize; ++i)
		{
			std::cout << "----";
		}
		std::cout << std::endl;
	}
}
