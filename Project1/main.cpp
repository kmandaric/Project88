#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
#include<SFML/Graphics.hpp>
#include<iostream>
#include"Game.h"
#include "Player.h"
#include "Animation.h"

int main()
{
	Game game;
	//Game loop
	while (game.running())
	{	
		//Update
		game.update();
		//Render
		game.render(); 
	}
	
		
	
	return 0;
}