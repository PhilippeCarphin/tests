#include <ncurses.h>

int main(void)
{
	initscr();
	printw("Hello World !!!");
	refresh();
	getch();
	endwin();

	return 0;
}
