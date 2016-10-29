#include <vector>

#include "components.h"

LogMessageHit::LogMessageHit(std::string _attacker, std::string _receiver)
{
	attacker = _attacker;
	receiver = _receiver;
}

std::string LogMessageHit::Text()
{
	return attacker + " hit " + receiver;
}

LogMessageCast::LogMessageCast(std::string _attacker, std::string _receiver, std::string _spell)
{
	attacker = _attacker;
	receiver = _receiver;
	spell = _spell;
}

std::string LogMessageCast::Text()
{
	return attacker + " cast " + spell + " to " + receiver;
}

LogMessageDeath::LogMessageDeath(std::string _attacker, std::string _receiver)
{
	attacker = _attacker;
	receiver = _receiver;
}

std::string LogMessageDeath::Text()
{
	return attacker + " killed " + receiver;
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
	std::string result;
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