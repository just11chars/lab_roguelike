#pragma once
#include <string>
#include <map>
#include <vector>
#include <fstream>

typedef std::map<std::string, std::string> strings_map;

class Sizes {
public:
	Sizes();
	Sizes(strings_map &m);
	int operator[](std::string s);

private:
	std::map<std::string, int> data;
	std::vector<std::string> fields = {
		"zombie_coeff",
		"dragon_coeff",
		"field_width",
		"field_height",
	};
};

class Config {
public:
	Config();
	~Config();

	static bool RequireField(strings_map &m, std::string name);
	Sizes sizes;

private:
	bool RequireBlock(std::string name);
	void ReadBlock(std::ifstream &file, std::string name);
	std::pair<std::string, std::string> ParseJSONString(std::string s);

	std::map<std::string, std::map<std::string, std::string>> blocks;
};

extern Config config;
