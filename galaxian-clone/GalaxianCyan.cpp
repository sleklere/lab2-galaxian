#include "GalaxianCyan.h"

GalaxianCyan::GalaxianCyan() {
	_texture = std::make_unique<sf::Texture>(); // alocar la nueva textura, haciendo que sea propiedad del puntero _texture
	_texture->loadFromFile("sprites-sheet.png"); // '->' desreferencia el puntero para acceder al obj
	_sprite.setTexture(*_texture); // desreferenciar el smart ptr para acceder a la textura
	sf::IntRect textureRect(4, 62, 12, 7);
	_sprite.setTextureRect(textureRect);
	_sprite.setOrigin(_sprite.getGlobalBounds().width / 2, _sprite.getGlobalBounds().height);
	_sprite.setScale(3, 3);
	_frame = 0;

	pointsValue = 30;
	_isHitted = false;
	_frameDeath = 0;
}

void GalaxianCyan::updateDrawing() {
	_frame += 0.02;

	if (!_isHitted) {
		if (_frame >= 3) { //3 porq son 3 frames de mi imagen
			_frame = 0;
		}

		if (_frame < 1) _sprite.setTextureRect({ 4, 61, 12, 8 });
		if (_frame >= 1 && _frame <= 2) _sprite.setTextureRect({ 21, 61, 12, 8 });
		if (_frame >= 2 && _frame <= 3) _sprite.setTextureRect({ 38, 61, 12, 8 });
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