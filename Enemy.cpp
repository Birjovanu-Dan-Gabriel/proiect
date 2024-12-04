#include "Enemy.h"

const int& Enemy::getPoints() const {
    return this->points;
}

const int& Enemy::getDamage() const {
    return this->damage;
}

sf::FloatRect Enemy::getBounds() const {
    return this->shape.getGlobalBounds();
}