#pragma once
#include "GameLevel.h"
#include "Unit.h"
#include "TestUnit.h"
#include <vector>

class TestLevel :
	public GameLevel
{
public:
	TestLevel() : GameLevel() {}

	void Load() override;
	void Unload() override;
	void Render() override;
	void Update(float deltaTime) override;
	void checkMouseDrag();
	void checkRightClick();
	void selectArea(POINT* start, POINT* end);

	~TestLevel()
	{
		Unload();
	}
private:
	float xOffset;
	float yOffset;
};

