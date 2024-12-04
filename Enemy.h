#ifndef ENEMY_H
#define ENEMY_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <exception>

// Enemy base class
class Enemy {
public:
    // Virtual constructor

    virtual ~Enemy() = default; // Destructor virtual

    // Pure virtual functions
    //This means that the derived classed are forced to implement this
    virtual void initShape() = 0;
    virtual void update() = 0;
    virtual void render(sf::RenderTarget* target) const = 0;

    // Access functions
    const int& getPoints() const;
    const int& getDamage() const;
    sf::FloatRect getBounds() const;

protected:
    sf::CircleShape shape;
    int pointCount = 0;
    float speed =0;
    int hpMax =0;
    int hp =0;
    int damage = 0;
    int points = 0;
};

#endif
