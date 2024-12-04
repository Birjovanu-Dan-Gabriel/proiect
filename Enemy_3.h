//
// Created by birjo on 12/1/2024.
//

#ifndef ENEMY_3_H
#define ENEMY_3_H



#include "Enemy.h"

class Enemy_3 : public Enemy {
private:
    ///static variables initialisations
    static const int DefaultPointCount;  //point count
    static const float DefaultRadius; //radius
    static const sf::Color DefaultColor; // color

public:
    Enemy_3(float pos_x, float pos_y); //constructor
    void initShape() override; //shape initialisation
    void update() override; // update
    void render(sf::RenderTarget* target) const override; //rendering

    ///Static function initialisation
    static float calculateSpeed(int pointCount); // calculates the speed
};


#endif //ENEMY_3_H
