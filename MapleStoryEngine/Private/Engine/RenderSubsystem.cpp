#include "EnginePch.h"
#include "Engine/Engine.h"
#include "Engine/RenderSubsystem.h"
#include "Engine/ResourceSubsystem.h"
#include "Engine/DebugSubsystem.h"
#include "Engine/WindowSubsystem.h"
#include "Utils/Utils.h"
#include "World/World.h"
#include "Level/Level.h"
#include "Actor/Actor.h"
#include "ActorComponent/RenderComponent.h"
#include "IMGUI/imgui.h"

URenderSubsystem::URenderSubsystem()
	:
	Camera{}
{
	Camera.FOV = 80.0f;
	Camera.Width = DEFAULT_WINDOW_SIZE_X;
	Camera.Height = DEFAULT_WINDOW_SIZE_Y;
	Camera.NearZ = 1.0f;
	Camera.FarZ = 10000.0f;
	Camera.Transform.Position.z = -1000.0f;

	RenderTargetViewColor[0] = 0.25f;
	RenderTargetViewColor[1] = 0.25f;
	RenderTargetViewColor[2] = 0.25f;
	RenderTargetViewColor[3] = 1.0f;
}

void URenderSubsystem::Tick(float fDeltaTime)
{
	Render(fDeltaTime);
}

DXGI_SWAP_CHAIN_DESC URenderSubsystem::MakeSwapChainDesc()
{
	RECT WindowSize = WindowSubsystem->GetWindowSize();

	DXGI_SWAP_CHAIN_DESC ScInfo{};

	ScInfo.BufferCount = 2;

	ScInfo.BufferDesc.Width = WindowSize.right;

	ScInfo.BufferDesc.Height = WindowSize.bottom;

	ScInfo.OutputWindow = WindowSubsystem->GetWindowHandle();

	ScInfo.Windowed = true;

	ScInfo.BufferDesc.RefreshRate.Denominator = 1;

	ScInfo.BufferDesc.RefreshRate.Numerator = 144;

	ScInfo.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;

	ScInfo.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;

	ScInfo.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;

	ScInfo.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT | DXGI_USAGE_SHADER_INPUT;

	ScInfo.SampleDesc.Quality = 0;

	ScInfo.SampleDesc.Count = 1;

	ScInfo.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;

	ScInfo.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

	return ScInfo;
}

