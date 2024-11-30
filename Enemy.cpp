#include "Enemy.h"



void Enemy::initShape()
{
    this->shape.setRadius(5.f * this->pointCount);
    this->shape.setPointCount(this->pointCount);
    this->shape.setFillColor(sf::Color(rand() % 255 + 1, rand() % 255 + 1, rand() % 255 + 1, 255));
}

Enemy::Enemy(const float pos_x, const float pos_y)
{
    this->pointCount = rand() % 8 + 3; //min = 3 max = 10
    this->type = 0;
    this->speed = static_cast<float>(this->pointCount / 3.0);
    this->hpMax = (this->pointCount);
    this->hp = this->hpMax;
    this->damage = this->pointCount;
    this->points = this->pointCount;

    this->initShape();

    this->shape.setPosition(pos_x, pos_y);
}

Enemy::~Enemy()
= default;


sf::FloatRect Enemy::getBounds() const {
    return this->shape.getGlobalBounds();
}

const int& Enemy::getPoints() const
{
    return this->points;
}

const int& Enemy::getDamage() const
{
    return this->damage;
}

void Enemy::update()
{
    this->shape.move(0.f, this->speed);
}

void Enemy::render(sf::RenderTarget* target) const {
    target->draw(this->shape);
}
