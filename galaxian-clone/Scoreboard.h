#pragma once
#include <SFML/Graphics.hpp>
#include "Menu.h"
#include "FilesManager.h"
#include "Score.h"
#include "Screen.h"

class Scoreboard: public Screen
{
private:
	sf::Font _font;
	sf::Text _titleText;
	sf::Text _backText;
	Score _score;
public:
	Scoreboard();
	void update(sf::RenderWindow& window,Menu& menu, FilesManager<Score> scoresFile, float deltaTime);
};

