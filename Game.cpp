#include "Game.h"
#include <iostream>
#include <map>
#include <sstream>
//adds an observer
void Game::addObserver(Observer* observer) {
    observers.push_back(observer);
}

//removes an observer
void Game::removeObserver(Observer* observer) {
    observers.erase(std::remove(observers.begin(), observers.end(), observer), observers.end());
}

//notifies the observer
void Game::notifyObservers() {
    for (Observer* observer : observers) {
        observer->update(points, lvl);
    }
}


//prints the current score and lvl
void ScoreObserver::update(int points, int level) {
    std::cout << "Score updated: " << points << ", Level: " << level << std::endl;
}


///starts the window
void Game::initWindow()
{
    this->window = new sf::RenderWindow(sf::VideoMode(800, 600), "Idleon", sf::Style::Close | sf::Style::Titlebar | sf::Style::Resize);
    this->window->setFramerateLimit(100); //fps limit = 60
    this->window->setVerticalSyncEnabled(false);//vsync false
}

///initialises bullet textures
void Game::initTextures()
{
    textureManager.loadResource("BULLET", "../assets/bullet.png");
    textureManager.loadResource("BACKGROUND", "../assets/bg.jpg");
}

///initialises GUI
void Game::initGUI()
{
    ///check if font loaded properly
    fontManager.loadResource("MAIN_FONT", "../assets/PixellettersFull.ttf");

    ///point count
    this->pointText.setPosition(700.f, 5.f);
    this->pointText.setFont(*fontManager.getResource("MAIN_FONT"));
    this->pointText.setCharacterSize(30);
    this->pointText.setFillColor(sf::Color::White);
    this->pointText.setString("aaaaaaaaaaaaa");

    ///game over screeen
    this->pointText.setFont(*fontManager.getResource("MAIN_FONT"));
    this->gameOverText.setCharacterSize(60);
    this->gameOverText.setFillColor(sf::Color::Red);
    this->gameOverText.setString("Game Over!");
    this->gameOverText.setPosition(
        this->window->getSize().x / 2.f - this->gameOverText.getGlobalBounds().width / 2.f,
        this->window->getSize().y / 2.f - this->gameOverText.getGlobalBounds().height / 2.f);

    ///player hp bar
    this->playerHpBar.setSize(sf::Vector2f(300.f, 25.f));
    this->playerHpBar.setFillColor(sf::Color::Red);
    this->playerHpBar.setPosition(sf::Vector2f(20.f, 20.f));
    this->playerHpBarBack = this->playerHpBar;
    this->playerHpBarBack.setFillColor(sf::Color(25, 25, 25, 200));
}

//initialises background
void Game::initWorld() {

        textureManager.loadResource("BACKGROUND", "../assets/bg.jpg");
        this->worldBackground.setTexture(*textureManager.getResource("BACKGROUND"));
}

void Game::initNextLvlGUI(){
    this->lvlText.setFont(this->font);
    this->lvlText.setCharacterSize(60);
    this->lvlText.setFillColor(sf::Color::Red);
    this->lvlText.setString("Level " + std::to_string(this->lvl) );
    this->lvlText.setPosition(
        this->window->getSize().x / 2.f - this->lvlText.getGlobalBounds().width / 2.f,
        this->window->getSize().y / 2.f - this->lvlText.getGlobalBounds().height / 2.f);
}

//initialises enemy spawn time
void Game::initEnemies()
{
    this->spawnTimerMax = 50.f;
    this->spawnTimer = this->spawnTimerMax;
}

//starts the next lvl
void Game::initLvl() {
    this-> lvl ++;
    this->initNextLvlGUI();
    enemies.clear();
    currentFactoryIndex = currentFactoryIndex + 1;
    notifyObservers(); // Notify observers when level changes
}

//constructor (now private for Singleton)
Game::Game()
{
    this-> lvl = 1;
    this->initWindow();
    this->initTextures();
    this->initGUI();
    this->initWorld();
    this->points = 0;

    this->player = new Player();
    this->initEnemyFactories();
    this->initEnemies();
}

//destructor
Game::~Game()
= default;

// Singleton instance
Game* Game::instance = nullptr;

// Access Singleton instance
Game &Game::getInstance() {
    if (!instance) {
        instance = new Game();
    }
    return *instance;
}

//keeps everything running
void Game::run()
{
    while (this->window->isOpen())
    {
        this->updatePollEvents();

        //if the player is no longer alive we stop updating
        if(this->player->getHp() > 0)
            this->update();

        this->render();
    }
}

//check if window is closed
void Game::updatePollEvents() const {
    sf::Event e{};
    while (this->window->pollEvent(e))
        //closes the window when exit is pressed
        if (e.Event::type == sf::Event::Closed)
            this->window->close();

}

//updates the input
void Game::updateInput()
{
    //move left
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        this->player->move(-1.f, 0.f);

    //move right
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        this->player->move(1.f, 0.f);

    //move up
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        this->player->move(0.f, -1.f);

    //move down
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        this->player->move(0.f, 1.f);

    //shooting a bullet
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && this->player->canAttack())
    {
        this->bullets.push_back(std::make_unique<Bullet>(textureManager.getResource("BULLET"),
            this->player->getPos().x + this->player->getBounds().width/2.f,
            this->player->getPos().y,
            0.f,
            -1.f,
            5.f));
    }
}

