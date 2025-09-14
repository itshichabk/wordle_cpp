#include "Window.h"
#include "Window.h"
#include "Window.h"

Window::Window(Console* console, std::string title, int h, int w, bool isCentered, int x, int y)
{
	_console = console;

	_w = w;
	_h = h;

	if (_w > CON_COLS)
	{
		_w = CON_COLS;
	}

	if (_h > CON_ROWS)
	{
		_h = CON_ROWS;
	}

	_title = title;
	_x = x;
	_y = y;

	if (isCentered)
	{
		int row = 0, 
			col = 0;

		getmaxyx(stdscr, row, col);

		y = (row - _h) / 2;
		x = (col - _w) / 2;
	}

	if (title.empty())
	{
		_box = newwin(h + 2, w + 2, y - 1, x - 1);
		_win = newwin(h, w, y, x);
	}
	else
	{
		_box = newwin(h + 3, w + 2, y - 2, x - 1);
		_win = newwin(h, w, y, x);
	}

	keypad(_win, true);

	drawWindow();
}

Window::~Window()
{
	_x = 0;
	_y = 0;
	_w = 0;
	_h = 0;
	_title = "";

	wclear(_win);
	wrefresh(_win);
	delwin(_win);

	wclear(_box);
	wrefresh(_box);
	delwin(_box);

	_box = nullptr;
	_win = nullptr;
	_console = nullptr;
}

Console* Window::getConsole() const
{
	return _console;
}

const int Window::getWidth() const
{
	return _w;
}

void Window::print(std::string strMsg, bool bCentered, int y, int x)
{
	if (y == -1)
	{
		y = getcury(_win);
	}

	if (x == -1)
	{
		x = getcurx(_win);
	}

	if (bCentered)
	{
		x = (_w - strMsg.length()) / 2;
	}

	mvwprintw(_win, y, x, strMsg.c_str());
	this->refresh();
}

void Window::print(std::string strMsg, int y, int x)
{
	print(strMsg, false, y, x);
}

const int Window::getHeight() const
{
	return _h;
}

void Window::printColor(std::string strMsg, int nFgColor, int nBgColor, bool bCentered, int y, int x)
{
	int nColorPairIdx = _console->getColorPairIdx(nFgColor, nBgColor);
	printColor(strMsg, nColorPairIdx, bCentered, y, x);
}

void Window::printColor(char c, int nFgColor, int nBgColor, bool bCentered, int y, int x)
{
	std::string strMsg(1, c);
	printColor(strMsg, nFgColor, nBgColor, bCentered, y, x);
}

void Window::printColor(std::string strMsg, int nColorPairIdx, bool bCentered, int y, int x)
{
	wattron(_win, COLOR_PAIR(nColorPairIdx));
	print(strMsg, bCentered, y, x);
	wattroff(_win, COLOR_PAIR(nColorPairIdx));

	this->refresh();
}

void Window::printColor(char c, int nColorPairIdx, bool bCentered, int y, int x)
{
	std::string strMsg(1, c);
	printColor(strMsg, nColorPairIdx);
}

char Window::getChar()
{
	return wgetch(_win);
}

void Window::addChar(char c)
{
	waddch(_win, c);
}

void Window::move(int y, int x)
{
	wmove(_win, y, x);
}

void Window::moveOffset(int y, int x)
{
	int nCurY = 0,
		nCurX = 0;

	getyx(_win, nCurY, nCurX);

	move(nCurY + y, nCurX + x);
}

void Window::refresh()
{
	wrefresh(_win);
}

void Window::drawWindow()
{
	box(_box, 0, 0);
	mvwprintw(_box, 0, (_w + 2 - _title.length()) / 2, _title.c_str());
	wrefresh(_box);
	this->refresh();
}
