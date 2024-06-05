#include "Grid.h"
#include <vector>

Grid::Grid(int rows, int cols) {
    _rows = rows;
    _cols = cols;

    _cells.resize(rows, std::vector<GalaxianCyan>(cols));
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            // config enemy on grid 
            _cells[i][j].getSprite().setPosition(j * 12 * 3 + 40, i * 7 * 3 + 18); // global scale variable
        }
    }
}

//void Grid::display(sf::RenderTarget& target, sf::RenderStates states) const {
//    //for (const auto& row : _cells) {
//    //    for (const auto& cell : row) {
//    //        target.draw(cell.getSprite(), states);
//    //    }
//    //}
//    for (int i = 0; i < _rows; i++) {
//        for (int j = 0; j < _cols; j++) {
//            GalaxianCyan obj = _cells[i][j];
//            target.draw(_cells[i][j].getSprite(), states);
//        }
//    }
//}


// TODO: RETURN REFERENCE NOT COPY
std::vector<std::vector<GalaxianCyan>> Grid::getCells() {
    return _cells;
}