void URenderSubsystem::SetTransformConstantBuffer(FTransform Transform)
{
	/* 월드 행렬 연산 */
	DirectX::XMMATRIX ScaleMatrix = DirectX::XMMatrixScalingFromVector(DirectX::XMVECTOR{Transform.Scale.x, Transform.Scale.y , Transform.Scale.z });

	DirectX::XMMATRIX RotationMatrix = DirectX::XMMatrixRotationRollPitchYawFromVector(DirectX::XMVECTOR{ DirectX::XMConvertToRadians(Transform.Rotation.x), DirectX::XMConvertToRadians(Transform.Rotation.y) , DirectX::XMConvertToRadians(Transform.Rotation.z) });

	DirectX::XMMATRIX TranslationMatrix = DirectX::XMMatrixTranslationFromVector(DirectX::XMVECTOR{ Transform.Position.x, Transform.Position.y , Transform.Position.z, 1.0f});

	DirectX::XMMATRIX WorldMatrix = ScaleMatrix * RotationMatrix * TranslationMatrix;

	/* 뷰 행렬 연산 */
	DirectX::XMVECTOR CameraPos{ Camera.Transform.Position.x, Camera.Transform.Position.y , Camera.Transform.Position.z , 1.0f };

	DirectX::XMVECTOR CameraRot{ Camera.Transform.Rotation.x, Camera.Transform.Rotation.y , Camera.Transform.Rotation.z };

	DirectX::XMMATRIX RotMatrix = DirectX::XMMatrixRotationRollPitchYaw(
		DirectX::XMConvertToRadians(Camera.Transform.Rotation.x),
		DirectX::XMConvertToRadians(Camera.Transform.Rotation.y),
		DirectX::XMConvertToRadians(Camera.Transform.Rotation.z)
	);

	DirectX::XMVECTOR DefaultForward = DirectX::XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f);
	DirectX::XMVECTOR DefaultUp = DirectX::XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
	DirectX::XMVECTOR EyeDir = DirectX::XMVector3TransformNormal(DefaultForward, RotMatrix);
	DirectX::XMVECTOR UpDir = DirectX::XMVector3TransformNormal(DefaultUp, RotMatrix);

	DirectX::XMMATRIX ViewMatrix = DirectX::XMMatrixLookToLH(CameraPos, EyeDir, UpDir);

	/* 투영 행렬 연산 */
	DirectX::XMMATRIX ProjectionMatrix{};
	if (Camera.IsPerspectiveProjection)
		ProjectionMatrix = DirectX::XMMatrixPerspectiveFovLH(DirectX::XMConvertToRadians(Camera.FOV), DEFAULT_WINDOW_SIZE_X / DEFAULT_WINDOW_SIZE_Y, Camera.NearZ, Camera.FarZ);
	else
		ProjectionMatrix = DirectX::XMMatrixOrthographicLH(Camera.Width, Camera.Height, Camera.NearZ, Camera.FarZ);

	/* WVP 산출 */

	FTransformConstants TransformConstants{};

	TransformConstants.WVP = WorldMatrix * ViewMatrix * ProjectionMatrix;

	/* WVP 상수 버퍼 그래픽 메모리 Set */

	D3D11_MAPPED_SUBRESOURCE TransformSubresource{};

	DeviceContext->Map(TransformConstantBuffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &TransformSubresource);

	if (TransformSubresource.pData == nullptr)
	{
		CRITICAL_ERROR(DEFAULT_ERROR_TEXT);
	}

	memcpy_s(TransformSubresource.pData, sizeof(FTransformConstants), &TransformConstants, sizeof(FTransformConstants));

	DeviceContext->Unmap(TransformConstantBuffer.Get(), 0);
	
	ID3D11Buffer* pTransformConstantBuffer[1] = { TransformConstantBuffer.Get() };

	DeviceContext->VSSetConstantBuffers(0, 1, pTransformConstantBuffer);
}

void URenderSubsystem::SetShaderResources(int SRVID)
{
	ID3D11ShaderResourceView* SRVs[1];
	ID3D11SamplerState* Samplers[1];

	SRVs[0] = ShaderResourceViews[SRVID].Get();
	Samplers[0] = DefaultSamplerState.Get();

	DeviceContext->PSSetShaderResources(0, 1, SRVs);
	DeviceContext->PSSetSamplers(0, 1, Samplers);
}

void URenderSubsystem::CreateDeviceAndContext()
{
	DXGI_SWAP_CHAIN_DESC SwapChainDesc = MakeSwapChainDesc();

	D3D_FEATURE_LEVEL FeatureLevel{};

	UINT Flag{};

#ifdef _DEBUG
	Flag = D3D11_CREATE_DEVICE_DEBUG;
#endif 

	HRESULT HR = D3D11CreateDeviceAndSwapChain(
		nullptr,
		D3D_DRIVER_TYPE_HARDWARE,
		nullptr,
		Flag,
		nullptr,
		0,
		D3D11_SDK_VERSION,
		&SwapChainDesc,
		SwapChain.GetAddressOf(),
		Device.GetAddressOf(),
		&FeatureLevel,
		DeviceContext.GetAddressOf()
		);

	if (HR != S_OK)
	{
		CRITICAL_ERROR(ENGINE_INIT_ERROR_TEXT);
	}
}

void URenderSubsystem::InitSwapChain()
{
	if (S_OK != SwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(BackBuffer.GetAddressOf())))
	{
		CRITICAL_ERROR(ENGINE_INIT_ERROR_TEXT);
	}

	if (S_OK != Device->CreateRenderTargetView(BackBuffer.Get(), nullptr, &RenderTargetView))
	{
		CRITICAL_ERROR(ENGINE_INIT_ERROR_TEXT);
	}
}

int URenderSubsystem::GetVertexBufferIDByName(string strKey)
{
	auto FindIter = StringMappedVertexBufferIDs.find(strKey);

	if (FindIter != StringMappedVertexBufferIDs.end())
	{
		return FindIter->second;
	}
	else
	{
		GEngine->DebugLog("Tried To Find Invalid Vertex Buffer Name : " + strKey, 2);
		return -1;
	}

}

