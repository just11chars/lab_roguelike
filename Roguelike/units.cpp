#include <curses.h>
#include <algorithm>
#include <string>
#include <vector>

using std::string;
using std::max;
using std::min;
using std::pair;
using std::vector;

#include "units.h"
#include "map.h"

Character::Character(string _name, int _max_health, int _damage,
	Map *_map, int _row, int _col, char _symbol, int _color)
{
	name = _name;
	health = _max_health;
	max_health = _max_health;
	damage = _damage;

	map = _map;
	row = _row;
	col = _col;

	symbol = _symbol;
	color = _color;
}

int Character::Health()
{
	return health;
}

int Character::MaxHealth()
{
	return max_health;
}

int Character::Damage()
{
	return damage;
}

Point Character::Position()
{
	return Point(row, col);
}

void Character::Move(vector<Unit*> &units)
{
	;
}

bool Character::TryMove(vector<Unit*> &units, int _row, int _col)
{
	if (map->IsCellFree(_row, _col)) {
		
		for each (Unit *u in units) {
			if (Point(_row, _col) == u->Position()) {
				Hit(u);
				return true;
			}
		}

		row = _row;
		col = _col;

		return true;
	}
	return false;
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

Peacefull::Peacefull(std::string _name, int _health, int _max_mana, int _damage,
	Map *_map, int _row, int _col, char _symbol, int _color)
	: Character(_name, _health, _damage, _map, _row, _col, _symbol, _color)
{
	max_mana = _max_mana;
	mana = _max_mana;
	experience = 0;
	level = 1;
	regen = 1;
}

int Peacefull::Mana()
{
	return mana;
}

int Peacefull::MaxMana()
{
	return max_mana;
}

int Peacefull::Level()
{
	return level;
}

int Peacefull::Experience()
{
	return experience;
}

int Peacefull::NextLevelExperience()
{
	return level * level_exp;
}

void Peacefull::ReceiveExperience(Monster *monster)
{
	experience += monster->ExperinceAward();
	while (experience >= NextLevelExperience()) {
		experience -= NextLevelExperience();
		
		damage += level_damage;
		max_mana += level_mana;
		max_health += level_health;

		++level;
		// level-up message
	}
}

void Peacefull::Regenerate()
{
	if (regen == regen_cycle) {
		regen = 1;
		health = min(health + 1, max_health);
		mana = min(mana + 1, max_mana);
	}
	else
		++regen;
}

void Peacefull::Hit(Unit *u)
{
	u->ReceiveDamage(this);
}

void Peacefull::Hit(Peacefull *u)
{
	// peacefull creatures don't fight with peacefull creatures
	;
}
void Peacefull::Hit(Monster *u)
{
	u->ReceiveDamage(this);
}

void Peacefull::ReceiveDamage(Unit *u)
{
	;
}

void Peacefull::ReceiveDamage(Peacefull *u)
{
	;
}

void Peacefull::ReceiveDamage(Monster *u)
{
	health -= u->Damage();
	if (health <= 0) {
		// some death message
	}
}



Knight::Knight(string name, Map *_map, int row, int col)
	: Peacefull(name, 20, 10, 3, _map, row, col, '@', COLOR_YELLOW)
{
	;
}

void Knight::Move(vector<Unit*> &units)
{
	int key;
	while (key = getch()) {
		if (key == KEY_UP && TryMove(units, row - 1, col)) {
			break;
		}
		else if (key == KEY_DOWN && TryMove(units, row + 1, col)) {
			break;
		}
		else if (key == KEY_LEFT && TryMove(units, row, col - 1)) {
			break;
		}
		else if (key == KEY_RIGHT && TryMove(units, row, col + 1)) {
			break;
		}
	}

	Regenerate();
}

Princess::Princess(std::string name, Map * _map, int row, int col)
	: Peacefull(name, 10000, 0, 0, _map, row, col, 'P', COLOR_YELLOW)
{
	;
}

void Princess::Move(vector<Unit*> &units)
{
	// she just stays at place
}

Monster::Monster(std::string _name, int _health, int _damage,
	int _exp_award,
	Map *_map, int _row, int _col, char _symbol, int _color)
	: Character(_name, _health, _damage, _map, _row, _col, _symbol, _color)
{
	experience_award = _exp_award;
}

int Monster::ExperinceAward()
{
	return experience_award;
}

void Monster::Hit(Unit *u)
{
	u->ReceiveDamage(this);
}

void Monster::Hit(Peacefull *u)
{
	u->ReceiveDamage(u);
}

void Monster::Hit(Monster *u)
{
	// monsters don't fight with monsters
	;
}

void Monster::ReceiveDamage(Unit *u)
{
	;
}

void Monster::ReceiveDamage(Peacefull *from)
{
	health -= from->Damage();
	if (health <= 0) {
		invalid = true;
		row = -1;
		from->ReceiveExperience(this);
	}
}

void Monster::ReceiveDamage(Monster *u)
{
	;
}

Zombie::Zombie(Map *_map, int row, int col)
	: Monster("Zombie", 10, 2, 4, _map, row, col, 'Z', COLOR_CYAN)
{
	;
}