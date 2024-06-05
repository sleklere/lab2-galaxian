#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Enemy.h"
#include "GalaxianCyan.h"

class Grid {
private:
    int _rows, _cols;
    std::vector<std::vector<GalaxianCyan>> _cells;

public:
    Grid(int rows, int cols);
    //void display(sf::RenderTarget& target, sf::RenderStates states) const override;
    std::vector<std::vector<GalaxianCyan>> getCells();
};


