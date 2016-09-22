#include "Button.h"

bool lastState = false;

Button::Button(float x, float y, wchar_t* upFileName, wchar_t* downFileName) : Minion (x, y, upFileName)
{
	name2 = downFileName;
}

Button::~Button()
{
	if (img2) img2->Release();
}

void Button::Update(float deltaTime, KeyboardListener* kbd, MinionList* minions)
{
	bool isPressed = isMouseOver(kbd) && kbd->isMouse1Down();
	isDown = isPressed;

	if (isPressed != lastState)
		stateChanged(isPressed, kbd);

	lastState = isPressed;
}

bool Button::isMouseOver(KeyboardListener* kbd)
{
	float left = getPosX();
	float bottom = getPosY();
	float right = left + getWidth();
	float top = bottom + getHeight();

	POINT* p = kbd->getMousePos(GameLevel::getWindow());
	int mouseX = p->x;
	int mouseY = p->y;

	bool isWithinX = (mouseX >= left) && (mouseX <= right);
	bool isWithinY = (mouseY >= bottom) && (mouseY <= top);
	
	return (isWithinX && isWithinY);
}

void Button::stateChanged(bool isDown, KeyboardListener* kbd)
{
	if (!isDown)
	{
		if (isMouseOver(kbd))
			GameController::SwitchLevel(new TestLevel());
	}
}

//Loads Image

HRESULT Button::loadImage(Graphics* gfx)
{
	OutputDebugString("Starting Button Load\n");

	HRESULT hr = gfx->loadBitmap(name, &img);

	if (hr != S_OK)
		return hr;

	hr = gfx->loadBitmap(name2, &img2);

	if (hr != S_OK)
		return hr;

	D2D1_SIZE_F size = img->GetSize();
	width = size.width;
	height = size.height;

	loaded = true;

	OutputDebugString("Minion Successfully Loaded!\n");

	return hr;
}

//Draws The Object

void Button::drawObject(Graphics* gfx, float xOffset, float yOffset)
{
	if (isDown)
		gfx->DrawImage(posX - xOffset, (GameLevel::getWindowY() - (posY + height + yOffset)), width, height, img2);
	else
		gfx->DrawImage(posX - xOffset, (GameLevel::getWindowY() - (posY + height + yOffset)), width, height, img);
}

void Button::drawObject(Graphics* gfx)
{
	if (isDown)
		gfx->DrawImage(posX, (GameLevel::getWindowY() - (posY + height)), width, height, img2);
	else
		gfx->DrawImage(posX, (GameLevel::getWindowY() - (posY + height)), width, height, img);
}