int URenderSubsystem::GetIndexBufferIDByName(string strKey)
{
	auto FindIter = StringMappedIndexBufferIDs.find(strKey);

	if (FindIter != StringMappedIndexBufferIDs.end())
	{
		return FindIter->second;
	}
	else
	{
		GEngine->DebugLog("Tried To Find Invalid Index Buffer Name : " + strKey, 2);
		return -1;
	}

}

int URenderSubsystem::GetTextureIDByName(string strKey)
{
	auto FindIter = StringMappedTextureIDs.find(strKey);

	if (FindIter != StringMappedTextureIDs.end())
	{
		return FindIter->second;
	}
	else
	{
		GEngine->DebugLog("Tried To Find Invalid Texture Name : " + strKey, 2);
		return MissingTextureTextureID;
	}

}

int URenderSubsystem::GetSRVIDByName(string strKey)
{
	auto FindIter = StringMappedSRVIDs.find(strKey);

	if (FindIter != StringMappedSRVIDs.end())
	{
		return FindIter->second;
	}
	else
	{
		GEngine->DebugLog("Tried To Find Invalid SRV Name : " + strKey, 2);
		return MissingTextureSRVID;
	}
}

void URenderSubsystem::AddNewVertexBuffer(string strKey, ComPtr<ID3D11Buffer> NewVertexBuffer)
{
	int nSize = (int)VertexBuffers.size();
	std::pair<string, int> MapPair = { strKey, nSize };
	StringMappedVertexBufferIDs.insert(MapPair);
	VertexBuffers.push_back(NewVertexBuffer);
}

void URenderSubsystem::AddNewIndexBuffer(string strKey, ComPtr<ID3D11Buffer> NewIndexBuffer)
{
	int nSize = (int)IndexBuffers.size();
	std::pair<string, int> MapPair = { strKey, nSize };
	StringMappedIndexBufferIDs.insert(MapPair);
	IndexBuffers.push_back(NewIndexBuffer);
}

void URenderSubsystem::AddNewTexture(string strKey, ComPtr<ID3D11Texture2D> NewTexture)
{
	int nSize = (int)Textures.size();
	std::pair<string, int> MapPair = { strKey, nSize };
	StringMappedTextureIDs.insert(MapPair);
	Textures.push_back(NewTexture);
}

void URenderSubsystem::AddNewSRV(string strKey, ComPtr<ID3D11ShaderResourceView> NewSRV)
{
	int nSize = (int)ShaderResourceViews.size();
	std::pair<string, int> MapPair = { strKey, nSize };
	StringMappedSRVIDs.insert(MapPair);
	ShaderResourceViews.push_back(NewSRV);
}


void URenderSubsystem::CreateTransformConstantBuffer()
{
	D3D11_BUFFER_DESC BufferInfo = { 0 };
	BufferInfo.ByteWidth = sizeof(FTransformConstants);
	BufferInfo.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	BufferInfo.CPUAccessFlags = D3D11_CPU_ACCESS_FLAG::D3D11_CPU_ACCESS_WRITE;
	BufferInfo.Usage = D3D11_USAGE_DYNAMIC;

	HRESULT hr = Device->CreateBuffer(&BufferInfo, nullptr, TransformConstantBuffer.GetAddressOf());
	if (hr != S_OK)
	{
		CRITICAL_ERROR(DEFAULT_ERROR_TEXT);
	}
}

void URenderSubsystem::CreateViewport()
{
	D3D11_VIEWPORT ViewPortInfo;
	RECT WindowSize = WindowSubsystem->GetWindowSize();

	ViewPortInfo.Width = (float)WindowSize.right;
	ViewPortInfo.Height = (float)WindowSize.bottom;
	ViewPortInfo.TopLeftX = 0.0f;
	ViewPortInfo.TopLeftY = 0.0f;
	ViewPortInfo.MinDepth = 0.0f;
	ViewPortInfo.MaxDepth = 1.0f;

	DeviceContext->RSSetViewports(1, &ViewPortInfo);
}

