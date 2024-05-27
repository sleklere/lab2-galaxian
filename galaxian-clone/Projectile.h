#pragma once
#include <SFML/Graphics.hpp>
#include "Globals.h"

class Projectile : public sf::Drawable
{
private:
	sf::Texture _texture;
	sf::Sprite _sprite;
	sf::Vector2f _direction;
public:
	Projectile(float startX, float startY, float speed, float directionX, float directionY);
	void update();
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};

