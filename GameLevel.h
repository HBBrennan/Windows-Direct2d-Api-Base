#pragma once
#include "Graphics.h"
#include "Minion.h"

const float BG_OFFSET_RATIO = 0.05f;

class KeyboardListener;

class GameLevel
{
protected:
	static Graphics* gfx;
	static KeyboardListener* kbd;
	static int windowX;
	static int windowY;
	static HWND window;
	static MinionList* bgMinions;
	static MinionList* fgMinions;
	static MinionList* UIMinions;

public:
	GameLevel();

	static void Init(Graphics* graphics, KeyboardListener* keyboard, int wX, int wY, HWND w);

	static int getWindowX()
	{
		return windowX;
	}

	static int getWindowY()
	{
		return windowY;
	}

	static HWND getWindow()
	{
		return window;
	}

	virtual void loadMinions();

	virtual void renderMinions(float xOffset, float yOffset);

	virtual void updateMinions(float deltaTime, KeyboardListener* kbd);


	virtual void Load() = 0;
	virtual void Unload();
	virtual void Render() = 0;
	virtual void Update(float deltaTime) = 0;

};