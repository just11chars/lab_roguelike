#include <curses.h>

#include "utils.h"
#include "map.h"
#include "units.h"
#include "level.h"

int main()
{
	init();
	
	WINDOW *field = newwin(25, 70, 5, 2);
	box(field, 0, 0);
	wrefresh(field);

	WINDOW *player_info = newwin(10, 20, 0, 72);
	
	Level level(LT_RANDOM, 100, 100, field, "name", player_info);

	while (true) {
		level.Iterate();
	}

	getch();
	endwin();
	return 0;
}