#pragma once
#include "EnginePch.h"
#include "EngineSubsystem.h"
#include "Math/Transform.h"

class UWindowSubsystem;

/* UWindowSubsystem에 의존 */
/* UWorld, ULevel, AActor에 의존 */
class URenderSubsystem : public UEngineSubsystem
{
public:
	/* Constructors and Overrides */
	URenderSubsystem();

	void Tick(float fDeltaTime) override;

	void LateInit() override;

public:
	DXGI_SWAP_CHAIN_DESC MakeSwapChainDesc();

	void CreateDeviceAndContext();

	void InitSwapChain();

	void Render(float fDeltaTime);

private:
	UWindowSubsystem* WindowSubsystem;

	ComPtr<ID3D11Device> Device;
	ComPtr<ID3D11DeviceContext> Context;
	ComPtr<IDXGISwapChain> SwapChain;
	ComPtr<ID3D11Texture2D> BackBuffer;
	ComPtr<ID3D11RenderTargetView> RTV;

	FTransform CameraTransform;
	float RenderTargetViewColor[4];
};

