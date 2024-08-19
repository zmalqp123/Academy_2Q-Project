#include "pch.h"
#include "D2DRenderer.h"
#pragma comment(lib, "Dxgi.lib")

bool D2DRenderer::InitDirect2D(HWND hWnd)
{
    HRESULT hr;
    hr = CoInitialize(NULL);
    if (FAILED(hr)) return false;

    hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &_D2DFactory);
    if (FAILED(hr)) return false;

    RECT rc;
    GetClientRect(hWnd, &rc);

    hr = _D2DFactory->CreateHwndRenderTarget(
        D2D1::RenderTargetProperties(),
        D2D1::HwndRenderTargetProperties(
            hWnd,
            D2D1::SizeU(rc.right - rc.left, rc.bottom - rc.top)
        ),
        &_RenderTarget
    );
    if (FAILED(hr)) return false;

    if (SUCCEEDED(hr))
    {
        // Create WIC factory
        hr = CoCreateInstance(
            CLSID_WICImagingFactory,
            NULL,
            CLSCTX_INPROC_SERVER,
            IID_PPV_ARGS(&g_pWICFactory)
        );
    }

    if (SUCCEEDED(hr))
    {
        hr = CreateD2DBitmapFromFile(L"../Resource/atk_1.png", &g_pD2DBitmap);
    }

    // DirectWrite 팩터리를 만듭니다.
    hr = DWriteCreateFactory(
        DWRITE_FACTORY_TYPE_SHARED,
        __uuidof(g_pDWriteFactory),
        reinterpret_cast<IUnknown**>(&g_pDWriteFactory));

    if (FAILED(hr))
        return FALSE;

    // DirectWrite 텍스트 형식 개체를 만듭니다.
    hr = g_pDWriteFactory->CreateTextFormat(
        L"Bodoni", // FontName    제어판-모든제어판-항목-글꼴-클릭 으로 글꼴이름 확인가능
        NULL,
        DWRITE_FONT_WEIGHT_NORMAL,
        DWRITE_FONT_STYLE_NORMAL,
        DWRITE_FONT_STRETCH_NORMAL,
        50.0f,   // Font Size
        L"ko-KR", //locale
        &g_pDWriteTextFormat
    );
    if (FAILED(hr))
        return FALSE;
    // 텍스트를 수평 및 수직으로 중앙에 맞춥니다.
    g_pDWriteTextFormat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_LEADING);
    g_pDWriteTextFormat->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_NEAR);


    if (FAILED(hr))
    {
        _com_error err(hr);
        ::MessageBox(hWnd, err.ErrorMessage(), L"FAILED", MB_OK);
        return false;
    }

    if (SUCCEEDED(hr)) {
        // Create a brush.
        _RenderTarget->CreateSolidColorBrush(
            D2D1::ColorF(D2D1::ColorF::Black),
            &g_brush
        );
    }

    // VRAM 정보얻기 위한 개체 생성
    if (SUCCEEDED(hr))
    {
        // Create DXGI factory
        hr = CreateDXGIFactory1(__uuidof(IDXGIFactory4), (void**)&m_pDXGIFactory);
    }
    if (SUCCEEDED(hr))
    {
        m_pDXGIFactory->EnumAdapters(0, reinterpret_cast<IDXGIAdapter**>(&m_pDXGIAdapter));
    }

    return true;
}

void D2DRenderer::UnInitDirect2D()
{
    if (g_pDWriteTextFormat) g_pDWriteTextFormat->Release();
    if (g_pDWriteFactory) g_pDWriteFactory->Release();

    if (g_brush) g_brush->Release();
    if (g_pWICFactory) g_pWICFactory->Release();

    if (_RenderTarget) _RenderTarget->Release();
    if (_D2DFactory) _D2DFactory->Release();

    if (m_pDXGIFactory) m_pDXGIFactory->Release();
    if (m_pDXGIAdapter) m_pDXGIAdapter->Release();

    CoUninitialize();
}

void D2DRenderer::BeginDraw()
{
    _RenderTarget->BeginDraw();

}

void D2DRenderer::Clear(D2D1::ColorF color)
{
    _RenderTarget->Clear(D2D1::ColorF(color));
    //_RenderTarget->SetTransform(D2D1::Matrix3x2F::Identity());
}

void D2DRenderer::Render()
{
    /*_RenderTarget->FillEllipse({ { 1.f, 1.f }, 0.01f, 0.01f }, g_brush);
    _RenderTarget->FillRectangle({ 50.5f, 50.5f, 20.5f, 20.5f }, white_brush);*/
}

void D2DRenderer::EndDraw()
{
    _RenderTarget->EndDraw();
}

void D2DRenderer::DrawRectangle(float x1, float y1, float x2, float y2, D2D1::ColorF color)
{
    HRESULT hr = _RenderTarget->CreateSolidColorBrush(color, &g_brush);
    if(SUCCEEDED(hr))
        _RenderTarget->FillRectangle({ x1, y1, x2, y2 }, g_brush);
}

void D2DRenderer::DrawLine(D2D1_POINT_2F p0, D2D1_POINT_2F p1, float width, D2D1::ColorF color, D2D1_MATRIX_3X2_F transform) {
    _RenderTarget->SetTransform(D2D1::Matrix3x2F::Identity());
    _RenderTarget->SetTransform(transform);
    HRESULT hr = _RenderTarget->CreateSolidColorBrush(color, &g_brush);
    if (SUCCEEDED(hr))
        _RenderTarget->DrawLine(p0, p1, g_brush, width);
}

