#pragma once
#include "EnginePch.h"
#include "EngineSubsystem.h"
#include "Math/Mesh.h"

class UResourceSubsystem : public UEngineSubsystem
{
public:
	/* �����ڿ� �������̵� */
	void Tick(float fDeltaTime) override;

	void LateInit() override;

public:
	FMesh& GetMesh(string strKey);

	ComPtr<ID3D11Buffer>& GetD3DVertexBuffer(string strKey);

private:
	void GenerateDefaultMeshes();

	void GeneratePlaneMesh();

public:
	unordered_map<string, FMesh>& GetMeshes();

private:
	/* �׷��� ���ҽ� */
	unordered_map<string, FMesh> Meshes;
	unordered_map<string, ComPtr<ID3D11Buffer>> D3DVertexBuffers;
	unordered_map<string, ComPtr<ID3D11InputLayout>> D3DInputLayouts;
	unordered_map<string, ComPtr<ID3DBlob>> D3DVSShaderCodeBlobs;
	unordered_map<string, ComPtr<ID3DBlob>> D3DVSErrorCodeBlobs;
};

