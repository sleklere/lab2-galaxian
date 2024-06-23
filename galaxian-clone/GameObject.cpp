#include "GameObject.h"

void GameObject::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(_sprite, states);
}

sf::Sprite& GameObject::getSprite()
{
	return _sprite;
}

const sf::Sprite& GameObject::getSprite() const
{
	return _sprite;
}