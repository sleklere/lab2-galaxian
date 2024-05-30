#include "Projectile.h"

//Projectile::Projectile(float startX, float startY, float speed, float directionX, float directionY) {
//    _texture.loadFromFile("");
//    _sprite.setTexture(_texture);
//    _sprite.setOrigin(_sprite.getGlobalBounds().width / 2, 0);
//    _sprite.setPosition(startX, startY);
//    _direction.x = directionX;
//    _direction.y = directionY;
//}
//
//void Projectile::update()
//{
//
//}
//
//void Projectile::draw(sf::RenderTarget& target, sf::RenderStates states) const
//{
//    target.draw(_sprite, states);
//}
Projectile::Projectile()
{
	_texture.loadFromFile("sprites-sheet.png");
	_sprite.setTexture(_texture);
    sf::IntRect textureRect(65, 39, 1, 4); // white projectile
    _sprite.setTextureRect(textureRect);
	//_speed = { 0,0 };


    //sf::IntRect textureRect(73, 39, 1, 4); // yellow projectile

    //sf::IntRect textureRect(18, 38, 6, 12); // flag

    //sf::IntRect textureRect(4, 53, 10, 6); // red galaxian 1
    //sf::IntRect textureRect(21, 52, 10, 7); // red galaxian 2
    //sf::IntRect textureRect(38, 52, 10, 7); // red galaxian 3
    //sf::IntRect textureRect(53, 52, 13, 7); // red galaxian 4    

    //sf::IntRect textureRect(4, 62, 10, 6); // cyan galaxian 1
    //sf::IntRect textureRect(21, 61, 10, 7); // cyan galaxian 2
    //sf::IntRect textureRect(38, 61, 10, 7); // cyan galaxian 3
    //sf::IntRect textureRect(53, 61, 13, 7); // cyan galaxian 4

    //sf::IntRect textureRect(4, 71, 10, 6); // pink galaxian 1
    //sf::IntRect textureRect(21, 70, 10, 7); // pink galaxian 2
    //sf::IntRect textureRect(38, 70, 10, 7); // pink galaxian 3
    //sf::IntRect textureRect(53, 70, 13, 7); // pink galaxian 4
}

void Projectile::update()
{
	if (_isFire) {
		_sprite.move(0, -5);
	}
}

void Projectile::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(_sprite, states);
}

sf::FloatRect Projectile::getBounds() const
{
	return _sprite.getGlobalBounds();
}

void Projectile::fire(sf::Vector2f coords)
{
	_sprite.setPosition(coords);
	_speed = { 0, 5 };
	_isFire = true;
}

void Projectile::impact()
{
	_sprite.setPosition({ -100, -100 });
}
