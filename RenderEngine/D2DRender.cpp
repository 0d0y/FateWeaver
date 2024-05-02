// D2DRender.cpp : 정적 라이브러리를 위한 함수를 정의합니다.
#include "D2DRender.h"

#include <d3d11.h>
#include <dwrite.h>
#include <tchar.h>
#include <wrl/client.h>
#include <exception>
#include <dxgi1_2.h>

using namespace Microsoft::WRL;

#pragma comment(lib, "d2d1.lib")
#pragma comment(lib, "dwrite.lib")
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "windowscodecs.lib")

McCol::D2DRender::D2DRender()
    : m_hWnd(nullptr)
    , m_dpi(0)
    , m_formatIndex(0)

{
}

McCol::D2DRender::~D2DRender()
{
}

bool McCol::D2DRender::InitWriteFactory()
{
    // DWrite 팩토리 생성
    DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED, __uuidof(IDWriteFactory), reinterpret_cast<IUnknown**>(&m_pDWriteFactory));

    HRESULT hr;

    // 텍스트 포맷 생성 및 설정
    hr = m_pDWriteFactory->CreateTextFormat(
        L"광양햇살체",     // 폰트 패밀리 이름
        nullptr,      // 폰트 컬렉션
        DWRITE_FONT_WEIGHT_REGULAR,    // 폰트 두께
        DWRITE_FONT_STYLE_NORMAL,     // 폰트 스타일
        DWRITE_FONT_STRETCH_NORMAL,   // 폰트 스트레치
        24.f,        // 폰트 크기
        L"en-us",     // 로캘
        &m_pDWriteTextFormat
    );

    m_pDWriteTextFormat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER);
    m_pDWriteTextFormat->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);

    return false;
}

bool McCol::D2DRender::Initialize(HWND hWnd)
{
    HRESULT hr;
    m_hWnd = hWnd;

    // COM사용
    hr = CoInitialize(NULL);
    if (SUCCEEDED(hr))
    {
        // 렌더타겟을 만들 수 있는 팩토리 객체를 생성하고 인터페이스 포인터를 얻어온다.
        hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &m_d2dFactory);
    }

    if (SUCCEEDED(hr))
    {
        // 이미 윈도우가 만들어진 상태에서 윈도우 사이즈를 구한다.
        RECT rc;
        GetClientRect(hWnd, &rc);
        D2D1_SIZE_U size = D2D1::SizeU(
            static_cast<UINT>(rc.right - rc.left),
            static_cast<UINT>(rc.bottom - rc.top)
        );
    }

    if (SUCCEEDED(hr))
    {
        hr = DWriteCreateFactory(
            DWRITE_FACTORY_TYPE_SHARED,
            __uuidof(m_pDWriteFactory),
            reinterpret_cast<IUnknown**>(&m_pDWriteFactory)
        );
    }

    InitWriteFactory();
    InitD3D();

    if (SUCCEEDED(hr))
    {
        hr = m_d2dContext->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Gray), &m_pGrayBrush);
    }
    if (SUCCEEDED(hr))
    {
        hr = m_d2dContext->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::White), &m_pWhiteBrush);
    }

    if (SUCCEEDED(hr))
    {
        hr = m_d2dContext->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Black), &m_pBlackBrush);
    }
    if (SUCCEEDED(hr))
    {
        hr = m_d2dContext->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Yellow), &m_pYellowBrush);
    }
    if (SUCCEEDED(hr))
    {
        hr = m_d2dContext->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Red), &m_pRedBrush);
    }
    if (SUCCEEDED(hr))
    {
        hr = m_d2dContext->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Green), &m_pGreenBrush);
    }
    if (SUCCEEDED(hr))
    {
        hr = m_d2dContext->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Blue), &m_pBlueBrush);
    }

    return true;
}

