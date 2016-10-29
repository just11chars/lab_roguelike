#pragma once
#include <vector>
#include <curses.h>

#include "units.h"
#include "utils.h"

enum CellState {
	CS_UNDEF = 0,
	CS_GROUND = 1,
	CS_WALL = 2,
	CS_CURSED = 3, // TODO: place, where hp will decrease, mb smth with mana
};

struct Cell {
	char fg_color, bg_color, symbol;
	Cell();
	Cell(char _fg_color, char _bg_color, char _symbol);
};

void init_cell_types();

class Map
{
public:
	Map(int _rows, int _cols);
	CellState GetCellState(int row, int col);
	Cell GetCell(int row, int col);

	bool IsCellFree(int row, int col);

	int MaxRow();
	int MaxCol();

private:
	void GenerateRectangle(int height, int width, double wall_prob = 0.0);
	bool IsCellValid(int row, int col);

	int rows, cols;
	std::vector<std::vector<CellState>> cells;
};

class Character;
class Unit;

class View
{
public:
	// TODO: safe pointers
	View(WINDOW *wind, Map *_map, Character *_player);
	Rect GetMapRect();
	void Display(std::vector<Unit*> &units);

private:
	WINDOW *window;
	int rows, cols;
	Map *map;
	Character *player;
};