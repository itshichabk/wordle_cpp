#pragma once
#include <curses.h>
#include <map>
#include <vector>

constexpr int CON_ROWS = 25;
constexpr int CON_COLS = 80;

class Console
{
public:
	static const int nRows;
	static const int nCols;

private:
	typedef struct colorPair
	{
		int fgColor;
		int bgColor;

		bool operator<(const colorPair& c) const
		{
			return fgColor < c.fgColor || (fgColor == c.fgColor && bgColor < c.bgColor);
		}

	} colorPair;

	std::map<colorPair, int> _colorPairsIdx;

public:
	Console();
	~Console();

	void init();
	void initColorPairs();

	int getColorPairIdx(int nBgColor, int nFgColor) const;
};
