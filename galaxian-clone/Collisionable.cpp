#include "Collisionable.h"

sf::FloatRect Collisionable::getBounds() const
{
	return sf::FloatRect();
}

bool Collisionable::isCollision(Collisionable& obj) const
{
	return getBounds().intersects(obj.getBounds());
}
//sf::FloatRect Collisionable::getBounds()
//{
//
//}