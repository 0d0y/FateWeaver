#include "D2DTextureSystem.h"
#include "../Engine/Macro.h"

#pragma comment(lib, "windowscodecs.lib")

McCol::D2DTextureSystem* McCol::D2DTextureSystem::m_Instance = nullptr;

McCol::D2DTextureSystem::D2DTextureSystem()
    : m_d2dContext(nullptr)
    , m_ImagingFactory(nullptr)
{
}

McCol::D2DTextureSystem::~D2DTextureSystem()
{
}

ID2D1Bitmap* McCol::D2DTextureSystem::LoadTexture(const std::wstring& strFilePath, std::wstring_view key)
{
	if (const auto bitmap = GetTexture(key))
	{
		return bitmap;
	}

	HRESULT hr = 0;
	IWICBitmapDecoder* pDecoder = nullptr;
	ID2D1Bitmap* pD2DBitmap = nullptr;

	if (SUCCEEDED(hr))
	{
		hr = m_ImagingFactory->CreateDecoderFromFilename(
			strFilePath.c_str(),
			NULL,
			GENERIC_READ,
			WICDecodeMetadataCacheOnDemand,
			&pDecoder
		);
	}

	IWICBitmapFrameDecode* pFrame = NULL;
	if (SUCCEEDED(hr))
	{
		hr = pDecoder->GetFrame(0, &pFrame);
	}

	IWICFormatConverter* pConverter = NULL;
	if (SUCCEEDED(hr))
	{
		hr = m_ImagingFactory->CreateFormatConverter(&pConverter);
	}
	if (SUCCEEDED(hr))
	{
		hr = pConverter->Initialize(
			pFrame,
			GUID_WICPixelFormat32bppPBGRA,
			WICBitmapDitherTypeNone,
			NULL,
			0.f,
			WICBitmapPaletteTypeCustom
		);
	}

	if (SUCCEEDED(hr))
	{
		hr = m_d2dContext->CreateBitmapFromWicBitmap(pConverter, NULL, &pD2DBitmap);
		m_TextureContainer.insert({ key, pD2DBitmap });
	}

	if (pFrame != NULL)
		pFrame->Release();

	if (pConverter != NULL)
		pConverter->Release();

	if (pDecoder != NULL)
		pDecoder->Release();

	return pD2DBitmap;
}

void McCol::D2DTextureSystem::Initialize(ID2D1DeviceContext* d2dContext)
{
	HRESULT hr = S_FALSE;
	m_d2dContext = d2dContext;

	if (SUCCEEDED(hr))
	{
		hr = CoCreateInstance(
			CLSID_WICImagingFactory,
			NULL,
			CLSCTX_INPROC_SERVER,
			IID_PPV_ARGS(&m_ImagingFactory)
		);
	}
}

void McCol::D2DTextureSystem::Finalize()
{
	for(auto& [path, bitmap] : m_TextureContainer)
	{
		bitmap->Release();
		bitmap = nullptr;
	}

	m_TextureContainer.clear();

	SAFE_DELETE(m_Instance)
}

ID2D1Bitmap* McCol::D2DTextureSystem::GetTexture(std::wstring_view key)
{
	if(m_TextureContainer.find(key) != m_TextureContainer.end())
	{
		return m_TextureContainer[key];
	}
	return nullptr;
}

