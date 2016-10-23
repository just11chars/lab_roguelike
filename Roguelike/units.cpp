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
	int pair_index = 1 + 8 * color + background;

	wattron(window, COLOR_PAIR(pair_index));
	mvwaddch(window, 1 + r, 1 + c, symbol);
	wattroff(window, COLOR_PAIR(pair_index));
}


void Character::Hit(Unit *u)
{
	u->ReceiveDamage(this->Damage());
}

void Character::ReceiveDamage(int rec_damage)
{
	health -= rec_damage;
}

Peacefull::Peacefull(std::string _name, int _health, int _mana, int _damage,
	Map *_map, int _row, int _col, char _symbol, int _color)
	: Character(_name, _health, _damage, _map, _row, _col, _symbol, _color)
{
	mana = _mana;
}

int Peacefull::ManaPoints()
{
	return mana;
}

Knight::Knight(string name, Map *_map, int row, int col)
	: Peacefull(name, 100, 50, 5, _map, row, col, '@', COLOR_YELLOW)
{
	;
}

void Knight::Move()
{
	int key = getch();
	if (key == KEY_UP) {
		if (map->IsCellFree(row - 1, col))
			--row;
	}
	else if (key == KEY_DOWN) {
		if (map->IsCellFree(row + 1, col))
			++row;
	}
	else if (key == KEY_LEFT) {
		if (map->IsCellFree(row, col - 1))
			--col;
	}
	else if (key == KEY_RIGHT) {
		if (map->IsCellFree(row, col + 1))
			++col;
	}
}

Princess::Princess(std::string name, Map * _map, int row, int col)
	: Peacefull(name, 10000, 0, 0, _map, row, col, 'P', COLOR_YELLOW)
{
	;
}

void Princess::Move()
{
	// she just stays at place
}

Monster::Monster(std::string _name, int _health, int _damage,
	Map *_map, int _row, int _col, char _symbol, int _color)
	: Character(_name, _health, _damage, _map, _row, _col, _symbol, _color)
{
	;
}

Zombie::Zombie(Map *_map, int row, int col)
	: Monster("Zombie", 20, 3, _map, row, col, 'Z', COLOR_CYAN)
{
	;
}