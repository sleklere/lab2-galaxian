#pragma once
#include <SFML/Graphics.hpp>

class Menu
{
private:
	sf::Font _font;
	sf::Text _titleText;
	sf::Text _playText;
	sf::Text _scoreboardText;
	sf::Text _exitText;
	bool _active;
	int _choice;
public:
	Menu();
	void update(sf::RenderWindow& window);
	int getChoice();
	bool getActive();
	void setActive(bool active);
};
