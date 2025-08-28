#include <curses.h>
#include <string>

int main()
{
	initscr();
	resize_term(25, 80);

	endwin();
	return 0;
}