void D2DRenderer::DrawHollowRectangle(float x1, float y1, float x2, float y2, float width, D2D1::ColorF color)
{
    if (g_brush != nullptr)
        g_brush->Release();
    HRESULT hr = _RenderTarget->CreateSolidColorBrush(color, &g_brush);
    if (SUCCEEDED(hr)) {
        _RenderTarget->DrawLine({x1, y1}, {x2, y1}, g_brush, width);
        _RenderTarget->DrawLine({x2, y1}, {x2, y2}, g_brush, width);
        _RenderTarget->DrawLine({x2, y2}, {x1, y2}, g_brush, width);
        _RenderTarget->DrawLine({x1, y2}, {x1, y1}, g_brush, width);
    }
}

void D2DRenderer::DrawCircle(float x, float y, float radius, D2D1::ColorF color)
{
    if (g_brush != nullptr)
        g_brush->Release();
    HRESULT hr = _RenderTarget->CreateSolidColorBrush(color, &g_brush);
    _RenderTarget->DrawEllipse({ D2D1::Point2F(0.f, 0.f),
    radius,
    radius }, g_brush);
}

HRESULT D2DRenderer::CreateD2DBitmapFromFile(const WCHAR* szFilePath, ID2D1Bitmap** ppID2D1Bitmap)
{
    HRESULT hr;
    // Create a decoder
    IWICBitmapDecoder* pDecoder = NULL;
    IWICFormatConverter* pConverter = NULL;

    hr = g_pWICFactory->CreateDecoderFromFilename(
        szFilePath,                      // Image to be decoded
        NULL,                            // Do not prefer a particular vendor
        GENERIC_READ,                    // Desired read access to the file
        WICDecodeMetadataCacheOnDemand,  // Cache metadata when needed
        &pDecoder                        // Pointer to the decoder
    );

    // Retrieve the first frame of the image from the decoder
    IWICBitmapFrameDecode* pFrame = NULL;
    if (SUCCEEDED(hr))
    {
        hr = pDecoder->GetFrame(0, &pFrame);
    }

    //Step 3: Format convert the frame to 32bppPBGRA
    if (SUCCEEDED(hr))
    {
        hr = g_pWICFactory->CreateFormatConverter(&pConverter);
    }

    if (SUCCEEDED(hr))
    {
        hr = pConverter->Initialize(
            pFrame,                          // Input bitmap to convert
            GUID_WICPixelFormat32bppPBGRA,   // Destination pixel format
            WICBitmapDitherTypeNone,         // Specified dither pattern
            NULL,                            // Specify a particular palette 
            0.f,                             // Alpha threshold
            WICBitmapPaletteTypeCustom       // Palette translation type
        );
    }

    if (SUCCEEDED(hr))
    {
        hr = _RenderTarget->CreateBitmapFromWicBitmap(pConverter, NULL, ppID2D1Bitmap);
    }


    // 파일을 사용할때마다 다시 만든다.
    if (pConverter)
        pConverter->Release();

    if (pDecoder)
        pDecoder->Release();

    if (pFrame)
        pFrame->Release();

    return hr;
}


void D2DRenderer::DrawBitmap(ID2D1Bitmap* pBitmap, D2D1_MATRIX_3X2_F transform)
{
   /* _RenderTarget->SetTransform(D2D1::Matrix3x2F::Identity());
    D2D1_VECTOR_2F pos{ 0,0 };
    D2D1_SIZE_F size = g_pD2DBitmap->GetSize();
    D2D1_RECT_F rect = { pos.x , pos.y, pos.x + size.width * 1.5f,pos.y + size.height * 1.5f };
    _RenderTarget->DrawBitmap(g_pD2DBitmap, rect);*/


    _RenderTarget->SetTransform(transform);
    _RenderTarget->DrawBitmap(pBitmap);


  /*  D2D1_MATRIX_3X2_F Matrix = D2D1::Matrix3x2F::Scale(-1.0f, 1.0f, D2D1::Point2F(0, 0));
    _RenderTarget->SetTransform(D2D1::Matrix3x2F::Identity());*/
}

void D2DRenderer::DrawStringText(const WCHAR* _text)
{
    D2D1_SIZE_F size = _RenderTarget->GetSize();

    std::wstring text = _text;
    //WCHAR sc_helloWorld[] = L"안녕!, 세계! Abg\n 어암ㅈ암장\n ㅇhagth";
    _RenderTarget->DrawText(
        text.c_str(),
        text.size(), //ARRAYSIZE(sc_helloWorld) - 1,
        g_pDWriteTextFormat,
        D2D1::RectF(60, 0, size.width, size.height),
        g_brush
    );
}

void D2DRenderer::DrawStringTextw(const WCHAR* _text, D2D1_MATRIX_3X2_F transform, D2D1::ColorF color)
{
    if (g_brush != nullptr)
        g_brush->Release();
    HRESULT hr = _RenderTarget->CreateSolidColorBrush(color, &g_brush);
    //g_brush->SetColor(color);

    _RenderTarget->SetTransform(transform);
    D2D1_SIZE_F size = _RenderTarget->GetSize();

    std::wstring text = _text;
    //WCHAR sc_helloWorld[] = L"안녕!, 세계! Abg\n 어암ㅈ암장\n ㅇhagth";
    _RenderTarget->DrawText(
        text.c_str(),
        text.size(), //ARRAYSIZE(sc_helloWorld) - 1,
        g_pDWriteTextFormat,
        D2D1::RectF(60, 0, size.width, size.height),
        g_brush
    );
}

size_t D2DRenderer::GetUsedVRAM()
{
    DXGI_QUERY_VIDEO_MEMORY_INFO videoMemoryInfo;
    m_pDXGIAdapter->QueryVideoMemoryInfo(0, DXGI_MEMORY_SEGMENT_GROUP_LOCAL, &videoMemoryInfo);
    return videoMemoryInfo.CurrentUsage;// / 1024 / 1024;
}
