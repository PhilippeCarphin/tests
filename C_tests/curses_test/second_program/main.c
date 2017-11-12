#include <ncurses.h>
#include <string.h>

int main(void)
{
	initscr();
	printw("Hello World !!!");

	// Create a window with a box on it
	WINDOW * philwin = newwin(3,77,2,5);
	box(philwin, 0, 0);
	refresh();

	mvwprintw(philwin, 0, 0, "snot");
	mvwprintw(philwin, 1, 0, "booger");
    mvwprintw(philwin, 2, 0, "nose gold");
	mvwprintw(philwin, 3, 0, "this is not shown but does not cause error");

	wrefresh(philwin);
	getch();

	wclear(philwin);
	box(philwin, 0, 0);
	wrefresh(philwin);

	getch();
	char *s = "Center of window";
	size_t ls = strlen(s);
    mvwprintw(philwin, 2, 0,s);

	endwin();

	return 0;
}
