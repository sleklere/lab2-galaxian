#pragma once
#include <ctime>
#include <string>
#include <iostream>

class Score {
private:
	int _points;
	time_t _date;
public:
	Score();
	int getPoints();
	time_t getDate() const;
	std::string getDateAsString() const;

	void setPoints(int points);

	void addPoints(int points);

	void Show();
};

