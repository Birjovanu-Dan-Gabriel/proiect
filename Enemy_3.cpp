#include "Enemy_3.h"

#include "Exceptions.h"
const int Enemy_3::DefaultPointCount = 100;
const float Enemy_3::DefaultRadius = 30.f; //Circle
const sf::Color Enemy_3::DefaultColor = sf::Color(255, 0, 0); // Pink
///Constructor
Enemy_3::Enemy_3(float pos_x, float pos_y) {
    try {
        // We check if the position is valid and every enemy that spawns is in a reachable area
        // The pos_y is constant at -100
        if (pos_x < 20 || pos_x > 800) {
            throw InvalidInputException("Enemy position cannot be negative: (" +
                                         std::to_string(pos_x) + ", " +
                                         std::to_string(pos_y) + ")");
        }

        ///Enemy variables initialisation
        this->pointCount = DefaultPointCount;
        this->speed = calculateSpeed(this->pointCount);
        this->hpMax = this->pointCount;
        this->hp = this->hpMax;
        this->damage = 10;
        this->points = this->pointCount;

        this->Enemy_3::initShape(); ///initialise shape
        this->shape.setPosition(pos_x, pos_y); ///set spawn position

    } catch (const MyException& e) {
        std::cerr << "Error creating Enemy_3: " << e.what() << std::endl;
        throw; // Rethrows the exception to be managed in superior levels
    }

}

///shape initialisation
void Enemy_3::initShape() {
        this->shape.setPointCount(DefaultPointCount);
        this->shape.setRadius(DefaultRadius);
        this->shape.setFillColor(DefaultColor);
}

///update function
void Enemy_3::update() {
    ///doesn't move on the x axis
    ///moves on the y axis by this->speed
    this->shape.move(0.f, this->speed);
}


///render function
void Enemy_3::render(sf::RenderTarget* target) const {
    // if the target is null this means that an error has occurred
    if (target == nullptr)
        throw InvalidInputException("Render target is null.");

    target->draw(this->shape); // draws the enemy
}

///Static function initialisation
float Enemy_3 ::calculateSpeed(int pointCount) {
    //pointCount must be always positive

    if (pointCount <= 0)
        throw InvalidInputException("Point count must be positive.");
    return static_cast<float>(pointCount) / 60.0f; //calculate and return speed
}