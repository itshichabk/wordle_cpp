#include "Grid.h"
#include "Window.h"
#include "Game.h"

Grid::Grid(Window* win)
{
	_pWin = win;

	_colorPairIdx[0] = win->getConsole()->getColorPairIdx(COLOR_WHITE, COLOR_BLACK);
	_colorPairIdx[1] = win->getConsole()->getColorPairIdx(COLOR_BLACK, COLOR_YELLOW);
	_colorPairIdx[2] = win->getConsole()->getColorPairIdx(COLOR_BLACK, COLOR_GREEN);

	_pnGrid = new int* [GAME_ROUNDS];

	for (int i = 0; i < GAME_ROUNDS; i++)
	{
		_pnGrid[i] = new int[GAME_CHARS];

		for (int j = 0; j < GAME_CHARS; j++)
		{
			_pnGrid[i][j] = Grid::INCORRECT;
		}
	}
}

Grid::~Grid()
{
	for (int i = 0; i < GAME_ROUNDS; i++)
	{
		delete[] _pnGrid[i];
	}

	delete[] _pnGrid;
}

void Grid::print()
{
	for (int i = 0; i < GAME_ROUNDS; i++)
	{
		printRow(i);
	}
}

void Grid::printRow(int nRow)
{
	moveToRow(nRow);

	for (int j = 0; j < GAME_CHARS; j++)
	{
		_pWin->print("_");
	}

	_pWin->refresh();
	moveToRow(nRow);
}

void Grid::printInputColor(std::string strWord, int nRow)
{
	moveToRow(nRow);

	for (int i = 0; i < GAME_CHARS; i++)
	{
		int nValue = (*this)[nRow][i];
		_pWin->printColor(strWord[i], _colorPairIdx[nValue]);
	}
}

void Grid::moveToRow(int nRow)
{
	int x = (_pWin->getWidth() - GAME_CHARS) / 2;
	_pWin->move(nRow, x);
}

bool Grid::isRowCorrect(int nRow)
{
	int nCorrectCharacters = 0;

	for (int i = 0; i < GAME_CHARS; i++)
	{
		if (_pnGrid[nRow][i] == Grid::CORRECT)
		{
			nCorrectCharacters++;
		}
	}

	return (nCorrectCharacters == GAME_CHARS);
}

int* Grid::operator[](int nRow)
{
	return _pnGrid[nRow];
}