void McCol::D2DRender::Finalize() const
{
    if (m_pDWriteTextFormat != NULL) m_pDWriteTextFormat->Release();
    if (m_pDWriteFactory != NULL) m_pDWriteFactory->Release();

    if (m_pYellowBrush != NULL) m_pYellowBrush->Release();
    if (m_pWhiteBrush != NULL) m_pWhiteBrush->Release();
    if (m_pBlackBrush != NULL) m_pBlackBrush->Release();
    if (m_pGrayBrush != NULL) m_pGrayBrush->Release();
    if (m_pRedBrush != NULL) m_pRedBrush->Release();
    if (m_pGreenBrush != NULL) m_pGreenBrush->Release();
    if (m_pBlueBrush != NULL) m_pBlueBrush->Release();

    if (m_d2dContext != NULL) m_d2dContext->Release();
    if (m_d2dFactory != NULL) m_d2dFactory->Release();
    if (m_d2dDevice != NULL) m_d2dDevice->Release();

    if (m_d2dTargetBitmap != NULL) m_d2dTargetBitmap->Release();
    if (m_dxgiDevice != NULL) m_dxgiDevice->Release();
    if (m_dxgiFactory != NULL) m_dxgiFactory->Release();
    if (m_dxgiAdapter != NULL) m_dxgiAdapter->Release();

    // todo : BrushMap Release

    CoUninitialize();
}

namespace DX
{
    inline void ThrowIfFailed(HRESULT hr)
    {
        if (FAILED(hr))
        {
            // Set a breakpoint on this line to catch DirectX API errors
            throw std::exception();
        }
    }
}

