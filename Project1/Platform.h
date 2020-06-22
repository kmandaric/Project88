#pragma once

#include <string>

class Platform
{
public:
	sf::Sprite sprite;
	sf::Texture texture;
	Collider collider;

	Platform(sf::Vector2f position, std::string path): collider(Collider(&sprite, true))
	{
		texture.loadFromFile(path);
		sprite.setTexture(texture);
		sprite.setPosition(position);
		this->sprite.setOrigin(this->sprite.getTextureRect().width / 2, this->sprite.getTextureRect().height / 2);
	}

	Platform(const Platform& other)
		: sprite(other.sprite), texture(other.texture), collider(other.collider)
	{
	}

	void render(sf::RenderTarget & target) {	
		target.draw(sprite);
	}
};