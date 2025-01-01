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
	float FOV;
	float Width;
	float Height;
	float NearZ;
	float FarZ;
	bool IsPerspectiveProjection;
	bool IsWireFrame;
};

/* UWindowSubsystem, UDebugSubsystem, UResourceSubsystem�� ���� */
/* UWorld, ULevel, AActor�� ���� */
class URenderSubsystem : public UEngineSubsystem
{
	friend class UResourceSubsystem;

public:
	/* Constructors and Overrides */
	URenderSubsystem();

	void Tick(float fDeltaTime) override;

	void LateInit() override;

public:
	ENGINE_API FCamera& GetCamera();

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
	DXGI_SWAP_CHAIN_DESC MakeSwapChainDesc();

	void CreateTransformConstantBuffer();
	
	void CreateViewport();

	void CreateInputLayout();

	void CreateVertexShader();

	void CreateRasterizer();

	void CreatePixelShader();


private:
	/* ī�޶� ���� */
	FCamera Camera;

	/* ���� ������ ���������� ���� */
	void SetTransformConstantBuffer(FTransform Transform);

	/* �޽� ������ */
	unordered_map<string, ComPtr<ID3D11Buffer>> VertexBuffers;
	unordered_map<string, ComPtr<ID3D11Buffer>> IndexBuffers;
	unordered_map<string, ComPtr<ID3D11Texture2D>> Textures;
	unordered_map<string, ComPtr<ID3D11ShaderResourceView>> ShaderResourceViews;

	/* ������ ���������� ���� ���� ���� */
	ComPtr<ID3D11Buffer> TransformConstantBuffer;

	/* ������ ���������� �ʱ�ȭ ���� */
	D3D11_VIEWPORT ViewPortInfo;
	ComPtr<ID3D11RasterizerState> RasterizerDefaultState;
	ComPtr<ID3D11RasterizerState> RasterizerWireframeState;
	ComPtr<ID3D11VertexShader> VertexShader;
	ComPtr<ID3D11PixelShader> PixelShader;
	ComPtr<ID3DBlob> VSCodeBlob;
	ComPtr<ID3DBlob> VSErrorCodeBlob;
	ComPtr<ID3DBlob> PSCodeBlob;
	ComPtr<ID3DBlob> PSErrorCodeBlob;
	ComPtr<ID3D11InputLayout> InputLayout;
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

