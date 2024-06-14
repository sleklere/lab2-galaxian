#include "Grid.h"
#include <vector>
#include <iostream>

Grid::Grid(int rows, int cols) {
    _rows = rows;
    _cols = cols;

    //_cells.resize(rows, std::vector<GalaxianCyan>(cols));
    _cells.resize(rows * cols);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            // config enemy on grid 
            float xSpacing = 100.f;
            float ySpacing = 120.f;
            float spriteWidth = 12.f * 2.f; // 3 is the scale
            float spriteHeight = 7.f * 2.f; // 3 is the scale

            //for (int k = 0; k < _cells.size(); k++) {
            std::cout << "EACH CELL SPRITE" << std::endl;
            _cells[i * cols + j].getSprite().setPosition(spriteWidth + (j + 1) * xSpacing, spriteHeight + (i + 1) * ySpacing); // global scale variable
            //}
        }
    }
}

void Grid::display(sf::RenderTarget& target, sf::RenderStates states) const {
    //for (const auto& row : _cells) {
    //    for (const auto& cell : row) {
    //        target.draw(cell.getSprite(), states);
    //    }
    //}
    /*for (int i = 0; i < _rows; i++) {
        for (int j = 0; j < _cols; j++) {
            GalaxianCyan obj = _cells[i][j];
            target.draw(_cells[i][j].getSprite(), states);
        }
    }*/
    for (const auto& enemy : _cells) {
        target.draw(enemy, states);
    }
}


// TODO: RETURN REFERENCE NOT COPY
std::vector<GalaxianCyan>& Grid::getCells() {
    return _cells;
}