#pragma once
#include "GameObject.h"
#include "Projectile.h"
#include "Collisionable.h"

enum class EnemyType {
	Cyan,
	Pink,
	Red,
	Commander
};

class Enemy : public GameObject
{
protected:
	sf::Vector2f _speed;
	float _frameDeath;
	int _facingDirection = 1;
	float _shootCoolDown;
	float _timeSinceLastShot;
	float _moving;
	sf::Vector2f _enemyPosition; //pos del enemigo antes de _attacking sea true
public:
	float _frame;
	int pointsValue;
	bool remove = false;
	bool _isHitted;
	bool _attacking;
	sf::Vector2f playerPos;
	bool _evenColumn;
	EnemyType type;
	
	Enemy();
	void update(float deltaTime, std::vector<Projectile>& projectiles, sf::Vector2f playerPosition) override;
	sf::FloatRect getBounds() const override;
	void shoot(std::vector<Projectile>& projectiles);
	EnemyType getType();
	sf::Vector2f getPosition();
};

