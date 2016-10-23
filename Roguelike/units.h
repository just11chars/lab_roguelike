#pragma once
#include <string>

#include "map.h"

class Unit
{
public:
	virtual int HealthPoints() = 0;
	virtual int Damage() = 0;
	virtual void Move() = 0;
	virtual void Draw(WINDOW *window, Point shift) = 0;
	virtual Point Position() = 0;

	virtual void Hit(Unit*) = 0;
	virtual void ReceiveDamage(int rec_damage) = 0;
};

class Map;

class Character: public Unit
{
public:
	Character(std::string _name, int _health, int _damage, int _mana,
		Map *_map, int _row, int _col, char _symbol, int _color);
	
	int HealthPoints() override;
	int ManaPoints(); 

	int Damage() override;
	Point Character::Position() override;

	void Move() override;
	void Draw(WINDOW *window, Point shift) override;

	void Hit(Unit*) override;
	void ReceiveDamage(int rec_damage) override;

protected:
	std::string name;
	int health, damage, mana;

	Map *map;
	int row, col;

	int color;
	char symbol;
};

class Knight : public Character
{
public:
	Knight(std::string name, Map *_map, int row, int col);

	void Move() override;
};

class Princess : public Character
{
public:
	Princess(std::string name, Map *_map, int row, int col);

	void Move() override;
};

class Monster : public Character
{
public:
	Monster(std::string name, Map *_map, int row, int col);
};