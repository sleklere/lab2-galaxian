#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include "Globals.h"
#include "Player.h"
#include "Projectile.h"
#include "GalaxianRed.h"
#include "GalaxianCyan.h"
#include "GalaxianPink.h"
#include "GalaxianCommander.h"
#include "Grid.h"

class Game
{
private:
    Player player;
    GalaxianCyan galaxianCyan;
    GalaxianRed galaxianRed1;
    GalaxianRed galaxianRed2;
    GalaxianPink galaxianPink;
    GalaxianCommander galaxianCommander;
    Grid enemiesGrid;
    std::vector<Projectile> playerProjectiles;
    std::vector<Projectile> enemyProjectiles;
    sf::Clock clock;
    sf::Font font;
    sf::Text livesText;
    sf::Text pointsText;
    int points;
public:
	Game();
	void update(sf::RenderWindow& window, float deltaTime);
};

