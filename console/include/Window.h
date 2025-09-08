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

	Window(const Window& win);
	~Window();

	WINDOW* getWIN() const;

	const int getHeight() const;
	const int getWidth() const;

	void print(std::string strMsg);
	void print(std::string strMsg, int y, int x);

	void printColor(std::string strMsg, int nBgColor, int nFgColor);
	void printColor(char c, int nBgColor, int nFgColor);

	void printColor(std::string strMsg, int nColorPairIdx);
	void printColor(char c, int nColorPairIdx);

	void move(int y, int x);
	void refresh();

	void drawWindow();

	void refreshBox();
};
