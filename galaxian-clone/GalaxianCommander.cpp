#include "GalaxianCommander.h"

GalaxianCommander::GalaxianCommander() {
	_texture = std::make_unique<sf::Texture>();
	_texture->loadFromFile("sprites-sheet.png");
	_sprite.setTexture(*_texture);
	sf::IntRect textureRect(29, 39, 14, 12);
	_sprite.setTextureRect(textureRect);
	//origen
	_sprite.setOrigin(_sprite.getGlobalBounds().width / 2, _sprite.getGlobalBounds().height);
	//escala
	_sprite.setScale(3, 3);

	_sprite.setPosition(400, 100);
	pointsValue = 60;
}