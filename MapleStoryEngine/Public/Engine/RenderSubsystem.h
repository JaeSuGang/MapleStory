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

	void Render(float fDeltaTime);

	void RenderActors(float fDeltaTime);

	ID3D11Device* GetDevice() const;

	ID3D11DeviceContext* GetDeviceContext() const;

	void CreateDeviceAndContext();

	void InitSwapChain();

public:
	int GetVertexBufferIDByName(string strKey);

	int GetIndexBufferIDByName(string strKey);

	int GetTextureIDByName(string strKey);

	int GetSRVIDByName(string strKey);

	void AddNewVertexBuffer(string strKey, ComPtr<ID3D11Buffer> NewVertexBuffer);

	void AddNewIndexBuffer(string strKey, ComPtr<ID3D11Buffer> NewIndexBuffer);

	void AddNewTexture(string strKey, ComPtr<ID3D11Texture2D> NewTexture);

	void AddNewSRV(string strKey, ComPtr<ID3D11ShaderResourceView> NewSRV);

private:
	/* 개별 매쉬 설정 */
	void SetTransformConstantBuffer(FTransform Transform);

	void SetShaderResources(int SRVID);

private:
	/* 렌더링 파이프라인 초기화 */
	DXGI_SWAP_CHAIN_DESC MakeSwapChainDesc();

	void CreateTransformConstantBuffer();
	
	void CreateViewport();

	void CreateInputLayout();

	void CreateDefaultSamplerState();

	void CreateVertexShader(string strShaderPath);

	void CreatePixelShaders(string strShaderPath);

	void CreateRasterizer();

	void CreateDepthStencilView();

private:
	/* 리소스 */
	/* SRVs */
	unordered_map<string, int> StringMappedSRVIDs;
	vector<ComPtr<ID3D11ShaderResourceView>> ShaderResourceViews;
	int MissingTextureSRVID;
	/* Textures */
	unordered_map<string, int> StringMappedTextureIDs;
	vector<ComPtr<ID3D11Texture2D>> Textures;
	int MissingTextureTextureID;
	/* Vertex Buffers */
	unordered_map<string, int> StringMappedVertexBufferIDs;
	vector<ComPtr<ID3D11Buffer>> VertexBuffers;
	/* Index Buffers */
	unordered_map<string, int> StringMappedIndexBufferIDs;
	vector<ComPtr<ID3D11Buffer>> IndexBuffers;

private:
	/* 카메라 설정 */
	FCamera Camera;

	/* 픽셀 쉐이더 */
	ComPtr<ID3D11PixelShader> DefaultPixelShader;
	ComPtr<ID3D11PixelShader> WireframePixelShader;

	/* 샘플러 */
	ComPtr<ID3D11SamplerState> DefaultSamplerState;

	/* 텍스처와 뷰 */
	ComPtr<ID3D11Texture2D> BackBuffer;
	ComPtr<ID3D11RenderTargetView> RenderTargetView;
	ComPtr<ID3D11Texture2D> DepthStencilBuffer;
	ComPtr<ID3D11DepthStencilView> DepthStencilView;


	/* 렌더링 파이프라인 개별 설정 변수 */
	ComPtr<ID3D11Buffer> TransformConstantBuffer;

	/* 렌더링 파이프라인 초기화 변수 */
	D3D11_VIEWPORT ViewPortInfo;
	ComPtr<ID3D11RasterizerState> RasterizerDefaultState;
	ComPtr<ID3D11RasterizerState> RasterizerWireframeState;
	ComPtr<ID3D11VertexShader> VertexShader;
	ComPtr<ID3DBlob> VSCodeBlob;
	ComPtr<ID3DBlob> VSErrorCodeBlob;
	ComPtr<ID3DBlob> PSCodeBlob;
	ComPtr<ID3DBlob> PSErrorCodeBlob;
	ComPtr<ID3D11InputLayout> InputLayout;
	ComPtr<ID3D11Device> Device;
	ComPtr<ID3D11DeviceContext> DeviceContext;
	ComPtr<IDXGISwapChain> SwapChain;

private:
	/* 서브시스템 변수들 */
	UWindowSubsystem* WindowSubsystem;
	float RenderTargetViewColor[4];
};

