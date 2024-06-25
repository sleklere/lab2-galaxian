#pragma once
#include "GameObject.h"
#include "Projectile.h"
#include "Collisionable.h"

class Enemy : public GameObject
{
protected:
	sf::Vector2f _speed;
	float _frame;
	float _frameDeath;
	int _facingDirection = 1;
	float _shootCoolDown;
	float _timeSinceLastShot;
	float _moving;
public:
	Enemy();
	void update(float deltaTime, std::vector<Projectile>& projectiles, sf::Vector2f playerPosition) override;
	sf::FloatRect getBounds() const override;
	int pointsValue;
	void shoot(std::vector<Projectile>& projectiles);
	bool remove = false;

	bool _isHitted;
	bool _attacking;
	sf::Vector2f playerPos;
	bool _evenColumn;
};

