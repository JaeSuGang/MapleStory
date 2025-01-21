#include "EnginePch.h"
#include "Utils/Utils.h"
#include "Engine/ResourceSubsystem.h"
#include "RenderCore/RenderSubsystem.h"
#include "Math/Mesh.h"
#include "Engine/Engine.h"
#include "RenderCore/Texture.h"

UResourceSubsystem::UResourceSubsystem()
{
	this->SetWorkingDirectory();
}

void UResourceSubsystem::Tick(float fDeltaTime)
{
}

void UResourceSubsystem::LateInit()
{
	this->SetMissingTexture();

	this->GenerateDefaultMeshes();
}


void UResourceSubsystem::AddNewMesh(string strKey, FMesh NewMesh)
{
	int nSize = (int)Meshes.size();
	std::pair<string, int> MapPair = { strKey, nSize };
	StringMappedMeshIDs.insert(MapPair);
	Meshes.push_back(NewMesh);
}

FMesh& UResourceSubsystem::GetMeshByID(int nID)
{
	return Meshes[nID];
}

int UResourceSubsystem::GetMeshIDByName(string strKey)
{

	auto FindIter = StringMappedMeshIDs.find(strKey);

	if (FindIter != StringMappedMeshIDs.end())
	{
		return FindIter->second;
	}
	else
	{
		GEngine->DebugLog("Tried To Find Invalid Mesh Name : " + strKey, 2);
		return -1;
	}
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

void UResourceSubsystem::LoadFolderRecursively(string strDirectoryName)
{
	std::filesystem::directory_iterator DirectoryIter{ strDirectoryName };

	while (!DirectoryIter._At_end())
	{
		std::filesystem::path ChildPath = *DirectoryIter;

		if (DirectoryIter->is_directory())
		{
			this->LoadFolderRecursively(ChildPath.string());
		}

		if (ChildPath.extension().string() == ".png")
		{
			this->LoadTextureFile(ChildPath.string());
		}

		++DirectoryIter;
	}
}

void UResourceSubsystem::LoadFolder(string strDirectoryName)
{
	std::filesystem::directory_iterator DirectoryIter{ strDirectoryName };

	while (!DirectoryIter._At_end())
	{
		std::filesystem::path ChildPath = *DirectoryIter;

		if (ChildPath.extension().string() == ".png")
		{
			this->LoadTextureFile(ChildPath.string());
		}

		++DirectoryIter;
	}
}

/* TextureID甫 府畔 */
int UResourceSubsystem::LoadTextureFile(string strPath)
{
	HRESULT hr;
	std::wstring wstrPath = Utils::StringToWString(strPath);

	ComPtr<ID3D11ShaderResourceView> NewSRV;
	ComPtr<ID3D11Texture2D> NewD3DTexture;
	DirectX::ScratchImage NewScratchImage;
	DirectX::ScratchImage NewSRGBScratchImage;
	DirectX::TexMetadata NewTexMetadata;

	hr = DirectX::LoadFromWICFile(wstrPath.c_str(), DirectX::WIC_FLAGS_NONE, &NewTexMetadata, NewScratchImage);
	if (hr != S_OK)
	{
		// GEngine->DebugLog("Texture File Load Failed : " + strPath, 1);
		return 0;
	}

	hr = DirectX::CreateTexture(GEngine->RenderSubsystem->Device.Get(), NewScratchImage.GetImages(), NewScratchImage.GetImageCount(), NewScratchImage.GetMetadata(), (ID3D11Resource**)NewD3DTexture.GetAddressOf());
	if (hr != S_OK)
	{
		GEngine->DebugLog("Texture Creation Failed : " + strPath, 1);
		return 0;
	}

	hr = DirectX::CreateShaderResourceView(GEngine->RenderSubsystem->Device.Get(), NewScratchImage.GetImages(), NewScratchImage.GetImageCount(), NewScratchImage.GetMetadata(), NewSRV.GetAddressOf());
	if (hr != S_OK)
	{
		GEngine->DebugLog("SRV Creation Failed : " + strPath, 1);
		return 0;
	}

	D3D11_TEXTURE2D_DESC desc;
	NewD3DTexture.Get()->GetDesc(&desc);

	shared_ptr<UTexture> NewTexture{ new UTexture{} };
	NewTexture->Width = (unsigned int)NewTexMetadata.width;
	NewTexture->Height = (unsigned int)NewTexMetadata.height;

	NewTexture->Texture = NewD3DTexture;
	NewTexture->SRV = NewSRV;

	return GEngine->RenderSubsystem->AddNewTexture(strPath, NewTexture);
}

void UResourceSubsystem::SetMissingTexture()
{
	GEngine->RenderSubsystem->SetMissingTexture();
}

void UResourceSubsystem::GenerateDefaultMeshes()
{
	this->GeneratePlaneMesh();

	this->GenerateCubeMesh();

	this->GenerateLineMesh();
}

void UResourceSubsystem::GeneratePlaneMesh()
{
	/* FMesh 积己 */
	FVertex v1{};
	v1.POSITION = { -0.5f, 0.5f, 0.0f, 1.0f };
	v1.TEXCOORD = { 0.0f, 0.0f };
	FVertex v2{};
	v2.POSITION = { 0.5f, 0.5f, 0.0f, 1.0f };
	v2.TEXCOORD = { 1.0f, 0.0f };
	FVertex v3{};
	v3.POSITION = { -0.5f, -0.5f, 0.0f, 1.0f };
	v3.TEXCOORD = { 0.0f, 1.0f };
	FVertex v4{};
	v4.POSITION = { 0.5f, -0.5f, 0.0f, 1.0f };
	v4.TEXCOORD = { 1.0f, 1.0f };

	FMesh Plane{};
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

	this->AddNewMesh("Plane", Plane);

	/* ID3D11Buffer 积己 */
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

	GEngine->RenderSubsystem->AddNewVertexBuffer("Plane", VertexBuffer);

	/* IndexBuffer 积己 */
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

	GEngine->RenderSubsystem->AddNewIndexBuffer("Plane", IndexBuffer);
}

void UResourceSubsystem::GenerateCubeMesh()
{
	/* FMesh 积己 */
	FVertex v1_1{}; // 沥搁
	v1_1.POSITION = { -0.5f, 0.5f, -0.5f, 1.0f };
	v1_1.TEXCOORD = { 0.0f, 0.0f };
	FVertex v1_2{};
	v1_2.POSITION = { 0.5f, 0.5f, -0.5f, 1.0f };
	v1_2.TEXCOORD = { 0.0f, 1.0f };
	FVertex v1_3{};
	v1_3.POSITION = { -0.5f, -0.5f, -0.5f, 1.0f };
	v1_3.TEXCOORD = { 1.0f, 0.0f };
	FVertex v1_4{};
	v1_4.POSITION = { 0.5f, -0.5f, -0.5f, 1.0f };
	v1_4.TEXCOORD = { 1.0f, 1.0f };

	FVertex v2_1{}; // 哭率 搁
	v2_1.POSITION = { -0.5f, 0.5f, 0.5f, 1.0f };
	v2_1.TEXCOORD = { 1.0f, 0.0f };
	FVertex v2_2{};
	v2_2.POSITION = { -0.5f, 0.5f, -0.5f, 1.0f };
	v2_2.TEXCOORD = { 1.0f, 1.0f };
	FVertex v2_3{};
	v2_3.POSITION = { -0.5f, -0.5f, 0.5f, 1.0f };
	v2_3.TEXCOORD = { 0.0f, 0.0f };
	FVertex v2_4{};
	v2_4.POSITION = { -0.5f, -0.5f, -0.5f, 1.0f };
	v2_4.TEXCOORD = { 0.0f, 1.0f };

	FVertex v3_1{}; // 快螟 搁
	v3_1.POSITION = { 0.5f, 0.5f, -0.5f, 1.0f };
	v3_1.TEXCOORD = { 1.0f, 0.0f };
	FVertex v3_2{};
	v3_2.POSITION = { 0.5f, 0.5f, 0.5f, 1.0f };
	v3_2.TEXCOORD = { 1.0f, 1.0f };
	FVertex v3_3{};
	v3_3.POSITION = { 0.5f, -0.5f, -0.5f, 1.0f };
	v3_3.TEXCOORD = { 0.0f, 0.0f };
	FVertex v3_4{};
	v3_4.POSITION = { 0.5f, -0.5f, 0.5f, 1.0f };
	v3_4.TEXCOORD = { 0.0f, 1.0f };

	FVertex v4_1{}; // 缔搁
	v4_1.POSITION = { 0.5f, 0.5f, 0.5f, 1.0f };
	v4_1.TEXCOORD = { 0.0f, 0.0f };
	FVertex v4_2{};
	v4_2.POSITION = { -0.5f, 0.5f, 0.5f, 1.0f };
	v4_2.TEXCOORD = { 0.0f, 1.0f };
	FVertex v4_3{};
	v4_3.POSITION = { 0.5f, -0.5f, 0.5f, 1.0f };
	v4_3.TEXCOORD = { 1.0f, 0.0f };
	FVertex v4_4{};
	v4_4.POSITION = { -0.5f, -0.5f, 0.5f, 1.0f };
	v4_4.TEXCOORD = { 1.0f, 1.0f };

	FVertex v5_1{}; // 拉搁
	v5_1.POSITION = { -0.5f, 0.5f, 0.5f, 1.0f };
	v5_1.TEXCOORD = { 1.0f, 0.0f };
	FVertex v5_2{};
	v5_2.POSITION = { 0.5f, 0.5f, 0.5f, 1.0f };
	v5_2.TEXCOORD = { 1.0f, 1.0f };
	FVertex v5_3{};
	v5_3.POSITION = { -0.5f, 0.5f, -0.5f, 1.0f };
	v5_3.TEXCOORD = { 0.0f, 0.0f };
	FVertex v5_4{};
	v5_4.POSITION = { 0.5f, 0.5f, -0.5f, 1.0f };
	v5_4.TEXCOORD = { 0.0f, 1.0f };

	FVertex v6_1{}; // 酒阀搁
	v6_1.POSITION = { -0.5f, -0.5f, -0.5f, 1.0f };
	v6_1.TEXCOORD = { 1.0f, 0.0f };
	FVertex v6_2{};
	v6_2.POSITION = { 0.5f, -0.5f, -0.5f, 1.0f };
	v6_2.TEXCOORD = { 1.0f, 1.0f };
	FVertex v6_3{};
	v6_3.POSITION = { -0.5f, -0.5f, 0.5f, 1.0f };
	v6_3.TEXCOORD = { 0.0f, 0.0f };
	FVertex v6_4{};
	v6_4.POSITION = { 0.5f, -0.5f, 0.5f, 1.0f };
	v6_4.TEXCOORD = { 0.0f, 1.0f };

	FMesh Cube{};
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

	this->AddNewMesh("Cube", Cube);

	/* ID3D11Buffer 积己 */
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

	GEngine->RenderSubsystem->AddNewVertexBuffer("Cube", VertexBuffer);
	

	/* IndexBuffer 积己 */
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

	GEngine->RenderSubsystem->AddNewIndexBuffer("Cube", IndexBuffer);
}

void UResourceSubsystem::GenerateLineMesh()
{
	/* FMesh 积己 */
	FVertex v1{}; // 沥搁
	v1.POSITION = { 0.0f, 0.0f, 0.0f, 1.0f };
	v1.TEXCOORD = { 0.0f, 0.0f };
	v1.COLOR = { 0.0f, 1.0f, 0.0f, 1.0f };
	FVertex v2{};
	v2.POSITION = { 1.0f, 0.0f, 0.0f, 1.0f };
	v2.TEXCOORD = { 1.0f, 1.0f };
	v2.COLOR = { 0.0f, 1.0f, 0.0f, 1.0f };

	FMesh Line{};
	Line.Vertices.push_back(v1);
	Line.Vertices.push_back(v2);
	Line.Indexes.push_back(0);
	Line.Indexes.push_back(1);

	Line.PrimitiveTopology = D3D11_PRIMITIVE_TOPOLOGY_LINELIST;
	this->AddNewMesh("Line", Line);

	/* ID3D11Buffer 积己 */
	ComPtr<ID3D11Buffer> VertexBuffer{};

	D3D11_BUFFER_DESC VertexBufferDesc{};
	VertexBufferDesc.ByteWidth = (UINT)(sizeof(Line.Vertices[0]) * Line.Vertices.size());
	VertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	VertexBufferDesc.CPUAccessFlags = 0;
	VertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	D3D11_SUBRESOURCE_DATA VertexBufferSubresourceData;
	VertexBufferSubresourceData.pSysMem = &Line.Vertices[0];

	if (S_OK != GEngine->RenderSubsystem->GetDevice()->CreateBuffer(&VertexBufferDesc, &VertexBufferSubresourceData, VertexBuffer.GetAddressOf()))
	{
		CRITICAL_ERROR(BUFFER_CREATE_FAILED_TEXT);
	}

	GEngine->RenderSubsystem->AddNewVertexBuffer("Line", VertexBuffer);


	/* IndexBuffer 积己 */
	ComPtr<ID3D11Buffer> IndexBuffer{};

	D3D11_BUFFER_DESC IndexBufferInfo{};
	IndexBufferInfo.ByteWidth = (UINT)(sizeof(Line.Indexes[0]) * Line.Indexes.size());
	IndexBufferInfo.BindFlags = D3D11_BIND_INDEX_BUFFER;
	IndexBufferInfo.CPUAccessFlags = 0;
	IndexBufferInfo.Usage = D3D11_USAGE_DEFAULT;

	D3D11_SUBRESOURCE_DATA IndexBufferSubresourceData{};
	IndexBufferSubresourceData.pSysMem = &Line.Indexes[0];

	if (S_OK != GEngine->RenderSubsystem->GetDevice()->CreateBuffer(&IndexBufferInfo, &IndexBufferSubresourceData, IndexBuffer.GetAddressOf()))
	{
		CRITICAL_ERROR(BUFFER_CREATE_FAILED_TEXT);
	}

	GEngine->RenderSubsystem->AddNewIndexBuffer("Line", IndexBuffer);
}

