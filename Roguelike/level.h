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
	Level(LevelType lt, int map_rows, int map_cols, WINDOW *window, std::string playerName);
	void GenerateRandom(int rows, int cols, WINDOW *wind, std::string playerName);
	void Iterate();

private:
	Map *map;
	Knight *player;
	View *view;
	std::vector<Unit*> units;
};