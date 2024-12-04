#include "Game.h"

///starts the window
void Game::initWindow()
{
	this->window = new sf::RenderWindow(sf::VideoMode(800, 600), "Idleon", sf::Style::Close | sf::Style::Titlebar | sf::Style::Resize);
	this->window->setFramerateLimit(60); //fps limit = 60
	this->window->setVerticalSyncEnabled(false);//vsync false
}

///initialises bullet textures
void Game::initTextures()
{
	this->textures["BULLET"] = new sf::Texture();
	this->textures["BULLET"]->loadFromFile("../assets/bullet.png");
}

///initialises GUI
void Game::initGUI()
{
	///check if font loaded properly
	if (!this->font.loadFromFile("../assets/PixellettersFull.ttf"))
		std::cout << "Eroare font" << "\n";

	///point count
	this->pointText.setPosition(700.f, 5.f);
	this->pointText.setFont(this->font);
	this->pointText.setCharacterSize(30);
	this->pointText.setFillColor(sf::Color::White);
	this->pointText.setString("aaaaaaaaaaaaa");

	///game over screeen
	this->gameOverText.setFont(this->font);
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
void Game::initWorld()
{
	if (!this->worldBackgroundTex.loadFromFile("../assets/bg.jpg"))
		std::cerr << "Background error" << "\n";

	this->worldBackground.setTexture(this->worldBackgroundTex);
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
void Game::initLvl2() {
	this -> lvl ++;
	this->initNextLvlGUI();
	enemies.clear();
}

//constructor
Game::Game()
{
	this-> lvl = 1;
	this->initWindow();
	this->initTextures();
	this->initGUI();
	this->initWorld();
	this->points = 0;

	this->player = new Player();
	this->initEnemies();
}

//destructor
Game::~Game()
= default;

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
		this->bullets.push_back(std::make_unique<Bullet>(this->textures["BULLET"],
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
		this->initLvl2();
	if (this->points >= 2000 &&  this->lvl==2)
		this->initLvl2();

	//checks the according lvl and spawns the enemy if the cooldown has passed
	//will update for more diversity between enemies
	if ((this->spawnTimer >= this->spawnTimerMax) && this->lvl == 1)
	{
		this->enemies.push_back(std::make_unique<Enemy_1>(rand() % (this->window->getSize().x -20) +20.f, -100.f));
		this->spawnTimer = 0.f;
	}else if (this->spawnTimer >= this->spawnTimerMax&& this->lvl == 2) {
		this->enemies.push_back(std::make_unique<Enemy_2>(rand() % this->window->getSize().x-20.f, -100.f));
		this->spawnTimer = 0.f;
	}else if (this->spawnTimer >= this->spawnTimerMax&& this->lvl == 3) {
		this->enemies.push_back(std::make_unique<Enemy_3>(rand() % this->window->getSize().x-20.f, -100.f));
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
