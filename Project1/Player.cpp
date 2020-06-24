#include "stdafx.h"
#include<iostream>
#include "Player.h"
#include "Animation.h"
#include "Game.h"


void Player::set_current_animation(std::string anim, bool flip) {
	currentAnimation = &animations[anim];
	animations[anim].setSprite(&this->sprite, flip);
}

Player::Player():collider(Collider(&sprite))
{
	this->initVariables();
	this->initTexture();
	this->initSprite();
	this->sprite.setPosition(200, 200);

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
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) //Up
	{
		velocity += sf::Vector2f(0.0f, 0.0f);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) //Left
	{
		velocity += sf::Vector2f(-moveSpeed, 0.0f);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) //Right
	{
		velocity += sf::Vector2f(moveSpeed, 0.0f);
	}
	
		if (velocity.x < -maxSpeed)
		{
			velocity.x = -maxSpeed;
		}
		else if(velocity.x > maxSpeed)
		{
			velocity.x = maxSpeed;
		}
	if (isJumping)
	{
		velocity.y += 10.0f;
	}
	else
	{
		if (velocity.x>0.1)
		{
			velocity.x -= friction;
		}
		else if(velocity.x < -0.1)
		{
			velocity.x += friction;
		}
		else
		{
			velocity.x = 0;
		}
	}
	this->sprite.move(velocity*dt);
	std::cout <<velocity.x << " " << velocity.y << std::endl;
	std::cout << sprite.getPosition().x << " " << sprite.getPosition().y << std::endl;
	//if (sprite.getPosition().x < sprite.getTexture()->getSize().x/2)
	//{
	//	sprite.setPosition(sprite.getTexture()->getSize().x / 2+1, sprite.getPosition().y);
	//}
}

void Player::update(float dt, float time)
{
	this->updateMovement(dt, time);
	if(currentAnimation) currentAnimation->update(dt, time);
}

void Player::render(sf::RenderTarget & target)
{
	target.draw(this->sprite);
}
