#include "EnginePch.h"
#include "IMGUI/imgui.h"
#include "IMGUI/imgui_impl_win32.h"
#include "IMGUI/imgui_impl_dx11.h"
#include "Engine/Engine.h"
#include "Engine/DebugSubsystem.h"
#include "Engine/WindowSubsystem.h"
#include "Engine/RenderSubsystem.h"
#include "World/World.h"
#include "Actor/Actor.h"

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
	ImGuiIO& io = ImGui::GetIO();

	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	ImGui::Begin("DebugSystem");
	if (ImGui::Button("Spawn Test Actor"))
	{
		GEngine->GetWorld()->SpawnActor<AActor>();
	}
	ImGui::End();

	ImGui::Render();
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

	if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
	{
		ImGui::UpdatePlatformWindows();
		ImGui::RenderPlatformWindowsDefault();
	}
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

	ImGuiIO& io = ImGui::GetIO();

	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
	io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

	ImGui::StyleColorsDark();

	ImGuiStyle& style = ImGui::GetStyle();
	if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
	{
		style.WindowRounding = 0.0f;
		style.Colors[ImGuiCol_WindowBg].w = 1.0f;

	}

	ImGui_ImplWin32_Init(WindowSubsystem->GetWindowHandle());

	ImGui_ImplDX11_Init(RenderSubsystem->GetDevice(), RenderSubsystem->GetDeviceContext());

	// ImGui_ImplWin32_EnableDpiAwareness();
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
