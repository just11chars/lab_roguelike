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
};

class Map;

class Character: public Unit
{
public:
	Character(std::string _name, int _health, int _damage,
		Map *_map, int _row, int _col, char _symbol, int _color = COLOR_WHITE);
	
	int HealthPoints() override;
	int Damage() override;
	Point Character::Position() override;

	void Move() override;
	void Draw(WINDOW *window, Point shift) override;

protected:
	std::string name;
	int health, damage;

	Map *map;
	int row, col;

	int color;
	char symbol;
};

class Knight : public Character
{
public:
	Knight(std::string name, Map *_map, int row, int col);

	void Move();
};

class Princess : public Character
{
public:
	Princess(std::string name, Map *_map, int row, int col);

	void Move() override;
};