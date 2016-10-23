#pragma once
#include <string>
#include <curses.h>
#include <vector>

#include "utils.h"
#include "map.h"
#include "units.h"

enum LevelType {
	LT_RANDOM = 0
};

class Level
{
public:
	Level(LevelType lt, int map_rows, int map_cols, WINDOW *window, std::string playerName, WINDOW *_player_info);
	void GenerateRandom(int rows, int cols, WINDOW *wind, std::string playerName);
	bool Iterate();

private:
	void UpdatePlayerInformation();

	Map *map;
	Knight *player;
	View *view;
	std::vector<Unit*> units;
	WINDOW *player_info;
};