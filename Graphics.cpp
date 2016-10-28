#include "Graphics.h"
#include <string>
#include <sstream>

//Constructor for Graphics class. Initializes Directx2D factory and the rendering target window as NULL to be a known value
Graphics::Graphics()
{
	factory = NULL;
	renderTarget = NULL;
	brush = NULL;
	imgFactory = NULL;
	imgLoader = NULL;
	bitmap = NULL;
}

//Destructor for Graphics class
Graphics::~Graphics()
{
	if (factory) factory->Release();
	if (renderTarget) renderTarget->Release();
	if (brush) brush->Release();
	if (imgFactory) imgFactory->Release();
	if (imgLoader) delete imgLoader;
	if (bitmap) bitmap->Release();
}

//Initializes the Direct2D Factory and Render target using the passed window handler. Returns whether initialization succeeded
bool Graphics::Init(HWND windowHandle)
{
	OutputDebugString("Initializing...\n");
	HRESULT res = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &factory);
	if (res != S_OK)
		return false;

	RECT rect;
	GetClientRect(windowHandle, &rect);

	res = factory->CreateHwndRenderTarget(
		D2D1::RenderTargetProperties(),
		D2D1::HwndRenderTargetProperties(
			windowHandle, D2D1::SizeU(rect.right, rect.bottom)),
			&renderTarget);

	if (res != S_OK)
		return false;

	res = renderTarget->CreateSolidColorBrush(D2D1::ColorF(0, 0, 0, 0), &brush);

	if (res != S_OK)
		return false;

	OutputDebugString("Creating Imaging Factory...\n");

	CoInitialize(NULL);
	res = CoCreateInstance(CLSID_WICImagingFactory, NULL, CLSCTX_INPROC_SERVER, IID_IWICImagingFactory, (LPVOID*)&imgFactory);

	if (res != S_OK)
		return false;


	OutputDebugString("Loading Image...\n");

	//test stuff
	imgLoader = new ImageLoader();

	if (res != S_OK)
		return false;

	OutputDebugString("Image Loaded\n");

	return true;
}

void Graphics::ClearScreen(float r, float g, float b)
{
	renderTarget->Clear(D2D1::ColorF(r, g, b));
}

void Graphics::DrawCircle(float x, float y, float radius, float r, float g, float b, float a)
{
	brush->SetColor(D2D1::ColorF(r, g, b, a));
	renderTarget->FillEllipse(D2D1::Ellipse(D2D1::Point2F(x, y), radius, radius), brush);
}

void Graphics::DrawImage(float x, float y, float w, float h, ID2D1Bitmap* bitmap) {
	D2D1_SIZE_F size = bitmap->GetSize();
	renderTarget->DrawBitmap(bitmap, &D2D1::RectF(x, y, x + w, y + h), 1.0f, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, &D2D1::RectF(0, 0, size.width, size.height));
}

ID2D1Bitmap* Graphics::getBitmap()
{
	return bitmap;
}

HRESULT Graphics::loadBitmap(LPWSTR fileName, ID2D1Bitmap** bmp)
{
	HRESULT res = imgLoader->getBitmapFromFile(fileName, renderTarget, imgFactory, bmp);

	return res;
}