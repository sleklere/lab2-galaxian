#pragma once
#include <SFML\Graphics.hpp>
#include "Globals.h"
#include "Projectile.h"

class Player : public sf::Drawable
{
private:
	sf::Sprite _sprite;
	sf::Texture _texture;
	sf::Vector2f _speed;
	float _shootCoolDown;
	float _timeSinceLastShot;

public:
	Player();
	void update(float deltaTime, std::vector<Projectile>& projectiles);
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	void shoot(std::vector<Projectile>& projectiles);
	sf::Vector2f getCoordinates();
};