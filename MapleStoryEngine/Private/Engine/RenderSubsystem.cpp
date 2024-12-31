#include "EnginePch.h"
#include "Engine/Engine.h"
#include "Engine/RenderSubsystem.h"
#include "Engine/ResourceSubsystem.h"
#include "Engine/DebugSubsystem.h"
#include "Engine/WindowSubsystem.h"
#include "Utils/Encoding.h"
#include "World/World.h"
#include "Level/Level.h"
#include "Actor/Actor.h"
#include "ActorComponent/RenderComponent.h"
#include "IMGUI/imgui.h"

URenderSubsystem::URenderSubsystem()
	:
	Camera{}
{
	Camera.Width = 1920.0f;
	Camera.Height = 1080.0f;
	Camera.NearZ = 0.1f;
	Camera.FarZ = 5000.0f;

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

	DirectX::XMMATRIX RotationMatrix = DirectX::XMMatrixRotationRollPitchYawFromVector(DirectX::XMVECTOR{ Transform.Rotation.x, Transform.Rotation.y , Transform.Rotation.z });

	DirectX::XMMATRIX TranslationMatrix = DirectX::XMMatrixTranslationFromVector(DirectX::XMVECTOR{ Transform.Position.x, Transform.Position.y , Transform.Position.z });

	DirectX::XMMATRIX WorldMatrix = ScaleMatrix * RotationMatrix * TranslationMatrix;

	/* 뷰 행렬 연산 */
	DirectX::XMVECTOR CameraPos{ Camera.Transform.Position.x, Camera.Transform.Position.y , Camera.Transform.Position.z , 1.0f };

	DirectX::XMVECTOR CameraRot{ Camera.Transform.Rotation.x, Camera.Transform.Rotation.y , Camera.Transform.Rotation.z };

	DirectX::XMMATRIX RotMatrix = DirectX::XMMatrixRotationRollPitchYaw(
		DirectX::XMConvertToRadians(Transform.Rotation.x),
		DirectX::XMConvertToRadians(Transform.Rotation.y),
		DirectX::XMConvertToRadians(Transform.Rotation.z)
	);

	DirectX::XMVECTOR DefaultForward = DirectX::XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f);
	DirectX::XMVECTOR DefaultUp = DirectX::XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
	DirectX::XMVECTOR EyeDir = DirectX::XMVector3TransformNormal(DefaultForward, RotMatrix);
	DirectX::XMVECTOR UpDir = DirectX::XMVector3TransformNormal(DefaultUp, RotMatrix);

	DirectX::XMMATRIX ViewMatrix = DirectX::XMMatrixLookToLH(CameraPos, EyeDir, UpDir);

	/* 투영 행렬 연산 */
	DirectX::XMMATRIX ProjectionMatrix = DirectX::XMMatrixOrthographicLH(Camera.Width, Camera.Height, Camera.NearZ, Camera.FarZ);

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

	if (S_OK != Device->CreateRenderTargetView(BackBuffer.Get(), nullptr, &RTV))
	{
		CRITICAL_ERROR(ENGINE_INIT_ERROR_TEXT);
	}
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

ID3D11Buffer* URenderSubsystem::GetD3DVertexBuffer(string strName)
{
	auto FindIter = VertexBuffers.find(strName);

	if (FindIter == VertexBuffers.end())
	{
		GEngine->DebugLog("GetD3DVertexBuffer()로 유효한 키를 찾지 못함", 1);
		return nullptr;
	}

	return FindIter->second.Get();
}

ID3D11Buffer* URenderSubsystem::GetD3DIndexBuffer(string strName)
{
	auto FindIter = IndexBuffers.find(strName);

	if (FindIter == IndexBuffers.end())
	{
		GEngine->DebugLog("GetD3DIndexBuffer()로 유효한 키를 찾지 못함", 1);
		return nullptr;
	}

	return FindIter->second.Get();
}

