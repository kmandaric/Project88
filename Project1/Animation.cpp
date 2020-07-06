#include<iostream>
#include "Player.h"
#include "Animation.h"



Animation::Animation(const char* path, sf::Sprite* sprite, sf::IntRect spriteSize, int Rows, int Cols, float frameTime)
	:spriteSize(spriteSize),Rows (Rows), Cols(Cols), frameTime(frameTime)
{
	this->animTexture.loadFromFile(path);
	animTextureSize = animTexture.getSize();

	setSprite(sprite);
}

Animation::~Animation()
{

}

void Animation::update(float dt, float time)
{
	timeSinceLastFrame += dt;
	if (timeSinceLastFrame >= frameTime)
	{
		timeSinceLastFrame = 0;
		currentCol++;
		if (currentCol < Cols)
		{
			currentFrame.left += spriteSize.width;
		}
		else
		{
			currentCol = 0;
			currentFrame.top += spriteSize.height;
			currentFrame.left = 0;
			currentRow++;
			if (currentRow >= Rows)
			{
				currentFrame.top = 0;
				currentRow = 0;
			}
		}
		this->sprite->setTextureRect(sf::IntRect(currentFrame.left, currentFrame.top, spriteSize.width, spriteSize.height));
	}

}

void Animation::setSprite(sf::Sprite * sprite, bool flip)
{
	
	this->sprite = sprite;
	this->sprite->setTexture(animTexture);
	this->sprite->setOrigin(this->sprite->getTextureRect().width/2, this->sprite->getTextureRect().height / 2);
	if (flip)
	{
		this->sprite->setScale(-spriteScale.x, spriteScale.y);
	}
	else
	{
		this->sprite->setScale(spriteScale);
	}
	
}






	



