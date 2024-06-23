#include "Grid.h"
#include <vector>
#include <iostream>
#include "GalaxianCommander.h"
#include "GalaxianRed.h"
#include "GalaxianPink.h"
#include "GalaxianCyan.h"

//Grid::Grid(int rows, int cols) {
//    xDirection = 1.f;
//    _rows = rows;
//    _cols = cols;
//
//    _cells.resize(rows * cols);
//    for (int i = 0; i < rows; i++) {
//        for (int j = 0; j < cols; j++) {
//            // config enemy on grid 
//            float xSpacing = 100.f;
//            float ySpacing = 60.f;
//            float spriteWidth = 12.f * 3.f; // 3 is the scale
//            float spriteHeight = 7.f * 3.f; // 3 is the scale
//            float gridMarginLeft = (W_WIDTH - (spriteWidth + xSpacing) * cols) / 2;
//
//            std::cout << "EACH CELL SPRITE" << std::endl;
//            _cells[i * cols + j].getSprite().setPosition(gridMarginLeft + spriteWidth + (j + 1) * xSpacing, 100.f + spriteHeight + (i + 1) * ySpacing); // global scale variable
//        }
//    }
//}

Grid::Grid(int rows, int cols) {
	xDirection = 1.f;
	_rows = 5;
	_cols = 10;

	_cells.resize(_rows);
	for (int i = 0; i < _rows; i++) {
		_cells[i].resize(_cols);
		for (int j = 0; j < _cols; j++) {
			float xSpacing = 50.f;
			float ySpacing = 60.f;
			float spriteWidth = 12.f * 3.f; // 3 is the scale
			float spriteHeight = 7.f * 3.f; // 3 is the scale
			float gridMarginLeft = (W_WIDTH - (spriteWidth + xSpacing) * _cols) / 2;

			// Create enemies based on row
			if (i == 0 && (j == 2 || j == 5)) {
				_cells[i][j] = std::make_unique<GalaxianCommander>();
			}
			else if (i == 1 && (j != 0 && j != 9)) {
				_cells[i][j] = std::make_unique<GalaxianRed>();
			}
			else if (i == 2 && (j != 0 && j != 1 && j != 8 && j != 9)) {
				_cells[i][j] = std::make_unique<GalaxianPink>();
			}
			else if (i == 3 || i == 4) {
				_cells[i][j] = std::make_unique<GalaxianCyan>();
			}

			std::cout << "EACH CELL SPRITE" << std::endl;

			if (_cells[i][j] != nullptr) {
				_cells[i][j]->getSprite().setPosition(gridMarginLeft + spriteWidth + (j + 1) * xSpacing, 100.f + spriteHeight + (i + 1) * ySpacing);
			}
		}
	}
}

void Grid::display(sf::RenderTarget& target, sf::RenderStates states) const {
	//for (const auto& enemy : _cells) {
	//    target.draw(enemy, states);
	//}
	for (const auto& row : _cells) {
		for (const auto& enemy : row) {
			if (enemy != nullptr) {
				target.draw(enemy->getSprite(), states);
			}
		}
	}

}

void Grid::moveLaterally()
{
	//float rightEdgeSpace = W_WIDTH - (_cells[_cells.size() - 1].getSprite().getGlobalBounds().left + 12.f * 3.f);
	//float leftEdgeSpace = _cells[0].getSprite().getGlobalBounds().left;


	//if (rightEdgeSpace < 150.f) {
	//    xDirection = -1.f;
	//}
	//else if (leftEdgeSpace < 150.f) {
	//    xDirection = 1.f;
	//}

	//for (auto& enemy : _cells) {
	//    sf::Vector2f direction;
	//    direction.x = 2.f * xDirection;
	//    direction.y = 0;

	//    enemy.getSprite().move(direction);
	//}
}


//std::vector<GalaxianCyan>& Grid::getCells() {
	//return _cells;
//}
std::vector<std::vector<std::unique_ptr<Enemy>>>& Grid::getCells() {
	return _cells;
}
