#pragma once
#include <string>
#include <vector>

#include "map.h"

class Peacefull;
class Monster;
class Projectile;

class Unit
{
public:
	virtual int MaxHealth() = 0;
	virtual int Health() = 0;
	virtual int Damage() = 0;

	virtual void Move(std::vector<Unit*> &units) = 0;

	virtual void Draw(WINDOW *window, Point shift) = 0;
	virtual Point Position() = 0;

	virtual void Hit(Unit*) = 0;
	virtual void Hit(Peacefull*) = 0;
	virtual void Hit(Monster*) = 0;
	virtual void Hit(Projectile*) = 0;

	virtual void ReceiveDamage(Unit*) = 0;
	virtual void ReceiveDamage(Peacefull*) = 0;
	virtual void ReceiveDamage(Monster*) = 0;
	virtual void ReceiveDamage(Projectile*) = 0;

	friend class Level;

protected:
	bool invalid = false;
};

class Map;

class Character: public Unit
{
public:
	Character(std::string _name, int _health, int _damage,
		Map *_map, int _row, int _col, char _symbol, int _color);
	
	int Health() override;
	int MaxHealth() override;
	int Damage() override;
	Point Character::Position() override;

	bool TryMove(std::vector<Unit*> &units, int row, int col);
	void Draw(WINDOW *window, Point shift) override;
	
	void Hit(Projectile*) override;
	virtual void Hit(Unit*) = 0;
	virtual void Hit(Peacefull*) = 0;
	virtual void Hit(Monster*) = 0;

protected:
	void Die();

	std::string name;
	int health, max_health;
	int damage;

	Map *map;
	int row, col;

	int color;
	char symbol;
};

class Peacefull : public Character
{
public:
	Peacefull(std::string _name, int _health, int _mana, int _damage,
		Map *_map, int _row, int _col, char _symbol, int _color);

	int Level();
	int Experience();
	int NextLevelExperience();
	
	int MaxMana();
	int Mana();
	void ReceiveExperience(Monster*);

	void Regenerate();

	void Hit(Unit*) override;
	void Hit(Peacefull*) override;
	void Hit(Monster*) override;

	void ReceiveDamage(Unit*) override;
	void ReceiveDamage(Peacefull*) override;
	void ReceiveDamage(Monster*) override;
	void ReceiveDamage(Projectile*) override;

protected:
	static const int level_exp = 15;
	static const int level_health = 4;
	static const int level_mana = 3;
	static const int level_damage = 2;
	static const int regen_cycle = 3;

	int mana, max_mana;
	int experience;
	int level;
	int regen;
};

class Knight : public Peacefull
{
public:
	Knight(std::string name, Map *_map, int row, int col);

	void Move(std::vector<Unit*> &units) override;
};

class Princess : public Peacefull
{
public:
	Princess(std::string name, Map *_map, int row, int col);

	void Move(std::vector<Unit*> &units) override;
	void ReceiveDamage(Peacefull *u);
	bool IsSaved();

private:
	bool saved;
};

class Monster : public Character
{
public:
	Monster(std::string _name, int _health, int _damage,
		int _exp_award, int _vis_radius,
		Map *_map, int _row, int _col, char _symbol, int _color);

	int ExperinceAward();

	void Hit(Unit*) override;
	void Hit(Peacefull*) override;
	void Hit(Monster*) override;

	void ReceiveDamage(Unit*) override;
	void ReceiveDamage(Peacefull*) override;
	void ReceiveDamage(Monster*) override;
	void ReceiveDamage(Projectile*) override;

	void Move(std::vector<Unit*> &units);

protected:
	bool InRadius(Unit*);

	int experience_award;
	int visibility_radius;
};

class Zombie : public Monster
{
public:
	Zombie(Map *_map, int row, int col);
};

class Dragon : public Monster
{
public:
	Dragon(Map *_map, int row, int col);
	void Move(std::vector<Unit*> &units);
};