//updates the GUI
void Game::updateGUI()
{
    // prints the score on the screen
    std::stringstream ss;
    ss << "Points: " << this->points;
    this->pointText.setString(ss.str());

    //prints the hp bar
    const float hpPercent = static_cast<float>(this->player->getHp()) / this->player->getHpMax();
    this->playerHpBar.setSize(sf::Vector2f(300.f * hpPercent, this->playerHpBar.getSize().y));
}

//this function blocks the player from moving off the window
void Game::updateCollision() const {
    //left
    if (this->player->getBounds().left < 0.f)
    {
        this->player->setPosition(0.f, this->player->getBounds().top);
    }
    //Right
    else if (this->player->getBounds().left + this->player->getBounds().width >= this->window->getSize().x)
    {
        this->player->setPosition(this->window->getSize().x - this->player->getBounds().width, this->player->getBounds().top);
    }

    //Top
    if (this->player->getBounds().top < 0.f)
    {
        this->player->setPosition(this->player->getBounds().left, 0.f);
    }
    //Bottom
    else if (this->player->getBounds().top + this->player->getBounds().height >= this->window->getSize().y)
    {
        this->player->setPosition(this->player->getBounds().left, this->window->getSize().y - this->player->getBounds().height);
    }
}

//updates the bullets
void Game::updateBullets()
{
    for (int i = this->bullets.size() - 1; i >= 0; --i)
    {
        this->bullets[i]->update();

        // Check if bullet is off-screen
        if (this->bullets[i]->getBounds().top + this->bullets[i]->getBounds().height < 0.f)
        {
            // Remove the bullet (automatically deletes via unique_ptr)
            this->bullets.erase(this->bullets.begin() + i);
        }
    }

}

// updates enemies
void Game::updateEnemies()
{

    this->spawnTimer += 0.5f;

    //initialises next lvl
    if (this->points >= 1000 &&  this->lvl==1)
        this->initLvl();
    if (this->points >= 2000 &&  this->lvl==2)
        this->initLvl();

    if (this->spawnTimer >= this->spawnTimerMax) {
        float posX = rand() % (this->window->getSize().x - 20) + 20.f;
        float posY = -100.f;

        this->enemies.push_back(
            enemyFactories[currentFactoryIndex]->createEnemy(posX, posY)
        );

        this->spawnTimer = 0.f;
    }

    //Update
    unsigned counter = 0;
    for ( counter = 0; counter < this->enemies.size(); ) // No increment in the loop declaration
    {
        auto& enemy = this->enemies[counter];
        enemy->update();

        // Check if enemy is out of bounds
        if (enemy->getBounds().top > this->window->getSize().y)
        {
            //TODO delete player health according to enemy type
            this->enemies.erase(this->enemies.begin() + counter); // Automatically deletes the enemy
        }
        // Check if enemy intersects with the player
        else if (enemy->getBounds().intersects(this->player->getBounds()))
        {
            this->player->loseHp(enemy->getDamage());
            this->enemies.erase(this->enemies.begin() + counter); // Automatically deletes the enemy
        }
        else
        {
            ++counter; // Only increment if no erasure happened
        }
    }
}

//updates the combat
void Game::updateCombat()
{
    for (int i = this->enemies.size() - 1; i >= 0; --i)
    {
        for (int k = this->bullets.size() - 1; k >= 0; --k)
        {
            if (this->enemies[i]->getBounds().intersects(this->bullets[k]->getBounds()))
            {
                // If the enemy has been hit increase the points
                this->points += this->enemies[i]->getPoints();

                // Erase the enemy and bullet (memory managed by unique_ptr)
                this->enemies.erase(this->enemies.begin() + i);
                this->bullets.erase(this->bullets.begin() + k);

                notifyObservers(); // Notify observers when points change

            }
        }
    }

}

//all update functions
void Game::update()
{
    this->updateInput();

    this->player->update();

    this->updateCollision();

    this->updateBullets();

    this->updateEnemies();

    this->updateCombat();

    this->updateGUI();


}

void Game::initEnemyFactories() {
    enemyFactories.push_back(std::make_unique<Enemy1Factory>());
    enemyFactories.push_back(std::make_unique<Enemy2Factory>());
    enemyFactories.push_back(std::make_unique<Enemy3Factory>());
    currentFactoryIndex = 0;
}

//renders the GUI
void Game::renderGUI() const {
    this->window->draw(this->pointText);
    this->window->draw(this->playerHpBarBack);
    this->window->draw(this->playerHpBar);
}

//renders the background
void Game::renderWorld() const {
    this->window->draw(this->worldBackground);
}

//renters everything else
void Game::render() const {
    this->window->clear();

    //renders the background
    //can replace this function directly with this->window->draw(this->worldBackground);
    //I will keep the function to be able to add a custom background for every lvl more easly
    this->renderWorld();

    //Draw player
    this->player->render(*this->window);

    //Renders the bullets
    for (const auto& bullet : this->bullets)
    {
        bullet->render(this->window);
    }
    //Renders the enemies
    for (const auto& enemy : this->enemies) {
        enemy->render(this->window);
    }

    //renders the GUI
    this->renderGUI();

    //renders the lvl 2 text
    if(this->lvl == 2 && this->points ==1000)
        this->window->draw(this->lvlText);

    //renders the lvl 3 screen
    if(this->lvl == 3 && this->points ==2000)
        this->window->draw(this->lvlText);

    //Game over screen
    if (this->player->getHp() <= 0)
        this->window->draw(this->gameOverText);

    this->window->display();
}
