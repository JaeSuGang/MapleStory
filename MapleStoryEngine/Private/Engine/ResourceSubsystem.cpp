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

	this->GenerateCubeMesh();
}

void UResourceSubsystem::GeneratePlaneMesh()
{
	/* FMesh 생성 */
	FVertex v1{};
	v1.POSITION = { -1.0f, 1.0f, 0.0f, 1.0f };
	v1.TEXCOORD = { 0.0f, 0.0f };
	FVertex v2{};
	v2.POSITION = { 1.0f, 1.0f, 0.0f, 1.0f };
	v2.TEXCOORD = { 1.0f, 0.0f };
	FVertex v3{};
	v3.POSITION = { -1.0f, -1.0f, 0.0f, 1.0f };
	v3.TEXCOORD = { 0.0f, 1.0f };
	FVertex v4{};
	v4.POSITION = { 1.0f, -1.0f, 0.0f, 1.0f };
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
	FVertex v1{};
	v1.POSITION = { -1.0f, 1.0f, -1.0f, 1.0f };
	v1.TEXCOORD = { 0.0f, 0.0f };
	FVertex v2{};
	v2.POSITION = { 1.0f, 1.0f, -1.0f, 1.0f };
	v2.TEXCOORD = { 1.0f, 0.0f };
	FVertex v3{};
	v3.POSITION = { -1.0f, -1.0f, -1.0f, 1.0f };
	v3.TEXCOORD = { 0.0f, 1.0f };
	FVertex v4{};
	v4.POSITION = { 1.0f, -1.0f, -1.0f, 1.0f };
	v4.TEXCOORD = { 1.0f, 1.0f };
	FVertex v5{};
	v5.POSITION = { -1.0f, 1.0f, 1.0f, 1.0f };
	v5.TEXCOORD = { 1.0f, 1.0f };
	FVertex v6{};
	v6.POSITION = { 1.0f, 1.0f, 1.0f, 1.0f };
	v6.TEXCOORD = { 0.0f, 1.0f };
	FVertex v7{};
	v7.POSITION = { -1.0f, -1.0f, 1.0f, 1.0f };
	v7.TEXCOORD = { 1.0f, 0.0f };
	FVertex v8{};
	v8.POSITION = { 1.0f, -1.0f, 1.0f, 1.0f };
	v8.TEXCOORD = { 0.0f, 0.0f };

	FMesh Cube;
	Cube.Vertices.push_back(v1);
	Cube.Vertices.push_back(v2);
	Cube.Vertices.push_back(v3);
	Cube.Vertices.push_back(v4);	
	Cube.Vertices.push_back(v5);
	Cube.Vertices.push_back(v6);
	Cube.Vertices.push_back(v7);
	Cube.Vertices.push_back(v8);

	// 앞
	Cube.Indexes.push_back(0);
	Cube.Indexes.push_back(1);
	Cube.Indexes.push_back(2);
	Cube.Indexes.push_back(1);
	Cube.Indexes.push_back(3);
	Cube.Indexes.push_back(2);

	// 왼
	Cube.Indexes.push_back(5);
	Cube.Indexes.push_back(0);
	Cube.Indexes.push_back(7);
	Cube.Indexes.push_back(0);
	Cube.Indexes.push_back(2);
	Cube.Indexes.push_back(7);

	// 오
	Cube.Indexes.push_back(1);
	Cube.Indexes.push_back(5);
	Cube.Indexes.push_back(3);
	Cube.Indexes.push_back(5);
	Cube.Indexes.push_back(7);
	Cube.Indexes.push_back(3);

	// 위
	Cube.Indexes.push_back(4);
	Cube.Indexes.push_back(5);
	Cube.Indexes.push_back(0);
	Cube.Indexes.push_back(5);
	Cube.Indexes.push_back(1);
	Cube.Indexes.push_back(0);

	// 아래
	Cube.Indexes.push_back(2);
	Cube.Indexes.push_back(3);
	Cube.Indexes.push_back(6);
	Cube.Indexes.push_back(3);
	Cube.Indexes.push_back(7);
	Cube.Indexes.push_back(6);

	// 뒤
	Cube.Indexes.push_back(5);
	Cube.Indexes.push_back(4);
	Cube.Indexes.push_back(7);
	Cube.Indexes.push_back(4);
	Cube.Indexes.push_back(6);
	Cube.Indexes.push_back(7);

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
