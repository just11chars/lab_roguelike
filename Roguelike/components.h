#pragma once
#include <vector>
#include <curses.h>

class LogMessage
{
public:
	virtual std::string Text() = 0;
};

class LogMessageHit : public LogMessage
{
public:
	LogMessageHit(std::string _attacker, std::string _receiver);
	std::string Text() override;

protected:
	std::string attacker, receiver;
};

class LogMessageCast : public LogMessageHit
{
public:
	LogMessageCast(std::string _attacker, std::string _receiver, std::string _spell);
	std::string Text();

protected:
	std::string spell;
};

class LogMessageDeath : public LogMessageHit
{
public:
	LogMessageDeath(std::string _attacker, std::string _receiver);
	std::string Text();
};

class LogMessageCastDeath : public LogMessageCast
{
public:
	LogMessageCastDeath(std::string _attacker, std::string _receiver, std::string _spell);
	std::string Text();
};

class LogMessageNewLevel : public LogMessage
{
public:
	LogMessageNewLevel(std::string _person, int _level);
	std::string Text() override;

protected:
	std::string person;
	int level;
};

class LogMessageWin : public LogMessage
{
public:
	LogMessageWin();
	std::string Text() override;
};

class Log
{
public:
	Log(WINDOW *_window);
	void AddMessage(LogMessage*);
	void Display();

private:
	void DeleteMessages();

	std::vector<LogMessage*> messages;
	WINDOW *window;
};