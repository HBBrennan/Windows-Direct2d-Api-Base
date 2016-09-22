#include "TestLevel.h"

Minion* ground;
Unit* testUnit;
Unit* testUnit2;

bool lastMouseState = false;
bool lastRightMouseState = false;
POINT* boxStart;
POINT* boxEnd;
bool dragging = false;

std::vector<Unit*> gameUnits;
std::vector<Unit*> selected;

void TestLevel::Load()
{
	ground = bgMinions->addObject(new Minion(L"Images/Grey-Texture.jpg"));
	testUnit = new TestUnit(0, 0);
	testUnit2 = new TestUnit(200, 0);
	fgMinions->addObject(testUnit);
	fgMinions->addObject(testUnit2);
	gameUnits.push_back(testUnit);
	gameUnits.push_back(testUnit2);

	loadMinions();

	float scaleFactor = GameLevel::getWindowY() / ground->getHeight();
	ground->scaleObject(scaleFactor * 2, scaleFactor * 2);

	xOffset = 0;
	yOffset = 0;

}

void TestLevel::Unload()
{
	GameLevel::Unload();
}

void TestLevel::Render()
{
	gfx->ClearScreen(0.0f, 0.0f, 0.0f);

	renderMinions(xOffset, yOffset);

	for (unsigned int i = 0; i < gameUnits.size(); i++) {
		Unit* u = gameUnits.at(i);

		if (u->isSelected()) {
			float x = u->getCenterX();
			float y = u->getCenterY();

			gfx->DrawCircle(x, GameLevel::getWindowY() - y, 100, 0, 1, 0, .5);
		}
	}

	if (dragging)
		gfx->DrawBox(boxStart->x, GameLevel::getWindowY() - boxStart->y, boxEnd->x, GameLevel::getWindowY() - boxEnd->y, 0.0f, 1.0f, 0.0f, 0.75f);
}

void TestLevel::Update(float deltaTime)
{
	updateMinions(deltaTime, kbd);

	checkMouseDrag();
	checkRightClick();
}

void TestLevel::checkRightClick()
{
	bool currentRightMouseState = kbd->isMouse2Down();

	if (!lastRightMouseState && currentRightMouseState) {
		for (unsigned int i = 0; i < selected.size(); i++) {
			Unit* u = selected.at(i);

			POINT* p = kbd->getMousePos(window);
			u->setMoveLocation(p->x, p->y);
		}
	}

	lastRightMouseState = currentRightMouseState;
}

void TestLevel::checkMouseDrag() {
	bool currentMouseState = kbd->isMouse1Down();

	if (dragging) {
		if (currentMouseState) {
			POINT* p = kbd->getMousePos(window);
			boxEnd = new POINT();
			boxEnd->x = p->x;
			boxEnd->y = p->y;
		}
		else {
			selectArea(boxStart, boxEnd);
			boxStart = NULL;
			boxEnd = NULL;
			dragging = false;
		}
	}
	else {
		if (!lastMouseState && currentMouseState) { //Drag Begin
			POINT* p = kbd->getMousePos(window);
			boxStart = new POINT();
			boxEnd = new POINT();

			boxStart->x = p->x;
			boxStart->y = p->y;
			boxEnd->x = p->x;
			boxEnd->y = p->y;

			dragging = true;
		}
	}

	lastMouseState = currentMouseState;
}

void TestLevel::selectArea(POINT* start, POINT* end) {
	//To be implemented later
	for (unsigned int i = 0; i < selected.size(); i++) {
		Unit* u = selected.at(i);
		u->deselect();
	}

	selected.clear();

	for (unsigned int i = 0; i < gameUnits.size(); i++) {
		Unit* u = gameUnits.at(i);

		float x = u->getCenterX();
		float y = u->getCenterY();

		int top = max(start->y, end->y);
		int left = min(start->x, end->x);
		int bottom = min(start->y, end->y);
		int right = max(start->x, end->x);

		if ((x >= left && x <= right) && (y <= top && y >= bottom)) {
			selected.push_back(u);
			u->select();
		}
	}
}