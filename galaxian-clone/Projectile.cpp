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
	_texture.loadFromFile("sprite-spaceship.png");
	_sprite.setTexture(_texture);
	//_speed = { 0,0 };
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
