#include "Projectile.h"
#include <iostream>

Projectile::Projectile(const int direction, bool isPlayer)
{
	_texture = std::make_unique<sf::Texture>();
	_texture->loadFromFile("sprites-sheet.png");
	_sprite.setTexture(*_texture);

	if (isPlayer) {
		sf::IntRect textureRect(73, 39, 1, 4); // yellow projectile
		_sprite.setTextureRect(textureRect);
	}
	else {
		sf::IntRect textureRect(65, 39, 1, 4); // white projectile
		_sprite.setTextureRect(textureRect);
	}

	_direction = direction;
	_isFire = false;
	remove = false;
	_sprite.setScale(2.f, 2.f);
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

