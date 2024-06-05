#include "GalaxianPink.h"

//sf::IntRect textureRect(4, 71, 10, 6); // pink galaxian 1
//sf::IntRect textureRect(21, 70, 10, 7); // pink galaxian 2
//sf::IntRect textureRect(38, 70, 10, 7); // pink galaxian 3
//sf::IntRect textureRect(53, 70, 13, 7); // pink galaxian 4

GalaxianPink::GalaxianPink() {
	_texture.loadFromFile("sprites-sheet.png");
	_sprite.setTexture(_texture);
	sf::IntRect textureRect(4, 71, 12, 7);
	_sprite.setTextureRect(textureRect);
	//origen
	_sprite.setOrigin(_sprite.getGlobalBounds().width / 2, _sprite.getGlobalBounds().height);
	//escala
	_sprite.setScale(3, 3);
	//frame
	_frame = 0;
	
	_sprite.setPosition(200, 420);
	pointsValue = 40;
}

void GalaxianPink::updateDrawing() {
	_frame += 0.02;
		 
	if (_frame >= 3) { //3 porq mi animacion de correr tiene 4 frames solo, osea 4 imgs distintas
		_frame = 0;
	}

	/*_sprite.setTextureRect({ 4 + int(_frame) * 12, 71, 12, 7 });*/
	if(_frame < 1) _sprite.setTextureRect({ 4, 71, 12, 7 });
	if (_frame >= 1 && _frame <= 2) _sprite.setTextureRect({ 21, 71, 12, 7 });
	if (_frame >= 2 && _frame <= 3) _sprite.setTextureRect({ 38, 71, 12, 7 });
}