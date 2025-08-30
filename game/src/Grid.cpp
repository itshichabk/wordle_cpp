#include "Game.h"

Grid::Grid()
{
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

void Grid::print() const
{
	for (int i = 0; i < Game::nRounds; i++)
	{
		move(i, 0);

		for (int j = 0; j < Game::nCharacters; j++)
		{
			addch('_');
		}

		refresh();
	}
}

bool Grid::isRowCorrect(int nRow) const
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
