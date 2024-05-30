#pragma once
#include "GameObject.h"

class Enemy : public GameObject
{
protected:
	sf::Vector2f _speed;
	float _frame;
public:
	virtual void update() = 0;
};

