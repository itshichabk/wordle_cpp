#include "Window.h"
#include "Window.h"
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

	_win = newwin(h, w, y, x);
	box(_win, 0, 0);
}

Window::Window(const Window& win)
{
	_w = win._w;
	_h = win._h;
	_title = win._title;
	_x = win._x;
	_y = win._y;

	int x = win._x;
	int y = win._y;

	_win = newwin(win._h, win._w, y, x);
	box(_win, 0, 0);
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

	_win = nullptr;
}

WINDOW* Window::getWIN() const
{
	return _win;
}

const int Window::getWidth() const
{
	return _w;
}

void Window::print(std::string strMsg)
{
	wprintw(_win, strMsg.c_str());
	this->refresh();
}

void Window::print(std::string strMsg, int y, int x)
{
	mvwprintw(_win, y, x, strMsg.c_str());
	this->refresh();
}

const int Window::getHeight() const
{
	return _h;
}

void Window::printColor(std::string strMsg, int nBgColor, int nFgColor)
{
	int nColorPairIdx = _console->getColorPairIdx(nBgColor, nFgColor);
	printColor(strMsg, nColorPairIdx);
}

void Window::printColor(char c, int nBgColor, int nFgColor)
{
	std::string strMsg(1, c);
	printColor(strMsg, nBgColor, nFgColor);
}

void Window::printColor(std::string strMsg, int nColorPairIdx)
{
	wattron(_win, COLOR_PAIR(nColorPairIdx));
	wprintw(_win, strMsg.c_str());
	wattroff(_win, COLOR_PAIR(nColorPairIdx));

	this->refresh();
}

void Window::printColor(char c, int nColorPairIdx)
{
	std::string strMsg(1, c);
	printColor(strMsg, nColorPairIdx);
}

void Window::move(int y, int x)
{
	wmove(_win, y, x);
}

void Window::refresh()
{
	wrefresh(_win);
}

void Window::drawWindow()
{
	mvwprintw(_win, 0, (_w - _title.length()) / 2, _title.c_str());
	this->refresh();
}

void Window::refreshBox()
{
	box(_win, 0, 0);
	mvwprintw(_win, 0, (_w - _title.length()) / 2, _title.c_str());
	this->refresh();
}
