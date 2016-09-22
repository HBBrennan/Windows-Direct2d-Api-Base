#include "GameController.h"
#include "GameLevel.h"
#include "MinionList.h"
#include "MainMenuLevel.h"
#include "Button.h"

MinionList* buttons;

Minion* background;
Minion* startButton;

void MainMenuLevel::Load()
{
	buttons = new MinionList();

	background = new Minion(L"Images/MainMenu.png");

	startButton = buttons->addObject(new Button(400.0f, 300.0f, L"Images/StartButton.png", L"Images/StartButtonDown.png"));

	HRESULT hr = background->loadImage(gfx);
	
	if (hr != S_OK)
		OutputDebugString("poop\n");

	float scaleFactor = getWindowY() / background->getHeight();
	background->scaleObject(scaleFactor, scaleFactor);

	float offset = (background->getWidth() - getWindowX())/2;
	background->setPosX(-offset);

	loadMinions();
	
	startButton->setPosX(startButton->getPosX() - startButton->getWidth() / 2);
}

void MainMenuLevel::Unload()
{
	delete background;
	delete buttons;
	background = nullptr;
	startButton = nullptr;
	buttons = nullptr;
}

void MainMenuLevel::Render()
{
	background->drawObject(gfx);

	renderMinions();
}

void MainMenuLevel::Update(float deltaTime)
{
	updateMinions(deltaTime);
}

void MainMenuLevel::loadMinions()
{
	int size = buttons->getSize();

	for (int i = 0; i < size; i++)
	{
		buttons->getObject(i)->loadImage(gfx);
	}
}

void MainMenuLevel::renderMinions()
{
	int size = buttons->getSize();

	for (int i = 0; i < size; i++)
	{
		buttons->getObject(i)->drawObject(gfx);
	}
}

void MainMenuLevel::updateMinions(float deltaTime)
{
	int size = buttons->getSize();

	for (int i = 0; i < size; i++)
	{
		buttons->getObject(i)->Update(deltaTime , kbd, buttons);
	}
}
