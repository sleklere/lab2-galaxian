#pragma once
#include <SFML\Graphics.hpp>
#include "Globals.h"
#include "Projectile.h"
#include "Collisionable.h"

class Player : public Collisionable, sf::Drawable
{
private:
	sf::Sprite _sprite;
	sf::Texture _texture;
	sf::Vector2f _speed;
	float _shootCoolDown;
	float _timeSinceLastShot;
	int _facingDirection = -1;
	int _lives = 3;
	float _frame;

public:
	Player();
	int getLives();
	void setLives(int numLives);
	void update(float deltaTime, std::vector<Projectile>& projectiles);
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	void shoot(std::vector<Projectile>& projectiles);
	sf::FloatRect getBounds() const override;
	bool _isHitted;
	//sf::Vector2f getCoordinates();
};