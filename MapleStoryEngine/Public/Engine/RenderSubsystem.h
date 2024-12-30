#pragma once
#include "EnginePch.h"
#include "EngineSubsystem.h"
#include "Math/Transform.h"

class UWindowSubsystem;
class UDebugSubsystem;

/* UWindowSubsystem, UDebugSubsystem, UResourceSubsystem에 의존 */
/* UWorld, ULevel, AActor에 의존 */
class URenderSubsystem : public UEngineSubsystem
{
public:
	/* Constructors and Overrides */
	URenderSubsystem();

	void Tick(float fDeltaTime) override;

	void LateInit() override;

public:
	ID3D11Buffer* GetD3DVertexBuffer(string strName);

	void Render(float fDeltaTime);

	void RenderActors(float fDeltaTime);

	ID3D11Device* GetDevice() const;

	ID3D11DeviceContext* GetDeviceContext() const;

	void CreateDeviceAndContext();

	void InitSwapChain();

	void SetViewport();

private:
	void CompileD3DVSShader();

	DXGI_SWAP_CHAIN_DESC MakeSwapChainDesc();

public:
	unordered_map<string, ComPtr<ID3D11Buffer>> D3DVertexBuffers;
	unordered_map<string, ComPtr<ID3D11InputLayout>> D3DInputLayouts;

private:
	FTransform CameraTransform;
	UWindowSubsystem* WindowSubsystem;
	float RenderTargetViewColor[4];

private:
	ComPtr<ID3D11Device> Device;
	ComPtr<ID3D11DeviceContext> DeviceContext;
	ComPtr<IDXGISwapChain> SwapChain;
	ComPtr<ID3D11Texture2D> BackBuffer;
	ComPtr<ID3D11RenderTargetView> RTV;
	ComPtr<ID3DBlob> D3DVSErrorCodeBlob;
	ComPtr<ID3DBlob> D3DVSShaderCodeBlob;

};

