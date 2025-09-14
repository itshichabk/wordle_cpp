#pragma once

#include <curses.h>
#include "Window.h"

class Grid
{
public:
	enum ColorPairs
	{
		INCORRECT,
		WRONG_SPOT,
		CORRECT
	};

private:
	int** _pnGrid;
	Window* _pWin;

	int _colorPairIdx[3];

public:
	Grid(Window* win);
	~Grid();

	void print();
	void printRow(int nRow);
	void printInputColor(std::string strWord, int nRow);

	std::string readInput(int nRound);

	void moveToRow(int nRow, int nCol = 0);
	bool isRowCorrect(int nRow);

	int* operator[](int nRow);
};
