//
// Created by birjo on 11/29/2024.
//

#ifndef BULLET_H
#define BULLET_H

#include<SFML/Graphics.hpp>


class Bullet
{
private:

    sf::Sprite shape;

    sf::Vector2f direction;
    float movementSpeed;

public:

    Bullet(const sf::Texture* texture, float pos_x, float pos_y, float dir_x, float dir_y, float movement_speed);
    virtual ~Bullet();
    //Accessor
    sf::FloatRect getBounds() const;

    void update();
    void render(sf::RenderTarget* target) const;
};




#endif //BULLET_H
