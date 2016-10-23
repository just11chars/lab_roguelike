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
	view = new View(wind, map, player);

	Princess* pr = new Princess("princess", map, rand() % rows, rand() % cols);
	units.push_back(pr);

	for (int i = 0; i < rows / 2 + cols / 2; ++i) {
		int row = rand() % rows;
		int col = rand() % cols;

		while (!map->IsCellFree(row, col)) {
			row = rand() % rows;
			col = rand() % cols;
		}

		units.push_back(new Zombie(map, row, col));
	}
}

bool Level::Iterate()
{
	ClearInvalidUnits();

	player->Move(units);
	for each (Unit *u in units)
		u->Move(units);

	UpdatePlayerInformation();
	view->Update(units);

	return player->Health() > 0 && player->Position() != units[0]->Position();
}

void Level::UpdatePlayerInformation()
{
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