void URenderSubsystem::CreateInputLayout()
{
	/* ID3D11InputLayout 생성 */
	vector<D3D11_INPUT_ELEMENT_DESC> InputLayouts;
	D3D11_INPUT_ELEMENT_DESC InputDesc1;
	InputDesc1.SemanticName = "POSITION";
	InputDesc1.InputSlot = 0;
	InputDesc1.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
	InputDesc1.AlignedByteOffset = 0;
	InputDesc1.InputSlotClass = D3D11_INPUT_CLASSIFICATION::D3D11_INPUT_PER_VERTEX_DATA;
	InputDesc1.SemanticIndex = 0;
	InputDesc1.InstanceDataStepRate = 0;
	InputLayouts.push_back(InputDesc1);
	D3D11_INPUT_ELEMENT_DESC InputDesc2;
	InputDesc2.SemanticName = "TEXCOORD";
	InputDesc2.InputSlot = 0;
	InputDesc2.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
	InputDesc2.AlignedByteOffset = sizeof(FVertex::POSITION);
	InputDesc2.InputSlotClass = D3D11_INPUT_CLASSIFICATION::D3D11_INPUT_PER_VERTEX_DATA;
	InputDesc2.SemanticIndex = 0;
	InputDesc2.InstanceDataStepRate = 0;
	InputLayouts.push_back(InputDesc2);
	D3D11_INPUT_ELEMENT_DESC InputDesc3;
	InputDesc3.SemanticName = "COLOR";
	InputDesc3.InputSlot = 0;
	InputDesc3.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
	InputDesc3.AlignedByteOffset = sizeof(FVertex::POSITION) + sizeof(FVertex::TEXCOORD);
	InputDesc3.InputSlotClass = D3D11_INPUT_CLASSIFICATION::D3D11_INPUT_PER_VERTEX_DATA;
	InputDesc3.SemanticIndex = 0;
	InputDesc3.InstanceDataStepRate = 0;
	InputLayouts.push_back(InputDesc3);

	GEngine->RenderSubsystem->GetDevice()->CreateInputLayout(&InputLayouts[0],
		(UINT)InputLayouts.size(),
		VSCodeBlob->GetBufferPointer(),
		VSCodeBlob->GetBufferSize(),
		InputLayout.GetAddressOf());
}

void URenderSubsystem::CreateDefaultSamplerState()
{
	D3D11_SAMPLER_DESC SampInfo = { D3D11_FILTER::D3D11_FILTER_MIN_MAG_MIP_POINT };
	SampInfo.AddressU = D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_BORDER; // 0~1사이만 유효
	SampInfo.AddressV = D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_BORDER; // y
	SampInfo.AddressW = D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_CLAMP; // z // 3중 

	SampInfo.BorderColor[0] = 0.0f;
	SampInfo.BorderColor[1] = 0.0f;
	SampInfo.BorderColor[2] = 0.0f;
	SampInfo.BorderColor[3] = 0.0f;

	HRESULT hr = Device->CreateSamplerState(&SampInfo, DefaultSamplerState.GetAddressOf());
	if (S_OK != hr)
	{
		GEngine->DebugLog("Failed To Create Sampler", 2);
	}
}

ENGINE_API FCamera& URenderSubsystem::GetCamera()
{
	return Camera;
}

