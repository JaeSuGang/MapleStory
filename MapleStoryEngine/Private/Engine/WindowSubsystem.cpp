#include "EnginePch.h"
#include "Engine/Engine.h"
#include "Engine/WindowSubsystem.h"
#include "Engine/DebugSubsystem.h"
#include "RenderCore/RenderSubsystem.h"

UWindowSubsystem::UWindowSubsystem()
{
    InitializeWCEX();

	string lpszTitle{ "MapleStory" };

    if (!RegisterClassExA(&WCEX))
    {
        CRITICAL_ERROR(ENGINE_INIT_ERROR_TEXT);
    }

    DWORD dwStyle = WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_THICKFRAME;
	RECT WindowSize = { 0, 0, (int)DEFAULT_WINDOW_SIZE_X, (int)DEFAULT_WINDOW_SIZE_Y};
    AdjustWindowRect(&WindowSize, dwStyle, FALSE);

    int nWidth = WindowSize.right - WindowSize.left;
    int nHeight = WindowSize.bottom - WindowSize.top;

	hGameWindow = CreateWindowA(lpszTitle.data(), lpszTitle.data(), dwStyle, 0, 0, nWidth, nHeight, nullptr, nullptr, nullptr, nullptr);

    if (!hGameWindow)
    {
        CRITICAL_ERROR(ENGINE_INIT_ERROR_TEXT);
    }

    ShowWindow(hGameWindow, SW_SHOW);
    UpdateWindow(hGameWindow);
}

void UWindowSubsystem::Tick(float fDeltaTime)
{
    MSG msg{};
    while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
}

HWND UWindowSubsystem::GetWindowHandle() const
{
    return hGameWindow;
}

RECT UWindowSubsystem::GetWindowSize() const
{
    RECT Size;
    GetClientRect(hGameWindow, &Size);
    return Size;
}

void UWindowSubsystem::InitializeWCEX()
{
    WCEX.cbSize = sizeof(WNDCLASSEX);
    WCEX.style = CS_HREDRAW | CS_VREDRAW;
    WCEX.lpfnWndProc = &UWindowSubsystem::WndProc;
    WCEX.cbClsExtra = 0;
    WCEX.cbWndExtra = 0;
    WCEX.hInstance = nullptr;
    WCEX.hIcon = nullptr;
    WCEX.hCursor = LoadCursor(nullptr, IDC_ARROW);
    WCEX.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    WCEX.lpszMenuName = nullptr;
    WCEX.lpszClassName = "MapleStory";
    WCEX.hIconSm = nullptr;
}

LRESULT UWindowSubsystem::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{

#ifdef _DEBUG

    if (GEngine)
        if (UDebugSubsystem* DebugSubsystem = GEngine->DebugSubsystem)
            if (DebugSubsystem->IMGUIWndProcHandler(hWnd, message, wParam, lParam))
                return true;

#endif // _DEBUG

    switch (message)
    {
    case WM_SIZE:
    {
        break;

        if (GEngine && GEngine->RenderSubsystem)
        {

            HRESULT hr{};

            UINT newWidth = LOWORD(lParam);
            UINT newHeight = HIWORD(lParam);

            if (newWidth == 0 || newHeight == 0)
                break;

            URenderSubsystem* RenderSubsystem = GEngine->RenderSubsystem;

            RenderSubsystem->DeviceContext->OMSetRenderTargets(0, nullptr, nullptr);
            RenderSubsystem->DeviceContext->ClearState();
            RenderSubsystem->DeviceContext->Flush();

            RenderSubsystem->BackBuffer = nullptr;
            RenderSubsystem->DepthStencilBuffer = nullptr;
            RenderSubsystem->DefaultDepthStencilState = nullptr;
            RenderSubsystem->RenderTargetView = nullptr;
            RenderSubsystem->DepthStencilView = nullptr;
            RenderSubsystem->RTVtoSRV = nullptr;
            RenderSubsystem->ReadOnlyDepthStencilView = nullptr;

            auto SwapChain = RenderSubsystem->GetSwapChain();

            hr = SwapChain->ResizeBuffers(2, newWidth, newHeight, DXGI_FORMAT_UNKNOWN, 0);
            hr = SwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(RenderSubsystem->BackBuffer.GetAddressOf()));
            hr = RenderSubsystem->Device->CreateRenderTargetView(RenderSubsystem->BackBuffer.Get(), nullptr, RenderSubsystem->RenderTargetView.GetAddressOf());
            RenderSubsystem->CreateDepthStencilView();

            RenderSubsystem->CreateViewport();


            RenderSubsystem->D3D11Debug->ReportLiveDeviceObjects(D3D11_RLDO_FLAGS::D3D11_RLDO_DETAIL);
        }
        break;
    }

    case WM_QUIT:
    case WM_CLOSE:
    case WM_DESTROY:
        GEngine->Terminate();
        [[fallthrough]];

    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

void UWindowSubsystem::LateInit()
{

}

