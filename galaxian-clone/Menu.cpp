#include "Menu.h"

Menu::Menu()
{
	_active = true;
	_font.loadFromFile("ARCADE_I.ttf");

	_titleText.setFont(_font);
	_titleText.setString("Galaxian");
	_titleText.setFillColor(sf::Color::Cyan);
	_titleText.setLetterSpacing(2);
	_titleText.setCharacterSize(40);
	_titleText.setPosition(1280 / 2 - _titleText.getGlobalBounds().width / 2, 80);

	_playText.setFont(_font);
	_playText.setString("Play");
	_playText.setPosition(100, 250);

	_scoreboardText.setFont(_font);
	_scoreboardText.setString("Scoreboard");
	_scoreboardText.setPosition(100, 350);

	_exitText.setFont(_font);
	_exitText.setString("Exit");
	_exitText.setPosition(100, 450);
}

void Menu::update(sf::RenderWindow& window) {
	sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
	sf::Vector2f mousePositionCoords = window.mapPixelToCoords(mousePosition);

	sf::Cursor cursor;
	cursor.loadFromSystem(sf::Cursor::Arrow);
	window.setMouseCursor(cursor);

	_playText.setFillColor(sf::Color::White);
	_scoreboardText.setFillColor(sf::Color::White);
	_exitText.setFillColor(sf::Color::White);

	if (_playText.getGlobalBounds().contains(mousePositionCoords) )
	{
		cursor.loadFromSystem(sf::Cursor::Hand);
		window.setMouseCursor(cursor);
		_playText.setFillColor(sf::Color::Red);
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			_choice = 1;
			_active = false;
			cursor.loadFromSystem(sf::Cursor::Arrow);
			window.setMouseCursor(cursor);
		}
	}
	if (_scoreboardText.getGlobalBounds().contains(mousePositionCoords))
	{
		cursor.loadFromSystem(sf::Cursor::Hand);
		window.setMouseCursor(cursor);
		_scoreboardText.setFillColor(sf::Color::Red);
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			_choice = 2;
			_active = false;
			cursor.loadFromSystem(sf::Cursor::Arrow);
			window.setMouseCursor(cursor);
		}
	}
	if (_exitText.getGlobalBounds().contains(mousePositionCoords))
	{
		cursor.loadFromSystem(sf::Cursor::Hand);
		window.setMouseCursor(cursor);
		_exitText.setFillColor(sf::Color::Red);
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			exit(1);
			cursor.loadFromSystem(sf::Cursor::Arrow);
			window.setMouseCursor(cursor);
		}
	}

	window.draw(_titleText);
	window.draw(_playText);
	window.draw(_scoreboardText);
	window.draw(_exitText);
}

int Menu::getChoice()
{
	return _choice;
}

bool Menu::getActive()
{
	return _active;
}

void Menu::setActive(bool active) {
	_active = active;
}