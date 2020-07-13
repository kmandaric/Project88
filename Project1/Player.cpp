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
	this->sprite.setPosition(250, 500);

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

bool isPressedW = false;
void Player::updateMovement(float dt, float time)
{
	velocity += sf::Vector2f(0.0f, 10.f);
	set_current_animation("idle");
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W) && !isJumping) //Up
	{
		velocity += sf::Vector2f(0.0f, -800.f);
		isJumping  = true; 
		
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) //Left
	{
		velocity += sf::Vector2f(-moveSpeed, 0.0f);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) //Right
	{
		velocity += sf::Vector2f(moveSpeed, 0.0f);
	}

	//Velocity clamping
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
		float frictionStopper = (friction + 0.5);
		if (velocity.x>frictionStopper)
		{
			velocity.x -= friction;
		}
		else if(velocity.x < -frictionStopper)
		{
			velocity.x += friction;
		}
		else
		{
			velocity.x = 0;
		}
	}
	this->sprite.move(velocity*dt);
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
