#include "EnginePch.h"
#include "Engine/Engine.h"
#include "RenderCore/RenderSubsystem.h"
#include "Engine/ResourceSubsystem.h"
#include "Engine/DebugSubsystem.h"
#include "Engine/WindowSubsystem.h"
#include "RenderCore/Texture.h"
#include "Utils/Utils.h"
#include "World/World.h"
#include "Level/Level.h"
#include "Actor/Actor.h"
#include "RenderCore/RenderComponent.h"
#include "RenderCore/Widget.h"
#include "IMGUI/imgui.h"
#include "Engine/TimeSubsystem.h"
#include "Engine/KeyInputSubsystem.h"

URenderSubsystem::URenderSubsystem()
	:
	Camera{}
{
	Camera.FOV = 80.0f;
	Camera.Width = DEFAULT_WINDOW_SIZE_X;
	Camera.Height = DEFAULT_WINDOW_SIZE_Y;
	Camera.NearZ = 1.0f;
	Camera.FarZ = 10000.0f;
	Camera.Transform.Position.z = -500.0f;

	RenderTargetViewColor[0] = 103.0f / 255.0f;
	RenderTargetViewColor[1] = 146.0f / 255.0f;
	RenderTargetViewColor[2] = 190.0f / 255.0f;
	RenderTargetViewColor[3] = 1.0f;

	int nSortingLayers = 14;
	int nZValues = 20;
	int nZIndexes = 100;
	RenderOrder.resize(nSortingLayers);

	for (int i = 0; i < nSortingLayers; i++)
		RenderOrder[i].resize(nZValues);

	for (int i = 0; i < nSortingLayers; i++)
		for (int j = 0; j < nZValues; j++)
			RenderOrder[i][j].resize(nZIndexes);

	Transculents.reserve(1000);
}

URenderSubsystem::~URenderSubsystem()
{
	
}

