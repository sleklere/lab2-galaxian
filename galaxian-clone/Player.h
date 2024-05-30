#pragma once
#include <SFML\Graphics.hpp>
#include "Globals.h"

class Player : public sf::Drawable
{
private:
	sf::Sprite _sprite;
	sf::Texture _texture;
	sf::Vector2f _speed;
	//std::vector<Projectile> _projectiles; // Container for projectiles
public:
	Player();
	void update();
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	//void shoot();
	sf::Vector2f getCoordinates();
};