void URenderSubsystem::Render(float fDeltaTime)
{
	// Camera.Transform.Position.y += 100.0f;

	DeviceContext->ClearRenderTargetView(RenderTargetView.Get(), RenderTargetViewColor);
	DeviceContext->ClearDepthStencilView(DepthStencilView.Get(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
	DeviceContext->IASetInputLayout(InputLayout.Get());
	DeviceContext->VSSetShader(VertexShader.Get(), nullptr, 0);
	DeviceContext->RSSetViewports(1, &ViewPortInfo);
	DeviceContext->RSSetState(Camera.IsWireFrame ? RasterizerWireframeState.Get() : RasterizerDefaultState.Get());
	DeviceContext->PSSetShader(Camera.IsWireFrame ? WireframePixelShader.Get() : DefaultPixelShader.Get(), nullptr, 0);
	DeviceContext->OMSetRenderTargets(1, RenderTargetView.GetAddressOf(), DepthStencilView.Get());

	this->RenderActors(fDeltaTime);

	Engine->DebugSubsystem->Render();

	HRESULT hr = SwapChain->Present(0, 0);

	if (hr == DXGI_ERROR_DEVICE_REMOVED || hr == DXGI_ERROR_DEVICE_RESET)
	{
		CRITICAL_ERROR("해상도 변경이나 디바이스 관련 설정이 런타임 도중 수정되었습니다");
		return;
	}
}

void URenderSubsystem::RenderActors(float fDeltaTime)
{
	vector<shared_ptr<AActor>>& Actors = Engine->GetWorld()->GetActors();

	for (shared_ptr<AActor>& LoopActor : Actors)
	{
		if (URenderComponent* RenderComponent = LoopActor->GetComponentByClass<URenderComponent>())
		{
			/* 정보 불러오기 및 지역 변수 설정 */
			FMesh& Mesh = GEngine->ResourceSubsystem->GetMeshByID(RenderComponent->MeshID);
			ID3D11Buffer* VertexBuffer = this->VertexBuffers[RenderComponent->VertexBufferID].Get();
			ID3D11Buffer* pVertexBuffer[1];
			pVertexBuffer[0] = VertexBuffer;
			UINT nVertexBufferStride = sizeof(FVertex);
			UINT nVertexBufferOffset = 0;

			ID3D11Buffer* IndexBuffer = this->IndexBuffers[RenderComponent->IndexBufferID].Get();

			/* 메쉬별 렌더링 파이프라인 설정 */
			DeviceContext->IASetVertexBuffers(0, 1, pVertexBuffer, &nVertexBufferStride, &nVertexBufferOffset);
			DeviceContext->IASetPrimitiveTopology(Mesh.PrimitiveTopology);
			DeviceContext->IASetIndexBuffer(IndexBuffer, DXGI_FORMAT::DXGI_FORMAT_R32_UINT, 0);
			this->SetTransformConstantBuffer(LoopActor->GetTransform());
			this->SetShaderResources(RenderComponent->SRVID);



			/* 드로우 콜 */
			DeviceContext->DrawIndexed((UINT)Mesh.Indexes.size(), 0, 0);
		}
	}
}

ID3D11Device* URenderSubsystem::GetDevice() const
{
	return Device.Get();
}

ID3D11DeviceContext* URenderSubsystem::GetDeviceContext() const
{
	return DeviceContext.Get();
}

void URenderSubsystem::LateInit()
{
	WindowSubsystem = Engine->WindowSubsystem;

	this->CreateDeviceAndContext();

	this->InitSwapChain();

	this->CreateVertexShader(VSShader_PATH);

	this->CreateInputLayout();

	this->CreateViewport();

	this->CreateTransformConstantBuffer();

	this->CreateRasterizer();

	this->CreatePixelShaders(PSShader_PATH);

	this->CreateDefaultSamplerState();

	this->CreateDepthStencilView();
}

void URenderSubsystem::CreateVertexShader(string strShaderPath)
{
	std::wstring wstrShaderPath = Utils::StringToWString(strShaderPath);

	int Flag0{};
#ifdef _DEBUG
	Flag0 = D3D10_SHADER_DEBUG;
#endif
	Flag0 |= D3DCOMPILE_PACK_MATRIX_ROW_MAJOR;

	HRESULT hr = D3DCompileFromFile(wstrShaderPath.data(), nullptr, nullptr, "VSMain", "vs_5_0", Flag0, 0, VSCodeBlob.GetAddressOf(), VSErrorCodeBlob.GetAddressOf());
	if (hr != S_OK)
	{
		CRITICAL_ERROR(static_cast<const char *>(VSErrorCodeBlob->GetBufferPointer()));
	}

	hr = Device->CreateVertexShader(VSCodeBlob->GetBufferPointer(), VSCodeBlob->GetBufferSize(), nullptr, VertexShader.GetAddressOf());
	if (hr != S_OK)
	{
		CRITICAL_ERROR(static_cast<const char*>(VSErrorCodeBlob->GetBufferPointer()));
	}
}

void URenderSubsystem::CreateRasterizer()
{
	D3D11_RASTERIZER_DESC DefaultRasterizerDesc = {};
	DefaultRasterizerDesc.CullMode = D3D11_CULL_MODE::D3D11_CULL_NONE;
	DefaultRasterizerDesc.FillMode = D3D11_FILL_MODE::D3D11_FILL_SOLID;
	Device->CreateRasterizerState(&DefaultRasterizerDesc, RasterizerDefaultState.GetAddressOf());

	D3D11_RASTERIZER_DESC WireframeRasterizerDesc = {};
	WireframeRasterizerDesc.CullMode = D3D11_CULL_MODE::D3D11_CULL_NONE;
	WireframeRasterizerDesc.FillMode = D3D11_FILL_MODE::D3D11_FILL_WIREFRAME;
	Device->CreateRasterizerState(&WireframeRasterizerDesc, RasterizerWireframeState.GetAddressOf());


	/* 뷰포트 설정 */
	ViewPortInfo.Width = (float)WindowSubsystem->GetWindowSize().right;
	ViewPortInfo.Height = (float)WindowSubsystem->GetWindowSize().bottom;
	ViewPortInfo.TopLeftX = 0.0f;
	ViewPortInfo.TopLeftY = 0.0f;
	ViewPortInfo.MinDepth = 0.0f;
	ViewPortInfo.MaxDepth = 1.0f;
}

void URenderSubsystem::CreateDepthStencilView()
{
	DXGI_SWAP_CHAIN_DESC SwapChainDesc{};
	SwapChain->GetDesc(&SwapChainDesc);

	D3D11_TEXTURE2D_DESC TextureDesc{};
	TextureDesc.Width = SwapChainDesc.BufferDesc.Width;
	TextureDesc.Height = SwapChainDesc.BufferDesc.Height;
	TextureDesc.MipLevels = 1;
	TextureDesc.ArraySize = 1;
	TextureDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	TextureDesc.SampleDesc.Count = 1;
	TextureDesc.Usage = D3D11_USAGE_DEFAULT;
	TextureDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;

	Device->CreateTexture2D(&TextureDesc, nullptr, DepthStencilBuffer.GetAddressOf());

	HRESULT hr = Device->CreateDepthStencilView(DepthStencilBuffer.Get(), nullptr, DepthStencilView.GetAddressOf());

	if (hr != S_OK)
	{
		CRITICAL_ERROR(ENGINE_INIT_ERROR_TEXT);
	}
}

void URenderSubsystem::CreatePixelShaders(string strShaderPath)
{
	std::wstring wstrShaderPath = Utils::StringToWString(strShaderPath);

	int Flag0{};
#ifdef _DEBUG
	Flag0 = D3D10_SHADER_DEBUG;
#endif
	Flag0 |= D3DCOMPILE_PACK_MATRIX_ROW_MAJOR;

	HRESULT hr = D3DCompileFromFile(wstrShaderPath.data(), nullptr, nullptr, "PSMain", "ps_5_0", Flag0, 0, PSCodeBlob.GetAddressOf(), PSErrorCodeBlob.GetAddressOf());
	if (hr != S_OK)
	{
		CRITICAL_ERROR(static_cast<const char*>(PSErrorCodeBlob->GetBufferPointer()));
	}

	hr = Device->CreatePixelShader(PSCodeBlob->GetBufferPointer(), PSCodeBlob->GetBufferSize(), nullptr, DefaultPixelShader.GetAddressOf());
	if (hr != S_OK)
	{
		CRITICAL_ERROR(static_cast<const char*>(PSErrorCodeBlob->GetBufferPointer()));
	}

	hr = D3DCompileFromFile(wstrShaderPath.data(), nullptr, nullptr, "PSWireframe", "ps_5_0", Flag0, 0, PSCodeBlob.GetAddressOf(), PSErrorCodeBlob.GetAddressOf());
	if (hr != S_OK)
	{
		CRITICAL_ERROR(static_cast<const char*>(PSErrorCodeBlob->GetBufferPointer()));
	}

	hr = Device->CreatePixelShader(PSCodeBlob->GetBufferPointer(), PSCodeBlob->GetBufferSize(), nullptr, WireframePixelShader.GetAddressOf());
	if (hr != S_OK)
	{
		CRITICAL_ERROR(static_cast<const char*>(PSErrorCodeBlob->GetBufferPointer()));
	}
}
