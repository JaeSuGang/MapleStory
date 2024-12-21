#pragma once
#include "EngineSubsystem.h"
#include "EnginePch.h"

class UWindowSubsystem : public UEngineSubsystem
{
public:
	/* Constructors and Overrides */
	UWindowSubsystem();

	void Tick(float fDeltaTime) override;

	void LateInit() override;

public:
	HWND GetWindowHandle() const;

	void InitializeWCEX();

	static LRESULT WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

private:
	HWND hGameWindow;

	WNDCLASSEXA WCEX;

};

