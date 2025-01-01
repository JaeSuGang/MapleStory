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

/* UWindowSubsystem, UDebugSubsystem, UResourceSubsystem에 의존 */
/* UWorld, ULevel, AActor에 의존 */
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
	/* 렌더링 파이프라인 초기화 */
	DXGI_SWAP_CHAIN_DESC MakeSwapChainDesc();

	void CreateTransformConstantBuffer();
	
	void CreateViewport();

	void CreateInputLayout();

	void CreateVertexShader();

	void CreateRasterizer();

	void CreatePixelShader();


private:
	/* 카메라 설정 */
	FCamera Camera;

	/* 개별 렌더링 파이프라인 설정 */
	void SetTransformConstantBuffer(FTransform Transform);

	/* 메쉬 데이터 */
	unordered_map<string, ComPtr<ID3D11Buffer>> VertexBuffers;
	unordered_map<string, ComPtr<ID3D11Buffer>> IndexBuffers;
	unordered_map<string, ComPtr<ID3D11Texture2D>> Textures;
	unordered_map<string, ComPtr<ID3D11ShaderResourceView>> ShaderResourceViews;

	/* 렌더링 파이프라인 개별 설정 변수 */
	ComPtr<ID3D11Buffer> TransformConstantBuffer;

	/* 렌더링 파이프라인 초기화 변수 */
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
	/* 서브시스템 변수들 */
	UWindowSubsystem* WindowSubsystem;
	float RenderTargetViewColor[4];
};

