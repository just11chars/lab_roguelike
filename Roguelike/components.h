#pragma once
#include <vector>
#include <curses.h>

class LogMessage
{
public:
	virtual std::string Text() = 0;
};

class LogMessageHit : LogMessage
{
public:
	LogMessageHit(std::string _attacker, std::string _receiver);
	std::string Text() override;

private:
	std::string attacker, receiver;
};

class LogMessageCast : LogMessage
{
public:
	LogMessageCast(std::string _attacker, std::string _receiver, std::string _spell);
	std::string Text() override;

private:
	std::string attacker, receiver;
	std::string spell;
};

class LogMessageDeath : LogMessage
{
public:
	LogMessageDeath(std::string _attacker, std::string _receiver);
	std::string Text() override;

private:
	std::string attacker, receiver;
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