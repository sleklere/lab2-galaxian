#include "GalaxianCommander.h"

GalaxianCommander::GalaxianCommander() {
	_texture = std::make_unique<sf::Texture>();
	_texture->loadFromFile("sprites-sheet.png");
	_sprite.setTexture(*_texture);
	sf::IntRect textureRect(29, 39, 14, 12);
	_sprite.setTextureRect(textureRect);
	_sprite.setOrigin(_sprite.getGlobalBounds().width / 2, _sprite.getGlobalBounds().height);
	_sprite.setScale(3, 3);

	pointsValue = 60;
	_isHitted = false;
	_frameDeath = 0;
}

void GalaxianCommander::updateDrawing()
{
	if (_isHitted) {
		_frameDeath += 0.02f;

		if (_frameDeath >= 0.26f) {
			this->remove = true;
		}

		if (_frameDeath < 0.1f) _sprite.setTextureRect({ 3, 79, 19, 16 });
		if (_frameDeath >= 0.1f && _frameDeath <= 0.2f) _sprite.setTextureRect({ 29, 79, 19, 16 });
		if (_frameDeath >= 0.2f && _frameDeath <= 0.26f) _sprite.setTextureRect({ 51, 79, 24, 16 });
	}
}
