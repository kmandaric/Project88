#pragma once
#include<SFML\Graphics.hpp>
#include <string>
#include <map>
#include "Player.h"
class Animation
{
private:
	sf::Texture animTexture;
	sf::Sprite* sprite;
	sf::IntRect spriteSize;
	int Rows, Cols;
	int currentRow=0, currentCol=0;
	float frameTime;
	float timeSinceLastFrame = 0;	
	sf::Vector2u animTextureSize; 
	sf::Vector2u currentFramePos;
	sf::IntRect currentFrame = {};
public:
	Animation() = default;
	Animation(const char* path, sf::Sprite* sprite, sf::IntRect spriteSize, int Rows, int Cols, float frameTime = 0.032f);
	~Animation();
	void update(float dt, float time);
	void setSprite(sf::Sprite* sprite, bool flip=false);
	sf::Vector2f spriteScale{ 0.17f , 0.17f };
};

