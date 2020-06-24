#pragma once
#include<SFML/Graphics.hpp>
#include "Animation.h"
#include "Collider.h"
class Player
{
private:
	//Movement

	//Core
	void initVariables();
	void initTexture();
	void initSprite();

	void set_current_animation(std::string, bool flip=false);

	std::map<std::string, Animation> animations;
	Animation *currentAnimation = nullptr;
	//Animation idleAnimation;

	float moveSpeed = 50.0f, maxSpeed = 400.0f, friction = 7.0f;
	sf::Vector2f velocity{}, position{};
	float timeSinceJumpStart=0, longJumpTime= .5f;

public:
	sf::Texture idleSheet;
	sf::Sprite sprite;
	Collider collider;

	bool isJumping = false, isLongJumping = false;
	
public:
	Player();
	virtual ~Player();

	//Functions
	void updateMovement(float dt, float time);
	void update(float dt, float time);
	void render(sf::RenderTarget & target);
	
};

