#pragma once
#include "GameObject.h"
#include "Projectile.h"

class Enemy : public GameObject
{
protected:
	sf::Vector2f _speed;
	float _frame;
	int _facingDirection = 1;
	float _shootCoolDown;
	float _timeSinceLastShot;
	bool _moving;
public:
	Enemy();
	void update(float deltaTime, std::vector<Projectile>& projectiles) override;
	void updateDrawing();
	sf::FloatRect getBounds() const override;
	int pointsValue;
	void shoot(std::vector<Projectile>& projectiles);
	bool remove = false;
};

