#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Enemy.h"
#include "GalaxianCyan.h"

class Grid {
private:
    int _rows, _cols;
    std::vector<std::vector<std::unique_ptr<Enemy>>> _cells;
    int _amountEnemies;
public:
    float xDirection;
    Grid(int rows, int cols);
    void display(sf::RenderTarget& target, sf::RenderStates states) const;
    void moveLaterally();
    std::vector<std::vector<std::unique_ptr<Enemy>>>& getCells();
    int getAmountEnemies();
};


