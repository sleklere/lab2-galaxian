#pragma once
#include <SFML/Graphics.hpp>
#include "Menu.h"
#include "Globals.h"
#include "Screen.h"

class GameOver: public Screen
{
private:
	sf::Font _font;
	sf::Text _titleText;
	sf::Text _menuText;
	sf::Text _exitText;
	sf::Text _scoreText;
	bool _active;
	int _finalScore;
public:
	GameOver();
	void update(sf::RenderWindow& window, Menu& menu, float deltaTime);
	bool getActive();
	void setActive(bool active);
	void setFinalScore(int finalScore);
};
