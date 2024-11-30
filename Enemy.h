//
// Created by birjo on 11/29/2024.
//

#ifndef ENEMY_H
#define ENEMY_H




#include<SFML/Graphics.hpp>




class Enemy
{
private:
    int pointCount{};
    sf::CircleShape shape;
    int type{};
    float speed{};
    int hp{};
    int hpMax{};
    int damage{};
    int points{};

    void initShape();

public:
    Enemy(float pos_x, float pos_y);
    virtual ~Enemy();

    sf::FloatRect getBounds() const;
    const int& getPoints() const;
    const int& getDamage() const;

    void update();
    void render(sf::RenderTarget* target) const;
};



#endif //ENEMY_H
