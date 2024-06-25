#include "Enemy.h"
#include "Projectile.h"
#include <iostream>
#include <random>

Enemy::Enemy() {
	_timeSinceLastShot = 0.f;

	std::random_device rd;
	std::mt19937 gen(rd());

	std::uniform_real_distribution<float> dis(0.0f, MAX_ENEMY_SHOOT_COOLDOWN);

	//_shootCoolDown = dis(gen);
	_shootCoolDown = 0.8;

	_attacking = false;
	_moving = 0;
}		

void Enemy::update(float deltaTime, std::vector<Projectile>& projectiles, sf::Vector2f playerPosition) {

	if (!_attacking) {
		playerPos = playerPosition; //tomo ultima posicion del player antes de atacar
		//_sprite.setPosition(_sprite.getPosition().x, _sprite.getPosition().y + 4);
	}

	if (_attacking) {
		if (_timeSinceLastShot < _shootCoolDown) {
			_timeSinceLastShot += deltaTime;
		}

		if (_timeSinceLastShot >= _shootCoolDown) {
			shoot(projectiles);
		}

		_moving += 0.05;
		//hago la curva
		if (_sprite.getPosition().x > W_WIDTH / 2) {
			if (_moving <= 1) _sprite.move(-3, -3);		
			if (_moving > 1 && _moving <= 2) _sprite.move(-3, 0);
			if (_moving > 2 && _moving <= 3) _sprite.move(-3, 3);
		} else {
			if (_moving <= 1) _sprite.move(3, -3);
			if (_moving > 1 && _moving <= 2) _sprite.move(3, 0);
			if (_moving > 2 && _moving <= 3) _sprite.move(3, 3);
		}
		//voy hasta la ultima posicion que tengo del player
		if (_moving > 3) {
			playerPos.y += 20;

			if (playerPos.x > _sprite.getPosition().x) _sprite.move(3, 0);
			if (playerPos.x < _sprite.getPosition().x) _sprite.move(-3, 0);
			if (playerPos.y > _sprite.getPosition().y) _sprite.move(0, 3);
			if (playerPos.y < _sprite.getPosition().y) _sprite.move(0, -3);

			if (_sprite.getPosition().y > W_HEIGHT) {
				remove = true;
			}
		}			
	}	
}

sf::FloatRect Enemy::getBounds() const
{
	return _sprite.getGlobalBounds();
}

void Enemy::shoot(std::vector<Projectile>& projectiles)
{
	Projectile projectile(_facingDirection);

	projectile.fire(_sprite.getPosition(), PROJECTILE_SPEED_ENEMY);

	projectiles.push_back(std::move(projectile));

	_timeSinceLastShot = 0.f;
}
