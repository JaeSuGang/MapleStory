#include "EnginePch.h"
#include "IMGUI/imgui.h"
#include "IMGUI/imgui_internal.h"
#include "IMGUI/imgui_impl_win32.h"
#include "IMGUI/imgui_impl_dx11.h"
#include "Engine/Engine.h"
#include "Engine/DebugSubsystem.h"
#include "Engine/WindowSubsystem.h"
#include "RenderCore/RenderSubsystem.h"
#include "World/World.h"
#include "Actor/Actor.h"
#include "Engine/TimeSubsystem.h"

void UDebugSubsystem::Log(string Text, int WarningLevel)
{
	if (WarningLevel >= 1)
	{
		int a = 0;
	}
}

void UDebugSubsystem::LateInit()
{
	WindowSubsystem = Engine->WindowSubsystem;

	RenderSubsystem = Engine->RenderSubsystem;

	InitIMGUI();

	this->InitMainViewport();

	this->CustomInit();
}

void UDebugSubsystem::Tick(float fDeltaTime)
{
	FPSRefreshTime += fDeltaTime;

	if (FPSRefreshTime > 0.1f)
	{
		FPSRefreshTime = 0.0f;
		FPS = GEngine->TimeSubsystem->GetFPS();
	}
}
void UDebugSubsystem::InitMainViewport()
{
	ImGuiViewport* viewport = ImGui::GetMainViewport();

	ImGui::SetNextWindowPos(viewport->WorkPos, ImGuiCond_::ImGuiCond_Once);
	ImGui::SetNextWindowSize(viewport->WorkSize);
	ImGui::SetNextWindowViewport(viewport->ID);
}

void UDebugSubsystem::RenderMainViewport()
{
	ImGuiWindowFlags window_flags =
		ImGuiWindowFlags_NoTitleBar
		| ImGuiWindowFlags_NoCollapse
		| ImGuiWindowFlags_NoResize
		| ImGuiWindowFlags_NoMove
		| ImGuiWindowFlags_NoBringToFrontOnFocus
		| ImGuiWindowFlags_NoNavFocus;
	ImGui::Begin("MainDockSpaceWindow", nullptr, window_flags);

	ImGuiID dockspaceID = ImGui::GetID("MainDockSpace");
	ImGuiDockNodeFlags dock_flags = ImGuiDockNodeFlags_None;

	ImGui::DockSpace(dockspaceID, ImVec2(0.0f, 0.0f), dock_flags);

	ImGui::End();
}

void UDebugSubsystem::Render()
{
	ImGuiIO& io = ImGui::GetIO();
	io.DisplayFramebufferScale = { io.DisplaySize.x / DEFAULT_WINDOW_SIZE_X, io.DisplaySize.y / DEFAULT_WINDOW_SIZE_Y };

	vector<shared_ptr<AActor>>& Actors = Engine->GetWorld()->GetActors();

	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	// this->RenderMainViewport();

	this->CustomCode();

	ImGui::Render();
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

	if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
	{
		ImGui::UpdatePlatformWindows();
		ImGui::RenderPlatformWindowsDefault();
	}
}


void UDebugSubsystem::CustomInit()
{

}

LRESULT UDebugSubsystem::IMGUIWndProcHandler(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	if (ImGui::GetCurrentContext() == nullptr)
		return 0;

	return ImGui_ImplWin32_WndProcHandler(hwnd, msg, wParam, lParam);
}

void UDebugSubsystem::InitIMGUI()
{
	ImGui::CreateContext();

	ImGuiIO& io = ImGui::GetIO();

	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
	io.ConfigFlags |= ImGuiConfigFlags_DpiEnableScaleViewports;
	io.ConfigFlags |= ImGuiConfigFlags_DpiEnableScaleFonts;
		
	/* 메인 윈도우 밖으로 IMGUI창이 나갈수 있도록 허용하는 옵션 */
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

}

UDebugSubsystem::~UDebugSubsystem()
{
	ImGui_ImplDX11_Shutdown();

	ImGui_ImplWin32_Shutdown();

	ImGui::DestroyContext();
}

