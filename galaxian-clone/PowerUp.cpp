#include "PowerUp.h"

PowerUp::PowerUp(sf::Vector2f originPosition)
{
	_texture = std::make_unique<sf::Texture>();
	_texture->loadFromFile("power-up.jpg"); 
	_sprite.setTexture(*_texture); 

	_speed = { 0, 2 };
	_sprite.setPosition(originPosition.x, originPosition.y - 45);
	_frameDeath = 0;
	_isHitted = false;
}

void PowerUp::update(float deltaTime, std::vector<Projectile>& projectiles, sf::Vector2f playerPosition)
{
}

void PowerUp::updateDrawing()
{
}

void PowerUp::updatePowerup(float deltaTime)
{
	_sprite.move(_speed);

	if (_sprite.getPosition().y > W_HEIGHT) {
		remove = true;
	}

	if (_isHitted) {
		_frameDeath += 0.02f;

		if (_frameDeath >= 0.26f) {
			this->remove = true;
		}

		_texture->loadFromFile("sprites-sheet.png");
		_sprite.setTexture(*_texture);
		_sprite.setScale(2.5, 2.5);

		if (_frameDeath < 0.1f) _sprite.setTextureRect({ 3, 79, 19, 16 });
		if (_frameDeath >= 0.1f && _frameDeath <= 0.2f) _sprite.setTextureRect({ 29, 79, 19, 16 });
		if (_frameDeath >= 0.2f && _frameDeath <= 0.26f) _sprite.setTextureRect({ 51, 79, 24, 16 });
	}
}

sf::FloatRect PowerUp::getBounds() const
{
	return _sprite.getGlobalBounds();
}