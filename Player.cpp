#include "Player.h"


#include "Exceptions.h"


//initialise static variables
sf::Texture Player::texture;

///init player texture
void Player::initTexture()
{
    // Check if the texture is already loaded before loading it again
    if (texture.getSize().x == 0)  // Only load if texture hasn't been loaded
        if (!texture.loadFromFile("../assets/protagonist.png"))  ///if the file in not found send the error
            throw FileNotFoundException("../assets/protagonist.png");


}


//init sprite
void Player::initSprite()
{
    //texture player
    this->sprite.setTexture(Player::texture);
    this->sprite.scale(0.25f, 0.25f); //resize texture
}

//constructor
Player::Player()
{

    this->movementSpeed = 4.f; // movement speed
    this->attackCooldownMax = 30.f; //max attack cooldown
    this->attackCooldown = this->attackCooldownMax;
    this->hpMax = 100; //maximum hp
    this->hp = this->hpMax; //initial hp
    Player::initTexture();
    this->initSprite();
}
//default destructor
Player::~Player()
= default;

// get current position
const sf::Vector2f & Player::getPos() const
{
    return this->sprite.getPosition();
}
// get bounds
sf::FloatRect Player::getBounds() const {
    return this->sprite.getGlobalBounds();
}

//get hp
const int & Player::getHp() const
{
    return this->hp;
}

//get max hp
const int & Player::getHpMax() const
{
    return this->hpMax;
}


//set position
void Player::setPosition(const sf::Vector2f pos)
{
    this->sprite.setPosition(pos);
}
void Player::setPosition(const float x, const float y)
{
    this->sprite.setPosition(x, y);
}


//loseHP
void Player::loseHp(int value)
{
    this->hp -= value;
    if (this->hp < 0)
        this->hp = 0;
}

//move player
void Player::move(const float dirX, const float dirY)
{
    this->sprite.move(this->movementSpeed * dirX, this->movementSpeed * dirY);
}

// check if player can attack
bool Player::canAttack() {
    if (this->attackCooldown >= this->attackCooldownMax) //checks if cooldown is over
    {
        this->attackCooldown = 0.f;
        return true;
    }

    return false;
}
// update attack
void Player::updateAttack()
{
    if(this->attackCooldown < this->attackCooldownMax)
        this->attackCooldown += 0.5f;
}

void Player::update()
{
        this->updateAttack();
}

void Player::render(sf::RenderTarget& target) const {
    target.draw(this->sprite);
}
