#include "Game.h"
#include "FilesManager.h"
#include "Score.h"

Game::Game() : enemiesGrid(3, 6)
{
	font.loadFromFile("ARCADE_I.ttf");
	livesText.setFont(font);
	livesText.setPosition(0, 30);
	pointsText.setFont(font);
	score.setPlayerName("testPlayer");
}

void Game::update(sf::RenderWindow& window, float deltaTime, FilesManager<Score> scoresFile)
{
	player.update(deltaTime, playerProjectiles);

	enemiesGrid.moveLaterally();

	for (auto& enemy : enemiesGrid.getCells())
	{
		//std::cout << "Enemies update for loop" << std::endl;
		enemy.update(deltaTime, enemyProjectiles);

		for (Projectile& projectile : enemyProjectiles)
		{
			//std::cout << "Enemy projectiles update for loop" << std::endl;

			projectile.update();

			if (projectile.remove)
			{
				continue;
			}

			if (projectile.isCollision(player))
			{
				player.setLives(player.getLives() - 1);
				player._isHitted = true;
				projectile.remove = true;
			}

		}

	}



	for (auto& projectile : playerProjectiles) {
		projectile.update();

		if (projectile.remove) {
			continue;
		}

		for (auto& enemy : enemiesGrid.getCells())
		{
			if (projectile.isCollision(enemy))
			{
				score.addPoints(enemy.pointsValue);
				projectile.remove = true;
				enemy.remove = true;
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

	std::vector<GalaxianCyan>& enemySprites = enemiesGrid.getCells();

	enemySprites.erase(
		std::remove_if(enemySprites.begin(), enemySprites.end(),
			[](const GalaxianCyan& e) { return e.remove; }),
		enemySprites.end());

	////textos
	livesText.setString(std::to_string(player.getLives()));
	pointsText.setString(std::to_string(score.getPoints()));

	// end game
	if (player.getLives() == 0) {
		std::cout << "juego finalizado" << std::endl;

		scoresFile.write(score);

		// TODO: volver al menu
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
}
