#include "Game.h"
#include "FilesManager.h"
#include "Score.h"
#include "Menu.h"
#include "PowerUp.h"
#include "PowerUp.cpp"
#include <vector>

Game::Game() : enemiesGrid(5, 10)
{
	font.loadFromFile("ARCADE_I.ttf");

	pointsText.setFont(font);
	pointsText.setFillColor(sf::Color::Red);

	highScoreText.setFont(font);
	highScoreText.setPosition(W_WIDTH / 2.f, 10.f);
	highScoreText.setFillColor(sf::Color::Red);

	generalTexture.loadFromFile("sprites-sheet.png");

	int livesPosInitial = W_WIDTH - 250;
	float livesPadding = 10.f;
	for (int i = 0; i < 3; i++) {
		lifeSprites[i].setTexture(generalTexture);
		sf::IntRect textureRect(3, 35, 12, 15); // player ship
		lifeSprites[i].setTextureRect(textureRect);
		lifeSprites[i].setScale(2.f, 2.f);
		if (i == 0) {
			lifeSprites[0].setPosition(livesPosInitial, 12.f);
		}
		else {
			lifeSprites[i].setPosition(lifeSprites[0].getPosition().x + static_cast<float>(i) * 40.f, 12.f);
		}
	}

	_roundsText.setFont(font);
	_roundsText.setString("01");
	_roundsText.setPosition(W_WIDTH - (_roundsText.getGlobalBounds().width + 10), 10);
	
	_textureFlag.loadFromFile("sprites-sheet.png");
	_spriteFlag.setTexture(_textureFlag);
	_spriteFlag.setTextureRect(sf::IntRect(18, 37, 8, 14));
	_spriteFlag.setPosition(W_WIDTH - (_roundsText.getGlobalBounds().width + 10) - (_spriteFlag.getGlobalBounds().width + 20), 10);
	_spriteFlag.setScale(2.5, 2.5);

	rounds = 1;

	time = 0; //tiempo para q un enemigo ataque
}

void Game::update(sf::RenderWindow& window, float deltaTime, Menu& menu, FilesManager<Score> scoresFile, int highScore, GameOver& gameOver)
{
	Screen::update(window, deltaTime);

	player.update(deltaTime, playerProjectiles);

	enemiesGrid.moveLaterally();

	int amountEnemies = enemiesGrid.getAmountEnemies();
	int cont = 0;
	int randomNum = amountEnemies ? rand() % amountEnemies : 0;
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

				if (enemy->remove) {
					amountEnemies--;
					enemiesGrid.setAmountEnemies(amountEnemies);
				}
			}


		}

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



	for (auto& projectile : playerProjectiles) {
		projectile.update();

		if (projectile.remove) {
			continue;
		}

		for (auto& row : enemiesGrid.getCells())
		{
			for (auto& enemy : row) {

				if (enemy != nullptr) {
					if (projectile.isCollision(*enemy))
					{
						score.addPoints(enemy->pointsValue);
						projectile.remove = true;
						//no pongo enemy->remove = true, porq lo hago en el updateDrawing de cada enemy cuando _isHitted = true
						enemy->_isHitted = true;

						if (!enemy->_attacking && enemy->getType() == EnemyType::Commander) {
							PowerUp powerUp(enemy->getPosition());
							powerUps.push_back(std::move(powerUp));
						}
					}
				}
			}

		}

		for (PowerUp& powerUpItem : powerUps) {
			if (projectile.isCollision(powerUpItem)) {
				powerUpItem._isHitted = true;
				player.setPowerUp(true);
			}
		}
	}

	for (PowerUp& powerUpItem : powerUps) {
		powerUpItem.updatePowerup(deltaTime);
		if (powerUpItem.isCollision(player)) {
			powerUpItem._isHitted = true;
			player.setPowerUp(true);
		}
	}

	//BORRAR ENEMIGOS Y PROYECTILES
	playerProjectiles.erase(
		std::remove_if(playerProjectiles.begin(), playerProjectiles.end(),
			[](const Projectile& p) { return p.remove; }),
		playerProjectiles.end());

	enemyProjectiles.erase(
		std::remove_if(enemyProjectiles.begin(), enemyProjectiles.end(),
			[](const Projectile& p) { return p.remove; }),
		enemyProjectiles.end());

	powerUps.erase(
		std::remove_if(powerUps.begin(), powerUps.end(),
			[](const PowerUp& i) { return i.remove; }),
		powerUps.end());

	for (auto& row : enemiesGrid.getCells()) {
		row.erase(
			std::remove_if(row.begin(), row.end(),
				[](const std::unique_ptr<Enemy>& e) { return e == nullptr || e->remove; }),
			row.end());
	}

	//ACTUALIZO LOS PUNTOS DEL PLAYER EN PANTALLA
	pointsText.setString(std::to_string(score.getPoints()));

	//VEO SI EL SCORE DEL PLAYER ES MAYOR AÑ HIGHSCORE Y SI ES ASI LO CAMBIO, SINO MANTENGO
	if (score.getPoints() > highScore) {
		highScoreText.setString(std::to_string(score.getPoints()));
	}
	else {
		highScoreText.setString(std::to_string(highScore));
	}
	highScoreText.setPosition(W_WIDTH / 2.f - highScoreText.getGlobalBounds().width, 10.f);


	/* ---------------------------------------------------------------------- */
	//                              NEXT ROUND                                //
	/* ---------------------------------------------------------------------- */
	
	if (enemiesGrid.getAmountEnemies() == 0) {
		enemiesGrid = Grid(5, 10);
		rounds++;

		if (rounds < 10) {
			_roundsText.setString("0" + std::to_string(rounds));
		}
		else {
			_roundsText.setString(std::to_string(rounds));
		}
	}

	/* ---------------------------------------------------------------------- */
	//                                END GAME                                //
	/* ---------------------------------------------------------------------- */
	
	if (player.getLives() == 0) {
		//creo el registro con fecha y score del player
		scoresFile.write(score);

		// GAME OVER SCREEN
		gameOver.setFinalScore(score.getPoints());
		gameOver.setRound(rounds);
		gameOver.setActive(true);

		//RESETEO VALORES
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

	for (const auto& powerUp : powerUps) {
		window.draw(powerUp);
	}

	enemiesGrid.display(window, sf::RenderStates::Default);

	player.draw(window, sf::RenderStates::Default);

	for (int i = 0; i < player.getLives(); i++) {
		window.draw(lifeSprites[i]);
	}

	window.draw(pointsText);
	window.draw(highScoreText);
	window.draw(_spriteFlag);
	window.draw(_roundsText);
}

void Game::reset()
{
	playerProjectiles.clear();
	enemyProjectiles.clear();
	player.setLives(3);
	player.resetPosition();
	score.setPoints(0);
	rounds = 1;
	_roundsText.setString("0" + std::to_string(rounds));
	enemiesGrid = Grid(5, 10);
}
