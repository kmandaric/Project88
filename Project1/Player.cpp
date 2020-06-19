#include "stdafx.h"
#include<iostream>
#include "Player.h"
#include "Animation.h"
#include "Game.h"

void Player::set_current_animation(std::string anim, bool flip) {
	currentAnimation = &animations[anim];
	animations[anim].setSprite(&this->sprite, flip);
}

Player::Player()
{
	this->initVariables();
	this->initTexture();
	this->initSprite();
	this->sprite.setPosition(50, 50);

	animations["run"] = Animation("Res/Run_Sheet.png", &this->sprite, sf::IntRect(0, 0, 416, 454), 5, 4, 0.032f);
	animations["idle"] = Animation("Res/Idle_Sheet.png", &this->sprite, sf::IntRect(0, 0, 416, 454), 4, 4, 0.032f);
	animations["jump"] = Animation("Res/Jump_Sheet.png", &this->sprite, sf::IntRect(0, 0, 416, 454), 5, 6, 0.032f);
	set_current_animation("idle");
	
	//idleAnimation = Animation("Res/Idle_Sheet.png",sf::IntRect(0,0,416,454), 4, 4, 0.032f);
	//idleAnimation.setSprite(&this->sprite);
}

Player::~Player()
{
}

void Player::initVariables()
{
}

void Player::initTexture()
{
	if (!this->idleSheet.loadFromFile("Res/Idle_Sheet.png"))
	{
		std::cout << "ERROR: Player: Could not load the player sheet!" << "\n";
	}	

	
}

void Player::initSprite()
{

}



void Player::updateMovement(float dt, float time)
{
	set_current_animation("idle");
	


	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) //Left
	{
		set_current_animation("run", true);
		this->sprite.move(-5.f, 0.f);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) //Right 
	{
		set_current_animation("run");
		this->sprite.move(5.f, 0.f);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)&& !isLongJumping) //Up
	{
		if (isJumping)
		{
			timeSinceJumpStart += dt;
			acceleration += sf::Vector2f(0, -15);
			if (timeSinceJumpStart >= longJumpTime)
			{
				timeSinceJumpStart = 0;
				isLongJumping = true;
			}
		}
		else
		{
			isJumping = true;
			acceleration += sf::Vector2f(0, -655);
		}
		
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
		{
			set_current_animation("jump",true);

		}
		else
		{
			set_current_animation("jump");
		}
		
		//this->sprite.move(0.f, -14.f);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) //Down
	{
		set_current_animation("run");
		//this->sprite.move(0.f, 5.f);
	}

	this->velocity += acceleration;
	this->sprite.move(velocity*dt);

	if (this->sprite.getPosition().y > 655) {
		this->sprite.setPosition(this->sprite.getPosition().x, 655);
		isJumping = isLongJumping = false;
	}

	//TODO COLLISION DETECTION
	/*if (sprite.getGlobalBounds().intersects(testCollision.getGlobalBounds()))
	{
		std::cout << "collision" << std::endl;
	}
	else
	{
		std::cout << "no collision" << std::endl;
	}*/
	
}
int sizeX = 406, sizeY = 420;
int posX = 0, posY = 0;
void Player::update(float dt, float time)
{
	//std::cout << dt << std::endl;

	acceleration.y = 9.81;
	this->updateMovement(dt, time);
	if(currentAnimation) currentAnimation->update(dt, time);


}

void Player::render(sf::RenderTarget & target)
{
	target.draw(this->sprite);
}
