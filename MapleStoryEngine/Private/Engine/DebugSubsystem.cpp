#include "EnginePch.h"
#include "IMGUI/imgui.h"
#include "IMGUI/imgui_impl_win32.h"
#include "IMGUI/imgui_impl_dx11.h"
#include "Engine/Engine.h"
#include "Engine/DebugSubsystem.h"
#include "Engine/WindowSubsystem.h"
#include "Engine/RenderSubsystem.h"

void UDebugSubsystem::Log(string Text, int WarningLevel)
{

}

void UDebugSubsystem::LateInit()
{
	WindowSubsystem = Engine->WindowSubsystem;

	RenderSubsystem = Engine->RenderSubsystem;

	InitIMGUI();
}

void UDebugSubsystem::Render()
{
	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	ImGui::ShowDemoWindow();

	ImGui::Begin("Test");
	ImGui::Text("Hello from another window!");
	ImGui::End();

	ImGui::Render();
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
}

LRESULT UDebugSubsystem::IMGUIWndProcHandler(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	if (ImGui::GetCurrentContext() == nullptr)
		return 0;

	return ImGui_ImplWin32_WndProcHandlerEx(hwnd, msg, wParam, lParam, ImGui::GetIO());
}

void UDebugSubsystem::InitIMGUI()
{
	ImGui::CreateContext();

	ImGui_ImplWin32_Init(WindowSubsystem->GetWindowHandle());

	ImGui_ImplDX11_Init(RenderSubsystem->GetDevice(), RenderSubsystem->GetDeviceContext());
}

UDebugSubsystem::~UDebugSubsystem()
{
	ImGui_ImplDX11_Shutdown();

	ImGui_ImplWin32_Shutdown();

	ImGui::DestroyContext();
}

void UDebugSubsystem::Tick(float fDeltaTime)
{
}
