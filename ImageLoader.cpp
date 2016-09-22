#include "ImageLoader.h"
#define SafeRelease(p) { if ( (p) ) { (p)->Release(); (p) = 0; } }


ImageLoader::ImageLoader()
{
}


ImageLoader::~ImageLoader()
{
}


HRESULT ImageLoader::getBitmapFromFile(LPWSTR fileName, ID2D1RenderTarget* renderTarget, IWICImagingFactory* factory, ID2D1Bitmap** bitmap)
{
	IWICBitmapDecoder* decoder = NULL;
	IWICBitmapFrameDecode* source = NULL;
	IWICStream* stream = NULL;
	IWICFormatConverter* converter = NULL;

	HRESULT hr = factory->CreateDecoderFromFilename(fileName, NULL, GENERIC_READ, WICDecodeMetadataCacheOnLoad, &decoder);

	if (SUCCEEDED(hr))
	{
		//Create the initial frame.
		hr = decoder->GetFrame(0, &source);
	}

	if (SUCCEEDED(hr))
	{
		//Convert the image format to 32bppPBGRA
		// (DXGI_FORMAT_B8G8R8A8_UNIFORM + D2D1_ALPHA_MODE_PREMULTIPLIED).
		hr = factory->CreateFormatConverter(&converter);
	}

	if (SUCCEEDED(hr))
	{
		hr = converter->Initialize(source, GUID_WICPixelFormat32bppPBGRA, WICBitmapDitherTypeNone, NULL, 0.0f, WICBitmapPaletteTypeMedianCut);
	}

	if (SUCCEEDED(hr))
	{
		//Create a Direct2D bitmap from the WIC bitmap.
		hr = renderTarget->CreateBitmapFromWicBitmap(converter, NULL, bitmap);
	}

	SafeRelease(decoder);
	SafeRelease(source);
	SafeRelease(stream);
	SafeRelease(converter);

	return hr;
}