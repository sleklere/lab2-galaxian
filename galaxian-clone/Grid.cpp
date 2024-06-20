#include "Grid.h"
#include <vector>
#include <iostream>

Grid::Grid(int rows, int cols) {
    _rows = rows;
    _cols = cols;

    _cells.resize(rows * cols);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            // config enemy on grid 
            float xSpacing = 100.f;
            float ySpacing = 120.f;
            float spriteWidth = 12.f * 2.f; // 3 is the scale
            float spriteHeight = 7.f * 2.f; // 3 is the scale

            std::cout << "EACH CELL SPRITE" << std::endl;
            _cells[i * cols + j].getSprite().setPosition(spriteWidth + (j + 1) * xSpacing, spriteHeight + (i + 1) * ySpacing); // global scale variable
        }
    }
}

void Grid::display(sf::RenderTarget& target, sf::RenderStates states) const {
    for (const auto& enemy : _cells) {
        target.draw(enemy, states);
    }
}


std::vector<GalaxianCyan>& Grid::getCells() {
    return _cells;
}