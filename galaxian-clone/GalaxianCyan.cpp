#include "GalaxianCyan.h"

//sf::IntRect textureRect(4, 62, 10, 6); // cyan galaxian 1
//sf::IntRect textureRect(21, 61, 10, 7); // cyan galaxian 2
//sf::IntRect textureRect(38, 61, 10, 7); // cyan galaxian 3
//sf::IntRect textureRect(53, 61, 13, 7); // cyan galaxian 4

GalaxianCyan::GalaxianCyan() {
	_texture.loadFromFile("sprites-sheet.png");
	_sprite.setTexture(_texture);
	sf::IntRect textureRect(4, 62, 12, 7);
	_sprite.setTextureRect(textureRect);
	//origen
	_sprite.setOrigin(_sprite.getGlobalBounds().width / 2, _sprite.getGlobalBounds().height);
	//escala
	_sprite.setScale(3, 3);
	//frame
	_frame = 0;

	//_sprite.setPosition(200, 452); // if set on the grid it can't be here
	pointsValue = 30;
}

void GalaxianCyan::updateDrawing() {
	_frame += 0.02;

	if (_frame >= 3) { //3 porq son 3 frames de mi imagen
		_frame = 0;
	}

	//_sprite.setTextureRect({ 4 + int(_frame) * 12, 62, 12, 7 });
	if (_frame < 1) _sprite.setTextureRect({ 4, 61, 12, 8 });
	if (_frame >= 1 && _frame <= 2) _sprite.setTextureRect({ 21, 61, 12, 8 });
	if (_frame >= 2 && _frame <= 3) _sprite.setTextureRect({ 38, 61, 12, 8 });
}

sf::Sprite& GalaxianCyan::getSprite()
{
	return _sprite;
}

const sf::Sprite& GalaxianCyan::getSprite() const
{
	return _sprite;
}