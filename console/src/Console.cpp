#include "Console.h"
#include "Grid.h"

const int Console::nRows = CON_ROWS;
const int Console::nCols = CON_COLS;

void Console::init()
{
	initscr();
	start_color();
	resize_term(25, 80);

	initColorPairs();

	/*int nRedGreenIdx    = getColorPairIdx(COLOR_RED, COLOR_GREEN);
	int nWhiteBlackIdx  = getColorPairIdx(COLOR_WHITE, COLOR_BLACK);
	int nYellowCyanIdx  = getColorPairIdx(COLOR_YELLOW, COLOR_CYAN);
	int nBlueMagentaIdx = getColorPairIdx(COLOR_BLUE, COLOR_MAGENTA);

	int nColorPairs[] = { nRedGreenIdx, nWhiteBlackIdx, nYellowCyanIdx, nBlueMagentaIdx };

	for (int i = 0; i < 4; i++)
	{
		printColor("HELLO\n", nColorPairs[i]);
	}

	getch();*/
}

Console::Console()// : _winMain(this)
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


int Console::getColorPairIdx(int nBgColor, int nFgColor) const
{
	return _colorPairsIdx.at({ nBgColor, nFgColor });
}
