#pragma once
#include <ctime>
#include <string>
#include <iostream>

class Score {
private:
	int _points;
	time_t _date;
	char _playerName[30];
public:
	Score();
	int getPoints();
	time_t getDate() const;
	std::string getDateAsString() const;

	const char* getPlayerName();
	void setPlayerName(const char* name);
	void setPoints(int points);

	void addPoints(int points);

	void Show();
};

