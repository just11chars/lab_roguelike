#include <vector>

#include "components.h"

using std::string;

LogMessageHit::LogMessageHit(string _attacker, string _receiver)
{
	attacker = _attacker;
	receiver = _receiver;
}

string LogMessageHit::Text()
{
	return attacker + " hit " + receiver;
}

LogMessageCast::LogMessageCast(string _attacker, string _receiver, string _spell)
	: LogMessageHit(_attacker, _receiver)
{
	spell = _spell;
}

string LogMessageCast::Text()
{
	return attacker + " cast " + spell + " to " + receiver;
}

LogMessageDeath::LogMessageDeath(string _attacker, string _receiver)
	: LogMessageHit(_attacker, _receiver)
{
	;
}

string LogMessageDeath::Text()
{
	return attacker + " killed " + receiver;
}

LogMessageNewLevel::LogMessageNewLevel(string _person, int _level)
{
	person = _person;
	level = _level;
}

string LogMessageNewLevel::Text()
{
	char str_level[5];
	_itoa_s(level, str_level, 10);

	return person + " received level " + str_level;
}

LogMessageCastDeath::LogMessageCastDeath(string _attacker, string _receiver, string _spell)
	: LogMessageCast(_attacker, _receiver, _spell)
{
	;
}

string LogMessageCastDeath::Text()
{
	return attacker + " killed " + receiver + " with " + spell;
}

LogMessageWin::LogMessageWin()
{
	;
}

string LogMessageWin::Text()
{
	return "---CONGRATULATIONS, YOU WIN---";
}

Log::Log(WINDOW *_window)
{
	border = _window;
	box(_window, 0, 0);
	wrefresh(_window);

	int x0 = _window->_begx;
	int y0 = _window->_begy;
	int maxx = _window->_maxx;
	int maxy = _window->_maxy;

	window = newwin(maxy - 2, maxx - 2, y0 + 1, x0 + 1);
}

Log::~Log()
{
	DeleteMessages();
	delete window;
}

void Log::AddMessage(LogMessage *message)
{
	messages.push_back(message);
}

void Log::Display()
{
	string result;
	for each (LogMessage *mes in messages)
		result += mes->Text() + ". ";

	box(border, 0, 0);
	wrefresh(border);

	wclear(window);
	mvwaddstr(window, 0, 0, result.c_str());
	wrefresh(window);

	DeleteMessages();
}

void Log::DeleteMessages()
{
	for (int i = 0; i < messages.size(); ++i)
		delete messages[i];

	messages.clear();
}

PlayerInfo::PlayerInfo(Knight *_player, WINDOW *_window)
{
	player = _player;
	window = _window;
	player->SetPlayerInfo(this);
}

void PlayerInfo::Display()
{
	wclear(window);
	box(window, 0, 0);

	mvwprintw(window, 1, 1, "Level %d ( %d / %d )", player->Level(), player->Experience(), player->NextLevelExperience());
	mvwprintw(window, 3, 1, "%-10s%d / %d", "Health", player->Health(), player->MaxHealth());
	mvwprintw(window, 4, 1, "%-10s%d / %d", "Mana", player->Mana(), player->MaxMana());
	mvwprintw(window, 5, 1, "%-10s%d", "Damage", player->Damage());
	mvwprintw(window, 7, 1, "%s", (player->State() == FS_MELEE) ? "MELEE" : "WIZARD");
	
	wrefresh(window);
}