#include "Bullet.h"


Bullet::Bullet(const sf::Texture * texture, const float pos_x, const float pos_y, const float dir_x, const float dir_y, const float movement_speed)
{
    this->shape.setTexture(*texture);

    this->shape.setPosition(pos_x, pos_y);
    this->direction.x = dir_x;
    this->direction.y = dir_y;
    this->movementSpeed = movement_speed;
}

Bullet::~Bullet()
= default;

sf::FloatRect Bullet::getBounds() const {
    return this->shape.getGlobalBounds();
}

void Bullet::update()
{

    this->shape.move(this->movementSpeed * this->direction);
}

void Bullet::render(sf::RenderTarget * target) const {
    target->draw(this->shape);
}
