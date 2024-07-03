#include "Score.h"

Score::Score()
{
	// setear fecha actual
	_date = time(0);
	_points = 0;
}

int Score::getPoints()
{
	return _points;
}

void Score::setPoints(int points)
{
	_points = points;
}

void Score::addPoints(int points)
{
	_points += points;
}

time_t Score::getDate() const
{
	return _date;
}

std::string Score::getDateAsString() const
{
	struct tm* localTime = localtime(&_date);
	int day = localTime->tm_mday;
	int month = localTime->tm_mon + 1; 
	int year = localTime->tm_year + 1900;

	std::string date = std::to_string(day) + " - " + std::to_string(month) + " - " + std::to_string(year);

	return date;
}

void Score::Show()
{
	std::cout << "+-------------------------+" << std::endl;
	std::cout << "Player score" << std::endl;
	std::cout << this->getDateAsString();
	std::cout << "+-------------------------+" << std::endl;
}
