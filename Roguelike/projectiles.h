#pragma once
#include <string>

#include "units.h"
#include "components.h"

class Projectile : public Unit
{
public:
	Projectile(std::string _name, Unit *_owner, int _damage,
		Point _direction, int _steps_left,
		Map *_map, int _row, int _col,
		char _symbol, int _color,
		Log *_log);

	int MaxHealth() override;
	int Health() override;
	int Damage() override;
	Unit* Owner();
	std::string Name() override;

	Point Position() override;
	void Draw(WINDOW *window, Point shift) override;
	void Move(std::vector<Unit*> &units) override;

	void Hit(Unit*);
	void Hit(Peacefull*);
	void Hit(Monster*);
	void Hit(Projectile*);

	void ReceiveDamage(Unit*);
	void ReceiveDamage(Peacefull*);
	void ReceiveDamage(Monster*);
	void ReceiveDamage(Projectile*);

protected:
	void Die();

	std::string name;
	Unit *owner;
	int damage;

	Map *map;
	int row, col;

	Point direction;
	int steps_left;

	int color;
	char symbol;
};

class Fireball : public Projectile
{
public:
	Fireball(Unit *owner, Point _direction, Map *_map, int row, int col, Log *_log);
	static int ManaCost();
};

class Iceball : public Projectile
{
public:
	Iceball(Unit *owner, Point _direction, Map *_map, int row, int col, Log *_log);
	static int ManaCost();
};
