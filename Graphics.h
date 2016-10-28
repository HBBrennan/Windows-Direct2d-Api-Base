//This file is an interface? for Direct2d
#pragma once
#include <Windows.h>
#include <d2d1.h>
#include "ImageLoader.h"
#include <wincodec.h>

class Graphics
{
	ID2D1Factory* factory;
	ID2D1HwndRenderTarget* renderTarget;
	ID2D1SolidColorBrush* brush;
	IWICImagingFactory* imgFactory;
	ImageLoader* imgLoader;
	ID2D1Bitmap* bitmap;
public:
	Graphics();
	~Graphics();

	bool Init(HWND windowHandle);

	ID2D1RenderTarget* GetRenderTarget()
	{
		return renderTarget;
	}

	void BeginDraw() { renderTarget->BeginDraw(); }
	void EndDraw() { renderTarget->EndDraw(); }

	void ClearScreen(float r, float g, float b);
	void DrawCircle(float x, float y, float radius, float r, float g, float b, float a);
	void DrawImage(float x, float y, float w, float h, ID2D1Bitmap* bitmap);

	ID2D1Bitmap* getBitmap();

	HRESULT loadBitmap(LPWSTR fileName, ID2D1Bitmap** bmp);
};