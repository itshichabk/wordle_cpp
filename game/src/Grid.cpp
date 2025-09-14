#include <algorithm>
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

std::string Grid::readInput(int nRound)
{
	int nTypedChars = 0;
	char cInput = 0;

	std::string strInput(GAME_CHARS, ' ');

	moveToRow(nRound);

	do
	{
		cInput = _pWin->getChar();

		if (cInput == '\n')
		{
			break;
		}
		else if (cInput == '\b' && nTypedChars > 0)
		{
			strInput[nTypedChars] = ' ';

			_pWin->moveOffset(0, -1);
			_pWin->addChar('_');
			_pWin->moveOffset(0, -1);

			nTypedChars--;
		}
		else if (nTypedChars < GAME_CHARS)
		{
			if ((cInput > 64 && cInput < 91) || (cInput > 96 && cInput < 123))
			{
				if (cInput > 96 && cInput < 123)
				{
					cInput = std::toupper(cInput);
				}

				strInput[nTypedChars] = cInput;
				_pWin->addChar(cInput);

				nTypedChars++;
			}
		}

		_pWin->refresh();

	} while (cInput != KEY_ENTER);

	strInput.erase(std::remove(strInput.begin(), strInput.end(), ' '), strInput.end());
	return strInput;
}

void Grid::moveToRow(int nRow, int nCol)
{
	int x = (_pWin->getWidth() - GAME_CHARS) / 2;
	_pWin->move(nRow, x + nCol);
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
