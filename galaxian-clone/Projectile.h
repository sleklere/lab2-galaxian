#pragma once
#include <SFML/Graphics.hpp>
#include "Globals.h"
#include "Collisionable.h"

class Projectile : public sf::Drawable, public Collisionable
{
private:
	sf::Texture _texture;
	sf::Sprite _sprite;
	sf::Vector2f _speed;
	bool _isFire;
	//sf::Vector2f _direction;
public:
	Projectile();
	void update();
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	sf::FloatRect getBounds() const override;
	void fire(sf::Vector2f coords);
	void impact();
};

