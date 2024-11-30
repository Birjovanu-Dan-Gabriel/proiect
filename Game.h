//
// Created by birjo on 11/29/2024.
//

#ifndef GAME_H
#define GAME_H





#include<map>
#include<string>
#include <iostream>
#include <sstream>
#include"Player.h"
#include"Bullet.h"
#include"Enemy.h"

class Game
{
private:

    sf::RenderWindow* window;

    std::map<std::string, sf::Texture*> textures;
    std::vector<Bullet*> bullets;

    sf::Font font;
    sf::Text pointText;

    sf::Text gameOverText;

    sf::Texture worldBackgroundTex;
    sf::Sprite worldBackground;


    unsigned points;


    Player* player;

    sf::RectangleShape playerHpBar;
    sf::RectangleShape playerHpBarBack;

    float spawnTimer;
    float spawnTimerMax;
    std::vector<Enemy*> enemies;

    void initWindow();
    void initTextures();
    void initGUI();
    void initWorld();
    void initSystems();

    void initPlayer();
    void initEnemies();

public:
    Game();
    virtual ~Game();

    void run();

    void updatePollEvents() const;
    void updateInput();
    void updateGUI();
    void updateWorld();
    void updateCollision() const;
    void updateBullets();
    void updateEnemies();
    void updateCombat();
    void update();

    void renderGUI() const;
    void renderWorld() const;
    void render();
};




#endif //GAME_H
