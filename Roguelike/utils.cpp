#include <cstdlib>
#include <ctime>
#include <curses.h>
#include <map>

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
	init_keys();
}

bool rand_event(double prob)
{
	return (double)rand() / RAND_MAX < prob;
}

void draw_char(WINDOW *window, int symbol, int row, int col, int bg_col, int front_col)
{
	int pair_index = 1 + 8 * front_col + bg_col;

	wattron(window, COLOR_PAIR(pair_index));
	mvwaddch(window, 1 + row, 1 + col, symbol);
	wattroff(window, COLOR_PAIR(pair_index));
}

Point::Point()
{
	;
}

Point::Point(int _row, int _col)
{
	row = _row;
	col = _col;
}

int Point::Length()
{
	return abs(row) + abs(col);
}

bool operator==(const Point &a, const Point &b)
{
	return a.row == b.row && a.col == b.col;
}

bool operator!=(const Point &a, const Point &b)
{
	return !(a == b);
}

Point operator-(const Point &a, const Point &b)
{
	return Point(a.row - b.row, a.col - b.col);
}

Rect::Rect(int _r0, int _c0, int _r1, int _c1)
{
	r0 = _r0;
	c0 = _c0;
	r1 = _r1;
	c1 = _c1;
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

std::map<int, Point*> _key_movements;

void init_keys()
{
	_key_movements[KEY_A1] = new Point(-1, -1);
	_key_movements[KEY_A2] = new Point(-1, 0);
	_key_movements[KEY_A3] = new Point(-1, 1);

	_key_movements[KEY_B1] = new Point(0, -1);
	_key_movements[KEY_B2] = new Point(0, 0);
	_key_movements[KEY_B3] = new Point(0, 1);

	_key_movements[KEY_C1] = new Point(+1, -1);
	_key_movements[KEY_C2] = new Point(+1, 0);
	_key_movements[KEY_C3] = new Point(+1, 1);

	_key_movements[' '] = new Point(0, 0);
}