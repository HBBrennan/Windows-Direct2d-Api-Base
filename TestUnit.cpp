#include "TestUnit.h"



TestUnit::TestUnit(float x, float y) : Unit (x, y, 5.0, 1.0, 1.0, 100.0, 100.0, 2.0, 0.0, 0.0, 20.0, 50.0, 0.0, 1, 1, false, L"Images/minion.png")
{
}

int TestUnit::getArmorType() {
	return ARMOR_NONE;
}

int TestUnit::getUnitType() {
	return TYPE_BIOLOGICAL;
}

bool TestUnit::isAirUnit() {
	return false;
}

TestUnit::~TestUnit()
{
}
