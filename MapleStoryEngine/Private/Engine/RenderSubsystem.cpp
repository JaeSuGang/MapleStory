#include "EnginePch.h"
#include "Engine/Engine.h"
#include "Engine/RenderSubsystem.h"
#include "Engine/DebugSubsystem.h"
#include "Engine/WindowSubsystem.h"
#include "World/World.h"
#include "Level/Level.h"
#include "Actor/Actor.h"
#include "ActorComponent/RenderComponent.h"
#include "IMGUI/imgui.h"

URenderSubsystem::URenderSubsystem()
{
	RenderTargetViewColor[0] = 0.0f;
	RenderTargetViewColor[1] = 0.0f;
	RenderTargetViewColor[2] = 1.0f;
	RenderTargetViewColor[3] = 1.0f;
}

void URenderSubsystem::Tick(float fDeltaTime)
{
	Render(fDeltaTime);
}

DXGI_SWAP_CHAIN_DESC URenderSubsystem::MakeSwapChainDesc()
{
	DXGI_SWAP_CHAIN_DESC ScInfo{};

	ScInfo.BufferCount = 2;

	ScInfo.BufferDesc.Width = 1920;

	ScInfo.BufferDesc.Height = 1080;

	ScInfo.OutputWindow = WindowSubsystem->GetWindowHandle();

	ScInfo.Windowed = true;

	ScInfo.BufferDesc.RefreshRate.Denominator = 1;

	ScInfo.BufferDesc.RefreshRate.Numerator = 144;

	ScInfo.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;

	ScInfo.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;

	ScInfo.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;

	ScInfo.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT | DXGI_USAGE_SHADER_INPUT;

	ScInfo.SampleDesc.Quality = 0;

	ScInfo.SampleDesc.Count = 1;

	ScInfo.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;

	ScInfo.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

	return ScInfo;
}

void URenderSubsystem::CreateDeviceAndContext()
{
	DXGI_SWAP_CHAIN_DESC SwapChainDesc = MakeSwapChainDesc();

	D3D_FEATURE_LEVEL FeatureLevel{};

	HRESULT HR = D3D11CreateDeviceAndSwapChain(
		nullptr,
		D3D_DRIVER_TYPE_HARDWARE,
		nullptr,
		0,
		nullptr,
		0,
		D3D11_SDK_VERSION,
		&SwapChainDesc,
		SwapChain.GetAddressOf(),
		Device.GetAddressOf(),
		&FeatureLevel,
		DeviceContext.GetAddressOf()
		);

	if (HR != S_OK)
	{
		CRITICAL_ERROR(ENGINE_INIT_ERROR_TEXT);
	}
}

void URenderSubsystem::InitSwapChain()
{
	if (S_OK != SwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(BackBuffer.GetAddressOf())))
	{
		CRITICAL_ERROR(ENGINE_INIT_ERROR_TEXT);
	}

	if (S_OK != Device->CreateRenderTargetView(BackBuffer.Get(), nullptr, &RTV))
	{
		CRITICAL_ERROR(ENGINE_INIT_ERROR_TEXT);
	}
}

void URenderSubsystem::Render(float fDeltaTime)
{
	DeviceContext->ClearRenderTargetView(RTV.Get(), RenderTargetViewColor);

	ID3D11RenderTargetView* _RTV = RTV.Get();
	DeviceContext->OMSetRenderTargets(1, &_RTV, nullptr);
	/*
	vector<shared_ptr<AActor>>& Actors = Engine->GetWorld()->GetActorContainer();

	for (shared_ptr<AActor>& Actor : Actors)
	{
		if (URenderComponent* Renderer = Actor->GetComponentByClass<URenderComponent>())
		{

		}
	}
	*/
#ifdef _DEBUG

	DebugRender(fDeltaTime);

#endif // _DEBUG

	SwapChain->Present(0, 0);
}

void URenderSubsystem::DebugRender(float fDeltaTime)
{
#ifdef _DEBUG

	DebugSubsystem->Render();

#endif // _DEBUG
}

ID3D11Device* URenderSubsystem::GetDevice() const
{
	return Device.Get();
}

ID3D11DeviceContext* URenderSubsystem::GetDeviceContext() const
{
	return DeviceContext.Get();
}

void URenderSubsystem::LateInit()
{
	WindowSubsystem = Engine->WindowSubsystem;

	DebugSubsystem = Engine->DebugSubsystem;

	CreateDeviceAndContext();

	InitSwapChain();
}
