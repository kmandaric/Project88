#include "Game.h"
#include "Player.h"
#include "Animation.h"
#include <iostream>

//Constructors & Destructors
Game::Game()
{
	std::srand(5);
	this->initializeVariables();
	this->initWindow();
	this->initPlayer();

	platforms.push_back(new Platform({ 245, 735 }, "Res/LongPlatform.png"));
	platforms.push_back(new Platform({ 105, 525 }, "Res/Tiles/grass.png"));
	platforms.push_back(new Platform({ 385, 525 }, "Res/Tiles/grass.png"));
	platforms.push_back(new Platform({ 245, 385 }, "Res/Tiles/grass.png"));
	platforms.push_back(new Platform({ 35, 105 }, "Res/Tiles/grass.png"));
	platforms.push_back(new Platform({ 455, 105 }, "Res/Tiles/grass.png"));
	platforms.push_back(new Platform({ -35, 105 }, "Res/Tiles/grass.png"));
	(*(platforms.end()-1))->sprite.setScale(1, 500);
	platforms.push_back(new Platform({ 525, 105 }, "Res/Tiles/grass.png"));
	(*(platforms.end()-1))->sprite.setScale(1, 500);



	lettersToPickUp.push_back(new Letter({ 250, -70 }, 'W', "Res/Letters/letter_W.png"));
	lettersToPickUp.push_back(new Letter({ 250, -70 }, 'I',"Res/Letters/letter_I.png"));
	lettersToPickUp.push_back(new Letter({ 250, -70 }, 'L',"Res/Letters/letter_L.png"));
	lettersToPickUp.push_back(new Letter({ 250, -70 }, 'L',"Res/Letters/letter_L.png"));
	lettersToPickUp.push_back(new Letter({ 250, -70 }, 'Y',"Res/Letters/letter_Y.png"));
	lettersToPickUp.push_back(new Letter({ 250, -70 }, 'O',"Res/Letters/letter_O.png"));
	lettersToPickUp.push_back(new Letter({ 250, -70 }, 'U',"Res/Letters/letter_U.png"));
	lettersToPickUp.push_back(new Letter({ 250, -70 }, 'M',"Res/Letters/letter_M.png"));
	lettersToPickUp.push_back(new Letter({ 250, -70 }, 'A',"Res/Letters/letter_A.png"));
	lettersToPickUp.push_back(new Letter({ 250, -70 }, 'R',"Res/Letters/letter_R.png"));
	lettersToPickUp.push_back(new Letter({ 250, -70 }, 'R',"Res/Letters/letter_R.png"));
	lettersToPickUp.push_back(new Letter({ 250, -70 }, 'Y',"Res/Letters/letter_Y.png"));
	lettersToPickUp.push_back(new Letter({ 250, -70 }, 'M',"Res/Letters/letter_M.png"));
	lettersToPickUp.push_back(new Letter({ 250, -70 }, 'E',"Res/Letters/letter_E.png"));
	numLettersToCollect = lettersToPickUp.size();

	
}

Game::~Game()
{
	for (auto p : platforms)
		delete p;

	for (auto p : lettersToPickUp)
		delete p;

	for (auto p : pickedUpLetters)
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

	if (endFont.loadFromFile("Res/MarckScript-Regular.ttf"))
	{
		endText.setFont(endFont);
		endText.setString("Will you marry me?");
		endText.setCharacterSize(50);
		endText.setFillColor(sf::Color::White);
		endText.setStyle(sf::Text::Bold);
		

		endText.setPosition(245-endText.getGlobalBounds().width / 2, 200);
	}

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
	
	if (currentLetterToPickUp)
	{
		currentLetterToPickUp->update(deltaTime, time.asSeconds());
	}
	else
	{
		if (lettersToPickUp.size()>0)
		{
			int index = rand() % lettersToPickUp.size();
			auto found = std::find(lettersToPickUp.begin(), lettersToPickUp.end(), lettersToPickUp[index]);
			if (found != lettersToPickUp.end())
			{
				currentLetterToPickUp = lettersToPickUp[index];
				lettersToPickUp.erase(found);
		
				float playerX = player->sprite.getPosition().x; 
				float playerHalfWidth = player->sprite.getGlobalBounds().width / 2;
				sf::Vector2f playerXBounds{ playerX - playerHalfWidth, playerX + playerHalfWidth };

				if (playerX > 245)
				{
					float randPos = rand() % 245;
					currentLetterToPickUp->sprite.setPosition(randPos, currentLetterToPickUp->sprite.getPosition().y);
				}
				else
				{
					float randPos = rand() % 245 + 245 ;
					currentLetterToPickUp->sprite.setPosition(randPos, currentLetterToPickUp->sprite.getPosition().y);
				}
				
			}
		}
	}

	for (Platform* p : platforms)
	{
		if (currentLetterToPickUp)
		{
			if (p->collider.CheckCollision(currentLetterToPickUp->collider, 1.0f))
			{
				
			}
		}

		if (player->collider.CheckCollision(p->collider, 0.0f)) 
		{
			if (p->collider.fromBottom)
			{
				player->isJumping = false;
				player->velocity.y = 0; 
			}
			else if (p->collider.fromTop)
			{
				player->velocity.y = 0; 
			}
			
			if (p->collider.fromLeft || p->collider.fromRight)
			{
				player->velocity.x = 0;
			}
			
		}
	}
	if (currentLetterToPickUp && player->collider.CheckCollision(currentLetterToPickUp->collider, 0.0f))
	{
		pickedUpLetters.push_back(currentLetterToPickUp);
		currentLetterToPickUp = nullptr;
		for (auto letter: pickedUpLetters)
		{
			std::cout << letter->letter << " ";
		}
		std::cout << std::endl;
	}
	if (pickedUpLetters.size()== numLettersToCollect)
	{
		end = true;
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
	if (currentLetterToPickUp)
	{
		this->currentLetterToPickUp->render(*this->window);
	}
	this->renderPlayer();

	if (end)
	{
		window->draw(endText);
		std::cout << "End" << std::endl;
	}

	this->window->display();
}
