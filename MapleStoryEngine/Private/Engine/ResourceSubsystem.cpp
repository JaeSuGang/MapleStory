#include "EnginePch.h"
#include "Utils/Utils.h"
#include "Engine/ResourceSubsystem.h"
#include "Engine/RenderSubsystem.h"
#include "Math/Mesh.h"
#include "Engine/Engine.h"

UResourceSubsystem::UResourceSubsystem()
{
	this->SetWorkingDirectory();
}

void UResourceSubsystem::Tick(float fDeltaTime)
{
}

void UResourceSubsystem::LateInit()
{
	this->LoadFolder(RESOURCES_FOLDER_NAME);

	this->GenerateDefaultMeshes();
}


FMesh& UResourceSubsystem::GetMesh(string strKey)
{
	auto FindIter = Meshes.find(strKey);

	if (FindIter == Meshes.end())
		GEngine->DebugLog("존재하지 않는 메쉬 이름을 참조", 1);

	return FindIter->second;
}

void UResourceSubsystem::SetWorkingDirectory()
{
	if (std::filesystem::exists(RESOURCES_FOLDER_NAME))
	{
		// this->ResourcePath = std::filesystem::current_path() / RESOURCES_FOLDER_NAME;
		return;
	}

	std::filesystem::current_path(std::filesystem::current_path().parent_path());

	if (std::filesystem::exists(RESOURCES_FOLDER_NAME))
	{
		// this->ResourcePath = std::filesystem::current_path() / RESOURCES_FOLDER_NAME;
		return;
	}
	 
	CRITICAL_ERROR(RESOURCE_FOLDER_FIND_FAILED_TEXT);
}

void UResourceSubsystem::LoadFolder(string strDirectoryName)
{
	std::filesystem::directory_iterator DirectoryIter{ strDirectoryName };

	while (!DirectoryIter._At_end())
	{
		std::filesystem::path ChildPath = *DirectoryIter;

		if (DirectoryIter->is_directory())
		{
			this->LoadFolder(ChildPath.string());
		}

		if (ChildPath.extension().string() == ".png")
		{
			this->LoadTextureFile(ChildPath.string());
		}

		++DirectoryIter;
	}
}

void UResourceSubsystem::LoadTextureFile(string strPath)
{
	std::wstring wstrPath = Utils::StringToWString(strPath);

	ComPtr<ID3D11ShaderResourceView> NewSRV;
	ComPtr<ID3D11Texture2D> NewTexture;
	DirectX::ScratchImage NewScratchImage;
	DirectX::TexMetadata NewTexMetadata;

	if (S_OK != DirectX::LoadFromWICFile(wstrPath.c_str(), DirectX::WIC_FLAGS_NONE, &NewTexMetadata, NewScratchImage))
	{
		GEngine->DebugLog("Texture File Load Failed" + strPath, 1);
		return;
	}

	if (S_OK != DirectX::CreateTexture(GEngine->RenderSubsystem->Device.Get(), NewScratchImage.GetImages(), NewScratchImage.GetImageCount(), NewTexMetadata, (ID3D11Resource**)NewTexture.GetAddressOf()))
	{
		GEngine->DebugLog("Texture Creation Failed" + strPath, 1);
		return;
	}

	/* 텍스쳐를 만들지 않고 ScratchImage를 바로 SRV로 만드는 DirectXTex함수 */
	/* CreateShaderResourceView(GEngine->RenderSubsystem->Device.Get(), NewScratchImage.GetImages(), NewScratchImage.GetImageCount(), NewScratchImage.GetMetadata(), NewSRV.GetAddressOf())) */

	// 만일 오류날 경우 srv desc작성
	if (S_OK != GEngine->RenderSubsystem->Device->CreateShaderResourceView(NewTexture.Get(), nullptr, NewSRV.GetAddressOf()))
	{
		GEngine->DebugLog("SRV Creation Failed" + strPath, 1);
		return;
	}

	std::pair<string, ComPtr<ID3D11Texture2D>> NewTexturePair{ strPath, NewTexture };
	std::pair<string, ComPtr<ID3D11ShaderResourceView>> NewSRVPair{ strPath, NewSRV };
	GEngine->RenderSubsystem->Textures.insert(NewTexturePair);
	GEngine->RenderSubsystem->ShaderResourceViews.insert(NewSRVPair);
}

void UResourceSubsystem::GenerateDefaultMeshes()
{
	this->GeneratePlaneMesh();

	this->GenerateCubeMesh();
}

