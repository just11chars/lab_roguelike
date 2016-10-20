#include <curses.h>

#include "utils.h"
#include "map.h"
#include "units.h"
#include "level.h"

int main()
{
	init();
	
	WINDOW *field = newwin(25, 70, 5, 10);
	box(field, 0, 0);
	wrefresh(field);
	
	/*
	Map map(100, 100);
	Knight player("name", &map, 3, 3);
	View view(field, &map, &player);
	
	Princess princess("princess name", &map, 70, 70);

	view.Update();

	while (true) {
		player.Move();
		view.Update();
	}*/

	Level level(LT_RANDOM, 100, 100, field, "name");

	while (true) {
		level.Iterate();
		refresh();
	}

	getch();
	endwin();
	return 0;
}