#pragma once

#include "GameLevel.h"
#include "Graphics.h"

class GameController
{
	GameController() { }
	static GameLevel* currentLevel;
	static bool Loading;

public:
	static void LoadInitialLevel(GameLevel* lev);
	static void SwitchLevel(GameLevel* lev);

	static void Init();

	static void Render();
	static void Update(float deltaTime);
};