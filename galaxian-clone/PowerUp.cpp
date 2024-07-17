#include "PowerUp.h"

PowerUp::PowerUp(sf::Vector2f originPosition)
{
	_duration = 10.f;
	_speed = { 0, 1 };
	_sprite.setPosition(originPosition);
	_frameDeath = 0;
}

void PowerUp::updateDrawing()
{
}

void PowerUp::updatePowerup(float deltaTime)
{
	_sprite.move(_speed);

	if (_sprite.getPosition().y < 0 || _sprite.getPosition().y > W_HEIGHT) {
		remove = true;
	}
}

sf::FloatRect PowerUp::getBounds() const
{
	return _sprite.getGlobalBounds();
}