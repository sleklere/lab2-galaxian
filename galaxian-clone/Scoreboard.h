#pragma once
#include <SFML/Graphics.hpp>
#include "Menu.h"

class Scoreboard
{
private:
	sf::Font _font;
	sf::Text _titleText;
	sf::Text _backText;
public:
	Scoreboard();
	void update(sf::RenderWindow& window,Menu& menu);
};

