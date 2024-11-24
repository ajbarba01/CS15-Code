#include "game.h"
#include "spriteWrapper.h"
#include "collider.h"


Game::~Game()
{
    this->objCollection.clean();

    // this->player gets deleted via this->components in the dtor
}

void Game::pollEvents()
{
    this->window.update(this->ev);
    this->input.update();
}

void Game::startFrame()
{
    this->lastTime = this->clock.getElapsedTime().asSeconds();
}

void Game::awake()
{
    // Some INIT stuff
    this->renderWindow = this->window.window;
    this->objCollection.setCollisionSystem(&this->collisionSystem);

    // Player
    this->player = new GameObject();
    SpriteWrapper* playerSpriteWrapper = new SpriteWrapper(this->player, "assets/sprites/player.png");
    this->player->addComponent(playerSpriteWrapper);

    Collider* playerCollider = new Collider(this->player);
    playerCollider->setRect(sf::FloatRect(0.0f, 0.0f, 32.0f, 64.0f));
    this->player->addComponent(playerCollider);

    this->objCollection.addObject(this->player);
    
    // Square
    GameObject* square = new GameObject();
    square->transform->setPosition(sf::Vector2f(300, 300));
    Collider* squareCollider = new Collider(square);
    square->transform->setStatic(true);
    squareCollider->setRect(sf::FloatRect(0.0f, 0.0f, 32.0f, 32.0f));
    square->addComponent(squareCollider);
    square->addComponent(new SpriteWrapper(square, "assets/tiles/1.png"));

    this->objCollection.addObject(square);


    // End Stuff
    objCollection.processNewObjects();
}

void Game::earlyUpdate()
{
    this->objCollection.earlyUpdate();
}

void Game::update()
{
    this->objCollection.update();
    this->collisionSystem.update();

    // Player Movement
    int moveSpeed = 400;
    float vertical = static_cast<float>(this->input.isKeyPressed(sf::Keyboard::S) - this->input.isKeyPressed(sf::Keyboard::W));
    float horizontal = static_cast<float>(this->input.isKeyPressed(sf::Keyboard::D) - this->input.isKeyPressed(sf::Keyboard::A));

    if (horizontal && vertical)
    {
        horizontal *= 0.707f;
        vertical *= 0.707f;
    }

    if (this->player)
    {
        this->player->transform->move(sf::Vector2f(horizontal * moveSpeed * this->deltaTime, vertical * moveSpeed * deltaTime));
    }
}

void Game::lateUpdate()
{
    this->objCollection.lateUpdate();
}

void Game::render()
{
    this->window.prepare();
    
    this->objCollection.render(this->renderWindow);

    this->window.render();
}

void Game::calculateDt()
{
    this->deltaTime = this->clock.getElapsedTime().asSeconds() - this->lastTime;
}

bool Game::isRunning()
{
	return !(this->window.windowClosed or this->shouldClose);
}

float Game::getElapsedTime()
{
    return this->clock.getElapsedTime().asSeconds();
}
