#include "EnginePch.h"
#include "Utils/Encoding.h"
#include "Engine/ResourceSubsystem.h"
#include "Engine/RenderSubsystem.h"
#include "Math/Mesh.h"
#include "Engine/Engine.h"

void UResourceSubsystem::Tick(float fDeltaTime)
{
}

void UResourceSubsystem::LateInit()
{
	this->SetWorkingDirectory();

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

	D3D11_BUFFER_DESC BufferDesc{};
	BufferDesc.ByteWidth = (UINT)(sizeof(Plane.Vertices[0]) * Plane.Vertices.size());
	BufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	BufferDesc.CPUAccessFlags = 0;
	BufferDesc.Usage = D3D11_USAGE_DEFAULT;
	D3D11_SUBRESOURCE_DATA SubresourceData;
	SubresourceData.pSysMem = &Plane.Vertices[0];

	if (S_OK != GEngine->RenderSubsystem->GetDevice()->CreateBuffer(&BufferDesc, &SubresourceData, VertexBuffer.GetAddressOf()))
	{
		CRITICAL_ERROR(BUFFER_CREATE_FAILED_TEXT);
	}

	std::pair<string, ComPtr<ID3D11Buffer>> Pair2{};
	Pair2.first = "Plane";
	Pair2.second = VertexBuffer;

	GEngine->RenderSubsystem->D3DVertexBuffers.insert(Pair2);

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

	GEngine->RenderSubsystem->GetDevice()->CreateInputLayout(&InputLayouts[0], (UINT)InputLayouts.size(), );

}

unordered_map<string, FMesh>& UResourceSubsystem::GetMeshes()
{
	return Meshes;
}
