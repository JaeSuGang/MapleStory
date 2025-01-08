#pragma once
#include "EnginePch.h"
#include "Engine/EngineSubsystem.h"
#include "Math/Transform.h"

class UWindowSubsystem;
class UDebugSubsystem;
class UTexture;

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
	friend class URenderComponent;
	friend class UAnimation;

public:
	/* Constructors and Overrides */
	URenderSubsystem();

	void Tick(float fDeltaTime) override;

	void LateInit() override;

public:
	ENGINE_API void ReleaseTextures();

	ENGINE_API FCamera& GetCamera();

	void Render(float fDeltaTime);

	void RenderActors(float fDeltaTime);

	ID3D11Device* GetDevice() const;

	ID3D11DeviceContext* GetDeviceContext() const;

	void CreateDeviceAndContext();

	void InitSwapChain();

public:
	void SetMissingTexture();

	int GetPixelShaderIDByName(string strKey);

	int GetVertexBufferIDByName(string strKey);

	int GetIndexBufferIDByName(string strKey);

	int GetTextureIDByName(string strKey);

	void AddNewVertexBuffer(string strKey, ComPtr<ID3D11Buffer> NewVertexBuffer);

	void AddNewIndexBuffer(string strKey, ComPtr<ID3D11Buffer> NewIndexBuffer);

	int AddNewTexture(string strKey, shared_ptr<UTexture> NewTexture);

private:
	/* ���� �Ž� ���� */
	void SetTransformConstantBuffer(FTransform Transform);

	void SetShaderResources(int TextureID);

private:
	/* ������ ���������� �ʱ�ȭ */
	DXGI_SWAP_CHAIN_DESC MakeSwapChainDesc();

	void ReserveMemories();

	void CreateD3D11Debug();

	void CreateTransformConstantBuffer();
	
	void CreateViewport();

	void CreateInputLayout();

	void CreateDefaultSamplerState();

	void CreateVertexShader(string strShaderPath);

	void CreatePixelShaders(string strShaderPath);

	void CreateRasterizer();

	void CreateDepthStencilView();

	void CreateBlendState();

private:
	/* ���ҽ� */
	/* Textures */
	unordered_map<string, int> StringMappedTextureIDs;
	vector<shared_ptr<UTexture>> Textures;
	int MissingTextureTextureID;
	/* Vertex Buffers */
	unordered_map<string, int> StringMappedVertexBufferIDs;
	vector<ComPtr<ID3D11Buffer>> VertexBuffers;
	/* Index Buffers */
	unordered_map<string, int> StringMappedIndexBufferIDs;
	vector<ComPtr<ID3D11Buffer>> IndexBuffers;
	/* Pixel Shaders */
	unordered_map<string, int> StringMappedIndexPixelShaderIDs;
	vector<ComPtr<ID3D11PixelShader>> PixelShaders;
	ID3D11PixelShader* WireframePixelShader;

public:
	/* ����� �������̽� */
	ComPtr<ID3D11Debug> D3D11Debug;

private:
	/* ī�޶� ���� */
	FCamera Camera;

	/* Depth Stencil State */
	ComPtr<ID3D11DepthStencilState> DefaultDepthStencilState;

	/* ���÷� */
	ComPtr<ID3D11SamplerState> DefaultSamplerState;

	/* ���� ���� */
	ComPtr<ID3D11BlendState> DefaultBlendState;

	/* �ؽ�ó�� �� */
	ComPtr<ID3D11Texture2D> BackBuffer;
	ComPtr<ID3D11RenderTargetView> RenderTargetView;
	ComPtr<ID3D11Texture2D> DepthStencilBuffer;
	ComPtr<ID3D11DepthStencilView> DepthStencilView;
	ComPtr<ID3D11DepthStencilView> ReadOnlyDepthStencilView;


	/* ������ ���������� ���� ���� ���� */
	ComPtr<ID3D11Buffer> TransformConstantBuffer;

	/* ������ ���������� �ʱ�ȭ ���� */
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
	/* ����ý��� ������ */
	UWindowSubsystem* WindowSubsystem;
	float RenderTargetViewColor[4];
};

