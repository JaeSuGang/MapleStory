#pragma once
#include "EnginePch.h"
#include "EngineSubsystem.h"
#include "Math/Mesh.h"

class UResourceSubsystem : public UEngineSubsystem
{
public:
	/* 생성자와 오버라이드 */
	UResourceSubsystem();

	void Tick(float fDeltaTime) override;

	void LateInit() override;

public:

	FMesh& GetMesh(string strKey);

private:
	void SetWorkingDirectory();

	void LoadTextureFile(string strPath);

	void GenerateDefaultMeshes();

	void GeneratePlaneMesh();

	void GenerateCubeMesh();

public:
	unordered_map<string, FMesh>& GetMeshes();

private:

private:
	/* 그래픽 리소스 */
	unordered_map<string, DirectX::TexMetadata> TexMetadatas;
	unordered_map<string, DirectX::ScratchImage> ScratchImages;
	unordered_map<string, FMesh> Meshes;
};

