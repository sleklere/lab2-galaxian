#pragma once
#include <SFML/Graphics.hpp>
class Collisionable
{
public:
	virtual sf::FloatRect getBounds() const;
	bool isCollision(Collisionable& obj) const;
};

