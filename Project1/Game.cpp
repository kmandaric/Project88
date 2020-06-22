#include "Game.h"
#include "Player.h"
#include "Animation.h"

//Constructors & Destructors
Game::Game()
{
	this->initializeVariables();
	this->initWindow();
	this->initPlayer();

	platforms.push_back(new Platform({ 245, 735 }, "Res/LongPlatform.png"));
	platforms.push_back(new Platform({ 105, 525 }, "Res/Tiles/grass.png"));
	platforms.push_back(new Platform({ 385, 525 }, "Res/Tiles/grass.png"));
	platforms.push_back(new Platform({ 245, 385 }, "Res/Tiles/grass.png"));
	platforms.push_back(new Platform({ 35, 105 }, "Res/Tiles/grass.png"));
	platforms.push_back(new Platform({ 455, 105 }, "Res/Tiles/grass.png"));


}

Game::~Game()
{
	for (auto p : platforms)
		delete p;

	delete this->player;
	delete this->window;
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
	//this->bg = sf::Sprite(bgt);

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
	
	for (Platform* p : platforms)
	{
		if (player->collider.CheckCollision(p->collider, 0.0f)) 
		{
			player->isJumping = player->isLongJumping = false;
		}
	}
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
	//for (auto & platform : platforms)
	//{
	//	platform.render(*this->window);
	//}
	for (Platform* p : platforms)
	{
		p->render(*this->window);
	}
	
	this->renderPlayer();

	this->window->display();
}
