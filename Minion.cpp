#include "Minion.h"
#include "GameLevel.h"
#include <cmath>

Minion::Minion(float x, float y, bool m, wchar_t * fileName) : Minion ()
{
	posX = x;
	posY = y;
	movable = m;
	name = fileName;
}

Minion::Minion()
{
	img = NULL;
	loaded = false;
}

Minion::~Minion()
{
	if (img) img->Release();
}

//Position Accessors

float Minion::getPosX() const
{
	return posX;
}

float Minion::getPosY() const
{
	return posY;
}

float Minion::getWidth() const
{
	return width;
}

float Minion::getHeight() const
{
	return height;
}

float Minion::getCenterX() const
{
	return (posX + (width / 2));
}

float Minion::getCenterY() const
{
	return (posY + (height / 2));
}

float Minion::getCenterDistance(Minion* minion2) const
{
	return sqrt(pow(minion2->getCenterX() - getCenterX(), 2) + pow(minion2->getCenterY() - getCenterY(), 2));
}

float Minion::getCenterDistance(float x, float y) const
{
	return sqrt(pow(x - getCenterX(), 2) + pow(y - getCenterY(), 2));
}

//Tangibility Mutator/Accessor

bool Minion::isTangible() const
{
	return tangible;
}

bool Minion::isMovable() const
{
	return movable;
}

void Minion::setTangible(bool t)
{
	tangible = t;
}

//Position Mutators

void Minion::setPosX(float x)
{
	posX = x;
}

void Minion::setPosY(float y)
{
	posY = y;
}

void Minion::setWidth(float w)
{
	width = w;
}

void Minion::setHeight(float h)
{
	height = h;
}

//Load Checker

bool Minion::isLoaded() const
{
	return loaded;
}

//Loads Image

HRESULT Minion::loadImage(Graphics* gfx)
{

	HRESULT hr = gfx->loadBitmap(name, &img);

	if (hr != S_OK)
	{
		return hr;
		OutputDebugString("Minion Failed to Load!\n");
	}

	D2D1_SIZE_F size = img->GetSize();
	width = size.width;
	height = size.height;

	loaded = true;

	OutputDebugString("Minion Successfully Loaded!\n");

	return hr;
}

//Draws The Object

void Minion::drawObject(Graphics* gfx, float xOffset, float yOffset)
{
	gfx->DrawImage(posX - xOffset, (GameLevel::getWindowY() - (posY + height + yOffset)), width, height, img);
}

void Minion::drawObject(Graphics* gfx)
{
	gfx->DrawImage(posX, (GameLevel::getWindowY() - (posY + height)), width, height, img);
}

//Scale The Object

void Minion::scaleObject(float xScale, float yScale)
{
	width *= xScale;
	height *= yScale;
}

//Collision

bool Minion::isInside(float x, float y, float top, float left, float bottom, float right) const
{
	if ((bottom - y) * (y - top) > 0 && (right - x) * (x - left) > 0)
	{
		return true;
	}

	return false;
}

bool Minion::isTouching(float x, float y, float top, float left, float bottom, float right) const
{
	if ((bottom - y) * (y - top) >= 0 && (right - x) * (x - left) >= 0)
	{
		return true;
	}

	return false;
}

bool Minion::collidesWith(Minion* obj) const
{
	float left1 = posX;
	float top1 = posY;
	float right1 = left1 + width;
	float bottom1 = top1 + height;

	float left2 = obj->getPosX();
	float top2 = obj->getPosY();
	float right2 = left2 + obj->getWidth();
	float bottom2 = top2 + obj->getHeight();

	bool inside = false;

	//Test Hitbox1

	//Test top-left1
	inside = inside || isInside(left1, top1, top2, left2, bottom2, right2);

	//Test bottom-left1
	inside = inside || isInside(left1, bottom1, top2, left2, bottom2, right2);

	//Test top-right1
	inside = inside || isInside(right1, top1, top2, left2, bottom2, right2);

	//Test bottom-right1
	inside = inside || isInside(right1, bottom1, top2, left2, bottom2, right2);

	//Test Hitbox2

	//Test top-left2
	inside = inside || isInside(left2, top2, top1, left1, bottom1, right1);

	//Test bottom-left2
	inside = inside || isInside(left2, bottom2, top1, left1, bottom1, right1);

	//Test top-right2
	inside = inside || isInside(right2, top2, top1, left1, bottom1, right1);

	//Test bottom-right2
	inside = inside || isInside(right2, bottom2, top1, left1, bottom1, right1);

	return inside;
}

bool Minion::objectTouches(Minion* obj) const
{
	float left1 = posX;
	float top1 = posY;
	float right1 = left1 + width;
	float bottom1 = top1 + height;

	float left2 = obj->getPosX();
	float top2 = obj->getPosY();
	float right2 = left2 + obj->getWidth();
	float bottom2 = top2 + obj->getHeight();

	bool inside = false;

	//Test Hitbox1

	//Test top-left1
	inside = inside || isTouching(left1, top1, top2, left2, bottom2, right2);

	//Test bottom-left1
	inside = inside || isTouching(left1, bottom1, top2, left2, bottom2, right2);

	//Test top-right1
	inside = inside || isTouching(right1, top1, top2, left2, bottom2, right2);

	//Test bottom-right1
	inside = inside || isTouching(right1, bottom1, top2, left2, bottom2, right2);

	//Test Hitbox2

	//Test top-left2
	inside = inside || isTouching(left2, top2, top1, left1, bottom1, right1);

	//Test bottom-left2
	inside = inside || isTouching(left2, bottom2, top1, left1, bottom1, right1);

	//Test top-right2
	inside = inside || isTouching(right2, top2, top1, left1, bottom1, right1);

	//Test bottom-right2
	inside = inside || isTouching(right2, bottom2, top1, left1, bottom1, right1);

	return inside;
}

//Push Out of Colliding Object

bool Minion::pushOutOf(Minion* obj, int axis)
{
	float left1 = posX;
	float top1 = posY;
	float right1 = left1 + width;
	float bottom1 = top1 + height;

	float left2 = obj->getPosX();
	float top2 = obj->getPosY();
	float right2 = left2 + obj->getWidth();
	float bottom2 = top2 + obj->getHeight();

	bool collide = collidesWith(obj);

	if (collide) //Confirm Collision
	{
		if (axis == AXIS_X)
		{
			float rightDistance = right1 - left2;
			float leftDistance = right2 - left1;

			if (rightDistance > 0)
			{
				if (leftDistance > 0)
				{
					if (rightDistance < leftDistance)
					{
						posX -= rightDistance;
					}
					else
					{
						posX += leftDistance;
					}
				}
				else
				{
					posX -= rightDistance;
				}
			}
			else if (leftDistance > 0)
			{
				posX += leftDistance;
			}
		}
		else if (axis == AXIS_Y)
		{
			float bottomDistance = bottom1 - top2;
			float topDistance = bottom2 - top1;

			if (bottomDistance > 0)
			{
				if (topDistance > 0)
				{
					if (bottomDistance < topDistance)
					{
						posY -= bottomDistance;
					}
					else
					{
						posY += topDistance;
					}
				}
				else
				{
					posY -= bottomDistance;
				}
			}
			else if (topDistance > 0)
			{
				posY += topDistance;
			}

		}
	}

	return collide;
}

void Minion::Update(float deltaTime, KeyboardListener* kbd, MinionList* minions)
{

}
