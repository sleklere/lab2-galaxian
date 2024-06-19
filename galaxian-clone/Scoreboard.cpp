#include "Scoreboard.h"

Scoreboard::Scoreboard()
{
	_font.loadFromFile("ARCADE_I.ttf");

	_titleText.setFont(_font);
	_titleText.setString("Scoreboard");
	_titleText.setCharacterSize(40);
	_titleText.setPosition(1280 / 2 - _titleText.getGlobalBounds().width / 2, 100);

	_backText.setFont(_font);
	_backText.setString("Back");
	_backText.setCharacterSize(25);
	_backText.setPosition(10, 10);
}

void Scoreboard::update(sf::RenderWindow& window, Menu& menu)
{
	sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
	sf::Vector2f mousePositionCoords = window.mapPixelToCoords(mousePosition);

	sf::Cursor cursor;
	cursor.loadFromSystem(sf::Cursor::Arrow);
	window.setMouseCursor(cursor);

	_backText.setFillColor(sf::Color::White);

	if (_backText.getGlobalBounds().contains(mousePositionCoords))
	{
		cursor.loadFromSystem(sf::Cursor::Hand);
		window.setMouseCursor(cursor);
		_backText.setFillColor(sf::Color::Red);
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			menu.setActive(true);
			cursor.loadFromSystem(sf::Cursor::Arrow);
			window.setMouseCursor(cursor);
		}
	}

	window.draw(_titleText);
	window.draw(_backText);
}
