#pragma once

#include <d2d1_1.h>
#include <d3d11.h>
#include <dxgi1_2.h>
#include <wrl/client.h>

#include <wincodec.h>
#include <string>
#include <unordered_map>

#define TEXT_LENGTH(T) static_cast<UINT32>(wcslen(T))

namespace McCol
{
    class Vector2;

    class D2DRender
	{
	public:
		D2DRender();
		~D2DRender();
		static D2DRender* m_pInstance;

	private:
		HWND m_hWnd;

		// d2d
		ID2D1Device* m_d2dDevice = nullptr;
		ID2D1DeviceContext* m_d2dContext = nullptr;
		ID2D1Factory1* m_d2dFactory = nullptr;

		// Brush
		ID2D1SolidColorBrush* m_pGrayBrush = nullptr;
		ID2D1SolidColorBrush* m_pBlackBrush = nullptr;
		ID2D1SolidColorBrush* m_pYellowBrush = nullptr;
		ID2D1SolidColorBrush* m_pWhiteBrush = nullptr;
		ID2D1SolidColorBrush* m_pRedBrush = nullptr;
		ID2D1SolidColorBrush* m_pGreenBrush = nullptr;
		ID2D1SolidColorBrush* m_pBlueBrush = nullptr;

		// Text
		IDWriteFactory* m_pDWriteFactory = nullptr;
		IDWriteTextFormat* m_pDWriteTextFormat;

		// for ImGui
		ID2D1Bitmap1* m_d2dTargetBitmap = nullptr;
		IDXGIDevice* m_dxgiDevice = nullptr;
		IDXGIFactory* m_dxgiFactory = nullptr;
		IDXGIAdapter* m_dxgiAdapter = nullptr;

		float m_dpi;

		Microsoft::WRL::ComPtr<IDXGISwapChain1> m_SwapChain;
		Microsoft::WRL::ComPtr <ID3D11Device> m_d3dDevice;
		Microsoft::WRL::ComPtr <ID3D11DeviceContext> m_d3dContext;

		std::unordered_map<D2D1::ColorF::Enum, ID2D1SolidColorBrush*> m_BrushMap;

		int m_formatIndex;

	public:
		bool Initialize(HWND hWnd);
		void Finalize() const;

	private:
		bool InitWriteFactory();
		void InitD3D();

	public: // for d2d
		ID2D1DeviceContext* GetContext() { return m_d2dContext; }

		IDWriteFactory* GetDWriteFactory() { return m_pDWriteFactory; }
		IDWriteTextFormat* GetDWriteTextFormat() { return m_pDWriteTextFormat; }

		ID2D1SolidColorBrush* GetBrush(D2D1::ColorF::Enum colorEnum);

		ID2D1SolidColorBrush* GetYellowBrush() { return m_pYellowBrush; }
		ID2D1SolidColorBrush* GetBlackBrush() { return m_pBlackBrush; }
		ID2D1SolidColorBrush* GetGrayBrush() { return m_pGrayBrush; }
		ID2D1SolidColorBrush* GetWhiteBrush() { return m_pWhiteBrush; }
		ID2D1SolidColorBrush* GetRedBrush() { return m_pRedBrush; }
		ID2D1SolidColorBrush* GetGreenBrush() { return m_pGreenBrush; }
		ID2D1SolidColorBrush* GetBlueBrush() { return m_pBlueBrush; }
		Microsoft::WRL::ComPtr<IDXGISwapChain> GetSwapChain() { return m_SwapChain; }

	public: // for ImGui
		ID3D11DeviceContext* GetContext3D() { return m_d3dContext.Get(); }
		ID3D11Device* GetDevice3D() { return m_d3dDevice.Get(); }
	};

}