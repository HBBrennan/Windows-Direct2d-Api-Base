#pragma once
#include <d2d1.h>
#include <iostream>
#include <wincodec.h>

class ImageLoader
{
public:
	ImageLoader();
	~ImageLoader();

	HRESULT getBitmapFromFile(LPWSTR fileName, ID2D1RenderTarget* renderTarget, IWICImagingFactory* factory, ID2D1Bitmap** bitmap);

	void Release();
};

