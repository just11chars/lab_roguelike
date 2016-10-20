#include <string>

#include "level.h"
#include "utils.h"
#include "map.h"
#include "units.h"

Level::Level(LevelType lt, int map_rows, int map_cols, WINDOW *window, std::string playerName)
{
	if (lt == LT_RANDOM)
		GenerateRandom(map_rows, map_cols, window, playerName);
}

void Level::GenerateRandom(int rows, int cols, WINDOW *wind, std::string playerName)
{
	map = new Map(rows, cols);
	player = new Knight(playerName, map, rand() % rows, rand() % cols);
	view = new View(wind, map, player);

	Princess* pr = new Princess("RichBitch", map, rand() % rows, rand() % cols);
	units.push_back(pr);
}

void Level::Iterate()
{
	player->Move();
	for each (Unit *u in units)
		u->Move();

	view->Update(units);
}