#pragma once
#include "EnginePch.h"
#include "EngineSubsystem.h"
#include "Math/Transform.h"

class UWindowSubsystem;
class UDebugSubsystem;

/* UWindowSubsystem, UDebugSubsystem에 의존 */
/* UWorld, ULevel, AActor에 의존 */
class URenderSubsystem : public UEngineSubsystem
{
public:
	/* Constructors and Overrides */
	URenderSubsystem();

	void Tick(float fDeltaTime) override;

	void LateInit() override;

public:
	void Render(float fDeltaTime);

	void DebugRender(float fDeltaTime);

	ID3D11Device* GetDevice() const;

	ID3D11DeviceContext* GetDeviceContext() const;

	DXGI_SWAP_CHAIN_DESC MakeSwapChainDesc();

	void CreateDeviceAndContext();

	void InitSwapChain();

	void InitViewport();


private:
	UWindowSubsystem* WindowSubsystem;

	UDebugSubsystem* DebugSubsystem;

	ComPtr<ID3D11Device> Device;
	ComPtr<ID3D11DeviceContext> DeviceContext;
	ComPtr<IDXGISwapChain> SwapChain;
	ComPtr<ID3D11Texture2D> BackBuffer;
	ComPtr<ID3D11RenderTargetView> RTV;

	FTransform CameraTransform;
	float RenderTargetViewColor[4];
};

