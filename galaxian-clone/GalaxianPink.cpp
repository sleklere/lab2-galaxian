#include "GalaxianPink.h"

GalaxianPink::GalaxianPink() {
	_texture = std::make_unique<sf::Texture>();
	_texture->loadFromFile("sprites-sheet.png");
	_sprite.setTexture(*_texture);
	sf::IntRect textureRect(4, 71, 12, 7);
	_sprite.setTextureRect(textureRect);
	_sprite.setOrigin(_sprite.getGlobalBounds().width / 2, _sprite.getGlobalBounds().height);
	_sprite.setScale(3, 3);
	_frame = 0;
	
	pointsValue = 40;
	_isHitted = false;
	_frameDeath = 0;
}

void GalaxianPink::updateDrawing() {
	_frame += 0.02;
	
	if (!_isHitted) {
		if (_frame >= 3) {
			_frame = 0;
		}

		if (_frame < 1) _sprite.setTextureRect({ 4, 71, 12, 7 });
		if (_frame >= 1 && _frame <= 2) _sprite.setTextureRect({ 21, 71, 12, 7 });
		if (_frame >= 2 && _frame <= 3) _sprite.setTextureRect({ 38, 71, 12, 7 });
	}

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