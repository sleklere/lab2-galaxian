#pragma once
#include "Enemy.h"

class GalaxianCyan : public Enemy
{
public:
	GalaxianCyan();
	void updateDrawing() override;
	sf::Sprite& getSprite();
	const sf::Sprite& getSprite() const;
};

