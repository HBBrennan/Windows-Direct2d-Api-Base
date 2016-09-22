#pragma once
#include "Minion.h"
#include "GameLevel.h"
#include "TestLevel.h"
#include "GameController.h"
#include "TestLevel.h"

class Button :
	public Minion
{
protected:
	void stateChanged(bool isDown, KeyboardListener* kbd);
	bool isMouseOver(KeyboardListener* kbd);
	bool isDown;

	ID2D1Bitmap* img2;
	LPWSTR name2;
public:
	Button() : Minion() {}
	Button(wchar_t* upFileName, wchar_t* downFileName) : Button(0, 0, upFileName, downFileName) {}
	Button(float x, float y, wchar_t* upFileName, wchar_t* downFileName);

	void Update(float deltaTime, KeyboardListener* kbd, MinionList* minions) override;
	HRESULT loadImage(Graphics* gfx) override;
	void drawObject(Graphics* gfx) override;
	void drawObject(Graphics* gfx, float xOffset, float yOffset) override;

	~Button();
};