void McCol::D2DRender::InitD3D()
{
    UINT creationFlags = D3D11_CREATE_DEVICE_BGRA_SUPPORT;

    D3D_FEATURE_LEVEL featureLevels[] =
    {
        D3D_FEATURE_LEVEL_11_1,
        D3D_FEATURE_LEVEL_11_0,
        D3D_FEATURE_LEVEL_10_1,
        D3D_FEATURE_LEVEL_10_0,
        D3D_FEATURE_LEVEL_9_3,
        D3D_FEATURE_LEVEL_9_2,

        D3D_FEATURE_LEVEL_9_1
    };

    D3D_FEATURE_LEVEL m_featureLevel;

    DX::ThrowIfFailed(
        D3D11CreateDevice(
            nullptr,                    // specify null to use the default adapter
            D3D_DRIVER_TYPE_HARDWARE,
            0,
            creationFlags,              // optionally set debug and Direct2D compatibility flags
            featureLevels,              // list of feature levels this app can support
            ARRAYSIZE(featureLevels),   // number of possible feature levels
            D3D11_SDK_VERSION,
            &m_d3dDevice,                    // returns the Direct3D device created
            &m_featureLevel,            // returns feature level of device created
            &m_d3dContext                    // returns the device immediate context
        )
    );

    DX::ThrowIfFailed(
        CreateDXGIFactory1(__uuidof(IDXGIFactory1), reinterpret_cast<void**>(&m_dxgiFactory))
    );

    DX::ThrowIfFailed(
        m_dxgiFactory->EnumAdapters(0, &m_dxgiAdapter)
    );

    DX::ThrowIfFailed(
        m_d3dDevice->QueryInterface(__uuidof(IDXGIDevice), reinterpret_cast<void**>(&m_dxgiDevice))
    );

    ComPtr<IDXGIDevice1> dxgiDevice;
    // Obtain the underlying DXGI device of the Direct3D11 device.
    DX::ThrowIfFailed(
        m_d3dDevice.As(&dxgiDevice)
    );

    // Obtain the Direct2D device for 2-D rendering.
    DX::ThrowIfFailed(
        m_d2dFactory->CreateDevice(dxgiDevice.Get(), &m_d2dDevice)
    );

    // Get Direct2D device's corresponding device context object.
    DX::ThrowIfFailed(
        m_d2dDevice->CreateDeviceContext(
            D2D1_DEVICE_CONTEXT_OPTIONS_NONE,
            &m_d2dContext
        )
    );

    // 스왑 체인 기본 설정
    DXGI_SWAP_CHAIN_DESC1 swapChainDesc = {};
    swapChainDesc.BufferCount = 2;                                   // 두 개의 백 버퍼를 사용합니다.
    swapChainDesc.Width = 0;                                         // 자동 크기 조정
    swapChainDesc.Height = 0;                                        // 자동 크기 조정
    swapChainDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;              // 가장 일반적인 스왑 체인 포맷
    swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;     // 백 버퍼는 렌더 타겟으로 사용됩니다.
    swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_SEQUENTIAL;     // Flip 모델을 사용합니다.
    swapChainDesc.SampleDesc.Count = 1;                              // 멀티샘플링을 사용하지 않습니다.

    // Identify the physical adapter (GPU or card) this device is runs on.
    ComPtr<IDXGIAdapter> dxgiAdapter;
    DX::ThrowIfFailed(
        dxgiDevice->GetAdapter(&dxgiAdapter)
    );

    // Get the factory object that created the DXGI device.
    ComPtr<IDXGIFactory2> dxgiFactory;
    DX::ThrowIfFailed(
        dxgiAdapter->GetParent(IID_PPV_ARGS(&dxgiFactory))
    );

    // 스왑 체인 생성
    DX::ThrowIfFailed(
        dxgiFactory->CreateSwapChainForHwnd(m_d3dDevice.Get(), m_hWnd, &swapChainDesc, nullptr, nullptr, &m_SwapChain)
    );

    // Ensure that DXGI doesn't queue more than one frame at a time.
    DX::ThrowIfFailed(
        dxgiDevice->SetMaximumFrameLatency(1)
    );

    // Get the backbuffer for this window which is be the final 3D render target.
    ComPtr<ID3D11Texture2D> backBuffer;
    DX::ThrowIfFailed(
        m_SwapChain->GetBuffer(0, IID_PPV_ARGS(&backBuffer))
    );

    D2D1_BITMAP_PROPERTIES1 bitmapProperties =
        D2D1::BitmapProperties1(
            D2D1_BITMAP_OPTIONS_TARGET | D2D1_BITMAP_OPTIONS_CANNOT_DRAW,
            D2D1::PixelFormat(DXGI_FORMAT_B8G8R8A8_UNORM, D2D1_ALPHA_MODE_IGNORE),
            m_dpi,
            m_dpi
        );

    // Direct2D needs the dxgi version of the backbuffer surface pointer.
    ComPtr<IDXGISurface> dxgiBackBuffer;
    DX::ThrowIfFailed(
        m_SwapChain->GetBuffer(0, IID_PPV_ARGS(&dxgiBackBuffer))
    );

    // Get a D2D surface from the DXGI back buffer to use as the D2D render target.
    DX::ThrowIfFailed(
        m_d2dContext->CreateBitmapFromDxgiSurface(
            dxgiBackBuffer.Get(),
            &bitmapProperties,
            &m_d2dTargetBitmap
        )
    );

    // Now we can set the Direct2D render target.
    m_d2dContext->SetTarget(m_d2dTargetBitmap);
}

ID2D1SolidColorBrush* McCol::D2DRender::GetBrush(D2D1::ColorF::Enum colorEnum)
{
    // 브러시 맵에서 해당 색상의 브러시를 찾습니다.
    auto it = m_BrushMap.find(colorEnum);

    if (it != m_BrushMap.end()) {
        // 브러시가 이미 있으면 반환합니다.
        return it->second;
    }
    else {
        // 브러시가 없으면 새로 만듭니다.
        ID2D1SolidColorBrush* newBrush;
        D2D1::ColorF color = static_cast<D2D1::ColorF>(colorEnum); // Enum 값을 실제 색상으로 변환
        HRESULT hr = m_d2dContext->CreateSolidColorBrush(color, &newBrush); // 렌더 타겟에서 브러시 생성
        if (SUCCEEDED(hr)) {
            m_BrushMap[colorEnum] = newBrush; // 브러시 맵에 추가
            return newBrush;
        }
        else {
            // 브러시 생성 실패 처리
            return nullptr;
        }
    }
}







