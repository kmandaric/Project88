#pragma once
#include<SFML/Graphics.hpp>
#include<SFML/System.hpp>
#include<SFML/Window.hpp>
#include "Player.h"
#include"Collider.h"
#include"Platform.h"
#include"Letter.h"
#include<vector>

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
	sf::Font endFont;
	sf::Text endText; 
	std::vector<Platform*> platforms;
	std::vector<Letter*> lettersToPickUp, pickedUpLetters;
	Letter* currentLetterToPickUp = nullptr;
	int numLettersToCollect;
	bool end = false;

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

