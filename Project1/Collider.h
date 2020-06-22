#pragma once
#include <SFML/Graphics.hpp>
class Collider	
{
public:
	Collider(sf::Sprite* body, bool isStatic =  false);
	~Collider();

	void Move(float dx, float dy) { if(!isStatic) body->move(dx, dy); }

	bool CheckCollision(Collider& other, float push);

	sf::Vector2f GetPosition() { return body->getPosition(); }

	sf::Vector2f GetHalfSize() { return sf::Vector2f(body->getGlobalBounds().width / 2.0f, body->getGlobalBounds().height / 2.0f);
	}

private: 
	sf::Sprite* body;
	bool isStatic = false;
};

