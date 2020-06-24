#pragma once

#include <string>
#include<SFML/Graphics.hpp>
#include "Collider.h"

class Letter
{
public:
	sf::Sprite sprite;
	sf::Texture texture;
	Collider collider;

	Letter(sf::Vector2f position, std::string path): collider(Collider(&sprite))
	{
		texture.loadFromFile(path);
		sprite.setTexture(texture);
		sprite.setPosition(position);
		sprite.setScale(sf::Vector2f(0.2f,0.2f));

		this->sprite.setOrigin(this->sprite.getTextureRect().width / 2, this->sprite.getTextureRect().height / 2);
	}

	Letter(const Letter& other)
		: sprite(other.sprite), texture(other.texture), collider(other.collider)
	{
	}

	void render(sf::RenderTarget & target) {	
		target.draw(sprite);
	}

	void update(float deltaTime, float time)
	{
		sprite.move(0.0f, 100.0f*deltaTime);
	}
};