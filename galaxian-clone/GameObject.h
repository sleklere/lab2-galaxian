#pragma once
#include <SFML\Graphics.hpp>
#include "Globals.h"
#include "Collisionable.h"

class GameObject : public Collisionable, public sf::Drawable
{
protected:
	sf::Sprite _sprite;
	sf::Texture _texture;
public:
	virtual void update() = 0;
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};

