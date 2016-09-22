#pragma once
#include <d2d1.h>
#include "Graphics.h"
#include "KeyboardListener.h"
#include "MinionList.h"

class Minion
{
public:
	Minion();
	Minion(wchar_t* fileName) : Minion(0, 0, false, fileName) {}
	Minion(float x, float y, wchar_t* fileName) : Minion(x, y, false, fileName) {}
	Minion(float x, float y, bool movable, wchar_t* fileName);

	~Minion();

	float virtual getPosX() const;
	float virtual getPosY() const;
	float virtual getWidth() const;
	float virtual getHeight() const;
	float getCenterX() const;
	float getCenterY() const;
	float getCenterDistance(Minion* minion2) const;
	float getCenterDistance(float x, float y) const;

	bool virtual isTangible() const;
	bool virtual isMovable() const;

	void virtual setPosX(float x);
	void virtual setPosY(float y);
	void virtual setWidth(float w);
	void virtual setHeight(float h);

	void virtual setTangible(bool t);

	bool virtual isLoaded() const;
	bool virtual collidesWith(Minion* obj) const;
	bool virtual isTouching(float x, float y, float top, float left, float bottom, float right) const;
	bool virtual isInside(float x, float y, float top, float left, float bottom, float right) const;
	bool virtual objectTouches(Minion * obj) const;

	HRESULT virtual loadImage(Graphics* gfx);

	void virtual drawObject(Graphics* gfx, float xOffset, float yOffset);
	void virtual drawObject(Graphics* gfx);

	void virtual scaleObject(float xScale, float yScale);

	bool virtual pushOutOf(Minion* obj, int axis);

	void virtual Update(float deltaTime, KeyboardListener* kbd, MinionList* minions);

	static const int AXIS_X = 0;
	static const int AXIS_Y = 1;
protected:
	float posX;
	float posY;
	float width;
	float height;
	
	bool tangible;
	bool loaded;
	bool movable;

	ID2D1Bitmap* img;

	LPWSTR name;
};

