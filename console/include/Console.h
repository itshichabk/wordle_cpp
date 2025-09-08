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
	//Window _winMain;
	//std::vector<Window> _windows;

	typedef struct colorPair
	{
		int bgColor;
		int fgColor;

		bool operator<(const colorPair& c) const
		{
			return bgColor < c.bgColor || (bgColor == c.bgColor && fgColor < c.fgColor);
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
