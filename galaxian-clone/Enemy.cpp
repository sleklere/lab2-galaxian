#include "Enemy.h"

void Enemy::update() {
	// 
}

sf::FloatRect Enemy::getBounds() const
{
	return _sprite.getGlobalBounds();
}
