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
	
	_sprite.setPosition(200, 420);
	pointsValue = 40;
}

void GalaxianPink::updateDrawing() {
	_frame += 0.02;
		 
	if (_frame >= 3) { //3 porq mi animacion de correr tiene 4 frames solo, osea 4 imgs distintas
		_frame = 0;
	}

	if(_frame < 1) _sprite.setTextureRect({ 4, 71, 12, 7 });
	if (_frame >= 1 && _frame <= 2) _sprite.setTextureRect({ 21, 71, 12, 7 });
	if (_frame >= 2 && _frame <= 3) _sprite.setTextureRect({ 38, 71, 12, 7 });
}