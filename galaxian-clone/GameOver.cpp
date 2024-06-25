#include "GameOver.h"

GameOver::GameOver() {
	_active = false;

	_font.loadFromFile("ARCADE_I.ttf");

	_titleText.setFont(_font);
	_titleText.setString("GAME OVER");
	_titleText.setCharacterSize(50);
	_titleText.setPosition(W_WIDTH / 2 - _titleText.getGlobalBounds().width / 2, W_HEIGHT / 2 - (_titleText.getGlobalBounds().height + _scoreText.getGlobalBounds().height));
	_titleText.setFillColor(sf::Color::Red);

	_scoreText.setFont(_font);
	_scoreText.setCharacterSize(25);

	_menuText.setFont(_font);
	_menuText.setString("Menu");
	_menuText.setCharacterSize(35);
	_menuText.setPosition(W_WIDTH / 2 - _menuText.getGlobalBounds().width / 2, _titleText.getPosition().y + 120);

	_exitText.setFont(_font);
	_exitText.setString("Exit");
	_exitText.setCharacterSize(35);
	_exitText.setPosition(W_WIDTH / 2 - _exitText.getGlobalBounds().width / 2, _menuText.getPosition().y + 60);

	backgroundTexture.loadFromFile("background.png");

	float scaleY = static_cast<float>(W_HEIGHT) / backgroundTexture.getSize().y;

	backgroundSprite1.setTexture(backgroundTexture);
	backgroundSprite2.setTexture(backgroundTexture);

	// el segundo fondo va justo abajo del primero
	backgroundSprite1.setPosition(0, 0);
	backgroundSprite2.setPosition(0, -static_cast<float>(backgroundTexture.getSize().y) * scaleY); //static_cast<float> previene error de tipos sin signo

	backgroundSpeed = 100.f;
}

void GameOver::update(sf::RenderWindow& window, Menu& menu, float deltaTime)
{
	sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
	sf::Vector2f mousePositionCoords = window.mapPixelToCoords(mousePosition);

	sf::Cursor cursor;
	cursor.loadFromSystem(sf::Cursor::Arrow);
	window.setMouseCursor(cursor);

	_menuText.setFillColor(sf::Color::White);
	_exitText.setFillColor(sf::Color::White);

	_scoreText.setString("YOUR SCORE: " + std::to_string(_finalScore));
	_scoreText.setPosition(W_WIDTH / 2 - _scoreText.getGlobalBounds().width / 2, _titleText.getPosition().y + 60); //pongo la pos aca pq sino no me toma bien el tamaño de scoreText

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

	backgroundSprite1.move(0, backgroundSpeed * deltaTime);
	backgroundSprite2.move(0, backgroundSpeed * deltaTime);

	// se 'envuelven' los fondos para que el scroll sea infinito
	if (backgroundSprite1.getPosition().y >= backgroundTexture.getSize().y * backgroundSprite1.getScale().y) {
		backgroundSprite1.setPosition(0, backgroundSprite2.getPosition().y - backgroundTexture.getSize().y * backgroundSprite1.getScale().y);
	}
	if (backgroundSprite2.getPosition().y >= backgroundTexture.getSize().y * backgroundSprite2.getScale().y) {
		backgroundSprite2.setPosition(0, backgroundSprite1.getPosition().y - backgroundTexture.getSize().y * backgroundSprite2.getScale().y);
	}


	window.draw(backgroundSprite1);
	window.draw(backgroundSprite2);
	window.draw(_titleText);
	window.draw(_scoreText);
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
