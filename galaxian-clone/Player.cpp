#include "Player.h"
#include "Projectile.h"

Player::Player()
{
	_texture.loadFromFile("sprite-spaceship.png");
	_sprite.setTexture(_texture);
    _sprite.setOrigin(_sprite.getGlobalBounds().width / 2, _sprite.getGlobalBounds().height);
    _sprite.setPosition(W_WIDTH / 2, W_HEIGHT);
    _speed = { MOVEMENT_SPEED, MOVEMENT_SPEED };
}

void Player::update()
{   
    _speed = { 0, 0 };

    /*if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
        _speed.y = -MOVEMENT_SPEED;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
        _speed.y = MOVEMENT_SPEED;
    }*/
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        _speed.x = -MOVEMENT_SPEED;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        _speed.x = MOVEMENT_SPEED;
    }

    // Disparar
  /*  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
        shoot();
    }*/

    _sprite.move(_speed);
    /*float angle = std::atan2(_speed.y, _speed.x) * 180 / 3.14159265;
    _sprite.setRotation(angle + 90);*/

    if (_speed.x < 0)
    {
        _sprite.setScale(-1, 1);
    }
    else if (_speed.x > 0) {
        _sprite.setScale(1, 1);
    }

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
}

void Player::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(_sprite, states);
}

//void Player::shoot()
//{
//    // Create a new projectile and add it to the list
//    Projectile newProjectile(_sprite.getPosition().x + _sprite.getGlobalBounds().width / 2,
//        _sprite.getPosition().y,
//        PROJECTILE_SPEED, 0.0f, -1.0f);
//    _projectiles.push_back(newProjectile);
//}

sf::Vector2f Player::getCoordinates()
{
    return _sprite.getPosition();
}