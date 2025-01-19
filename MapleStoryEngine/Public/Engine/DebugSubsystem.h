#pragma once
#include "EnginePch.h"
#include "Engine/Engine.h"
#include "EngineSubsystem.h"

class URenderSubsystem;
class UWindowSubsystem;
struct ImGuiIO;

typedef unsigned int ImGuiID;

/* WindowSystem과 RenderSystem에 종속적 */
class UDebugSubsystem : public UEngineSubsystem
{
public:
	/* Contructors and Overrides */
	ENGINE_API ~UDebugSubsystem();
	ENGINE_API void LateInit() override;
	ENGINE_API void Tick(float fDeltaTime);
	ENGINE_API virtual void CustomCode() = 0;
	ENGINE_API virtual void CustomInit() = 0;

public:
	void Render();

	void RenderMainViewport();

	void InitMainViewport();

	LRESULT IMGUIWndProcHandler(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

	void InitIMGUI();

	/* Warning Level 0 : Normal White Log */
	/* Warning Level 1 : Orange Log */
	/* Warning Level 2 : Red Log */
	ENGINE_API void Log(string Text, int WarningLevel);


protected:
	UWindowSubsystem* WindowSubsystem;

	URenderSubsystem* RenderSubsystem;

	float FPS;

	float FPSRefreshTime;

};

extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
extern LRESULT ImGui_ImplWin32_WndProcHandlerEx(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam, ImGuiIO& io);