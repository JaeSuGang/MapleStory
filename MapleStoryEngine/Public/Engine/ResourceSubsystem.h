#pragma once
#include "EnginePch.h"
#include "EngineSubsystem.h"
#include "Math/Mesh.h"

class UResourceSubsystem : public UEngineSubsystem
{
public:
	/* 생성자와 오버라이드 */
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
	/* 그래픽 리소스 */
	unordered_map<string, FMesh> Meshes;
};

