#pragma once
#include "EnginePch.h"
#include "EngineSubsystem.h"

class UWindowSubsystem;

/* UWindowSubsystem¿¡ ÀÇÁ¸ */
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

private:
	UWindowSubsystem* WindowSubsystem;

	ComPtr<ID3D11Device> Device;
	ComPtr<ID3D11DeviceContext> Context;
	ComPtr<IDXGISwapChain> SwapChain;


};

