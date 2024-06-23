#include "Grid.h"
#include <vector>
#include <iostream>
#include "GalaxianCommander.h"
#include "GalaxianRed.h"
#include "GalaxianPink.h"
#include "GalaxianCyan.h"

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
			if (i == 0 && (j == 3 || j == 6)) {
				_cells[i][j] = std::make_unique<GalaxianCommander>();
			}
			else if (i == 1 && (j != 0 && j != 1 && j != 8 && j != 9)) {
				_cells[i][j] = std::make_unique<GalaxianRed>();
			}
			else if (i == 2 && (j != 0 && j != 9)) {
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
	for (const auto& row : _cells) {
		for (const auto& enemy : row) {
			if (enemy != nullptr) {
				target.draw(enemy->getSprite(), states);
			}
		}
	}

}

template <typename T>
bool isMatrixEmpty(const std::vector<std::vector<T>>& matrix) {
	if (matrix.empty()) {
		return true;
	}

	for (const auto& row : matrix) {
		if (!row.empty()) {
			return false;
		}
	}

	return true;
}

void Grid::moveLaterally()
{
	if (isMatrixEmpty(_cells)) return;

	float rightEdgeSpace = 200.f;
	float leftEdgeSpace = 200.f;

	// encontrar el menor espacio entre un sprite y el borde izquierdo. lo mismo para el derecho
	for (auto& row : _cells) {
		for (auto& enemy : row) {
			if (enemy == nullptr) continue;
			float spaceRight = W_WIDTH - (enemy->getSprite().getGlobalBounds().left + 12.f * 3.f);
			float spaceLeft = enemy->getSprite().getGlobalBounds().left;

			if (spaceRight < rightEdgeSpace) rightEdgeSpace = spaceRight;

			if (spaceLeft < leftEdgeSpace) leftEdgeSpace = spaceLeft;
		}
	}


	if (rightEdgeSpace < 150.f) {
		xDirection = -1.f;
	}
	else if (leftEdgeSpace < 150.f) {
		xDirection = 1.f;
	}

	for (auto& row : _cells) {
		for (auto& enemy : row) {
			if (enemy == nullptr) continue;

			sf::Vector2f direction;
			direction.x = 2.f * xDirection;
			direction.y = 0;

			enemy->getSprite().move(direction);
		}
	}
}

std::vector<std::vector<std::unique_ptr<Enemy>>>& Grid::getCells() {
	return _cells;
}
