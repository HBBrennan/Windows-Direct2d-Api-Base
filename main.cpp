#include <Windows.h>
#include "Graphics.h"
#include "MainMenuLevel.h"
#include "GameController.h"
#include "KeyboardListener.h"
#include <chrono>
#include <sstream>

float getDelta();

Graphics* graphics;
KeyboardListener* keyboard;

static const int X_WINDOW_SIZE = 1280;
static const int Y_WINDOW_SIZE = 720;

std::chrono::time_point<std::chrono::high_resolution_clock> lastFrame;
std::chrono::time_point<std::chrono::high_resolution_clock> currentTime;
std::chrono::duration<float> duration;

//Event Handling. If not X button, return rest of stuff.
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	if (uMsg == WM_DESTROY)
	{
		PostQuitMessage(0);
		return 0;
	}

	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE prevInstance, LPWSTR cmd, int nCmdShow)
{
	WNDCLASSEX windowclass{};
	windowclass.cbSize = sizeof(WNDCLASSEX);
	windowclass.hbrBackground = (HBRUSH)COLOR_WINDOW;
	windowclass.hInstance = hInstance;
	windowclass.lpfnWndProc = WindowProc;
	windowclass.lpszClassName = "MainWindow";
	windowclass.style = CS_HREDRAW | CS_VREDRAW;

	RegisterClassEx(&windowclass);

	RECT rect = { 0, 0, X_WINDOW_SIZE, Y_WINDOW_SIZE };
	AdjustWindowRectEx(&rect, WS_OVERLAPPEDWINDOW, false, WS_EX_OVERLAPPEDWINDOW);

	HWND windowHandle = CreateWindowEx(WS_EX_OVERLAPPEDWINDOW, "MainWindow", "TodayistheDay", WS_OVERLAPPEDWINDOW, 100, 100, rect.right - rect.left, rect.bottom - rect.top, NULL, NULL, hInstance, 0);

	if (!windowHandle)
		return -1;

	//Initialize Direct2d
	graphics = new Graphics();
	keyboard = new KeyboardListener();

	if (!graphics->Init(windowHandle))
	{
		delete graphics;
		return -1;
	}

	GameLevel::Init(graphics, keyboard, X_WINDOW_SIZE, Y_WINDOW_SIZE, windowHandle);

	ShowWindow(windowHandle, nCmdShow);

	GameController::LoadInitialLevel(new MainMenuLevel());

	MSG message;
	message.message = WM_NULL;

	float deltaTime = 0.0;
	getDelta();

	while (message.message != WM_QUIT)
	{
		if (PeekMessage(&message, NULL, 0, 0, PM_REMOVE))
			DispatchMessage(&message);
		else
		{
			deltaTime = getDelta();

			//Get Keyboard Info
			keyboard->Update();

			//Update
			GameController::Update(deltaTime);
			
			//Render
			graphics->BeginDraw();
			GameController::Render();
			graphics->EndDraw();
		}
	}

	delete graphics;

	return 0;
}

float getDelta()
{
	currentTime = std::chrono::high_resolution_clock::now();
	duration = currentTime - lastFrame;
	lastFrame = currentTime;
	return duration.count();
}