#include <string>
#include <vector>
using std::vector;

#include "level.h"
#include "utils.h"
#include "map.h"
#include "units.h"

Level::Level(LevelType lt, int map_rows, int map_cols, WINDOW *window, std::string playerName, WINDOW *_player_info)
{
	if (lt == LT_RANDOM)
		GenerateRandom(map_rows, map_cols, window, playerName);
	player_info = _player_info;
}

void Level::GenerateRandom(int rows, int cols, WINDOW *wind, std::string playerName)
{
	map = new Map(rows, cols);
	player = new Knight(playerName, map, rand() % rows, rand() % cols);
	//player = new Knight(playerName, map, 15, 15);
	view = new View(wind, map, player);

	princess = new Princess("princess", map, rand() % rows, rand() % cols);
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

	UpdatePlayerInformation();
	view->Update(units);

	return player->Health() > 0 && !princess->IsSaved();
}

void Level::UpdatePlayerInformation()
{
	wclear(player_info);
	box(player_info, 0, 0);

	//mvwaddstr(player_info, 1, (player_info->_maxx - strlen("Player")) / 2, "Player");
	mvwprintw(player_info, 1, 1, "Level %d ( %d / %d )", player->Level(), player->Experience(), player->NextLevelExperience());
	mvwprintw(player_info, 3, 1, "%-10s%d / %d", "Health", player->Health(), player->MaxHealth());
	mvwprintw(player_info, 4, 1, "%-10s%d / %d", "Mana", player->Mana(), player->MaxMana());
	mvwprintw(player_info, 5, 1, "%-10s%d", "Damage", player->Damage());
	wrefresh(player_info);
}

void Level::ClearInvalidUnits()
{
	for (auto it = units.begin(); it != units.end(); ) {
		if ((*it)->invalid) {
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

		units.push_back(new T(map, row, col));
	}
}
