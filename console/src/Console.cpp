#include "Console.h"
#include "Grid.h"
#include "Game.h"

const int Console::nRows = CON_ROWS;
const int Console::nCols = CON_COLS;

void Console::init()
{
	initscr();
	start_color();
	resize_term(25, 80);
	noecho();

	initColorPairs();
}

Console::Console()
{
	init();
}

Console::~Console()
{
	curs_set(1);
	clear();
	endwin();
}

void Console::initColorPairs()
{
	int nIndex = 1;
	int nColors[] = { COLOR_BLACK, COLOR_RED, COLOR_GREEN, COLOR_BLUE, COLOR_CYAN, COLOR_MAGENTA, COLOR_YELLOW, COLOR_WHITE };

	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if (nColors[i] != nColors[j])
			{
				init_pair(nIndex, nColors[i], nColors[j]);

				std::pair<colorPair, int> pair({ nColors[i], nColors[j] }, nIndex);
				_colorPairsIdx.insert(pair);

				nIndex++;
			}
		}
	}
}


int Console::getColorPairIdx(int nFgColor, int nBgColor) const
{
	return _colorPairsIdx.at({ nFgColor, nBgColor });
}
