#include "Grid.h"
#include "Window.h"
#include "Game.h"

Grid::Grid(Window* win)
{
	_pWin = win;

	_colorPairIdx[0] = win->getConsole()->getColorPairIdx(COLOR_WHITE, COLOR_BLACK);
	_colorPairIdx[1] = win->getConsole()->getColorPairIdx(COLOR_BLACK, COLOR_YELLOW);
	_colorPairIdx[2] = win->getConsole()->getColorPairIdx(COLOR_BLACK, COLOR_GREEN);

	_pnGrid = new int* [Game::nRounds];

	for (int i = 0; i < Game::nRounds; i++)
	{
		_pnGrid[i] = new int[Game::nCharacters];

		for (int j = 0; j < Game::nCharacters; j++)
		{
			_pnGrid[i][j] = Grid::INCORRECT;
		}
	}
}

Grid::~Grid()
{
	for (int i = 0; i < Game::nRounds; i++)
	{
		delete[] _pnGrid[i];
	}

	delete[] _pnGrid;
}

void Grid::print()
{
	for (int i = 0; i < Game::nRounds; i++)
	{
		printRow(i);
	}
}

void Grid::printRow(int nRow)
{
	moveToRow(nRow);

	for (int j = 0; j < Game::nCharacters; j++)
	{
		_pWin->print("_");
	}

	_pWin->refresh();
	moveToRow(nRow);
}

void Grid::printInputColor(std::string strWord, int nRow)
{
	moveToRow(nRow);

	for (int i = 0; i < Game::nCharacters; i++)
	{
		int nValue = (*this)[nRow][i];
		_pWin->printColor(strWord[i], _colorPairIdx[nValue]);
	}
}

void Grid::moveToRow(int nRow)
{
	int x = (_pWin->getWidth() - Game::nCharacters) / 2;
	_pWin->move(nRow, x);
}

bool Grid::isRowCorrect(int nRow)
{
	int nCorrectCharacters = 0;

	for (int i = 0; i < Game::nCharacters; i++)
	{
		if (_pnGrid[nRow][i] == Grid::CORRECT)
		{
			nCorrectCharacters++;
		}
	}

	return (nCorrectCharacters == Game::nCharacters);
}

int* Grid::operator[](int nRow)
{
	return _pnGrid[nRow];
}
