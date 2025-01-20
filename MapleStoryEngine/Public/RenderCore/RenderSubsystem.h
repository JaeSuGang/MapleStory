#pragma once
#include "EnginePch.h"
#include "Engine/EngineSubsystem.h"
#include "Math/Transform.h"

/* SortingLayer 0 : BackGround */
/* SortingLayer 0 ~ 7 : 맵 지정 */
/* SortingLayer 8 : 몹 */
/* SortingLayer 9 : 캐릭터 */
/* SortingLayer 10 : 스킬 */
/* SortingLayer 11 : 디버그 레이어 */



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
	bool IsFreeMode;
	bool IsPerspectiveProjection;
	bool IsWireFrame;
	int DebugLayerLevel = 12;
};

/* UWindowSubsystem, UDebugSubsystem, UResourceSubsystem에 의존 */
/* UWorld, ULevel, AActor에 의존 */
class URenderSubsystem : public UEngineSubsystem
{
	friend class UWindowSubsystem;
	friend class UResourceSubsystem;
	friend class URenderComponent;
	friend class UAnimation;

public:
	/* Constructors and Overrides */
	URenderSubsystem();

	~URenderSubsystem();

	void Tick(float fDeltaTime) override;

	void LateInit() override;

public:
	ENGINE_API IDXGISwapChain* GetSwapChain();

	ENGINE_API ID3D11ShaderResourceView* GetMainScreenSRV();

	ENGINE_API void ReleaseTextures();

	ENGINE_API void RotateCameraByMousePosition();

	ENGINE_API void ResetCameraMousePosition();

	ENGINE_API void MoveCamera(FVector3 _MoveVector);

	ENGINE_API FCamera& GetCamera();

	void RenderWidgets(float fDeltaTime);

	void DebugRender(float fDeltaTime);

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
	/* 개별 매쉬 설정 */
	void SetTransformConstantBuffer(FTransform Transform);

	void SetShaderResources(int TextureID);

private:
	/* 렌더링 파이프라인 초기화 */
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
	vector<URenderComponent*> Widgets;
	vector<URenderComponent*> Transculents;
	/* Sorting Layer, Order in Group, Components */
	vector<vector<vector<vector<URenderComponent*>>>> RenderOrder;

private:
	/* 리소스 */
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
	int WireframePixelShaderID;
	int GreenOutlinePixelShaderID;
	int TransparentPixelShaderID;

public:
	/* 디버그 인터페이스 */
	ComPtr<ID3D11Debug> D3D11Debug;

private:
	/* 카메라 설정 */
	FCamera Camera;
	POINT LastMousePosition;

	/* Depth Stencil State */
	ComPtr<ID3D11DepthStencilState> DefaultDepthStencilState;

	/* 샘플러 */
	ComPtr<ID3D11SamplerState> DefaultSamplerState;

	/* 블렌드 설정 */
	ComPtr<ID3D11BlendState> DefaultBlendState;

	/* 텍스처와 뷰 */
	ComPtr<ID3D11Texture2D> BackBuffer;
	ComPtr<ID3D11RenderTargetView> RenderTargetView;
	ComPtr<ID3D11ShaderResourceView> RTVtoSRV;
	ComPtr<ID3D11Texture2D> DepthStencilBuffer;
	ComPtr<ID3D11RenderTargetView> OffScreenRTV;
	ComPtr<ID3D11Texture2D> OffScreenBuffer;

	ComPtr<ID3D11DepthStencilView> DepthStencilView;
	ComPtr<ID3D11DepthStencilView> ReadOnlyDepthStencilView;


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

