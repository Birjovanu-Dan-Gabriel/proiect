#include "Bullet.h"
#include <iostream>
#include "Exceptions.h"



Bullet::Bullet(const sf::Texture* texture, const float pos_x, const float pos_y, const float dir_x, const float dir_y, const float movement_speed) {
    try {
        //possible errors
        if (texture == nullptr) {
            throw InvalidInputException("Texture cannot be null.");
        }
        if (movement_speed <= 0.f) {
            throw InvalidInputException("Movement speed must be positive.");
        }
        if (dir_x == 0.f && dir_y == 0.f) {
            throw InvalidInputException("Direction cannot be (0, 0).");
        }

        this->shape.setTexture(*texture);
        this->shape.setPosition(pos_x, pos_y);
        this->direction.x = dir_x;
        this->direction.y = dir_y;
        this->movementSpeed = movement_speed;

    } catch (const MyException& e) {
        std::cerr << "Error initializing Bullet: " << e.what() << std::endl;
        throw; // Rethrow the exception to handle it at a higher level
    }
}


Bullet::~Bullet()
= default;

//get bounds function
sf::FloatRect Bullet::getBounds() const {
    return this->shape.getGlobalBounds();
}

void Bullet::update()
{
    this->shape.move(this->movementSpeed * this->direction);
}

void Bullet::render(sf::RenderTarget* target) const {
    try {
        if (target == nullptr) {
            throw InvalidInputException("Render target cannot be null.");
        }
        target->draw(this->shape);
    } catch (const MyException& e) {
        std::cerr << "Error rendering Bullet: " << e.what() << std::endl;
        throw;
    }
}

