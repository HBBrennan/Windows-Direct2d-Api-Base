#pragma once
#include "Unit.h"
class TestUnit :
	public Unit
{
public:
	TestUnit(float x, float y);
	~TestUnit();

	int getArmorType() override;
	int getUnitType() override;
	bool isAirUnit() override;
};