void UResourceSubsystem::GeneratePlaneMesh()
{
	/* FMesh 생성 */
	FVertex v1{};
	v1.POSITION = { -10.0f, 10.0f, 0.0f, 1.0f };
	v1.TEXCOORD = { 0.0f, 0.0f };
	FVertex v2{};
	v2.POSITION = { 10.0f, 10.0f, 0.0f, 1.0f };
	v2.TEXCOORD = { 1.0f, 0.0f };
	FVertex v3{};
	v3.POSITION = { -10.0f, -10.0f, 0.0f, 1.0f };
	v3.TEXCOORD = { 0.0f, 1.0f };
	FVertex v4{};
	v4.POSITION = { 10.0f, -10.0f, 0.0f, 1.0f };
	v4.TEXCOORD = { 1.0f, 1.0f };

	FMesh Plane;
	Plane.Vertices.push_back(v1);
	Plane.Vertices.push_back(v2);
	Plane.Vertices.push_back(v3);
	Plane.Vertices.push_back(v4);

	Plane.Indexes.push_back(0);
	Plane.Indexes.push_back(1);
	Plane.Indexes.push_back(2);

	Plane.Indexes.push_back(1);
	Plane.Indexes.push_back(3);
	Plane.Indexes.push_back(2);

	Plane.PrimitiveTopology = D3D11_PRIMITIVE_TOPOLOGY::D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;

	std::pair<string, FMesh> Pair{};
	Pair.first = "Plane";
	Pair.second = Plane;

	Meshes.insert(Pair);

	/* ID3D11Buffer 생성 */
	ComPtr<ID3D11Buffer> VertexBuffer{};

	D3D11_BUFFER_DESC VertexBufferDesc{};
	VertexBufferDesc.ByteWidth = (UINT)(sizeof(Plane.Vertices[0]) * Plane.Vertices.size());
	VertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	VertexBufferDesc.CPUAccessFlags = 0;
	VertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	D3D11_SUBRESOURCE_DATA VertexBufferSubresourceData;
	VertexBufferSubresourceData.pSysMem = &Plane.Vertices[0];

	if (S_OK != GEngine->RenderSubsystem->GetDevice()->CreateBuffer(&VertexBufferDesc, &VertexBufferSubresourceData, VertexBuffer.GetAddressOf()))
	{
		CRITICAL_ERROR(BUFFER_CREATE_FAILED_TEXT);
	}

	std::pair<string, ComPtr<ID3D11Buffer>> VertexBufferPair{};
	VertexBufferPair.first = "Plane";
	VertexBufferPair.second = VertexBuffer;
	GEngine->RenderSubsystem->VertexBuffers.insert(VertexBufferPair);


	/* IndexBuffer 생성 */
	ComPtr<ID3D11Buffer> IndexBuffer{};

	D3D11_BUFFER_DESC IndexBufferInfo{};
	IndexBufferInfo.ByteWidth = (UINT)(sizeof(Plane.Indexes[0]) * Plane.Indexes.size());
	IndexBufferInfo.BindFlags = D3D11_BIND_INDEX_BUFFER;
	IndexBufferInfo.CPUAccessFlags = 0;
	IndexBufferInfo.Usage = D3D11_USAGE_DEFAULT;

	D3D11_SUBRESOURCE_DATA IndexBufferSubresourceData{};
	IndexBufferSubresourceData.pSysMem = &Plane.Indexes[0];

	if (S_OK != GEngine->RenderSubsystem->GetDevice()->CreateBuffer(&IndexBufferInfo, &IndexBufferSubresourceData, IndexBuffer.GetAddressOf()))
	{
		CRITICAL_ERROR(BUFFER_CREATE_FAILED_TEXT);
	}

	std::pair<string, ComPtr<ID3D11Buffer>> IndexBufferPair{};
	IndexBufferPair.first = "Plane";
	IndexBufferPair.second = IndexBuffer;
	GEngine->RenderSubsystem->IndexBuffers.insert(IndexBufferPair);
}

