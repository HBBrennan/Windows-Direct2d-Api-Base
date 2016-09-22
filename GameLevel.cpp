#include "GameLevel.h"

Graphics* GameLevel::gfx;
KeyboardListener* GameLevel::kbd;
int GameLevel::windowX;
int GameLevel::windowY;
HWND GameLevel::window;
MinionList* GameLevel::bgMinions;
MinionList* GameLevel::fgMinions;
MinionList* GameLevel::UIMinions;

GameLevel::GameLevel()
{
	bgMinions = new MinionList();
	fgMinions = new MinionList();
	UIMinions = new MinionList();
}

void GameLevel::Init(Graphics* graphics, KeyboardListener* keyboard, int wX, int wY, HWND w)
{
	gfx = graphics;
	kbd = keyboard;
	windowX = wX;
	windowY = wY;
	window = w;
}

void GameLevel::loadMinions()
{
	int size = bgMinions->getSize();

	for (int i = 0; i < size; i++)
	{
		bgMinions->getObject(i)->loadImage(gfx);
	}

	size = fgMinions->getSize();

	for (int i = 0; i < size; i++)
	{
		fgMinions->getObject(i)->loadImage(gfx);
	}

	size = UIMinions->getSize();

	for (int i = 0; i < size; i++)
	{
		UIMinions->getObject(i)->loadImage(gfx);
	}
}

void GameLevel::renderMinions(float xOffset, float yOffset)
{
	int size = bgMinions->getSize();

	for (int i = 0; i < size; i++)
	{
		bgMinions->getObject(i)->drawObject(gfx, (xOffset * BG_OFFSET_RATIO) + 10, 0);
	}

	size = fgMinions->getSize();

	for (int i = 0; i < size; i++)
	{
		fgMinions->getObject(i)->drawObject(gfx, xOffset, yOffset);
	}

	size = UIMinions->getSize();

	for (int i = 0; i < size; i++)
	{
		UIMinions->getObject(i)->drawObject(gfx);
	}
}

void GameLevel::updateMinions(float deltaTime, KeyboardListener* kbd)
{
	int size = bgMinions->getSize();

	for (int i = 0; i < size; i++)
	{
		bgMinions->getObject(i)->Update(deltaTime, kbd, bgMinions);
	}

	size = fgMinions->getSize();

	for (int i = 0; i < size; i++)
	{
		fgMinions->getObject(i)->Update(deltaTime, kbd, fgMinions);
	}

	size = UIMinions->getSize();

	for (int i = 0; i < size; i++)
	{
		UIMinions->getObject(i)->Update(deltaTime, kbd, UIMinions);
	}
}

void GameLevel::Unload()
{
	delete bgMinions;
	delete fgMinions;
	delete UIMinions;
	bgMinions = nullptr;
	fgMinions = nullptr;
	UIMinions = nullptr;
}