#include "GameOver.h"

GameOver::GameOver() {
	_active = false;

	_font.loadFromFile("ARCADE_I.ttf");

	_titleText.setFont(_font);
	_titleText.setString("GAME OVER");
	_titleText.setCharacterSize(50);
	_titleText.setPosition(W_WIDTH / 2 - _titleText.getGlobalBounds().width / 2, 200);
	_titleText.setFillColor(sf::Color::Red);

	_scoreText.setFont(_font);
	_scoreText.setCharacterSize(25);
	_scoreText.setFillColor(sf::Color::Cyan);

	_roundText.setFont(_font);
	_roundText.setCharacterSize(25);
	_roundText.setFillColor(sf::Color::Cyan);

	_menuText.setFont(_font);
	_menuText.setString("Menu");
	_menuText.setCharacterSize(35);
	_menuText.setPosition(W_WIDTH / 2 - _menuText.getGlobalBounds().width / 2, _titleText.getPosition().y + 200);

	_exitText.setFont(_font);
	_exitText.setString("Exit");
	_exitText.setCharacterSize(35);
	_exitText.setPosition(W_WIDTH / 2 - _exitText.getGlobalBounds().width / 2, _menuText.getPosition().y + 60);
}

void GameOver::update(sf::RenderWindow& window, Menu& menu, float deltaTime)
{
	Screen::update(window, deltaTime);
	sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
	sf::Vector2f mousePositionCoords = window.mapPixelToCoords(mousePosition);

	sf::Cursor cursor;
	cursor.loadFromSystem(sf::Cursor::Arrow);
	window.setMouseCursor(cursor);

	_menuText.setFillColor(sf::Color::White);
	_exitText.setFillColor(sf::Color::White);

	_scoreText.setString("SCORE: " + std::to_string(_finalScore));
	_scoreText.setPosition(W_WIDTH / 2 - _scoreText.getGlobalBounds().width / 2, /*_titleText.getPosition().y + 60*/ 290); //pongo la pos aca pq sino no me toma bien el tamaño de scoreText

	_roundText.setString("ROUND: " + std::to_string(_round));
	_roundText.setPosition(W_WIDTH / 2 - _roundText.getGlobalBounds().width / 2, 330);

	if (_menuText.getGlobalBounds().contains(mousePositionCoords))
	{
		cursor.loadFromSystem(sf::Cursor::Hand);
		window.setMouseCursor(cursor);
		_menuText.setFillColor(sf::Color::Red);
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			menu.setActive(true);
			setActive(false);
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
	window.draw(_scoreText);
	window.draw(_roundText);
	window.draw(_menuText);
	window.draw(_exitText);
}

bool GameOver::getActive()
{
	return _active;
}

void GameOver::setActive(bool active) {
	_active = active;
}

void GameOver::setFinalScore(int finalScore)
{
	_finalScore = finalScore;
}

void GameOver::setRound(int round)
{
	_round = round;
}
