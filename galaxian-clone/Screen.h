#pragma once
#include <SFML/Graphics.hpp>
#include "Globals.h"

class Screen
{
private:
	sf::Texture backgroundTexture;
	sf::Sprite backgroundSprite1;
	sf::Sprite backgroundSprite2;
	float backgroundSpeed;
public:
	Screen();
	void update(sf::RenderWindow& window, float deltaTime);
};

