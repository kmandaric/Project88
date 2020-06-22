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
	//sf::Vector2f otherPosition = ;
	sf::Vector2f otherPosition = other.GetPosition();
	sf::Vector2f otherHalfSize = other.GetHalfSize();
	sf::Vector2f otherScale = other.body->getScale();

	//sf::Vector2f thisPosition = ;
	sf::Vector2f thisPosition = GetPosition();
	sf::Vector2f thisHalfSize = GetHalfSize();
	sf::Vector2f thisScale = body->getScale();

	float deltaX = otherPosition.x - thisPosition.x;
	float deltaY = otherPosition.y - thisPosition.y;

	float intersectX = abs(deltaX) - (otherHalfSize.x + thisHalfSize.x);
	float intersectY = abs(deltaY) - (otherHalfSize.y + thisHalfSize.y);

	//if (intersectX < 0.0f && intersectY < 0.0f)
	//{
	//	if (deltaY < 0) Move(0, -intersectY);
	//	else Move(0, intersectY);
	//
	//	if (deltaX < 0) Move(-intersectX, 0);
	//	else Move(intersectX, 0);
	//}

	if (1)
	if (intersectX < 0.0f && intersectY < 0.0f)
	{
		//
		//std::cout
		//	<< otherPosition.x << " "
		//	<< otherPosition.y << " "
		//	<< thisPosition.x << " "
		//	<< thisPosition.y << " "
		//	<< std::endl;
		push = std::min(std::max(push, 0.0f), 1.0f);
		std::cout << "Collision" << std::endl;

		

		//Move(0, intersectY);

		if (intersectX > intersectY)
		{
		
			if (deltaX > 0.0f)
			{
				Move(intersectX * (1.0f - push), 0.0f);
				other.Move(-intersectX * push, 0.0f);
			}
			else
			{
				Move(-intersectX * (1.0f - push), 0.0f);
				other.Move(intersectX * push, 0.0f);
			}
		}
		else
		{
			if (deltaY > 0.0f)
			{
				Move(0.0f, intersectY * (1.0f - push));
				other.Move(0.0f, -intersectY * push);
			}
			else
			{
				Move(0.0f, -intersectY * (1.0f - push));
				other.Move(0.0f,intersectY * push);
			}
		
		}

		return true;
	}
	return false;
}
