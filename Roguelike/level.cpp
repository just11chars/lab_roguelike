#include <string>

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

	for (int i = 0; i < rows / 20 + cols / 20; ++i)
		units.push_back(new Zombie(map, rand() % rows, rand() % cols));
}

bool Level::Iterate()
{
	player->Move();
	for each (Unit *u in units)
		u->Move();

	UpdatePlayerInformation();
	view->Update(units);

	return player->HealthPoints() > 0 && player->Position() != units[0]->Position();
}

void Level::UpdatePlayerInformation()
{
	box(player_info, 0, 0);
	mvwaddstr(player_info, 1, (player_info->_maxx - strlen("Player")) / 2, "Player");
	mvwprintw(player_info, 3, 1, "%-10s%d", "Health", player->HealthPoints());
	mvwprintw(player_info, 4, 1, "%-10s%d", "Mana", player->ManaPoints());
	wrefresh(player_info);
}