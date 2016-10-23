#include <cstdlib>
#include <ctime>
#include <curses.h>

#include "utils.h"
#include "map.h"

void init_utils()
{
	srand(time(NULL));
	init_cell_types();
}

void init_curses()
{
	initscr();
	cbreak();
	noecho();
	keypad(stdscr, TRUE);
	curs_set(0);
	start_color();
}

void init()
{
	init_utils();
	init_curses();
}

bool rand_event(double prob)
{
	return (double)rand() / RAND_MAX < prob;
}

Point::Point(int _row, int _col)
{
	row = _row;
	col = _col;
}

Rect::Rect(int _r0, int _c0, int _r1, int _c1)
{
	r0 = _r0;
	c0 = _c0;
	r1 = _r1;
	c1 = _c1;
}

bool operator!=(const Point &a, const Point &b)
{
	return a.row != b.row || a.col != b.col;
}

bool Rect::PointInside(int row, int col)
{
	return r0 <= row && row <= r1 &&
		c0 <= col && col <= c1;
}

bool Rect::PointInside(Point p)
{
	return PointInside(p.row, p.col);
}