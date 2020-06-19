#pragma once
#include<SFML/Graphics.hpp>
#include<SFML/System.hpp>
#include<SFML/Window.hpp>
#include "Player.h"

/* 
	
*/

class Game
{
private:
	//Variables
	//Window
	sf::RenderWindow* window;
	sf::Event event;
	sf::Sprite bg;
	sf::Texture bgt;

	

	Player* player;

	void initializeVariables();
	void initWindow();
	void initPlayer();


public:
	// Constructor & Destructors
	Game();
	virtual ~Game();

	

	//Accessors
	const bool running() const;
	sf::Time time, lastTime;
	sf::Clock clock; 
	float deltaTime;

	

	//Functions
	void updatePlayer();
	void update();
	void pollEvents();
	void renderPlayer();
	void render();

};

