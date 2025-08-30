#pragma once

#include <curses.h>

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
	Grid();
	~Grid();

	void print() const;
	bool isRowCorrect(int nRow) const;

	int* operator[](int nRow);
};
