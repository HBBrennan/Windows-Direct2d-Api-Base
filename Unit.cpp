#include "Unit.h"

Unit::~Unit()
{
}

void Unit::setMoveLocation(float moveX, float moveY)
{
	this->moveX = moveX;
	this->moveY = moveY;
	moving = true;
}

void Unit::Update(float deltaTime, KeyboardListener * kbd, MinionList * minions)
{
	if (moving && target == nullptr || target->getAlly())
	{
		float distance = getCenterDistance(moveX, moveY);
		if (distance > stopRadius)
		{
			move(deltaTime, distance);
		}
		else
			moving = false;
	}
}


void Unit::move(float deltaTime, float distance)
{
	posX += deltaTime * movementSpeed * (moveX - getCenterX()) / distance;
	posY += deltaTime * movementSpeed * (moveY - getCenterY()) / distance;
}

