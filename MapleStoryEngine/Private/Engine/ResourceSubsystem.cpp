#include "EnginePch.h"
#include "Utils/Encoding.h"
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

void UResourceSubsystem::GenerateDefaultMeshes()
{
	this->GeneratePlaneMesh();
}

void UResourceSubsystem::GeneratePlaneMesh()
{
	/* FMesh 생성 */
	FVertex v1{};
	v1.POSITION = { -1.0f, 1.0f, 0.0f };
	v1.TEXCOORD = { 0.0f, 0.0f };
	FVertex v2{};
	v2.POSITION = { 1.0f, 1.0f, 0.0f };
	v2.TEXCOORD = { 1.0f, 0.0f };
	FVertex v3{};
	v3.POSITION = { -1.0f, -1.0f, 0.0f };
	v3.TEXCOORD = { 0.0f, 1.0f };
	FVertex v4{};
	v4.POSITION = { 1.0f, -1.0f, 0.0f };
	v4.TEXCOORD = { 1.0f, 1.0f };

	FMesh Plane;
	Plane.Vertices.push_back(v1);
	Plane.Vertices.push_back(v2);
	Plane.Vertices.push_back(v3);
	Plane.Vertices.push_back(v4);

	Plane.Indexes.push_back(0);
	Plane.Indexes.push_back(2);
	Plane.Indexes.push_back(1);

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
	GEngine->RenderSubsystem->D3DVertexBuffers.insert(VertexBufferPair);


	/* IndexBuffer 생성 */
	ComPtr<ID3D11Buffer> IndexBuffer{};

	D3D11_BUFFER_DESC IndexBufferInfo{};
	IndexBufferInfo.ByteWidth = (UINT)(sizeof(Plane.Indexes[0]) * Plane.Indexes.size());
	IndexBufferInfo.BindFlags = D3D11_BIND_INDEX_BUFFER;
	IndexBufferInfo.CPUAccessFlags = 0;
	IndexBufferInfo.Usage = D3D11_USAGE_DEFAULT;

	D3D11_SUBRESOURCE_DATA IndexBufferSubresourceData{};
	IndexBufferSubresourceData.pSysMem = &Plane.Indexes[0];

	if (S_OK != GEngine->RenderSubsystem->GetDevice()->CreateBuffer(&IndexBufferInfo, &VertexBufferSubresourceData, IndexBuffer.GetAddressOf()))
	{
		CRITICAL_ERROR(BUFFER_CREATE_FAILED_TEXT);
	}

	std::pair<string, ComPtr<ID3D11Buffer>> IndexBufferPair{};
	IndexBufferPair.first = "Plane";
	IndexBufferPair.second = IndexBuffer;
	GEngine->RenderSubsystem->D3DIndexBuffers.insert(IndexBufferPair);
}

unordered_map<string, FMesh>& UResourceSubsystem::GetMeshes()
{
	return Meshes;
}
