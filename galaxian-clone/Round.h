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
#include "FilesManager.h"
#include "Score.h"
#include "Menu.h"
#include "GameOver.h"
#include "Screen.h"

class Round
{
private:
    Grid enemiesGrid;
    std::vector<Projectile> playerProjectiles;
    std::vector<Projectile> enemyProjectiles;
    sf::Clock clock;
    float time;
public:
    Round();
    void update(sf::RenderWindow& window, float deltaTime, Player player, Score score);
};

