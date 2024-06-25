#pragma once
#include <SFML/Graphics.hpp>
#include "Globals.h"
#include "Collisionable.h"
#include "Projectile.h"

class GameObject : public Collisionable, public sf::Drawable
{
protected:
	sf::Sprite _sprite;
	std::unique_ptr<sf::Texture> _texture; // se declara el puntero que eventualmente va a apuntar a la textura
public:
	virtual void update(float deltaTime, std::vector<Projectile>& projectiles, sf::Vector2f playerPosition = sf::Vector2f()) = 0;
	virtual void updateDrawing() = 0;
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	sf::Sprite& getSprite();
	const sf::Sprite& getSprite() const;
};

