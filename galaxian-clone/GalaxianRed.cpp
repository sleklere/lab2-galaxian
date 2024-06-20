#include "GalaxianRed.h"

GalaxianRed::GalaxianRed() {
	_texture = std::make_unique<sf::Texture>();
	_texture->loadFromFile("sprites-sheet.png");
	_sprite.setTexture(*_texture);
	sf::IntRect textureRect(4, 53, 12, 7);
	_sprite.setTextureRect(textureRect);
	_sprite.setOrigin(_sprite.getGlobalBounds().width / 2, _sprite.getGlobalBounds().height);
	_sprite.setScale(3, 3);
	_frame = 0;
	
	_sprite.setPosition(200, 388);
	pointsValue = 50;
}

void GalaxianRed::updateDrawing() {
	_frame += 0.02;

	if (_frame >= 3) { //3 porq son 3 frames de mi imagen
		_frame = 0;
	}

	//_sprite.setTextureRect({ 4 + int(_frame) * 12, 53, 12, 7 });
	if (_frame < 1) _sprite.setTextureRect({ 4, 52, 12, 8 });
	if (_frame >= 1 && _frame <= 2) _sprite.setTextureRect({ 21, 52, 12, 8 });
	if (_frame >= 2 && _frame <= 3) _sprite.setTextureRect({ 38, 52, 12, 8 });
}