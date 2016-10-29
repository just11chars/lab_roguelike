#include "projectiles.h"
#include "components.h"

Projectile::Projectile(std::string _name, Unit *_owner, int _damage,
	Point _direction, int _steps_left,
	Map *_map, int _row, int _col,
	char _symbol, int _color,
	Log *_log)
	: direction(_direction)
{
	name = _name;
	owner = _owner;
	damage = _damage;
	
	steps_left = _steps_left;
	map = _map;
	row = _row;
	col = _col;

	symbol = _symbol;
	color = _color;

	log = _log;
}

int Projectile::MaxHealth()
{
	return damage;
}

int Projectile::Health()
{
	return damage;
}

int Projectile::Damage()
{
	return damage;
}

Point Projectile::Position()
{
	return Point(row, col);
}

Unit* Projectile::Owner()
{
	return owner;
}

std::string Projectile::Name()
{
	return name;
}

void Projectile::Draw(WINDOW *window, Point shift)
{
	int r = row - shift.row;
	int c = col - shift.col;

	char background = map->GetCell(r, c).bg_color;
	draw_char(window, symbol, r, c, background, color);
}

void Projectile::Die()
{
	row = -10;
	invalid = true;
}

void Projectile::Move(std::vector<Unit*> &units)
{
	if (!steps_left) {
		Die();
		return;
	}

	--steps_left;
	row += direction.row;
	col += direction.col;

	if (map->IsCellFree(row, col)) {
		for (int i = 0; i < units.size(); ++i)
			if (this != units[i] && Point(row, col) == units[i]->Position()) {
				Hit(units[i]);
				Die();
			}
	}
	else
		Die();
}

void Projectile::Hit(Unit *u)
{
	ReceiveDamage(u);
}

void Projectile::Hit(Peacefull *u)
{
	Hit((Unit*)u);
}

void Projectile::Hit(Monster *u)
{
	Hit((Unit*)u);
}

void Projectile::Hit(Projectile *u)
{
	Hit((Unit*)u);
}

void Projectile::ReceiveDamage(Unit *u)
{
	// can't beat our creator
	if (owner != u) {
		u->ReceiveDamage(this);
		Die();
	}
}

void Projectile::ReceiveDamage(Peacefull *u)
{
	ReceiveDamage((Unit*)u);
}

void Projectile::ReceiveDamage(Monster *u)
{
	ReceiveDamage((Unit*)u);
}

void Projectile::ReceiveDamage(Projectile *u)
{
	if (invalid)
		return;

	Die();
	u->ReceiveDamage(this);
}

Fireball::Fireball(Unit *owner, Point _direction, Map *_map, int row, int col, Log *_log)
	: Projectile("Fireball", owner, 5, _direction, 8, _map, row, col, '*', COLOR_RED, _log)
{
	;
}

int Fireball::ManaCost()
{
	return 5;
}

Iceball::Iceball(Unit *owner, Point _direction, Map *_map, int row, int col, Log *_log)
	: Projectile("Iceball", owner, 3, _direction, 8, _map, row, col, '*', COLOR_BLUE, _log)
{
	;
}

int Iceball::ManaCost()
{
	return 3;
}
