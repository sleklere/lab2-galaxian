#include "Enemy.h"
#include "Projectile.h"
#include <iostream>
#include <random>

Enemy::Enemy() {
	_timeSinceLastShot = 0.f;

	std::random_device rd;
	std::mt19937 gen(rd());

	std::uniform_real_distribution<float> dis(0.0f, 20.0f);

	_shootCoolDown = dis(gen);
}		

void Enemy::update(float deltaTime, std::vector<Projectile>& projectiles) {
	if (_timeSinceLastShot < _shootCoolDown) {
		_timeSinceLastShot += deltaTime;
	}

	if (_timeSinceLastShot >= _shootCoolDown) {
		shoot(projectiles);
	}
}

void Enemy::updateDrawing()
{
	//
}

sf::FloatRect Enemy::getBounds() const
{
	return _sprite.getGlobalBounds();
}

void Enemy::shoot(std::vector<Projectile>& projectiles)
{
	Projectile projectile(_facingDirection);

	projectile.fire(_sprite.getPosition(), PROJECTILE_SPEED_ENEMY);

	projectiles.push_back(projectile);

	_timeSinceLastShot = 0.f;
}
