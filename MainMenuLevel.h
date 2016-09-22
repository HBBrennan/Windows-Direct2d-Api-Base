#pragma once

#include "GameLevel.h"
#include "Minion.h"
#include "KeyboardListener.h"

class MainMenuLevel : public GameLevel
{
public:
	void Load() override;
	void Unload() override;
	void Render() override;
	void Update(float deltaTime) override;
	void loadMinions();
	void renderMinions();
	void updateMinions(float deltaTime);
};
