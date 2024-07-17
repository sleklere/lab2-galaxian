#pragma once
#include "GameObject.h"
class PowerUp : public GameObject
{
private:
	sf::Vector2f _speed;
	float _frameDeath;
public:
	PowerUp(sf::Vector2f originPosition);
	bool remove = false;
	void update(float deltaTime, std::vector<Projectile>& projectiles, sf::Vector2f playerPosition) override;
	void updateDrawing() override;
	void updatePowerup(float deltaTime);
	sf::FloatRect getBounds() const override;
	bool _isHitted;
};

