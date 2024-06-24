#include "Game.h"
#include "FilesManager.h"
#include "Score.h"
#include "Menu.h"

Game::Game() : enemiesGrid(3, 6)
{
	font.loadFromFile("ARCADE_I.ttf");
	livesText.setFont(font);
	livesText.setPosition(0, 30);
	pointsText.setFont(font);
	highScoreText.setFont(font);
	highScoreText.setPosition(W_WIDTH / 2.f, 10.f);
	score.setPlayerName("testPlayer");
}

void Game::update(sf::RenderWindow& window, float deltaTime, Menu& menu, FilesManager<Score> scoresFile, int highScore)
{
	player.update(deltaTime, playerProjectiles);

	enemiesGrid.moveLaterally();

	for (auto& row : enemiesGrid.getCells()) {

		for (auto& enemy : row)
		{
			if (enemy != nullptr) {
				enemy->update(deltaTime, enemyProjectiles);
			}

			for (Projectile& projectile : enemyProjectiles)
			{
				projectile.update();

				if (projectile.remove)
				{
					continue;
				}

				if (projectile.isCollision(player) && !player._isHitted)
				{
					player.setLives(player.getLives() - 1);
					player._isHitted = true;
					projectile.remove = true;
				}

			}
		}

	}



	for (auto& projectile : playerProjectiles) {
		projectile.update();

		if (projectile.remove) {
			continue;
		}

		for (auto& row : enemiesGrid.getCells())
		{
			for (auto& enemy : row) {

				if (projectile.isCollision(*enemy))
				{
					score.addPoints(enemy->pointsValue);
					projectile.remove = true;
					enemy->remove = true;
				}
			}

		}
	}

	//Borrar enemigos y proyectiles
	playerProjectiles.erase(
		std::remove_if(playerProjectiles.begin(), playerProjectiles.end(),
			[](const Projectile& p) { return p.remove; }),
		playerProjectiles.end());
	enemyProjectiles.erase(
		std::remove_if(enemyProjectiles.begin(), enemyProjectiles.end(),
			[](const Projectile& p) { return p.remove; }),
		enemyProjectiles.end());

	for (auto& row : enemiesGrid.getCells()) {
		row.erase(
			std::remove_if(row.begin(), row.end(),
				[](const std::unique_ptr<Enemy>& e) { return e == nullptr || e->remove; }),
			row.end());
	}

	////textos
	livesText.setString(std::to_string(player.getLives()));
	pointsText.setString(std::to_string(score.getPoints()));

	if (score.getPoints() > highScore) {
		highScoreText.setString(std::to_string(score.getPoints()));
	}
	else {
		highScoreText.setString(std::to_string(highScore));
	}

	highScoreText.setPosition(W_WIDTH / 2.f - highScoreText.getGlobalBounds().width, 10.f);

	// end game
	if (player.getLives() == 0) {
		std::cout << "juego finalizado" << std::endl;
		std::cout << "score points: " << score.getPoints() << std::endl;

		scoresFile.write(score);
		std::cout << "Menu active: " << menu.getActive() << std::endl;
		menu.setActive(true);

		// TODO: PANTALLA GAME OVER
		this->reset();
	}

	/* ---------------------------------------------------------------------- */
	//                                 DRAW                                   //
	/* ---------------------------------------------------------------------- */

	for (const auto& projectile : enemyProjectiles) {
		window.draw(projectile, sf::RenderStates::Default);
	}

	for (const auto& projectile : playerProjectiles) {
		window.draw(projectile, sf::RenderStates::Default);
	}

	enemiesGrid.display(window, sf::RenderStates::Default);
	player.draw(window, sf::RenderStates::Default);
	window.draw(livesText);
	window.draw(pointsText);
	window.draw(highScoreText);
}

void Game::reset()
{
	playerProjectiles.clear();
	enemyProjectiles.clear();
	player.setLives(3);
	player.resetPosition();
	score.setPoints(0);
	enemiesGrid = Grid(3, 6);
}
