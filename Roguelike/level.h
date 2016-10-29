#pragma once
#include <string>
#include <curses.h>
#include <vector>

#include "utils.h"
#include "map.h"
#include "units.h"
#include "components.h"

enum LevelType {
	LT_RANDOM = 0
};

class Level
{
public:
	Level(LevelType lt, int map_rows, int map_cols, WINDOW *window, std::string playerName,
		WINDOW *_player_info_win, Log *_log);

	void GenerateRandom(int rows, int cols, WINDOW *wind, std::string playerName);
	bool Iterate();

private:
	void Display();
	void ClearInvalidUnits();
	bool CellWithUnit(int row, int col);

	template <class T>
	void GenerateUnits(int count, int rows, int cols);

	Knight *player;
	Princess *princess;
	std::vector<Unit*> units;

	Map *map;
	View *view;
	PlayerInfo *player_info; 
	Log *log;
};