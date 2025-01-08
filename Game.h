#ifndef GAME_H
#define GAME_H


#include <vector>
#include <memory>
#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Bullet.h"
#include "Enemy.h"
#include "Enemy_1.h"
#include "Enemy_2.h"
#include "Enemy_3.h"
#include "ResourceManager.h"

class Observer {
public:
    virtual ~Observer() = default;
    virtual void update(int points, int level) = 0;
};

class Subject {
public:
    virtual ~Subject() = default;
    virtual void addObserver(Observer* observer) = 0;
    virtual void removeObserver(Observer* observer) = 0;
    virtual void notifyObservers() = 0;
};
class ScoreObserver : public Observer {
public:
    void update(int points, int level) override;
};

class EnemyFactory {
public:
    virtual std::unique_ptr<Enemy> createEnemy(float posX, float posY) = 0;
    virtual ~EnemyFactory() = default;
};

class Enemy1Factory : public EnemyFactory {
public:
    std::unique_ptr<Enemy> createEnemy(float posX, float posY) override {
        return std::make_unique<Enemy_1>(posX, posY);
    }
};

class Enemy2Factory : public EnemyFactory {
public:
    std::unique_ptr<Enemy> createEnemy(float posX, float posY) override {
        return std::make_unique<Enemy_2>(posX, posY);
    }
};

class Enemy3Factory : public EnemyFactory {
public:
    std::unique_ptr<Enemy> createEnemy(float posX, float posY) override {
        return std::make_unique<Enemy_3>(posX, posY);
    }
};

class Game : public Subject {
private:
    // Private attributes
    sf::RenderWindow* window;
    std::vector<std::unique_ptr<Bullet>> bullets;
    std::vector<std::unique_ptr<Enemy>> enemies;
    std::vector<Observer*> observers;

    sf::Font font;
    sf::Text pointText;
    sf::Text gameOverText;
    sf::RectangleShape playerHpBar;
    sf::RectangleShape playerHpBarBack;

    sf::Texture worldBackgroundTex;
    sf::Sprite worldBackground;

    ResourceManager<sf::Texture> textureManager;
    ResourceManager<sf::Font> fontManager;

    sf::Text lvlText;
    int lvl;

    float spawnTimer;
    float spawnTimerMax;

    int points;
    Player* player;

    static Game* instance; // Declaration for Singleton instance

    std::vector<std::unique_ptr<EnemyFactory>> enemyFactories;
    int currentFactoryIndex;

    // Private functions
    Game(); // Constructor is private for Singleton
    void initWindow();
    void initTextures();
    void initGUI();
    void initWorld();
    void initEnemies();
    void initNextLvlGUI();
    void initLvl();

public:
    // Deleted copy constructor and assignment operator for Singleton
    Game(const Game&) = delete;
    Game& operator=(const Game&) = delete;

    // Destructor
    ~Game() override;

    // Singleton accessor
    static Game& getInstance();

    // Public functions
    void run();
    void updatePollEvents() const;
    void updateInput();
    void updateGUI();
    void updateCollision() const;
    void updateBullets();
    void updateEnemies();
    void updateCombat();
    void update();
    void initEnemyFactories();
    void  renderGUI() const;
    void renderWorld() const;
    void render() const;

    // Observer pattern methods
    void addObserver(Observer* observer) override;
    void removeObserver(Observer* observer) override;
    void notifyObservers() override;

    // Getter methods for observers
    int getPoints() const { return points; }
    int getLevel() const { return lvl; }

};

#endif
