#pragma once

void init();
void init_utils();
void init_curses();

bool rand_event(double prob);

struct Point
{
	int row, col;

	Point(int _row, int _col);
	int Length();

	friend bool operator==(const Point &a, const Point &b);
	friend bool operator!=(const Point &a, const Point &b);
	friend Point operator-(const Point &a, const Point &b);
};

struct Rect
{
	int r0, c0;
	int r1, c1;

	Rect(int _r0, int _c0, int _r1, int _c1);
	bool PointInside(int row, int col);
	bool PointInside(Point p);
};