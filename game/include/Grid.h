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

public:
	Grid(Window* win);
	~Grid();

	Window* _pWin;

	void print() const;
	bool isRowCorrect(int nRow) const;

	int* operator[](int nRow);
};
