#pragma once
#include "EnginePch.h"
#include "Engine/Engine.h"
#include "EngineSubsystem.h"

class URenderSubsystem;
class UWindowSubsystem;
struct ImGuiIO;

/* WindowSystem과 RenderSystem에 종속적 */
class UDebugSubsystem : public UEngineSubsystem
{
public:
	/* Contructors and Overrides */
	~UDebugSubsystem();
	void Tick(float fDeltaTime) override;
	void LateInit() override;

public:
	void Render();

	LRESULT IMGUIWndProcHandler(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

	void InitIMGUI();

	/* Warning Level 0 : Normal White Log */
	/* Warning Level 1 : Orange Log */
	/* Warning Level 2 : Red Log */
	ENGINE_API void Log(string Text, int WarningLevel);


private:
	UWindowSubsystem* WindowSubsystem;

	URenderSubsystem* RenderSubsystem;

};

extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
extern LRESULT ImGui_ImplWin32_WndProcHandlerEx(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam, ImGuiIO& io);