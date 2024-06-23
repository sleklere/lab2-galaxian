#include "Score.h"

Score::Score()
{
	// setear fecha actual
	_date = time(0);
}

int Score::getPoints()
{
	return _points;
}

const char* Score::getPlayerName()
{
	return _playerName;
}

void Score::setPlayerName(const char* name)
{
	strcpy_s(_playerName, name);
}

void Score::setPoints(int points)
{
	_points = points > 0 ? points : _points;;
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
	return ctime(&_date);
}

void Score::Show()
{
	std::cout << "+-------------------------+" << std::endl;
	std::cout << "Player score" << std::endl;
	std::cout << this->getPlayerName() << std::endl;
	std::cout << this->getDateAsString();
	std::cout << "+-------------------------+" << std::endl;
}
