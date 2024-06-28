#include "Round.h"

Round::Round() : enemiesGrid(3, 6)
{
	time = 0;
}

void Round::update(sf::RenderWindow& window, float deltaTime, Player player, Score score)
{
	player.update(deltaTime, playerProjectiles);

	enemiesGrid.moveLaterally();

	int amountEnemies = enemiesGrid.getAmountEnemies();
	int cont = 0;
	int randomNum = rand() % amountEnemies;
	int randomTime = 2 + rand() % 6;
	time += deltaTime;

	for (auto& row : enemiesGrid.getCells()) {

		for (auto& enemy : row)
		{
			if (enemy != nullptr) {
				enemy->update(deltaTime, enemyProjectiles, player.getPosition());
				enemy->updateDrawing();

				//si un enemigo colisiona con el jugador
				if (enemy->isCollision(player) && !player._isHitted)
				{
					player.setLives(player.getLives() - 1);
					player._isHitted = true;
					enemy->_isHitted = true;
				}

				//enemigo al azar ataca
				if (cont == randomNum && time >= randomTime) {
					enemy->_attacking = true;
					time = 0;
				}
				cont++;
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
					enemy->_isHitted = true;
					//enemy->remove = true;
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
	/*for (int i = 0; i < player.getLives(); i++) {
		window.draw(lifeSprites[i]);
	}*/
}
