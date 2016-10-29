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
	itoa(level, str_level, 10);

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
	window = _window;
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

	wclear(window);
	box(window, 0, 0);
	mvwaddstr(window, 1, 1, result.c_str());
	wrefresh(window);

	DeleteMessages();
}

void Log::DeleteMessages()
{
	for (int i = 0; i < messages.size(); ++i)
		delete messages[i];

	messages.clear();
}