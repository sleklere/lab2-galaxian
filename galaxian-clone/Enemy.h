#pragma once
#include "GameObject.h"

class Enemy : public GameObject
{
private:
	sf::Vector2f _speed;
public:
	virtual void update() const = 0;
};

