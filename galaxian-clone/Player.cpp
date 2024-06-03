#include "Player.h"
#include "Projectile.h"

Player::Player()
{
	_texture.loadFromFile("sprites-sheet.png");
	_sprite.setTexture(_texture);
    sf::IntRect textureRect(3, 35, 12, 15); // player ship
    _sprite.setTextureRect(textureRect);
    //_sprite.setScale(2.f, 2.f);
    _sprite.setOrigin(_sprite.getGlobalBounds().width / 2, _sprite.getGlobalBounds().height);
    _sprite.setPosition(W_WIDTH / 2, W_HEIGHT);
    _speed = { MOVEMENT_SPEED, MOVEMENT_SPEED };
    _timeSinceLastShot = 0.f;
    _shootCoolDown = SHOOT_COOLDOWN;
    _frame = 0;
    _isHitted = false;
}

void Player::update(float deltaTime, std::vector<Projectile>& projectiles)
{   
    _speed = { 0, 0 };

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
        _speed.y = -MOVEMENT_SPEED;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
        _speed.y = MOVEMENT_SPEED;
    }
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

    _sprite.move(_speed);
    /*float angle = std::atan2(_speed.y, _speed.x) * 180 / 3.14159265;
    _sprite.setRotation(angle + 90);*/


    // dont allow player to go out of the screen
    if (_sprite.getGlobalBounds().left < 0) {
        _sprite.setPosition(_sprite.getOrigin().x, _sprite.getPosition().y);
    }
    if (_sprite.getGlobalBounds().top < 0) {
        _sprite.setPosition(_sprite.getPosition().x, _sprite.getOrigin().y);
    }

    if (_sprite.getGlobalBounds().left + _sprite.getGlobalBounds().width > W_WIDTH) {
        _sprite.setPosition(W_WIDTH - _sprite.getOrigin().x, _sprite.getPosition().y);
    }
    if (_sprite.getGlobalBounds().top + _sprite.getGlobalBounds().height > W_HEIGHT) {
        _sprite.setPosition(_sprite.getPosition().x, W_HEIGHT - (_sprite.getGlobalBounds().height - _sprite.getOrigin().y));
    }

    if (_frame == 0) {
        _sprite.setTextureRect({ 3, 35, 12, 15 });
    }

    //animacion si es golpeado por enemigo
    if (_isHitted) {
        _frame += 0.02;

        if (_frame >= 3) {
            _frame = 0;
            _isHitted = false;
            _sprite.setPosition(W_WIDTH / 2, W_HEIGHT);
        }

        if (_frame < 1) _sprite.setTextureRect({ 3, 79, 19, 16 });
        if (_frame >= 1 && _frame <= 2) _sprite.setTextureRect({ 29, 79, 19, 16 });
        if (_frame >= 2 && _frame <= 3) _sprite.setTextureRect({ 51, 79, 24, 16 });
    }
}

void Player::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(_sprite, states);
}

void Player::shoot(std::vector<Projectile>& projectiles)
{
    Projectile projectile(_facingDirection);

    projectile.fire(_sprite.getPosition());

    projectiles.push_back(projectile);

    _timeSinceLastShot = 0.f;
}

sf::FloatRect Player::getBounds() const
{
    return _sprite.getGlobalBounds();
}

void Player::setLives(int numLives)
{
    if (numLives >= 0)
    {
        _lives = numLives;
    }
}

int Player::getLives()
{
    return _lives;
}

//sf::Vector2f Player::getCoordinates()
//{
//    return _sprite.getPosition();
//}