void UResourceSubsystem::GenerateCubeMesh()
{
	/* FMesh 생성 */
	FVertex v1_1{}; // 정면
	v1_1.POSITION = { -10.0f, 10.0f, -10.0f, 1.0f };
	v1_1.TEXCOORD = { 0.0f, 0.0f };
	FVertex v1_2{};
	v1_2.POSITION = { 10.0f, 10.0f, -10.0f, 1.0f };
	v1_2.TEXCOORD = { 0.0f, 1.0f };
	FVertex v1_3{};
	v1_3.POSITION = { -10.0f, -10.0f, -10.0f, 1.0f };
	v1_3.TEXCOORD = { 1.0f, 0.0f };
	FVertex v1_4{};
	v1_4.POSITION = { 10.0f, -10.0f, -10.0f, 1.0f };
	v1_4.TEXCOORD = { 1.0f, 1.0f };

	FVertex v2_1{}; // 왼쪽 면
	v2_1.POSITION = { -10.0f, 10.0f, 10.0f, 1.0f };
	v2_1.TEXCOORD = { 1.0f, 0.0f };
	FVertex v2_2{};
	v2_2.POSITION = { -10.0f, 10.0f, -10.0f, 1.0f };
	v2_2.TEXCOORD = { 1.0f, 1.0f };
	FVertex v2_3{};
	v2_3.POSITION = { -10.0f, -10.0f, 10.0f, 1.0f };
	v2_3.TEXCOORD = { 0.0f, 0.0f };
	FVertex v2_4{};
	v2_4.POSITION = { -10.0f, -10.0f, -10.0f, 1.0f };
	v2_4.TEXCOORD = { 0.0f, 1.0f };

	FVertex v3_1{}; // 우측 면
	v3_1.POSITION = { 10.0f, 10.0f, -10.0f, 1.0f };
	v3_1.TEXCOORD = { 1.0f, 0.0f };
	FVertex v3_2{};
	v3_2.POSITION = { 10.0f, 10.0f, 10.0f, 1.0f };
	v3_2.TEXCOORD = { 1.0f, 1.0f };
	FVertex v3_3{};
	v3_3.POSITION = { 10.0f, -10.0f, -10.0f, 1.0f };
	v3_3.TEXCOORD = { 0.0f, 0.0f };
	FVertex v3_4{};
	v3_4.POSITION = { 10.0f, -10.0f, 10.0f, 1.0f };
	v3_4.TEXCOORD = { 0.0f, 1.0f };

	FVertex v4_1{}; // 뒷면
	v4_1.POSITION = { 10.0f, 10.0f, 10.0f, 1.0f };
	v4_1.TEXCOORD = { 0.0f, 0.0f };
	FVertex v4_2{};
	v4_2.POSITION = { -10.0f, 10.0f, 10.0f, 1.0f };
	v4_2.TEXCOORD = { 0.0f, 1.0f };
	FVertex v4_3{};
	v4_3.POSITION = { 10.0f, -10.0f, 10.0f, 1.0f };
	v4_3.TEXCOORD = { 1.0f, 0.0f };
	FVertex v4_4{};
	v4_4.POSITION = { -10.0f, -10.0f, 10.0f, 1.0f };
	v4_4.TEXCOORD = { 1.0f, 1.0f };

	FVertex v5_1{}; // 윗면
	v5_1.POSITION = { -10.0f, 10.0f, 10.0f, 1.0f };
	v5_1.TEXCOORD = { 1.0f, 0.0f };
	FVertex v5_2{};
	v5_2.POSITION = { 10.0f, 10.0f, 10.0f, 1.0f };
	v5_2.TEXCOORD = { 1.0f, 1.0f };
	FVertex v5_3{};
	v5_3.POSITION = { -10.0f, 10.0f, -10.0f, 1.0f };
	v5_3.TEXCOORD = { 0.0f, 0.0f };
	FVertex v5_4{};
	v5_4.POSITION = { 10.0f, 10.0f, -10.0f, 1.0f };
	v5_4.TEXCOORD = { 0.0f, 1.0f };

	FVertex v6_1{}; // 아랫면
	v6_1.POSITION = { -10.0f, -10.0f, -10.0f, 1.0f };
	v6_1.TEXCOORD = { 1.0f, 0.0f };
	FVertex v6_2{};
	v6_2.POSITION = { 10.0f, -10.0f, -10.0f, 1.0f };
	v6_2.TEXCOORD = { 1.0f, 1.0f };
	FVertex v6_3{};
	v6_3.POSITION = { -10.0f, -10.0f, 10.0f, 1.0f };
	v6_3.TEXCOORD = { 0.0f, 0.0f };
	FVertex v6_4{};
	v6_4.POSITION = { 10.0f, -10.0f, 10.0f, 1.0f };
	v6_4.TEXCOORD = { 0.0f, 1.0f };

	FMesh Cube;
	Cube.Vertices.push_back(v1_1);
	Cube.Vertices.push_back(v1_2);
	Cube.Vertices.push_back(v1_3);
	Cube.Vertices.push_back(v1_4);
	Cube.Vertices.push_back(v2_1);
	Cube.Vertices.push_back(v2_2);
	Cube.Vertices.push_back(v2_3);
	Cube.Vertices.push_back(v2_4);
	Cube.Vertices.push_back(v3_1);
	Cube.Vertices.push_back(v3_2);
	Cube.Vertices.push_back(v3_3);
	Cube.Vertices.push_back(v3_4);
	Cube.Vertices.push_back(v4_1);
	Cube.Vertices.push_back(v4_2);
	Cube.Vertices.push_back(v4_3);
	Cube.Vertices.push_back(v4_4);
	Cube.Vertices.push_back(v5_1);
	Cube.Vertices.push_back(v5_2);
	Cube.Vertices.push_back(v5_3);
	Cube.Vertices.push_back(v5_4);
	Cube.Vertices.push_back(v6_1);
	Cube.Vertices.push_back(v6_2);
	Cube.Vertices.push_back(v6_3);
	Cube.Vertices.push_back(v6_4);

	for (int i = 0; i < 6; i++)
	{
		Cube.Indexes.push_back(i * 4 + 0);
		Cube.Indexes.push_back(i * 4 + 1);
		Cube.Indexes.push_back(i * 4 + 2);
		Cube.Indexes.push_back(i * 4 + 1);
		Cube.Indexes.push_back(i * 4 + 3);
		Cube.Indexes.push_back(i * 4 + 2);
	}

	Cube.PrimitiveTopology = D3D11_PRIMITIVE_TOPOLOGY::D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;

	std::pair<string, FMesh> Pair{};
	Pair.first = "Cube";
	Pair.second = Cube;

	Meshes.insert(Pair);

	/* ID3D11Buffer 생성 */
	ComPtr<ID3D11Buffer> VertexBuffer{};

	D3D11_BUFFER_DESC VertexBufferDesc{};
	VertexBufferDesc.ByteWidth = (UINT)(sizeof(Cube.Vertices[0]) * Cube.Vertices.size());
	VertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	VertexBufferDesc.CPUAccessFlags = 0;
	VertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	D3D11_SUBRESOURCE_DATA VertexBufferSubresourceData;
	VertexBufferSubresourceData.pSysMem = &Cube.Vertices[0];

	if (S_OK != GEngine->RenderSubsystem->GetDevice()->CreateBuffer(&VertexBufferDesc, &VertexBufferSubresourceData, VertexBuffer.GetAddressOf()))
	{
		CRITICAL_ERROR(BUFFER_CREATE_FAILED_TEXT);
	}

	std::pair<string, ComPtr<ID3D11Buffer>> VertexBufferPair{};
	VertexBufferPair.first = "Cube";
	VertexBufferPair.second = VertexBuffer;
	GEngine->RenderSubsystem->VertexBuffers.insert(VertexBufferPair);


	/* IndexBuffer 생성 */
	ComPtr<ID3D11Buffer> IndexBuffer{};

	D3D11_BUFFER_DESC IndexBufferInfo{};
	IndexBufferInfo.ByteWidth = (UINT)(sizeof(Cube.Indexes[0]) * Cube.Indexes.size());
	IndexBufferInfo.BindFlags = D3D11_BIND_INDEX_BUFFER;
	IndexBufferInfo.CPUAccessFlags = 0;
	IndexBufferInfo.Usage = D3D11_USAGE_DEFAULT;

	D3D11_SUBRESOURCE_DATA IndexBufferSubresourceData{};
	IndexBufferSubresourceData.pSysMem = &Cube.Indexes[0];

	if (S_OK != GEngine->RenderSubsystem->GetDevice()->CreateBuffer(&IndexBufferInfo, &IndexBufferSubresourceData, IndexBuffer.GetAddressOf()))
	{
		CRITICAL_ERROR(BUFFER_CREATE_FAILED_TEXT);
	}

	std::pair<string, ComPtr<ID3D11Buffer>> IndexBufferPair{};
	IndexBufferPair.first = "Cube";
	IndexBufferPair.second = IndexBuffer;
	GEngine->RenderSubsystem->IndexBuffers.insert(IndexBufferPair);
}

unordered_map<string, FMesh>& UResourceSubsystem::GetMeshes()
{
	return Meshes;
}
