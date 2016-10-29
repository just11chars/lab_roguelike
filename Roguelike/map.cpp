#include <curses.h>
#include <vector>
#include <cstdlib>
#include <algorithm>

#include "utils.h"
#include "map.h"
#include "units.h"

using std::vector;
using std::max;
using std::min;

// CellState is index
std::vector<Cell> _cells;

void init_cell_types()
{
	_cells.resize(sizeof(CellState));
	_cells[CS_UNDEF] = Cell(COLOR_WHITE, COLOR_BLACK, '?');
	_cells[CS_GROUND] = Cell(COLOR_WHITE, COLOR_BLACK, ' ');
	_cells[CS_WALL] = Cell(COLOR_WHITE, COLOR_BLACK, '#');
	_cells[CS_CURSED] = Cell(COLOR_CYAN, COLOR_MAGENTA, '.');

	//for (char i = COLOR_BLACK; i <= COLOR_WHITE; ++i)
	//	for (char j = COLOR_BLACK; j <= COLOR_WHITE; ++j)
	//		init_pair(1 + 8 * i + j, i, j);
}

Cell::Cell()
{
	;
}

Cell::Cell(char _fg_color, char _bg_color, char _symbol)
{
	fg_color = _fg_color;
	bg_color = _bg_color;
	symbol = _symbol;
}

CellState Map::GetCellState(int row, int col)
{
	if (IsCellValid(row, col))
		return cells[row][col];
	return CS_UNDEF;
}

Cell Map::GetCell(int row, int col)
{
	return _cells[GetCellState(row, col)];
}

bool Map::IsCellFree(int row, int col)
{
	CellState st = GetCellState(row, col);
	return IsCellValid(row, col) && st != CS_WALL && st != CS_UNDEF;
}

bool Map::IsCellValid(int row, int col)
{
	return Rect(0, 0, MaxRow(), MaxCol()).PointInside(row, col);
}

Map::Map(int _rows, int _cols)
{
	rows = _rows;
	cols = _cols;
	GenerateRectangle(rows, cols, 0.05);
}

int Map::MaxRow()
{
	return rows - 1;
}

int Map::MaxCol()
{
	return cols - 1;
}

void Map::GenerateRectangle(int height, int width, double wall_prob)
{
	cells.resize(height);
	for (int i = 0; i < height; ++i) {
		cells[i].resize(width);
		for (int j = 0; j < width; ++j){
			if (rand_event(wall_prob))
				cells[i][j] = CS_WALL;
			else
				cells[i][j] = CS_GROUND;
		}
	}
}

View::View(WINDOW *wind, Map *_map, Character *_player)
{
	window = wind;
	map = _map;
	player = _player;

	// cause of borders
	rows = window->_maxy - 2;
	cols = window->_maxx - 2;
}

Rect View::GetMapRect()
{
	int pr = player->Position().row;
	int pc = player->Position().col;

	int cent_r = rows / 2;
	int cent_c = cols / 2;

	int r0 = max(0, pr - cent_r);
	int c0 = max(0, pc - cent_c);
	int r1 = min(map->MaxRow(), pr + cent_r);
	int c1 = min(map->MaxCol(), pc + cent_c);
	
	r0 = min(r0, map->MaxRow() - rows + 1);
	c0 = min(c0, map->MaxCol() - cols + 1);
	r1 = max(rows - 1, r1);
	c1 = max(cols - 1, c1);

	return Rect(r0, c0, r1, c1);
}

void View::Display(vector<Unit*> &units)
{
	Rect rect(GetMapRect());
	
	for (int i = rect.r0; i <= rect.r1; ++i)
		for (int j = rect.c0; j <= rect.c1; ++j)
			mvwaddch(window, 1 + i - rect.r0, 1 + j - rect.c0, map->GetCell(i, j).symbol);

	player->Draw(window, Point(rect.r0, rect.c0));
	for each (Unit *u in units)
		if (rect.PointInside(u->Position()))
			u->Draw(window, Point(rect.r0, rect.c0));
	
	box(window, 0, 0);
	wrefresh(window);
}