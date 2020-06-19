#include "Game.h"
#include "Player.h"
#include "Animation.h"

//Constructors & Destructors
Game::Game()
{
	this->initializeVariables();
	this->initWindow();
	this->initPlayer();
}

Game::~Game()
{
	delete this->window;
	delete this->player;
}

//Private functions

//Initializations
void Game::initializeVariables()
{
	this->window = nullptr;
}
//Initialize window
void Game::initWindow()
{
	this->window = new sf::RenderWindow(sf::VideoMode(490,770), "Project88");
	this->window->setFramerateLimit(60);
	
	bgt.loadFromFile("Res/TestMap.png");
	this->bg = sf::Sprite(bgt);
}

//Initialize player
void Game::initPlayer()
{
	this->player = new Player();
}

const bool Game::running() const
{
	return this->window->isOpen();
}

//Functions
void Game::updatePlayer()
{
	this->player->update(this->deltaTime, this->time.asSeconds());
}

void Game::pollEvents()
{
	while (this->window->pollEvent(this->event))
	{
		switch (this->event.type)
		{
		case sf::Event::Closed:
				this->window->close();
				break;
			case sf::Event::KeyPressed:
				if (this->event.key.code == sf::Keyboard::Escape)
					this->window->close();
				break;
		}
	}
	
	
}

void Game::renderPlayer()
{
	this->player->render(*this->window);
}

void Game::update()
{
	lastTime = time;
	time = clock.getElapsedTime();
	deltaTime = time.asSeconds() - lastTime.asSeconds();

	this->pollEvents();
	this->updatePlayer();
}

void Game::render()
{
	/* 
		-Clears frame
		-Renders the game objects
		-Display frame in window
	*/
	this->window->clear();

	// Draw game objects
	this->window->draw(bg);
	this->renderPlayer();
	this->window->display();
}
