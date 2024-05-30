#include "GameObject.h"

void GameObject::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(_sprite, states);
}
