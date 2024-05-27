#include "Collisionable.h"

bool Collisionable::isCollision(Collisionable& obj) const
{
	return getBounds().intersects(obj.getBounds());
}
//sf::FloatRect Collisionable::getBounds()
//{
//
//}