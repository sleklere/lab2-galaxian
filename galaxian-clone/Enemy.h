#pragma once
#include "GameObject.h"

class Enemy : public GameObject
{
protected:
	sf::Vector2f _speed;
	float _frame;
	int _facingDirection = 1;
public:
	void update() override;
	sf::FloatRect getBounds() const override;
	int pointsValue;
	bool remove = false;
};

