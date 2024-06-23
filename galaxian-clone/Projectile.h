#pragma once
#include <SFML/Graphics.hpp>
#include "Globals.h"
#include "Collisionable.h"

class Projectile : public sf::Drawable, public Collisionable
{
private:
	sf::Texture _texture;
	sf::Sprite _sprite;
	float _speed;
	bool _isFire;
	int _direction;
public:
	bool remove = false;
	Projectile(int direction);
	void update();
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	sf::FloatRect getBounds() const override;
	void fire(sf::Vector2f coords, float speed);
	void impact();
};

