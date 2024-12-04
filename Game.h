
#ifndef GAME_H
#define GAME_H

#include<map>
#include<string>
#include <iostream>
#include <sstream>
#include"Player.h"
#include"Bullet.h"
#include"Enemy.h"
#include"Enemy_1.h"
#include <memory>  // for std::unique_ptr
#include "Enemy_3.h"
#include "Enemy_2.h"
#include "memory"

class Game
{
private:

    sf::RenderWindow* window;
    std::map<std::string, sf::Texture*> textures;
    std::vector<std::unique_ptr<Bullet>> bullets;

    ///font and text definitions
    sf::Font font;
    sf::Text pointText;

    sf::Text gameOverText;
    sf::Text lvlText;

    //background texture definition
    sf::Texture worldBackgroundTex;
    sf::Sprite worldBackground;

    //points
    unsigned points;


    Player* player;

    //GUI - hp bar
    sf::RectangleShape playerHpBar;
    sf::RectangleShape playerHpBarBack;

    float spawnTimer;
    float spawnTimerMax;

    std::vector<std::unique_ptr<Enemy>> enemies;

    int lvl;

    void initWindow(); //initialises the window
    void initTextures(); //init bullet textures
    void initGUI(); //gui
    void initWorld();// init background
    void initSystems();
    void initNextLvlGUI(); // "Lvl x" text
    void initPlayer();
    void initEnemies();
    void initLvl2(); //init next lvl

public:
    Game();
    virtual ~Game();

    void run();

    void updatePollEvents() const;
    void updateInput();
    void updateGUI();
    void updateCollision() const;
    void updateBullets();
    void updateEnemies();
    void updateCombat();
    void update();

    void renderGUI() const;
    void renderWorld() const;
    void render() const;
};




#endif //GAME_H
