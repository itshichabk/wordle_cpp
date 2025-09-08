/*
	Class derived from the "hOS" C++ project: https://github.com/itshichabk/hOS_Cpp
*/

#pragma once

#include <curses.h>
#include <string>
#include "Console.h"

class Window
{
protected:
	WINDOW*  _box;
	WINDOW*  _win;
	Console* _console;

	int _y, _x,
		_h, _w;

	std::string _title;

public:
	Window(Console* console,
		   std::string title = "",
		   int h = CON_ROWS, int w = CON_COLS,
		   bool isCentered = false,
		   int x = 0, int y = 0);

	~Window();

	WINDOW* getWIN() const;
	Console* getConsole() const;

	const int getHeight() const;
	const int getWidth() const;

	void print(std::string strMsg, bool bCentered = false, int y = - 1, int x = -1);
	void print(std::string strMsg, int y, int x);

	void printColor(std::string strMsg, int nBgColor, int nFgColor, bool bCentered = false, int y = -1, int x = -1);
	void printColor(char c, int nBgColor, int nFgColor, bool bCentered = false, int y = -1, int x = -1);

	void printColor(std::string strMsg, int nColorPairIdx, bool bCentered = false, int y = -1, int x = -1);
	void printColor(char c, int nColorPairIdx, bool bCentered = false, int y = -1, int x = -1);

	void move(int y, int x);
	void refresh();

	void drawWindow();
};
