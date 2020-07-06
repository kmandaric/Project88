#include "Collider.h"
#include <iostream>

Collider::Collider(sf::Sprite* body, bool isStatic): body(body), isStatic(isStatic)
{
}

Collider::~Collider()
{
}

bool Collider::CheckCollision(Collider & other, float push)
{
	sf::Vector2f otherPosition = other.GetPosition();
	sf::Vector2f otherHalfSize = other.GetHalfSize();
	sf::Vector2f otherScale = other.body->getScale();

	sf::Vector2f thisPosition = GetPosition();
	sf::Vector2f thisHalfSize = GetHalfSize();
	sf::Vector2f thisScale = body->getScale();

	float deltaX = otherPosition.x - thisPosition.x;
	float deltaY = otherPosition.y - thisPosition.y;

	float intersectX = abs(deltaX) - (otherHalfSize.x + thisHalfSize.x);
	float intersectY = abs(deltaY) - (otherHalfSize.y + thisHalfSize.y);

	if (intersectX < 0.0f && intersectY < 0.0f)
	{
		push = std::min(std::max(push, 0.0f), 1.0f);

		if (intersectX > intersectY)
		{
		
			if (deltaX > 0.0f)
			{
				fromLeft = true;
				other.fromRight = true;
				other.fromLeft = other.fromTop = other.fromBottom = false;
				fromRight = fromTop = fromBottom = false;
				Move(intersectX * (1.0f - push), 0.0f);
				other.Move(-intersectX * push, 0.0f);
			}
			else
			{
				fromRight = true;
				other.fromLeft = true; 
				other.fromRight = other.fromTop = other.fromBottom = false;
				fromLeft = fromTop = fromBottom = false;
				Move(-intersectX * (1.0f - push), 0.0f);
				other.Move(intersectX * push, 0.0f);
			}
		}
		else
		{
			if (deltaY > 0.0f)
			{
				fromTop = true;
				other.fromBottom = true; 
				other.fromLeft = other.fromTop = other.fromRight = false;
				fromRight = fromLeft = fromBottom = false;
				Move(0.0f, intersectY * (1.0f - push));
				other.Move(0.0f, -intersectY * push);
			}
			else
			{
				fromBottom = true;
				other.fromTop = true;
				other.fromLeft = other.fromRight = other.fromBottom = false;
				fromRight = fromTop = fromLeft = false;
				Move(0.0f, -intersectY * (1.0f - push));
				other.Move(0.0f, intersectY * push);
			}
		}
		return true;
	}
	return false;
}
