#pragma once
#include "windows.h"

class KeyboardListener
{
	unsigned char* keys;
public:
	KeyboardListener();
	~KeyboardListener();

	bool isKeyDown(int key) const;
	bool isMouse1Down() const;
	bool isMouse2Down() const;
	POINT* getMousePos(HWND window);
	void Update();
};

