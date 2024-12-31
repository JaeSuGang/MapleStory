#pragma once
#include "EnginePch.h"
#include "EngineSubsystem.h"
#include "Math/Transform.h"

class UWindowSubsystem;
class UDebugSubsystem;

struct FTransformConstants
{
public:
	DirectX::XMMATRIX WVP;
};

struct FCamera
{
public:
	FTransform Transform;
	float Width;
	float Height;
	float NearZ;
	float FarZ;
};

/* UWindowSubsystem, UDebugSubsystem, UResourceSubsystem�� ���� */
/* UWorld, ULevel, AActor�� ���� */
class URenderSubsystem : public UEngineSubsystem
{
public:
	/* Constructors and Overrides */
	URenderSubsystem();

	void Tick(float fDeltaTime) override;

	void LateInit() override;

public:
	ID3D11Buffer* GetD3DVertexBuffer(string strName);

	ID3D11Buffer* GetD3DIndexBuffer(string strName);

	void Render(float fDeltaTime);

	void RenderActors(float fDeltaTime);

	ID3D11Device* GetDevice() const;

	ID3D11DeviceContext* GetDeviceContext() const;

	void CreateDeviceAndContext();

	void InitSwapChain();


private:
	/* ������ ���������� �ʱ�ȭ */
	void CreateTransformConstantBuffer();
	
	void CreateViewport();

	void CreateInputLayout();

	void CreateD3DVertexShader();

	DXGI_SWAP_CHAIN_DESC MakeSwapChainDesc();

private:
	/* ���� ������ ���������� ���� */
	void SetTransformConstantBuffer(FTransform Transform);


public:
	/* ������ ���������� ���� ���� ���� */
	ComPtr<ID3D11Buffer> TransformConstantBuffer;
	FCamera Camera;

public:

	/* ������ ���������� �ʱ�ȭ ���� */
	ComPtr<ID3D11VertexShader> D3DVertexShader;
	ComPtr<ID3DBlob> D3DVSShaderCodeBlob;
	ComPtr<ID3DBlob> D3DVSErrorCodeBlob;
	unordered_map<string, ComPtr<ID3D11Buffer>> D3DVertexBuffers;
	unordered_map<string, ComPtr<ID3D11Buffer>> D3DIndexBuffers;
	ComPtr<ID3D11InputLayout> D3DInputLayout;
	ComPtr<ID3D11Device> Device;
	ComPtr<ID3D11DeviceContext> DeviceContext;
	ComPtr<IDXGISwapChain> SwapChain;
	ComPtr<ID3D11Texture2D> BackBuffer;
	ComPtr<ID3D11RenderTargetView> RTV;

private:
	/* ����ý��� ������ */
	UWindowSubsystem* WindowSubsystem;
	float RenderTargetViewColor[4];
};