void URenderSubsystem::Render(float fDeltaTime)
{
	/* 오류날시 omsetrendertargets의 RTV.GetAddressOf()를 지역변수로 치환해서 넘기는것으로 변경 */
	DeviceContext->ClearRenderTargetView(RTV.Get(), RenderTargetViewColor);
	DeviceContext->IASetInputLayout(InputLayout.Get());
	DeviceContext->VSSetShader(VertexShader.Get(), nullptr, 0);
	DeviceContext->RSSetViewports(1, &ViewPortInfo);
	DeviceContext->RSSetState(RasterizerState.Get());
	DeviceContext->PSSetShader(PixelShader.Get(), nullptr, 0);
	DeviceContext->OMSetRenderTargets(1, RTV.GetAddressOf(), nullptr);

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
			const char* MeshName = RenderComponent->GetMeshName();
			FMesh& Mesh = GEngine->ResourceSubsystem->GetMesh(MeshName);
			ID3D11Buffer* VertexBuffer = GetD3DVertexBuffer(MeshName);
			ID3D11Buffer* pVertexBuffer[1];
			pVertexBuffer[0] = VertexBuffer;
			UINT nVertexBufferStride = sizeof(FVertex);
			UINT nVertexBufferOffset = 0;

			ID3D11Buffer* IndexBuffer = GetD3DIndexBuffer(MeshName);

			/* WVP 변환 */
			this->SetTransformConstantBuffer(LoopActor->GetTransform());

			/* 메쉬별 렌더링 파이프라인 설정 */
			DeviceContext->IASetVertexBuffers(0, 1, pVertexBuffer, &nVertexBufferStride, &nVertexBufferOffset);
			DeviceContext->IASetPrimitiveTopology(Mesh.PrimitiveTopology);
			DeviceContext->IASetIndexBuffer(IndexBuffer, DXGI_FORMAT::DXGI_FORMAT_R32_UINT, 0);
			DeviceContext->VSSetConstantBuffers(0, 1, TransformConstantBuffer.GetAddressOf());
			// DeviceContext->PSSetShaderResources();
			// DeviceContext->PSSetSamplers();


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

	this->CreateVertexShader();

	this->CreateInputLayout();

	this->CreateViewport();

	this->CreateTransformConstantBuffer();

	this->CreateRasterizer();

	this->CreatePixelShader();

}

void URenderSubsystem::CreateVertexShader()
{
	HRESULT hr = D3DCompileFromFile(L"Resources\\Shaders\\test.hlsl", nullptr, nullptr, "DefaultVertexShader", "vs_5_0", 0, 0, VSCodeBlob.GetAddressOf(), VSErrorCodeBlob.GetAddressOf());
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
	D3D11_RASTERIZER_DESC RasterizerDesc = {};
	RasterizerDesc.CullMode = D3D11_CULL_MODE::D3D11_CULL_NONE;
	RasterizerDesc.FillMode = D3D11_FILL_MODE::D3D11_FILL_SOLID;

	Device->CreateRasterizerState(&RasterizerDesc, RasterizerState.GetAddressOf());

	/* 뷰포트 설정 */
	ViewPortInfo.Width = (float)WindowSubsystem->GetWindowSize().right;
	ViewPortInfo.Height = (float)WindowSubsystem->GetWindowSize().bottom;
	ViewPortInfo.TopLeftX = 0.0f;
	ViewPortInfo.TopLeftY = 0.0f;
	ViewPortInfo.MinDepth = 0.0f;
	ViewPortInfo.MaxDepth = 1.0f;
}

void URenderSubsystem::CreatePixelShader()
{
	int Flag0{};
#ifdef _DEBUG
	Flag0 = D3D10_SHADER_DEBUG;
#endif
	Flag0 |= D3DCOMPILE_PACK_MATRIX_ROW_MAJOR;

	HRESULT hr = D3DCompileFromFile(L"Resources\\Shaders\\test.hlsl", nullptr, nullptr, "DefaultPixelShader", "ps_5_0", Flag0, 0, PSCodeBlob.GetAddressOf(), PSErrorCodeBlob.GetAddressOf());
	if (hr != S_OK)
	{
		CRITICAL_ERROR(static_cast<const char*>(PSErrorCodeBlob->GetBufferPointer()));
	}

	hr = Device->CreatePixelShader(PSCodeBlob->GetBufferPointer(), PSCodeBlob->GetBufferSize(), nullptr, PixelShader.GetAddressOf());
	if (hr != S_OK)
	{
		CRITICAL_ERROR(static_cast<const char*>(PSErrorCodeBlob->GetBufferPointer()));
	}
}
