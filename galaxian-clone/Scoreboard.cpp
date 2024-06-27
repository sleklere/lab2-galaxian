#include "Scoreboard.h"

Scoreboard::Scoreboard()
{
	_font.loadFromFile("ARCADE_I.ttf");

	_titleText.setFont(_font);
	_titleText.setString("Scoreboard");
	_titleText.setFillColor(sf::Color::Cyan);
	_titleText.setCharacterSize(40);
	_titleText.setPosition(1280 / 2 - _titleText.getGlobalBounds().width / 2, 100);

	_backText.setFont(_font);
	_backText.setString("Back");
	_backText.setCharacterSize(25);
	_backText.setPosition(10, 10);
}

void Scoreboard::update(sf::RenderWindow& window, Menu& menu, FilesManager<Score> scoresFile, float deltaTime)
{
	Screen::update(window, deltaTime);

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

	int posY = 250;

	std::vector<Score> top5 = scoresFile.top5();

	for (int i = 0; i < 5; i++) {
		_score = top5[i];

		sf::Text _numberText;
		_numberText.setFont(_font);
		_numberText.setString(std::to_string(i + 1) + ".");
		_numberText.setCharacterSize(25);
		_numberText.setPosition(300, posY);

		sf::Text _dateText;
		_dateText.setFont(_font);
		_dateText.setString(_score.getDateAsString());
		_dateText.setCharacterSize(25);
		_dateText.setPosition(1280 / 2 - _dateText.getGlobalBounds().width / 2, posY);
		
		sf::Text _scoreText;
		_scoreText.setFont(_font);
		_scoreText.setString(std::to_string(_score.getPoints()));
		_scoreText.setCharacterSize(25);
		_scoreText.setFillColor(sf::Color::Green);
		_scoreText.setPosition(950, posY);
		
		posY += 50;

		window.draw(_numberText);
		window.draw(_dateText);
		window.draw(_scoreText);
	}

	window.draw(_titleText);
	window.draw(_backText);
}
