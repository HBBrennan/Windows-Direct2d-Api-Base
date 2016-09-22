#include "KeyboardListener.h"

KeyboardListener::KeyboardListener()
{
	keys = new unsigned char[256];
}


KeyboardListener::~KeyboardListener()
{
	keys = NULL;
}

void KeyboardListener::Update()
{
	GetKeyboardState(keys);
}

bool KeyboardListener::isKeyDown(int key) const
{
	return (keys[key] & 0b10000000) > 0;
}

bool KeyboardListener::isMouse1Down() const
{
	return isKeyDown(VK_LBUTTON);
}

bool KeyboardListener::isMouse2Down() const
{
	return isKeyDown(VK_RBUTTON);
}

POINT* KeyboardListener::getMousePos(HWND window)
{
	POINT* p = new POINT();
	GetCursorPos(p);
	ScreenToClient(window, p);
	LPRECT rect = new RECT();
	GetClientRect(window, rect);
	p->y = (rect->bottom - rect->top) - p->y;

	return p;
}