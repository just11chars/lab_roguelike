#include "config.h"

Config config;

Sizes::Sizes()
{

}

Sizes::Sizes(strings_map &m)
{
	for (auto it = m.begin(); it != m.end(); ++it)
		data[it->first] = std::stoi(it->second);

	for (int i = 0; i < fields.size(); ++i)
		Config::RequireField(m, fields[i]);
}

int Sizes::operator[](std::string s)
{
	return data[s];
}

Config::Config()
{
	std::ifstream file("config.txt");
	if (file.fail()) {
		throw std::exception("Error while opening file \"config.txt\"");
		return;
	}

	while (!file.eof()) {
		std::string s;
		getline(file, s);

		if (!s.empty() && s.front() != '#' && s.back() == '{') {
			s.pop_back();
			ReadBlock(file, s);
		}
	}

	RequireBlock("sizes");
	sizes = Sizes(blocks["sizes"]);
}

Config::~Config()
{
	blocks.clear();
}

std::pair<std::string, std::string> Config::ParseJSONString(std::string s)
{
	s.erase(0, 1);
	s.pop_back();

	int i;
	for (i = (int)s.length() - 1; i >= 2; --i)
		if (s.substr(i - 2, 3) == "\"=\"") {
			std::string a = s.substr(0, i - 2);
			std::string b = s.substr(i + 1, s.length());
			return std::make_pair(a, b);
			break;
		}
	if (i < 2) { 
		throw std::exception(("String \"" + s + "\"is corrupted").c_str());
	}
}

void Config::ReadBlock(std::ifstream &file, std::string name)
{
	while (!file.eof()) {
		std::string s;
		getline(file, s);
		if (s == "}")
			break;

		if (!s.empty() && s.front() != '#') {
			std::pair<std::string, std::string> p = ParseJSONString(s);
			blocks[name][p.first] = p.second;
		}
	}
}

bool Config::RequireBlock(std::string name)
{
	if (!blocks.count(name)) {
		throw std::exception(("Block \"" + name + "\" is missing").c_str());
		return false;
	}
	return true;
}

bool Config::RequireField(strings_map &m, std::string name)
{
	if (!m.count(name)) {
		throw std::exception(("\"" + name + "\" is missing").c_str());
		return false;
	}
	return true;
}
