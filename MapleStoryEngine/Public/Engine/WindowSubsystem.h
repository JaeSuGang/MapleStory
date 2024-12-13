#pragma once
#include <Windows.h>
#include "EngineSubsystem.h"

class UWindowSubsystem : public UEngineSubsystem
{
public:
	UWindowSubsystem();

	void Tick(float fDeltaTime) override;

	void InitializeWCEX();

	static LRESULT WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

private:
	HWND hGameWindow;

	WNDCLASSEXA WCEX;
};

