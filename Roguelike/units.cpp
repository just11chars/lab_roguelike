#include <curses.h>
#include <algorithm>
#include <string>

using std::string;
using std::max;
using std::min;
using std::pair;

#include "units.h"
#include "map.h"

Character::Character(string _name, int _health, int _damage,
	Map *_map, int _row, int _col, char _symbol, int _color)
{
	name = _name;
	health = _health;
	damage = _damage;

	map = _map;
	row = _row;
	col = _col;

	symbol = _symbol;
	color = _color;
}

int Character::HealthPoints()
{
	return health;
}

int Character::Damage()
{
	return damage;
}

Point Character::Position()
{
	return Point(row, col);
}

void Character::Move()
{
	;
}

void Character::Draw(WINDOW *window, Point shift)
{
	int r = row - shift.row;
	int c = col - shift.col;

	char background = map->GetCell(r, c).bg_color;
	init_pair(1, color, background);
	
	wattron(window, COLOR_PAIR(1));
	mvwaddch(window, 1 + r, 1 + c, symbol);
	wattroff(window, COLOR_PAIR(1));
}


Knight::Knight(string name, Map *_map, int row, int col)
	: Character(name, 100, 5, _map, row, col, '@', COLOR_YELLOW)
{
	;
}

void Knight::Move()
{
	int key = getch();
	if (key == KEY_UP) {
		if (map->IsCellFree(row - 1, col))
			row = max(0, row - 1);
	}
	else if (key == KEY_DOWN) {
		if (map->IsCellFree(row + 1, col))
			row = min(map->MaxRow(), row + 1);
	}
	else if (key == KEY_LEFT) {
		if (map->IsCellFree(row, col - 1))
			col = max(0, col - 1);
	}
	else {
		if (map->IsCellFree(row, col + 1))
			col = min(map->MaxCol(), col + 1);
	}
}

Princess::Princess(std::string name, Map * _map, int row, int col)
	: Character(name, 10000, 0, _map, row, col, 'P', COLOR_YELLOW)
{

}

void Princess::Move()
{
	// she just stays at place
}