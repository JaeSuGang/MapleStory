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
	void SetWorkingDirectory();

	void CompileD3DVSShader();

	void CreateD3DInputLayout();

	void GenerateDefaultMeshes();

	void GeneratePlaneMesh();

public:
	unordered_map<string, FMesh>& GetMeshes();

private:

private:
	/* �׷��� ���ҽ� */
	unordered_map<string, FMesh> Meshes;
};

