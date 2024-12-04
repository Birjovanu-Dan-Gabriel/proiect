#ifndef ENEMY_1_H
#define ENEMY_1_H

#include "Enemy.h"

class Enemy_1 : public Enemy {

private:
    ///static variables initialisations
    static const int DefaultPointCount;  //point count
    static const float DefaultRadius; //radius
    static const sf::Color DefaultColor; // color

public:
    Enemy_1(float pos_x, float pos_y); //constructor
    void initShape() override; //shape initialisation
    void update() override; // update
    void render(sf::RenderTarget* target) const override; //rendering

    ///Static function initialisation
    static float calculateSpeed(int pointCount); // calculates the speed
};

#endif
