#include "Game.h"
#include "FilesManager.h"
#include "Score.h"
#include "Menu.h"

Game::Game() : enemiesGrid(3, 6)
{
	font.loadFromFile("ARCADE_I.ttf");
	pointsText.setFont(font);
	highScoreText.setFont(font);
	highScoreText.setPosition(W_WIDTH / 2.f, 10.f);
	score.setPlayerName("testPlayer");
	pointsText.setFillColor(sf::Color::Red);
	highScoreText.setFillColor(sf::Color::Red);
	generalTexture.loadFromFile("sprites-sheet.png");

	float livesPadding = 10.f;

	for (int i = 0; i < 3; i++) {
		lifeSprites[i].setTexture(generalTexture);
		sf::IntRect textureRect(3, 35, 12, 15); // player ship
		lifeSprites[i].setTextureRect(textureRect);
		lifeSprites[i].setScale(2.f, 2.f);
		lifeSprites[i].setPosition(static_cast<float>(i) * 40.f + livesPadding, W_HEIGHT - lifeSprites[i].getGlobalBounds().height - livesPadding);

	}

	backgroundTexture.loadFromFile("background.png");

	float scaleY = static_cast<float>(W_HEIGHT) / backgroundTexture.getSize().y;

	backgroundSprite1.setTexture(backgroundTexture);
	backgroundSprite2.setTexture(backgroundTexture);

	// el segundo fondo va justo abajo del primero
	backgroundSprite1.setPosition(0, 0);
	backgroundSprite2.setPosition(0, -static_cast<float>(backgroundTexture.getSize().y) * scaleY); //static_cast<float> previene error de tipos sin signo

	backgroundSpeed = 100.f;

	time = 0; //////////
}

void Game::update(sf::RenderWindow& window, float deltaTime, Menu& menu, FilesManager<Score> scoresFile, int highScore, GameOver& gameOver)
{

	backgroundSprite1.move(0, backgroundSpeed * deltaTime);
	backgroundSprite2.move(0, backgroundSpeed * deltaTime);

	// se 'envuelven' los fondos para que el scroll sea infinito
	if (backgroundSprite1.getPosition().y >= backgroundTexture.getSize().y * backgroundSprite1.getScale().y) {
		backgroundSprite1.setPosition(0, backgroundSprite2.getPosition().y - backgroundTexture.getSize().y * backgroundSprite1.getScale().y);
	}
	if (backgroundSprite2.getPosition().y >= backgroundTexture.getSize().y * backgroundSprite2.getScale().y) {
		backgroundSprite2.setPosition(0, backgroundSprite1.getPosition().y - backgroundTexture.getSize().y * backgroundSprite2.getScale().y);
	}

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

	////textos
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

		// pantalla game over
		gameOver.setFinalScore(score.getPoints());
		gameOver.setActive(true);

		//reset
		this->reset();

	}

	/* ---------------------------------------------------------------------- */
	//                                 DRAW                                   //
	/* ---------------------------------------------------------------------- */

	// importante que se dibuje primero el fondo
	window.draw(backgroundSprite1);
	window.draw(backgroundSprite2);

	for (const auto& projectile : enemyProjectiles) {
		window.draw(projectile, sf::RenderStates::Default);
	}

	for (const auto& projectile : playerProjectiles) {
		window.draw(projectile, sf::RenderStates::Default);
	}

	enemiesGrid.display(window, sf::RenderStates::Default);
	player.draw(window, sf::RenderStates::Default);
	for (int i = 0; i < player.getLives(); i++) {
		window.draw(lifeSprites[i]);
	}
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
