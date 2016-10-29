#include <string>
#include <vector>
using std::vector;

#include "level.h"
#include "utils.h"
#include "map.h"
#include "units.h"
#include "components.h"

Level::Level(LevelType lt, int map_rows, int map_cols, WINDOW *window, std::string playerName,
	WINDOW *_player_info_win,  Log *_log)
{
	log = _log;

	if (lt == LT_RANDOM)
		GenerateRandom(map_rows, map_cols, window, playerName);

	player_info = new PlayerInfo(player, _player_info_win);
	Display();
}

void Level::GenerateRandom(int rows, int cols, WINDOW *wind, std::string playerName)
{
	map = new Map(rows, cols);
	player = new Knight(playerName, map, rand() % rows, rand() % cols, log);
	//player = new Knight(playerName, map, 15, 15);
	view = new View(wind, map, player);

	princess = new Princess("princess", map, rand() % rows, rand() % cols, log);
	units.push_back(player);
	units.push_back(princess);

	GenerateUnits<Zombie>(rows / 3 + cols / 3, rows, cols);
	GenerateUnits<Dragon>(rows / 30 + cols / 30, rows, cols);
	//GenerateUnits<Dragon>(1, 1, 1);
}

bool Level::Iterate()
{
	ClearInvalidUnits();

	for (int i = 0; i < units.size(); ++i)
		units[i]->Move(units);
	
	Display();

	return player->Health() > 0 && !princess->IsSaved();
}

void Level::Display()
{
	player_info->Display();
	view->Display(units);
	log->Display();
}

void Level::ClearInvalidUnits()
{
	for (auto it = units.begin(); it != units.end(); ) {
		if ((*it)->invalid) {
			delete *it;
			it = units.erase(it);
		}
		else {
			++it;
		}
	}
}

bool Level::CellWithUnit(int row, int col)
{
	for each (Unit *u in units) {
		if (u->Position() == Point(row, col))
			return true;
	}
	return false;
}

template <class T>
void Level::GenerateUnits(int count, int rows, int cols)
{
	while (count--) {
		int row = rand() % rows;
		int col = rand() % cols;

		while (!map->IsCellFree(row, col) && CellWithUnit(row, col)) {
			row = rand() % rows;
			col = rand() % cols;
		}

		units.push_back(new T(map, row, col, log));
	}
}
