#include "Projectile.h"

Projectile::Projectile(float startX, float startY, float speed, float directionX, float directionY) {
    _texture.loadFromFile("");
    _sprite.setTexture(_texture);
    _sprite.setOrigin(_sprite.getGlobalBounds().width / 2, 0);
    _sprite.setPosition(startX, startY);
    _direction.x = directionX;
    _direction.y = directionY;
}

void Projectile::update()
{

}

void Projectile::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(_sprite, states);
}