void URenderSubsystem::Tick(float fDeltaTime)
{
	if (!GEngine->IsDebug)
		Render(fDeltaTime);
	else
		DebugRender(fDeltaTime);

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

IDXGISwapChain* URenderSubsystem::GetSwapChain()
{
	return SwapChain.Get();
}

ID3D11ShaderResourceView* URenderSubsystem::GetMainScreenSRV()
{
	return RTVtoSRV.Get();
}

void URenderSubsystem::ReserveMemories()
{
	Textures.reserve(1000);
	StringMappedTextureIDs.reserve(1000);


}

void URenderSubsystem::CreateD3D11Debug()
{
	HRESULT hr;
	hr = Device->QueryInterface(__uuidof(ID3D11Debug), (void**)D3D11Debug.GetAddressOf());

	if (hr != S_OK)
	{
		CRITICAL_ERROR(ENGINE_INIT_ERROR_TEXT);
	}
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

void URenderSubsystem::SetShaderResources(int TextureID)
{
	ID3D11ShaderResourceView* SRVs[1];
	ID3D11SamplerState* Samplers[1];

	SRVs[0] = Textures[TextureID]->SRV.Get();
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

	// Device->CreateTexture2D(null);

	//if (S_OK != Device->CreateRenderTargetView(OffScreenBuffer.Get(), nullptr, &OffScreenRTV))
	//{
	//	CRITICAL_ERROR(ENGINE_INIT_ERROR_TEXT);
	//}

	if (S_OK != Device->CreateShaderResourceView(BackBuffer.Get(), nullptr, &RTVtoSRV))
	{
		CRITICAL_ERROR(ENGINE_INIT_ERROR_TEXT);
	}
}

void URenderSubsystem::MoveCamera(FVector3 _MoveVector)
{
	float fDeltaTime = GEngine->TimeSubsystem->GetDeltaTime();

	DirectX::XMVECTOR MoveXMVector{ _MoveVector.x * fDeltaTime, _MoveVector.y * fDeltaTime, _MoveVector.z * fDeltaTime, 1.0f };

	DirectX::XMMATRIX TranslationMatrix = DirectX::XMMatrixTranslationFromVector(MoveXMVector);

	DirectX::XMMATRIX RotationMatrix = DirectX::XMMatrixRotationRollPitchYaw(
		DirectX::XMConvertToRadians(Camera.Transform.Rotation.x),
		DirectX::XMConvertToRadians(Camera.Transform.Rotation.y),
		DirectX::XMConvertToRadians(Camera.Transform.Rotation.z)
	);
	DirectX::XMMATRIX FinalMatrix = TranslationMatrix * RotationMatrix;
	DirectX::XMVECTOR FinalMoveVector = FinalMatrix.r[3];

	Camera.Transform.Position.x += FinalMoveVector.m128_f32[0];
	Camera.Transform.Position.y += FinalMoveVector.m128_f32[1];
	Camera.Transform.Position.z += FinalMoveVector.m128_f32[2];

}

void URenderSubsystem::SetMissingTexture()
{
	this->MissingTextureTextureID = GEngine->RenderSubsystem->GetTextureIDByName(MISSING_TEXTURE_PATH);
}

int URenderSubsystem::GetPixelShaderIDByName(string strKey)
{
	auto FindIter = StringMappedIndexPixelShaderIDs.find(strKey);

	if (FindIter != StringMappedIndexPixelShaderIDs.end())
	{
		return FindIter->second;
	}
	else
	{
		GEngine->DebugLog("Tried To Find Invalid Pixel Shader : " + strKey, 2);
		return -1;
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
		return GEngine->ResourceSubsystem->LoadTextureFile(strKey);
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

int URenderSubsystem::AddNewTexture(string strKey, shared_ptr<UTexture> NewTexture)
{
	int nSize = (int)Textures.size();
	std::pair<string, int> MapPair = { strKey, nSize };
	StringMappedTextureIDs.insert(MapPair);
	Textures.push_back(NewTexture);
	return nSize;
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

void URenderSubsystem::ReleaseTextures()
{
	Textures.clear();
	StringMappedTextureIDs.clear();
	this->SetMissingTexture();
}

void URenderSubsystem::RotateCameraByMousePosition()
{
	POINT CurrentMousePosition = GEngine->KeyInputSubsystem->GetMousePosition();

	if (LastMousePosition.x == 0 && LastMousePosition.y == 0)
	{
		LastMousePosition = CurrentMousePosition;
		return;
	}

	FVector3 VectorDiff{ (float)(CurrentMousePosition.x - LastMousePosition.x), (float)(CurrentMousePosition.y - LastMousePosition.y) };

	Camera.Transform.Rotation.y += VectorDiff.x;
	Camera.Transform.Rotation.x += VectorDiff.y;
	LastMousePosition = CurrentMousePosition;
}

void URenderSubsystem::ResetCameraMousePosition()
{
	LastMousePosition = { 0, 0 };
}

FCamera& URenderSubsystem::GetCamera()
{
	return Camera;
}

void URenderSubsystem::RenderWidgets(float fDeltaTime)
{
	int nPlaneMeshID = GEngine->ResourceSubsystem->GetMeshIDByName("Plane");
	FMesh& Mesh = GEngine->ResourceSubsystem->GetMeshByID(nPlaneMeshID);

	ID3D11Buffer* pVertexBuffer[] = { this->VertexBuffers[nPlaneMeshID].Get() };
	ID3D11Buffer* IndexBuffer = { this->IndexBuffers[nPlaneMeshID].Get() };
	UINT nVertexBufferStride = sizeof(FVertex);
	UINT nVertexBufferOffset = 0;

	DeviceContext->OMSetRenderTargets(1, RenderTargetView.GetAddressOf(), nullptr);
	DeviceContext->IASetVertexBuffers(0, 1, pVertexBuffer, &nVertexBufferStride, &nVertexBufferOffset);
	DeviceContext->IASetPrimitiveTopology(Mesh.PrimitiveTopology);
	DeviceContext->IASetIndexBuffer(IndexBuffer, DXGI_FORMAT::DXGI_FORMAT_R32_UINT, 0);

	UGameInstance* GameInstance = GEngine->GetGameInstance();

	auto Widgets = GameInstance->GetWidgets();

	for (int i = 0; i < Widgets.size(); i++)
	{
		for (shared_ptr<UWidget>& Widget : Widgets[i])
		{
			int nPSShaderID = Widget->GetPSShaderID();

			DeviceContext->PSSetShader(PixelShaders[nPSShaderID].Get(), nullptr, 0);
			// this->SetTransformConstantBuffer(RenderComponent->Owner->GetTransform());
			// this->SetShaderResources(RenderComponent->Material->TextureID);


			/* 드로우 콜 */
			DeviceContext->DrawIndexed((UINT)Mesh.Indexes.size(), 0, 0);
		}
	}
}

void URenderSubsystem::DebugRender(float fDeltaTime)
{
	DeviceContext->ClearRenderTargetView(RenderTargetView.Get(), RenderTargetViewColor);
	DeviceContext->ClearDepthStencilView(DepthStencilView.Get(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
	DeviceContext->IASetInputLayout(InputLayout.Get());
	DeviceContext->VSSetShader(VertexShader.Get(), nullptr, 0);
	DeviceContext->RSSetViewports(1, &ViewPortInfo);

	if (Camera.IsWireFrame)
		DeviceContext->RSSetState(RasterizerWireframeState.Get());

	else
		DeviceContext->RSSetState(RasterizerDefaultState.Get());

	DeviceContext->OMSetBlendState(DefaultBlendState.Get(), nullptr, 0xFFFFFFFF);
	DeviceContext->OMSetDepthStencilState(DefaultDepthStencilState.Get(), 1);


	this->RenderActors(fDeltaTime);

	this->RenderWidgets(fDeltaTime);

	Engine->DebugSubsystem->Render();

	HRESULT hr = SwapChain->Present(0, 0);

	if (hr == DXGI_ERROR_DEVICE_REMOVED || hr == DXGI_ERROR_DEVICE_RESET)
	{
		CRITICAL_ERROR("해상도 변경이나 디바이스 관련 설정이 런타임 도중 수정되었습니다");
		return;
	}
}

void URenderSubsystem::Render(float fDeltaTime)
{
	DeviceContext->ClearRenderTargetView(RenderTargetView.Get(), RenderTargetViewColor);
	DeviceContext->ClearDepthStencilView(DepthStencilView.Get(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
	DeviceContext->IASetInputLayout(InputLayout.Get());
	DeviceContext->VSSetShader(VertexShader.Get(), nullptr, 0);
	DeviceContext->RSSetViewports(1, &ViewPortInfo);

	if (Camera.IsWireFrame)
		DeviceContext->RSSetState(RasterizerWireframeState.Get());

	else
		DeviceContext->RSSetState(RasterizerDefaultState.Get());

	DeviceContext->OMSetBlendState(DefaultBlendState.Get(), nullptr, 0xFFFFFFFF);
	DeviceContext->OMSetDepthStencilState(DefaultDepthStencilState.Get(), 1);


	this->RenderActors(fDeltaTime);

	this->RenderWidgets(fDeltaTime);

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
	Transculents.clear();

	DeviceContext->OMSetRenderTargets(1, RenderTargetView.GetAddressOf(), DepthStencilView.Get());


	for (shared_ptr<AActor>& SharedActor : Actors)
	{
		if (URenderComponent* RenderComponent = SharedActor->GetComponentByClass<URenderComponent>())
		{
			if (SharedActor->GetIsBeginPlayed() && RenderComponent->IsVisible)
			{
				int i = RenderComponent->GetSortingLayer();
				int j = RenderComponent->GetZValue();
				int k = RenderComponent->GetZIndex();
				RenderOrder[i][j][k].push_back(RenderComponent);
			}
		}
	}

	for (int i = 0; i < RenderOrder.size(); i++)
	{
		for (int j = 0; j < RenderOrder[i].size(); j++)
		{
			for (int k = 0; k < RenderOrder[i][j].size(); k++)
			{
				for (URenderComponent* RenderComponent : RenderOrder[i][j][k])
				{
					/* Transculent 머티리얼을 가진 경우 나중에 렌더링 */
					if (RenderComponent->Material->BlendMode == UMaterial::EBlendMode::Transculent)
					{
						Transculents.push_back(RenderComponent);
						continue;
					}


					/* 정보 불러오기 및 지역 변수 설정 */
					FMesh& Mesh = GEngine->ResourceSubsystem->GetMeshByID(RenderComponent->MeshID);
					ID3D11Buffer* VertexBuffer = this->VertexBuffers[RenderComponent->MeshID].Get();
					ID3D11Buffer* pVertexBuffer[1];
					pVertexBuffer[0] = VertexBuffer;
					UINT nVertexBufferStride = sizeof(FVertex);
					UINT nVertexBufferOffset = 0;

					ID3D11Buffer* IndexBuffer = this->IndexBuffers[RenderComponent->MeshID].Get();

					/* 메쉬별 렌더링 파이프라인 설정 */
					int nPSShaderID{};
					if (Camera.IsWireFrame)
						nPSShaderID = WireframePixelShaderID;

					else
					{
						if (i >= Camera.DebugLayerLevel)
							nPSShaderID = GreenOutlinePixelShaderID;

						else
							nPSShaderID = RenderComponent->Material->PSShaderID;
					}


					DeviceContext->PSSetShader(PixelShaders[nPSShaderID].Get(), nullptr, 0);
					DeviceContext->IASetVertexBuffers(0, 1, pVertexBuffer, &nVertexBufferStride, &nVertexBufferOffset);
					DeviceContext->IASetPrimitiveTopology(Mesh.PrimitiveTopology);
					DeviceContext->IASetIndexBuffer(IndexBuffer, DXGI_FORMAT::DXGI_FORMAT_R32_UINT, 0);
					this->SetTransformConstantBuffer(RenderComponent->Owner->GetTransform());
					this->SetShaderResources(RenderComponent->Material->TextureID);


					/* 드로우 콜 */
					DeviceContext->DrawIndexed((UINT)Mesh.Indexes.size(), 0, 0);
				}
			}
		}
	}

	/* Transculents 후처리 */
	DeviceContext->OMSetRenderTargets(1, RenderTargetView.GetAddressOf(), ReadOnlyDepthStencilView.Get());
	for (URenderComponent* RenderComponent : Transculents)
	{
		/* 정보 불러오기 및 지역 변수 설정 */
		FMesh& Mesh = GEngine->ResourceSubsystem->GetMeshByID(RenderComponent->MeshID);
		ID3D11Buffer* VertexBuffer = this->VertexBuffers[RenderComponent->MeshID].Get();
		ID3D11Buffer* pVertexBuffer[1];
		pVertexBuffer[0] = VertexBuffer;
		UINT nVertexBufferStride = sizeof(FVertex);
		UINT nVertexBufferOffset = 0;

		ID3D11Buffer* IndexBuffer = this->IndexBuffers[RenderComponent->MeshID].Get();

		/* 메쉬별 렌더링 파이프라인 설정 */
		int nPSShaderID{};
		if (Camera.IsWireFrame)
			nPSShaderID = WireframePixelShaderID;

		else
		{
			if (Camera.DebugLayerLevel <= 11)
				nPSShaderID = GreenOutlinePixelShaderID;

			else
				nPSShaderID = RenderComponent->Material->PSShaderID;
		}
		DeviceContext->PSSetShader(PixelShaders[nPSShaderID].Get(), nullptr, 0);
		DeviceContext->IASetVertexBuffers(0, 1, pVertexBuffer, &nVertexBufferStride, &nVertexBufferOffset);
		DeviceContext->IASetPrimitiveTopology(Mesh.PrimitiveTopology);
		DeviceContext->IASetIndexBuffer(IndexBuffer, DXGI_FORMAT::DXGI_FORMAT_R32_UINT, 0);
		this->SetTransformConstantBuffer(RenderComponent->Owner->GetTransform());
		int a = RenderComponent->Material->TextureID;
		this->SetShaderResources(a);


		/* 드로우 콜 */
		DeviceContext->DrawIndexed((UINT)Mesh.Indexes.size(), 0, 0);
	}

	for (int i = 0; i < RenderOrder.size(); i++)
		for (int j = 0; j < RenderOrder[i].size(); j++)
			for (int k = 0; k < RenderOrder[i][j].size(); k++)
				RenderOrder[i][j][k].clear();

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

	this->ReserveMemories();
#ifdef _DEBUG
	this->CreateD3D11Debug();
#endif
	this->InitSwapChain();

	this->CreateVertexShader(VSShader_PATH);

	this->CreateInputLayout();

	this->CreateViewport();

	this->CreateTransformConstantBuffer();

	this->CreateRasterizer();

	this->CreatePixelShaders(PSShader_PATH);

	this->CreateDefaultSamplerState();

	this->CreateDepthStencilView();

	this->CreateBlendState();
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
	HRESULT hr;
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

	DepthStencilBuffer = nullptr;
	Device->CreateTexture2D(&TextureDesc, nullptr, DepthStencilBuffer.ReleaseAndGetAddressOf());

	DepthStencilView = nullptr;
	hr = Device->CreateDepthStencilView(DepthStencilBuffer.Get(), nullptr, DepthStencilView.ReleaseAndGetAddressOf());

	if (hr != S_OK)
	{
		CRITICAL_ERROR(ENGINE_INIT_ERROR_TEXT);
	}

	D3D11_DEPTH_STENCIL_VIEW_DESC ReadOnlyDSVDesc{};
	ReadOnlyDSVDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	ReadOnlyDSVDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	ReadOnlyDSVDesc.Flags = D3D11_DSV_READ_ONLY_DEPTH | D3D11_DSV_READ_ONLY_STENCIL;

	ReadOnlyDepthStencilView = nullptr;
	hr = Device->CreateDepthStencilView(DepthStencilBuffer.Get(), &ReadOnlyDSVDesc, ReadOnlyDepthStencilView.ReleaseAndGetAddressOf());

	if (hr != S_OK)
	{
		CRITICAL_ERROR(ENGINE_INIT_ERROR_TEXT);
	}

	D3D11_DEPTH_STENCIL_DESC dsDesc = {};
	dsDesc.DepthEnable = TRUE;
	dsDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	dsDesc.DepthFunc = D3D11_COMPARISON_LESS_EQUAL;
	DefaultDepthStencilState = nullptr;
	Device->CreateDepthStencilState(&dsDesc, DefaultDepthStencilState.ReleaseAndGetAddressOf());
}

void URenderSubsystem::CreateBlendState()
{
	D3D11_BLEND_DESC BlendDesc = {};
	BlendDesc.RenderTarget[0].BlendEnable = TRUE;
	BlendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;       // 소스 픽셀의 알파값 사용
	BlendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;   // 1 - 알파
	BlendDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
	BlendDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
	BlendDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
	BlendDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
	BlendDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

	Device->CreateBlendState(&BlendDesc, DefaultBlendState.GetAddressOf());
}

void URenderSubsystem::CreatePixelShaders(string strShaderPath)
{
	std::wstring wstrShaderPath = Utils::StringToWString(strShaderPath);

	HRESULT hr;
	int Flag0{};
#ifdef _DEBUG
	Flag0 = D3D10_SHADER_DEBUG;
#endif
	Flag0 |= D3DCOMPILE_PACK_MATRIX_ROW_MAJOR;



	/* Default Pixel Shader 생성 */
	ComPtr<ID3D11PixelShader> DefaultPixelShader;
	hr = D3DCompileFromFile(wstrShaderPath.data(), nullptr, nullptr, DEFAULT_PIXEL_SHADER_NAME, "ps_5_0", Flag0, 0, PSCodeBlob.GetAddressOf(), PSErrorCodeBlob.GetAddressOf());
	if (hr != S_OK)
	{
		CRITICAL_ERROR(static_cast<const char*>(PSErrorCodeBlob->GetBufferPointer()));
	}
	hr = Device->CreatePixelShader(PSCodeBlob->GetBufferPointer(), PSCodeBlob->GetBufferSize(), nullptr, DefaultPixelShader.GetAddressOf());
	if (hr != S_OK)
	{
		CRITICAL_ERROR(static_cast<const char*>(PSErrorCodeBlob->GetBufferPointer()));
	}
	StringMappedIndexPixelShaderIDs.insert(std::make_pair(DEFAULT_PIXEL_SHADER_NAME, (int)PixelShaders.size()));
	PixelShaders.push_back(DefaultPixelShader);

	/* Transparent Pixel Shader 생성 */
	{
		ComPtr<ID3D11PixelShader> TransparentPixelShader;
		hr = D3DCompileFromFile(wstrShaderPath.data(), nullptr, nullptr, TRANSPARENT_PIXEL_SHADER_NAME, "ps_5_0", Flag0, 0, PSCodeBlob.GetAddressOf(), PSErrorCodeBlob.GetAddressOf());
		if (hr != S_OK)
		{
			CRITICAL_ERROR(static_cast<const char*>(PSErrorCodeBlob->GetBufferPointer()));
		}
		hr = Device->CreatePixelShader(PSCodeBlob->GetBufferPointer(), PSCodeBlob->GetBufferSize(), nullptr, TransparentPixelShader.GetAddressOf());
		if (hr != S_OK)
		{
			CRITICAL_ERROR(static_cast<const char*>(PSErrorCodeBlob->GetBufferPointer()));
		}
		int nPixelShaderID = (int)PixelShaders.size();
		StringMappedIndexPixelShaderIDs.insert(std::make_pair(TRANSPARENT_PIXEL_SHADER_NAME, (int)PixelShaders.size()));
		PixelShaders.push_back(TransparentPixelShader);
		this->TransparentPixelShaderID = nPixelShaderID;
	}

	/* Green Outlined Pixel Shader 생성 */
	{
		ComPtr<ID3D11PixelShader> GreenOutlinedPixelShader;
		hr = D3DCompileFromFile(wstrShaderPath.data(), nullptr, nullptr, BOX_OUTLINED_GREEN_PIXEL_SHADER_NAME, "ps_5_0", Flag0, 0, PSCodeBlob.GetAddressOf(), PSErrorCodeBlob.GetAddressOf());
		if (hr != S_OK)
		{
			CRITICAL_ERROR(static_cast<const char*>(PSErrorCodeBlob->GetBufferPointer()));
		}
		hr = Device->CreatePixelShader(PSCodeBlob->GetBufferPointer(), PSCodeBlob->GetBufferSize(), nullptr, GreenOutlinedPixelShader.GetAddressOf());
		if (hr != S_OK)
		{
			CRITICAL_ERROR(static_cast<const char*>(PSErrorCodeBlob->GetBufferPointer()));
		}
		int nPixelShaderID = (int)PixelShaders.size();
		StringMappedIndexPixelShaderIDs.insert(std::make_pair(BOX_OUTLINED_GREEN_PIXEL_SHADER_NAME, (int)PixelShaders.size()));
		PixelShaders.push_back(GreenOutlinedPixelShader);
		this->GreenOutlinePixelShaderID = nPixelShaderID;
	}

	/* Wireframe Pixel Shader 생성 */
	ComPtr<ID3D11PixelShader> WireframePixelShader;
	hr = D3DCompileFromFile(wstrShaderPath.data(), nullptr, nullptr, WIREFRAME_PIXEL_SHADER_NAME, "ps_5_0", Flag0, 0, PSCodeBlob.GetAddressOf(), PSErrorCodeBlob.GetAddressOf());
	if (hr != S_OK)
	{
		CRITICAL_ERROR(static_cast<const char*>(PSErrorCodeBlob->GetBufferPointer()));
	}
	hr = Device->CreatePixelShader(PSCodeBlob->GetBufferPointer(), PSCodeBlob->GetBufferSize(), nullptr, WireframePixelShader.GetAddressOf());
	if (hr != S_OK)
	{
		CRITICAL_ERROR(static_cast<const char*>(PSErrorCodeBlob->GetBufferPointer()));
	}
	int nWireframePixelShaderID = (int)PixelShaders.size();
	StringMappedIndexPixelShaderIDs.insert(std::make_pair(WIREFRAME_PIXEL_SHADER_NAME, nWireframePixelShaderID));
	PixelShaders.push_back(WireframePixelShader);
	this->WireframePixelShaderID = nWireframePixelShaderID;

	/* Wireframe Pixel Shader 생성 */
	ComPtr<ID3D11PixelShader> GreenPixelShader;
	hr = D3DCompileFromFile(wstrShaderPath.data(), nullptr, nullptr, GREEN_PIXEL_SHADER_NAME, "ps_5_0", Flag0, 0, PSCodeBlob.GetAddressOf(), PSErrorCodeBlob.GetAddressOf());
	if (hr != S_OK)
	{
		CRITICAL_ERROR(static_cast<const char*>(PSErrorCodeBlob->GetBufferPointer()));
	}
	hr = Device->CreatePixelShader(PSCodeBlob->GetBufferPointer(), PSCodeBlob->GetBufferSize(), nullptr, GreenPixelShader.GetAddressOf());
	if (hr != S_OK)
	{
		CRITICAL_ERROR(static_cast<const char*>(PSErrorCodeBlob->GetBufferPointer()));
	}
	int nGreenPixelShaderID = (int)PixelShaders.size();
	StringMappedIndexPixelShaderIDs.insert(std::make_pair(GREEN_PIXEL_SHADER_NAME, nGreenPixelShaderID));
	PixelShaders.push_back(GreenPixelShader);
}


