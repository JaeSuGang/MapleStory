#include "EnginePch.h"
#include "Engine/Engine.h"
#include "Engine/WindowSubsystem.h"

UWindowSubsystem::UWindowSubsystem()
{
    InitializeWCEX();

	string lpszTitle{ "MapleStory" };

    if (!RegisterClassExA(&WCEX))
    {
        CRITICAL_ERROR("오류");
    }

	hGameWindow = CreateWindowA(lpszTitle.data(), lpszTitle.data(), WS_OVERLAPPED | WS_SYSMENU | WS_MINIMIZEBOX, 0, 0, CW_USEDEFAULT, 0, nullptr, nullptr, nullptr, nullptr);

    if (!hGameWindow)
    {
        CRITICAL_ERROR("오류");
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
    switch (message)
    {
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

