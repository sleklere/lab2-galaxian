#include "Projectile.h"

Projectile::Projectile(const int direction)
{
	_texture.loadFromFile("sprites-sheet.png");
	_sprite.setTexture(_texture);
    sf::IntRect textureRect(65, 39, 1, 4); // white projectile
    _sprite.setTextureRect(textureRect);
	_direction = direction;
	_isFire = false;
	remove = false;
	//_speed = { 0,0 };


    //sf::IntRect textureRect(73, 39, 1, 4); // yellow projectile

    //sf::IntRect textureRect(18, 38, 6, 12); // flag
}

void Projectile::update()
{
	if (_isFire) {
		_sprite.move(0, _speed * _direction);
	}

	if (_sprite.getPosition().y < 0 || _sprite.getPosition().y > W_HEIGHT) {
		remove = true;
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

void Projectile::fire(sf::Vector2f coords, float speed)
{
	_sprite.setPosition(coords);
	_speed = speed;
	_isFire = true;
}

void Projectile::impact()
{
	_sprite.setPosition({ -100, -100 });
}
