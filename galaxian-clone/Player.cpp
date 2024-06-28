#include "Player.h"
#include "Projectile.h"
#include <iostream>

Player::Player()
{
	_texture.loadFromFile("sprites-sheet.png");
	_sprite.setTexture(_texture);
    _fixedProjectileSprite.setTexture(_texture);
    sf::IntRect textureRect(3, 35, 12, 15); // player ship
    sf::IntRect projectileTextureRect(73, 39, 1, 4);
    _sprite.setTextureRect(textureRect);
    _fixedProjectileSprite.setTextureRect(projectileTextureRect);
    _sprite.setOrigin(_sprite.getGlobalBounds().width / 2, _sprite.getGlobalBounds().height);
    _sprite.setScale(2.f, 2.f);
    _fixedProjectileSprite.setScale(2.f, 2.f);
    _sprite.setPosition(static_cast<float>(W_WIDTH) / 2, W_HEIGHT - 20);
    _speed = { MOVEMENT_SPEED, MOVEMENT_SPEED };
    _timeSinceLastShot = 0.f;
    _shootCoolDown = PLAYER_SHOOT_COOLDOWN;
    _frame = 0;
    _isHitted = false;
}

void Player::update(float deltaTime, std::vector<Projectile>& projectiles)
{   
    _speed = { 0, 0 };

    if (!_isHitted) { //si fue impactado por misil enemigo no se puede mover mientras animacion
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            _speed.x = -MOVEMENT_SPEED;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            _speed.x = MOVEMENT_SPEED;
        }

        if (_timeSinceLastShot < _shootCoolDown) {
            _timeSinceLastShot += deltaTime;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)
            && _timeSinceLastShot >= _shootCoolDown) {
            shoot(projectiles);
        }

        if (!_isHitted) {
            _sprite.move(_speed);
            _fixedProjectileSprite.setPosition(_sprite.getPosition().x, _sprite.getGlobalBounds().top - _fixedProjectileSprite.getGlobalBounds().height);
            _fixedProjectileSprite.move(0.f, 1.f);
        }
    }

    // dont allow player to go out of the screen
    if ((_sprite.getGlobalBounds().left * 2.f) < 0) {
        std::cout << "OUT OF WINDOW (LEFT)" << std::endl;
        _sprite.setPosition(_sprite.getOrigin().x * 2.f, _sprite.getPosition().y);
    }
    if (_sprite.getGlobalBounds().top * 2.f < 0) {
        _sprite.setPosition(_sprite.getPosition().x, _sprite.getOrigin().y * 2.f);
    }

    if (_sprite.getGlobalBounds().left + _sprite.getGlobalBounds().width > W_WIDTH) {
        std::cout << "OUT OF WINDOW (RIGHT)" << std::endl;
        _sprite.setPosition(W_WIDTH - _sprite.getOrigin().x * 2.f, _sprite.getPosition().y);
    }
    if (_sprite.getGlobalBounds().top + _sprite.getGlobalBounds().height > W_HEIGHT) {
        _sprite.setPosition(_sprite.getPosition().x, W_HEIGHT - (_sprite.getGlobalBounds().height - _sprite.getOrigin().y * 2.f));
    }

    if (_frame == 0) {
        _sprite.setTextureRect({ 3, 35, 12, 15 });
    }

    //animacion si es golpeado por enemigo
    if (_isHitted) {
        _frame += 0.01f;

        if (_frame >= 0.6f) {
            this->resetPosition();
        }

        if (_frame < 0.1f) _sprite.setTextureRect({ 3, 79, 19, 16 });
        if (_frame >= 0.1f && _frame <= 0.2f) _sprite.setTextureRect({ 29, 79, 19, 16 });
        if (_frame >= 0.2f && _frame <= 0.3f) _sprite.setTextureRect({ 51, 79, 24, 16 });
    }
}

void Player::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(_sprite, states);
    if (_timeSinceLastShot >= _shootCoolDown && !_isHitted) {
        target.draw(_fixedProjectileSprite, states);
    }
}

void Player::shoot(std::vector<Projectile>& projectiles)
{
    Projectile projectile(_facingDirection, true);

    sf::Vector2f currentPos = _sprite.getPosition();

    currentPos.x = _sprite.getPosition().x;
    currentPos.y = _sprite.getGlobalBounds().top - _fixedProjectileSprite.getGlobalBounds().height;

    projectile.fire(currentPos, PROJECTILE_SPEED_PLAYER);

    projectiles.push_back(std::move(projectile));

    _timeSinceLastShot = 0.f;
}

sf::FloatRect Player::getBounds() const
{
    return _sprite.getGlobalBounds();
}

void Player::resetPosition()
{
    _frame = 0;
    _isHitted = false;
    _sprite.setPosition(W_WIDTH / 2, W_HEIGHT - 20);
}


void Player::setLives(int numLives)
{
    if (numLives >= 0)
    {
        _lives = numLives;
    }
}

int Player::getLives() const
{
    return _lives;
}

sf::Vector2f Player::getPosition()
{
    return _sprite.getPosition();
}