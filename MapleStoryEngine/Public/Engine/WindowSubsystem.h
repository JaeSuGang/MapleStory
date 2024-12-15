#pragma once
#include "EngineSubsystem.h"
#include "EnginePch.h"

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

