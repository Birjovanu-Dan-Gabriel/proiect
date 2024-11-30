//
// Created by birjo on 11/29/2024.
//

#ifndef PLAYER_H
#define PLAYER_H

#include<SFML/Graphics.hpp>


class Player
{
private:
    sf::Sprite sprite;
    sf::Texture texture;

    float movementSpeed;

    float attackCooldown;
    float attackCooldownMax;

    int hp;
    int hpMax;


    void initTexture();
    void initSprite();

public:
    Player();
    virtual ~Player();

    const sf::Vector2f& getPos() const;

    sf::FloatRect getBounds() const;
    const int& getHp() const;
    const int& getHpMax() const;


    void setPosition( sf::Vector2f pos);
    void setPosition( float x,  float y);
    void setHp( int hp);
    void loseHp( int value);


    void move( float dirX,  float dirY);

    bool canAttack();

    void updateAttack();
    void update();
    void render(sf::RenderTarget& target) const;
};




#endif //PLAYER_H
