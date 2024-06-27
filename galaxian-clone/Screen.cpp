#include "Screen.h"

Screen::Screen()
{
	backgroundTexture.loadFromFile("background.png");

	float scaleY = static_cast<float>(W_HEIGHT) / backgroundTexture.getSize().y;

	backgroundSprite1.setTexture(backgroundTexture);
	backgroundSprite2.setTexture(backgroundTexture);

	// el segundo fondo va justo abajo del primero
	backgroundSprite1.setPosition(0, 0);
	backgroundSprite2.setPosition(0, -static_cast<float>(backgroundTexture.getSize().y) * scaleY); //static_cast<float> previene error de tipos sin signo

	backgroundSpeed = 100.f;
}

void Screen::update(sf::RenderWindow& window, float deltaTime)
{
	backgroundSprite1.move(0, backgroundSpeed * deltaTime);
	backgroundSprite2.move(0, backgroundSpeed * deltaTime);

	// se 'envuelven' los fondos para que el scroll sea infinito
	if (backgroundSprite1.getPosition().y >= backgroundTexture.getSize().y * backgroundSprite1.getScale().y) {
		backgroundSprite1.setPosition(0, backgroundSprite2.getPosition().y - backgroundTexture.getSize().y * backgroundSprite1.getScale().y);
	}
	if (backgroundSprite2.getPosition().y >= backgroundTexture.getSize().y * backgroundSprite2.getScale().y) {
		backgroundSprite2.setPosition(0, backgroundSprite1.getPosition().y - backgroundTexture.getSize().y * backgroundSprite2.getScale().y);
	}

	window.draw(backgroundSprite1);
	window.draw(backgroundSprite2);
}
